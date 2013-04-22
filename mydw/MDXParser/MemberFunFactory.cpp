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
 
QueryMember* MemberFunFactory::funInstance(XSchema* _pSch, string& _cubeName, MemType _type, std::vector<std::string>& theVector, FunParam *param)
{
//	std::auto_ptr<QueryMember>pQmem(new QueryMember);

	QueryMember *pQmem;
	int size = theVector.size();
	XCube* pCube = _pSch->getCube(_cubeName);

	Dimension* pDim =NULL;
	Hierarchy* pHie = NULL;
	string dimName = "";
	string hieName = "";
	
	if (isDimHie(theVector.at(0)))
	{
		vector<string> temp = distinct(theVector.at(0));
		dimName = temp.at(0);
		pDim = pCube->getDimension(dimName);
		assert(pDim);
		hieName = temp.at(1);
		pHie = pDim->getHierarchy(hieName);
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
	
	pHie->LoadMembers();


	switch(_type)
	{	
	case PrevMember:
		if (size == 1)
		{
			//size ==1 �����Ҳ���ڣ����ڳ��ּ����Աʱ��������WHIT�Ӿ�
			//�磺Time.PrevMember,��ʱһ��ʱ������滻WHERE�Ӿ��г��ֵ�Timeά�ĳ�Ա
			//��Time.1998,�൱��Time.1997��Time.1998.PrevMember
			//��ʱ�Ȳ�����
			cout<<"incorrect usage of function PrevMember."<<endl;
		}
		else
		{		
				vector<Level*> levelVec= pHie->getLeveles();

				Member* pMem = levelVec.at(0)->getMember(theVector.at(1), 0);
				assert(pMem);

				Level* plevel = levelVec.at(0);//ָ��PrevMember��ָ��Level
				
				for (int i = 1; i < size-1; i++)
				{
					pMem = levelVec.at(i)->getMember(theVector.at(i+1), pMem); 
					plevel = levelVec.at(i);
				}
				
                vector<Member*> vecMem = plevel->getMembers();
				vector<Member*>::iterator theIterator;

				for (theIterator = vecMem.begin(); theIterator < vecMem.end(); theIterator++)
				{
					if (*theIterator == pMem )  // Ҫ�������һ��Member��PrevMemberʱ�����ڵ����  add by eason
					{						
						if(theIterator > vecMem.begin())
						{
							pMem = *(theIterator-1);
							pQmem = DwMemToQryMem(pMem,dimName,hieName);							
						}

						else
						{
							cout<<"the prevmember not exist..."<<endl;
						}
							
						pHie->CleanMembers();
						break;               
					}				
				}							
			}	
	
		break;
		
	case NextMember:

		if (size == 1)
		{
			cout<<"incorrect usage of function NextMember."<<endl;
		}
		else
		{	
			vector<Level*> levelVec= pHie->getLeveles();
			
			Member* pMem = levelVec.at(0)->getMember(theVector.at(1), 0);
			assert(pMem);
			
			Level* plevel = levelVec.at(0);//ָ��NextMember��ָ��Level
			
			for (int i = 1; i < size-1; i++)
			{
				pMem = levelVec.at(i)->getMember(theVector.at(i+1), pMem); 
				plevel = levelVec.at(i);
			}
			
			vector<Member*> vecMem = plevel->getMembers();
				
				vector<Member*>::iterator theIterator;

				for (theIterator = vecMem.begin(); theIterator < vecMem.end(); theIterator++)
				{
					if (*theIterator == pMem && theIterator < vecMem.end()-1 )  // Ҫ�������һ��Member��NextMemberʱ�����ڵ����  add by eason
					{						
						pMem = *(theIterator+1);
						assert(pMem);
						pQmem = DwMemToQryMem(pMem,dimName,hieName);
							
						pHie->CleanMembers();
						break;               
					}				
				}							
			}

		break;

//	[Time].[1995].FirstChild
//	vector�е�ֵӦ����ΪTime,1995
//	����FoodMart������[Time.Time].[1995].[January]
   case FirstChild: 
		
		if (size == 1)  // [Time].FirstChild
		{
			vector<Level*> levelVec = pHie->getLeveles();
			//ȡ��һ��LEVEL��ΪĬ�ϵ�Level
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
				pQmem = DwMemToQryMem(pMem,dimName,hieName);
			}
		}
		
		else //   [Time].[1997].[Q1].FirstChild
		{							
			vector<Level*> levelVec= pHie->getLeveles();
			
			Member* pMem = levelVec.at(0)->getMember(theVector.at(1), 0);
			assert(pMem);
						
			for (int i = 1; i < size-1; i++)
			{
				pMem = levelVec.at(i)->getMember(theVector.at(i+1), pMem); 
			}
			
			vector<Member*> pMemChild = pMem->getChildrenMember();
			
			pQmem = DwMemToQryMem(pMemChild.at(0),dimName,hieName);
			
			pHie->CleanMembers();
		}					

		break;
	

   case LastChild:
	   if (size == 1)  // [Time].FirstChild
	   {
		   vector<Level*> levelVec = pHie->getLeveles();
		   //ȡ��һ��LEVEL��ΪĬ�ϵ�Level
		   Level* pLevel = levelVec.at(0);
		   if (!pLevel)
		   {
			   cout<<"can not get default level when using function FirstChild!"<<endl;
		   } 
		   else
		   {
			   string levelName = pLevel->getName();
			   vector<Member*> memVec = pLevel->getMembers();
			   int size = memVec.size();
			   Member* pMem = memVec.at(size-1);
			   pQmem = DwMemToQryMem(pMem,dimName,hieName);
		   }
	   }
	   
	   else //   [Time].[1997].[Q1].FirstChild
	   {							
		   vector<Level*> levelVec= pHie->getLeveles();
		   
		   Member* pMem = levelVec.at(0)->getMember(theVector.at(1), 0);
		   assert(pMem);
		   
		   for (int i = 1; i < size-1; i++)
		   {
			   pMem = levelVec.at(i)->getMember(theVector.at(i+1), pMem); 
		   }
		   
		   vector<Member*> pMemChild = pMem->getChildrenMember();
		   
		   int size = pMemChild.size();
		   pQmem = DwMemToQryMem(pMemChild.at(size-1),dimName,hieName);
		   
		   pHie->CleanMembers();
	   }					
		   break;

	case CurrentMember:
		if (theVector.size() == 1)
		{
				auto_ptr<Member> pMem = pHie->getDefaultMember();
				assert(pMem.release());

				Member *pMem1 = pMem.get();
				pQmem = DwMemToQryMem(pMem1,dimName,hieName);

		}
		break;

   	case FirstSibling:
		// size=2ʱ,�����ڸ���Ա
			if (size > 2)
			{  
				vector<Level*> levelVec= pHie->getLeveles();
				
				Member* pMem = levelVec.at(0)->getMember(theVector.at(1), 0);
				assert(pMem);
				
				for (int i = 1; i < size-1; i++)
				{
					pMem = levelVec.at(i)->getMember(theVector.at(i+1), pMem); 
				}
				
				vector<Member*> pSiblingMem = pMem->getParent()->getChildrenMember();

				pQmem = DwMemToQryMem(pSiblingMem.at(0),dimName,hieName);

				pHie->CleanMembers();
			}
			break;

		case LastSibling:
			// size=2ʱ,�����ڸ���Ա

			if (size > 2)
			{  
				vector<Level*> levelVec= pHie->getLeveles();
				
				Member* pMem = levelVec.at(0)->getMember(theVector.at(1), 0);
				assert(pMem);
				
				for (int i = 1; i < size-1; i++)
				{
					pMem = levelVec.at(i)->getMember(theVector.at(i+1), pMem); 
				}
				
				vector<Member*> pSiblingMem = pMem->getParent()->getChildrenMember();
				
				int size = pSiblingMem.size();
				pQmem = DwMemToQryMem(pSiblingMem.at(size-1),dimName,hieName);
				
				pHie->CleanMembers();
			}

			break;
			
		case Parent:

			if(size>=2)
			{
				vector<Level*> levelVec= pHie->getLeveles();
				
				Member* pMem = levelVec.at(0)->getMember(theVector.at(1), 0);
				assert(pMem);
				
				for (int i = 1; i < size-1; i++)
				{
					pMem = levelVec.at(i)->getMember(theVector.at(i+1), pMem); 
				}
				
				Member * ParentMem = pMem->getParent();
				assert(ParentMem);
				pQmem = DwMemToQryMem(ParentMem ,dimName,hieName);

				pHie->CleanMembers();
			}
			break;
			
		case Ancestor:

			if(size>=2)
			{
				Level* pLevel;
				vector<Level*> levelVec = pHie->getLeveles();
				Member* temp = levelVec.at(0)->getMember(theVector.at(1), 0);
				
				for (int i = 1; i < size-1; i++)
				{
					temp = levelVec.at(i)->getMember(theVector.at(i+1), temp); 
					pLevel = levelVec.at(i-1);					
				}

				Member* pMem = temp;
				 
				if(param->getHasIntParam())
				{
					int num = param->getIntParam();

					for(int j=0;j<num;j++)
					{
						pMem = pMem ->getParent();
						assert(pMem);   //�����ڸ���Ա
					}
				}
				
				if(param->getHasStrParam())
				{
					char *str = param->getStrParam();
					cout<<"strParam: "<<str<<endl;		
					string strLevel = pMem->getLevel()->getName();
					cout<<"strLevel: "<<strLevel<<endl;
					
					while(strcmp(str,strLevel.c_str())!=0 )
					{
						pMem = pMem ->getParent();
						assert(pMem);   //�����ڸ���Ա
						strLevel = pMem->getLevel()->getName();
					}
				}
				
				pQmem = DwMemToQryMem(pMem,dimName,hieName);
				
				pHie->CleanMembers();
			}
			break;
	}
	
//	return pQmem.release();

return pQmem;
}