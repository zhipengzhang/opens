
/**
 * @file QueryComputationBase
 * ��ѯ�㷨�����ඨ���ļ�
 * ���ļ������ѯ�㷨������
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