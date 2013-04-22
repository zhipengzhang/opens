// QueryCmptException.h: interface for the QueryCmptException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUERYCMPTEXCEPTION_H__815D709D_0296_497C_8A85_0E97E6AEC224__INCLUDED_)
#define AFX_QUERYCMPTEXCEPTION_H__815D709D_0296_497C_8A85_0E97E6AEC224__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Common.h"

namespace QueryComputationMethods
{

class QueryCmptException  
{
public:
	QueryCmptException(string error);
	virtual ~QueryCmptException();

	string GetError();
	void SetError(string error);
private:
	string _error;
};


}

#endif // !defined(AFX_QUERYCMPTEXCEPTION_H__815D709D_0296_497C_8A85_0E97E6AEC224__INCLUDED_)
