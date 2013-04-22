
/**
 * @file QueryComputationBase
 * 查询算法抽象类定义文件
 * 该文件定义查询算法抽象类
 *
 */

#ifndef __QueryComputationBase_H__
#define __QueryComputationBase_H__

#include "Common.h"
#include "QueryResult.h"
#include "AggReader.h"

#include "QueryCmptException.h"


namespace QueryComputationMethods{

class QueryComputationBase
{
public:
	QueryComputationBase(){}
	virtual ~QueryComputationBase(){};

	virtual CellSet query() = 0;

};

};
#endif