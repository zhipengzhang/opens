/**
 * @file MolapCCPreComputation.h
 *
 * 封闭立方体预计算文件
 *
 * @author DBNCLab
 * Copyright(c) 2007 by School Of Computer Science & Engineering, South China University of Technology, Guangzhou, Guangdong, P.R.C. 
 *
 */

#ifndef _MOLAPCCPRECOMPUTATION_H_INCLUDE__
#define _MOLAPCCPRECOMPUTATION_H_INCLUDE__

#include "Common.h"
#include "MolapPreComputationBase.h"
#include "PreCmptException.h"

namespace PreCmpt{

class MolapCCPreComputation : public MolapPreComputationBase
{
private:
	int **dimDataDouble[2];
	double **msrDataDouble[2];
	int dflag;
	int uclsNum;
	int *aggsNumPerLayer;
	double* msrValues;
	FILE **fps;
	vector<long> **tmpData;
	string outDir;

	void preComputation();
	inline int findCard( int bPos, int ePos, int d );                        ///< find cardinality / maximum value of data on d th dimension.
	void Partition( int bPos, int ePos, int d, int card, int *freq );        ///< partition on the d th dimension.
	void DFS( const int const cl[], int bPos, int ePos, int d );             ///< DFS algorithm.

	inline int outputTomsrDataFile(int layer, double outputMsrData[]);       ///< output measures data to file.
	inline int outputToFile(int layer, int dims, int  outputStr);            ///< output dimension data to file by layers and dimensions.
	
	long filesize(FILE *stream) ;                                            ///< compute the file size.
	vector<long> changeStore(vector<long> num);                              ///< compress data and change storing method.
	void buildCCInvertListsIndex();                                          ///< build invert index algorithm.
	
public:
	explicit MolapCCPreComputation( XCube* cube /*,JobConf* conf*/ );
	virtual ~MolapCCPreComputation();

	virtual void excutePreCompute();
	
	virtual void loadData();
	virtual void loadNextData( int start, int end, string partitionNum );
	int getAggsNum();
};

}

#endif