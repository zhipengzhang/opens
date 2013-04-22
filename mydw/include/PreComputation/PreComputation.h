/**
 * @file MolapPreComputationBase.h
 *
 * 预计算的对外接口文件
 *
 * @author DBNCLab
 * Copyright(c) 2007 by School Of Computer Science & Engineering, South China University of Technology, Guangzhou, Guangdong, P.R.C. 
 *
 */

/**
 * @file PreComputation
 *
 * 该文件定义了对预计算的接口
 *
 * @author xyh
 */

/**
 * @brief 执行预计算
 * 
 */

#ifndef _PRCOMPUTATION_H_INCLUDE__
#define _PRCOMPUTATION_H_INCLUDE__

#include "MolapCCPreComputation.h"
#include "MolapMTCCPreComputation.h"
#include "MolapFCPreComputation.h"
#include "RolapCCPreComputation.h"
#include "MTPDCCPreComputation.h"
#include "PreCmptException.h"

#include "./dwconfig/DWConfig.h"
#include "./dwconfig/DWConfiguration.h"
#include "./dwconfig/DWElement.h"

namespace PreCmpt{

class PreComputation
{	
public:
	PreComputation();
	~PreComputation();

	/*
	* Interface of preCompute
	*@param schemaName: the schema to preCompute
	*@param cubeName: the cube to preCompute
	*@return string: the result of preCompute
	*/
	string preCompute( string schemaName, string cubeName );
};

};
#endif
