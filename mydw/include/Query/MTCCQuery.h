#ifndef _MTCCQuery_H_
#define _MTCCQuery_H_


#include <windows.h>
#include <process.h>
#include "QueryResult.h"
#include "common.h"

#include "MolapQueryComputationBase.h"
#include "MolapCCInvertListQuery.h"
#include "RolapCCQuery.h"

#include "./dwconfig/DWConfig.h"
#include "./dwconfig/DWConfiguration.h"
#include "./dwconfig/DWElement.h"

#include "./MdxParser/ParsedMDX.h"

#include "QueryCmptException.h"

using namespace std;
class ParsedMDX;
class Cell;

namespace QueryComputationMethods{

struct Critical_Section_Query{
	CRITICAL_SECTION cs;
    int level;
	int flag;
	int finished_threads;
};

typedef enum _AlgType{ ROLAP, MOLAP } ALGTYPE;

class MTCCQuery
{
	
public:
	MTCCQuery(ParsedMDX *parsedMDX,ALGTYPE algType_t);
	
	virtual ~MTCCQuery();
	void lock();
	void unlock();
	static unsigned __stdcall QueryChildThread(void* param);
	CellSet query();
	   
protected:
	virtual DWORD ThreadQueryWork();
private:
	vector<string> mdxMsrAggType;
	int msrsLineCount;

	unsigned thread_id;
	struct Critical_Section_Query gs;
	HANDLE* thread_set;
	HANDLE host_thread;

	ParsedMDX *parsedMdx;
	ALGTYPE algType;
	
	int splitNumber;                                     ///分块的个数
	vector<Cell> *Cells;

	int QuerythreadNum;                                  ///线程数
	
	void getMdxMsrAggType();	
	map<string,string> getMetaMsrAggType();
	
	void mergeFun();
	double aggSum( vector<double>& values );
	double aggMax( vector<double>& values );
	double aggMin( vector<double>& values );
	double aggCount( vector<double>& values );
	//double aggAvg( vector<double>&sum , vector<double>&count );
};

};
#endif