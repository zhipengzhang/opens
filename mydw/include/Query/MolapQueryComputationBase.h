 /*============================================================================
  File:    QueryComputation.h

  Summary: The identifier of QueryComputation members and operations for query

  Copyright(c) 2007 by DBNC Lab, South China University of Technology, Guangzhou, Guangdong, P.R.C. 

------------------------------------------------------------------------------
  Modification history:
  2007.01.30 Version 1.0 by Yuhong Xiao
============================================================================*/
/**
 * @file MolpQueryComputationBase
 * molap查询算法类定义文件
 * 该文件定义MOLAP查询算法基类
 */

#ifndef __MOLAPQUERYCOMPUTATIONBASE_H_INCLUDE__
#define __MOLAPQUERYCOMPUTATIONBASE_H_INCLUDE__

#include "Common.h"
#include "QueryResult.h"
#include "AggReader.h"
#include "AggDBReader.h"
#include "AggFileReader.h"
#include "QueryComputationBase.h"
#include "xodbc/XODBCDatabase.h"

#include "DWSchemac/XSchemas.h"
#include "DWSchemac/XSchema.h"
#include "DWSchemac/Measure.h"
#include "DWSchemac/XCube.h"

#include "QueryCmptException.h"

using namespace dwschemac;
using namespace xodbc;

class ParsedMDX;
class QueryTuple;


namespace QueryComputationMethods{

//该map用于判断某条查询是否存在，不存在的插入并把对应的度量作为map的键的值存储起来
typedef map< vector<int>, vector<double> > queryCellMapType;

class MolapQueryComputationBase:public QueryComputationBase
{
private:
	MapTable hdrData;
	MapTable* mapTable;
	int row;

	void mdxHdrMap(vector< vector<QueryTuple*> > &axes);
	void getCartesianProduct(vector< vector<QueryTuple*> > &axes,int axesNum);

	void getMsrFormatStr();
	
protected:
	int** qryPoints;						 ///< 保存ParsedMDX类的对象转换后的点集,查询点集
	string** qryPointsDimsVals;              ///< 保存点查询原来的维度值
             
	vector<double> msrValues;				 ///< 读取点查询结果所有度量的向量
	vector<string> dimValues;				 ///< 查询返回的上界 

	//parsedMDX头信息
	vector<int> mdxMsrHdr;
	vector<string> msrFormatStr;             ///< 存放所有度量的FormatString
	int dimsNum;						     ///< 查询的维度数量
	int msrsNum;						     ///< 查询的度量数量
	int tuplesNum;                           ///< 从ParsedMdx获得的点查询记录条数	
	int enterLayer;					         ///< 查询入口层

	ParsedMDX *parsedMdx;                    ///< 保存MDX解析后的对象

	AggReader *aggReader;
	
	int msrsLineCount;				         ///< 用于统计度量值关联的行数
	bool isNull;                             ///< 判断某条查询记录是否存在
	queryCellMapType queryCellMap;           ///< 记录查询的不同记录cells
	vector<int> qrycell;				     ///< 用于加入queryCellMap中的查询记录向量作为查询的键
	int slicerTuplesNum;                     ///< 记录切片轴tuples数目，用于结果度量的合并

	//下面两个函数用于和缓存的处理接口
	//设置点查询对应的上界
	virtual void setCacheUpper(vector< string > upper);
	//获得点查询对应的上界
	virtual vector<string> getCacheUpper() const;


	virtual inline void pointQuery( int *qry ) = 0;

public:
	/**
	* @brief 查询算法基类的构造函数
	*
	* 接收MDX解析后的对象、连接对象等初始化操作
	*
	* @param parsedMDX MDX解析后的对象
	* @param conn 多维数据库连接对象
	*/
	explicit MolapQueryComputationBase( ParsedMDX* parsedMDX );

	/**
	 * @brief 查询算法基类的析构函数
	 *
	 * 释放计算所用到的资源
	 */
	virtual ~MolapQueryComputationBase();


	/**
	 * @brief 执行查询计算
	 *
	 * 读取MDX解析后的对象，进行查询计算，并返回查询结果集，任何查询算法都要实现它，
	 */
	virtual CellSet query();

	int** getQueryPoints(ParsedMDX *parsedMdx);

};

};
#endif
