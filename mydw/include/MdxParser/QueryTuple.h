#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif
#ifndef __QUERYTUPLE_H__
#define __QUERYTUPLE_H__
#include <vector>
#include "QueryMember.h"

using namespace std;
//namespace mdx{
/**
 *  类QueryTuple. 
 *  QueryTuple用于记录MDX查询的多维数据块，即元组的信息，
 *  它是QueryMember的一个向量，定义了数据切片.
 *  @see QueryMember
 *  @see ParsedMDX
 */
class QueryTuple
{   
    public:
            /**
			  *  默认构造函数. 
              */
            QueryTuple(); 
			/**
			  *  拷贝构造函数. 
              */
			QueryTuple(const QueryTuple& qt);
			/**
			  *  带参数的构造函数. 
			  *  @param _members 类型是vector<QueryMember>
              */
            QueryTuple(vector<QueryMember*>& _members);
            /**
			  *  获得在这个元组中的所有成员. 
			  *  @return vector<QueryMember>
              */
            const vector<QueryMember*> getMembers()const;
            /**
			 *  重载操作符＝
             */
		    QueryTuple& operator=(const QueryTuple& other);
			
			/**
			  *  判断QueryTuple对象是否为空，即是否不存在QueryMember对象
			  *  @return bool
              */
			bool empty()const;
            /**
			  *  重置QueryTuple对象
			  *  @return void
              */
            void setTuple(vector<QueryMember*>& _members);

			/**
			  *  展示QueryTuple
			  *  @return void
              */
			void showTuple();

	 private:
		    /**
			  *  一个QueryMember的容器，用以存储QueryMember对象
              */
            vector<QueryMember*> members;
	            
};

//}
#endif
