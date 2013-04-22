// PreComputeMethod.h: interface for the PreComputeMethod class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRECOMPUTEMETHOD_H__B2F1F929_C011_49D5_8045_F817AB1C7FCA__INCLUDED_)
#define AFX_PRECOMPUTEMETHOD_H__B2F1F929_C011_49D5_8045_F817AB1C7FCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../soap/SoapEngineMethod.h"

class PreComputeMethod: public SoapEngineMethod
{
public:
	PreComputeMethod(SoapServer * s):SoapEngineMethod("preCompute",s){
		setBasicSeAndDeMethod();
		setUserTypeSeAndDeMethod();
	}
	virtual ~PreComputeMethod();


	int invoke(list<Param> params,void ** pResult,void ** pSZFunct,string &mURI,string &rURI);

protected:
	void setUserTypeSeAndDeMethod();
	void setBasicSeAndDeMethod();

} PreCompute(SoapServer::instance());


#endif // !defined(AFX_PRECOMPUTEMETHOD_H__B2F1F929_C011_49D5_8045_F817AB1C7FCA__INCLUDED_)
