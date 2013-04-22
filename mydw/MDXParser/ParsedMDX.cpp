#include <iostream>
#include "MdxParser/ParsedMDX.h"
#include "MdxParser/QueryTuple.h"

using namespace std;
//using namespace mdx;

class QueryMember;
class QueryTuple;

ParsedMDX::ParsedMDX()
{
	axes.erase(axes.begin(),axes.end());
}

ParsedMDX::ParsedMDX(const ParsedMDX& pm)
{
     this->cubeName = pm.cubeName;
     this->schemaName = pm.schemaName;
     this->slicer = pm.slicer;
	 this->pCaclMember = pm.pCaclMember;
	 this->axes =pm.axes;
	 this->nonEmpty = pm.nonEmpty;
}
ParsedMDX::ParsedMDX(string _cubeName,
			      string _schemaName,
				  vector<QueryTuple*>& _slicer,
				  vector<calculatedMember*>& _pCaclMember,
                  const vector< vector<QueryTuple*> >& _axes,
				  bool _nonempty)
{
     cubeName = _cubeName;
     schemaName = _schemaName;
     slicer = _slicer;
	 pCaclMember = _pCaclMember,
	 axes = _axes;
	 nonEmpty = _nonempty;
}

ParsedMDX::~ParsedMDX()
{
    if(this == NULL)
		return;
//	if (slicer != NULL)
//		delete [] slicer;
//	if (this != NULL)
//       delete axes;
}

const string ParsedMDX::getSchemaName()const
{
    return this->schemaName;
}

 const string ParsedMDX::getCubeName() const
{
    return this->cubeName;
}

vector< vector<QueryTuple*> > ParsedMDX::getAxes()
{
     return this->axes;      
}

vector< calculatedMember* > ParsedMDX::getCalcMember()
{
	return this->pCaclMember;
}

const vector<QueryTuple*> ParsedMDX::getSlicer()const
{
     return this->slicer;
}

void ParsedMDX::setSchemaName(string _schemaName)
{
    this->schemaName = _schemaName;
}

void ParsedMDX::setAxes(const vector< vector<QueryTuple*> >& _axes)
{
    this->axes = _axes;
}


void ParsedMDX::showParsedMDX()
{
	cout<<"show the ParsedMDX......."<<endl;
    cout<<"schema name is:"<<this->getSchemaName()<<endl;
	cout<<"cube name is:"<<this->getCubeName()<<endl;

    vector< vector<QueryTuple*> > theVector;
	vector< vector<QueryTuple*> >::iterator theIterator;
	theVector = this->getAxes();
    for (theIterator = theVector.begin(); theIterator != theVector.end();
         theIterator++)
    {
		cout << "show one of the Axes:"<<endl;
	    vector<QueryTuple*> theVector1;
		vector<QueryTuple*>::iterator theIterator1;
		theVector1 = *theIterator;
		for(theIterator1 = theVector1.begin(); theIterator1 != theVector1.end(); theIterator1++)
		{
			cout<<"   show one of the QueryTuples in the axis:"<<endl;
		    QueryTuple* p = *theIterator1;
			p->showTuple();
		}                                             
    }
 
	if((this->getSlicer()).empty())
	{
	     cout<<"there is no slicer in the MDX query....."<<endl;
	}
	else
	{
	    vector<QueryTuple*> vec = this->getSlicer();
		vector<QueryTuple*>::iterator theIterator2;
        for(theIterator2 = vec.begin(); theIterator2 != vec.end(); theIterator2++)
		{
			cout<<"show one of the QueryTuples in the slicer:"<<endl;
		    QueryTuple* p = *theIterator2;
			p->showTuple();
		}
		//cout<<"members of the slicer:"<<endl;
		//p->showTuple();
	}

	if((this->getCalcMember()).empty())
	{
		cout<<"there is no calcMember in the MDX query....."<<endl;
	}
	else
	{
		vector<calculatedMember*> vec = this->getCalcMember();
		vector<calculatedMember*>::iterator theIterator;
        for(theIterator = vec.begin(); theIterator != vec.end(); theIterator++)
		{
			cout<<"show one of the calcMember in the MDX query:"<<endl;
			calculatedMember* temp = *theIterator;
			temp->showCalcMember();
			cout<<endl;			
		}

	}
	
}