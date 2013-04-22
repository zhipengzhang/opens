#include "./Query/MTCCQuery.h"

namespace QueryComputationMethods
{

MTCCQuery::MTCCQuery(ParsedMDX *parsedMDX_t,ALGTYPE algType_t)
:parsedMdx(parsedMDX_t),algType(algType_t)
{
	cout<<"INFO: class MTCCQuery--Constructor"<<endl;
	DWConfiguration &dwConfig = DWConfiguration::instance();
	dwConfig.addConfig("System","../../DWServer/conf/system-config.xml");
	DWConfig *config = NULL;	
	if ( !(config = dwConfig.getConfig("System")) )
	{
		string errorMessage = "open system-config.xml failed";
		throw QueryCmptException(errorMessage);
	}
	
	string qryThredNumStr = "";
	if ( (qryThredNumStr = config->getValue("ConfigurationSettings.PreCmptThreadNum")) == "" )
	{
		string errorMessage = "get ConfigurationSettings.PreCmptThreadNum value failed";
		throw QueryCmptException(errorMessage);
	}

	QuerythreadNum = atoi(qryThredNumStr.c_str());

	thread_set = new HANDLE[QuerythreadNum];
}

MTCCQuery::~MTCCQuery()
{
	delete [] thread_set;
}

void MTCCQuery::lock()
{
	EnterCriticalSection(&(gs.cs));
}

void MTCCQuery::unlock()
{
	LeaveCriticalSection(&(gs.cs));
}

unsigned __stdcall MTCCQuery::QueryChildThread( void* param )
{	
	MTCCQuery *pto=(MTCCQuery*) param;
	return pto->ThreadQueryWork();
}

DWORD MTCCQuery::ThreadQueryWork()
{
	HANDLE my_thread=GetCurrentThread();
	SuspendThread(my_thread);//子线程挂起，等待主进程分配任务
	int my_level;
	while(gs.flag)
	{	
		lock();
		if ( gs.flag == 0 )
		{
			unlock();
			break;
		}

		my_level = gs.level;
		gs.level++;
		if ( gs.level == splitNumber )
			gs.flag = 0;
		unlock();
		cout<<"INFO: level:"<<my_level<<endl;
		string partitionNum = itos(my_level);
		
		vector<Cell> cells;
		if ( algType == MOLAP )
		{
			MolapCCInvertListQuery molapCC(parsedMdx,partitionNum);
			lock();
			molapCC.getQueryPoints(parsedMdx);
			unlock();
			cells = molapCC.Cellquery();
		}
		else
		{
			RolapCCQuery rolapCC(parsedMdx,partitionNum);
 			lock();
 			rolapCC.getQueryPoints(parsedMdx);
 			unlock();
			cells = rolapCC.Cellquery();
		}

		//保存每个线程的结果
		lock();
		cout<<"INFO: level:"<<my_level<<" query complete"<<endl;
		Cells[my_level]=cells;
		unlock();
	}

	lock();
	gs.finished_threads++; //最后一个结束的线程唤醒主线程
	unlock();

	cout<<"INFO: Finish Thread Number"<<gs.finished_threads<<endl;
	if ( gs.finished_threads == QuerythreadNum )
	{
		int t = ResumeThread(host_thread);
	}

	return 0;
}

CellSet MTCCQuery::query()
{	   
	int i;
	InitializeCriticalSection(&(gs.cs));
	gs.finished_threads = 0;
	gs.flag = 1;
	gs.level = 0;
	DuplicateHandle( GetCurrentProcess(),
					 GetCurrentThread(),
					 GetCurrentProcess(),
					 &(host_thread),
					 0,
					 FALSE,
					 DUPLICATE_SAME_ACCESS );
	for ( i = 0; i < QuerythreadNum; ++i )
	{
		thread_set[i] = (HANDLE) _beginthreadex( NULL,
												 0,
												 MTCCQuery::QueryChildThread,
												 this,
												 0,
												 &(thread_id));
	} 
	
	Sleep(20);
	
	if ( algType == MOLAP )
	{			
		string cubeDir = "";
		string schemaName = parsedMdx->getSchemaName();
		string cubeName = parsedMdx->getCubeName();

		DWConfiguration &dwConfig = DWConfiguration::instance();
		dwConfig.addConfig("System","../../DWServer/conf/system-config.xml");
		DWConfig *config = NULL;	
		if ( !(config = dwConfig.getConfig("System")) )
		{
			string errorMessage = "open system-config.xml failed";
			throw QueryCmptException(errorMessage);
		}
		
		if ( (cubeDir = config->getValue("ConfigurationSettings.DataDir")) == "" )
		{
			string errorMessage = "get ConfigurationSettings.DataDir value failed";
			throw QueryCmptException(errorMessage);
		}
		
		cubeDir += "/" + schemaName + "_" + cubeName + "/UcellsInfo.txt";
		cout<<"INFO: class MTCCQuery--"<<cubeDir<<endl;	
		FILE* in = NULL;
		if( (in = fopen( cubeDir.c_str(), "r" )) == NULL )
		{
			string errorMessage = "open "+cubeDir+" failed";
			throw QueryCmptException(errorMessage);
		}

		fread( &splitNumber,sizeof(int),1,in );
		splitNumber++;
		cout<<"INFO: splitNumber:"<<splitNumber<<endl;
	}
	else
	{
		string schemaName = parsedMdx->getSchemaName();
		string cubeName = parsedMdx->getCubeName();
		XSchema* schema = XSchemas::instance().getSchema(schemaName);
		DataSource* datasource=schema->getDataSource();
		string URL = datasource->getURL();
		string username = datasource->getUserName();
		string password = datasource->getPassWord();	
		string selectSQL = "select * from agg"+schemaName+"_"+cubeName+"_UcellsInfo";
		XODBCDatabase InXDB;
		try
		{				
			InXDB.Open(URL,username,password,XODBCDatabase::openReadOnly);
			
			XODBCRecordset InXRS(&InXDB);
			InXRS.Open(XODBCRecordset::forwardOnly,selectSQL);
			
			string field;
			InXRS.GetFieldValue(0,field);
			splitNumber = atoi(field.c_str())+1;

			InXRS.Close();
			InXDB.Close();
		}
		catch (XODBCException* e)
		{
			InXDB.Close();
			XODBCError error;
			e->GetError(error);
			cout<<"ERROR: "<<error.GetErrorText()<<endl;
			cout<<"ERROR: "<<error.GetState()<<endl;
			string errorMessage = "execute "+selectSQL+" failed";
			throw QueryCmptException(errorMessage);
		}
	}

	Cells=new vector<Cell>[splitNumber];

	cout<<"INFO: resume thread"<<endl;
	for ( i = 0; i < QuerythreadNum; ++i )//唤醒其他P个子线程
	        ResumeThread(thread_set[i]); 
		
	SuspendThread(GetCurrentThread());   //主线程挂起，等待其他线程结束。

	CellSet ToXMLAResult(parsedMdx);

	getMdxMsrAggType();

	cout<<"INFO: 开始合并查询结果 "<<endl;
	mergeFun();

	ToXMLAResult.Cells=Cells[0];
	
	return ToXMLAResult;
}

void MTCCQuery::getMdxMsrAggType()
{
	msrsLineCount = 1;
	vector< QueryMember* > temp;
	vector< vector<QueryTuple*> > axes = parsedMdx->getAxes();
	int slicerTuplesNum = (parsedMdx->getSlicer()).size();
	//加入切片轴
	if (slicerTuplesNum != 0)
	{
		axes.push_back(parsedMdx->getSlicer());
	}
	
	map<string,string> metaMsrAggType = getMetaMsrAggType();
	
	string tMember;
	string tmptMember;
	bool hasCount;
	for ( int i = 0; i < axes.size(); ++i )
	{
		hasCount = false;
		for ( int ii = 0; ii < axes[i].size(); ++ii )
		{
			temp = axes[i][ii]->getMembers();		
			for ( int iii = 0; iii < temp.size(); ++iii )
			{
				tMember = temp[iii]->getDimensionName()+"."+temp[iii]->getHierarchyName();

				if (tMember.compare( "Measures.Measures" ) == 0)
				{
					mdxMsrAggType.push_back(metaMsrAggType[temp[iii]->getVal()]);
					if ( !hasCount )
					{
						for ( int iiii = i - 1; iiii >= 0; iiii--)
						{
							msrsLineCount *= axes[iiii].size();
						}
						hasCount = true;
					}
				}
			}
			temp.clear();
		}
	}
}	

map<string,string> MTCCQuery::getMetaMsrAggType()
{	
	map<string,string> msrToAggType;

	string schemaName = parsedMdx->getSchemaName();
	string cubeName = parsedMdx->getCubeName();
	
	XSchema* schema = XSchemas::instance().getSchema( schemaName );
	XCube* cube = schema->getCube(cubeName);
	
	vector<Measure*>& measures = cube->getMeasures();
	for ( int i = 0; i < measures.size(); ++i )
	{
		msrToAggType.insert(pair<string,string>(measures[i]->getName(),measures[i]->getAggregator()));
	}

	return msrToAggType;
}


void MTCCQuery::mergeFun()
{
	int i;
	vector<Cell>::iterator lb;
	int size = Cells[0].size();
	vector<double> *values = new vector<double>[size];
	
	for ( i = 0; i < splitNumber; ++i )
	{
		int k = 0;

		for ( lb = Cells[i].begin(); lb < Cells[i].end(); lb++ )
		{
			if ( !(lb->isNull) )
				values[k].push_back(lb->value);
			
			++k;
		}	
	}

	i = 0;
	for ( lb = Cells[0].begin(); lb < Cells[0].end(); lb++ )
	{
		int index = ((i % (msrsLineCount * mdxMsrAggType.size()))/msrsLineCount)%(mdxMsrAggType.size());
		if ( mdxMsrAggType[i%mdxMsrAggType.size()] == "sum" )
			lb->value = aggSum(values[i]);
		else if ( mdxMsrAggType[i%mdxMsrAggType.size()] == "count" )
			lb->value = aggCount(values[i]);
		else if ( mdxMsrAggType[i%mdxMsrAggType.size()] == "max" )
			lb->value = aggMax(values[i]);
		else if ( mdxMsrAggType[i%mdxMsrAggType.size()] == "min" )
			lb->value = aggMin(values[i]);
		else 
			lb->value = aggSum(values[i]);

		++i;
	}	 
}

double MTCCQuery::aggCount( vector<double>& values )
{
	double count = 0;
	for ( int i = 0; i < values.size(); ++i )
	{
		count += values[i];
	}
	return count;
} 

double MTCCQuery::aggMax( vector<double>& values )
{
	double max = values[0];
	for ( int i = 0; i < values.size(); ++i )
	{
		max = max > values[i] ? max : values[i];
	}
	return max;
}

double MTCCQuery::aggMin( vector<double>& values )
{
	double min = values[0];
	for ( int i = 0; i < values.size(); ++i )
	{
		min = min < values[i] ? min : values[i];
	}
	return min;
}

double MTCCQuery::aggSum( vector<double>& values )
{
	double sum = 0;
	for ( int i = 0; i < values.size(); ++i )
	{
		sum += values[i];
	}
	return sum;
}

};