// QueryCmptException.cpp: implementation of the QueryCmptException class.
//
//////////////////////////////////////////////////////////////////////

#include "./Query//QueryCmptException.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace QueryComputationMethods
{
	
QueryCmptException::QueryCmptException(string error)
:_error(error)
{

}

QueryCmptException::~QueryCmptException()
{

}


string QueryCmptException::GetError()
{
	return _error;
}

void QueryCmptException::SetError(string error)
{
	error = _error;
}

}
