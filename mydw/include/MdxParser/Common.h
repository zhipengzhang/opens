                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
                                                               
#ifndef __COMMON_H__
#define __COMMON_H__

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <assert.h>

#include "DWSchemac/Level.h"
#include "DWSchemac/Member.h"
#include "MdxParser/QueryMember.h"
#include "MdxParser/QueryTuple.h" 


using namespace std;
using namespace dwschemac;


/*
 *MDX语句支持多个Hierarchy，一般情况下，Hierarchy
 *是默认的，在MDX语句里面是不会出现Hierarchy的信息的
 *但也可以指定是不对默认的Hierarchy进行查询，此时，
 *Hierarchy的名字附加在Dimension名字后。
 *如，默认情况下，[Time].[1997],Time 是维度名字，1997是
 *成员名，Hierarchy名字是看不到的，默认的；但可以指定
 *对一个非默认的Hierarchy进行查询，如[Time.***].[1997]
 *这时，***即为指定的Hierarchy;
 *
 */

inline bool isDimHie(string& dimHie)
{
	int a = dimHie.find(".");
    if(a == -1)
		return false;
	else
		return true;
}


inline std::vector<string> distinct(string& dimHie)
{
	std::vector<string> dimHieInfo;
     if (isDimHie(dimHie))
     {
		 int n = dimHie.find(".");
		 int size = dimHie.size();
		 string dimName, hieName;
		 dimName.assign(dimHie, 0, n);
		 hieName.assign(dimHie, n+1, size);
		 dimHieInfo.push_back(dimName);
		 dimHieInfo.push_back(hieName);
     }
	 else
	 {
	     string dimName = dimHie;
		 dimHieInfo.push_back(dimName);
	 }

	 return dimHieInfo;
}

//判断两个同size的vector<QueryMember*>的前n个QueryMember是否相同,n的范围为[0,vec1.size()-1]    // 前n个吧 add by eason
//0表示对第一列进行处理，前面没有列，永为真。
//主要用在hirarchize函数的处理上
inline bool isEqual(vector<QueryMember*>& vec1, vector<QueryMember*>& vec2, int n )
{
	bool eql = true;
	if (vec1.size() != vec2.size())
	{
		return false;
	}
	else if(n >= vec1.size())
	{
		return false;
	}
	else if (n == 0)
	{
		return true;
	} 
	else
	{
		for (int i = 0; i != n; i++)
		{
			if ((vec1[n-1-i]->getVal() != vec2[n-1-i]->getVal())&&(vec1[n-1-i]->getLevelName() != vec2[n-1-i]->getLevelName()))
			{
				//该函数有错，应把上面的&&改为||   add bu eason
				eql = false;
				break;                      // add by eason
			}
		}
		return eql;
	}
}


//判断两个QueryMember是否相同
inline bool isEqual_QryMember(QueryMember *mem1, QueryMember* mem2)
{
	vector<string> name1 = mem1->getMemberName();
	vector<string> name2 = mem2->getMemberName();

	if (name1.size() != name2.size())
	{
		return false;
	}
	
	else
	{
		int n = name1.size();
		
		for (int i = 0; i < n; i++)
		{
			if ( name1.at(i) != name2.at(i) )
			{
				return false;
			}
		}
	}
	
	return true;

}



//判断两个vector<QueryMember*>是否相同

inline bool isEqual_vecMember(vector<QueryMember*>& vec1, vector<QueryMember*>& vec2 )
{
	
	if (vec1.size() != vec2.size())
	{
		return false;
	}
	
	else
	{
		int n = vec1.size();
		
		for (int i = 0; i < n; i++)
		{
			if ( !isEqual_QryMember(vec1.at(n-1-i),vec2.at(n-1-i)))
			{
				return false;
			}
		}
	
	}

	return true;
}

//去除vector<QueryTuple *>中重复的QueryTuple

inline std::vector<QueryTuple*> TupleDistinct(std::vector<QueryTuple*>& set)
{
	vector<QueryTuple*> vec_set = set;				

	vector<QueryTuple*>::iterator iterator1, iterator2;
	
	for (iterator2 = vec_set.end()-1; iterator2 >= vec_set.begin()+1; iterator2--)
	{
//		cout<<"iterator2:"<<endl;
//		(*iterator2)->showTuple();

		vector<QueryMember*> vecMem2 = (*iterator2)->getMembers();
		
		for(iterator1 = iterator2-1; iterator1 >= vec_set.begin(); iterator1--)
		{	
//			cout<<"iterator1:"<<endl;
//			(*iterator1)->showTuple();

			vector<QueryMember*> vecMem1 = (*iterator1)->getMembers();
			
			if(isEqual_vecMember( vecMem1, vecMem2))
			{     
				vec_set.erase(iterator2);
				break;
			}
		}
		
	}
	return vec_set;
}


// DWSchemac中的Member转化为QueryMember

inline QueryMember* DwMemToQryMem(Member * dwMem,string dimName,string hieName)
{
	Level *pLevel = dwMem->getLevel();
	bool isAll = pLevel->isAllLevel();
	
	vector<Member *> memParentVec = dwMem ->getAllParents();
	vector<string> ancestorVal;
	vector<string> ancestorLevel;
	vector<Member*>::reverse_iterator memParentIterator;
	
	Level *pAncestorLevel;
	for(memParentIterator = memParentVec.rbegin();memParentIterator < memParentVec.rend();memParentIterator++)
	{
		ancestorVal.push_back((*memParentIterator)->getKey());
        pAncestorLevel = (*memParentIterator)->getLevel();
		ancestorLevel.push_back(pAncestorLevel->getName());;
	}
	
	string QueryMemberVal = dwMem->getKey();
	std::auto_ptr<QueryMember>ptr(new QueryMember);
	ptr->setVal(QueryMemberVal);
	ptr->setLevelName(pLevel->getName());
	ptr->setHierarchyName(hieName);
	ptr->setDimensionName(dimName);
	ptr->setAncestorVals(ancestorVal);
	ptr->setAncestorLevels(ancestorLevel);
	ptr->setIsAll(isAll);

	return(ptr.release());

}

//前序遍历，获得指定成员的所有后代(包括其本身)
inline void  getDescendants(Member * dwMem,string dimName,string hieName,vector<QueryTuple *> &QtupleVector)
{
	if(!dwMem) return;

	vector<QueryMember*> QmemVector;
	
	QueryMember* qryMember = DwMemToQryMem(dwMem,dimName,hieName);

	QmemVector.push_back(qryMember);
	std::auto_ptr<QueryTuple>pTuple(new QueryTuple(QmemVector));	
	QmemVector.pop_back();
	QtupleVector.push_back(pTuple.release());


	vector<Member *> childrenMem = dwMem->getChildrenMember();
	for(int i = 0; i< childrenMem.size();i++)
		getDescendants(childrenMem.at(i),dimName,hieName,QtupleVector);

	
}

// 判断mem1是否mem2的祖先，仅从表达式上判断，而且要求2个成员表达式必须严格完整
inline bool isAncestor(QueryMember *ancMem, QueryMember* decMem)
{
	vector<string> ancStr = ancMem->getMemberName();
	vector<string> decStr = decMem->getMemberName();

  // 判断mem2的前n个是否与mem1相同，若全相同，即说明mem2是mem1的后代
	for(int i=0; i< ancStr.size(); i++)
	{
		if(ancStr.at(i) != decStr.at(i)) return false;
	}

	return true;
}
#endif  