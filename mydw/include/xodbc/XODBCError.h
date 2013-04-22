#ifndef XODBCERROR_H_
#define XODBCERROR_H_

#include "XODBCGlobal.h"

namespace xodbc{

const char ERROR_LOG_DIR[] = "./XODBCERROR.LOG";

enum XErrorType
{
	ConnectionError = 0, // ¡¨Ω”¥ÌŒÛ
	StatementError  = 1, // ”Ôæ‰÷¥––¥ÌŒÛ
};

class XODBCError
{

//Constructor
public:
	XODBCError();
	~XODBCError();

//Attribute
private:
	XErrorType m_nErrorType;
	string     m_strErrorText;
	char       m_szState[6];
	long        m_lNativeError;

//Operations
public:
	bool SetErrorType(XErrorType nErrorType);
	void SetErrorText(string strErrorText);
	bool SetState(char szState[6]);
	void SetNativeError(long lNativeError);
    void SetError(XODBCError XError);

	XErrorType   GetErrorType();
	string       GetErrorText();
	const char * GetState();
	long         GetNativeError();

	void ErrorLog();

};

}

#endif