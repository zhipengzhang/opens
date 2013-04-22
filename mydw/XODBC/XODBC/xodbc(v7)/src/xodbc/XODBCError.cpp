#include <xodbc/XODBCError.h>
#include <ctime>
#include <fstream>

namespace xodbc{

XODBCError::XODBCError()
{
	m_nErrorType = ConnectionError;
	m_strErrorText = "";
	strcpy(m_szState,"00000");
	m_lNativeError = 0;
}


XODBCError::~XODBCError()
{
	;
}


bool XODBCError::SetErrorType(XErrorType nErrorType)
{
	if( nErrorType == ConnectionError || nErrorType == StatementError)
	{
		m_nErrorType = nErrorType;;
		return true;
	}
	else
	{
		return false;
	}
}
	
void XODBCError::SetErrorText(string strErrorText)
{
	long nPos = 0;
	if( !strErrorText.empty() )
	{
		nPos = (long)strErrorText.find_last_of(']'); //Skip the ']'
		m_strErrorText.assign(strErrorText,nPos+1,strErrorText.size());
	}
	else
	{
		m_strErrorText = strErrorText;
	}
}

bool XODBCError::SetState(char szState[6])
{
	if( strlen(szState) == 5)
	{
		strcpy(m_szState,szState);
		return true;
	}
	else
	{
		return false;
	}
}
	
void XODBCError::SetNativeError(long lNativeError)
{
	m_lNativeError = lNativeError;
}
	

void XODBCError::SetError(XODBCError XError)
{
	m_nErrorType   = XError.GetErrorType();
	m_strErrorText = XError.GetErrorText();
	m_lNativeError = XError.GetNativeError();
	strcpy(m_szState,XError.GetState());
}

XErrorType XODBCError::GetErrorType()
{
	return m_nErrorType;
}
	
string XODBCError::GetErrorText()
{
	return m_strErrorText;
}

const char * XODBCError::GetState()
{
	return m_szState;
}

long XODBCError::GetNativeError()
{
	return m_lNativeError;	
}

void XODBCError::ErrorLog()
{
	time_t lTime;
	struct tm *pTime;
	string strErrorLog;
	char * str = new char[25];
	fstream f(ERROR_LOG_DIR,ios_base::out| ios_base::app);
	if( !f )
	{
		//cout<<"Failed to open the error log file"<<endl;
		f.close();
	}

	time(&lTime);
	pTime = localtime(&lTime);
	
	strErrorLog += "[";
	strErrorLog += itoa(pTime->tm_year+1900,str,10);
	strErrorLog += "-";
	strErrorLog += itoa(pTime->tm_mon+1,str,10);
	strErrorLog += "-";
	strErrorLog += itoa(pTime->tm_mday,str,10);
	strErrorLog += " ";
	strErrorLog += itoa(pTime->tm_hour,str,10);
	strErrorLog += ":";
	strErrorLog += itoa(pTime->tm_min,str,10);
	strErrorLog += ":";
	strErrorLog += itoa(pTime->tm_sec,str,10);
	strErrorLog += "]";
	if( m_nErrorType == ConnectionError)
	{
		strErrorLog += "[Connection Error][";
	}
	else
	{
		strErrorLog += "[Statement Error][";
	}
	strErrorLog += m_szState;
	strErrorLog += "]";
	strErrorLog += " ";
	strErrorLog += m_strErrorText;
	f<<strErrorLog;
	f<<"\n";
	f.close();

	delete str;
}

}


