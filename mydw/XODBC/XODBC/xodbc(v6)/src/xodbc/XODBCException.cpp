#include <xodbc/XODBCException.h>

namespace xodbc{

XODBCException::XODBCException()
{
	;
}
XODBCException::~XODBCException()
{
}

void XODBCException::GetErrorMessage(string &strError)
{
	strError = m_XError.GetErrorText();
}

void XODBCException::GetError(XODBCError &XError)
{
	XError.SetError(m_XError);
}
	
void XODBCException::SetError(XODBCError XError)
{
	m_XError.SetError(XError);
}

void AfxThrowXODBCException(XODBCError XError)
{
	XODBCException e;
	e.SetError(XError);
	//XError.ErrorLog();
	throw e;
}

}