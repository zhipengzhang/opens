#ifndef __PARSEDMDX_H__
#define __PARSEDMDX_H__

#pragma warning (disable: 4514 4786)

#include <string>
#include "QueryTuple.h"
#include "calculatedMember.h"

using namespace std;
/**
 *  类ParsedMDX. 
 *  ParsedMDX 是QueryTuple的一个向量，记录了待查询的所有元组信息
 *  ParsedMDX 是预计算模块所需要的，从MDX编译器解析出来查询对象
 *  @see QueryTuple
 *  @see QueryMember
 */
class ParsedMDX
{
    public:
		/**
          *  默认构造函数
          */
        ParsedMDX();

	    /**
          *  拷贝构造函数. 
          */
		ParsedMDX(const ParsedMDX& );

        /**
          *  带参数的构造函数
		  *  @param _cubeName 立方体的名字
		  *  @param _schemaName MDX查询主题的名字
		  *  @param _slicer  一个切片，即QueryTuple对象
		  *  @param _pCaclMember  存储计算成员的容器
		  *  @param _axes 查询轴的信息，是一个容器的容器，用于存储查询的成员、元组的信息
          */
        ParsedMDX(string _cubeName,
			      string _schemaName,
				  vector<QueryTuple*>& _slicer,
				  vector<calculatedMember*>& _pCaclMember,
                  const vector< vector<QueryTuple*> >& _axes,
				  bool _nonempty);

        /**
          *  析构函数
          */
        ~ParsedMDX();
		
		/**
         * 用于得到MDX查询的立方体的所在的schema的名字
		 * @return string
         */
        const string getSchemaName()const;

        /**
         * 用于得到MDX查询的立方体的名字
		 * @return string
         */
        const string getCubeName()const;

		/**
         * 用于得到轴上的所有成员、元组
		 * @return vector< vector<QueryTuple> >
         */
        vector< vector<QueryTuple*> > getAxes();


		/**
         * 用于得到所有计算成员
		 * @return vector< calculatedMember* >
         */
		vector<calculatedMember*> getCalcMember();


        /**
         * 用于得到切片的信息
		 * @return QueryTuple
         */
        const vector<QueryTuple*> getSlicer()const;

        /**
         * 用于重置主题名
		 * @param _sechemaName 主题名
		 * @return void
         */
		void setSchemaName(string _schemaName);

		/**
         * 用于重置切片轴
		 * @param _slicer 切片，QueryTuple对象
		 * @return void
         */
		//void setSlicer(const QueryTuple& _slicer);
			//throw (MDXParsedException);

		/**
         * 用于重置所有轴（除去切片轴）
		 * @param _axes 查询轴，类型为vector< vector<QueryTuple> >
		 * @return void
         */
		void setAxes(const vector< vector<QueryTuple*> >& _axes);

       /**
         * 用于展示ParsedMDX的内容
		 * @return void
         */
		void showParsedMDX();

    private:
	    /**
          *  立方体的名字
          */
        string cubeName;

		/**
          *  主题名字
          */
	    string schemaName;

		/**
          *  切片,用于存储切片；
		  *  其中对于一条特定的MDX查询语句，slicer要存储出现在WHERE
		  *  子句中的切片和除出现在MDX查询轴（SELECT）中的Cube中的所有的
		  *  维度的所有的顶层Member，并且要按顺序存储；即没有出现在查询轴
		  *  的维必须出现在切片轴,这样处理主要是由于查询模块和XMLA所需；
		  *  如：一个立方体有3个维度依次为Product,Time和Store，Time维出现在
		  *  WHERE中，形如where [Time].[All times].[1997]。而Product和Stroe
		  *  的顶层成员分别为[All products]和[All stroes]。则要依次存储
		  *  [Product].[All products],[Time].[All times].[1997]和
		  *  [Stroe].[All stroes]这样三个QueryTuple；
          */
        vector<QueryTuple*> slicer; 

		/**
          *  查询轴
          */
		vector< vector<QueryTuple*> > axes;


		/**
          *  计算成员
          */
		vector<calculatedMember*> pCaclMember;

		/**
		 *  是否显示空的值                                                       
		 */
		bool nonEmpty;
};

//}
#endif
