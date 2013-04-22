#ifndef _MolapMTCCPreComputation_H_
#define _MolapMTCCPreComputation_H_


#include <windows.h>
#include <process.h>
#include "MolapPreComputationBase.h"
#include "PreCmptException.h"
#include "FreqPool.h"
#include "common.h"

namespace PreCmpt{

const int P = 2;  //Ïß³ÌÊý

struct Critical_Section{
	CRITICAL_SECTION cs;
    int level;
	int finished_threads;
};

struct thread_para{
	HANDLE host_thread;
	int id;
};

class MolapMTCCPreComputation: public MolapPreComputationBase
{
 
   public:
	   explicit MolapMTCCPreComputation(XCube *cube/*,JobConf* conf*/);
	   virtual ~MolapMTCCPreComputation();
	   HANDLE thread_set;
	   HANDLE host_thread;
	   void Createthread();
	   void lock();
	   void unlock();
	   static unsigned __stdcall ChildThread(void* param);
	   virtual void excutePreCompute();
	   virtual void loadData();
	   virtual void loadNextData( int start, int end, string partitionNum );
	   int getAggsNum();
   protected:
	   virtual DWORD Threadwork();
   private:
	   unsigned thread_id;
	   struct Critical_Section gs;
       struct thread_para para;
       int globe_id;
	   int *cmd;
	   int Gcard;
	   int *Gfreq;
	   int dim_id;
       int tempflag;
	   int MiddleNum[P];
	   int MiddlePos[P];
	   int tempcheck[P];
	   int MiddleCard[P];

	   freq_pool Freq_pool[P];
	   int malloc_numbers[P];
	   int free_numbers[P];

	   int **dimDataDouble[2];
	   double **msrDataDouble[2];
	   int dflag[P];
	   double * msrValues;
	   int uclsNum[P];
	   int *aggsNumPerLayer;
	   FILE **fps;
	   string outDir;

	   void preComputation();
	   inline int findCard(int bPos, int ePos, int d,int thread_id); ///< find cardinality / maximum value of data on d th dimension.
	   void Partition(int bPos, int ePos, int d, int card, int *freq,int thread_id); ///< partition on the d th dimension.
	   void DFS(const int const cl[], int bPos, int ePos, int d,int thread_id);  ///< DFS algorithm.
	   inline int outputTodimDataFile(int layer, int outputDimData[]); ///< output dimension data to file.
	   inline int outputTomsrDataFile(int layer, double outputMsrData[]); ///< output measures data to file.
       void ReDFS(const int const cl[], int bCard, int eCard, int d,int thread_id);
};

}
#endif