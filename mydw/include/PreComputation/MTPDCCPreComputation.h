#ifndef _MTPDCCPreComputation_h_
#define _MTPDCCPreComputation_h_

#include "MolapPreComputationBase.h"
#include "MolapCCPreComputation.h"
#include "RolapCCPreComputation.h"
#include "PreCmptException.h"

#include "./dwconfig/DWConfig.h"
#include "./dwconfig/DWConfiguration.h"
#include "./dwconfig/DWElement.h"

#include <windows.h>
#include <process.h>
#include "FreqPool.h"

namespace PreCmpt{

typedef enum _ALGTYPE{ ROLAP, MOLAP }ALGTYPE;
	
const int threadNum = 2;  //线程数
	
const int readdataNum=4;

struct Critical_Section_PD{
	CRITICAL_SECTION cs;
	int level;
	bool flag;
	int finished_threads;
};


struct producer_consumer_state{
	int queue[readdataNum];
	int level;
	bool flag;
	int finished;
	MolapPreComputationBase *molapcompute[readdataNum];
};


class MTPDCCPreComputation {

public:
	explicit MTPDCCPreComputation(XCube *cube,ALGTYPE algType);
	virtual ~MTPDCCPreComputation();

	XCube *cb;
	
	int BUFFERSIZE;

	int CPU_NUM;


	void excutePreCompute();
	
protected:
	virtual DWORD MultiCPU_DFS();
	virtual DWORD MultiCPU_ReadData();
	virtual DWORD singleCPU_DFS();

private:
	unsigned thread_id;
	struct Critical_Section_PD gs;
    struct producer_consumer_state pc_state;
       
	HANDLE thread_set[threadNum];
	HANDLE readthread_set;
	HANDLE host_thread;
	int producer,consumer;

	ALGTYPE algType;                    ///<输出类型Rolap,Molap

	void lock();
	void unlock();
	static unsigned __stdcall MultiCPU_DFS_ChildThread(void* param);
	static unsigned __stdcall MultiCPU_ReadData_ChildThread(void* param);
	static unsigned __stdcall singleCPU_ChildThread(void* param);
	void MultiCPU_preComputation();
	void singleCPU_preComputation();
	MolapPreComputationBase *check_state(int *returnstate,int producer_consumer,int *queue);

	void outputPartitionInfo();
		
};

};

#endif