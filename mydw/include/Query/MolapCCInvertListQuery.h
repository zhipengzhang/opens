/**
 * @file CCInvertListQuery
 * 压缩求交查询算法类定义文件
 * 该文件定义压缩求交查询算法类
 *
 * 
 */
#ifndef _CCINVERTLISTQUERY_H_INCLUDE__
#define _CCINVERTLISTQUERY_H_INCLUDE__

#include "Common.h"
#include "AggReader.h"
#include "MolapQueryComputationBase.h"
#include "QueryResult.h"
#include "AggFileReader.h"

#include "QueryCmptException.h"

#include "./MdxParser/ParsedMDX.h"

#include "./dwconfig/DWConfig.h"
#include "./dwconfig/DWConfiguration.h"
#include "./dwconfig/DWElement.h"

using namespace std;
class ParsedMDX;

namespace QueryComputationMethods
{
/**
 * @brief 压缩的堆求交查询算法类
 *
 * 利用压缩的堆求交查询算法进行OLAP查询，返回查询的结果集
 * 
 */
class MolapCCInvertListQuery : public MolapQueryComputationBase
{
public:
	/**
     * @brief 压缩的堆求交查询算法类的构造函数
     *
     * 接收MDX解析后的对象，以及连接对象
     *
     * @param parsedMDX MDX解析后的对象
     * @param conn 多维数据库连接对象
     */
	MolapCCInvertListQuery( ParsedMDX* parsedMDX );
	MolapCCInvertListQuery( ParsedMDX* parsedMDX, string partitionNum );

	/**
     * @brief 压缩的堆求交查询算法类的析构函数
     *
     * 释放类初始化的相关资源
     *
     */
	virtual ~MolapCCInvertListQuery();
	/**
     * @brief 压缩的堆求交查询算法类的点集查询函数
     *
     * 执行所有OLAP查询请求，并返回最终的查询结果到QueryResult对象
     *
	 * @return 返回所有查询的结果到QueryResult对象
     */
	CellSet query();

	vector<Cell> Cellquery();

protected:
	void setCacheUpper(vector< string > upper);		//设置某个查询缓存的上界
	vector<string> getCacheUpper() const;			//获得某个查询缓存的上界
		/**
     * @brief 堆求交查询算法类的获取查询结果维度值函数
     *
     * 用于获取用户请求的查询结果存在的查询记录的维度值集合
     *
	 * @param layer 满足的查询记录所在上界的层数
	 * @param layer 满足的查询记录所在上界layer层中的行数
     */
	inline void getDimValues(int layer, int row);
    /**
     * @brief 堆求交查询算法类的获取查询结果度量值函数
     *
     * 用于获取用户请求的查询结果存在的查询记录的度量值集合
     *
	 * @param layer 满足的查询记录所在上界的层数
	 * @param row 满足的查询记录所在上界layer层中的行数
     */
	inline void getMsrValues(int layer, int row);
			/**
     * @brief 压缩的堆求交查询算法类的点查询函数
     *
     * 利用已经建立好的压缩的反转索引元组ID列表执行单条OLAP查询请求，并获取查询结果
     *
     */
	inline void pointQuery( int *qry );				//也作为缓存查询调用入口

private:
		/**
     * @brief 压缩的堆求交查询算法类的获得维度值元组ID列表函数
     *
     * 接收点查询某一维度上某个维度值，读取压缩的反转索引获取该维度值的元组ID列表
     *
     * @param dims 点查询的某一个维度
     * @param val  点查询该维度上的维度值
	 * @return 返回元组ID列表的位置集合
     */
	vector<int> getDimsPos(int dims,int val);
		/**
     * @brief 压缩的堆求交查询算法类的运用顺序查找算法返回查找当前维度中不小于nVal的位置值函数
     *
     * 接收当前比较位置值、所在的维度位置集合和开始查找的位置，
	 * 返回查找当前维度中不小于nVal的位置值，如果到达最后一个位置返回－2
     *
     * @param nVal 当前比较位置值
     * @param dimsVal  该值所在维度位置值集合
	 * @param vecPos 在位置值集合中开始查找的位置
	 * @return 返回查找当前维度中不小于nVal的位置值，找不到返回－2
     */
    int findNextMaxVal(int nVal, vector<int> &dimsVal, int &vecPos);
		/**
     * @brief 压缩的堆求交查询算法类的获得点查询在上界集中的位置函数
     *
     * 接收点查询各个维度上查询维度值的元组ID列表的集合，返回找到的该点查询在原始上界集中的位置值
     *
     * @param dimsPos 点查询各个维度上查询维度值的元组ID列表的集合
	 * @return 返回找到的该点查询在原始上界集中的位置值
     */
	int findQryPointPos(vector< vector<int> > &dimsPos);
	vector<int> aggsNumPerLayer;                             ///<上界集每一层的行数
	int zeroLayer;                                           ///<上界集空的层的层数
	int* perLayerNumBefore;                                  ///<每一层前面的行数
	map< int, vector<int> >* buffer;
	
ofstream outfile;
ofstream out_file;
ofstream out_time;
};

};
#endif