// FunParam.h: interface for the FunParam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FUNPARAM_H__E7F6B83F_C24E_47B4_860C_6CD71A8185DA__INCLUDED_)
#define AFX_FUNPARAM_H__E7F6B83F_C24E_47B4_860C_6CD71A8185DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class FunParam  
{
public:
	int int_Param;
	char * str_Param;
	bool hasIntParam;
	bool hasStrParam;

	void setIntParam(int num);
	void setStrParam(char *str);
	void setHasIntParam(bool num);
	void setHasStrParam(bool str);

	int getIntParam();
	char* getStrParam();
	bool getHasIntParam();
	bool getHasStrParam();

	FunParam();
	virtual ~FunParam();

};

#endif // !defined(AFX_FUNPARAM_H__E7F6B83F_C24E_47B4_860C_6CD71A8185DA__INCLUDED_)
