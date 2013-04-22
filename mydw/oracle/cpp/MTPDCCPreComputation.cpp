#include "./PreComputation/MTPDCCPreComputation.h"

namespace PreCmpt{

extern EXECUTESTATE PreErrorNo;

MTPDCCPreComputation::MTPDCCPreComputation( XCube *cube, ALGTYPE algType_t )
{
	cout<<"INFO: class MTPDCCPreComputation--Constructor"<<endl;
	DWConfiguration &dwConfig = DWConfiguration::instance();
	dwConfig.addConfig("System","../../DWServer/conf/system-config.xml");
	DWConfig *config = NULL;	
	if ( !(config = dwConfig.getConfig("System")) )
	{
		PreErrorNo = SYSTEM_OPEN_FAILED;
		string errorMessage = "open system-config.xml failed";
		throw PreCmptException(errorMessage);
	}

	string CPUNumStr = "";
	if ( (CPUNumStr = config->getValue("ConfigurationSettings.PreCmptThreadNum")) == "" )
	{
		PreErrorNo = SYSTEM_GET_FAILED;
		string errorMessage = "get ConfigurationSettings.PreCmptThreadNum value failed";
		throw PreCmptException(errorMessage);
	}
	CPU_NUM = atoi( CPUNumStr.c_str() );
	
	string BufferSizeStr = "";
	if ( (BufferSizeStr = config->getValue("ConfigurationSettings.BlocktupleSize")) == "" )
	{
		PreErrorNo = SYSTEM_GET_FAILED;
		string errorMessage = "get ConfigurationSettings.BlocktupleSize value failed";
		throw PreCmptException(errorMessage);
	}
	BUFFERSIZE = atoi( BufferSizeStr.c_str() );

	algType = algType_t;

	int i;
	cb=cube;
	InitializeCriticalSection(&(gs.cs));
	for(i=0;i<threadNum;i++)
		thread_set[i]=NULL;
	thread_id=0;
	host_thread=GetCurrentThread();
	if ( CPU_NUM == 1 )
	{
		gs.level=0;
		gs.flag=1;
		gs.finished_threads=0;
	}
	else
	{
		pc_state.level=0;
		pc_state.flag=1;
		pc_state.finished=0;
		gs.finished_threads=0;
		for ( i = 0; i < readdataNum; ++i ) 
		{
			pc_state.queue[i]=0;
			pc_state.molapcompute[i]=NULL;
		}
		producer=1;
		consumer=0;
	}
	
}

MTPDCCPreComputation::~MTPDCCPreComputation(){
	DeleteCriticalSection(&(gs.cs));

}

void MTPDCCPreComputation::lock(){
	EnterCriticalSection(&(gs.cs));
	
}

void MTPDCCPreComputation::unlock(){
	LeaveCriticalSection(&(gs.cs));
}

void MTPDCCPreComputation::singleCPU_preComputation()
{
	cout<<"INFO: class MTPDCCPreComputation--singleCPU_preComputation"<<endl;
	int i;
    unsigned thread_id;
    cout<<"singleCpu work"<<endl;
	InitializeCriticalSection(&(gs.cs));
	for ( i = 0; i < threadNum; ++i )
	{
		DuplicateHandle(GetCurrentProcess(),
			GetCurrentThread(),
			GetCurrentProcess(),
			&(host_thread),
			0,
			FALSE,
			DUPLICATE_SAME_ACCESS);
		
		thread_set[i]=(HANDLE) _beginthreadex(NULL,
			0,
			MTPDCCPreComputation::singleCPU_ChildThread,
			this,
			0,
			&(thread_id));
	} 
		
	    Sleep(20);
	    for(i=0;i<threadNum;i++)
	        ResumeThread(thread_set[i]); 
		SuspendThread(GetCurrentThread());
		Sleep(100);
		
}


void MTPDCCPreComputation::MultiCPU_preComputation()
{
	cout<<"INFO: MTPDCCPreComputation--MultiCPU_preComputation"<<endl;

	int i;
    unsigned thread_id;
	cout<<"INFO: MultiCPU work"<<endl;
    InitializeCriticalSection(&(gs.cs));
	DuplicateHandle(GetCurrentProcess(),
			GetCurrentThread(),
			GetCurrentProcess(),
			&(host_thread),
			0,
			FALSE,
			DUPLICATE_SAME_ACCESS);
	for ( i = 0; i < threadNum; ++i )
	{
		thread_set[i]=(HANDLE) _beginthreadex(NULL,
			0,
			MTPDCCPreComputation::MultiCPU_DFS_ChildThread,
			this,
			0,
			&(thread_id));
	} 

	readthread_set=(HANDLE) _beginthreadex(NULL,
		0,
		MTPDCCPreComputation::MultiCPU_ReadData_ChildThread,
		this,
		0,
		&(thread_id));

		
	Sleep(20);
	ResumeThread(readthread_set);
	Sleep(1000);
	for ( i = 0; i < readdataNum; ++i )
		ResumeThread(thread_set[i]);		
	SuspendThread(GetCurrentThread());
	Sleep(100);
}

unsigned __stdcall MTPDCCPreComputation::singleCPU_ChildThread(void* param){
	
	MTPDCCPreComputation *pto=(MTPDCCPreComputation*) param;
	return pto->singleCPU_DFS();

}

unsigned __stdcall MTPDCCPreComputation::MultiCPU_DFS_ChildThread(void* param){
	
	MTPDCCPreComputation *pto=(MTPDCCPreComputation*) param;
	return pto->MultiCPU_DFS();
}

unsigned __stdcall MTPDCCPreComputation::MultiCPU_ReadData_ChildThread(void* param){
	
	MTPDCCPreComputation *pto=(MTPDCCPreComputation*) param;
	return pto->MultiCPU_ReadData();
	
}


DWORD MTPDCCPreComputation::singleCPU_DFS(){

	HANDLE my_thread=GetCurrentThread();
	SuspendThread(my_thread);
	int my_level;
	int beginTuple;
	int endTuple;
	
	while(gs.flag)
	{
		lock();
		if(gs.flag==0){
			unlock();
			break;
		}
		
		MolapPreComputationBase* preCmpt;
		switch( algType )
		{
			case MOLAP:
			{
				preCmpt = new MolapCCPreComputation(cb);
				break;
			}
			case ROLAP:
			{
				preCmpt = new RolapCCPreComputation(cb); 
				break;
			}
			default: break;
		}
		
		my_level=gs.level;
		cout<<"INFO: level= "<<my_level<<endl;
		gs.level++;
		beginTuple=my_level*BUFFERSIZE;
		endTuple=beginTuple+BUFFERSIZE-1;
		cout<<"INFO: loadData..."<<beginTuple<<"->"<<endTuple<<endl;
		preCmpt->loadNextData(beginTuple,endTuple,itos(my_level));
		cout<<"INFO: end loadData!"<<endl;
		if (preCmpt->getTuplesNum()<BUFFERSIZE)
		{
			gs.flag=0;
		}
		unlock();
		cout<<"INFO: tupleNum:"<<preCmpt->getTuplesNum()<<endl;
		if ( preCmpt->getTuplesNum() == 0 )
		{
			delete preCmpt;
			break;
		}

		cout<<"INFO: start precompute..."<<endl;
		preCmpt->excutePreCompute();
		cout<<"INFO: end precompute"<<endl;
		delete preCmpt;
	
	}
	lock();
	gs.finished_threads++;
	unlock();
	if (gs.finished_threads==threadNum)
	{
		ResumeThread(host_thread);
	}
	
	Sleep(100);
            
	
	return 0;
}

DWORD MTPDCCPreComputation::MultiCPU_ReadData(){
	
	HANDLE my_thread=GetCurrentThread();
	SuspendThread(my_thread);
	int beginTuple;
	int endTuple;
	int my_level;

	MolapPreComputationBase *preCmpt;
	int queue;
	int state;
	
	while(1){
		lock();
		preCmpt = check_state(&state,producer,&queue);
		unlock();
		if (state==1) {
			my_level = pc_state.level;
			cout<<"INFO: level= "<<my_level<<endl;
			lock();
			pc_state.level++;
			unlock();
			beginTuple=my_level*BUFFERSIZE;
		    endTuple=beginTuple+BUFFERSIZE-1;
			cout<<"INFO: start loading ..."<<" "<<beginTuple<<"->"<<endTuple<<endl;
			preCmpt->loadNextData(beginTuple,endTuple,itos(my_level));
			cout<<"INFO: end loading!"<<endl;
			lock();
			pc_state.queue[queue]=1;
			unlock();
		    if (preCmpt->getTuplesNum()<BUFFERSIZE)
			{
				lock();
				for (int i=0;i<readdataNum;i++) {
					if(pc_state.queue[i]==1)
						pc_state.finished++;
				}
				pc_state.flag=0;
				unlock();
			    break;
			}
		}
		else{
			cout<<"INFO: read thread suspend"<<endl;
			SuspendThread(my_thread);
		}
	
	}
	Sleep(100);
	return 0;
}

DWORD MTPDCCPreComputation::MultiCPU_DFS(){

	HANDLE my_thread=GetCurrentThread();
	SuspendThread(my_thread);
	MolapPreComputationBase *preCmpt;
	int queue;
	int state;
	while(pc_state.flag||pc_state.finished)
	{
		lock();
		preCmpt=check_state(&state,consumer,&queue);
		unlock();
		if (state==1) {
			if(pc_state.flag==0)
				pc_state.finished--;
			preCmpt->excutePreCompute();
			delete preCmpt;
		}
	
	}
	
	lock();
	gs.finished_threads++;
	unlock();
	if (gs.finished_threads==threadNum)
	{
		ResumeThread(host_thread);
	}
	
	Sleep(100);
            
	
	return 0;
}


MolapPreComputationBase* MTPDCCPreComputation::check_state(int *state,int producer_consumer,int *queue){
	
	int i;
	if(producer_consumer==1){
		for (i=0;i<readdataNum;i++) {
			if(pc_state.queue[i]==0){

				MolapPreComputationBase *preCmpt;
				if ( algType == MOLAP )
				{
					preCmpt = new MolapCCPreComputation(cb);
				}
				else
					preCmpt = new RolapCCPreComputation(cb);

				pc_state.molapcompute[i]=preCmpt;
				*state=1;
				*queue=i;
				return preCmpt;
				
			}
		}
		*state=0;
		return NULL;
		
	}
	else{
		for (i=0;i<readdataNum;i++) {
			if (pc_state.queue[i]==1) {
				*state=1;
				pc_state.queue[i]=0;
				return pc_state.molapcompute[i];
			}
			else if(i==3)
				ResumeThread(readthread_set);
		}
		*state=0;
		return NULL;
	}
}


void MTPDCCPreComputation::excutePreCompute()
{
	if(CPU_NUM==1)
		singleCPU_preComputation();
	else
		MultiCPU_preComputation();
	
	outputPartitionInfo();
	
}

void MTPDCCPreComputation::outputPartitionInfo()
{
	int size=pc_state.level-1;
	if ( algType == MOLAP )
	{		
		DWConfiguration &dwConfig = DWConfiguration::instance();
		dwConfig.addConfig("System","../../DWServer/conf/system-config.xml");
		DWConfig *config = NULL;	
		if ( !(config = dwConfig.getConfig("System")) )
		{
			PreErrorNo = SYSTEM_OPEN_FAILED;
			string errorMessage = "open system-config.xml failed";
			throw PreCmptException(errorMessage);
		}
		
		string cubeDir = "";
		if ( (cubeDir = config->getValue("ConfigurationSettings.DataDir")) == "" )
		{
			PreErrorNo = SYSTEM_GET_FAILED;
			string errorMessage = "get ConfigurationSettings.DataDir value failed";
			throw PreCmptException(errorMessage);
		}

		string schemaName = cb->getSchema()->getName();
		string cubeName = cb->getName();
		cubeDir += "/"+schemaName+"_"+cubeName;
		cubeDir += "/ucellsinfo.txt";
		FILE *out = fopen( cubeDir.c_str(),"w" );
		fwrite(&size,sizeof(int),1,out);
		fclose(out);
	}
	else
	{
		XSchema* schema = cb->getSchema();
		string schemaName = schema->getName();
		string cubeName = cb->getName();
		DataSource* datasource=schema->getDataSource();
		string URL = datasource->getURL();
		string username = datasource->getUserName();
		string password = datasource->getPassWord();
		XODBCDatabase OutXDB;
		try
		{
			OutXDB.Open(URL,username,password,XODBCDatabase::openCanUpdate);
			
			string tableName = "agg_ucellsinfo";
			string createSql = "create table \"SYSTEM\".\""+tableName+"\" ( ucellInfo int );";  //by hch
			//string createSql = "create table "+tableName+"( ucellInfo int );";
			OutXDB.ExecuteSQL(createSql);
			
			string insertSql = "insert into \"SYSTEM\".\""+tableName+"\" values("+itos(size)+");";    //by hch
			//string insertSql = "insert into "+tableName+"("+itos(size)+");";
			OutXDB.ExecuteSQL(insertSql);

			OutXDB.Close();
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
}

};

