#ifndef XODBCEXCEPTION_H_
#define XODBCEXCEPTION_H_

#include "XODBCError.h"

namespace xodbc{

class XODBCException
{
public:
	XODBCException();
	~XODBCException();
	void GetErrorMessage(string &strError);
	void GetError(XODBCError &XError);
	void SetError(XODBCError XError);
private:
	XODBCError m_XError;
};

void AfxThrowXODBCException(XODBCError XError);

}


#endif 