// FunParam.cpp: implementation of the FunParam class.
//
//////////////////////////////////////////////////////////////////////

#include "MdxParser/FunParam.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FunParam::FunParam()
{
	hasIntParam = false;
	hasStrParam = false;
}

void FunParam::setIntParam(int num)
{
	int_Param = num ;
}

void FunParam::setStrParam(char *str)
{
	str_Param = str;
}

int FunParam::getIntParam()
{
	return int_Param;
}

char* FunParam::getStrParam()
{
	return str_Param;
}

void FunParam::setHasIntParam(bool num)
{
	hasIntParam = num;
}

void FunParam::setHasStrParam(bool str)
{
	hasStrParam = str;
}

bool FunParam::getHasIntParam()
{
	return hasIntParam ;
}

bool FunParam::getHasStrParam()
{
	return hasStrParam ;
}

FunParam::~FunParam()
{

}
