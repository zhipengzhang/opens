                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
                                                               
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
 *MDX���֧�ֶ��Hierarchy��һ������£�Hierarchy
 *��Ĭ�ϵģ���MDX��������ǲ������Hierarchy����Ϣ��
 *��Ҳ����ָ���ǲ���Ĭ�ϵ�Hierarchy���в�ѯ����ʱ��
 *Hierarchy�����ָ�����Dimension���ֺ�
 *�磬Ĭ������£�[Time].[1997],Time ��ά�����֣�1997��
 *��Ա����Hierarchy�����ǿ������ģ�Ĭ�ϵģ�������ָ��
 *��һ����Ĭ�ϵ�Hierarchy���в�ѯ����[Time.***].[1997]
 *��ʱ��***��Ϊָ����Hierarchy;
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

//�ж�����ͬsize��vector<QueryMember*>��ǰn��QueryMember�Ƿ���ͬ,n�ķ�ΧΪ[0,vec1.size()-1]    // ǰn���� add by eason
//0��ʾ�Ե�һ�н��д���ǰ��û���У���Ϊ�档
//��Ҫ����hirarchize�����Ĵ�����
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
				//�ú����д�Ӧ�������&&��Ϊ||   add bu eason
				eql = false;
				break;                      // add by eason
			}
		}
		return eql;
	}
}


//�ж�����QueryMember�Ƿ���ͬ
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



//�ж�����vector<QueryMember*>�Ƿ���ͬ

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

//ȥ��vector<QueryTuple *>���ظ���QueryTuple

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


// DWSchemac�е�Memberת��ΪQueryMember

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

//ǰ����������ָ����Ա�����к��(�����䱾��)
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

// �ж�mem1�Ƿ�mem2�����ȣ����ӱ��ʽ���жϣ�����Ҫ��2����Ա���ʽ�����ϸ�����
inline bool isAncestor(QueryMember *ancMem, QueryMember* decMem)
{
	vector<string> ancStr = ancMem->getMemberName();
	vector<string> decStr = decMem->getMemberName();

  // �ж�mem2��ǰn���Ƿ���mem1��ͬ����ȫ��ͬ����˵��mem2��mem1�ĺ��
	for(int i=0; i< ancStr.size(); i++)
	{
		if(ancStr.at(i) != decStr.at(i)) return false;
	}

	return true;
}
#endif  