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
												    std::vector<QueryTuple*>& set2,
													FunParam *param)
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

	case Union:  
		{
			bool all = false;

			if( strcmp(param->getStrParam(),"ALL")==0 )
			{
		//		cout<<"����������������"<<endl;
				all = true;	// ��ALL��ģ�Ҳ���Ǳ����ظ��� 
			}

			vector<QueryTuple*>::iterator iterator2;
			for (iterator2 = set2.begin(); iterator2 != set2.end(); iterator2++)
			{
					set1.push_back(*iterator2);					
			}
			
			if(!all) //����ALLѡ��ģ�Ҳ���ǲ������ظ���
			{
				set1 = TupleDistinct(set1);			
			}

			vec = set1;
		}
		break;	
		
	case Intersect:
		{
			bool all = false;
			
			if( strcmp(param->getStrParam(),"ALL")==0 )
			{
				cout<<"����������������"<<endl;
				all = true;	// ��ALL��ģ�Ҳ���Ǳ����ظ��� 
			}
			

			vector<QueryMember*> vec1,vec2;
			vector<QueryTuple*> vecTuple_Return;

			if(!all)
			{
				set1 = TupleDistinct(set1);
				set2 = TupleDistinct(set2);
			}
			
			vector<QueryTuple*>::iterator iterator1, iterator2;
			for (iterator1 = set1.begin(); iterator1 != set1.end(); iterator1++)
			{
				vec1 = (*iterator1)->getMembers();

				for (iterator2 = set2.begin(); iterator2 != set2.end(); iterator2++)
				{
					vec2 = (*iterator2)->getMembers();
					
					if(isEqual_vecMember(vec1,vec2))
					{
						vecTuple_Return.push_back((*iterator1));

						if(!all)
						{
							break;
						}
					}
				}
				
			}
			vec = vecTuple_Return;
		}		
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
									                std::vector<std::string>& theVector,
													FunParam *param)
{
    int size = theVector.size();
    XCube* pCube = _pSch->getCube(_cubeName);
	vector<QueryMember*> QmemVector;
	vector<QueryTuple*> QtupleVector;

	string dimName = "";
	string hieName = "";			
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
	hieName = pHie->getName();
	
	//���Ȱ�Member�����ݿ���load����
	pHie->LoadMembers();
	
	switch(_typesec)
	{
		//����Members�Ĵ������
		//����[Time].[Time].[1995].[Q1].[Month].Members
		//theVector��Ӧ���δ���string��Time, Time, 1995, Q1, Month
	case Members:
		if (size == 0 )
		{
			cout<<"error! please input query information..."<<endl;
		}
		else if (size == 1) //�������ڻ���֧�ֶ��Hierarchy������size Ϊ1��2�����һ����
		{   
			if ((theVector.at(0) == "Measures")||(theVector.at(0) == "measures"))
			{
				//Ԫ�������ڻ�û��֧��Ĭ�϶��������Ե�һ������ΪĬ�ϵ�
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
				string hierarcyName = pHie->getName();
				vector<string> vecLevelName;
	//			vector< vector<string> > memNameInLevels;//���ڴ洢ÿ��Level�ϳ�Ա���ֵ�vector
				
				vector<Level*> vecLevel = pHie->getLeveles();

				Member* temp = (vecLevel.at(0)->getMembers()).at(0);//��ȡ��һ�������һ����Ա
				
				getDescendants(temp,dimName,hieName,QtupleVector); // ��ȡ�ó�Ա�����к��
				
				pHie->CleanMembers();
				return QtupleVector;
				
			}
		}

		else if (size == 2)
		{   
			
			Level* pLevel = pHie->getLevel(theVector.at(1));
			
			vector<Member *> memVector1 = pLevel->getMembers();
			if (memVector1.empty())
			{
				cout<<"empty member vector,do not get the members from database"<<endl;
			} 
			else
			{
				vector<Member*>::iterator theIterator;
				QueryMember *pMem;

				for (theIterator = memVector1.begin(); theIterator < memVector1.end(); theIterator++)
				{
					
				    pMem = DwMemToQryMem(*theIterator,dimName,hieName);
					QmemVector.push_back(pMem);
					std::auto_ptr<QueryTuple>pTuple(new QueryTuple(QmemVector));
					QmemVector.pop_back();
					QtupleVector.push_back(pTuple.release());
				}
				
				pHie->CleanMembers();
				
				return QtupleVector;
			}	

		} 

		else if(size >= 3)  // [Time.Time].[Month].[Day].Members
		{
			cout<<"Members funtion error,too much member"<<endl;
			return 0;
		}

	break;
 
	//����AllMembers,�ο�SQL Server��������
	//���ذ���ָ��ά�Ȼ򼶱�����г�Ա�ļ��ϣ����������Ա��
	//ע����ʱ�����Ǽ����Ա�Ĵ���,��ʱ���ܺ�Members���ܲ��
	case AllMembers:
		if (size == 0 )
		{
			cout<<"error! please input the query information!"<<endl;
		}

		else
		{
			if (size == 1)
			{
				std::auto_ptr<QueryMember>pMem(new QueryMember);
				pMem->setVal("All");
				pMem->setDimensionName(dimName);    // add by eason
				pMem->setHierarchyName(hieName);
				pMem->setLevelName("All");
				QmemVector.push_back(pMem.release());
				std::auto_ptr<QueryTuple>pTuple(new QueryTuple(QmemVector));
				QmemVector.pop_back();
				QtupleVector.push_back(pTuple.release());
				return QtupleVector;
			} 	
		
			else if(size == 2)//[Time].[Quarter].AllMembers
			{
				pHie->LoadMembers();             //���Ȱ�Member�����ݿ���load���� add by eason
				
				Level* pLevel = pHie->getLevel(theVector.at(size-1));
				vector<Member*> memVector = pLevel->getMembers();
				vector<Member*>::iterator theIterator;
				QueryMember *pMem;

				for (theIterator = memVector.begin(); theIterator < memVector.end(); theIterator++)
				{
					pMem = DwMemToQryMem(*theIterator,dimName,hieName);
					QmemVector.push_back(pMem);
					std::auto_ptr<QueryTuple>pTuple(new QueryTuple(QmemVector));
					QmemVector.pop_back();
					QtupleVector.push_back(pTuple.release());
				}
				pHie->CleanMembers();  
				
				return QtupleVector;
			}
		
			else //[Time].[Year].[Month].AllMembers
			{
				cout<<"AllMembers funtion error,too much member"<<endl;
				return 0;
			}
		}
	break;

	case Children:
		{
		//ע��JPivot�����ǲ����ܳ������������
		//��Ϊһ�����֣�JPivot���Զ�ת���ɼ�һ��CurrentMember����
		//�磺[Time].Children���Զ�ת���[Time].CurrentMember.Children
		
		bool isall = false;
		if (size == 1)
		{
			cout<<"error! invalid using of Children"<<endl;

		} 

		else
		{			
			vector<Level*> levelVec = pHie->getLeveles();
			
			Member* mem = levelVec.at(0)->getMember(theVector.at(1), 0);
			
			for (int i = 1; i < size-1; i++)
			{
				mem = levelVec.at(i)->getMember(theVector.at(i+1), mem); 
			}
		
			vector<Member*> memVec = mem->getChildrenMember();

			vector<Member*>::iterator memIterator;
			QueryMember * ptr;
				
			for (memIterator = memVec.begin(); memIterator < memVec.end(); memIterator++)
			{
				ptr = DwMemToQryMem(*memIterator,dimName,hieName);
				QmemVector.push_back(ptr);
				std::auto_ptr<QueryTuple>pTuple(new QueryTuple(QmemVector));
				QmemVector.pop_back();
				QtupleVector.push_back(pTuple.release());
			}
		
			pHie->CleanMembers();

 			return QtupleVector;
 		}
		
		break;
		
}
	    //��һ���������
		case Siblings:

			if(size >= 2){
				
				vector<Level*> levelVec = pHie->getLeveles();
				Level *pLevel = levelVec.at(0);
				
				Member* temp = levelVec.at(0)->getMember(theVector.at(1), 0);
								
				for (int i = 1; i < size-1; i++)
				{
					temp = levelVec.at(i)->getMember(theVector.at(i+1), temp); 
				    pLevel = levelVec.at(i);	//�ֵܳ�Ա���ڵ�level				
				}
								
				Member* pMem = temp->getParent();
								
				vector<Member *> memVec;
							
				if(!pMem)   //�����ڸ���Ա,��Time.1998
				{	
					memVec = pLevel->getMembers();
				}
								
				else
				{
					memVec = pMem->getChildrenMember();
				}
				
				vector<Member *>::iterator memIterator;
				QueryMember *ptr;
				
				for(memIterator = memVec.begin();memIterator != memVec.end();memIterator++)
				{
					ptr = DwMemToQryMem(*memIterator,dimName,hieName);
					QmemVector.push_back(ptr);
					std::auto_ptr<QueryTuple>pTuple(new QueryTuple(QmemVector));
					QmemVector.pop_back();
					QtupleVector.push_back(pTuple.release());
				}
				pHie->CleanMembers();
				
				return QtupleVector;
			}
			else 
			{
				cout<<"Siblings funtion error,too less member"<<endl;
				return 0;
			}
			
			break;	
	
			
	case Descendants:
		{	
			   

				Level *ancLevel;  //�ȴ���Ա���ڵ�level
				Level *decLevel;  //�����Ա���ڵ�level
				vector<Level*> levelVec = pHie->getLeveles();
				Member* ancMember = levelVec.at(0)->getMember(theVector.at(1), 0);
				
				//��λĿ���Ա
				for (int i = 1; i < size-1; i++)
				{
					ancMember = levelVec.at(i)->getMember(theVector.at(i+1), ancMember); 
                    ancLevel = levelVec.at(i);
				}
				
				if(param->getHasIntParam() || param->getHasStrParam())
				{ 
					if(param->getHasIntParam())   //������������Ͳ���
					{
						int num = param->getIntParam();
						decLevel = ancLevel;

						if(num>0)
						{
							// ��λĿ�꼶��
							for(int j=0;j<num;j++)
							{
								decLevel = decLevel ->getChildLevel();
								assert(decLevel);   //�����ڸü���
							}
						}
					}
				
					if(param->getHasStrParam())  //��������ַ��Ͳ���
					{
						char *str = param->getStrParam();
						// ��λĿ�꼶��
						decLevel = pHie->getLevel(str); 
						assert(decLevel);   //�����ڸü���
					}

					vector<Member *> _mem = decLevel->getMembers();
					vector<QueryMember*> QmemVector;
					QueryMember* ancMem = DwMemToQryMem(ancMember,dimName,hieName);
					QueryMember* decMem;
				
					for(int i = 0; i< _mem.size(); i++)
					{
						decMem = DwMemToQryMem(_mem.at(i),dimName,hieName);
					
						//�˴��ԿɸĽ���û��Ҫ���������ϵ����г�Ա
						if(isAncestor(ancMem, decMem))
						{
							QmemVector.push_back(decMem);
							std::auto_ptr<QueryTuple>pTuple(new QueryTuple(QmemVector));	
							QmemVector.pop_back();
							QtupleVector.push_back(pTuple.release());
						}
					}
				}

				else         //�����������
				{
					getDescendants(ancMember,dimName,hieName,QtupleVector);
				}

				pHie->CleanMembers();
				return QtupleVector;
		}
				break;

		case Ascendants:
		{			
					vector<Level*> levelVec = pHie->getLeveles();
					Member* decMember = levelVec.at(0)->getMember(theVector.at(1), 0);
					
					//��λĿ���Ա
					for (int i = 1; i < size-1; i++)
					{
						decMember = levelVec.at(i)->getMember(theVector.at(i+1), decMember); 
						assert(decMember);
					}

					vector<QueryMember*> QmemVector;
					QueryMember * ancQryMem;
					Member* ancMember = decMember ;

					while(ancMember)
					{
						ancQryMem = DwMemToQryMem(ancMember,dimName,hieName);
						QmemVector.push_back(ancQryMem);
						std::auto_ptr<QueryTuple>pTuple(new QueryTuple(QmemVector));	
						QmemVector.pop_back();
						QtupleVector.push_back(pTuple.release());
						ancMember = ancMember->getParent();
					}

					pHie->CleanMembers();
					return QtupleVector;
		}
					break;
	}

}

/*************************************************************
 * another kind of function that deal with one set 
 * and returns a set;
 ************************************************************/
 std::vector<QueryTuple*> SetFunFactory::funInstance(SetTypethird _typethird, std::vector<QueryTuple*>& set, FunParam *param)
{
	switch(_typethird)
	{
	//��QueryTuple���û�������
	case Hierarchize:
		{
		//	cout<<"����������������:"<<set.size()<<endl;
			int QueryTuplesize = set.size();
			QueryTuple* p = set.at(0);
			vector<QueryMember*> vecMem = p->getMembers();
			int size = vecMem.size();
			//�û�������,�����һ��ά��ʼ��
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
						//allString1�ǰ�һ��member�����и��׵�val���Լ���val���һ����
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
						//allString2�ǰ�һ��member�����и��׵�val���Լ���val���һ����
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


	case Distinct:// add by eason
	{
		vector<QueryTuple*> vec_set = set;
		return TupleDistinct(vec_set);
		break;
	}

	case Tail:
	{	
		vector<QueryTuple*> vec_set;
		int num = param->getIntParam();
		int size = set.size();

		if(num<1)
		{
            return vec_set;
		}

		else if(num>size)
		{
			return set;
		}

		for(int i= num; i >= 1; i--)
		{
			vec_set.push_back(set.at(size-i));
		}

		return vec_set;
		break;
	}

	case Head:
		{	
			vector<QueryTuple*> vec_set;
			int num = param->getIntParam();
			int size = set.size();
			
			if(num<1)
			{
				return vec_set;
			}
			
			else if(num>size)
			{
				return set;
			}
			
			for(int i= 0; i <num; i++)
			{
				vec_set.push_back(set.at(i));
			}
			
			return vec_set;
			break;
		}
	
	}
}