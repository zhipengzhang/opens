//*****************************************************
//Header file of QueryMember.h for the MDX
//Copyright(c) 2007/6/1 by Roger,MDX complier
//*****************************************************
#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

#include <string>
#include <vector>


#ifndef __QUERYMEMBER_H__
#define __QUERYMEMBER_H__
using namespace std;

class calcMemFormat;

/**
 *  类QueryMember . 
 *  QueryMember 是用来表示MDX查询语句查询的成员，成员是MDX查询中的最小粒度，
 *  其主由成员的值、成员所在的level名字、成员所在的hierarchy名字、成员的所
 *  有父成员所在的level名字和成员所有父成员的值,成员的后缀表达式(如果是计算
 *  成员)构成.
 *  @see QueryTuple
 *  @see ParsedMDX
 *  @see calcMemFormat
 */
class QueryMember 
{
    public:
	   /**
        * 默认构造函数.
        */
		QueryMember();

        /**
         * 拷贝构造函数.
         */
		QueryMember(const QueryMember& other);

        /**
         * 带参数的构造函数.
		 * @param _hierarchyName 成员所在的hierarchy名字
		 * @param _levelName     成员所在的level名字
         * @param _val           成员的值
		 * @param _ancestorVals  成员的父成员的值，类型为一个string型的vector容器
         * @param _ancestorLevels  成员的父成员所在的level，类型为一个string型的vector容器
         */
        QueryMember(string& _dimensionName,
					string& _hierarchyName,
					string& _levelName,
					string& _val,
					vector<string>& _ancestorVals,
					vector<string>& _ancestorLevels,
					bool _isAll,
					bool _isCalculated); 


        /**
         * 用于得到成员的值
		 * @return string
         */
        const string getVal()const;

		/**
         * 用于得到成员所在level的名字
		 * @return string
         */
        const string getLevelName()const;

		/**
         * 用于得到成员所在hierarchy的名字
		 * @return string
         */
        const string getHierarchyName()const;

		/**
         * 用于得到成员所在dimension的名字
		 * @return string
         */
        const string getDimensionName()const;

        /**
         * 用于得到成员的所有父成员的值
		 * @return vector<string>
         */
		const vector<string> getAncestorVals()const;

		/**
         * 用于得到成员所有父成员所在的level名字
		 * @return vector<string>
         */
		const vector<string> getAncestorLevels()const;

		/**
         *  返回QueryMember是否为顶层member的信息
		 *  @return bool
		 */
         bool hasAll();

		 /**
         *  返回QueryMember是否为计算成员的信息
		 *  @return bool
		 */
		 bool getIsCalculated();

		 /**
         *  返回计算成员的后缀表达式信息
		 *  @return vector<calcMemFormat* >
		 */
		 vector<calcMemFormat* > getCalcFormat();

        /**
         * 重载操作符＝
         */
		QueryMember& operator=(const QueryMember& other);
		
        /**
         * 重置成员的值
		 * @return void
         */
		void setVal(string _val);
			
        
		/**
         * 重置成员所在的level名字
		 * @return void
         */
		void setLevelName(string _levelName);
			
        
		/**
         * 重置成员所在的hierarchy名字
		 * @return void
         */
		void setHierarchyName(string _hierarchyName);
			
        /**
         * 重置成员所在的dimension名字
		 * @return void
         */
		void setDimensionName(string _dimensionName);
			
        /**
         * 重置成员所有父成员的值
		 * @return void
         */
		void setAncestorVals(const vector<string>& _ancestorVals);

		/**
         * 重置成员所有父成员所在的level的值
		 * @return void
         */
		void setAncestorLevels(const vector<string>& _ancestorLevels);

		void setIsAll(bool _isAll);

		/**
         * 设置成员是否为计算成员
		 * @return void
         */
		void setIsCalculated(bool _isCalculated);

		/**
         * 设置计算成员的后缀表达式
		 * @return void
         */
		void setCalcFormat(vector<calcMemFormat *> &_format);
        /**
         * 打印成员的信息
		 * @return void
         */
		void showMember();

		void _showMember();

		vector<string> getMemberName();

	private:
		/**
         * 用于表示成员所在的dimension名字
         */
		string dimensionName;
		/**
         * 用于表示成员所在的hierarchy名字
         */
        string hierarchyName;
		/**
         * 用于表示成员所在的level名字
         */
        string levelName;
		/**
         * 用于表示成员的值
         */
        string val;	  
        /**
         * 用于表示成员所有的父成员的值
         */
	    vector<string> ancestorVals;
		/**
         * 用于表示成员父成员所在的level名字
         */
		vector<string> ancestorLevels;

		/**
 		 * bool型，用于判断成员是否是ALL
 		 * 即Hierarchy的hasall属性是否为真
 		 */
		 bool isAll;

		 /**
 		 * bool型，用于判断成员是否为计算成员
 		 */
		 bool isCalculated;

		 /**
 		 * 用于表示计算成员的后缀表达式
 		 */
		 vector<calcMemFormat* > calcFormat;
};

#endif
