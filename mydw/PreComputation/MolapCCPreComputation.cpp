#include "./PreComputation/MolapCCPreComputation.h"

namespace PreCmpt{

extern EXECUTESTATE PreErrorNo;

MolapCCPreComputation::MolapCCPreComputation(XCube* cube)
:MolapPreComputationBase(cube)
{
	cout<<"INFO: class MolapCCPreComputation--Constructor"<<endl;

	//initial variable
	dimDataDouble[0] = NULL;
	dimDataDouble[1] = NULL;
	msrDataDouble[0] = NULL;
	msrDataDouble[1] = NULL;

	dflag = 0;
	msrValues = NULL;
	uclsNum = 0;
	aggsNumPerLayer = NULL;
	fps = NULL;
	tmpData = NULL;

	DWConfiguration &dwConfig = DWConfiguration::instance();
	dwConfig.addConfig("System","../../DWServer/conf/system-config.xml");
	DWConfig *config = NULL;	
	if ( !(config = dwConfig.getConfig("System")) )
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

MolapCCPreComputation::~MolapCCPreComputation()
{
	cout<<"INFO: class MolapCCPreCompuation--Destructor"<<endl;

	if ( dimDataDouble[1] )
	{
		delete[] dimDataDouble[1];
	}
	if ( msrDataDouble[1] )
	{
		delete[] msrDataDouble[1];
	}
	if ( msrValues )
	{
		delete[] msrValues;
	}
	if ( aggsNumPerLayer )
	{
		delete[] aggsNumPerLayer;
	}

	int i = 0;
	if ( fps )
	{
		for ( i = 0; i < dimsNum+1; ++i )
		{
			fclose(fps[i]);
		}
		delete[] fps;
	}

	if ( tmpData )
	{
		for ( i = 0; i < dimsNum; ++i )
		{
			if ( tmpData[i] )
				delete[] tmpData[i];
		}	
		delete[] tmpData;
	}
}

void MolapCCPreComputation::loadData()
{
	cout<<"INFO: class MolapCCPreComputation--loadData"<<endl;

	MolapPreComputationBase::loadData();
	
	aggWriter = new AggFileWriter(outDir,dimsNum,msrsNum);

	//输出映射文件
	for ( int i = 0; i < dimsNum; ++i )
	{
		aggWriter->insertMapData( mapData[i], i );
	}

	aggWriter->insertHdrData(hdrData);            //输出头文件

	delete[] mapData;	
}

void MolapCCPreComputation::loadNextData( int start, int end, string partitionNum )
{
	cout<<"INFO: class MolapCCPreComputation--loadNextData"<<endl;

	MolapPreComputationBase::loadNextData(start,end,partitionNum);
	
	cout<<"tuplesNum:"<<tuplesNum<<endl;
	if ( this->getTuplesNum()!= 0 )
	{
		aggWriter = new AggFileWriter(outDir,dimsNum,msrsNum,partitionNum);
		
		outDir += string("/")+partitionNum;
		//输出映射文件
		for ( int i = 0; i < dimsNum; ++i )
		{
			aggWriter->insertMapData( mapData[i], i );
		}

		aggWriter->insertHdrData(hdrData);            //输出头文件
	}	
	delete[] mapData;
}

void MolapCCPreComputation::preComputation()
{
	cout<<"INFO: class MolapCCPreComputation--preComputation"<<endl;

	int i = 0;
	int j = 0;
	
	fps = new FILE*[dimsNum+1];

	for ( i = 0; i < dimsNum+1; ++i )
	{
		string aggMsrDataFileName = outDir + "/aggMsrData" + itos(i) + ".dat";
		if( !(fps[i] = fopen(aggMsrDataFileName.c_str(),"wb")) )
		{
			PreErrorNo = FILE_OPER_FAILED;
			string errorMessage = "open "+aggMsrDataFileName+" failed";
			throw PreCmptException(errorMessage);
		}
	}

	tmpData = new vector<long>* [dimsNum+1];
	for ( i = 0; i < dimsNum+1; ++i )
	{
		tmpData[i] = new vector<long>[dimsNum];
	}

	aggsNumPerLayer = new int [dimsNum+1];
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
	for ( i = 0; i < dimsNum; ++i )
	{
		cl[i] = ALL;
	}

	//QC algorithm
	DFS(cl, 0, tuplesNum, 0);

	string filename = outDir + "/aggsNumPerLayer.dat";
	FILE* fsNumPerLayer = NULL;
	if ( !(fsNumPerLayer = fopen( filename.c_str(), "wb" )) )
	{
		PreErrorNo = FILE_OPER_FAILED;
		string errorMessage = "open "+filename+" failed";
		throw PreCmptException(errorMessage);
	}

	if ( fwrite(aggsNumPerLayer,sizeof(int)*(dimsNum+1),1,fsNumPerLayer) != 1 )
	{
		PreErrorNo = FILE_OPER_FAILED;
		string errorMessage = "write aggsNumPerLayer error";
		throw PreCmptException(errorMessage);
	}

	fclose(fsNumPerLayer);
	
	delete[] cl;
	
	buildCCInvertListsIndex();	
}


inline int MolapCCPreComputation::findCard(int bPos, int ePos, int d)
{
	int max = 0;
	for(int i = bPos; i < ePos; i ++)
	{
		max = dimDataDouble[dflag][i][d] > max ? dimDataDouble[dflag][i][d] : max;
	}
	return (max + 1);
}

void MolapCCPreComputation::Partition(int bPos, int ePos, int d, int card, int *freq)
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

void MolapCCPreComputation::DFS( const int const cl[], int bPos, int ePos, int d )
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
				k ++;
			}
		}
		else
		{
			k ++;
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
		msrValues[i] = ((this->*aggFunLib[aggFunOrder[i]]))(msrDataDouble[dflag], bPos, ePos, i);
	}
	
	outputTomsrDataFile(k, msrValues);
	for ( i = 0; i < dimsNum; ++i )
	{
		tmpData[k][i].push_back(ucl[i]);
	}

	++aggsNumPerLayer[k];            //第k层输出的上界集数＋1

	++uclsNum;

	int* tmpucl = new int[dimsNum];
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

inline int MolapCCPreComputation::outputTomsrDataFile(int layer, double outputMsrData[])
{
	if( msrsNum != 0 )
	{
		if( fwrite(outputMsrData,sizeof(double)*msrsNum,1,fps[layer]) != 1 )
		{
			PreErrorNo = FILE_OPER_FAILED;
			string errorMessage = "write aggregate msrData error";
			throw PreCmptException(errorMessage);
		}
	}
	return 0;
}

long MolapCCPreComputation::filesize(FILE *stream)
{
	long curpos;
	long length;   
	curpos = ftell(stream);   
	fseek(stream,0L,SEEK_END);   
	length = ftell(stream);   
	fseek(stream, curpos, SEEK_SET);  
	return length;  	
} 

vector<long> MolapCCPreComputation::changeStore(vector<long> num)
{
	const int tagNum = -1;
	int i = 0;
	int j = 0;
	int size = num.size();

	vector<long> numStore;
	int count = 0;

	if ( size > 1 )              
	{
		for ( i = 0, j = 1; j < size; ++i , ++j )
		{
			if ( num[j] == num[i]+1 )
			{	
				if ( count == 0 )
				{
					numStore.push_back(tagNum);
					numStore.push_back(num[i]);
					count ++;
				}
			}
			else
			{
				if ( count != 0 )
				{
					numStore.push_back(num[i]);
					count = 0;
				}
				else
					numStore.push_back(num[i]);
			}
		}
		//deal with the last one
		numStore.push_back(num[size - 1]);
	}
	else              //size==1
		numStore.push_back(num[0]);
	
	return numStore;
}

void MolapCCPreComputation::buildCCInvertListsIndex()
{
	cout<<"INFO: class MolapCCPreComputation--buildCCInvertListsIndex"<<endl;

	int i = 0;
	int j = 0;
	//realease the points
	if (fps)
	{
		for ( i = 0; i < dimsNum+1; ++i )
		{
			fclose(fps[i]);
		}
		delete[] fps;
		fps = NULL;
	}
	
	vector< vector<long> > vecDim;
	
	for ( j = 0; j < dimsNum; ++j )
	{		
		vector<long> tmpD;
		for ( i = 0; i < card[j]; ++i )
			vecDim.push_back(tmpD);

		long l = 0;
		long k = 0;

		long writePos = 0;
		for ( i = 0; i < dimsNum+1; ++i )
		{
			for ( k = 0; k < tmpData[i][j].size(); ++k )
			{
				if ( tmpData[i][j][k] != 0 )
					( vecDim[ ( (tmpData[i][j][k]) - 1) ] ).push_back(l+k);
			}
			l += tmpData[i][j].size();
		}

		string keyPos = outDir + "/keyPos" + itos(j) + ".dat"; 
		string key = outDir + "/key" + itos(j) + ".dat";
		FILE* keyFile = NULL;
		if ( !(keyFile = fopen(key.c_str(),"wb")) )
		{   
			PreErrorNo = FILE_OPER_FAILED;
			string errorMessage = "open "+key+" failed";
			throw PreCmptException(errorMessage);
		}   

		FILE* keyPosFile = NULL;
		if ( !(keyPosFile = fopen(keyPos.c_str(),"wb")) )
		{   
			PreErrorNo = FILE_OPER_FAILED;
			string errorMessage = "open "+keyPos+" failed";
			throw PreCmptException(errorMessage);
		}  

		vector<long> numChange;

		for ( int mm = 0; mm < vecDim.size() ; ++mm )
		{
			numChange = changeStore(vecDim[mm]);
			if ( fwrite(&(numChange[0]), (sizeof(long)) * (numChange.size()), 1, keyFile) != 1 )
			{
				PreErrorNo = FILE_OPER_FAILED;
				string errorMessage = "write aggregate data error";
				throw PreCmptException(errorMessage);
			}

			writePos = ftell(keyFile);

			if ( fwrite(&writePos, sizeof(long), 1, keyPosFile) != 1)
			{
				PreErrorNo = FILE_OPER_FAILED;
				string errorMessage = "write aggregate data error";
				throw PreCmptException(errorMessage);
			}
			numChange.clear();
		}
		vecDim.clear();
		tmpD.clear();
		fclose(keyFile);
		fclose(keyPosFile);
	}
}

int MolapCCPreComputation::getAggsNum()
{
	return uclsNum;
}

void MolapCCPreComputation::excutePreCompute()
{
	cout<<"INFO: class MolapCCPreComputation--excutePreCompute"<<endl;
	if ( tuplesNum == 0 )
	{
		loadData();
	}	

	preComputation();

	cout<< "INFO: the amount of cls is :" << getAggsNum() << endl;
}

}