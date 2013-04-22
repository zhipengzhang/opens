/**
 * @file MolapFullPreComputation.h
 *
 * 完全立方体预计算文件
 *
 * @author DBNCLab
 * Copyright(c) 2007 by School Of Computer Science & Engineering, South China University of Technology, Guangzhou, Guangdong, P.R.C. 
 *
 */

#ifndef _MolapFullPreComputation_h_
#define _MolapFullPreComputation_h_

#include "Common.h"
#include "MolapPreComputationBase.h"
#include "PreCmptException.h"

namespace PreCmpt{

class MolapFullPreComputation : public MolapPreComputationBase{
private:

	int **dimDataDouble[2];
	double **msrDataDouble[2];
	int dflag;
	double * msrValues;
	int uclsNum;
	int *aggsNumPerLayer;
	FILE **fps;
	string outDir;
	

	void preComputation();
	inline int findCard(int bPos, int ePos, int d); ///< find cardinality / maximum value of data on d th dimension.
	void Partition(int bPos, int ePos, int d, int card, int *freq); ///< partition on the d th dimension.
	void DFS( int cl[], int bPos, int ePos, int d);  ///< DFS algorithm.
	inline int outputTodimDataFile(int layer, int outputDimData[]); ///< output dimension data to file.
	inline int outputTomsrDataFile(int layer, double outputMsrData[]); ///< output measures data to file.

public:
	explicit MolapFullPreComputation(XCube *cube /*,JobConf* conf*/);
	virtual ~MolapFullPreComputation();

	virtual void excutePreCompute();

	virtual void loadData();
	virtual void loadNextData( int start, int end, string partitionNum );
	int getAggsNum();
};

}

#endif