#include "./PreComputation/MolapPreComputationBase.h"
#include "xodbc/XODBCDatabase.h"
#include "xodbc/XODBCRecordset.h"

using namespace xodbc;

namespace PreCmpt{

extern EXECUTESTATE PreErrorNo;

XODBCDatabase MolapPreComputationBase::InXDB;
XODBCRecordset* MolapPreComputationBase::pRS = NULL;

MolapPreComputationBase::MolapPreComputationBase(XCube* cube)
:PreComputationBase(cube),
 dimData(NULL),
 msrData(NULL),
 dimsNum(0),
 msrsNum(0),
 tuplesNum(0),
 card(NULL),
 InDir(""),
 aggWriter(NULL)
{
	cout<<"INFO: class MolapPreComputationBase--Constructor"<<endl;

	setAttribute();

	aggFunLib[0]=&MolapPreComputationBase::sumFun;
	aggFunLib[1]=&MolapPreComputationBase::countFun;
	aggFunLib[2]=&MolapPreComputationBase::avgFun;
	aggFunLib[3]=&MolapPreComputationBase::maxFun;
	aggFunLib[4]=&MolapPreComputationBase::minFun;
	aggFunLib[5]=&MolapPreComputationBase::firstFun;
	aggFunLib[6]=&MolapPreComputationBase::lastFun;
	aggFunLib[7]=&MolapPreComputationBase::distinctFun;
	aggFunLib[8]=&MolapPreComputationBase::mediumFun;
}

MolapPreComputationBase::~MolapPreComputationBase()
{
	cout<<"INFO: class MolapPreComputation--Destructor"<<endl;

	if ( dimData && msrData )
	{
		for ( int i = 0; i < tuplesNum; ++i )
		{
			delete[] dimData[i];
			delete[] msrData[i];
		}
		delete[] dimData;
		delete[] msrData;
 	}

	if ( card )
	{
		delete[] card;
	}

	if ( aggWriter )
	{
		delete aggWriter;
	}
}

void MolapPreComputationBase::setAttribute()
{
	cubeName = cube->getName();
	XSchema* schema = cube->getSchema();
	schemaName = schema->getName();
	
	DataSource* datasource=schema->getDataSource();
	if ( datasource->getDSType() == DataSource::DATABASETYPE )
	{ 
		inputType = DB;

		if ( !InXDB.IsOpen() )
		{
			string URL = datasource->getURL();
			string username = datasource->getUserName();
			string password = datasource->getPassWord();
			try
			{
				InXDB.Open(URL,username,password,XODBCDatabase::openReadOnly);
				DWConfiguration &dwConfig = DWConfiguration::instance();
				dwConfig.addConfig("System","../../DWServer/conf/system-config.xml");
				DWConfig *config = DWConfiguration::instance().getConfig("System");
				
				InXDB.SetQueryTimeout(atoi(config->getValue("ConfigurationSettings.PrecmptQueryTime").c_str()));
				cout<<"INFO: has connect da"<<endl;
			}
			catch (XODBCException* e)
			{
				XODBCError error;
				e->GetError(error);
				cout<<"Error: errorMessage--"<<error.GetErrorText()<<endl;
				cout<<"Error: errorID--"<<error.GetState()<<endl;
				string errorMessage = "class MolapPreComputationBase--Connect DA failed";
				PreErrorNo = DB_OPER_FAILED;
				throw PreCmptException(errorMessage);
			}
	
		}
		
	}
	else
	{
		//获取数据源InDir
		inputType = TXT;
		
		DWConfiguration &dwConfig = DWConfiguration::instance();
		dwConfig.addConfig("System","../../DWServer/conf/system-config.xml");
		DWConfig *config = DWConfiguration::instance().getConfig("System");
		
		InDir = config->getValue("ConfigurationSettings.DataDir");
	}

}

string MolapPreComputationBase::buildSQL()
{
	vector<Dimension *> &dimensions = this->cube->getDimensions();
	vector<Measure *> &measures = this->cube->getMeasures();

	set<string> dimensionTables;
	set<string> dimensionJOINfacts;

	string facttablename = toLower(this->cube->getFactTable());
	string selectSQL="select ";

	string formSQL=" from ";
	string whereSQL = " where ";
   
	for( int i=0; i < dimensions.size(); i++ )
	{
		string dimTableToInsert = dimensions[i]->getDefaultHierarchy()->getFactTable();
        dimTableToInsert = toLower(dimTableToInsert);
		if (dimensionTables.find(dimTableToInsert) == dimensionTables.end() && dimTableToInsert != facttablename )
		{	
			dimensionTables.insert(dimTableToInsert);
			formSQL+=dimTableToInsert+",";
		}

		vector<Hierarchy*> hierarchies = dimensions[i]->getHierarchies();
		vector<Level*> levels;
		column levelcolumns;
		string temp;

		for (int ii=0;ii<hierarchies.size();ii++)
		{
			string temp = hierarchies[ii]->getFactTable()+"."+hierarchies[ii]->getPrimaryKey()
				+"="+this->cube->getFactTable()+"."+dimensions[i]->getForeignKey();
			if (dimensionJOINfacts.find(temp) == dimensionJOINfacts.end())
			{
				dimensionJOINfacts.insert(temp);
				whereSQL+=temp+" and ";
			}
			levels = hierarchies[ii]->getLeveles();
            
			for (int j=0;j<levels.size();j++)
			{
				bool isAllLevel = levels[j]->isAllLevel();
				if(!isAllLevel)
				{			 
					if (levelcolumns.find(levels[j]->getColumn()) == levelcolumns.end())
					{
						string t=hierarchies[ii]->getFactTable()+"."+levels[j]->getColumn();
						string t1=dimensions[i]->getName()+"."+hierarchies[ii]->getName()+"."+levels[j]->getName();  //20071009 added
						selectSQL+=t+",";
						levelcolumns.insert(levels[j]->getColumn());
						dimsNum++;
		    			hdrData.push_back(t1);
					}
				}
			
			}
		}

	}

	formSQL+=facttablename;
	for (i=0;i<measures.size();i++)
	{
		selectSQL += this->cube->getFactTable()+"."+measures[i]->getColumn()+",";
		addAggFunOrder(measures[i]->getAggregator());
		string headoutstr = string("Measures.Measures.") + measures[i]->getName();
		hdrData.push_back(headoutstr);
		msrsNum++;
	}

	selectSQL = selectSQL.substr(0,selectSQL.length()-1);
	if ( whereSQL != " where " )
		whereSQL = whereSQL.substr(0,whereSQL.length()-5);
	string allSQL = selectSQL+formSQL+whereSQL;
	
	return allSQL;
}

inline void MolapPreComputationBase::addAggFunOrder(const string& aggFunType)
{
	if(aggFunType == "sum")
		aggFunOrder.push_back(0);
	else if(aggFunType == "count")
		aggFunOrder.push_back(1);
	else if(aggFunType == "avg")
		aggFunOrder.push_back(2);
	else if(aggFunType == "max")
		aggFunOrder.push_back(3);
	else if(aggFunType == "min")
		aggFunOrder.push_back(4);
	else if(aggFunType == "first")
		aggFunOrder.push_back(5);
	else if(aggFunType == "last")
		aggFunOrder.push_back(6);
	else if(aggFunType == "distinct")
		aggFunOrder.push_back(7);
	else if(aggFunType == "medium")
		aggFunOrder.push_back(8);
	else
	{
		aggFunOrder.push_back(0);
	}
}

void MolapPreComputationBase::loadData()
{
	switch ( inputType )
	{
		case DB:
		{
			loadDataTable();
			break;
		}
		case TXT:
		{
			loadDataTxt();
			break;
		}
		default: 
		{
			PreErrorNo = LOAD_DATA_FAILED;
			string errorMessage = "ambiguous when load data";
			throw PreCmptException(errorMessage);
		}
	}
}

void MolapPreComputationBase::loadNextData( int start, int end , string partitionNum )
{
	switch ( inputType )
	{
		case DB:
		{
			loadDataTable( start, end );
			break;
		}
		case TXT:
		{
			loadDataTxt( start, end );
			break;
		}
		default: 
		{
			PreErrorNo = LOAD_DATA_FAILED;
			string errorMessage = "ambiguous when load data";
			throw PreCmptException(errorMessage);
		}
	}
}

void MolapPreComputationBase::loadDataTable( int start, int end )
{
	assert( start >= 0 && end >= 0 );
	assert( end >= start );

	string SQL = buildSQL();
	try{
		int i = 0;
		int j = 0;
		if ( pRS == NULL )
		{
			pRS = new XODBCRecordset(&InXDB);
			pRS->Open(XODBCRecordset::forwardOnly,SQL);
		}
		
		Mapper* columncards = NULL;
		dimData = NULL;

		int maxRecordNum = end-start+1;
		columncards = new Mapper[dimsNum];
		dimData = new int*[maxRecordNum];
		msrData = new double*[maxRecordNum];
		for ( i = 0; i<maxRecordNum; i++ )
		{
			dimData[i]=new int[dimsNum];
			msrData[i]=new double[msrsNum];
		}

		string value;
		
		card = new int[dimsNum];		
		for ( i = 0; i < dimsNum; ++i )
		{
			card[i] = 0;
		}

		tuplesNum = 0;
		mapData = new string[dimsNum];
		for ( i = 0; i < dimsNum; ++i )
		{
			mapData[i].reserve(10*maxRecordNum);
		}
		
		while ( !pRS->IsEOF() && tuplesNum<maxRecordNum )
		{
			for ( i = 0; i < dimsNum; ++i )
			{
				pRS->GetFieldValue( i, value );
				Mapper::iterator it = columncards[i].find(value);
				if ( it != columncards[i].end() )
				{
					dimData[j][i]=it->second;
				}
 				else
				{
					card[i]++;
					dimData[j][i] = columncards[i].size()+1;
					columncards[i][value] = dimData[j][i];

					mapData[i] += value + "\n";
				}
			}
			for ( ; i < msrsNum+dimsNum; ++i )
			{
				pRS->GetFieldValue(i,value);
				//如果value不是数字的话，会出错
				msrData[j][i-dimsNum]=atof(value.c_str());
			}
			++j;
			++tuplesNum;
			pRS->MoveNext();
		}

		if ( tuplesNum < maxRecordNum )
		{
			pRS->Close();
			InXDB.Close();
			delete pRS;
		}
		delete[] columncards;
	}
	catch(XODBCException e)
	{
		InXDB.Close();
		PreErrorNo = DB_OPER_FAILED;
		string errorMessage = "Execute select SQL "+SQL+" failed";
		throw PreCmptException(errorMessage);
	}
}

void MolapPreComputationBase::loadDataTxt( int start, int end )
{
	assert( start >= 0 && end >= 0 );
	assert( end >= start );

	char* delimiter = "\t";
	int i = 0;
	int j = 0;
	int k = 0;
	int maxRecordNum = end-start+1;

	// open data file
	DFHandle df;
	if ( !df.Open(InDir.c_str()) )
	{
		PreErrorNo = FILE_OPER_FAILED;
		string errorMessage = "open "+InDir+" failed";
		throw PreCmptException(errorMessage);
	}

	//TID tid;
	FID fid;
	char field[MAXTUPLELEN];
	TupleHandle tHandle(delimiter);

	//read the first line of the data
	df.GetNextTuple(tHandle);
	while (tHandle.GetNextField(field, sizeof(field), fid))
	{
		string tmp = field;
		int pos = tmp.find("measures.");
		if (pos < 0)
		{
			++dimsNum;
		}
		else
		{
			pos = tmp.rfind(",");
			string aggFunType = tmp.substr(pos+1);
			addAggFunOrder(aggFunType);
			++msrsNum;
		}
		hdrData.push_back(tmp);
	}	

	//init dimData and msrData
	dimData = new int* [maxRecordNum];
	msrData = new double* [maxRecordNum];
	for ( i = 0; i < maxRecordNum; ++i )
	{
		dimData[i] = new int[dimsNum];
		msrData[i] = new double[msrsNum];
	}

	Mapper *mapper = new Mapper[dimsNum];
	card = new int[dimsNum];
	for ( i = 0; i < dimsNum; ++i )
		card[i] = 0;

	i = 0;
	df.ReWind();
	df.GetNextTuple(tHandle);  //skip the header line

	mapData = new string[dimsNum];

	//position to the start line
	while( start>i++ && df.GetNextTuple(tHandle) );
	
	i = 0;	
	tuplesNum = 0;
	while( df.GetNextTuple(tHandle) && tuplesNum < maxRecordNum )
	{
		j = 0;
		k = 0;

		//tHandle.GetTid(tid);
		while(tHandle.GetNextField(field, sizeof(field), fid))
		{
			if ( j < dimsNum)
			{
				//find field in the map table
				Mapper::iterator lb = mapper[j].lower_bound(field);
				if(lb != mapper[j].end() && !(mapper[j].key_comp()(field, lb->first)))
				{
					dimData[i][j] = lb->second;
				}
				else
				{
					card[j] ++;
					mapper[j].insert(lb, Mapper::value_type(field, card[j]));
					dimData[i][j] = card[j];

					mapData[j] += string(field) + "\n";
				}
				++j;
			}
			else if( k < msrsNum)
			{
				msrData[i][k] = atof(field);
				++k;
			}
		}
		++i;
		++tuplesNum;
	}

	delete[] mapper;

	df.Close();
}

void MolapPreComputationBase::loadDataTable()
{
	string SQL = buildSQL();

	try{
		XODBCRecordset XRS(&InXDB);
		Mapper* columncards = NULL;
		dimData = NULL;

		XRS.Open(XODBCRecordset::snapshot,SQL);

		long recordnumber = 0;
		int columnnumber =0;

		//统计记录个数
    	XODBCRecordset conutXRS(&InXDB);
		string countSQL="select count(*) from "+cube->getFactTable();
		conutXRS.Open(XODBCRecordset::forwardOnly,countSQL);
		string countstring="0";
		conutXRS.GetFieldValue(0,countstring);
		recordnumber = stoi(countstring);
		conutXRS.Close();

		cout<<"INFO: recordnumber: "<<recordnumber<<endl;
		
		columnnumber = XRS.GetFieldCount();
		if (columnnumber!=0 && recordnumber!=0)
		{
			columncards = new Mapper[dimsNum];
			dimData = new int*[recordnumber];
			msrData = new double*[recordnumber];
			for (int i=0;i<recordnumber;i++)
			{
				dimData[i]=new int[dimsNum];
				msrData[i]=new double[msrsNum];
			}
		}

		tuplesNum=recordnumber;

		string value;
		int i = 0;
		int j = 0;
		
		card = new int[dimsNum];		
		for ( i = 0; i < dimsNum; ++i )
		{
			card[i] = 0;
		}

		mapData = new string[dimsNum];
		for ( i = 0; i < dimsNum; ++i )
		{
			mapData[i].reserve( 10*tuplesNum );	
		}

		while( !XRS.IsEOF() )
		{
			for ( i = 0; i < dimsNum; ++i )
			{
				XRS.GetFieldValue( i, value );
				Mapper::iterator it = columncards[i].find(value);
				if ( it != columncards[i].end() )
				{
					dimData[j][i]=it->second;
				}
 				else
				{
					card[i]++;
					dimData[j][i] = columncards[i].size()+1;
					columncards[i][value] = dimData[j][i];

					mapData[i] += value + "\n";
				}
			}

			for ( ; i < msrsNum+dimsNum; ++i )
			{
				XRS.GetFieldValue(i,value);
				//如果value不是数字的话，会出错
				msrData[j][i-dimsNum]=atof(value.c_str());
			}
			j++;
			XRS.MoveNext();
		}

		if ( columncards != NULL )
		{
			delete[] columncards;
			columncards=NULL;
		}
		XRS.Close();
		InXDB.Close();
	}
	catch(XODBCException e)
	{
		InXDB.Close();
		PreErrorNo = DB_OPER_FAILED;
		string errorMessage = "Execute select SQL "+SQL+" failed";
		throw PreCmptException(errorMessage);
	}
}

void MolapPreComputationBase::loadDataTxt()
{
	int i = 0;
	int j = 0;
	int k = 0;
	char* delimiter = "\t";

	// open data file
	DFHandle df;
	if (!df.Open(InDir.c_str()))
	{
		PreErrorNo = FILE_OPER_FAILED;
		string errorMessage = "open "+InDir+" failed";
		throw PreCmptException(errorMessage);
	}

	FID fid;
	char field[MAXTUPLELEN];
	TupleHandle tHandle(delimiter);

	//read the first line of the data
	df.GetNextTuple(tHandle);
	while(tHandle.GetNextField(field, sizeof(field), fid))
	{	
		string tmp = field;
		int pos = tmp.find("measures.");
		if(pos < 0)
		{
			++dimsNum;
		}
		else
		{
			pos = tmp.rfind(",");
			string aggFunType = tmp.substr(pos + 1);
			addAggFunOrder(aggFunType);
	    	++msrsNum;
		}
		hdrData.push_back(tmp);
	}

	while(df.GetNextTuple(tHandle))
	{
		++tuplesNum;
	}

	//init dimData and msrData
	dimData = new int* [tuplesNum];
	msrData = new double* [tuplesNum];
	for(i = 0; i < tuplesNum; i++)
	{
		dimData[i] = new int[dimsNum];
		msrData[i] = new double[msrsNum];
	}

	Mapper *mapper = new Mapper[dimsNum];

	card = new int[dimsNum];
	for(i = 0; i < dimsNum; i++)
	{
		card[i] = 0;
	}

	i = 0;
	df.ReWind();
	df.GetNextTuple(tHandle);  //skip the header line

	mapData = new string[dimsNum];
	while(df.GetNextTuple(tHandle))
	{
		j = 0;
		k = 0;
		while(tHandle.GetNextField(field, sizeof(field), fid))
		{
			if ( j < dimsNum )
			{
				Mapper::iterator lb = mapper[j].lower_bound(field);
				if ( lb != mapper[j].end() && !(mapper[j].key_comp()(field, lb->first)))
				{
					dimData[i][j] = lb->second;
				}
				else
				{
					++card[j];
					mapper[j].insert(lb, Mapper::value_type(field, card[j]));
					dimData[i][j] = card[j];

					mapData[j] += string(field) + "\n";
				}
				++j;
			}
			else if ( k < msrsNum )
			{
				msrData[i][k] = atof(field);
				++k;
			}
		}
		++i;
	}

	delete[] mapper;
	df.Close();
}

double MolapPreComputationBase::sumFun( double **msrData, int bPos, int ePos, int msrNum )
{
	assert( bPos < ePos );
	double value = 0;
	for ( int i = bPos; i < ePos; i++ )
	{
		value += msrData[i][msrNum];
	}

	return value;
}

double MolapPreComputationBase::countFun( double **msrData, int bPos, int ePos, int msrNum )
{
	assert( bPos < ePos );
	return (ePos - bPos);
}

double MolapPreComputationBase::avgFun( double **msrData, int bPos, int ePos, int msrNum )
{
	assert( bPos < ePos );
	return sumFun(msrData, bPos, ePos, msrNum)/countFun(msrData, bPos, ePos, msrNum);
}

double MolapPreComputationBase::maxFun( double **msrData, int bPos, int ePos, int msrNum )
{
	assert( bPos < ePos );
	double value = msrData[bPos][msrNum];
	for(int i = bPos + 1; i < ePos; i++)
	{
		value = value > msrData[i][msrNum] ? value : msrData[i][msrNum];
	}

	return value;
}

double MolapPreComputationBase::minFun( double **msrData, int bPos, int ePos, int msrNum )
{
	assert( bPos < ePos );
	double value = msrData[bPos][msrNum];
	for(int i = bPos + 1; i < ePos; i++)
	{
		value = value < msrData[i][msrNum] ? value : msrData[i][msrNum];
	}

	return value;
}

double MolapPreComputationBase::firstFun( double **msrData, int bPos, int ePos, int msrNum )
{
	assert( bPos < ePos );
	return msrData[bPos][msrNum];
}

double MolapPreComputationBase::lastFun( double **msrData, int bPos, int ePos, int msrNum )
{
	assert( bPos < ePos );
	return msrData[ePos - 1][msrNum];
}

double MolapPreComputationBase::distinctFun( double **msrData, int bPos, int ePos, int msrNum )
{
	assert( bPos < ePos );
	int distinct = 0;
	set<double> data;
	pair<set<double>::iterator, bool> result;

	for (int i = bPos; i < ePos; i++)
	{
		result = data.insert(msrData[i][msrNum]);
		if (result.second)
			distinct++;
	}

	return distinct;
}

double MolapPreComputationBase::mediumFun( double **msrData, int bPos, int ePos, int msrNum )
{
	assert( bPos < ePos );
	int distinct = 0;
	int medium;
	int i;
	set<double> data;
	set<double>::iterator it;
	pair<set<double>::iterator, bool> result;

	for ( i = bPos; i < ePos; i++ )
	{
		result = data.insert(msrData[i][msrNum]);
		if (result.second)
			distinct++;
	}

	if (distinct % 2 == 0)
		medium = distinct/2  - 1;
	else
		medium = distinct/2;
	for (i = 0,it = data.begin(); i < medium; i++)
	{
		it++;
	}

	return (*it);
}

int MolapPreComputationBase::getTuplesNum()
{
	return tuplesNum;
}

}