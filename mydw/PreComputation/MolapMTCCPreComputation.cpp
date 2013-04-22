#include "./PreComputation/MolapMTCCPreComputation.h"

namespace PreCmpt{

extern EXECUTESTATE PreErrorNo;

MolapMTCCPreComputation::MolapMTCCPreComputation( XCube *cube )
:MolapPreComputationBase(cube)
{
	cout<<"INFO: class MolapMTCCPreComputation--Constructor"<<endl;

	int i;
	InitializeCriticalSection(&(gs.cs));
	thread_set=NULL;
	thread_id=0;
	host_thread=GetCurrentThread();
    Gfreq=NULL;
	tempflag=0;
	dimDataDouble[0] = NULL;
	dimDataDouble[1] = NULL;
	msrDataDouble[0] = NULL;
	msrDataDouble[1] = NULL;
    globe_id=0;
	for(i=0;i<P;i++){
	    dflag[i] = 0;
		uclsNum[i] = 0;
	}
	msrValues = NULL;
	
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

MolapMTCCPreComputation::~MolapMTCCPreComputation(){
	
	cout<<"INFO: class MolapMTCCPreComputation--Destructor"<<endl;

	DeleteCriticalSection(&(gs.cs));

	delete[] dimDataDouble[1];
	delete[] msrDataDouble[1];
	delete[] msrValues;
	delete[] aggsNumPerLayer;

	if(fps)
	{
		for(int i = 0; i < 2*(dimsNum + 1); i ++)
		{
			fclose(fps[i]);
		}
		delete[] fps;
	}
}

void MolapMTCCPreComputation::lock(){
	EnterCriticalSection(&(gs.cs));
}

void MolapMTCCPreComputation::unlock(){
	LeaveCriticalSection(&(gs.cs));
}

void MolapMTCCPreComputation::loadData()
{
	cout<<"INFO: class MolapMTCCPreComputation--loadData"<<endl;

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

void MolapMTCCPreComputation::loadNextData( int start, int end, string partitionNum )
{
	cout<<"INFO: class MolapMTCCPreComputation--loadNextData"<<endl;

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

void MolapMTCCPreComputation::preComputation()
{
	int i;
    for(i=0;i<P;i++){
        malloc_numbers[i]=0;
	    free_numbers[i]=0;
		uclsNum[i]=0;
	}

	//open aggregate files
	fps = new FILE* [2*(dimsNum+1)];
	for ( i = 0; i < dimsNum+1; ++i )
	{
		string aggDimDataFileName = outDir + "/aggDimData" + itos(i) + ".dat";
		fps[i] = NULL;
		if ( !(fps[i] == fopen(aggDimDataFileName.c_str(), "wb")) )
		{
			PreErrorNo = FILE_OPER_FAILED;
			string errorMessage = "open "+aggDimDataFileName+" failed";
			throw PreCmptException(errorMessage);
		}

	}

	for ( ; i < 2*(dimsNum+1); ++i )
	{
		string aggMsrDataFileName = outDir + "/aggMsrData" + itos(i-dimsNum-1) + ".dat";
		fps[i] = NULL;
		if ( !(fps[i] == fopen(aggMsrDataFileName.c_str(),"wb")) ) 
		{
			PreErrorNo = FILE_OPER_FAILED;
			string errorMessage = "open "+aggMsrDataFileName+" failed";
			throw PreCmptException(errorMessage);
		}
	}

	aggsNumPerLayer = new int [dimsNum + 1];
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
	cmd=new int[dimsNum];

	for ( i = 0; i < dimsNum; ++i )
	{
		cl[i] = ALL;
	    cmd[i]=ALL;
	}

	for(i=0;i<P;i++)
		dflag[i]=0;

	
	HANDLE thread_set[P];
	struct thread_para para[P];
	unsigned thread_id;
    
	
	InitializeCriticalSection(&(gs.cs));
	for(i=0;i<P;i++){
		DuplicateHandle(GetCurrentProcess(),
			GetCurrentThread(),
			GetCurrentProcess(),
			&(host_thread),
			0,
			FALSE,
			DUPLICATE_SAME_ACCESS);
		para[i].id=i;
	
		thread_set[i]=(HANDLE) _beginthreadex(NULL,
			0,
			MolapMTCCPreComputation::ChildThread,
			this,
			0,
			&(thread_id));
	} 

	SetThreadAffinityMask(thread_set[0],0x01);
	SetThreadAffinityMask(thread_set[1],0x02);
	
	for(dim_id=0;dim_id<dimsNum;dim_id++)
	{
		EnterCriticalSection(&(gs.cs));

	    gs.level=0;
	    gs.finished_threads=0;
		Gcard = findCard(0, tuplesNum, dim_id,0);
	
		Gfreq = new int[Gcard];
		
		if(Gfreq==NULL)
				cout<<"Gfreq 为空指针"<<endl;
		Partition(0, tuplesNum, dim_id, Gcard, Gfreq,0);

		for(i=0;i<P;i++)
			MiddleNum[i]=(i+1)*Gfreq[Gcard-1]/P;
		
		i=0;
		for(int k=0;k<P;k++)
		{
			for(;i<Gcard;i++)
			{
				if(MiddleNum[k]<Gfreq[i] || MiddleNum[k]==Gfreq[i])
				{	
					MiddlePos[k]=Gfreq[i];
				    MiddleCard[k]=i;
					break;
				}
			}
		}
		tempflag=!tempflag;
		for(i=0;i<P;i++)
		{
			dflag[i]=tempflag;
		    tempcheck[i]=0;
		}

		LeaveCriticalSection(&(gs.cs));
		
	    Sleep(20);
	    
	    for(i=0;i<P;i++)//唤醒其他P个子线程
	        ResumeThread(thread_set[i]); 
		
		SuspendThread(GetCurrentThread());   //主线程挂起，等待其他线程结束。
		Sleep(100);
	}

}

unsigned __stdcall MolapMTCCPreComputation::ChildThread(void* param){
	
	MolapMTCCPreComputation *pto=(MolapMTCCPreComputation*) param;
	return pto->Threadwork();

}

DWORD MolapMTCCPreComputation::Threadwork(){

	HANDLE my_thread=GetCurrentThread();
	SuspendThread(my_thread);//子线程挂起，等待主进程分配任务
	int my_id;
	lock();
	my_id=globe_id;
	globe_id++;
	unlock();
	while(dim_id<dimsNum)
	{
		int *ucl = Freq_pool[my_id].malloc_freq(dimsNum);
		malloc_numbers[my_id]++;
	    for ( int i = 0; i < dimsNum; i++ )
		{
    	    ucl[i] = cmd[i];
		}
		if(my_id==0)
            ReDFS(ucl, 0,MiddleCard[my_id]+1,dim_id,my_id);
		else 
			ReDFS(ucl, MiddleCard[my_id-1],MiddleCard[my_id]+1,dim_id,my_id);
		
		gs.finished_threads++; //最后一个结束的线程唤醒主线程
	    if(gs.finished_threads==P)
		{
		    int t;
			t=ResumeThread(host_thread);
		}

        Freq_pool[my_id].free_freq(ucl,dimsNum);
		free_numbers[my_id]++;
        SuspendThread(my_thread);//子线程挂起，等待主进程分配任务
		Sleep(100);
            
	}
	return 0;
}

void MolapMTCCPreComputation::ReDFS(const int const cl[], int bCard, int eCard, int d,int thread_id)
{	
	int i;
	int j;
    int *ucl = Freq_pool[thread_id].malloc_freq(dimsNum);
	malloc_numbers[thread_id]++;
	for ( i = 0; i < dimsNum; i++ )
	{
		ucl[i] = cl[i];
	}
	i=d;
//	cout<<"线程 "<<thread_id <<"所算的条数是 "<<Gfreq[eCard-1]-Gfreq[bCard]<<endl;
    int tmpdflag = dflag[thread_id];
		
	for(j = bCard; j < eCard- 1; j ++)
	{
		if(Gfreq[j + 1] > Gfreq[j])
		{
			
			ucl[i] =  dimDataDouble[dflag[thread_id]][ Gfreq[j] ][i] ;
					DFS(ucl, Gfreq[j], Gfreq[j + 1], i,thread_id);
            
	
				
		}
		dflag[thread_id] = tmpdflag;
	}
	Freq_pool[thread_id].free_freq(ucl,dimsNum);
	free_numbers[thread_id]++;
			
}

inline int MolapMTCCPreComputation::findCard( int bPos, int ePos, int d, int thread_id )
{
	int max = 0;
	for ( int i = bPos; i < ePos; i ++)
	{
		max = dimDataDouble[dflag[thread_id]][i][d] > max ? dimDataDouble[dflag[thread_id]][i][d] : max;
	}
	return (max + 1);
}

void MolapMTCCPreComputation::Partition(int bPos, int ePos, int d, int card, int *freq,int thread_id)
{
	int i;
	int *tmpFreq = Freq_pool[thread_id].malloc_freq(card);
	malloc_numbers[thread_id]++;
 
	//initialize the frequency;
	for(i = 0; i < card; i++)
	{
		freq[i] = 0;
	}

	//calculate the frequency of input data element occurrence. 
	//Note: assuming the elements begin from 1, so freq[0] should be 0.
	for(i = bPos; i < ePos; i++)
		freq[ dimDataDouble[dflag[thread_id]][i][d] ] ++;

	//calculate the begin of every element.
	freq[0] = bPos;
	for(i = 1; i < card; i++)
		freq[i] = freq[i] + freq[i - 1];

	//make a copy of freq
	for(i = 0; i < card; i++)
	{
		tmpFreq[i] = freq[i];
	}

	for(i = bPos; i < ePos; i++)
	{
		dimDataDouble[!dflag[thread_id]][ tmpFreq[ dimDataDouble[dflag[thread_id]][i][d] ] - 1 ] = dimDataDouble[dflag[thread_id]][i];
		msrDataDouble[!dflag[thread_id]][ tmpFreq[ dimDataDouble[dflag[thread_id]][i][d] ] - 1 ] = msrDataDouble[dflag[thread_id]][i];
		tmpFreq[ dimDataDouble[dflag[thread_id]][i][d] ] --;
	}

	int tempdflag=dflag[thread_id];
	
	dflag[thread_id] = !tempdflag;

	Freq_pool[thread_id].free_freq(tmpFreq,card);
	free_numbers[thread_id]++;

	   
}

void MolapMTCCPreComputation::DFS( const int const cl[], int bPos, int ePos, int d,int thread_id )
{
	int i = 0;
	int j = 0;
	int k = 0;
    
	int *ucl = Freq_pool[thread_id].malloc_freq(dimsNum);
	malloc_numbers[thread_id]++;
	for ( i = 0; i < dimsNum; i++ )
	{
		ucl[i] = cl[i];
	}


	//计算上界集 ucl
	for(i = 0; i < dimsNum; i ++)
	{
		if(cl[i] == ALL)
		{
			int diff = 0;
			for(j = bPos + 1; j < ePos; j++)
			{
				diff = dimDataDouble[dflag[thread_id]][j][i] - dimDataDouble[dflag[thread_id]][bPos][i];
				if(diff)
				{
					break;
				}
			}
			if(!diff)
			{
				ucl[i] = dimDataDouble[dflag[thread_id]][bPos][i];
				k ++;
			}
		}
		else
		{
			k ++;
		}
	}	

	//prune the cells which have been examined.
	for(j = 0; j < d; j ++)
	{
		if(cl[j] == ALL && ucl[j] != ALL)
		{
			delete []ucl;
			return;
		}
	}

	for(i = 0; i < msrsNum; i ++)
	{
		msrValues[i] = (this->*aggFunLib[aggFunOrder[i]])(msrDataDouble[dflag[thread_id]], bPos, ePos, i);

	}

	outputTodimDataFile(k, ucl);
	outputTomsrDataFile(k, msrValues);

	aggsNumPerLayer[k] ++;        //第k层输出的上界集数＋1

	uclsNum[thread_id] ++;
    int *tmpucl = Freq_pool[thread_id].malloc_freq(dimsNum);
	malloc_numbers[thread_id]++;
	
	for ( i = 0; i < dimsNum; i++ )
	{
		tmpucl[i] = ucl[i];
	}
	for(i = d; i < dimsNum; i++)
	{
		if(ucl[i] == ALL)
		{
			int card = findCard(bPos, ePos, i,thread_id);
			//Does it need to judge the card?
			int *freq = Freq_pool[thread_id].malloc_freq(card);
			malloc_numbers[thread_id]++;
			Partition(bPos, ePos, i, card, freq,thread_id);

			int tmpdflag  = dflag[thread_id]; 
			for(j = 0; j < card - 1; j ++)
			{
				if(freq[j + 1] > freq[j])
				{
					ucl[i] = dimDataDouble[dflag[thread_id]][ freq[j] ][i];
					DFS(ucl, freq[j], freq[j + 1], i,thread_id);	
				}
				dflag[thread_id] = tmpdflag;
			}
			Freq_pool[thread_id].free_freq(freq,card);
			free_numbers[thread_id]++;
		}
		for ( j =0; j < dimsNum; j++)
		{
			ucl[j] = tmpucl[j];
		}

	}
	Freq_pool[thread_id].free_freq(tmpucl,dimsNum);
	free_numbers[thread_id]++;
    Freq_pool[thread_id].free_freq(ucl,dimsNum);
	free_numbers[thread_id]++;
}

inline int MolapMTCCPreComputation::outputTodimDataFile(int layer, int outputDimData[])
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

inline int MolapMTCCPreComputation::outputTomsrDataFile(int layer, double outputMsrData[])
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

int MolapMTCCPreComputation::getAggsNum()
{
	int countNum=0;
	for ( int i = 0; i < P; i++ )
	{
		countNum=countNum+uclsNum[i];
	}
	return countNum;
}

void MolapMTCCPreComputation::excutePreCompute()
{
	cout<<"INFO: class MolapMTCCPreComputation--excutePreCompute"<<endl;
	if ( tuplesNum == 0 )
	{
		loadData();
	}	

	preComputation();

	cout<< "INFO: the amount of cls is :" << getAggsNum() << endl;
}

};