/************************************************************************/
/* @author:	Weiji Xiao (xwjxwj238@163.com)                              */
/* Integration on 24/08/2007                                            */
/************************************************************************/


#include "Query/Common.h"
#include "Query/QueryResult.h"
#include "Query/QueryComputation.h"
#include "MdxParser/ParsedMDX.h"
#include "xodbc/XODBCDatabase.h"


using namespace std;
using namespace QueryComputationMethods;
using namespace xodbc;

void main()
{
	string cubeDir = "../Data/Foodmart/MTSales";
//	string mdxstring = "select from Sales";
//	string mdxstring = "SELECT {[Measures].[Store Cost], [Measures].[Store Sales]} ON columns, CrossJoin(Hierarchize(Union({[Promotion Media].[All Media]}, [Promotion Media].[All Media].Children)), {[Product].[All Products]}) ON rows FROM Sales WHERE ([Time].[1997])";

    string mdxstring = "SELECT {[Measures].[Store Cost], [Measures].[Store Sales]} ON columns, Hierarchize(Union(Union(CrossJoin({[Promotion Media].[All Media]}, Union(CrossJoin({[Product].[All Products]}, {[Gender].[All Genders]}), CrossJoin({[Product].[All Products]}, [Gender].[All Genders].Children))), CrossJoin({[Promotion Media].[All Media]}, Union(CrossJoin([Product].[All Products].Children, {[Gender].[All Genders]}), CrossJoin([Product].[All Products].Children, [Gender].[All Genders].Children)))), Union(CrossJoin([Promotion Media].[All Media].Children, Union(CrossJoin({[Product].[All Products]}, {[Gender].[All Genders]}), CrossJoin({[Product].[All Products]}, [Gender].[All Genders].Children))), CrossJoin([Promotion Media].[All Media].Children, Union(CrossJoin([Product].[All Products].Children, {[Gender].[All Genders]}), CrossJoin([Product].[All Products].Children, [Gender].[All Genders].Children)))))) ON rows FROM Sales WHERE ([Time].[1997])";
//	string mdxstring = "SELECT {[Measures].[Store Cost], [Measures].[Store Sales]} ON columns, Hierarchize(Union(Union(Union(CrossJoin({[Promotion Media].[All Media]}, {[Product].[All Products]}), CrossJoin({[Promotion Media].[All Media]}, [Product].[All Products].Children)), CrossJoin({[Promotion Media].[All Media]}, [Product].[All Products].[ADJ].Children)), Union(Union(CrossJoin([Promotion Media].[All Media].Children, {[Product].[All Products]}), CrossJoin([Promotion Media].[All Media].Children, [Product].[All Products].Children)), CrossJoin([Promotion Media].[All Media].Children, [Product].[All Products].[ADJ].Children)))) ON rows FROM Sales WHERE ([Time].[1997])";
	cout<<"开始查询："<<mdxstring<<endl;
	QueryComputation queried (mdxstring,cubeDir);

	//执行查询
	//for ( int k = 0; k < 2; k++ )
	//{
		Settime();
		CellSet queryResult = queried.queryComputation();
		cout<<"the query time:"<<Gettime()<<endl;
		
		//输出查询结果信息
		/*cout<<"axesSize:"<<queryResult.parsedMdx->getAxes().size()<<endl;
		cout<<"the Result cells:\n";
		cout<<"query Size:"<<queryResult.Cells.size();
		for ( int i = 0; i < queryResult.Cells.size(); i++ )
		{
			cout<<"Cell "<<i<<":  "<<queryResult.Cells[i].value<<endl;
			for(int j = 0; j <queryResult.Cells[i].cellDimsVals.size(); j ++)
				cout<<queryResult.Cells[i].cellDimsVals[j]<<" ";
			cout<<endl;
		}*/
//	}
}
