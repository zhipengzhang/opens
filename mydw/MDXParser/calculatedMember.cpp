// calculatedMember.cpp: implementation of the calculatedMember class.
//
//////////////////////////////////////////////////////////////////////
#include <iostream>
#include "MdxParser/calculatedMember.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

calculatedMember::calculatedMember(vector<string>& _memberName,vector<calcMemFormat *>& _Format)
{
	memberName = _memberName;
    Format = _Format;
}

vector<string> calculatedMember::getCalcMemberName()
{
	return this->memberName;
}

vector<calcMemFormat *> calculatedMember::getCalcMemFormat()
{
	return this->Format;
}


void calculatedMember::showCalcMember()
{
	vector<std::string> theVector;
	vector<std::string>::iterator theIterator;
	
	theVector = this->memberName;
	
    for (theIterator = theVector.begin(); theIterator != theVector.end();theIterator++)
    {
        cout << "["<<*theIterator<<"]";
        if (theIterator < theVector.end()-1) cout << ".";                                             
    }

	cout<<endl<<"计算成员的后缀表达式:";
	vector<calcMemFormat *> theVector1;
    vector<calcMemFormat *>::iterator theIterator1;

	theVector1 = this->Format;

	for (theIterator1 = theVector1.begin(); theIterator1 != theVector1.end();theIterator1++)
    {
		        
		if( (*theIterator1)->type == INT_NUMBER )
		{
			//	printf("整数 ");
			//	cout<<(*theIterator1)->FormatContent.number;  
			printf("%d",(*theIterator1)->FormatContent.int_number);
		}
		
			
		if( (*theIterator1)->type == DEC_NUMBER )
		{
			//	printf("小数 ");
			//	cout<<(*theIterator1)->FormatContent.number;  
			printf("%f",(*theIterator1)->FormatContent.dec_number);
		}
		

		if( (*theIterator1)->type == MATH_OPERATER )
		{
		//	printf("符号 ");
		//	cout<<(*theIterator1)->FormatContent.mathOper; 
			printf("%c",(*theIterator1)->FormatContent.mathOper);
		}

		if( (*theIterator1)->type == QUERYMEMBER )
		{
		//	printf("成员 ");
			QueryMember *temp = (*theIterator1)->FormatContent.member;
			temp->_showMember();
		}
		if( (*theIterator1)->type == QUERYMEMBER_UMINUS )
		{
			printf("负号");
			QueryMember *temp = (*theIterator1)->FormatContent.member;
			temp->_showMember();
		}	

		if(theIterator1 != theVector1.end()-1)
		{
			cout<<",";
		}

    }

	cout<<endl;
}

calculatedMember::~calculatedMember()
{

}
