/**
 * @file MolapPreComputationBase.h
 *
 * 立方体预计算基类文件
 *
 * @author DBNCLab
 * Copyright(c) 2007 by School Of Computer Science & Engineering, South China University of Technology, Guangzhou, Guangdong, P.R.C. 
 *
 */

#ifndef _PRECOMPUTATIONBASE_H_INCLUDE__
#define _PRECOMPUTATIONBASE_H_INCLUDE__

#include "DWSchemac/XCube.h"
#include "DWSchemac/XSchema.h"

#include "PreCmptException.h"

using namespace dwschemac;

namespace PreCmpt
{

class PreComputationBase
{	
protected:
	XCube* cube;
	string schemaName;
	string cubeName;
	
public:
	PreComputationBase( XCube* cube );
	virtual ~PreComputationBase();

	virtual void excutePreCompute() = 0;                                        ///<执行预计算
	virtual void loadData() = 0;
	virtual void loadNextData( int start, int end, string partitionNum ) = 0;

};

}

#endif

	