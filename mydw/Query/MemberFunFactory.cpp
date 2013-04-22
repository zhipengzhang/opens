#include "DWSchemac/XCube.h"
#include "DWSchemac/Dimension.h"
#include "DWSchemac/Hierarchy.h"
#include "DWSchemac/Member.h"
#include "DWSchemac/Level.h"
#include "DWSchemac/Measure.h"
#include "MdxParser/MemberFunFactory.h"
#include "MdxParser/Common.h"
 
using namespace std;
using namespace dwschemac;
 
QueryMember* MemberFunFactory::funInstance(XSchema* _pSch, string& _cubeName, MemType _type, std::vector<std::string>& theVector)
{
	std::auto_ptr<QueryMember>pQmem(new QueryMember);
	int size = theVector.size();
	XCube* pCube = _pSch->getCube(_cubeName);
	switch(_type)
	{
	case PrevMember:
        if (size == 2)//Time.1997.PrevMember
        {
			Dimension* pDim = pCube->getDimension(theVector.at(0));
			if (!pDim)
			{
				cout<<"invalid dimension name"<<endl;
			} 
			else
			{
				vector<Hierarchy*> hieVec = pDim->getHierarchies();
				//取第一个为默认hierarchy
				if (hieVec.empty())
				{
					cout<<"can not get valid hierarchy"<<endl;
				} 
				else
				{
					Hierarchy* pHie = hieVec.at(0);
					pHie->LoadMembers();
					string hieName = pHie->getName(); 
					vector<Level*> levelVec = pHie->getLeveles();
					string levelName = levelVec.at(0)->getName();
					Member* pMem = levelVec.at(0)->getMember(theVector.at(1), 0);
					if (!pMem)
					{
						cout<<"invalid member'value in the top level when using function PrevMember."<<endl;
					} 
					else
					{
						vector<Member*> vecMem = levelVec.at(0)->getMembers();
						vector<Member*>::iterator theIterator;
						for (theIterator = vecMem.begin(); theIterator < vecMem.end(); theIterator++)
						{
							if (*theIterator == pMem)
							{
								pMem = *(theIterator-1);
							}
						}
					}
					string memVal = pMem->getKey();
					pQmem->setVal(memVal);
					pQmem->setLevelName(levelName);
					pQmem->setHierarchyName(hieName);
					pHie->CleanMembers();
				}
			}
        } 
        else if(size == 3)
        {
			Dimension* pDim = pCube->getDimension(theVector.at(0));
			if (!pDim)
			{
				cout<<"invalid dimension name"<<endl;
			} 
			else
			{
				Hierarchy* pHie = pDim->getHierarchy(theVector.at(1));
				pHie->LoadMembers();
				if (!pHie)
				{
					cout<<"invalid hierarchy name when using function PrevMember."<<endl;
				} 
				else
				{
					string strHie = pHie->getName();
					
					vector<Level*> levelVectemp = pHie->getLeveles();

					Member* pMem = levelVectemp.at(0)->getMember(theVector.at(2), 0);

					if (pMem == 0)
					{
						cout<<"没生成Member"<<endl;
					}

					Level* plevel = levelVectemp.at(0);//指向PrevMember所指的Level
                    vector<Member*> vecMem = plevel->getMembers();
					vector<Member*>::iterator theIterator;
					for (theIterator = vecMem.begin(); theIterator < vecMem.end(); theIterator++)
					{

						if (*theIterator == pMem)
						{
							pMem = *(theIterator-1);
						}
					}
					string LevelName = plevel->getName();
                    pQmem->setVal(pMem->getKey());
					pQmem->setLevelName(LevelName);
					pQmem->setHierarchyName(strHie);
					pHie->CleanMembers();
				}
			}
        }
		else if(size > 3)
        {
			Dimension* pDim = pCube->getDimension(theVector.at(0));
			
			if (!pDim)
			{
				cout<<"invalid dimension name"<<endl;
			} 
			else
			{
				Hierarchy* pHie = pDim->getHierarchy(theVector.at(1));  
				if (!pHie)
				{
					cout<<"invalid hierarchy name when using function PrevMember."<<endl;
				} 
				else
				{
					pHie->LoadMembers();
					string strHie = pHie->getName();
					vector<string> ancestorVal;
					vector<string> ancestorLevel;
					vector<Level*> levelVectemp = pHie->getLeveles();
					vector<Level*> levelVec1;
					vector<Level*>::iterator levelIterator;
					levelVec1.assign(levelVectemp.begin(),levelVectemp.begin()+size-2);
					for (levelIterator = levelVec1.begin(); levelIterator < levelVec1.end()-1; levelIterator++)
					{
						string strAncestorLevel = (*levelIterator)->getName();
					
						ancestorLevel.push_back(strAncestorLevel);
					}

					ancestorVal.assign(theVector.begin()+2, theVector.end()-1);

					Level* plevel1 = levelVectemp.at(0);
					
					Member* pMem = plevel1->getMember(theVector.at(2), 0);
					assert(pMem);

					
					for (int i = 4; i < size+1; i++)
					{
						Member* temp = levelVec1.at(i-3)->getMember(theVector.at(i-1), pMem); 
						pMem = temp;
					}
				
					Level* plevel = *(levelVec1.end()-1);//指向PrevMember所指的Level
					assert(plevel);
                    vector<Member*> vecMem = plevel->getMembers();
					vector<Member*>::iterator theIterator;
					for (theIterator = vecMem.begin(); theIterator < vecMem.end(); theIterator++)
					{
						if (*theIterator == pMem)
						{
							pMem = *(theIterator-1);
						}
					}
					string LevelName = plevel->getName();
                    pQmem->setVal(pMem->getKey());
					pQmem->setLevelName(LevelName);
					pQmem->setHierarchyName(strHie);
					pQmem->setAncestorVals(ancestorVal);
					pQmem->setAncestorLevels(ancestorLevel);
					pHie->CleanMembers();
				}
			}
        }
		else
		{
			//size ==1 的情况也存在，是在出现计算成员时，出现在WHIT子句
			//如：Time.PrevMember,这时一般时吧这个替换WHERE子句中出现的Time维的成员
			//如Time.1998,相当于Time.1997或Time.1998.PrevMember
			//暂时先不考虑
			cout<<"incorrect usage of function PrevMember."<<endl;
		}
		break;
		//[Time].[Time].[1995].FirstChild
		//vector中的值应依次为：Time,Time,1995
		//对于FoodMart，返回[Time].[Time].[1995].[January]
 	case FirstChild: 
		if (size == 1)
		{
			Dimension* pDim = pCube->getDimension(theVector.at(0));
			if (!pDim)
			{
				cout<<"invalid dimension name when using function FirstChild!"<<endl;
			} 
			else
			{
				vector<Hierarchy*> hieVec = pDim->getHierarchies();
				//取第一个为默认的hierarchy
				Hierarchy* pHie = hieVec.at(0);
				if (!pHie)
				{
					cout<<"can not get default hierarchy when using function FirstChild!"<<endl;
				} 
				else
				{
					pHie->LoadMembers();
					string hieName = pHie->getName();
					vector<Level*> levelVec = pHie->getLeveles();
					//取第一个LEVEL作为默认的Level
					Level* pLevel = levelVec.at(0);
					if (!pLevel)
					{
						cout<<"can not get default level when using function FirstChild!"<<endl;
					} 
					else
					{
						string levelName = pLevel->getName();
						vector<Member*> memVec = pLevel->getMembers();
						Member* pMem = memVec.at(0);
						string memName = pMem->getKey();
						pQmem->setVal(memName);
						pQmem->setLevelName(levelName);
						pQmem->setHierarchyName(hieName);
						pHie->CleanMembers();
					}
				}
			}
		} 
		else if(size == 2)
		{
			Dimension* pDim = pCube->getDimension(theVector.at(0));
			if (!pDim)
			{
				cout<<"invalid dimension name when using function FirstChild!"<<endl;
			} 
			else
			{
				//vector<Hierarchy*> hieVec = pDim->getHierarchies();
				
				Hierarchy* pHie = pDim->getHierarchy(theVector.at(1));
				if (!pHie)
				{
					cout<<"can not get default hierarchy when using function FirstChild!"<<endl;
				} 
				else
				{
					pHie->LoadMembers();
					string hieName = pHie->getName();
					vector<Level*> levelVec = pHie->getLeveles();
					//取第一个LEVEL作为默认的Level
					Level* pLevel = levelVec.at(0);
					if (!pLevel)
					{
						cout<<"can not get default level when using function FirstChild!"<<endl;
					} 
					else
					{
						string levelName = pLevel->getName();
						vector<Member*> memVec = pLevel->getMembers();
						Member* pMem = memVec.at(0);
						string memName = pMem->getKey();
						pQmem->setVal(memName);
						pQmem->setLevelName(levelName);
						pQmem->setHierarchyName(hieName);
						pHie->CleanMembers();
					}
				}
			}
		}
		else if (size > 2)
		{
			Dimension* pDim = pCube->getDimension(theVector.at(0));
			if (!pDim)
			{
				cout<<"invalid dimension name when using function FirstChild!"<<endl;
			} 
			else
			{
				//vector<Hierarchy*> hieVec = pDim->getHierarchies();
				
				Hierarchy* pHie = pDim->getHierarchy(theVector.at(1));
				if (!pHie)
				{
					cout<<"can not get hierarchy when using function FirstChild!"<<endl;
				} 
				else
				{
					pHie->LoadMembers();
					string hieName = pHie->getName();
					vector<Level*> levelVec = pHie->getLeveles();
					vector<string> anscestorVals;
					vector<string> anscestorLevels;
					vector<Level*> anscestorLevelVec;
					vector<Level*>::iterator theIterator;
					anscestorLevelVec.assign(levelVec.begin(), levelVec.begin()+size-2);
					for (theIterator = anscestorLevelVec.begin(); theIterator < anscestorLevelVec.end(); theIterator++)
					{
						Level* pLevel = (*theIterator);
						string str = pLevel->getName();
						anscestorLevels.push_back(str);
					}
					anscestorVals.assign(theVector.begin()+2, theVector.end());
					Level* mempLevel = levelVec.at(size-2);//level of the first child
					vector<Member*> memVec = mempLevel->getMembers();
                    Member* pMem = memVec.at(0);
					string memVal = pMem->getKey();
					string levelName = mempLevel->getName();
					pQmem->setVal(memVal);
					pQmem->setLevelName(levelName);
					pQmem->setHierarchyName(hieName);
					pQmem->setAncestorVals(anscestorVals);
					pQmem->setAncestorLevels(anscestorLevels);
					pHie->CleanMembers();
				}
			}
		}
 		break;
// 	case NextMember:
// 		break;
 	case LastChild:
        if (size == 1)
		{
			Dimension* pDim = pCube->getDimension(theVector.at(0));
			if (!pDim)
			{
				cout<<"invalid dimension name when using function FirstChild!"<<endl;
			} 
			else
			{
				vector<Hierarchy*> hieVec = pDim->getHierarchies();
				//取第一个为默认的hierarchy
				Hierarchy* pHie = hieVec.at(0);
				if (!pHie)
				{
					cout<<"can not get default hierarchy when using function FirstChild!"<<endl;
				} 
				else
				{
					pHie->LoadMembers();
					string hieName = pHie->getName();
					vector<Level*> levelVec = pHie->getLeveles();
					//取第一个LEVEL作为默认的Level
					Level* pLevel = levelVec.at(0);
					if (!pLevel)
					{
						cout<<"can not get default level when using function FirstChild!"<<endl;
					} 
					else
					{
						string levelName = pLevel->getName();
						vector<Member*> memVec = pLevel->getMembers();
						int size1 = memVec.size();
						Member* pMem = memVec.at(size1 - 1);
						string memName = pMem->getKey();
						pQmem->setVal(memName);
						pQmem->setLevelName(levelName);
						pQmem->setHierarchyName(hieName);
						pHie->CleanMembers();
					}
				}
			}
		} 
		else if(size == 2)
		{
			Dimension* pDim = pCube->getDimension(theVector.at(0));
			if (!pDim)
			{
				cout<<"invalid dimension name when using function FirstChild!"<<endl;
			} 
			else
			{
				//vector<Hierarchy*> hieVec = pDim->getHierarchies();
				
				Hierarchy* pHie = pDim->getHierarchy(theVector.at(1));
				if (!pHie)
				{
					cout<<"can not get default hierarchy when using function FirstChild!"<<endl;
				} 
				else
				{
					pHie->LoadMembers();
					string hieName = pHie->getName();
					vector<Level*> levelVec = pHie->getLeveles();
					//取第一个LEVEL作为默认的Level
					Level* pLevel = levelVec.at(0);
					if (!pLevel)
					{
						cout<<"can not get default level when using function FirstChild!"<<endl;
					} 
					else
					{
						string levelName = pLevel->getName();
						vector<Member*> memVec = pLevel->getMembers();
						int size1 = memVec.size();
						Member* pMem = memVec.at(size1 - 1);
						string memName = pMem->getKey();
						pQmem->setVal(memName);
						pQmem->setLevelName(levelName);
						pQmem->setHierarchyName(hieName);
						pHie->CleanMembers();
					}
				}
			}
		}
		else if (size > 2)
		{
			Dimension* pDim = pCube->getDimension(theVector.at(0));
			if (!pDim)
			{
				cout<<"invalid dimension name when using function FirstChild!"<<endl;
			} 
			else
			{
				Hierarchy* pHie = pDim->getHierarchy(theVector.at(1));
				if (!pHie)
				{
					cout<<"can not get hierarchy when using function FirstChild!"<<endl;
				} 
				else
				{
					pHie->LoadMembers();
					
					string hieName = pHie->getName();
					vector<Level*> levelVec = pHie->getLeveles();
					vector<string> ancestorVals;
					vector<string> ancestorLevels;
					vector<Level*> ancestorLevelVec;
					vector<Level*>::iterator theIterator;
					ancestorLevelVec.assign(levelVec.begin(), levelVec.begin()+size-2);
                    ancestorVals.assign(theVector.begin()+2, theVector.end());
					int i = 0;
					Member* temp = ancestorLevelVec.at(0)->getMember(ancestorVals.at(i), 0);
					string str1 = ancestorLevelVec.at(0)->getName();
					ancestorLevels.push_back(str1);
					if (size > 3)
					{
						/*cout<<"OK?"<<endl;*/
						for (theIterator = ancestorLevelVec.begin()+1; theIterator < ancestorLevelVec.end(); theIterator++)
						{
							Level* pLevel = (*theIterator);
							string str2 = pLevel->getName();
							ancestorLevels.push_back(str2);
							temp = pLevel->getMember(ancestorVals.at(i+1), temp);
							i++;
						}
					}
					
					Level* mempLevel = levelVec.at(size-2);//level of the first child
					vector<Member*> memVec = temp->getChildrenMember();
					int size1 = memVec.size();
                    Member* pMem = memVec.at(size1 - 1);
					string memVal = pMem->getKey();
					string levelName = mempLevel->getName();
					pQmem->setVal(memVal);
					pQmem->setLevelName(levelName);
					pQmem->setHierarchyName(hieName);
					pQmem->setAncestorVals(ancestorVals);
					pQmem->setAncestorLevels(ancestorLevels);
					pHie->CleanMembers();
				}
			}
		}
		break;
	case CurrentMembers:
		if (theVector.size() == 1)
		{
			string temp = theVector.at(0);
			if (isDimHie(temp))
			{
				vector<string> tempVec = distinct(temp);
				string dimName = tempVec.at(0);
				string hieName = tempVec.at(1);
				Dimension* pDim = pCube->getDimension(dimName);
				assert(pDim);
				Hierarchy* pHie = pDim->getHierarchy(hieName);
				assert(pHie);
				
				pHie->LoadMembers();

				bool isall = false;

				if (pHie->hasAll())
				{
                   isall = true;
				}
				
				auto_ptr<Member> pMem = pHie->getDefaultMember();
				assert(pMem.release());
				vector<Level*> vec = pHie->getLeveles();
				Level* p = vec.at(0);
				assert(p);
				string levelName = p->getName();
				string val = pMem->getKey();
				vector<string> ancestorVals, ancestorLevels;
				pQmem->setDimensionName(dimName);
				pQmem->setHierarchyName(hieName);
				pQmem->setLevelName(levelName);
				pQmem->setVal(val);
				pQmem->setAncestorLevels(ancestorLevels);
				pQmem->setAncestorVals(ancestorVals);
				pQmem->setIsAll(isall);
			} 
			else
			{
				string dimName = temp;
				
				Dimension* pDim = pCube->getDimension(dimName);
				assert(pDim);

				Hierarchy* pHie = pDim->getDefaultHierarchy();
				assert(pHie);
				string hieName = pHie->getName();
				
				pHie->LoadMembers();

				bool isall = false;

				if (pHie->hasAll())
				{
                   isall = true;
				}
				
				auto_ptr<Member> pMem = pHie->getDefaultMember();
				assert(pMem.release());
				vector<Level*> vec = pHie->getLeveles();
				Level* p = vec.at(0);
				assert(p);
				string levelName = p->getName();
				string val = pMem->getKey();
				vector<string> ancestorVals, ancestorLevels;
				pQmem->setDimensionName(dimName);
				pQmem->setHierarchyName(hieName);
				pQmem->setLevelName(levelName);
				pQmem->setVal(val);
				pQmem->setAncestorLevels(ancestorLevels);
				pQmem->setAncestorVals(ancestorVals);
				pQmem->setIsAll(isall);
			}			
		}
	}
	return pQmem.release();
}