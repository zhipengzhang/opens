#include <xodbc/XODBCDatabase.h>
#include <xodbc/XODBCRecordset.h>
#include <xodbc/XODBCDataSource.h>
namespace xodbc{
//////////////////////////////////////////////////////////
// XODBCDatabase

XODBCDatabase::XODBCDatabase()
{
	m_henv=SQL_NULL_HENV;
	m_hdbc = SQL_NULL_HDBC;
	m_hstmt = SQL_NULL_HSTMT;
	m_bOpen =false;
	m_bUpdatable = false;
	m_bTransactions = false;

	m_lLoginTimeout = DEFAULT_LOGIN_TIMEOUT;
	m_lQueryTimeout = DEFAULT_QUERY_TIMEOUT;

	m_bStripTrailingSpaces = false;
	m_bIncRecordCountOnAdd = false;
	m_bAddForUpdate = false;
	
	m_XError[0].SetErrorType(ConnectionError);
	m_XError[1].SetErrorType(StatementError);

	m_nRetcode = SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&m_henv);
	if(!Check(m_nRetcode))
	{
		XODBCError XError;
		XError.SetErrorText("分配环境句柄失败");
		AfxThrowXODBCException(XError);
	} 
	else
	{ 
		m_nRetcode =SQLSetEnvAttr(m_henv,SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC3,0);
	}
	if(!Check(m_nRetcode))
	{
		m_nRetcode =SQLSetEnvAttr(m_henv,SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC2,0);
		if(!Check(m_nRetcode))
		{
			XODBCError XError;
			XError.SetErrorText("设置环境句柄版本失败");
			AfxThrowXODBCException(XError);
		}
	}
}

XODBCDatabase::~XODBCDatabase()
{
	Free();
}

bool XODBCDatabase::Open(string strDSN, string strUser, string strPassword, long lOption )
{
	m_bUpdatable = !(lOption & openReadOnly);
	XODBC_TRY
	{
		// Allocate the HDBC and make connection
		AllocConnect(lOption);
		if(!Connect(strDSN,strUser,strPassword))
		{
			return false;
		}
	//	Verify support for required functionality and cache info
		VerifyConnect();
		GetConnectInfo();
	}
	catch(XODBCException e)
	{
		XODBCError XError;
		e.GetError(XError);
		AfxThrowXODBCException(XError);
	}
	XODBC_CATCH
	{
		Free();
		XODBCError XError;
		XError.SetErrorText("连接数据源失败");
		AfxThrowXODBCException(XError);		
	}
	m_bOpen = true;
	return true;
}

bool XODBCDatabase::OpenEx(string strDSNConnectString, long lOption)
{
	
	m_bUpdatable = !(lOption & openReadOnly);

	XODBC_TRY
	{
		m_strConnect = strDSNConnectString;
		// Allocate the HDBC and make connection
		AllocConnect(lOption);
		if(!DriverConnect(strDSNConnectString,lOption))
		{
			return false;
		}
		// Verify support for required functionality and cache info
		VerifyConnect();
		GetConnectInfo();
		
	}
	catch(XODBCException e)
	{
		XODBCError XError;
		e.GetError(XError);
		AfxThrowXODBCException(XError);
	}
	XODBC_CATCH
	{
		Free();	
		XODBCError XError;
		XError.SetErrorText("打开数据源失败");
		AfxThrowXODBCException(XError);		
	}	
	m_bOpen = true;
	return true;
}

void XODBCDatabase::Free()
{
	XODBC_TRY
	{
		if( IsOpen())
		{
			Close();
		}
		if (m_hdbc != SQL_NULL_HDBC)
		{  
			if( m_bTransactions) 
			{
				Rollback();
			}
			/*if(m_bOpen == true)
			{
				m_nRetcode = SQLDisconnect(m_hdbc);
				if(!Check(m_nRetcode))
				{
					XODBCError XError;
					XError.SetErrorText("断开连接句柄失败");
					AfxThrowXODBCException(XError);
				} 
			}*/
			m_nRetcode=SQLFreeHandle(SQL_HANDLE_DBC,m_hdbc);
		
			if(!Check(m_nRetcode))
			{
				SetLastError(ConnectionError,SQL_NULL_HSTMT);
				AfxThrowXODBCException(m_XError[0]);
			} 
			m_hdbc  = SQL_NULL_HDBC;
			m_bOpen = false;
		}
	}
	catch(XODBCException e)
	{
		XODBCError XError;
		e.GetError(XError);
		AfxThrowXODBCException(XError);
	}
	XODBC_CATCH
	{
		XODBCError XError;
		XError.SetErrorText("断开数据源连接或者释放连接句柄失败");
		AfxThrowXODBCException(XError);
	}

	XODBC_TRY
	{
		if( m_henv != SQL_NULL_HENV) 
		{
			m_nRetcode = SQLFreeHandle(SQL_HANDLE_ENV,m_henv);
			if(!Check(m_nRetcode))
			{
				XODBCError XError;
				XError.SetErrorText("释放环境句柄失败");
				AfxThrowXODBCException(XError);
			}
			m_henv=SQL_NULL_HENV;
		}
	}
	XODBC_CATCH
	{
		XODBCError XError;
		XError.SetErrorText("释放环境句柄失败");
		AfxThrowXODBCException(XError);
	}
}

void XODBCDatabase::Close()
{
	XODBC_TRY
	{
		while (!m_listRecordsets.empty())
		{
			XODBCRecordset * pSet = (XODBCRecordset *)m_listRecordsets.back();//(CRecordset*)m_listRecordsets.GetHead();
			if( pSet != NULL)
			{
				if( pSet->IsOpen() )
				{
					pSet->Close();  // will implicitly remove from list
				}
				pSet->m_pDatabase = NULL;
			}
			m_listRecordsets.pop_back();
		}
	}
	catch(XODBCException e)
	{
		XODBCError XError;
		e.GetError(XError);
		AfxThrowXODBCException(XError);
	}
	XODBC_CATCH
	{
		XODBCError XError;
		XError.SetErrorText("删除Recordset列表失败!");
		AfxThrowXODBCException(XError);
	}


	if (m_hdbc != SQL_NULL_HDBC)
	{  
		if( m_bTransactions) 
		{
			Rollback();
		}
		if(m_bOpen == true)
		{
			m_nRetcode = SQLDisconnect(m_hdbc);
			if(!Check(m_nRetcode))
			{
				XODBCError XError;
				XError.SetErrorText("断开连接句柄失败");
				AfxThrowXODBCException(XError);
			} 
		}
		/*m_nRetcode=SQLFreeHandle(SQL_HANDLE_DBC,m_hdbc);
	
		if(!Check(m_nRetcode))
		{
			SetLastError(ConnectionError,SQL_NULL_HSTMT);
			AfxThrowXODBCException(m_XError[0]);
		} 
		m_hdbc  = SQL_NULL_HDBC;*/
		m_bOpen = false;
	}
	
}
void XODBCDatabase::AllocConnect(long lOption)
{

	if (m_hdbc != SQL_NULL_HDBC)
	{
		return;
	}
	if (m_henv ==  SQL_NULL_HENV)
	{
		// need to allocate an environment for first connection
		m_nRetcode = SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&m_henv);	
		if(!Check(m_nRetcode))
		{
			XODBCError XError;
			XError.SetErrorText("分配环境句柄失败");
			AfxThrowXODBCException(XError);
		} 
		m_nRetcode =SQLSetEnvAttr(m_henv,SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC3,0);
		if(!Check(m_nRetcode))
		{
			m_nRetcode =SQLSetEnvAttr(m_henv,SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC2,0);
		}
		if(!Check(m_nRetcode))
		{
			XODBCError XError;
			XError.SetErrorText("设置环境句柄版本失败");
			AfxThrowXODBCException(XError);
		}

	}   
	m_nRetcode=SQLAllocHandle(SQL_HANDLE_DBC,m_henv,&m_hdbc);
	if (!Check(m_nRetcode))
	{
		XODBCError XError;
		XError.SetErrorText("分配连接句柄失败");
		AfxThrowXODBCException(XError);
	}

	//m_nRetcode=SQLSetConnectAttr(m_hdbc,SQL_LOGIN_TIMEOUT,(SQLPOINTER)m_lLoginTimeout,0);
	m_nRetcode=SQLSetConnectOption(m_hdbc,SQL_LOGIN_TIMEOUT,(SQLUINTEGER)m_lLoginTimeout);
	if (!Check(m_nRetcode))
	{
		XODBCError XError;
		XError.SetErrorText("设置连接超时属性失败");
		AfxThrowXODBCException(XError);
	}

	if( !m_bUpdatable )
	{
		m_nRetcode = SQLSetConnectAttr(m_hdbc,SQL_ACCESS_MODE,(SQLPOINTER)SQL_MODE_READ_ONLY,0);
		if (!Check(m_nRetcode))
		{
			XODBCError XError;
			XError.SetErrorText("设置连接只读属性失败");
			AfxThrowXODBCException(XError);
		}
	}
	// Turn on cursor lib support
	
	//*******************************************
	if (lOption & useCursorLib)
	{
		m_nRetcode = SQLSetConnectAttr(m_hdbc,SQL_ODBC_CURSORS,(SQLPOINTER)SQL_CUR_USE_ODBC,0);
		if (!Check(m_nRetcode))
		{
			XODBCError XError;
			XError.SetErrorText("设置连接光标属性失败");
			AfxThrowXODBCException(XError);
		}
	//********************************************
	
		// With cursor library added records immediately in result set
		m_bIncRecordCountOnAdd =true;
	}
}

bool XODBCDatabase::Connect(string strDSN, string strUser, string strPassword)
{
	
    m_nRetcode = SQLConnect(m_hdbc,(SQLCHAR *)strDSN.c_str(),SQL_NTS,(SQLCHAR  *)strUser.c_str(),SQL_NTS,
				(SQLCHAR *)strPassword.c_str(),SQL_NTS);

	if (m_nRetcode == SQL_NO_DATA_FOUND)
	{
		m_bOpen = false;
		Free();
		return false;
	}

	if (!Check(m_nRetcode))
	{
		m_bOpen = false;
		SetLastError(ConnectionError);
		Close();
		AfxThrowXODBCException(m_XError[0]);
	}
	m_strConnect = "DSN="+strDSN+",UID="+strUser+",PWD="+strPassword;
	return true;
}//end Connect

bool XODBCDatabase::DriverConnect(string strDSNString,long lOption)
{
	char         szConnectOutput[255];
	SQLSMALLINT  nbConnStrOut = 0;
	SQLSMALLINT  lConnectOption = SQL_DRIVER_NOPROMPT;

	if (lOption & noOdbcDialog)
	{
		lConnectOption = SQL_DRIVER_NOPROMPT;
	}
	else if (lOption & forceOdbcDialog)
	{
		lConnectOption = SQL_DRIVER_PROMPT;
	}
	m_nRetcode=SQLDriverConnect(m_hdbc,NULL,(SQLCHAR *)strDSNString.c_str(),SQL_NTS, (SQLCHAR *)szConnectOutput,255,&nbConnStrOut,lConnectOption);
/*
if (hWndTop != NULL)
		::EnableWindow(hWndTop, TRUE);
*/
	// If user hit 'Cancel'
	if (m_nRetcode == SQL_NO_DATA_FOUND)
	{
		m_bOpen = false;
		Free();
		return false;
	}
	if (!Check(m_nRetcode))
	{
		m_bOpen = false;
		SetLastError(ConnectionError);
		Close();
		AfxThrowXODBCException(m_XError[0]);
	}

	m_strConnect = szConnectOutput;
	return true;
}//end DriverConnect

void XODBCDatabase::VerifyConnect()
{
	
//  string info;
	short nResult;
	long lAPIConformance;
	m_nRetcode = SQLGetInfo(m_hdbc, SQL_ODBC_API_CONFORMANCE,
		&lAPIConformance, sizeof(lAPIConformance), &nResult);
	if (!Check(m_nRetcode))
	{
		SetLastError(ConnectionError,NULL);
		AfxThrowXODBCException(m_XError[0]);
	}
//**********************************************//
/*	if (lAPIConformance < SQL_OAC_LEVEL1)
	{
		XODBCError XError;
//		info=(string)AFX_SQL_ERROR_API_CONFORMANCE;
		
		XError.SetErrorText("error: lAPIConformance < SQL_OAC_LEVEL1");
		cout<<"!Check(m_nRetcode)333"<<endl;
		AfxThrowXODBCException(XError);
	}*/

    long lSQLConformance;
	m_nRetcode = SQLGetInfo(m_hdbc, SQL_ODBC_SQL_CONFORMANCE,&lSQLConformance, sizeof(lSQLConformance), &nResult);
	if (!Check(m_nRetcode))
	{
		SetLastError(ConnectionError,NULL);
		AfxThrowXODBCException(m_XError[0]);
	}
//********************************************//
/*	if (lSQLConformance < SQL_OSC_MINIMUM)
	{
		XODBCError XError;
	//	info=(string)AFX_SQL_ERROR_SQL_CONFORMANCE;
		XError.SetErrorText("error: lSQLConformance < SQL_OSC_MINIMUM");
		cout<<"!Check(m_nRetcode)351"<<endl;
		AfxThrowXODBCException(XError);
	}*/

}
//end VerifyConnect



void XODBCDatabase::GetConnectInfo()
{
	
	short nResult;

	// Reset the database update options
	m_lUpdateOptions = 0;

	// Check for SQLSetPos support
	unsigned long lDriverPosOperations;

    m_nRetcode = SQLGetInfo(m_hdbc, SQL_POS_OPERATIONS,
		&lDriverPosOperations, sizeof(lDriverPosOperations), &nResult);
	if (Check(m_nRetcode) &&
		(lDriverPosOperations & SQL_POS_UPDATE) &&
		(lDriverPosOperations & SQL_POS_DELETE) &&
		(lDriverPosOperations & SQL_POS_ADD))
	{
		m_lUpdateOptions |= SQL_SETPOSUPDATES;
	}

	// Check for positioned update SQL support
	unsigned long lPositionedStatements;
	m_nRetcode = SQLGetInfo(m_hdbc, SQL_POSITIONED_STATEMENTS,
		&lPositionedStatements, sizeof(lPositionedStatements),
		&nResult);
	if (Check(m_nRetcode) &&
		(lPositionedStatements & SQL_PS_POSITIONED_DELETE) &&
		(lPositionedStatements & SQL_PS_POSITIONED_UPDATE))
	{
		m_lUpdateOptions |= SQL_POSITIONEDSQL;
	}

	// Check for transaction support
	short nTxnCapable;
	m_nRetcode = SQLGetInfo(m_hdbc, SQL_TXN_CAPABLE, &nTxnCapable,
		sizeof(nTxnCapable), &nResult);
	if(Check(m_nRetcode) && nTxnCapable != SQL_TC_NONE)
	{
		m_bTransactions = true;
	}

	// Cache the effect of transactions on cursors
	m_nRetcode = SQLGetInfo(m_hdbc, SQL_CURSOR_COMMIT_BEHAVIOR,
		&m_nCursorCommitBehavior, sizeof(m_nCursorCommitBehavior),
		&nResult);
	if (!Check(m_nRetcode))
	{
		m_nCursorCommitBehavior = SQL_ERROR;
	}
	
	m_nRetcode = SQLGetInfo(m_hdbc, SQL_CURSOR_ROLLBACK_BEHAVIOR,
		&m_nCursorRollbackBehavior, sizeof(m_nCursorRollbackBehavior),
		&nResult);
	if (!Check(m_nRetcode))
	{
		m_nCursorRollbackBehavior = SQL_ERROR;
	}

	// Cache bookmark attributes
	m_nRetcode = SQLGetInfo(m_hdbc, SQL_BOOKMARK_PERSISTENCE,
		&m_lBookmarkAttributes, sizeof(m_lBookmarkAttributes),
		&nResult);
	Check(m_nRetcode);

	// Check for SQLGetData support req'd by RFX_LongBinary
	unsigned long lGetDataExtensions;
	m_nRetcode = SQLGetInfo(m_hdbc, SQL_GETDATA_EXTENSIONS,
		&lGetDataExtensions, sizeof(lGetDataExtensions),
		&nResult);
	if (!Check(m_nRetcode))
	{
		lGetDataExtensions = 0;
	}

	if (lGetDataExtensions & SQL_GD_BOUND)
	{
		m_lUpdateOptions |= SQL_GDBOUND;
	}
	if ( m_bUpdatable )
	{
		// Make sure data source is Updatable
		// 有些数据源由于用户权限问题并不支持数据更新
		char szReadOnly[10];
		m_nRetcode = SQLGetInfo(m_hdbc, SQL_DATA_SOURCE_READ_ONLY, szReadOnly, sizeof(szReadOnly), &nResult);
		if ( Check(m_nRetcode) && nResult == sizeof(char) )
		{
			m_bUpdatable = szReadOnly[0] == 'N';
		}
		else
		{
			m_bUpdatable = false;
		}
	}
	else
	{
		// Make data source is !Updatable
		SQLSetConnectOption(m_hdbc,SQL_ACCESS_MODE, SQL_MODE_READ_ONLY);
	}

	// Cache the quote char to use when constructing SQL
	// 检查驱动程序在构造SQL语句中引号是单引号还是双引号
	char szIDQuoteChar[2];
	m_nRetcode = SQLGetInfo(m_hdbc, SQL_IDENTIFIER_QUOTE_CHAR,szIDQuoteChar, sizeof(szIDQuoteChar), &nResult);
	if ( Check(m_nRetcode) && nResult == sizeof(char) )
	{
		m_szchIDQuoteChar = szIDQuoteChar[0];
	}
	else
	{
		m_szchIDQuoteChar = '\"';
	}

/*
	char  szInfo[64];
	m_nRetcode = SQLGetInfo(m_hdbc, SQL_DBMS_NAME,szInfo, sizeof(szInfo), &nResult);
	if (Check(m_nRetcode))
	{
		cout<<"DBMS Name is :  "<< szInfo<<endl;
		m_nRetcode =SQLGetInfo(m_hdbc, SQL_DBMS_VER,szInfo, sizeof(szInfo), &nResult);
		if (Check(m_nRetcode))
		{
			printf("DBMS Version is : %s",szInfo);
			cout<<endl;
		}
	}

	m_nRetcode = SQLGetInfo(m_hdbc, SQL_ODBC_VER,szInfo, sizeof(szInfo), &nResult);
	if(Check(m_nRetcode))
	{
		cout<<"ODBC Driver Manager Version is : "<<szInfo<<endl;
	}

*/
}

bool XODBCDatabase::IsOpen() const     // Database successfully opened?
{
	return m_bOpen;
}

bool XODBCDatabase::CanTransact() const
{
	return m_bTransactions;
}

bool XODBCDatabase::CanUpdate() const
{
	return m_bUpdatable;
}

const string XODBCDatabase::GetDatabaseName() 
{
	
	string strDBName;
	short nResult;

	m_nRetcode = SQLGetInfo(m_hdbc, SQL_DATABASE_NAME, NULL, 0, &nResult);
	if ( Check(m_nRetcode) )
	{
		char * pszName = new char[256];

		m_nRetcode = SQLGetInfo(m_hdbc, SQL_DATABASE_NAME, pszName,
			short(nResult + sizeof(char)), &nResult);
  
		strDBName = pszName;

		if( !Check(m_nRetcode) )
		{
			strDBName = "";
		}
		delete pszName;
	}
	return strDBName;
}

const string XODBCDatabase::GetDSName()
{
	return XODBCDataSource::GetDSNameFromDSNString(m_strConnect);
}

const string XODBCDatabase::GetConnectString() const
{
	return m_strConnect;
}

long XODBCDatabase::GetBookmarkPersistence()
{
	return  m_lBookmarkAttributes;
}

long XODBCDatabase::GetEffectCount()
{
   return m_lRowCount;
}

void XODBCDatabase::SetQueryTimeout(long lSeconds)
{
   m_lQueryTimeout = lSeconds;
}

void XODBCDatabase::SetLoginTimeout(long lSeconds)
{
	m_lLoginTimeout = lSeconds;
}

void XODBCDatabase::ExecuteSQL(string strSQL)
{
	HSTMT hstmt;
	m_nRetcode = SQLAllocHandle(SQL_HANDLE_STMT,m_hdbc,&hstmt);
	if (!Check(m_nRetcode))
	{
		SetLastError(ConnectionError);
		AfxThrowXODBCException(m_XError[0]);
	}

	XODBC_TRY
	{
		OnSetOptions(hstmt);
		// Give derived CDatabase classes option to use parameters
		BindParameters(hstmt);
        m_lRowCount = -1;
	
		m_nRetcode = SQLExecDirect(hstmt,(SQLCHAR *)strSQL.c_str(), SQL_NTS);

		if (!Check(m_nRetcode))
		{
			SetLastError(StatementError,hstmt);
			AfxThrowXODBCException(m_XError[1]);
		}
	
		m_nRetcode = SQLRowCount(hstmt,&m_lRowCount);  
		if (!Check(m_nRetcode))
		{
			SetLastError(StatementError,hstmt);
			AfxThrowXODBCException(m_XError[1]);
		}
		short nResultColumns;
		do
		{
			m_nRetcode = SQLNumResultCols(hstmt, &nResultColumns);
			if(!Check(m_nRetcode))
			{
				SetLastError(StatementError,hstmt);
				AfxThrowXODBCException(m_XError[1]);
			}
			if (nResultColumns != 0)
			{
				do
				{
					m_nRetcode = SQLFetch(hstmt);
					if(!Check(m_nRetcode))
					{
						SetLastError(StatementError,hstmt);
						AfxThrowXODBCException(m_XError[1]);
					}

				} while (m_nRetcode != SQL_NO_DATA_FOUND);
			}

			m_nRetcode = SQLMoreResults(hstmt);
			if(!Check(m_nRetcode))
			{
				SetLastError(StatementError,hstmt);
				AfxThrowXODBCException(m_XError[1]);
			}

		} while (m_nRetcode != SQL_NO_DATA_FOUND);
	}
	catch(XODBCException e)
	{
		SQLCancel(hstmt);
		m_nRetcode = SQLFreeStmt(hstmt, SQL_DROP);	
		if(!Check(m_nRetcode))
		{
			SetLastError(StatementError,hstmt);
			AfxThrowXODBCException(m_XError[1]);
		}
		if( m_bTransactions)
		{
			Rollback();
		}
		XODBCError XError;
		e.GetError(XError);
		AfxThrowXODBCException(XError);
	}
	XODBC_CATCH
	{
		SQLCancel(hstmt);
		m_nRetcode = SQLFreeStmt(hstmt, SQL_DROP);	
		if(!Check(m_nRetcode))
		{
			SetLastError(StatementError,hstmt);
			AfxThrowXODBCException(m_XError[1]);
		}
		if( m_bTransactions)
		{
			Rollback();
		}
		XODBCError XError;
		XError.SetErrorText("执行SQL语句错误");
		AfxThrowXODBCException(XError);
	}
	
	m_nRetcode = SQLFreeStmt(hstmt, SQL_DROP);
	if(!Check(m_nRetcode))
	{	
		SetLastError(StatementError,hstmt);
		AfxThrowXODBCException(m_XError[1]);
	}

}//end ExecuteSQL


void XODBCDatabase::OnSetOptions(HSTMT hstmt)
{
	if (m_lQueryTimeout != -1)
	{
		// Attempt to set query timeout.  Ignore failure
		m_nRetcode = SQLSetStmtOption(hstmt, SQL_QUERY_TIMEOUT,m_lQueryTimeout);
		if (!Check( m_nRetcode))
		{// don't attempt it again
			m_lQueryTimeout = -1;
		}
	}
}

void XODBCDatabase::BindParameters(HSTMT /* hstmt */ )
{
	;// Must override and call SQLBindParameter directly
}



bool XODBCDatabase::BeginTrans()
{
	if (!m_bTransactions)
	{
		return false;
	}
	// Only 1 level of transactions supported
	m_nRetcode = SQLSetConnectOption(m_hdbc, SQL_AUTOCOMMIT,SQL_AUTOCOMMIT_OFF);
	return Check(m_nRetcode);
}

bool XODBCDatabase::CommitTrans()
{
	if (!m_bTransactions)
	{
		return false;
	}
	// BeginTrans must be called first
	
    m_nRetcode = SQLTransact(m_henv, m_hdbc, SQL_COMMIT);
	bool bSuccess = Check(m_nRetcode);

	// Turn back on auto commit
	m_nRetcode = SQLSetConnectOption(m_hdbc, SQL_AUTOCOMMIT,SQL_AUTOCOMMIT_ON);

	return bSuccess;
}

bool XODBCDatabase::Rollback()
{
	
	if (!m_bTransactions)
	{
		return false;
	}

	// BeginTrans must be called first
    m_nRetcode = SQLTransact(m_henv, m_hdbc, SQL_ROLLBACK);
	bool bSuccess = Check(m_nRetcode);

	// Turn back on auto commit
	m_nRetcode = SQLSetConnectOption(m_hdbc, SQL_AUTOCOMMIT,SQL_AUTOCOMMIT_ON);
	return bSuccess;
}


bool XODBCDatabase::Check(SQLRETURN nRetcode) const
{
	switch(nRetcode)
	{
	case SQL_SUCCESS_WITH_INFO:
	case SQL_SUCCESS:
	case SQL_NO_DATA_FOUND:
		return true;
	default:
		return false;
	}
}


void XODBCDatabase::GetLastError(XErrorType nErrorType, XODBCError &XError)
{
	switch(nErrorType)
	{
		case ConnectionError:
			XError.SetError(m_XError[0]);
			break;
		case StatementError:
			XError.SetError(m_XError[1]);
			break;
		default:
			break;
	}
}


bool XODBCDatabase::SetLastError(XErrorType nErrorType, SQLHSTMT hstmt)
{
	char     * lpszError = new char[256];
	char       szState[6];
	long       lNativeError;
	SQLRETURN  retcode;
	if( hstmt != SQL_NULL_HSTMT)
	{
		retcode = SQLError(NULL,NULL,hstmt,(unsigned char*)szState,&lNativeError,(unsigned char*)lpszError,256,0);
	}
	else
	{
		if(nErrorType ==  ConnectionError)
		{
			retcode = SQLError(NULL,m_hdbc,NULL,(unsigned char*)szState,&lNativeError,(unsigned char*)lpszError,256,0);
		}
		else
		{
			retcode = SQLError(NULL,NULL,m_hstmt,(unsigned char*)szState,&lNativeError,(unsigned char*)lpszError,256,0);
		}
	}
	if (retcode != SQL_SUCCESS && retcode !=SQL_SUCCESS_WITH_INFO)
	{
		delete lpszError;
		return false;
	}
	switch(nErrorType)
	{
		case ConnectionError:
			m_XError[0].SetErrorText((string)lpszError);
			m_XError[0].SetState(szState);
			m_XError[0].SetNativeError(lNativeError);
			break;
		case StatementError:
			m_XError[1].SetErrorText((string)lpszError);
			m_XError[1].SetState(szState);
			m_XError[1].SetNativeError(lNativeError);
			break;
		default:
			break;
	}
	delete lpszError;
	return true;

}

}


