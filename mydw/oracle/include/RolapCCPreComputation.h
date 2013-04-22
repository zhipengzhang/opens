#ifndef _ROLAPCCPRECOMPUTATION_H_INCLUDE__
#define _ROLAPCCPRECOMPUTATION_H_INCLUDE__

#include "Common.h"
#include "MolapPreComputationBase.h"

#include "PreCmptException.h"

namespace PreCmpt{

class RolapCCPreComputation : public MolapPreComputationBase
{
private:
	int** dimDataDouble[2];
	double** msrDataDouble[2];
	int dflag;
	int uclsNum;
	vector<int> aggsNumPerLayer;
	double* msrValues;                                                       ///< storage upper cell measure values
	XODBCDatabase outXDB;

	void preComputation();
	inline int findCard( int bPos, int ePos, int d );                        ///< find cardinality / maximum value of data on d th dimension.
	void Partition( int bPos, int ePos, int d, int card, int *freq );        ///< partition on the d th dimension.
	void DFS( const int const cl[], int bPos, int ePos, int d );             ///< DFS algorithm.
	
public:
	explicit RolapCCPreComputation( XCube* cube /*,JobConf* conf*/ );
	virtual ~RolapCCPreComputation();

	virtual void loadData();
	virtual void loadNextData( int start, int end, string partitionNum );
	virtual void excutePreCompute();
	int getAggsNum();
};

}

#endif