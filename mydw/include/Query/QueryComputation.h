/**
 * @file QueryComputation
 * 查询算法抽象类定义文件
 * 该文件定义查询算法抽象类
 *
 */
#ifndef __QueryComputation_H_INCLUDE__
#define __QueryComputation_H_INCLUDE__

#include "MolapCCInvertListQuery.h"
#include "RolapCCQuery.h"
#include "MolapQueryComputationBase.h"
#include "MTCCQuery.h"

#include "QueryCmptException.h"

#include "./dwconfig/DWConfig.h"
#include "./dwconfig/DWConfiguration.h"
#include "./dwconfig/DWElement.h"

class ParsedMDX;

namespace QueryComputationMethods{
class QueryComputation
{
private:
	ParsedMDX* parsed;					///< MDX解析后的对象
	string mdxstring;					///< mdx语句
	string schemaName;
	string cubeName;

	void initialParsedMDX();
public:
	/**
	* @brief 查询算法接口类的构造函数
	*
	* 接收MDX解析后的对象，以及连接对象
	*
	* @param parsedMDX MDX解析后的对象
	* @param cubedir 多维数据库存储信息
	*/

	//从构造函数里面初始化出ParsedMDX对象出来
	explicit QueryComputation(string mdxstring_t,string schemaName_t);

	/**
	* @brief 查询算法接口类的析构函数
	*
	*释放资源
	*/
	~QueryComputation();
	
	/**
	* @brief 查询算法接口类的查询函数
	*
	*返回查询的结果集
	*/
	CellSet queryComputation( );
	
	ParsedMDX* getParsedMDX();  
};

};
#endif