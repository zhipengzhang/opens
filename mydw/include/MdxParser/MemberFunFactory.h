/*******************************************
 * 此工厂类由于处理返回值对应于QueryMember
 * 的函数，并不是指MDX语言里的成员函数
 *******************************************/
#ifndef __MEMBERFUNFACTORY_H__
#define __MEMBERFUNFACTORY_H__

#include "QueryMember.h"
#include "DWSchemac/XSchema.h"
#include <vector>
#include <iostream>
#include "FunParam.h"

using namespace std;
using namespace dwschemac; 

//可以在此添加函数名来拓展支持的函数
enum MemType
	{
	     PrevMember,
	     FirstChild,
		 NextMember,
         LastChild,
		 CurrentMember,
		 FirstSibling,
		 LastSibling,
		 Parent,
		 Ancestor,
	};

class MemberFunFactory
{
public:
	  QueryMember* funInstance(XSchema* _pSch, string& _cubeName, MemType _type, std::vector<std::string>& theVector, FunParam *param);
};

#endif