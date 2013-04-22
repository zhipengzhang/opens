#include "./PreComputation/MolapFCPreComputation.h"

namespace PreCmpt{

extern EXECUTESTATE PreErrorNo;

MolapFullPreComputation::MolapFullPreComputation(XCube *cube)
:MolapPreComputationBase(cube)
{
	cout<<"INFO: class MolapFullPreComputation--Constructor"<<endl;

	dimDataDouble[0] = NULL;
	dimDataDouble[1] = NULL;
	msrDataDouble[0] = NULL;
	msrDataDouble[1] = NULL;

	dflag = 0;
	msrValues = NULL;
	uclsNum = 0;
	aggsNumPerLayer = NULL;
	fps = NULL;

	DWConfiguration &dwConfig = DWConfiguration::instance();
	dwConfig.addConfig("System","../../DWServer/conf/system-config.xml");
	DWConfig *config = NULL;	
	if ( !(config = DWConfiguration::instance().getConfig("System")) )
	{
		PreErrorNo = SYSTEM_OPEN_FAILED;
		string errorMessage = "open system-config.xml failed";
		throw PreCmptException(errorMessage);
	}
	
	outDir = "";
	if ( (outDir = config->getValue("ConfigurationSettings.DataDir")) == "" )
	{
		PreErrorNo = SYSTEM_GET_FAILED;
		string errorMessage = "get ConfigurationSettings.DataDir value failed";
		throw PreCmptException(errorMessage);
	}
	
	outDir += "/" + schemaName + "_" + cubeName;
}

MolapFullPreComputation::~MolapFullPreComputation()
{
	cout<<"INFO: class MolapFullPreComputation--Destructor"<<endl;

	delete[] dimDataDouble[1];
	delete[] msrDataDouble[1];
	delete[] msrValues;
	delete[] aggsNumPerLayer;

	if (fps)
	{
		for ( int i = 0; i < 2*(dimsNum+1); ++i )
		{
			fclose(fps[i]);
		}
		delete[] fps;
	}
}


void MolapFullPreComputation::loadData()
{
	cout<<"INFO: class MolapFullPreComputation--loadData"<<endl;

	MolapPreComputationBase::loadData();
	
	aggWriter = new AggFileWriter(outDir,dimsNum,msrsNum);

	//output map data
	for ( int i = 0; i < dimsNum; ++i )
	{
		aggWriter->insertMapData( mapData[i], i );
	}

	//output hdr data
	aggWriter->insertHdrData(hdrData);            

	delete[] mapData;
}

void MolapFullPreComputation::loadNextData( int start, int end, string partitionNum )
{
	cout<<"INFO: class MolapFullPreComputation--loadNextData"<<endl;

	MolapPreComputationBase::loadNextData(start,end,partitionNum);

	aggWriter = new AggFileWriter(outDir,dimsNum,msrsNum,partitionNum);

	//output map data
	for ( int i = 0; i < dimsNum; ++i )
	{
		aggWriter->insertMapData( mapData[i], i );
	}

	//output hdr data
	aggWriter->insertHdrData(hdrData); 

	delete[] mapData;
}

void MolapFullPreComputation::preComputation()
{
	cout<<"INFO: class MolapFullPreComputation--preComputation"<<endl;

	int i = 0;

	//open aggregate files
	fps = new FILE* [2*(dimsNum + 1)];
	for ( i = 0; i < dimsNum+1; ++i )
	{
		string aggDimDataFileName = outDir + "/aggDimData" + itos(i) + ".dat";
		if( !(fps[i] = fopen(aggDimDataFileName.c_str(), "wb")) )
		{
			PreErrorNo = FILE_OPER_FAILED;
			string errorMessage = "open "+aggDimDataFileName+" failed";
			throw PreCmptException(errorMessage);
		}

	}

	for ( ; i < 2*(dimsNum +1); ++i )
	{
		string aggMsrDataFileName = outDir + "/aggMsrData" + itos(i-dimsNum-1) + ".dat";
		if( !(fps[i] = fopen(aggMsrDataFileName.c_str(),"wb")) )
		{
			PreErrorNo = FILE_OPER_FAILED;
			string errorMessage = "open "+aggMsrDataFileName+" failed";
			throw PreCmptException(errorMessage);
		}
	}

	aggsNumPerLayer = new int[dimsNum + 1];
	for ( i = 0; i < dimsNum+1; ++i )
	{
		aggsNumPerLayer[i] = 0;
	}

	dimDataDouble[0] = MolapPreComputationBase::dimData;
	dimDataDouble[1] = new int* [tuplesNum];
	msrDataDouble[0] = MolapPreComputationBase::msrData;
	msrDataDouble[1] = new double* [tuplesNum];

	msrValues = new double[msrsNum];
	int *cl = new int[dimsNum];
	for( i = 0; i < dimsNum; ++i )
	{
		cl[i] = ALL;
	}

	DFS(cl, 0, tuplesNum, 0);

	string filename = outDir + "/aggsNumPerLayer.dat";
	FILE* fsNumPerLayer = NULL;
	if ( !(fsNumPerLayer = fopen( filename.c_str(), "w" )) )
	{
		PreErrorNo = FILE_OPER_FAILED;
		string errorMessage = "open "+filename+" failed";
		throw PreCmptException(errorMessage);
	}

	if( fwrite(aggsNumPerLayer, sizeof(int)*(dimsNum+1), 1, fsNumPerLayer) != 1 )
	{
		PreErrorNo = FILE_OPER_FAILED;
		string errorMessage = "write aggsNumPerLayer error";
		throw PreCmptException(errorMessage);
	}

	fclose(fsNumPerLayer);
	
	delete[] cl;
}

inline int MolapFullPreComputation::findCard(int bPos, int ePos, int d)
{
	int max = 0;
	for ( int i = bPos; i < ePos; ++i )
	{
		max = dimDataDouble[dflag][i][d] > max ? dimDataDouble[dflag][i][d] : max;
	}
	return (max + 1);
}

void MolapFullPreComputation::Partition(int bPos, int ePos, int d, int card, int *freq)
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
		freq[ dimDataDouble[dflag][i][d] ] ++;

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

//添加一个bufSize字段，当uclCount达到bufSize，输出到数据库，并将uclCount清0 
void MolapFullPreComputation::DFS( int cl[], int bPos, int ePos, int d )
{
	int i = 0;
	int j = 0;
	int k = 0;

	for ( i = 0; i < dimsNum; ++i )
	{
		if ( cl[i] != ALL )
		{
			++k;
		}
	}

	for ( i = 0; i < msrsNum; ++i )
	{
		msrValues[i] = (this->*aggFunLib[aggFunOrder[i]])(msrDataDouble[dflag], bPos, ePos, i);
	}

	outputTodimDataFile(k, cl);
	outputTomsrDataFile(k, msrValues);

	++aggsNumPerLayer[k];        //第k层输出的上界集数＋1

	++uclsNum;

	int* tmpucl = new int[dimsNum];
	for ( i = 0; i < dimsNum; ++i )
	{
		tmpucl[i] = cl[i];
	}
	for ( i = d; i < dimsNum; ++i )
	{
		if ( cl[i] == ALL )
		{
			int card = findCard(bPos, ePos, i);
			//Does it need to judge the card?
			int* freq = new int[card];
			Partition(bPos, ePos, i, card, freq);

			int tmpdflag  = dflag; 
			for ( j = 0; j < card - 1; ++j )
			{
				if ( freq[j + 1] > freq[j] )
				{
					cl[i] = dimDataDouble[dflag][ freq[j] ][i];
					DFS(cl, freq[j], freq[j + 1], i);	
				}
				dflag = tmpdflag;
			}
			delete[] freq;
		}
		for ( j =0; j < dimsNum; ++j )
		{
			cl[j] = tmpucl[j];
		}
	}
	delete []tmpucl;
}


inline int MolapFullPreComputation::outputTodimDataFile(int layer, int outputDimData[])
{
	assert( layer>=0 );
	assert( dimsNum > 0);

	if ( fwrite(outputDimData, sizeof(int)*dimsNum, 1, fps[layer]) != 1)
	{
		PreErrorNo = FILE_OPER_FAILED;
		string errorMessage = "write dim data error";
		throw PreCmptException(errorMessage);
	}

	return 0;
}

inline int MolapFullPreComputation::outputTomsrDataFile(int layer, double outputMsrData[])
{
	assert( layer>=0 );

	if ( msrsNum > 0 )
	{
		if ( fwrite(outputMsrData,sizeof(double)*msrsNum,1,fps[dimsNum+1+layer]) != 1)
		{	
			PreErrorNo = FILE_OPER_FAILED;
			string errorMessage = "write msr data error";
			throw PreCmptException(errorMessage);
		}
	}

	return 0;
}

int MolapFullPreComputation::getAggsNum()
{
	return uclsNum;
}

void MolapFullPreComputation::excutePreCompute()
{	
	cout<<"INFO: class MolapFullPreComputation--excutePreCompute"<<endl;
	if ( tuplesNum == 0 )
	{
		loadData();
	}	

	preComputation();

	cout<< "INFO: the amount of cls is :" << getAggsNum() << endl;
}

};