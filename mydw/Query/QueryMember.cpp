#include <iostream>
#include "MdxParser/QueryMember.h"

using namespace std;

QueryMember::QueryMember()
{
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
}

QueryMember::QueryMember(string& _dimensionName,
			string& _hierarchyName,
			string& _levelName,
			string& _val,
			vector<string>& _ancestorVals,
			vector<string>& _ancestorLevels,
			bool _isAll)
{
	 dimensionName = _dimensionName;
     hierarchyName = _hierarchyName;
	 levelName = _levelName;
     val = _val;
	 ancestorVals = _ancestorVals;
	 ancestorLevels = _ancestorLevels;
	 isAll = _isAll;
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
}