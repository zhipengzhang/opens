#include <string>
#include <iostream>
#include "MdxParser/QueryTuple.h"

using namespace std;

QueryTuple::QueryTuple()
{      
	members.erase(members.begin(),members.end());
}//end default constructor

QueryTuple::QueryTuple(const QueryTuple& qt)
{
    this->members = qt.members;
}

QueryTuple::QueryTuple(vector<QueryMember*>& _members)
{
   members = _members;                               
}

const vector<QueryMember*> QueryTuple::getMembers()const
{
    return this->members;                           
}

QueryTuple& QueryTuple::operator=(const QueryTuple& other)
{
    this->members = other.members;
	return *this;
}


bool QueryTuple::empty()const
{
    return (members.empty() == true);
}

void QueryTuple::setTuple(vector<QueryMember*>& _members)
{
    this->members = _members; 
}

void QueryTuple::showTuple()
{
    vector<QueryMember*> theVector;
	vector<QueryMember*>::iterator theIterator;

    theVector = this->getMembers();

    cout << "         show the members in this QueryTuple: "<<endl;
    for (theIterator = theVector.begin(); theIterator != theVector.end(); theIterator++)
    {
        QueryMember* p = *theIterator;
		p->showMember();                                      
    }
}
