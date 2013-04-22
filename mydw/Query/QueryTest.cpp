/************************************************************************/
/* @author:	Weiji Xiao (xwjxwj238@163.com)                              */
/* Integration on 24/08/2007                                            */
/************************************************************************/


#include "Query/Common.h"
#include "Query/QueryComputationBase.h"
#include "Query/MolapCCInvertListQuery.h"
#include "Query/MolapQueryComputationBase.h"
#include "Query/QueryResult.h"
#include "Query/QueryComputation.h"
#include "MdxParser/ParsedMDX.h"

using namespace std;
using namespace QueryComputationMethods;

void main()
{
/************************************************************************/
/* MDX????                                                          */
/************************************************************************/
//		Settime();
//
//		yyin = fopen("..\\MdxParser\\Debug\\mdx.txt","rt");
//
//		//call the parser 
//		yyparse (); 
//    
//		ErrorSummary ();
//
//		XSchemas s;
//		s.createSchema("..\\smq.xml");
// 		XSchema *ok=s.getSchema("FoodMart");  	
// 		ParsedMDX* p = tree->traverse(vecMemInfo, vecMem, vecTuple, vecSet, ok);
//		s.Dispose();
//		cout<<"MDXTime:"<<Gettime()<<endl<<endl;	

/************************************************************************/
/* ??????????                                                 */
/************************************************************************/ 	

		//??????????(????????),?????????????????????
		//???????????
//	string cubeDir1 = ".\\TEST";
string cubeDir1 = ".\\Sales";
		//string mdxstring = "select {([Measures].[unit sales]),([Measures].[store cost]), ([Measures].[store sales])} on 0 from [Sales]";//?????????mdx??
		//string mdxstring = "select {([Measures].[unit sales])} on 0 from [Sales]";//?????????mdx??
		//string mdxstring = "select from [Sales]";

     //string mdxstring = "select {([D1].[s2],[D2].[p1]),([D1].[s1],[D2].[p2])} on 0 from [TEST]";
		//string mdxstring = "select from Sales where ([Measures].[Store Sales])";
	  //string mdxstring = "select from Sales where ([Time].[1997])";

	string mdxstring = "select {[Measures].[Store Cost], [Measures].[Store Sales]} on columns, {([Promotion Media].[All Promotion Medias], [Product].[All Products])} ON rows from Sales where ([Time].[1997])";

	//	std::ofstream logFile("out.txt");
	//	std::streambuf *outbuf = std::cout.rdbuf(logFile.rdbuf());
		cout<<"堆求交算法："<<endl;
		QueryComputation queried (mdxstring,cubeDir1);
		
		//执行查询
		CellSet queryResult1 = queried.queryComputation();
		//输出查询结果信息
		
		cout<<"axesSize:"<<queryResult1.parsedMdx->getAxes().size()<<endl;
		cout<<"XMLA Result cells:\n";
		for (int i = 0; i < queryResult1.Cells.size();i ++)
		{
			cout<<"Cell "<<i<<":  "<<queryResult1.Cells[i].value<<endl;
			for(int j = 0; j <queryResult1.Cells[i].cellDimsVals.size(); j ++)
				cout<<queryResult1.Cells[i].cellDimsVals[j]<<" ";
			cout<<endl;
		}
	//	std::cout.rdbuf(outbuf);
}
