#pragma warning (disable: 4715 4786)
#include <algorithm>
#include <iostream>
#include "MdxParser/SetFunFactory.h"
#include "MdxParser/QueryMember.h"
#include "MdxParser/QueryTuple.h" 
#include "DWSchemac/XCube.h"
#include "DWSchemac/Dimension.h"
#include "DWSchemac/Hierarchy.h"
#include "DWSchemac/Member.h"
#include "DWSchemac/Level.h"
#include "DWSchemac/Measure.h"
#include "MdxParser/Common.h"
#include <assert.h>

using namespace std;

std::vector<QueryTuple*> SetFunFactory::funInstance(SetTypefirst _typefirst, 
												    std::vector<QueryTuple*>& set1,
												    std::vector<QueryTuple*>& set2)
{
	std::vector<QueryTuple*> vec; 
	std::vector<QueryMember*> mVec1;
	std::vector<QueryMember*> mVec3;
	switch(_typefirst)
	{
	case Crossjoin:
		{
			vector<QueryTuple*>::iterator theIterator1, theIterator2;
			for (theIterator1 = set1.begin(); theIterator1 < set1.end(); theIterator1++)
			{
				mVec1 = (*theIterator1)->getMembers();
				
				for (theIterator2 = set2.begin(); theIterator2 < set2.end(); theIterator2++)
				{
					mVec3 = mVec1;
					std::vector<QueryMember*> mVec2 = (*theIterator2)->getMembers();
					std::vector<QueryMember*>::iterator iter;
					for (iter = mVec2.begin(); iter < mVec2.end(); iter++)
					{
						QueryMember* p = *iter;
						mVec3.push_back(p);
					}					
					std::auto_ptr<QueryTuple> pt(new QueryTuple(mVec3));
					vec.push_back(pt.release());
				}

			}
		}
		break;
	case Union://暂时不考虑带ALL选项的
		vector<QueryTuple*>::iterator iterator1, iterator2;
		for (iterator2 = set2.begin(); iterator2 != set2.end(); iterator2++)
		{
			iterator1 = find(set1.begin(), set1.end(), (*iterator2));
			if (iterator1 == set1.end())
			{
                set1.push_back(*iterator2);
			}
		}
		vec = set1;
		//return vec;
		break;			 
	}
	return vec;
}


/*************************************************************
 * another kind of function that return a set
 ************************************************************/
std::vector<QueryTuple*> SetFunFactory::funInstance(XSchema* _pSch, 
										            std::string& _cubeName, 
									                SetTypesec _typesec, 
									                std::vector<std::string>& theVector)
{
    int size = theVector.size();
    XCube* pCube = _pSch->getCube(_cubeName);
	vector<QueryMember*> QmemVector;
	vector<QueryTuple*> QtupleVector;
	
	switch(_typesec)
	{
		//函数Members的处理对象
		//对于[Time].[Time].[1995].[Q1].[Month].Members
		//theVector中应依次存有string：Time, Time, 1995, Q1, Month
	case Members:
		if (size == 0 )
		{
			cout<<"error! please input query information..."<<endl;
		}
		else if (size == 1) //由于现在还不支持多个Hierarchy，所以size 为1、2结果是一样的
		{   
			if ((theVector.at(0) == "Measures")||(theVector.at(0) == "measures"))
			{
				//元数据现在还没有支持默认度量，先以第一个度量为默认的
				vector<Measure*> vecMea = pCube->getMeasures();
				vector<Measure*>::iterator meaIterator;
				if (!vecMea.empty())
				{
					for (meaIterator = vecMea.begin(); meaIterator < vecMea.end(); meaIterator++)
					{
						std::auto_ptr<QueryMember>pMem(new QueryMember);
	                    
						pMem->setHierarchyName("Measures");
						pMem->setLevelName("Measures");
					    pMem->setVal((*meaIterator)->getName());

						QmemVector.push_back(pMem.release());
						std::auto_ptr<QueryTuple>pTuple(new QueryTuple(QmemVector));
						QmemVector.pop_back();
						QtupleVector.push_back(pTuple.release());
					}
				}
 				
 				return QtupleVector;
			} 
			else
			{
				Dimension* pDim = pCube->getDimension(theVector.at(0));
				if (!pDim)
				{
					cout<<"error! wrong dimension name...."<<endl;
				} 
				else
				{
					//是取默认Hierarchy
					//获得的QueryMember应该是最细粒度的所有的QueryMember
					//所以在这里要作笛卡儿积（并不算纯粹的笛卡儿积），见for循环
					vector< Hierarchy* > hieVector = pDim->getHierarchies();
					Hierarchy* pHie = hieVector.at(0);//取第一个为默认Hierarchy
								//首先把Member从数据库中load出来
					pHie->LoadMembers();
					string hierarcyName = pHie->getName();
					vector<string> vecLevelName;
					vector< vector<string> > memNameInLevels;//用于存储每个Level上成员名字的vector
					vector<Level*> vecLevel = pHie->getLeveles();
					int levelSize = vecLevel.size();
					Level* pLevel = vecLevel.at(levelSize-1);
					string levelName = pLevel->getName();
					vector<Member*> vecMem = pLevel->getMembers();
					vector<Member*>::iterator memIterator;
					for (memIterator = vecMem.begin(); memIterator < vecMem.end(); memIterator++)
					{
						string memberVal = (*memIterator)->getKey();
						vector<string> vecAncestorVal;
						vector<string> vecAncestorLevel;
						vector<Member*> vecParentMems;
						vector<Member*>::iterator pMemIterator;
						vecParentMems = (*memIterator)->getAllParents();
						for (pMemIterator = vecParentMems.begin(); pMemIterator < vecParentMems.end(); pMemIterator++)
						{
							string parentVal = (*pMemIterator)->getKey();
							Level* pLevel = (*pMemIterator)->getLevel();
							string parentLevel = pLevel->getName();
							vecAncestorVal.push_back(parentVal);
							vecAncestorLevel.push_back(parentLevel);
						}
						std::auto_ptr<QueryMember>p(new QueryMember);
						p->setHierarchyName(hierarcyName);
						p->setAncestorVals(vecAncestorVal);
						p->setAncestorLevels(vecAncestorLevel);
						p->setVal(memberVal);
						p->setLevelName(levelName);
						QmemVector.push_back(p.release());
					    std::auto_ptr<QueryTuple>pTuple(new QueryTuple(QmemVector));
					    QmemVector.pop_back();
					    QtupleVector.push_back(pTuple.release());
					}
				
				    pHie->CleanMembers();

 				    return QtupleVector;
				}
			}
		}
		else if (size == 2)
		{   
			string dimName = theVector.at(0);

			Dimension* pDim = pCube->getDimension(dimName);
			if (pDim == NULL)
			{
				cout<<"null point to dimension"<<endl;
			}
			Hierarchy* pHie = pDim->getHierarchy(theVector.at(1));
			if (pHie == NULL)
			{
				cout<<"null point to Hierarchy"<<endl;
			}
			//首先把Member从数据库中load出来
			pHie->LoadMembers();
			string hierarcyName = pHie->getName();
			vector<string> vecLevelName;
			vector< vector<string> > memNameInLevels;//用于存储每个Level上成员名字的vector
			vector<Level*> vecLevel = pHie->getLeveles();
			int levelSize = vecLevel.size();
			Level* pLevel = vecLevel.at(levelSize-1);
			string levelName = pLevel->getName();
			vector<Member*> vecMem = pLevel->getMembers();
			vector<Member*>::iterator memIterator;
			for (memIterator = vecMem.begin(); memIterator < vecMem.end(); memIterator++)
			{
				string memberVal = (*memIterator)->getKey();
				vector<string> vecAncestorVal;
				vector<string> vecAncestorLevel;
				vector<Member*> vecParentMems;
				vector<Member*>::iterator pMemIterator;
				vecParentMems = (*memIterator)->getAllParents();
                for (pMemIterator = vecParentMems.begin(); pMemIterator < vecParentMems.end(); pMemIterator++)
                {
					string parentVal = (*pMemIterator)->getKey();
					Level* pLevel = (*pMemIterator)->getLevel();
					string parentLevel = pLevel->getName();
					vecAncestorVal.push_back(parentVal);
					vecAncestorLevel.push_back(parentLevel);
                }
				std::auto_ptr<QueryMember>p(new QueryMember);
				p->setHierarchyName(hierarcyName);
				p->setAncestorVals(vecAncestorVal);
				p->setAncestorLevels(vecAncestorLevel);
				p->setVal(memberVal);
				p->setLevelName(levelName);
				QmemVector.push_back(p.release());
			    std::auto_ptr<QueryTuple>pTuple(new QueryTuple(QmemVector));
				QmemVector.pop_back();
				QtupleVector.push_back(pTuple.release());
			}
				
			pHie->CleanMembers();

 			return QtupleVector;
		} 
		else if(size == 3)
		{
			Dimension* pDim = pCube->getDimension(theVector.at(0));
			Hierarchy* pHie = pDim->getHierarchy(theVector.at(1));
			//首先把Member从数据库中load出来
			pHie->LoadMembers();
			Level* pLevel = pHie->getLevel(theVector.at(2));

			vector<Member*> memVector1;
			memVector1 = pLevel->getMembers();
			if (memVector1.empty())
			{
				cout<<"empty member vector,do not get the members from database"<<endl;
			} 
			else{
				vector<Member*>::iterator theIterator;
				for (theIterator = memVector1.begin(); theIterator < memVector1.end(); theIterator++)
				{
					if (*theIterator == NULL)
					{
						cout<<"do not get the members from the database!"<<endl;
					}
					string QueryMemberVal = (*theIterator)->getKey();
					std::auto_ptr<QueryMember>pMem(new QueryMember);
					pMem->setVal(QueryMemberVal);
					pMem->setLevelName(theVector.at(2));
					pMem->setHierarchyName(theVector.at(1));
					QmemVector.push_back(pMem.release());
			        std::auto_ptr<QueryTuple>pTuple(new QueryTuple(QmemVector));
					QmemVector.pop_back();
					QtupleVector.push_back(pTuple.release());
				}
				
			    pHie->CleanMembers();

 			    return QtupleVector;
			}	
		}
		else//出现成员等于或多于一个的情况 eg. [Time].[Time].[1995].[Q1].[Month].Members
		{
             Dimension* pDim = pCube->getDimension(theVector.at(0));
			 Hierarchy* pHie = pDim->getHierarchy(theVector.at(1));
			 //首先把Member从数据库中load出来
			 pHie->LoadMembers();
			 Level* pLevel = pHie->getLevel(theVector.at(size-1));
			 vector<Member*> memVector = pLevel->getMembers();
			 vector<Member*>::iterator theIterator;
			 for (theIterator = memVector.begin(); theIterator < memVector.end(); theIterator++)
			{
				string QueryMemberVal = (*theIterator)->getKey();
                std::auto_ptr<QueryMember>pMem(new QueryMember);
				pMem->setVal(QueryMemberVal);
				pMem->setLevelName(theVector.at(size));
				pMem->setHierarchyName(theVector.at(1));
				vector<string> ancestorVals;				
                vector<string> ancestorLevles;
				for (int i = 2; i < size-1; i++)
				{
					vector<Level*> levelVec;
					levelVec = pHie->getLeveles();
					ancestorVals.push_back(theVector.at(i));
					Level* p = levelVec.at(i);
					ancestorLevles.push_back(p->getName());
				}
				pMem->setAncestorVals(ancestorVals);
				pMem->setAncestorLevels(ancestorLevles);
				QmemVector.push_back(pMem.release());
                std::auto_ptr<QueryTuple>pTuple(new QueryTuple(QmemVector));
				QmemVector.pop_back();
				QtupleVector.push_back(pTuple.release());
			}
				
			pHie->CleanMembers();

 			return QtupleVector;
		}
	break;
 
	//函数AllMembers,参考SQL Server联机丛书
	//返回包含指定维度或级别的所有成员的集合，包括计算成员。
	//注：暂时不考虑计算成员的处理,此时功能和Members功能差不多
	case AllMembers:
		if (size == 0 )
		{
			cout<<"error! please input the query information!"<<endl;
		}
		else if (size == 1)
		{
			//取得默认Hierarchy
			//暂时只支持一个Hierarchy，即和维度名相同
			string dimensionName = theVector.at(0);
			
            string hierarchyName = dimensionName;
			std::auto_ptr<QueryMember>pMem(new QueryMember);
			pMem->setVal("All");
			pMem->setHierarchyName(hierarchyName);
			pMem->setLevelName("All");
			QmemVector.push_back(pMem.release());
            std::auto_ptr<QueryTuple>pTuple(new QueryTuple(QmemVector));
		    QmemVector.pop_back();
			QtupleVector.push_back(pTuple.release());
				
 			return QtupleVector;
		} 	
		else if(size == 2)//[Time].[Time].AllMembers
		{
			string dimensionName = theVector.at(0);
            Dimension* pDim = pCube->getDimension(dimensionName);
			Hierarchy* pHie = pDim->getHierarchy(theVector.at(1));
			std::auto_ptr<QueryMember>pMem(new QueryMember);
			pMem->setHierarchyName(pHie->getName());
			pMem->setLevelName("All");
			pMem->setVal("All");
			QmemVector.push_back(pMem.release());
			std::auto_ptr<QueryTuple>pTuple(new QueryTuple(QmemVector));
			QmemVector.pop_back();
			QtupleVector.push_back(pTuple.release());

 			return QtupleVector;
		}
		else //[Time].[Time].[Year].AllMembers
		{
            Dimension* pDim = pCube->getDimension(theVector.at(0));
			 Hierarchy* pHie = pDim->getHierarchy(theVector.at(1));
			 Level* pLevel = pHie->getLevel(theVector.at(size-1));
			 vector<Member*> memVector = pLevel->getMembers();
			 vector<Member*>::iterator theIterator;
			 for (theIterator = memVector.begin(); theIterator < memVector.end(); theIterator++)
			 {
				string QueryMemberVal = (*theIterator)->getKey();
                std::auto_ptr<QueryMember>pMem(new QueryMember);
				pMem->setVal(QueryMemberVal);
				pMem->setLevelName(theVector.at(size));
				pMem->setHierarchyName(theVector.at(1));
				vector<string> ancestorVals;				
                vector<string> ancestorLevles;
				for (int i = 2; i < size-1; i++)
				{
					vector<Level*> levelVec;
					levelVec = pHie->getLeveles();
					ancestorVals.push_back(theVector.at(i));
					Level* p = levelVec.at(i);
					ancestorLevles.push_back(p->getName());
				}
				pMem->setAncestorVals(ancestorVals);
				pMem->setAncestorLevels(ancestorLevles);
				QmemVector.push_back(pMem.release());
			    std::auto_ptr<QueryTuple>pTuple(new QueryTuple(QmemVector));
				QmemVector.pop_back();
				QtupleVector.push_back(pTuple.release());
			}
				
			//pHie->CleanMembers();没有加载过member

 			return QtupleVector;
		}
	break;
	case Children:
		
		//注：JPivot里面是不可能出现这种情况的
		//因为一旦出现，JPivot会自动转化成加一个CurrentMember函数
		//如：[Time].Children会自动转变成[Time].CurrentMember.Children
		string dimName = "";
		string hieName = "";
		bool isall = false;
		if (size == 1)
		{
			cout<<"error! invalid using of Children"<<endl;

		} 
		else if(size == 2)
		{
			Dimension* pDim =NULL;
            Hierarchy* pHie = NULL;
			
			if (isDimHie(theVector.at(0)))
			{
				vector<string> temp = distinct(theVector.at(0));
				dimName = temp.at(0);
				pDim = pCube->getDimension(dimName);
				assert(pDim);
				hieName = temp.at(1);
				Hierarchy* pHie = pDim->getHierarchy(hieName);
				assert(pHie);
			}
			else
			{
				dimName = theVector.at(0);
 				pDim = pCube->getDimension(theVector.at(0));
				assert(pDim);
				pHie = pDim->getDefaultHierarchy();
				hieName = pHie->getName();
				assert(pHie);
			}
			assert(pHie);
			pHie->LoadMembers();
			
			
               		
			vector<Level*> levelVec = pHie->getLeveles();
			Level* pLevel1 = levelVec.at(0);//父member所在的level
			assert(pLevel1);
			string ancestorVal = theVector.at(1);
			string ancestorLevel = pLevel1->getName();
            vector<string> valVec;
			vector<string> theVec;
			valVec.push_back(ancestorVal);
            theVec.push_back(ancestorLevel);

			Level* pLevel2 = levelVec.at(1);//查询的member所在的level
			string QueryMemberLevel = pLevel2->getName();
//  		cout<<"value:"<<theVector.at(1)<<endl;
  		Member* pm = pLevel1->getMember(theVector.at(1),NULL);////////////////////////////////
			vector<Member*> memVec = pm->getChildrenMember();
		//cout<<QueryMemberLevel<<"  "<<memVec.size()<<endl;
			vector<Member*>::iterator memIterator;
			for (memIterator = memVec.begin(); memIterator < memVec.end(); memIterator++)
			{
				string QueryMemberVal = (*memIterator)->getKey();
				
                std::auto_ptr<QueryMember>p(new QueryMember(dimName,hieName,QueryMemberLevel,QueryMemberVal,valVec,theVec,isall));
                QmemVector.push_back(p.release());
				std::auto_ptr<QueryTuple>pTuple(new QueryTuple(QmemVector));
				QmemVector.pop_back();
				QtupleVector.push_back(pTuple.release());
			}
			pHie->CleanMembers();
 			
 			return QtupleVector;               
		}

		else if (size >= 2)
		{
			Dimension* pDim = NULL;
			Hierarchy* pHie = NULL;
            if (isDimHie(theVector.at(0)))
			{
				vector<string> temp = distinct(theVector.at(0));
				dimName = temp.at(0);
			    pDim = pCube->getDimension(temp.at(0));
				assert(pDim);
				hieName = temp.at(1);
				pHie = pDim->getHierarchy(temp.at(1));
				assert(pHie);
			}
            else
			{
				dimName = theVector.at(0);

				pDim = pCube->getDimension(theVector.at(0));
				assert(pDim);
				
				pHie = pDim->getDefaultHierarchy();
			}
            assert(pHie);
			string hieName = pHie->getName();
			pHie->LoadMembers();
			
			vector<Level*> levelVec = pHie->getLeveles();
			//children members'level
			Level* pLevel = levelVec.at(size-1);
		
			vector<Level*> parentLevels;
            vector<Level*>::iterator levelIterator;

            parentLevels.assign(levelVec.begin(),levelVec.begin()+size-1);

			vector<string> ancestorVal;
			vector<string> ancestorLevel;
			for (int i = 1; i < size; i++)
			{

				ancestorVal.push_back(theVector.at(i));
			}

			for (levelIterator = parentLevels.begin(); levelIterator < parentLevels.end(); levelIterator++)
			{
				string ancestorLevelName = (*levelIterator)->getName();
				ancestorLevel.push_back(ancestorLevelName);
			} 
		
            string firstparentMemVal = theVector.at(1);

			Member* firstparentMem = parentLevels.at(0)->getMember(firstparentMemVal, NULL);

            Member* lastParentMem = NULL; 
			if (size == 2)
			{
				assert(firstparentMem);
                lastParentMem = firstparentMem; 
			}
		
			else
			{
				for(int n = 2; n < size; n++)
				{
					//cout<<"theVector.at(n)"<<theVector.at(n)<<endl;
					firstparentMem = parentLevels.at(n-1)->getMember(theVector.at(n), firstparentMem);
					assert(firstparentMem);
				}
			}				
			lastParentMem = firstparentMem;						 
	        assert(lastParentMem);
			vector<Member*> memVec = lastParentMem->getChildrenMember();

			vector<Member*>::iterator memIterator;
			for (memIterator = memVec.begin(); memIterator < memVec.end(); memIterator++)
			{
				string QueryMemberVal = (*memIterator)->getKey();
				std::auto_ptr<QueryMember>ptr(new QueryMember);
				ptr->setVal(QueryMemberVal);
				ptr->setLevelName(pLevel->getName());
				ptr->setHierarchyName(hieName);
				ptr->setDimensionName(dimName);
				ptr->setAncestorVals(ancestorVal);
				ptr->setAncestorLevels(ancestorLevel);
				ptr->setIsAll(isall);
				QmemVector.push_back(ptr.release());
				std::auto_ptr<QueryTuple>pTuple(new QueryTuple(QmemVector));
				QmemVector.pop_back();
				QtupleVector.push_back(pTuple.release());
			}
		
			pHie->CleanMembers();

 			return QtupleVector;
 		}
		break;
	    //下一个函数起点
	}
}

/*************************************************************
 * another kind of function that deal with one set 
 * and returns a set;
 ************************************************************/
 std::vector<QueryTuple*> SetFunFactory::funInstance(SetTypethird _typethird, std::vector<QueryTuple*>& set)
{
	switch(_typethird)
	{
	//对QueryTuple采用基数排序
	case Hierarchize:
		{
			int QueryTuplesize = set.size();
			QueryTuple* p = set.at(0);
			vector<QueryMember*> vecMem = p->getMembers();
			int size = vecMem.size();
			//用基数排序,从最后一个维开始排
			while (size > 0)
			{
				for (int m = 0; m < QueryTuplesize; m++)
				{
					for(int n = 0; n < QueryTuplesize-1-m; n++)
					{
						vector<QueryMember*> vec1 = set[n]->getMembers();
						QueryMember *p1 = vec1.at(size-1);
						string val1 = p1->getVal();
						vector<string> parent1 = p1->getAncestorVals();

						vector<string>::iterator strIter1;
						//allString1是把一个member的所有父亲的val和自己的val组成一个串
						string allString1;
						if(parent1.size()>0)
						{
							for (strIter1 = parent1.begin(); strIter1 != parent1.end(); strIter1++)
							{
								allString1.append(*strIter1);

							}
						}
						allString1.append(val1);

						vector<QueryMember*> vec2 =set[n+1]->getMembers();
						QueryMember *p2 = vec2.at(size-1);
						string val2 = p2->getVal();
						vector<string> parent2 = p2->getAncestorVals();
                       
						vector<string>::iterator strIter2;
						//allString2是把一个member的所有父亲的val和自己的val组成一个串
						string allString2;
                        for (strIter2 = parent2.begin(); strIter2 != parent2.end(); strIter2++)
						{
							allString2.append(*strIter2);
						}
						allString2.append(val2);
							
						if (strcmpi(allString1.c_str(), allString2.c_str()) == 1 )
						{

							QueryTuple* temp = set[n+1];
							set[n+1] = set[n];
							set[n] = temp;

						}
					}
				}

				size--;
			}

			return set;
			break;
		}
	case Distinct:
		break;
	}
}