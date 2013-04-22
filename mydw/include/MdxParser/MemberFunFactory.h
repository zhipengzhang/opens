/*******************************************
 * �˹��������ڴ�����ֵ��Ӧ��QueryMember
 * �ĺ�����������ָMDX������ĳ�Ա����
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

//�����ڴ���Ӻ���������չ֧�ֵĺ���
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