#include "./PreComputation/RolapCCPreComputation.h"

namespace PreCmpt{

extern EXECUTESTATE PreErrorNo;

RolapCCPreComputation::RolapCCPreComputation(XCube* cube)
:MolapPreComputationBase(cube)
{
	cout<<"INFO: class RolapCCPreComputation--Constructor"<<endl;

	dimDataDouble[0] = NULL;
	dimDataDouble[1] = NULL;
	msrDataDouble[0] = NULL;
	msrDataDouble[1] = NULL;

	dflag = 0;
	msrValues = NULL;
	uclsNum = 0;
	
	XSchema* schema = cube->getSchema();
	DataSource* datasource=schema->getDataSource();
	string URL = datasource->getURL();
	string username = datasource->getUserName();
	string password = datasource->getPassWord();
	try
	{
		outXDB.Open(URL,username,password,XODBCDatabase::openCanUpdate);
	}
	catch ( XODBCException* e)
	{
		XODBCError error;
		e->GetError(error);
		cout<<"Error: errorMessage--"<<error.GetErrorText()<<endl;
		cout<<"Error: errorID--"<<error.GetState()<<endl;
		PreErrorNo = CONN_DA_FAILED;
		string errorMessage = "connect to datasource "+URL+" with name:"+username
								+" password:"+password+" failed";
		throw PreCmptException(errorMessage);
	}
	
}

RolapCCPreComputation::~RolapCCPreComputation()
{
	cout<<"INFO: class RolapCCPreComputation--Destructor"<<endl;

	if ( dimDataDouble[1] )
	{
		delete[] dimDataDouble[1];
		dimDataDouble[1] = NULL;
	}
	if ( msrDataDouble[1] )
	{
		delete[] msrDataDouble[1];
		msrDataDouble[1] = NULL;
	}
	if ( msrValues )
	{
		delete[] msrValues;
		msrValues = NULL;
	}
}

void RolapCCPreComputation::loadData()
{
	cout<<"INFO: class RolapCCPreComputation--loadData"<<endl;
	MolapPreComputationBase::loadData();
	
	aggWriter = new AggDBWriter(&outXDB,dimsNum,msrsNum,schemaName,cubeName);

	//output map data
	for ( int i = 0; i < dimsNum; ++i )
	{
		aggWriter->insertMapData( mapData[i], i );
	}

	//output hdr data
	aggWriter->insertHdrData(hdrData);         

	delete[] mapData;	
}

void RolapCCPreComputation::loadNextData( int start, int end, string partitionNum )
{
	cout<<"INFO: class RolapCCPreComputation--loadNextData"<<endl;

	MolapPreComputationBase::loadNextData(start,end,partitionNum);

	cout<<"tuplesNum:"<<this->getTuplesNum()<<endl;
	if ( this->getTuplesNum() != 0 )
	{
		aggWriter = new AggDBWriter(&outXDB,dimsNum,msrsNum,schemaName,cubeName,partitionNum);

		//输出映射文件
		for ( int i = 0; i < dimsNum; ++i )
		{
			aggWriter->insertMapData( mapData[i], i );
		}

		aggWriter->insertHdrData(hdrData);            //输出头文件
	}	
	
	delete[] mapData;
}

void RolapCCPreComputation::preComputation()
{
	int i = 0;

	for ( i = 0; i < dimsNum + 1; ++i )
	{
		aggsNumPerLayer.push_back(0);
	}

	dimDataDouble[0] = MolapPreComputationBase::dimData;
	dimDataDouble[1] = new int* [tuplesNum];
	msrDataDouble[0] = MolapPreComputationBase::msrData;
	msrDataDouble[1] = new double* [tuplesNum];

	msrValues = new double[msrsNum];
	int *cl = new int[dimsNum];

	for ( i = 0; i < dimsNum; ++i )
	{
		cl[i] = ALL;
	}

	//QC algorithm
	DFS ( cl, 0, tuplesNum, 0 );

	//output aggNumPerLayer
	aggWriter->insertNumPerLayer(aggsNumPerLayer);

	delete[] cl;
}

inline int RolapCCPreComputation::findCard(int bPos, int ePos, int d)
{
	int max = 0;
	for ( int i = bPos; i < ePos; ++i )
	{
		max = dimDataDouble[dflag][i][d] > max ? dimDataDouble[dflag][i][d] : max;
	}
	return (max + 1);
}

void RolapCCPreComputation::Partition(int bPos, int ePos, int d, int card, int *freq)
{
	int i;
	int *tmpFreq = new int[card];

	//initialize the frequency;
	for ( i = 0; i < card; ++i )
	{
		freq[i] = 0;
	}

	//calculate the frequency of input data element occurrence. 
	//Note: assuming the elements begin from 1, so freq[0] should be 0.
	for ( i = bPos; i < ePos; ++i )
		++freq[ dimDataDouble[dflag][i][d] ];

	//calculate the begin of every element.
	freq[0] = bPos;
	for ( i = 1; i < card; ++i )
		freq[i] = freq[i] + freq[i - 1];

	//make a copy of freq
	for ( i = 0; i < card; ++i )
	{
		tmpFreq[i] = freq[i];
	}

	for ( i = bPos; i < ePos; ++i )
	{
		dimDataDouble[!dflag][ tmpFreq[ dimDataDouble[dflag][i][d] ] - 1 ] = dimDataDouble[dflag][i];
		msrDataDouble[!dflag][ tmpFreq[ dimDataDouble[dflag][i][d] ] - 1 ] = msrDataDouble[dflag][i];
		tmpFreq[ dimDataDouble[dflag][i][d] ] --;
	}

	dflag = !dflag;

	delete[] tmpFreq;   
}

void RolapCCPreComputation::DFS( const int const cl[], int bPos, int ePos, int d )
{
	int i = 0;
	int j = 0;
	int k = 0;

	int *ucl = new int[dimsNum];
	for ( i = 0; i < dimsNum; ++i )
	{
		ucl[i] = cl[i];
	}

	//计算上界集 ucl
	for ( i = 0; i < dimsNum; ++i )
	{
		if ( cl[i] == ALL )
		{
			int diff = 0;
			for ( j = bPos + 1; j < ePos; ++j )
			{
				diff = dimDataDouble[dflag][j][i] - dimDataDouble[dflag][bPos][i];
				if (diff)
				{
					break;
				}
			}
			if (!diff)
			{
				ucl[i] = dimDataDouble[dflag][bPos][i];
				++k;
			}
		}
		else
		{
			++k;
		}
	}	

	//prune the cells which have been examined.
	for ( j = 0; j < d; ++j )
	{
		if ( cl[j] == ALL && ucl[j] != ALL )
		{
			delete []ucl;
			return;
		}
	}

	for ( i = 0; i < msrsNum; ++i )
	{
		msrValues[i] = (this->*aggFunLib[aggFunOrder[i]])(msrDataDouble[dflag], bPos, ePos, i);
	}
	
	
	static_cast<AggDBWriter*>(aggWriter)->insertUclData( ucl, msrValues, k );

	++aggsNumPerLayer[k];        //第k层输出的上界集数＋1
	++uclsNum;

	int *tmpucl = new int[dimsNum];
	for ( i = 0; i < dimsNum; ++i )
	{
		tmpucl[i] = ucl[i]; 
	}
	for ( i = d; i < dimsNum; ++i )
	{
		if ( ucl[i] == ALL )
		{
			int card = findCard(bPos, ePos, i);
			//Does it need to judge the card?
			int *freq = new int[card];
			Partition(bPos, ePos, i, card, freq);

			int tmpdflag  = dflag; 
			for ( j = 0; j < card - 1; ++j )
			{
				if (freq[j + 1] > freq[j])
				{
					ucl[i] = dimDataDouble[dflag][ freq[j] ][i];
					DFS(ucl, freq[j], freq[j + 1], i);	
				}
				dflag = tmpdflag;
			}
			delete[] freq;
		}
		for ( j = 0; j < dimsNum; ++j )
		{
			ucl[j] = tmpucl[j];
		}

	}
	delete []tmpucl;
	delete []ucl;
}

int RolapCCPreComputation::getAggsNum()
{
	return uclsNum;
}

void RolapCCPreComputation::excutePreCompute()
{
	cout<<"INFO: class RolapCCPreComputation--excutePreCompute"<<endl;
	
	if ( tuplesNum == 0 )
	{
		loadData();
	}	

	preComputation();

	cout<< "INFO: the amount of cls is :" << getAggsNum() << endl;
}

};