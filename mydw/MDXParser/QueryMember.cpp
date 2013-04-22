#include <iostream>
#include "MdxParser/QueryMember.h"

// class calcMemFormat;
#include "MdxParser/calcMemFormat.h"

using namespace std;

QueryMember::QueryMember()
{
	isAll = false;
	isCalculated = false;
}//end default constructor

QueryMember::QueryMember(const QueryMember& other)
{
     dimensionName = other.dimensionName;
     hierarchyName = other.hierarchyName;
	 levelName = other.levelName;
     val = other.val;
	 ancestorVals = other.ancestorVals;
	 ancestorLevels = other.ancestorLevels;
	 isAll = other.isAll;
     isCalculated = other.isCalculated;
}

QueryMember::QueryMember(string& _dimensionName,
			string& _hierarchyName,
			string& _levelName,
			string& _val,
			vector<string>& _ancestorVals,
			vector<string>& _ancestorLevels,
			bool _isAll,
			bool _isCalculated)
{
	 dimensionName = _dimensionName;
     hierarchyName = _hierarchyName;
	 levelName = _levelName;
     val = _val;
	 ancestorVals = _ancestorVals;
	 ancestorLevels = _ancestorLevels;
	 isAll = _isAll;
	 isCalculated = false;
	 isCalculated = _isCalculated;
}//~end constructor


const string QueryMember::getVal()const
{
       return this->val;
}

const string QueryMember::getLevelName()const
{
     return this->levelName;      
}

const string QueryMember::getHierarchyName()const
{
       return this->hierarchyName;
}

const string QueryMember::getDimensionName()const
{
	return this->dimensionName;
}

const vector<string> QueryMember::getAncestorVals()const
{
    return this->ancestorVals;
}

const vector<string> QueryMember::getAncestorLevels()const
{
    return this->ancestorLevels;
}

bool QueryMember::hasAll()
{
    return  isAll;
}

bool QueryMember::getIsCalculated()
{
	return isCalculated;
}

vector<calcMemFormat* > QueryMember::getCalcFormat()
{
	return calcFormat;
}

QueryMember& QueryMember::operator=(const QueryMember& other)
{
        this->hierarchyName = other.hierarchyName;
        this->levelName = other.levelName;
        this->val = other.val;	  
	    this->ancestorVals = other.ancestorLevels;
		this->ancestorLevels = other.ancestorLevels;
		return *this;
}

void QueryMember::setVal(string _val)
{
    val = _val;
}

void QueryMember::setLevelName(string _levelName)
{
    levelName = _levelName;
}

void QueryMember::setHierarchyName(string _hierarchyName)
{
    hierarchyName = _hierarchyName;
}

void QueryMember::setDimensionName(string _dimensionName)
{
     dimensionName = _dimensionName;
}

void QueryMember::setAncestorVals(const vector<string>& _ancestorVals)
{
    ancestorVals = _ancestorVals;
}

void QueryMember::setAncestorLevels(const vector<string>& _ancestorLevels)
{
    ancestorLevels = _ancestorLevels;
}

void QueryMember::setIsAll(bool _isAll)
{  
    isAll = _isAll;
}

void QueryMember::setIsCalculated(bool _isCalculated)
{
	isCalculated = _isCalculated;
}

void QueryMember::setCalcFormat(vector<calcMemFormat *> &_format)
{
	calcFormat = _format;
}



void QueryMember::showMember()
{
    vector<std::string> theVector;
	vector<std::string>::iterator theIterator;
	
	theVector = this->getAncestorVals();

    
	if(this->getDimensionName() == "Measures")
	{
        cout<<"            the member is:"<<"["<<this->getDimensionName()<<"]"<<".";
	}
	else
	{
	//	if(this->getDimensionName().empty()) {  cout<<"DimensionName is empty"<<endl; }    // add by eason
       cout<<"            the member is:"<<"["<<this->getDimensionName()<<".";
	   cout<<this->getHierarchyName()<<"]"<<".";
	}
    for (theIterator = theVector.begin(); theIterator != theVector.end();
         theIterator++)
    {
        cout << "["<<*theIterator<<"]";
        if (theIterator != theVector.end()) cout << ".";                                             
    }
	cout<<"["<<this->getVal()<<"]"<<endl;

	cout<<"                the member's value is:"<<this->getVal()<<endl;
	cout<<"                the member's level is:"<<this->getLevelName()<<endl;

	cout<<"                the member's ancestorVals:{";
    for (theIterator = theVector.begin(); theIterator != theVector.end();
         theIterator++)
    {
        cout << *theIterator;
        if (theIterator != theVector.end()-1) cout << ", ";                                             
    }
    cout << "}" << endl ;

    theVector = this->getAncestorLevels();
	cout<<"                the member's ancestorLevels:{";
    for (theIterator = theVector.begin(); theIterator != theVector.end();
         theIterator++)
    {
        cout << *theIterator;
        if (theIterator != theVector.end()-1) 
			cout << ", ";                                             
    }
    cout << "}" << endl ;
	cout<<"                isAll:"<<this->hasAll()<<endl;
	cout<<"                isCalculated:"<<this->getIsCalculated()<<endl;
	
	if(this->getIsCalculated())
	{
		vector<calcMemFormat *> vecFormat = this->calcFormat;
		cout<<"后缀表达式大小为"<<vecFormat.size()<<":";
		vector<calcMemFormat *>::iterator format;

		for (format = vecFormat.begin(); format != vecFormat.end(); format++)
		{
			
		    (*format)->showFormat();
			if (format != vecFormat.end()-1) 
			{
				cout << ",";
			}                                
		}
		cout<<endl;
	}
}


void QueryMember::_showMember()
{
    vector<std::string> theVector;
	vector<std::string>::iterator theIterator;
	
	theVector = this->getAncestorVals();
	
    
	if(this->getDimensionName() == "Measures")
	{
        cout<<"["<<this->getDimensionName()<<"]"<<".";
	}
	else
	{
		//	if(this->getDimensionName().empty()) {  cout<<"DimensionName is empty"<<endl; }    // add by eason
		cout<<"["<<this->getDimensionName()<<".";
		cout<<this->getHierarchyName()<<"]"<<".";
	}
    for (theIterator = theVector.begin(); theIterator != theVector.end();
	theIterator++)
    {
        cout << "["<<*theIterator<<"]";
        if (theIterator != theVector.end()) cout << ".";                                             
    }
	cout<<"["<<this->getVal()<<"]";
}

vector<string> QueryMember::getMemberName()
{
	vector<std::string> vecName;

	vector<std::string> theVector;
	vector<std::string>::iterator theIterator;
	
	theVector = this->getAncestorVals();
	
    
	if(this->getDimensionName() == "Measures")
	{
		vecName.push_back(this->getDimensionName());
	}
	else
	{
		string temp = this->getDimensionName()+"."+this->getHierarchyName();

//		vecName.push_back(this->getDimensionName());
//		vecName.push_back(this->getHierarchyName());

		vecName.push_back(temp);

	}
    for (theIterator = theVector.begin(); theIterator != theVector.end();
	theIterator++)
    {
        vecName.push_back(*theIterator);
    }
	vecName.push_back(this->getVal());

	return vecName;
}