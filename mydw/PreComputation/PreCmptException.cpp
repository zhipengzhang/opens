// PreCmptException.cpp: implementation of the PreCmptException class.
//
//////////////////////////////////////////////////////////////////////

#include "./PreComputation/PreCmptException.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace PreCmpt
{


PreCmptException::PreCmptException( string error )
:_error(error)
{

}

PreCmptException::~PreCmptException()
{

}

void PreCmptException::SetError( string error )
{
	_error = error;
}

string PreCmptException::GetError()
{
	return _error;
}

}