// calcMemFormat.cpp: implementation of the calcMemFormat class.
//
//////////////////////////////////////////////////////////////////////

#include "MdxParser/calcMemFormat.h"
#include <iostream>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

calcMemFormat::calcMemFormat(ContentType _type,char* _mathOper)
{
	type = _type;
	FormatContent.mathOper = _mathOper;

}

calcMemFormat::calcMemFormat(ContentType _type,int _int_number)
{
	type = _type;
	FormatContent.int_number = _int_number;
}

calcMemFormat::calcMemFormat(ContentType _type,double _dec_number)
{
	type = _type;
	FormatContent.dec_number = _dec_number;
}

calcMemFormat::calcMemFormat(ContentType _type,QueryMember* _member)
{
	type = _type;
	FormatContent.member = _member;
}

ContentType calcMemFormat::getType()
{
	return type;
}

char* calcMemFormat::getMathOper()
{
	return FormatContent.mathOper;
}

int calcMemFormat::getIntNum()
{
	return FormatContent.int_number;
}

double calcMemFormat::getDecNum()
{
	return FormatContent.dec_number;
}

QueryMember* calcMemFormat::getQryMember()
{
	return FormatContent.member;
}

void calcMemFormat::showFormat()
{
	if( this->getType() == INT_NUMBER )
	{
		//	printf("整数 ");
//		cout<<this->FormatContent.int_number;  
		printf("%d",this->getIntNum());
	}
	
	
	if( this->getType() == DEC_NUMBER )
	{
		//	printf("小数 ");
//		cout<<this->FormatContent.dec_number;  
		printf("%f",this->getDecNum());
	}
	
	
	if( this->getType() == MATH_OPERATER )
	{
		//	printf("符号 ");
//		cout<<this->FormatContent.mathOper; 
		printf("%c",this->getMathOper());
	}
	
	if( this->getType() == QUERYMEMBER )
	{
		//	printf("成员 ");
		QueryMember *temp = this->getQryMember();
		temp->_showMember();
	}

	if( this->getType() == QUERYMEMBER_UMINUS )
	{
		//	printf("成员 ");
		QueryMember *temp = this->getQryMember();
        printf("负号");
		temp->_showMember();
	}
}

calcMemFormat::~calcMemFormat()
{

}





















