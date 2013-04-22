#include "DWSchemac/XSchemas.h"
#include "DWSchemac/XSchema.h"
#include "DWSchemac/XCube.h"
#include "DWSchemac/Dimension.h"
#include "DWSchemac/Hierarchy.h"
#include "DWSchemac/Member.h"
#include "DWSchemac/Level.h"
#include "DWSchemac/Measure.h"
#include "MdxParser/Common.h"

#include "calcMemFormat.h"
#include "calculatedMember.h"
//#include "MdxParser/QueryMember.h"

//判断是否合法的成员
bool isMember(XSchema* _pSch, string& _cubeName,vector<string>& theVector)
{
	XCube* pCube = _pSch->getCube(_cubeName);
	int size = theVector.size();
	
	Dimension* pDim =NULL;
	Hierarchy* pHie = NULL;
	string dimName = "";
	string hieName = "";
	
	if (theVector.at(0)=="Measures"||theVector.at(0)=="measures")
	{
		if (size == 2)
		{
			Measure* pMea = pCube->getMeasure(theVector.at(1));
			if(!pMea)
			{
				cout<<"error measure member information:";
				vector<std::string>::iterator theIterator;
				for (theIterator = theVector.begin(); theIterator != theVector.end();theIterator++)
				{
					cout << "["<<*theIterator<<"]";
					if (theIterator < theVector.end()-1) cout << ".";                                             
				}
				cout<<endl;
				return false;
			}
			return true;
		} 
		
		if(size>2)
		{
			cout<<"error...invalid measure"<<endl;
			return false;
		}
	}

	else
	{ 
		if (isDimHie(theVector.at(0)))
		{
			vector<string> temp = distinct(theVector.at(0));
			dimName = temp.at(0);
			pDim = pCube->getDimension(dimName);
			if(!pDim)
			{
				cout<<"can not get dimension pointer:";
				vector<std::string>::iterator theIterator;
				for (theIterator = theVector.begin(); theIterator != theVector.end();theIterator++)
				{
					cout << "["<<*theIterator<<"]";
					if (theIterator < theVector.end()-1) cout << ".";                                             
				}
				cout<<endl;
				return false;
			}
		
			hieName = temp.at(1);
			pHie = pDim->getHierarchy(hieName);
		
			if(!pHie)
			{
				cout<<"can not get hierarchy pointer when creat calcMember:";
				vector<std::string>::iterator theIterator;
			
				for (theIterator = theVector.begin(); theIterator != theVector.end();theIterator++)
				{
					cout << "["<<*theIterator<<"]";
					if (theIterator < theVector.end()-1) cout << ".";                                             
				}
				cout<<endl;
				return false;
			}
		}
	
		else
		{
			dimName = theVector.at(0);
			pDim = pCube->getDimension(theVector.at(0));
		
			if(!pDim)
			{
				cout<<"can not get dimension pointer:";
				vector<std::string>::iterator theIterator;
			
				for (theIterator = theVector.begin(); theIterator != theVector.end();theIterator++)
				{
					cout << "["<<*theIterator<<"]";
					if (theIterator < theVector.end()-1) cout << ".";                                             
				}
				cout<<endl;
				return false;
			}
			pHie = pDim->getDefaultHierarchy();
		
			if(!pHie)
			{
				cout<<"can not get hierarchy pointer:";
				vector<std::string>::iterator theIterator;
			
				for (theIterator = theVector.begin(); theIterator != theVector.end();theIterator++)
				{
					cout << "["<<*theIterator<<"]";
					if (theIterator < theVector.end()-1) cout << ".";                                             
				}
				cout<<endl;
				return false;
			}
		}

		if(size>1)
		{
			pHie->LoadMembers();
			vector<Level*> levelVec = pHie->getLeveles();
			Member* pMem = levelVec.at(0)->getMember(theVector.at(1), 0);

			if(!pMem)
			{
				cout<<"the member doesn't exit:";
				vector<std::string>::iterator theIterator;
				for (theIterator = theVector.begin(); theIterator != theVector.end();theIterator++)
				{
					cout << "["<<*theIterator<<"]";
					if (theIterator < theVector.end()-1) cout << ".";                                             
				}
				cout<<endl;
				return false;
			}
	
			for (int i = 4; i < size+2; i++)
			{
				Member* temp = levelVec.at(i-3)->getMember(theVector.at(i-2), pMem); 
	
				if(!temp)
				{
					cout<<"the member doesn't exit:";
					vector<std::string>::iterator theIterator;
					for (theIterator = theVector.begin(); theIterator != theVector.end();theIterator++)
					{
						cout << "["<<*theIterator<<"]";
						if (theIterator < theVector.end()-1) cout << ".";                                             
					}
					cout<<endl;
					return false;
				}
				pMem = temp;
			}
		}
	}
	return true;
}

//判断2个字符串向量是否相同
bool isEqual_String(vector<string>& vec1, vector<string>& vec2)
{
	if(vec1.size()!=vec2.size())
	{
		return false;
	}

	for (int i = 0; i < vec1.size(); i++)
	{
		if (vec1.at(i) != vec2.at(i))   
		{
			return false;
		}
	}
	return true;		
}


	

// 如果qryMember是计算成员，返回其计算表达式
vector<calcMemFormat *> getCalcFormat(QueryMember* qryMember,vector<calculatedMember*> &_vec_calcMember)
{
	vector<calcMemFormat *> format;
	vector<string> _memInfo = qryMember->getMemberName();

	vector<calculatedMember*>::iterator iter;
	
	for(iter = _vec_calcMember.begin(); iter != _vec_calcMember.end();iter++)
	{
		vector<string> vec = (*iter)->getCalcMemberName();
		if(isEqual_String(_memInfo, vec))
		{
			format = (*iter)->getCalcMemFormat();
			return format;
		}		
	}
	return 0; //找不到
	
}


// 如果qryMember是计算成员，返回其计算成员类
calculatedMember* getCalcMem(QueryMember* qryMember,vector<calculatedMember*> &_vec_calcMember)
{
	vector<string> _memInfo = qryMember->getMemberName();
	
	vector<calculatedMember*>::iterator iter;
	
	for(iter = _vec_calcMember.begin(); iter != _vec_calcMember.end();iter++)
	{
		vector<string> vec = (*iter)->getCalcMemberName();
		if(isEqual_String(_memInfo, vec))
		{
			return *iter;
		}
		
	}
	return 0;//找不到
}


// 如果某成员(用_memInfo表示)是计算成员，返回其计算表达式
vector<calcMemFormat *> getCalcFormat2(vector<string> &_memInfo,vector<calculatedMember*> &_vec_calcMember)
{
	vector<calcMemFormat *> format;
	
	vector<calculatedMember*>::iterator iter;
	
	for(iter = _vec_calcMember.begin(); iter != _vec_calcMember.end();iter++)
	{
		vector<string> vec = (*iter)->getCalcMemberName();
		if(isEqual_String(_memInfo, vec))
		{
			format = (*iter)->getCalcMemFormat();
			return format;
		}		
	}
	return 0; //找不到
	
}