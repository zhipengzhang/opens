#ifndef __SETFUNFACTORY_H__
#define __SETFUNFACTORY_H__
#include "DWSchemac/XSchema.h"
#include <vector>
#include <string>
using namespace std;
using namespace dwschemac; 

#include "FunParam.h"

class QueryTuple;
enum SetTypefirst {
	Crossjoin,
	Union,
	Intersect,
};
enum SetTypesec {
	Children,
	Members,
	AllMembers,
	Siblings,
	Descendants,
	Ascendants
			 
};
enum SetTypethird {
	Hierarchize, //不考虑使用POST参数
	Distinct,
	Tail,
	Head,
	Order
};
class SetFunFactory
{
public:
	std::vector<QueryTuple*> funInstance(SetTypefirst _typefist, 
									     std::vector<QueryTuple*>& set1,
									     std::vector<QueryTuple*>& set2,
										 FunParam *param);

	std::vector<QueryTuple*> funInstance(XSchema* _pSch, 
										 std::string& _cubeName, 
									     SetTypesec _typesec, 
									     std::vector<std::string>& theVector,
										 FunParam *param);
	
	std::vector<QueryTuple*> funInstance(SetTypethird _typethird, std::vector<QueryTuple*>& set, FunParam *param);
};				


#endif