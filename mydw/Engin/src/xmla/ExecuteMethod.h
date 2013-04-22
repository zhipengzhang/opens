// ExecuteMethod.h: interface for the ExecuteMethod class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXECUTEMETHOD_H__5B61DAE5_0C18_42C0_BCD3_4628DFF08607__INCLUDED_)
#define AFX_EXECUTEMETHOD_H__5B61DAE5_0C18_42C0_BCD3_4628DFF08607__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../soap/SoapEngineMethod.h"
#include "../soap/SoapParser.h"
#include "Resultset.h"
#include "RowsetBuilder.h"

extern int deProperties(void * *mObject,const void * paramNode);
extern int seProperties(void * rs, SoapSerializer *serializer, bool bArray);

class ExecuteMethod : public SoapEngineMethod
{
public:
	ExecuteMethod(SoapServer * s):SoapEngineMethod("Execute",s){
		setBasicSeAndDeMethod();
		setUserTypeSeAndDeMethod();
	}
	virtual ~ExecuteMethod();

	int invoke(list<Param> params,void ** pResult,void ** pSZFunct,string &mURI,string &rURI);

protected:
	void setUserTypeSeAndDeMethod();
	void setBasicSeAndDeMethod();

}Execute(SoapServer::instance());

#endif // !defined(AFX_EXECUTEMETHOD_H__5B61DAE5_0C18_42C0_BCD3_4628DFF08607__INCLUDED_)
