
/**
 * @file MolapPreComputationBase.h
 *
 * MOLAP架构下立方体预计算文件
 *
 * @author DBNCLab
 * Copyright(c) 2007 by School Of Computer Science & Engineering, South China University of Technology, Guangzhou, Guangdong, P.R.C. 
 *
 */
#ifndef _MOLAPPRECOMPUTATIONBASE_H_INCLUDE__
#define _MOLAPPRECOMPUTATIONBASE_H_INCLUDE__

#include "PreComputationBase.h"
#include "PreCmptException.h"
#include "AggWriter.h"
#include "AggDBWriter.h"
#include "AggFileWriter.h"

#include "Common.h"
#include "FileHandle.h"

#include "DWSchemac/Dimension.h"
#include "DWSchemac/Hierarchy.h"
#include "DWSchemac/XSchemas.h"
#include "DWSchemac/Level.h"
#include "DWSchemac/XCube.h"
#include "DWSchemac/XSchema.h"
#include "DWSchemac/Measure.h"
#include "xodbc/XODBCDatabase.h"

#include "./dwconfig/DWConfig.h"
#include "./dwconfig/DWConfiguration.h"
#include "./dwconfig/DWElement.h"

using namespace xodbc;
using namespace dwschemac;

namespace PreCmpt{

typedef set<string> column;
typedef map<string,int> Mapper;                                            ///< 维度值映射为数字的映射表

typedef enum _INTYPE{ TXT,DB }INTYPE;                                                     ///<数据输入类型TXT:文本输入 DB:数据库输入

const int ALL = 0;
const int AGGFUNNUM = 9;                                                   ///< 定义聚集函数个数

class MolapPreComputationBase;
typedef double (MolapPreComputationBase::* aggFun)( double **msrData, int bPos, int ePos, int msrNum );

class MolapPreComputationBase : public PreComputationBase
{
protected:
	int** dimData;
	double** msrData;
	int* card;
	int dimsNum;
	int msrsNum;
	int tuplesNum;

	string* mapData;
	vector<string> hdrData;
	AggWriter* aggWriter;
	
	static XODBCDatabase InXDB;
	static XODBCRecordset* pRS;
	
	INTYPE inputType;
	string InDir;

	vector<int> aggFunOrder;
	aggFun aggFunLib[AGGFUNNUM];

	void setAttribute();
	void loadDataTxt();
	void loadDataTable();
	void loadDataTxt( int start, int end );
	void loadDataTable( int start, int end );
	string buildSQL();                                                      ///< 根据XCube对象构造SQL
	inline void addAggFunOrder( const string& aggFunType );                           ///< 添加聚集函数标志

	/**
	* @brief 下面几个函数为系统所支持的各种聚集函数
	*/
	double sumFun(double **msrData, int bPos, int ePos, int msrNum);        ///< 求和
	double countFun(double **msrData, int bPos, int ePos, int msrNum);      ///< 求元素个数
	double avgFun(double **msrData, int bPos, int ePos, int msrNum);        ///< 求平均值
	double maxFun(double **msrData, int bPos, int ePos, int msrNum);        ///< 求最大值
	double minFun(double **msrData, int bPos, int ePos, int msrNum);        ///< 求最小值
	double firstFun(double **msrData, int bPos, int ePos, int msrNum);      ///< 求第一个元素
	double lastFun(double **msrData, int bPos, int ePos, int msrNum);       ///< 求最后一个元素
	double distinctFun(double **msrData, int bPos, int ePos, int msrNum);   ///< 求不同元素的个数
	double mediumFun(double **msrData, int bPos, int ePos, int msrNum);     ///< 求中间值

public:
	MolapPreComputationBase( XCube* cube );
	virtual ~MolapPreComputationBase();

	virtual void excutePreCompute()=0;   ///<执行预计算
	int getTuplesNum();
	virtual void loadData();
	virtual void loadNextData( int start, int end, string partitionNum );
};

}
#endif
