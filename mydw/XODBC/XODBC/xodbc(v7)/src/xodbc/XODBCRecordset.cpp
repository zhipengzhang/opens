#include <xodbc/XODBCRecordset.h>

namespace xodbc{
//////////////////////////////////////////////////////////
// XFieldInfo

XFieldInfo::XFieldInfo()
{
	;
}

XFieldInfo::~XFieldInfo()
{
	;
}

void XFieldInfo::SetFieldInfo(XFieldInfo fieldInfo)
{
	m_nForeignKey    = fieldInfo.m_nForeignKey;
	m_nLength        = fieldInfo.m_nLength;
	m_nNullability   = fieldInfo.m_nNullability;
	m_lPrecision     = fieldInfo.m_lPrecision;
	m_nPrimaryKey    = fieldInfo.m_nPrimaryKey;
	m_nScale         = fieldInfo.m_nScale;
	m_nSQLType       = fieldInfo.m_nSQLType;
	m_strName        = fieldInfo.m_strName;
}

//////////////////////////////////////////////////////////
//XParamInfo

XParamInfo::XParamInfo()
{
	;
}

XParamInfo::~XParamInfo()
{
	;
}

//////////////////////////////////////////////////////////
//XSTRING

XSTRING::XSTRING()
{
	m_strBuffer = NULL;
	m_lLength = 0;
}



bool XSTRING::AllocBuffer(long lLength)
{
	if( lLength <= 0 )
	{
		return false;
	}
	if( m_strBuffer != NULL)
	{
		delete m_strBuffer;
		m_strBuffer = NULL;
		m_lLength = 0;
	}
	if( (m_strBuffer = new char[lLength]) != NULL)
	{
		m_lLength = lLength;
		return true;
	}
	else
	{
		return false;
	}
}

char * XSTRING::GetBuffer()
{
	return m_strBuffer;
}

long XSTRING::GetLength()
{
	return m_lLength;
}

void XSTRING::Free()
{
	if( m_strBuffer != NULL)
	{
		delete m_strBuffer;
		m_strBuffer = NULL;
		m_lLength = 0;
	}
}


//////////////////////////////////////////////////////////
//XWSTRING

XWSTRING::XWSTRING()
{
	m_wstrBuffer = NULL;
	m_lLength = 0;
}



bool XWSTRING::AllocBuffer(long lLength)
{
	if( lLength <= 0 )
	{
		return false;
	}
	if( m_wstrBuffer != NULL)
	{
		delete m_wstrBuffer;
		m_wstrBuffer = NULL;
		m_lLength = 0;
	}
	if( (m_wstrBuffer = new wchar_t[lLength]) != NULL)
	{
		m_lLength = lLength;
		return true;
	}
	else
	{
		return false;
	}
}

wchar_t * XWSTRING::GetBuffer()
{
	return m_wstrBuffer;
}

long XWSTRING::GetLength()
{
	return m_lLength;
}

void XWSTRING::Free()
{
	if( m_wstrBuffer != NULL)
	{
		delete m_wstrBuffer;
		m_wstrBuffer = NULL;
		m_lLength = 0;
	}
}


//////////////////////////////////////////////////////////
//XBINARY

XBINARY::XBINARY()
{
	m_lDataLength = 0; 
	m_pData       = NULL;
}

bool XBINARY::AllocBuffer(long lDataLength)
{
	if( lDataLength <= 0 )
	{
		return false;
	}
	if( m_pData != NULL)
	{
		free(m_pData);
		m_pData = NULL;
		m_lDataLength = 0;
	}
	if( (m_pData = malloc(lDataLength)) !=NULL)
	{
		m_lDataLength = lDataLength;
		/*long * p = (long *)m_pData;
		* p = 0x0;*/
		return true;
	}
	else
	{
		return false;
	}

}

void * XBINARY::GetBuffer()
{
	return m_pData;
}

long XBINARY::GetLength()
{
	return m_lDataLength;
}

void XBINARY::Free()
{
	if( m_pData != NULL)
	{
		free(m_pData);
		m_pData = NULL;
		m_lDataLength = 0;
	}
}

//////////////////////////////////////////////////////////
//XDBVariant

XDBVariant::XDBVariant()
{
	m_nType		= XDBVT_NULL;
	m_bNull		= false;
	m_stringVal = "";
	m_wstringVal= L"";
	m_binaryVal;
}


XDBVariant::~XDBVariant()
{
	Clear();
}


string XDBVariant::AsString()
{
	string strValue;
	char * pszTemp = new char[256];
	char * pTemp;
	switch(m_nType)
	{
	case XDBVT_BOOL:
			itoa(m_boolVal,pszTemp,10);
			strValue = pszTemp;
			break;
		case XDBVT_UCHAR:
			itoa((int)m_chVal,pszTemp,10);
			strValue = pszTemp;
			break;

		case XDBVT_SHORT:
			itoa((int)m_shVal,pszTemp,10);
			strValue = pszTemp;
			break;

		case XDBVT_LONG:
			ltoa(m_lVal,pszTemp,10);
			strValue = pszTemp;
			break;

		case XDBVT_SINGLE:
			_gcvt(m_fltVal,54,pszTemp);
			strValue = pszTemp;
			break;

		case XDBVT_DOUBLE:
			_gcvt(m_dblVal,54,pszTemp);
			strValue = pszTemp;
			break;

		case XDBVT_LONGLONG:
			_i64toa(m_llVal,pszTemp,10);
			strValue = pszTemp;
			break;

		case XDBVT_DATE:
			strValue  = itoa(m_dateVal.year,pszTemp,10);
			strValue += "-";
			strValue += itoa(m_dateVal.month,pszTemp,10);
			strValue += "-";
		    strValue += itoa(m_dateVal.day,pszTemp,10);
			break;

		case XDBVT_TIME:
			strValue  = itoa(m_timeVal.hour,pszTemp,10);
			strValue += ":";
			strValue += itoa(m_timeVal.minute,pszTemp,10);
			strValue += ":";
			strValue += itoa(m_timeVal.second,pszTemp,10);
			break;

		case XDBVT_TIMESTAMP:
			strValue  = itoa(m_tsVal.year,pszTemp,10);
			strValue += "-";
			strValue += itoa(m_tsVal.month,pszTemp,10);
			strValue += "-";
			strValue += itoa(m_tsVal.day,pszTemp,10);
			strValue += " ";
			strValue += itoa(m_tsVal.hour,pszTemp,10);
			strValue += ":";
			strValue += itoa(m_tsVal.minute,pszTemp,10);
			strValue += ":";
			strValue += itoa(m_tsVal.second,pszTemp,10);
			strValue += ".";
			strValue += itoa(m_tsVal.fraction,pszTemp,10);
			break;

		case XDBVT_STRING:
			strValue = m_stringVal;
			break;

		case XDBVT_WSTRING:
			//_wsetlocale( LC_CTYPE,L"");
			//unicode编码转换为多字节
			setlocale(LC_ALL, "Chinese");
			//setlocale(LC_ALL, ".936");
			pTemp = new char[(m_wstringVal.length() + 1) * 2];
			wcstombs(pTemp, m_wstringVal.c_str() ,m_wstringVal.length() * 2);
			pTemp[m_wstringVal.length() * 2] = '\0';
			strValue = pTemp;
			delete pTemp;
			break;

		case XDBVT_BINARY: //    二进制转成ANSI字符串可能会出现乱码    //
			pTemp = new char[m_binaryVal.GetLength() + 1];
			memcpy((char *)pTemp,m_binaryVal.GetBuffer(),m_binaryVal.GetLength());
			strcpy( (pTemp + m_binaryVal.GetLength()) ,"\0");
			strValue = pTemp;
			delete pTemp;
			break;
		default:
			strValue = "\0";
			break;
	}
	delete pszTemp;
	return strValue;
}

wstring XDBVariant::AsWString()
{
	wstring wstrValue;
	wchar_t * pwszTemp = new wchar_t[256];
	wchar_t * pTemp;
	char    * pszTemp = new char[256];   
	switch(m_nType)
	{
	case XDBVT_BOOL:
			_itow(m_boolVal,pwszTemp,10);
			wstrValue = pwszTemp;
			break;
		case XDBVT_UCHAR:
			_itow((int)m_chVal,pwszTemp,10);
			wstrValue = pwszTemp;
			break;

		case XDBVT_SHORT:
			_itow((int)m_shVal,pwszTemp,10);
			wstrValue = pwszTemp;
			break;

		case XDBVT_LONG:
			_ltow(m_lVal,pwszTemp,10);
			wstrValue = pwszTemp;
			break;

		case XDBVT_SINGLE:
			_gcvt(m_fltVal,54,pszTemp);
			mbstowcs(pwszTemp,(const char *)pszTemp,strlen(pszTemp));
			pwszTemp[strlen(pszTemp)] = L'\0';
			wstrValue = pwszTemp;
			break;

		case XDBVT_DOUBLE:
			_gcvt(m_dblVal,54,pszTemp);
			mbstowcs(pwszTemp,pszTemp,strlen(pszTemp));
			pwszTemp[strlen(pszTemp)] = L'\0';
			wstrValue = pwszTemp;
			break;

		case XDBVT_LONGLONG:
			_i64tow(m_llVal,pwszTemp,10);
			wstrValue = pwszTemp;
			break;

		case XDBVT_DATE:
			wstrValue  = _itow(m_dateVal.year,pwszTemp,10);
			wstrValue += L"-";
			wstrValue += _itow(m_dateVal.month,pwszTemp,10);
			wstrValue += L"-";
		    wstrValue += _itow(m_dateVal.day,pwszTemp,10);
			break;

		case XDBVT_TIME:
			wstrValue  = _itow(m_timeVal.hour,pwszTemp,10);
			wstrValue += L":";
			wstrValue += _itow(m_timeVal.minute,pwszTemp,10);
			wstrValue += L":";
			wstrValue += _itow(m_timeVal.second,pwszTemp,10);
			break;

		case XDBVT_TIMESTAMP:
			wstrValue  = _itow(m_tsVal.year,pwszTemp,10);
			wstrValue += L"-";
			wstrValue += _itow(m_tsVal.month,pwszTemp,10);
			wstrValue += L"-";
			wstrValue += _itow(m_tsVal.day,pwszTemp,10);
			wstrValue += L" ";
			wstrValue += _itow(m_tsVal.hour,pwszTemp,10);
			wstrValue += L":";
			wstrValue += _itow(m_tsVal.minute,pwszTemp,10);
			wstrValue += L":";
			wstrValue += _itow(m_tsVal.second,pwszTemp,10);
			wstrValue += L".";
			wstrValue += _itow(m_tsVal.fraction,pwszTemp,10);
			break;

		case XDBVT_STRING:
			//setlocale(LC_CTYPE, ""); 
			//多字节转换为unicode编码
			//setlocale(LC_ALL, ".936");
			setlocale(LC_ALL, "Chinese");
			pTemp = new wchar_t[m_stringVal.length() + 1];
			mbstowcs(pTemp,m_stringVal.c_str(),m_stringVal.length());
			pTemp[m_stringVal.length()] = L'\0';
			wstrValue = pTemp;
			delete pTemp;
			break;

		case XDBVT_WSTRING:
			wstrValue = m_wstringVal.c_str();
			break;

		case XDBVT_BINARY:   // 二进制转成UNICODE字符串可能会出现乱码 //
			pTemp = new wchar_t[m_binaryVal.GetLength() + 1];
			memcpy((wchar_t *)pTemp,m_binaryVal.GetBuffer(),m_binaryVal.GetLength());
			wcscpy((pTemp + m_binaryVal.GetLength()) ,L"\0");
			wstrValue = pTemp;
			delete pTemp;
			break;
		default:
			wstrValue = L"\0";
			break;
	}
	delete pwszTemp;
	delete pszTemp;
	return wstrValue;
}

void XDBVariant::Clear()
{
	m_stringVal  = "";
	m_wstringVal = L"";
	m_binaryVal.Free();
	m_nType = XDBVT_NULL;
	m_bNull = false;
}

//////////////////////////////////////////////////////////
//XODBCVariant
XODBCVariant::XODBCVariant()
{
	m_nType = XDBVT_NULL;
}


XODBCVariant::~XODBCVariant()
{
	//Clear();
}


void XODBCVariant::SetXDBVariant(XDBVariant &varValue ,long lLength)
{
	varValue.Clear();
	varValue.m_nType = m_nType;
	if( lLength == -1)
	{
		varValue.m_bNull = true;
	}
	switch(m_nType)
	{
	case XDBVT_BOOL:
			varValue.m_boolVal = * m_pboolVal;
			break;

		case XDBVT_UCHAR:
			varValue.m_chVal =  *m_pchVal;
			break;

		case XDBVT_SHORT:
			varValue.m_shVal =  *m_pshVal;
			break;

		case XDBVT_LONG:
			varValue.m_lVal = *m_plVal;
			break;

		case XDBVT_SINGLE:
			varValue.m_fltVal = *m_pfltVal;
			break;

		case XDBVT_DOUBLE:
			varValue.m_dblVal = *m_pdblVal;
			break;

		case XDBVT_LONGLONG:
			varValue.m_llVal = *m_pllVal;
			break;

		case XDBVT_DATE:
			if( !varValue.m_bNull)
			{
				varValue.m_dateVal.year  = m_pdateVal->year;
				varValue.m_dateVal.month = m_pdateVal->month;
				varValue.m_dateVal.day   = m_pdateVal->day;
			}
			else
			{
				varValue.m_dateVal.year  = 0;
				varValue.m_dateVal.month = 0;
				varValue.m_dateVal.day  = 0;
			}
			break;

		case XDBVT_TIME:
			if( !varValue.m_bNull )
			{
				varValue.m_timeVal.hour   = m_ptimeVal->hour;
				varValue.m_timeVal.minute = m_ptimeVal->minute;
				varValue.m_timeVal.second = m_ptimeVal->second;
			}
			else
			{
				varValue.m_timeVal.hour   = 0;
				varValue.m_timeVal.minute = 0;
				varValue.m_timeVal.second = 0;
			}
			break;

		case XDBVT_TIMESTAMP:
			if( !varValue.m_bNull)
			{
				varValue.m_tsVal.year     = m_ptsVal->year;
				varValue.m_tsVal.month    = m_ptsVal->month;
				varValue.m_tsVal.day      = m_ptsVal->day; 
				varValue.m_tsVal.hour     = m_ptsVal->hour;
				varValue.m_tsVal.minute   = m_ptsVal->minute;
				varValue.m_tsVal.second   = m_ptsVal->second;
				varValue.m_tsVal.fraction = m_ptsVal->fraction; 
			}
			else
			{
				varValue.m_tsVal.year     = 0;
				varValue.m_tsVal.month    = 0;
				varValue.m_tsVal.day      = 0; 
				varValue.m_tsVal.hour     = 0;
				varValue.m_tsVal.minute   = 0;
				varValue.m_tsVal.second   = 0;
				varValue.m_tsVal.fraction = 0; 
			}
			break;

		case XDBVT_STRING:
			if( !varValue.m_bNull)
			{
				varValue.m_stringVal = (string)m_pstringVal->GetBuffer();
			}
			else
			{
				varValue.m_stringVal = (string)"";	
			}
			break;

		case XDBVT_WSTRING:
			if( !varValue.m_bNull)
			{
				varValue.m_wstringVal = (wstring)m_pwstringVal->GetBuffer();
			}
			else
			{
				varValue.m_wstringVal = L"";	
			}
			break;

		case XDBVT_BINARY:
			if( lLength >= 8001 )
			{ 
				lLength = 8001;
			}
			else if( lLength <= 0 )
			{
				lLength = 1;
			}
			if( !varValue.m_bNull )
			{
				if( !varValue.m_binaryVal.AllocBuffer(lLength))
				{
					XODBCError error;
					error.SetErrorText("字段绑定值在为二进制分配内存时失败");
					AfxThrowXODBCException(error);
				}
				memcpy(varValue.m_binaryVal.GetBuffer(),m_pbinaryVal->GetBuffer(),lLength);	
			}
			else
			{
				if( !varValue.m_binaryVal.AllocBuffer(1))
				{
					XODBCError error;
					error.SetErrorText("字段绑定值在为二进制分配内存时失败");
					AfxThrowXODBCException(error);
				}
				//memcpy(varValue.m_pbinaryVal->GetBuffer(),0x01,1);	
			}

			break;
		default:
			break;
		}
}

bool XODBCVariant::SetValue(XDBVariant varValue)
{
	switch(m_nType)
	{
	case XDBVT_BOOL:
		*m_pboolVal = varValue.m_boolVal;
		break;

	case XDBVT_UCHAR:
		*m_pchVal = varValue.m_chVal ;
		break;

	case XDBVT_SHORT:
		*m_pshVal = varValue.m_shVal ;
		break;

	case XDBVT_LONG:
		*m_plVal = varValue.m_lVal ;
		break;

	case XDBVT_SINGLE:
	    *m_pfltVal = varValue.m_fltVal ;
		break;

	case XDBVT_DOUBLE:
		*m_pdblVal = varValue.m_dblVal ;
		break;

	case XDBVT_LONGLONG:
		*m_pllVal = varValue.m_llVal ;
		break;

	case XDBVT_DATE:
		m_pdateVal->year  = varValue.m_dateVal.year ;
		m_pdateVal->month = varValue.m_dateVal.month;
		m_pdateVal->day   = varValue.m_dateVal.day;
		
		break;

	case XDBVT_TIME:
		m_ptimeVal->hour   = varValue.m_timeVal.hour;
		m_ptimeVal->minute = varValue.m_timeVal.minute;
		m_ptimeVal->second = varValue.m_timeVal.second;
		
		break;

	case XDBVT_TIMESTAMP:
		m_ptsVal->year     = varValue.m_tsVal.year;
		m_ptsVal->month    = varValue.m_tsVal.month;
		m_ptsVal->day      = varValue.m_tsVal.day; 
		m_ptsVal->hour     = varValue.m_tsVal.hour;
		m_ptsVal->minute   = varValue.m_tsVal.minute;
		m_ptsVal->second   = varValue.m_tsVal.second;
		m_ptsVal->fraction = varValue.m_tsVal.fraction; 
	
		break;

	case XDBVT_STRING:
		if( (long)varValue.m_stringVal.length() >= m_pstringVal->GetLength())
		{
			return false;
		}

		try
		{
			strcpy( m_pstringVal->GetBuffer(), varValue.m_stringVal.c_str() );
		}
		catch (...)
		{
			XODBCError error;
			error.SetErrorText("复制ANSII字符串值失败!");
			AfxThrowXODBCException(error);
		}
		
		
		break;

	case XDBVT_WSTRING:
	
		if( (long)varValue.m_wstringVal.length() >= m_pwstringVal->GetLength())
		{
			return false;
		}
		try
		{
			WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE),varValue.m_wstringVal.c_str(),(DWORD)wcslen(varValue.m_wstringVal.c_str()), 0,NULL); 
			wcscpy( m_pwstringVal->GetBuffer(), varValue.m_wstringVal.c_str());
			WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE),m_pwstringVal->GetBuffer(),(DWORD)wcslen(m_pwstringVal->GetBuffer()), 0,NULL); 
		}
		catch (...)
		{
			XODBCError error;
			error.SetErrorText("复制Unicode字符串值失败!");
			AfxThrowXODBCException(error);
		}
        
		break;

	case XDBVT_BINARY:
	
		if( varValue.m_binaryVal.GetLength() > m_pbinaryVal->GetLength())
		{
			return false;
		}
        try
        {
			memcpy( m_pbinaryVal->GetBuffer(),varValue.m_binaryVal.GetBuffer(),varValue.m_binaryVal.GetLength());	
        }
        catch ( ... )
        {
        	XODBCError error;
			error.SetErrorText("复制二进制值失败!");
			AfxThrowXODBCException(error);
        }
		break;
	default:
		break;
	}
	return true;
}

void XODBCVariant::Clear()
{
	switch(m_nType)
	{
	case XDBVT_BOOL :   
		if( this->m_pboolVal != NULL)
		{
			delete this->m_pboolVal;
			this->m_pboolVal = NULL;
		}
		break;
	case XDBVT_UCHAR:
		if( this->m_pchVal != NULL)
		{
			delete this->m_pchVal;
			this->m_pchVal = NULL;
		}
		break;
	case XDBVT_SHORT:
		if( this->m_pshVal != NULL)
		{
			delete this->m_pshVal;
			this->m_pshVal = NULL;
		}
		break;
	case XDBVT_LONG:
		if( this->m_plVal != NULL)
		{
			delete this->m_plVal;
			this->m_plVal = NULL;
		}
		break;
	case XDBVT_SINGLE:        
		if( this->m_pfltVal != NULL)
		{
			delete this->m_pfltVal;
			this->m_pfltVal = NULL;
		}
		break;
	case XDBVT_DOUBLE:
		if( this->m_pdblVal != NULL)
		{
			delete this->m_pdblVal;
			this->m_pdblVal = NULL;
		}
	case XDBVT_LONGLONG: 
		if( this->m_pllVal != NULL)
		{
			delete this->m_pllVal;
			this->m_pllVal = NULL;
		}
		break;
	case XDBVT_DATE:
		if( this->m_pdateVal != NULL)
		{
			delete this->m_pdateVal;
			this->m_pdateVal = NULL;
		}
		break;
	case XDBVT_TIME:
		if( this->m_ptimeVal != NULL)
		{
			delete this->m_ptimeVal;
			this->m_ptimeVal = NULL;
		}
		break;
	case XDBVT_TIMESTAMP:
		if( this->m_ptsVal != NULL)
		{
			delete this->m_ptsVal;
			this->m_ptsVal = NULL;
		}
		break;
	case XDBVT_STRING:
		if( this->m_pstringVal != NULL)
		{
			this->m_pstringVal->Free();
			delete this->m_pstringVal;
			this->m_pstringVal = NULL;
		}
		break;
	case XDBVT_WSTRING:
		if( this->m_pwstringVal != NULL)
		{
			this->m_pwstringVal->Free();
			delete this->m_pwstringVal;
			this->m_pwstringVal = NULL;
		}
		break;
	case XDBVT_BINARY:
		if( this->m_pbinaryVal != NULL)
		{
			this->m_pbinaryVal->Free();
			delete this->m_pbinaryVal;
			this->m_pbinaryVal = NULL;
		}
		break;
	default:
		break;
	}
	m_nType = XDBVT_NULL;
}


//////////////////////////////////////////////////////////
//XODBCRecordset

XODBCRecordset::XODBCRecordset(XODBCDatabase * pDatabase)
{

	//ASSERT(pDatabase == NULL || AfxIsValidAddress(pDatabase, sizeof(CDatabase)));
	Initiate();
	if ( pDatabase != NULL)
	{  
		XODBC_TRY	  
		{
			m_pDatabase = pDatabase;
			m_nRetcode = SQLAllocStmt(m_pDatabase->m_hdbc, &m_hstmt);

			if (!Check(m_nRetcode))
			{
				SetLastError( ConnectionError) ;
				AfxThrowXODBCException( m_XError[1] ) ;
			}
			XODBC_TRY
			{
				m_pDatabase->m_listRecordsets.push_back(this);
			}
			XODBC_CATCH
			{
				XODBCError XError;
				XError.SetErrorText("添加Recordset指针到Database的指针链表时发生错误");
				AfxThrowXODBCException(XError);
			}
		}
			
		XODBC_CATCH
		{
			XODBCError XError;
			XError.SetErrorText("分配语句句柄出错");
			AfxThrowXODBCException(XError);
		}
		
	}
	else
	{
		XODBCError XError;
		XError.SetErrorText("无效的XDatabase指针!");
		AfxThrowXODBCException(XError);
	}
}
	
XODBCRecordset::XODBCRecordset(string strDSN, string strUser, string strPassword,long  lOption)
{
	Initiate();
	m_pDatabase = new XODBCDatabase();
	if( m_pDatabase != NULL )
	{
		m_bRecordsetDb = true;
		XODBC_TRY
		{
			if( m_pDatabase->Open(strDSN, strUser,strPassword, lOption))
			{
				m_nRetcode = SQLAllocStmt(m_pDatabase->m_hdbc, &m_hstmt);
				if (!Check(m_nRetcode))
				{
					SetLastError( ConnectionError) ;
					AfxThrowXODBCException( m_XError[1] ) ;
				}
			}
		}
		catch(XODBCException e)
		{
			delete m_pDatabase;
			XODBCError XError;
			e.GetError(XError);
			AfxThrowXODBCException(XError);
		}
		XODBC_CATCH
		{
			XODBCError XError;
			XError.SetErrorText("创建XODBCRecordset对象失败");
			AfxThrowXODBCException(XError);
		}
	}
	else
	{
		XODBCError XError;
		XError.SetErrorText("创建XODBCDatabase对象失败");
		AfxThrowXODBCException(XError);
	}
}


XODBCRecordset::XODBCRecordset(string strDSNString, long lOption )
{
	Initiate();
	m_pDatabase = new XODBCDatabase();
	if( m_pDatabase != NULL )
	{
		XODBC_TRY
		{
			m_bRecordsetDb = true;
			if( m_pDatabase->OpenEx(strDSNString, lOption))
			{
				m_nRetcode = SQLAllocStmt(m_pDatabase->m_hdbc, &m_hstmt);

				if (!Check(m_nRetcode))
				{
					SetLastError( ConnectionError) ;
					AfxThrowXODBCException( m_XError[1] ) ;
				}
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
			XError.SetErrorText("创建XODBCRecordset对象失败!!");
			AfxThrowXODBCException(XError);
		}
	}
	else
	{
		XODBCError XError;
		XError.SetErrorText("创建XODBCDatabase对象失败");
		AfxThrowXODBCException(XError);
	}

}
	

XODBCRecordset::~XODBCRecordset()
{
	XODBC_TRY
	{
		if (m_hstmt != NULL)
		{
			if( IsOpen())
			{
				Close(); // 在Close中销毁m_hstmt,在Open中构造
			}
		}
		if ( m_bRecordsetDb )
		{
			//如果是XODBCRecordset内部构造的XODBCDatabase对象，则在此删除。
			if(m_pDatabase->IsOpen())
			{
				m_pDatabase->Close();
			}
			delete m_pDatabase;
			m_pDatabase = NULL;
		}
		else if( m_pDatabase != NULL)
		{
			
			//关闭结果集,并将其移出m_pDatabase的XODBCRecordset列表
			
			vector<XODBCRecordset *>::iterator pos;
			int index = 0;
			
			//cout<<"Now the size is: "<<m_pDatabase->m_listRecordsets.size()<<endl;
			
			for(pos = m_pDatabase->m_listRecordsets.begin(); pos != m_pDatabase->m_listRecordsets.end();pos++)
			{
				// 找到本XODBCRecordset对象指针的地址并删除

				if( m_pDatabase->m_listRecordsets.at(index) == this )
				{
					m_pDatabase->m_listRecordsets.erase(pos);
					
					/*cout<<"从m_pDatabase移除本XODBCRecordset"<<endl;
					cout<<"Now the size is: "<<m_pDatabase->m_listRecordsets.size()<<"\n\n";
					*/
	
					break; 
				}
				index++;
			}
			if( IsOpen())
			{
				Close(); // 在Close中销毁m_hstmt,在Open中构造
			}
			m_pDatabase = NULL;
		}
	}
	XODBC_CATCH
	{
		XODBCError XError;
		XError.SetErrorText("析构XODBCRecordset对象失败");
		AfxThrowXODBCException(XError);
	}

}

void XODBCRecordset::Initiate()
{
	m_pDatabase     = NULL;
	m_nOpenType     = snapshot;
	m_lOpen         = RECORDSET_STATUS_UNKNOWN;
	m_nEditMode     = noMode;
	m_nDefaultType  = snapshot;
	m_lOptions      = none;

	m_bAppendable   = false;
	m_bUpdatable    = false;
	m_bScrollable   = false;
	m_bRecordsetDb  = false;
	m_bRebindParams = false;
	m_bEOF          = false;
	m_bEOF          = false;
	m_rgRowStatus   = NULL;
	m_lRowsetSize   = 25;
	m_lAllocatedRowsetSize = 0;
	m_lRowsFetched  = 0;

	m_hstmtUpdate   = SQL_NULL_HSTMT;
	m_hstmt         = SQL_NULL_HSTMT;

	m_nResultCols   = 0;
	m_lRecordCount  = 0;
	m_strSQL = "";
	m_strCursorName = "";
	m_strTableName = "";

	m_XError[0].SetErrorType(ConnectionError);
	m_XError[1].SetErrorType(StatementError);
}



void XODBCRecordset::SetMaxRecordCount(long lCount)
{
	AllocHstmt();
	m_nRetcode = SQLSetStmtAttr(m_hstmt,SQL_ATTR_MAX_ROWS,(SQLPOINTER)lCount,SQL_IS_INTEGER);
	if( !Check(m_nRetcode) )
	{
		SetLastError(StatementError);
		AfxThrowXODBCException(m_XError[1]);
	}
}

bool XODBCRecordset::Open(int nOpenType,string strSQL, long lOpenOption)
{
	if( IsOpen() )
	{
		XODBCError error;
		error.SetErrorText("存在已打开的记录集!");
		AfxThrowXODBCException(error);
	}
	if( strSQL.empty() )
	{
		XODBCError error;
		error.SetErrorText("SQL语句不能为空!");
		AfxThrowXODBCException(error);
	}
	
	// Can only use optimizeBulkAdd with appendOnly recordsets
	// forwardOnly recordsets have limited functionality
	
	AllocHstmt();

	// Cache state info and allocate hstmt
	SetState(nOpenType, strSQL, lOpenOption);	

	XODBC_TRY
	{
		OnSetOptions(m_hstmt);

		m_lEffectCount = -1;
        m_strSQL = strSQL;

		//prep/execute or just execute direct
		PrepareAndExecute();

		// Cache some field info and prepare the rowset
		InitFieldInfo();

		if( m_nResultCols == 0)
		{
			m_nRetcode = SQLRowCount(m_hstmt,&m_lEffectCount);
			if( !Check(m_nRetcode) )
			{
				SetLastError(StatementError);
				AfxThrowXODBCException(m_XError[1]);
			}

			FreeHstmt();
			m_fieldList.clear();
			ResetAttribute();
			return false;
		}
		AllocRowset();
		BindFieldValue();

		// Fetch the first row of data
		MoveNext();

		// If EOF, then result set empty, so set BOF as well
		m_bBOF = m_bEOF;
	}
	catch(XODBCException e)
	{
		Close();
		XODBCError XError;
		e.GetError(XError);
		AfxThrowXODBCException(XError);
	}
	XODBC_CATCH
	{
		Close();
		XODBCError XError;
		XError.SetErrorText("打开记录集失败");
		AfxThrowXODBCException(XError);
		
	}
	return true;
}


void XODBCRecordset::Close()
{
	if(m_pDatabase == NULL)
	{
		return;
	}

	if( IsOpen() )
	{
		m_nRetcode = SQLFreeStmt(m_hstmt,SQL_CLOSE);
		if( !Check(m_nRetcode) )
		{
			SetLastError(StatementError);
			AfxThrowXODBCException(m_XError[1]);
		}
	}
	
	FreeHstmt();
	FreeRowset();
	m_fieldList.clear();
	FreeFieldValueList();
	ResetAttribute();
	
}

void XODBCRecordset::ResetAttribute()
{
	m_nOpenType     = snapshot;
	m_lOpen         = RECORDSET_STATUS_CLOSED;
	m_nEditMode     = noMode;
	m_nDefaultType  = snapshot;
	m_lOptions      = none;

	m_bDeleted      = false;
	m_bAppendable   = false;
	m_bUpdatable    = false;
	m_bScrollable   = false;
	m_bRecordsetDb  = false;
	m_bRebindParams = false;
	m_bEOF          = false;
	m_bEOF          = false;
	m_rgRowStatus   = NULL;
	m_lRowsetSize   = 25;
	m_lAllocatedRowsetSize = 0;
	m_lRowsFetched  = 0;

	m_nResultCols   = 0;
	m_lRecordCount  = 0;
	m_strSQL = "";
	m_strCursorName = "";
	m_strTableName ="";

	m_bRebindParams = false;
	m_bLongBinaryColumns = false;
	m_nLockMode = optimistic;

	m_nFieldsBound = 0;

}

void XODBCRecordset::ResetCursor()
{
	m_bEOFSeen = m_bBOF = m_bEOF =false;
	m_bDeleted = false;
	m_lCurrentRecord = CURRENT_RECORD_BOF;
	m_lRecordCount = 0;
}


void XODBCRecordset::FreeHstmt()
{
	if (m_hstmt != SQL_NULL_HSTMT)
	{
		m_nRetcode = SQLFreeStmt(m_hstmt, SQL_DROP);
		if ( !Check(m_nRetcode) )
		{
			SetLastError(StatementError);
			AfxThrowXODBCException(m_XError[1]);
		}
		m_hstmt = SQL_NULL_HSTMT;
	}

	if (m_hstmtUpdate != SQL_NULL_HSTMT)
	{
		m_nRetcode = SQLFreeStmt(m_hstmtUpdate, SQL_DROP);
		if ( !Check(m_nRetcode) )
		{
			SetLastError(StatementError,m_hstmtUpdate);
			AfxThrowXODBCException(m_XError[1]);
		}
		m_hstmtUpdate = SQL_NULL_HSTMT;
	}
}

// Cache state information internally in CRecordset
void XODBCRecordset::SetState(int nOpenType, string strSQL, long lOptions)
{
	if (nOpenType == DB_USE_DEFAULT_TYPE)
	{
		m_nOpenType = m_nDefaultType;
	}
	else
	{
		m_nOpenType = nOpenType;
	}

	m_bAppendable = (lOptions & appendOnly) != 0 || (lOptions & readOnly) == 0;
	m_bUpdatable = (lOptions & readOnly) == 0 && (lOptions & appendOnly) == 0;

	// Can turn off dirty field checking via dwOptions
	if (lOptions & noDirtyFieldCheck || lOptions & useMultiRowFetch)
	{
		m_bCheckCacheForDirtyFields = false;
	}

	// Set recordset readOnly if forwardOnly
	if (m_nOpenType == forwardOnly && !(lOptions & readOnly))
	{
		lOptions |= readOnly;
		// If using multiRowFetch also set useExtendFetch
		if (lOptions & useMultiRowFetch)
		{
			lOptions |= useExtendedFetch;
		}
	}

	// Archive info for use in Requery
	m_lOptions = lOptions;
	m_strRequerySQL = strSQL;
	m_strRequeryFilter = strFilter;
	m_strRequerySort = strSort;
}

// Allocate the Hstmt and implicitly create and open Database if necessary
void XODBCRecordset::AllocHstmt()
{
	
	SQLRETURN nRetCode;
	if(m_hstmt == SQL_NULL_HSTMT)
	{
		nRetCode = SQLAllocStmt(m_pDatabase->m_hdbc, &m_hstmt);	
		if (!Check(nRetCode))
		{
			SetLastError(ConnectionError);
			AfxThrowXODBCException(m_XError[0]);
		}
	}
}

void XODBCRecordset::OnSetOptions(HSTMT hstmt)
{

	m_pDatabase->OnSetOptions(m_hstmt);

	if (m_nOpenType == forwardOnly && !(m_lOptions & useExtendedFetch))
	{
		return;
	}

	// Turn on bookmark support if necessary

	if (m_nOpenType == forwardOnly)
	{
		return;
	}

//Make sure driver supports extended fetch, ODBC 2.0 and requested cursor type
	VerifyDriverBehavior();
	long lScrollType = VerifyCursorSupport();

	
	// Set  concurrency and cursor type
	SetUpdateMethod();
	SetConcurrencyAndCursorType(m_hstmt, lScrollType);
}

// Ensure that driver supports extended fetch and ODBC 2.0 if necessary
void XODBCRecordset::VerifyDriverBehavior()
{
	RETCODE nRetCode;
	unsigned short nScrollable;
	// If SQLExtendedFetch not supported, use SQLFetch
	nRetCode = SQLGetFunctions(m_pDatabase->m_hdbc,SQL_API_SQLEXTENDEDFETCH, &nScrollable);
	if (!Check(nRetCode))
	{
		XODBCError XError;
		XError.SetErrorText("驱动程序不支持函数SQLExtendedFetch，请使用函数SQLFetch!!");
		AfxThrowXODBCException(XError);
	}
	m_bScrollable = (nScrollable != 0);
	if (!m_bScrollable)
	{
		m_bUpdatable = false;
		return;
	}


	char szResult[30];
	short nResult;
	// require ODBC v2.0
	nRetCode = SQLGetInfo(m_pDatabase->m_hdbc, SQL_ODBC_VER, szResult, sizeof(szResult), &nResult);
	if (!Check(nRetCode))
	{
		XODBCError XError;
		XError.SetErrorText("检查ODBC版本失败");
		AfxThrowXODBCException(XError);
	}
	if ( szResult[0] == '0' &&  szResult[1] < '2')
	{
		XODBCError XError;
		XError.SetErrorText("需要ODBC 2.0以上版本");
		AfxThrowXODBCException(XError);
	}
}

// Check that driver supports requested cursor type
unsigned long XODBCRecordset::VerifyCursorSupport()
{
	RETCODE nRetCode;
	short nResult;
	unsigned long lDriverScrollOptions;
	nRetCode = SQLGetInfo(m_pDatabase->m_hdbc, SQL_SCROLL_OPTIONS,&lDriverScrollOptions, sizeof(lDriverScrollOptions), &nResult);
	if (!Check(nRetCode))
	{
		XODBCError XError;
		XError.SetErrorText("获取驱动程序游标信息失败 !!");
		AfxThrowXODBCException(XError);
	}

	long lScrollOptions = SQL_CURSOR_FORWARD_ONLY;
	if (m_nOpenType == dynaset)
	{
		// Dynaset support requires ODBC's keyset driven cursor model
		if (!(lDriverScrollOptions & SQL_SO_KEYSET_DRIVEN))
			{
				XODBCError XError;
				XError.SetErrorText("驱动程序不支持键集驱动游标模式");
				AfxThrowXODBCException(XError);
			}
		lScrollOptions = SQL_CURSOR_KEYSET_DRIVEN;
	}
	else if (m_nOpenType == snapshot)
	{
		// Snapshot support requires ODBC's static cursor model
		if (!(lDriverScrollOptions & SQL_SO_STATIC))
			{
				XODBCError XError;
				XError.SetErrorText("驱动程序不支持静态游标模式");
				AfxThrowXODBCException(XError);
			}
		lScrollOptions = SQL_CURSOR_STATIC;
	}
	else
	{
		// Dynamic cursor support requires ODBC's dynamic cursor model
		if (!(lDriverScrollOptions & SQL_SO_DYNAMIC))
			{
				XODBCError XError;
				XError.SetErrorText("驱动程序不支持动态游标模式");
				AfxThrowXODBCException(XError);
			}
		lScrollOptions = SQL_CURSOR_DYNAMIC;
	}

	return lScrollOptions;
}

void XODBCRecordset::SetUpdateMethod()
{

	if (m_pDatabase->m_lUpdateOptions & SQL_SETPOSUPDATES)
	{
		m_bUseUpdateSQL = false;
	}
	else if (m_pDatabase->m_lUpdateOptions & SQL_POSITIONEDSQL)
	{
		m_bUseUpdateSQL = true;
	}
	else
	{
		m_bUpdatable = false;
	}
 }


// Determine which type of concurrency to set, set it and cursor type
void XODBCRecordset::SetConcurrencyAndCursorType(HSTMT hstmt, long lScrollOptions)
{
	RETCODE nRetCode;
	short nResult;

	m_lConcurrency = SQL_CONCUR_READ_ONLY;
	if ((m_bUpdatable || m_bAppendable) && m_pDatabase->m_bUpdatable)
	{
		nRetCode = SQLGetInfo(m_pDatabase->m_hdbc, SQL_SCROLL_CONCURRENCY,&m_lDriverConcurrency, sizeof(m_lDriverConcurrency), &nResult);
		if (!Check(nRetCode))
		{
			XODBCError XError;
			XError.SetErrorText("获取驱动程序游标并发信息失败!!");
			AfxThrowXODBCException(XError);
		}

		if (m_nLockMode == pessimistic)
		{
			if (m_lDriverConcurrency & SQL_SCCO_LOCK)
			{
				m_lConcurrency = SQL_CONCUR_LOCK;
			}

		}
		else
		{
			// Use cheapest, most concurrent model
			if (m_lDriverConcurrency & SQL_SCCO_OPT_ROWVER)
			{
				m_lConcurrency = SQL_CONCUR_ROWVER;
			}
			else if (m_lDriverConcurrency & SQL_SCCO_OPT_VALUES)
			{
				m_lConcurrency = SQL_CONCUR_VALUES;
			}
			else if (m_lDriverConcurrency & SQL_SCCO_LOCK)
			{
				m_lConcurrency = SQL_CONCUR_LOCK;
			}
		}
	}

	nRetCode = SQLSetStmtOption(hstmt, SQL_CURSOR_TYPE, lScrollOptions);
	if (!Check(nRetCode))
	{
		XODBCError XError;
		XError.SetErrorText("设置游标类型失败");
		AfxThrowXODBCException(XError);
	}

	// Set the concurrency model (NOTE: may have to reset concurrency later).
	nRetCode = SQLSetStmtOption(hstmt, SQL_CONCURRENCY, m_lConcurrency);
	if ( !Check(nRetCode) )
	{
		XODBCError XError;
		XError.SetErrorText("设置游标的并发属性时失败");
		AfxThrowXODBCException(XError);
	}
}



// Prepare and Execute the SQL or simple call SQLExecDirect, resetting concurrency if necessary
void XODBCRecordset::PrepareAndExecute()
{
	bool bConcurrency = false;
	//CHAR *pszSQL = const_cast<LPTSTR>(static_cast<LPCTSTR>(m_strSQL));
	int nLen = (int)m_strSQL.length();
	char * pszSQL= new char[nLen + 1];
	strcpy(pszSQL,m_strSQL.c_str());

	while ( !bConcurrency )
	{
		// Prepare or execute the query
		if (m_lOptions & executeDirect)
		{
			m_nRetcode = SQLExecDirect(m_hstmt,(SQLCHAR *)pszSQL,SQL_NTS);
		}
		else
		{
			m_nRetcode = SQLPrepare(m_hstmt, (SQLCHAR *)pszSQL, SQL_NTS);
		}
		if ( Check(m_nRetcode))
		{
		    bConcurrency = true;
		}
		else
		{
			if (m_lConcurrency != SQL_CONCUR_READ_ONLY )
			{
				
				// ODBC will automatically attempt to set alternate concurrency if
				// request fails, but it won't try LOCK even if driver supports it.
				if ((m_lDriverConcurrency & SQL_SCCO_LOCK) &&
					(m_lConcurrency == SQL_CONCUR_ROWVER ||
					m_lConcurrency == SQL_CONCUR_VALUES))
				{
					m_lConcurrency = SQL_CONCUR_LOCK;
				}
				else
				{
					m_lConcurrency = SQL_CONCUR_READ_ONLY;
					m_bUpdatable   = m_bAppendable = false;
				}

				// Attempt to reset the concurrency model.
				m_nRetcode = SQLSetStmtOption(m_hstmt, SQL_CONCURRENCY,m_lConcurrency);
				if ( !Check(m_nRetcode) )
				{
					SetLastError(StatementError);
					AfxThrowXODBCException(m_XError[1]);
				}
			}
			else
			{
				XODBCError XError;
				XError.SetErrorText((string)"ODBC执行SQLPrepare或者SQLExecDirect失败");
				AfxThrowXODBCException(XError);
			}
		}
	}


	// now attempt to execute the SQL Query if not executed already
	if (!(m_lOptions & executeDirect))
	{
		m_nRetcode = SQLExecute( m_hstmt);
		if ( !Check(m_nRetcode) )
		{
			SetLastError(StatementError);
			AfxThrowXODBCException(m_XError[1]);
		}
	}
	m_lOpen = RECORDSET_STATUS_OPEN;

	// SQLExecute or SQLExecDirect may have changed an option value
	if (m_nRetcode == SQL_SUCCESS_WITH_INFO)
	{
		// Check if concurrency was changed in order to mark
		// recordset non-updatable if necessary
		long lConcurrency;
		m_nRetcode = SQLGetStmtOption(m_hstmt, SQL_CONCURRENCY, &lConcurrency);
		if ( !Check(m_nRetcode) )
		{
			SetLastError(StatementError);
			AfxThrowXODBCException(m_XError[1]);
		}

		if (lConcurrency == SQL_CONCUR_READ_ONLY && (m_bUpdatable || m_bAppendable))
		{
			m_bUpdatable = false;
			m_bAppendable = false;
		}
	}
}


bool XODBCRecordset::CanAppend() const
{
	return m_bAppendable;
}

bool XODBCRecordset::CanUpdate() const
{
	return m_bUpdatable;
}

bool XODBCRecordset::CanTransact() const
{
	return m_pDatabase->CanTransact();
}

bool XODBCRecordset::IsDeleted() const
{
	return m_bDeleted;
}
	
bool XODBCRecordset::CanScroll() const
{
	return m_bScrollable;
}

bool XODBCRecordset::CanRestart() const
{
	return !(m_lOptions & executeDirect); //能否对原SQL语句重新查询
}

bool XODBCRecordset::CanBookmark() const
{
	if (!(m_lOptions & useBookmarks) ||
		(m_nOpenType == forwardOnly && !(m_lOptions & useExtendedFetch)))
	{
		return false;
	}

	return ((m_pDatabase->GetBookmarkPersistence() & SQL_BP_SCROLL) != 0);
}

const string XODBCRecordset::GetSQL() const
{
	return m_strSQL;
}
	
void XODBCRecordset::GetStatus(XODBCRecordsetStatus & rStatus) const
{
	rStatus.m_lCurrentRecord = m_lCurrentRecord;
	rStatus.m_bRecordCountFinal = m_bEOFSeen;
}

const string XODBCRecordset::GetTableName() const
{
	return m_strTableName;
}
	
const short XODBCRecordset::GetFieldCount() const
{
	return m_nResultCols;
}
	

const long XODBCRecordset::GetEffectCount() const
{
	return m_lEffectCount;
}

bool XODBCRecordset::IsOpen() 
{
	if (m_hstmt == NULL)
	{
		return false;
	}

	bool bOpen = false;

	if (m_nResultCols != 0)
	{
		bOpen = true;
	}
	return bOpen;
}
	
bool XODBCRecordset::IsBOF() const
{
	return m_bBOF;
}
	
bool XODBCRecordset::IsEOF() const
{
	return m_bEOF;
}

vector<string> XODBCRecordset::GetTableList()
{
	vector<string>  strTables;
	char * pszTableName   = new char[256];
	string   strTemp;
  
	SQLHSTMT   hstmt;
	SQLRETURN  nRetcode;

	pszTableName[0] = '\0';

	nRetcode = SQLAllocHandle(SQL_HANDLE_STMT,m_pDatabase->m_hdbc,&hstmt);
	if( !Check(nRetcode) )
	{
		SetLastError(StatementError,hstmt);
		AfxThrowXODBCException(m_XError[1]);
	}
	nRetcode = SQLTables(hstmt,NULL,0,NULL,0,NULL,0,(SQLCHAR *)"TABLE",5);
	if( !Check(nRetcode) )
	{
		SetLastError(StatementError,hstmt);
		AfxThrowXODBCException(m_XError[1]);
	}

	nRetcode = SQLBindCol(hstmt,3,SQL_C_CHAR,pszTableName,256,0);
	if( !Check(nRetcode) )
	{
		SetLastError(StatementError,hstmt);
		AfxThrowXODBCException(m_XError[1]);
	}

	while( (nRetcode = SQLFetch(hstmt)) == SQL_SUCCESS ||  nRetcode == SQL_SUCCESS_WITH_INFO )
	{
		strTables.push_back((const char*)pszTableName);
	}

	if( nRetcode != SQL_NO_DATA_FOUND )
	{
    	SetLastError( StatementError, hstmt);
		AfxThrowXODBCException( m_XError[1] );
	}		

	nRetcode = SQLFreeStmt(hstmt,SQL_DROP);
	if( !Check(nRetcode) )
	{
		SetLastError( StatementError, hstmt );
		AfxThrowXODBCException(m_XError[1]);
	}

	delete pszTableName;
	return strTables; 

}

vector<XTableDesc> XODBCRecordset::GetTableDescList() 
{
	vector<XTableDesc>  tableDescs;
	XTableDesc tableDesc;
	char * pszCatalogName   = new char[256];
	char * pszSchemaName   = new char[256];
	char * pszTableName   = new char[256];
	
	string   strCatalogName;
	string   strTemp;
  
	SQLHSTMT   hstmt;
	SQLRETURN  nRetcode;

	pszCatalogName[0] = '\0';
	pszSchemaName[0] = '\0';
	pszTableName[0] = '\0';

	nRetcode = SQLAllocHandle(SQL_HANDLE_STMT,m_pDatabase->m_hdbc,&hstmt);
	if( !Check(nRetcode) )
	{
		SetLastError(StatementError,hstmt);
		AfxThrowXODBCException(m_XError[1]);
	}
	nRetcode = SQLTables(hstmt,NULL,0,NULL,0,NULL,0,(SQLCHAR *)"TABLE",5);
	if( !Check(nRetcode) )
	{
		SetLastError(StatementError,hstmt);
		AfxThrowXODBCException(m_XError[1]);
	}

	//nRetcode = SQLBindCol(hstmt,1,SQL_C_CHAR,pszCatalogName,256,0);
	//if( !Check(nRetcode) )
	//{
	//	SetLastError(StatementError,hstmt);
	//	AfxThrowXODBCException(m_XError[1]);
	//}

	strCatalogName = m_pDatabase->GetDatabaseName();

	nRetcode = SQLBindCol(hstmt,2,SQL_C_CHAR,pszSchemaName,256,0);
	if( !Check(nRetcode) )
	{
		SetLastError(StatementError,hstmt);
		AfxThrowXODBCException(m_XError[1]);
	}
	nRetcode = SQLBindCol(hstmt,3,SQL_C_CHAR,pszTableName,256,0);
	if( !Check(nRetcode) )
	{
		SetLastError(StatementError,hstmt);
		AfxThrowXODBCException(m_XError[1]);
	}

	while( (nRetcode = SQLFetch(hstmt)) == SQL_SUCCESS ||  nRetcode == SQL_SUCCESS_WITH_INFO )
	{
		tableDesc.m_strCatalogName = strCatalogName;
	    tableDesc.m_strSchemaName = pszSchemaName;
		tableDesc.m_strTableName = pszTableName;
		tableDescs.push_back(tableDesc);
	}
	if( nRetcode != SQL_NO_DATA_FOUND )
	{
    	SetLastError( StatementError, hstmt);
		AfxThrowXODBCException( m_XError[1] );
	}		

	nRetcode = SQLFreeStmt(hstmt,SQL_DROP);
	if( !Check(nRetcode) )
	{
		SetLastError( StatementError, hstmt );
		AfxThrowXODBCException(m_XError[1]);
	}

	delete pszTableName;
	delete pszCatalogName;
	delete pszSchemaName;

	return tableDescs; 
}

vector<string> XODBCRecordset::GetIndexList(string strTableName, vector<string> &strColumnNameList,vector<short> &nIsUniqueList, vector<short> &nIndexTypeList)
{
	vector<string> strIndexList;
	char * pszIndexName   = new char[256];
	char * pszColumnName = new char[256];
	SQLSMALLINT nIsUnique = 0;
	SQLSMALLINT nIndexType = 0;
	SQLHSTMT   hstmt;
	SQLRETURN  nRetcode;
	SQLUSMALLINT nSupported;


	nRetcode = SQLAllocHandle(SQL_HANDLE_STMT,m_pDatabase->m_hdbc,&hstmt);
	if( !Check(nRetcode) )
	{
		SetLastError(StatementError,hstmt);
		AfxThrowXODBCException(m_XError[1]);
	}
	nRetcode = SQLGetFunctions(m_pDatabase->m_hdbc,SQL_API_SQLSTATISTICS,&nSupported);
	if( !Check(nRetcode) )
	{
		SetLastError(ConnectionError);
		AfxThrowXODBCException(m_XError[0]);
	}

	if(nSupported)
	{
		//cout<<"驱动程序支持SQLStatistics函数"<<endl;
	}
	else
	{
		XODBCError XError;
		XError.SetErrorText(" 驱动程序不提供获取索引信息的功能");
		AfxThrowXODBCException(XError);
	}
	
	nRetcode = SQLStatistics(hstmt,NULL,0,NULL,0,(SQLCHAR*)strTableName.c_str(),SQL_NTS,SQL_INDEX_ALL,SQL_ENSURE);
	if( !Check(nRetcode) )
	{
		SetLastError(StatementError,hstmt);
		AfxThrowXODBCException(m_XError[1]);
	}


	nRetcode = SQLBindCol(hstmt,4,SQL_C_SSHORT,&nIsUnique,0,0);
	if( !Check(nRetcode) )
	{
		SetLastError(StatementError,hstmt);
		AfxThrowXODBCException(m_XError[1]);
	}

	nRetcode = SQLBindCol(hstmt,6,SQL_C_CHAR,pszIndexName,256,0);
	if( !Check(nRetcode) )
	{
		SetLastError(StatementError,hstmt);
		AfxThrowXODBCException(m_XError[1]);
	}

	
	nRetcode = SQLBindCol(hstmt,7,SQL_C_SSHORT,&nIndexType,0,0);
	if( !Check(nRetcode) )
	{
		SetLastError(StatementError,hstmt);
		AfxThrowXODBCException(m_XError[1]);
	}
	
	nRetcode = SQLBindCol(hstmt,9,SQL_C_CHAR,pszColumnName,256,0);
	if( !Check(nRetcode) )
	{
		SetLastError(StatementError,hstmt);
		AfxThrowXODBCException(m_XError[1]);
	}
	

	while( (nRetcode = SQLFetch(hstmt)) == SQL_SUCCESS ||  nRetcode == SQL_SUCCESS_WITH_INFO )
	{
		strIndexList.push_back((string)pszIndexName);
		strColumnNameList.push_back((string)pszColumnName);
		nIsUniqueList.push_back(nIsUnique);
		nIndexTypeList.push_back(nIndexType);
	}

	if( nRetcode != SQL_NO_DATA_FOUND )
	{
		SetLastError( StatementError, hstmt);
		AfxThrowXODBCException( m_XError[1] );
	}		

	nRetcode = SQLFreeStmt(hstmt,SQL_DROP);
	if( !Check(nRetcode) )
	{
		SetLastError( StatementError, hstmt );
		AfxThrowXODBCException(m_XError[1]);
	}
 
	delete pszIndexName;
	delete pszColumnName;
	return strIndexList;
}
	
vector<string> XODBCRecordset::GetPrimaryKeyList(string strTableName) 
{
	vector<string> strPKList;
	char * pszPKName   = new char[256];;
	SQLHSTMT   hstmt;
	SQLRETURN  nRetcode;
	SQLUSMALLINT nSupported;

	nRetcode = SQLAllocHandle(SQL_HANDLE_STMT,m_pDatabase->m_hdbc,&hstmt);
	if( !Check(nRetcode) )
	{
		SetLastError(StatementError,hstmt);
		AfxThrowXODBCException(m_XError[1]);
	}

	nRetcode = SQLGetFunctions(m_pDatabase->m_hdbc,SQL_API_SQLPRIMARYKEYS,&nSupported);
	if( !Check(nRetcode) )
	{
		SetLastError(ConnectionError);
		AfxThrowXODBCException(m_XError[0]);
	}

	if(nSupported)
	{
		//cout<<"驱动程序支持SQLPrimaryKeys函数"<<endl;
	}
	else
	{
		XODBCError XError;
		XError.SetErrorText((string)" 驱动程序不提供获取主键信息的功能");
		AfxThrowXODBCException(XError);
	}

	nRetcode = SQLPrimaryKeys(hstmt,NULL,0,NULL,0,(SQLCHAR*) strTableName.c_str(),SQL_NTS);
	if( !Check(nRetcode) )
	{
		SetLastError(StatementError,hstmt);
		AfxThrowXODBCException(m_XError[1]);
	}

	nRetcode = SQLBindCol(hstmt,4,SQL_C_CHAR,pszPKName,256,0);
	if( !Check(nRetcode) )
	{
		SetLastError(StatementError,hstmt);
		AfxThrowXODBCException(m_XError[1]);
	}
	while( (nRetcode = SQLFetch(hstmt)) == SQL_SUCCESS ||  nRetcode == SQL_SUCCESS_WITH_INFO )
	{
		strPKList.push_back((string)pszPKName);
	}
	if( nRetcode != SQL_NO_DATA_FOUND )
	{
		SetLastError( StatementError, hstmt);
		AfxThrowXODBCException( m_XError[1] );
	}		

	nRetcode = SQLFreeStmt(hstmt,SQL_DROP);
	if( !Check(nRetcode) )
	{
		SetLastError( StatementError, hstmt );
		AfxThrowXODBCException(m_XError[1]);
	}

	delete pszPKName;
	return strPKList;
}

vector<string> XODBCRecordset::GetForeignKeyList(string strTableName,vector<string> &strPKTableNameList) 
{
	vector<string> strFKList;
	SQLUSMALLINT   nSupported;
	SQLRETURN      nRetcode;
	char *         pszFKName  = new char[256];
	char *         pszPKTableName  = new char[256];
	SQLHSTMT       hstmt;


	/*
	如果*PKTableName包含一个表名，SQLForeignKeys返回一个包含指定表的主键及引用它的所有外键的结果集。
	其他表中的外键的列表不包含指向指定表中唯一限制的外键。如果*FKTableName包含一个表名，SQLForeignKeys
	返回一个包含指向其他表中的主键的、在指定表中的所有外键，以及外键所引用的、在其他表中的主键的结果集。
	指定表中外键的列表不包含引用其他表中唯一限制的外键。如果*PKTableName和*FKTableName都包含表名，
	SQLForeignKeys返回在*FKTable Name中所指定表的外键，而*FKTableName引用在*PKTableName中所指定表的主键。
	多数情况下是一个键。
	*/
	strPKTableNameList.clear();

	nRetcode = SQLGetFunctions(m_pDatabase->m_hdbc,SQL_API_SQLFOREIGNKEYS,&nSupported);
	if( !Check(nRetcode) )
	{
		SetLastError(ConnectionError);
		AfxThrowXODBCException(m_XError[0]);
	}

	if( nSupported)
	{
		//cout<<"驱动程序支持SQLForeignKeys函数"<<endl;
	}
	else
	{
		XODBCError XError;
		XError.SetErrorText((string)" 驱动程序不提供获取外键信息的功能");
		AfxThrowXODBCException(XError);
	}

	nRetcode = SQLAllocHandle(SQL_HANDLE_STMT,m_pDatabase->m_hdbc,&hstmt);
	if( !Check(nRetcode) )
	{
		SetLastError(StatementError,hstmt);
		AfxThrowXODBCException(m_XError[1]);
	}

	nRetcode = SQLForeignKeys(hstmt,NULL,0,NULL,0,NULL,0,NULL,0,NULL,0,(SQLCHAR*) strTableName.c_str(),SQL_NTS);
	if( !Check(nRetcode) )
	{
		SetLastError(StatementError,hstmt);
		AfxThrowXODBCException(m_XError[1]);
	}

	nRetcode = SQLBindCol(hstmt,3,SQL_C_CHAR,pszPKTableName,256,0);
	if( !Check(nRetcode) )
	{
		SetLastError(StatementError,hstmt);
		AfxThrowXODBCException(m_XError[1]);
	}
	nRetcode = SQLBindCol(hstmt,8,SQL_C_CHAR,pszFKName,256,0);
	if( !Check(nRetcode) )
	{
		SetLastError(StatementError,hstmt);
		AfxThrowXODBCException(m_XError[1]);
	}

	while( (nRetcode = SQLFetch(hstmt)) == SQL_SUCCESS ||  nRetcode == SQL_SUCCESS_WITH_INFO )
	{
		strPKTableNameList.push_back((string)pszPKTableName);
		strFKList.push_back((string)pszFKName);
	}
	if( nRetcode != SQL_NO_DATA_FOUND )
	{
		SetLastError( StatementError, hstmt);
		AfxThrowXODBCException( m_XError[1] );
	}		

	nRetcode = SQLFreeStmt(hstmt,SQL_DROP);
	if( !Check(nRetcode) )
	{
		SetLastError( StatementError, hstmt );
		AfxThrowXODBCException(m_XError[1]);
	}

	delete pszPKTableName;
	delete pszFKName;

	return strFKList;
}

void XODBCRecordset::AllocRowset()
{
	if (m_lOptions & useMultiRowFetch)
	{
		SetRowsetSize(m_lRowsetSize);
	}
	else
	{
		// Not using bulk row fetch, set rowset size to 1
		m_rgRowStatus = new SQLUSMALLINT[1];
		m_lRowsetSize = 1;
	}
}

void XODBCRecordset::SetRowsetSize(long lNewRowsetSize)
{
	if (!IsOpen())
	{
		m_lRowsetSize = lNewRowsetSize;
		return;
	}

	if (!(m_lOptions & useMultiRowFetch))
	{
		return;
	}
	if (m_lAllocatedRowsetSize == 0 ||
		(m_lAllocatedRowsetSize < (SQLUINTEGER) lNewRowsetSize))
	{
		FreeRowset();
		m_rgRowStatus = new SQLUSMALLINT[lNewRowsetSize];
		if (!(m_lOptions & userAllocMultiRowBuffers))
		{
			// Allocate the rowset field buffers
			m_lRowsetSize          = lNewRowsetSize;
			m_lAllocatedRowsetSize = lNewRowsetSize;
		}
	}
	else
	{
		// Just reset the new rowset size
		m_lRowsetSize = lNewRowsetSize;
	}
	m_nRetcode = SQLSetStmtOption(m_hstmt, SQL_ROWSET_SIZE,m_lRowsetSize);

}

void XODBCRecordset::FreeRowset()
{
	delete [] m_rgRowStatus;
	m_rgRowStatus = NULL;

	if (m_lOptions & useMultiRowFetch &&
		!(m_lOptions & userAllocMultiRowBuffers))
	{
		// Calling virtual function, DoBulkFieldExchange, here is bad
		// because Close then FreeRowset may get called from destructor.
		// There is no simple choice however if RFX_Bulk functions do
		// a memory allocation. The net result is that users MUST call
		// Close explicitly (rather than relying on destructor) if
		// using multi row fetches, otherwise they will get a memory leak.
		// If rowset already allocated, delete old rowset buffers
		if (m_lAllocatedRowsetSize != 0)
		{
			/*
			CFieldExchange fx(CFieldExchange::DeleteMultiRowBuffer, this);
			DoBulkFieldExchange(&fx);
			*/
		}
	}

	m_lAllocatedRowsetSize = 0;
}

void XODBCRecordset::MoveNext()
{
	Move( 1, SQL_FETCH_NEXT);
}

void XODBCRecordset::MovePrev()
{
	Move( -1, SQL_FETCH_PRIOR);
}

void XODBCRecordset::MoveFirst()
{
	Move( 1, SQL_FETCH_FIRST);
}
	
void XODBCRecordset::MoveLast()
{
	Move( -1, SQL_FETCH_LAST);
}

void XODBCRecordset::Move(long lRows, short nFetchType )
{
	// Check scrollability, EOF/BOF status
	CheckRowsetCurrencyStatus(nFetchType, lRows);

	// Fetch the data, skipping deleted records if necessary
	if ((nFetchType == SQL_FETCH_FIRST ||
		nFetchType == SQL_FETCH_LAST ||
		nFetchType == SQL_FETCH_NEXT ||
		nFetchType == SQL_FETCH_PRIOR ||
		nFetchType == SQL_FETCH_RELATIVE) )//&&m_lOptions & skipDeletedRecords)
	{
		;//SkipDeletedRecords(wFetchType, nRows, &m_dwRowsFetched, &nRetCode);
	}
	else
	{
		;//nRetCode = FetchData(wFetchType, nRows, &m_dwRowsFetched);
	}
	m_nRetcode = FetchData(nFetchType, lRows, &m_lRowsFetched);

	// Set currency status and increment the record counters
	SetRowsetCurrencyStatus(m_nRetcode, nFetchType, lRows, m_lRowsFetched);

	// Need to fixup bound fields in some cases
	/*if (m_nFields > 0 && !IsEOF() && !IsBOF() &&
		!(m_dwOptions & useMultiRowFetch))
	{
		Fixups();
	};*/
}

RETCODE  XODBCRecordset::FetchData(short nFetchType, long lRow, SQLUINTEGER *plRowsFetched)
{
	if (m_nOpenType == forwardOnly && !(m_lOptions & useExtendedFetch) && nFetchType == SQL_FETCH_NEXT)
	{
		m_nRetcode = SQLFetch(m_hstmt);
		*plRowsFetched = 1;
		m_bDeleted = false;
	}
	else
	{
		m_nRetcode = SQLExtendedFetch(m_hstmt, nFetchType, lRow, plRowsFetched, m_rgRowStatus);

		// Set deleted status
		//m_bDeleted = GetRowStatus(1) == SQL_ROW_DELETED;
	}
	if( !Check(m_nRetcode))
	{
		SetLastError(StatementError);
		AfxThrowXODBCException(m_XError[1]);
	}
	return m_nRetcode;
}

void  XODBCRecordset::CheckRowsetCurrencyStatus(short wFetchType, long lRows)
{
	if (!m_bScrollable && wFetchType != SQL_FETCH_NEXT)
	{
		XODBCError XError;
		XError.SetErrorText((string)"仅支持前滚(FORWARD_ONLY)记录集");
		AfxThrowXODBCException(XError);
	}

	if (IsEOF() && IsBOF())
	{
		XODBCError XError;
		XError.SetErrorText((string)"记录集为空");
		AfxThrowXODBCException(XError);
	}

	if (m_nOpenType != dynamic)
	{
		if (IsEOF() && (wFetchType == SQL_FETCH_NEXT ||
		(wFetchType == SQL_FETCH_RELATIVE && lRows > 0)))
		{
			XODBCError XError;
			XError.SetErrorText((string)"已到记录集末尾");
			AfxThrowXODBCException(XError);
		}
		else if (IsBOF() && (wFetchType == SQL_FETCH_PRIOR ||
		(wFetchType == SQL_FETCH_RELATIVE && lRows < 0)))
		{
			XODBCError XError;
			XError.SetErrorText((string)"已到记录集开头");
			AfxThrowXODBCException(XError);
		}
	}

}

void  XODBCRecordset::SetRowsetCurrencyStatus(RETCODE nRetcode,SQLUSMALLINT nFetchType, long lRows, SQLUINTEGER lRowsFetched)
{
	// Set the fetch direction
	int nDirection = 0;

	switch (nFetchType)
	{
	case SQL_FETCH_FIRST:
		nDirection = 1;
		if (nRetcode == SQL_NO_DATA_FOUND)
		{
			m_lCurrentRecord = CURRENT_RECORD_UNDEFINED;
			m_lRecordCount = 0;
		}
		else
		{
			m_lCurrentRecord = 0;
		}
		break;

	case SQL_FETCH_NEXT:
		nDirection = 1;
		if ( m_lCurrentRecord != CURRENT_RECORD_UNDEFINED && nRetcode != SQL_NO_DATA_FOUND)
		{
			m_lCurrentRecord += lRows;
		}

		// If not at the end and haven't yet been to the end, incr count
	   if (nRetcode != SQL_NO_DATA_FOUND && !m_bEOFSeen && m_lCurrentRecord != CURRENT_RECORD_UNDEFINED)
		{
		// lCurrentRecord 0-based and it's already been set
	       m_lRecordCount = __max( m_lRecordCount, m_lCurrentRecord + 1);
		}
	

		// This is the only way to know you've hit the end (m_bEOFSeen)
		if (!m_bEOFSeen && nRetcode == SQL_NO_DATA_FOUND && m_lRecordCount == m_lCurrentRecord + 1)
		{
			m_bEOFSeen = true;
		}
		break;

	case SQL_FETCH_LAST:
		nDirection = -1;
		if (nRetcode == SQL_NO_DATA_FOUND)
		{
			m_lCurrentRecord = CURRENT_RECORD_UNDEFINED;
			m_lRecordCount = 0;
		}
		else if (m_bEOFSeen)
		{
			m_lCurrentRecord = m_lRecordCount - 1;
		}
		else
		{
			m_lCurrentRecord = CURRENT_RECORD_UNDEFINED;
		}
		break;

	case SQL_FETCH_PRIOR:
		nDirection = -1;
		// If doing MovePrev after m_bEOF, don't increment current rec
		if (!m_bEOF)
		{
			if ( m_lCurrentRecord != CURRENT_RECORD_UNDEFINED && nRetcode != SQL_NO_DATA_FOUND)
			{
				m_lCurrentRecord += lRows;
			}
		}
		break;

	case SQL_FETCH_RELATIVE:
		nDirection = (int)lRows;
		if ( m_lCurrentRecord != CURRENT_RECORD_UNDEFINED && nRetcode != SQL_NO_DATA_FOUND)
		{
			m_lCurrentRecord += lRows;
		}

	    if (nRetcode != SQL_NO_DATA_FOUND && !m_bEOFSeen && m_lCurrentRecord != CURRENT_RECORD_UNDEFINED)
		{
	       m_lRecordCount = __max( m_lRecordCount, m_lCurrentRecord + 1);
		}
		break;

	case SQL_FETCH_ABSOLUTE:
		nDirection = (int)lRows;
		if (nRetcode != SQL_NO_DATA_FOUND)
		{
			if (lRows > 0)
			{
				m_lCurrentRecord = lRows - 1;
			}
			else if (m_bEOFSeen)
			{
				m_lCurrentRecord = m_lRecordCount + lRows;
			}
			else
			{
				m_lCurrentRecord = CURRENT_RECORD_UNDEFINED;
			}
		}
		else
		{
			m_lCurrentRecord = CURRENT_RECORD_UNDEFINED;
		}

	    if (nRetcode != SQL_NO_DATA_FOUND && !m_bEOFSeen && m_lCurrentRecord != CURRENT_RECORD_UNDEFINED)
		{
	       m_lRecordCount = __max( m_lRecordCount, m_lCurrentRecord + 1);
		}
		break;

	case SQL_FETCH_BOOKMARK:
		nDirection = 0;
		m_lCurrentRecord = CURRENT_RECORD_UNDEFINED;
		break;
	}

	// Set the BOF/EOF flags
	if (nRetcode == SQL_NO_DATA_FOUND)
	{
		if (nFetchType == SQL_FETCH_FIRST || nFetchType == SQL_FETCH_LAST ||
			nFetchType == SQL_FETCH_BOOKMARK)
		{
			// If MoveFirst/MoveLast fails, result set is empty
			// If SetBookmark fails, currency undefined
			m_bEOF = m_bBOF = true;
		}
		else
		{
			m_bEOF = nDirection >= 0;
			m_bBOF = !m_bEOF;
		}
	}
	else
	{
		m_bEOF = m_bBOF = false;
	}
}

SQLUSMALLINT XODBCRecordset::GetRowStatus( SQLUSMALLINT nRow)
{
	return m_rgRowStatus[nRow - 1];
}

bool XODBCRecordset::Requery()
{
	// Can't requery if using direct execution
	if (m_lOptions & executeDirect)
	{
		return false;
	}
	XODBC_TRY
	{
		// Shutdown current query, preserving buffers for performance
		m_nRetcode = SQLFreeStmt(m_hstmt, SQL_CLOSE);
		if ( !Check(m_nRetcode) )
		{
			SetLastError(StatementError);
			AfxThrowXODBCException(m_XError[1]);
		}
		m_lOpen = RECORDSET_STATUS_CLOSED;

		// now attempt to re-execute the SQL Query
		m_nRetcode = SQLExecute(m_hstmt);
		if ( !Check(m_nRetcode) )
		{
			SetLastError(StatementError);
			AfxThrowXODBCException(m_XError[1]);
		}

		m_lOpen = RECORDSET_STATUS_OPEN;

		// Reset some cursor properties and fetch first record
		ResetCursor();
		MoveNext();

		// If EOF, then result set empty, so set BOF as well
		m_bBOF = m_bEOF;
	}
	XODBC_CATCH
	{
		Close();
		XODBCError XError;
		XError.SetErrorText("更新查询失败!");
		AfxThrowXODBCException(XError);
	}

	return true;
}


void XODBCRecordset::Cancel()
{
	m_nRetcode = SQLCancel(m_hstmt);
	if( !Check(m_nRetcode) )
	{
		SetLastError(StatementError);
		AfxThrowXODBCException(m_XError[1]);
	}
}

bool XODBCRecordset::FlushResultSet()
{
	bool bReturn = false;
	m_nRetcode = SQLMoreResults(m_hstmt);

	if ( !Check( m_nRetcode) )
	{
		SetLastError(StatementError);
		AfxThrowXODBCException(m_XError[1]);
	}
	if( m_nRetcode != SQL_NO_DATA_FOUND )
	{
		bReturn = true;
	}
	else
	{
		return false;
	}

	InitFieldInfo();
	BindFieldValue();
	ResetCursor();

	MoveNext();
	return bReturn;
	
}

void XODBCRecordset::GetFieldInfo(int nColIndex, XFieldInfo &fieldInfo)
{
	if( m_nResultCols <= 0)
	{
		return;
	}
	if( nColIndex >= 0 && nColIndex < (int)m_fieldList.size())
	{
		XFieldInfo xfInfo;
		xfInfo = m_fieldList.at(nColIndex);
		fieldInfo.SetFieldInfo(xfInfo);
	}
	else
	{
		XODBCError error;
		error.SetErrorText("字段下标越界!");
		AfxThrowXODBCException(error);
	}
}

void XODBCRecordset::GetFieldInfo(string strColName, XFieldInfo &fieldInfo)
{
	int nColIndex = -1;
	if( m_nResultCols <= 0)
	{
		return;
	}
	nColIndex = GetFieldIndexByName(strColName);
	if( nColIndex < 0 || nColIndex > (int)m_fieldList.size())
	{
		XODBCError error;
		error.SetErrorText("找不到匹配的字段名");
		AfxThrowXODBCException(error);
	}
	GetFieldInfo(nColIndex,fieldInfo);
}

short XODBCRecordset::GetFieldIndexByName(string strColName)
{
	int nColIndex = -1;
	int i;
	for(i = 0;i< (int)m_fieldList.size();i++ )
	{
		if(m_fieldList.at(i).m_strName == strColName)
		{
			nColIndex = i;
		}
	}
	return nColIndex;
}

string XODBCRecordset::GetFieldNameByIndex(short  nIndex)
{
	if( nIndex < 0 || nIndex >= (int)m_fieldList.size())
	{
		return "";
	}
	return m_fieldList.at(nIndex).m_strName;
}

void  XODBCRecordset::InitFieldInfo()
{
	XFieldInfo xfInfo;
	char * fieldName = new char[MAX_FNAME_LEN+1];
	m_nResultCols = 0;
	m_nRetcode = SQLNumResultCols(m_hstmt,&m_nResultCols);
	if(! Check(m_nRetcode))
	{
		SetLastError(StatementError);
		AfxThrowXODBCException(m_XError[1]);
	}
	if( m_nResultCols == 0)
	{
		return;
	}
	m_fieldList.clear();
	for(short i = 0; i< m_nResultCols; i++)
	{
		m_nRetcode =SQLDescribeCol(m_hstmt,i+1,(SQLCHAR *)fieldName,MAX_FNAME_LEN,0,&xfInfo.m_nSQLType,&xfInfo.m_lPrecision,&xfInfo.m_nScale,&xfInfo.m_nNullability);
		if(! Check(m_nRetcode))
		{
			SetLastError(StatementError);
			AfxThrowXODBCException(m_XError[1]);
		}
		xfInfo.m_strName = fieldName;
		m_fieldList.push_back(xfInfo);
	}
}

short XODBCRecordset::GetCTypeFromSqlType( short nSqlType)
{  
    short nCType = 0;	
	switch(nSqlType)
	{
	case SQL_CHAR:
	case SQL_WCHAR:
	case SQL_VARCHAR:
		nCType = SQL_C_CHAR;
		break;

	case SQL_WVARCHAR:
	case SQL_LONGVARCHAR:
	case SQL_WLONGVARCHAR:
		nCType = SQL_C_WCHAR;
		break;

	case SQL_DECIMAL:
	case SQL_NUMERIC:
		nCType = SQL_C_CHAR;  //用字符串存储，存进数据库时需要转换
		break;

	case SQL_BIT:
		nCType = SQL_C_BIT;
		break;

	case SQL_TINYINT:
		nCType = SQL_C_TINYINT; //用unsigned char 获取
		break;

	case SQL_SMALLINT:
		nCType = SQL_C_SSHORT;
		break;

	case SQL_INTEGER:
		nCType = SQL_C_LONG;
		break;

	case SQL_GUID:
		nCType = SQL_C_LONG;  //用long获取，可能会出现转换错误
		break;

	case SQL_BIGINT:
		nCType = SQL_C_SBIGINT;
		break;

	case SQL_REAL:
		nCType = SQL_C_FLOAT;
		break;

	case SQL_FLOAT:
	case SQL_DOUBLE:
		nCType = SQL_C_DOUBLE;
		break;

	case SQL_BINARY:
	case SQL_VARBINARY:
	case SQL_LONGVARBINARY:
		nCType = SQL_C_BINARY;
		break;

	case SQL_TYPE_DATE:
	case SQL_DATE:
		nCType = SQL_C_DATE;
		break;

	case SQL_TYPE_TIME:
	case SQL_TIME:
		nCType = SQL_C_TIME;
		break;

	case SQL_TYPE_TIMESTAMP:
	case SQL_TIMESTAMP:
		nCType = SQL_C_TIMESTAMP;
		break;

	default:
		nCType = SQL_C_CHAR;//余下的用字符串形式获取
		break;
	}
	return nCType;
}
	
short XODBCRecordset::GetXODBCTypeFromSqlType( short nSqlType)
{
	short nXODBCType = 0;	
	switch( nSqlType )
	{
	case SQL_CHAR:
	case SQL_VARCHAR:
	case SQL_LONGVARCHAR:
		nXODBCType = XDBVT_STRING;
		break;

	case SQL_WCHAR:
	case SQL_WVARCHAR:
	case SQL_WLONGVARCHAR:
		nXODBCType = XDBVT_WSTRING;
		break;

	case SQL_DECIMAL:
	case SQL_NUMERIC:
		nXODBCType = XDBVT_STRING;
		break;

	case SQL_BIT:
		nXODBCType = XDBVT_BOOL;
		break;

	case SQL_TINYINT:
		nXODBCType = XDBVT_UCHAR; //用unsigned char 获取
		break;

	case SQL_SMALLINT:
		nXODBCType = XDBVT_SHORT;
		break;

	case SQL_INTEGER:
		nXODBCType = XDBVT_LONG;
		break;

	case SQL_GUID:
		nXODBCType = XDBVT_LONG;  //用long获取，可能会出现转换错误
		break;

	case SQL_BIGINT:
		nXODBCType = XDBVT_LONGLONG;
		break;

	case SQL_REAL:
		nXODBCType = XDBVT_SINGLE;
		break;

	case SQL_FLOAT:
	case SQL_DOUBLE:
		nXODBCType = XDBVT_DOUBLE;
		break;

	case SQL_BINARY:
	case SQL_VARBINARY:
	case SQL_LONGVARBINARY:
		nXODBCType = XDBVT_BINARY;
		break;

	case SQL_TYPE_DATE:
	case SQL_DATE:
		nXODBCType = XDBVT_DATE;
		break;

	case SQL_TYPE_TIME:
	case SQL_TIME:
		nXODBCType = XDBVT_TIME;
		break;

	case SQL_TYPE_TIMESTAMP:
	case SQL_TIMESTAMP:
		nXODBCType = XDBVT_TIMESTAMP;
		break;

	default:
		nXODBCType = XDBVT_STRING;//余下的用字符串形式获取
		break;
	}
	return nXODBCType;
}

long XODBCRecordset::GetTextLen(short nSQLType, SQLUINTEGER lPrecision)
{
	long nLen;

	if (nSQLType == SQL_LONGVARCHAR || nSQLType == SQL_LONGVARBINARY)
	{
		// Use a dummy length of 1 (will just get NULL terminator)
		//nLen = 1;
		nLen = 8000 + 1; 
	}
	
	else if(nSQLType == SQL_WLONGVARCHAR)
	{
		// Use a dummy length of DBCS 1
		//nLen = sizeof(short);
		nLen = 8000 + 1;
	}
	else if (nSQLType == SQL_WVARCHAR || nSQLType == SQL_WCHAR)
	{
		nLen =  (lPrecision  + 1)  * 2;
	}
	else
	{

		nLen = lPrecision + 1;

		switch (nSQLType)
		{
		case SQL_INTEGER:
		case SQL_SMALLINT:
			nLen++;  // '-' sign
			break;

		case SQL_NUMERIC:
		case SQL_DECIMAL:
		case SQL_FLOAT:
		case SQL_REAL:
		case SQL_DOUBLE:
			nLen += 2;  // '-' sign and decimal point
			break;
		default:
			break;
		}
	}

	return nLen;
}

void  XODBCRecordset::FreeFieldValueList()
{
	for( int i = 0; i < (int)m_varList.size(); i++)
	{
		m_varList.at(i).Clear();
	}
	m_varList.clear();
}

void  XODBCRecordset::AllocFieldValueList()
{
	short i;
	XODBCVariant varValue;
	for( i = 0;i < m_nResultCols; i++)
	{
		varValue.m_nType = GetXODBCTypeFromSqlType(m_fieldList.at(i).m_nSQLType);
		switch (varValue.m_nType)
		{
		case XDBVT_BOOL:
			varValue.m_pboolVal = new XBOOL;
			*varValue.m_pboolVal = 0;  
			break;

		case XDBVT_UCHAR:
			varValue.m_pchVal  = new XUCHAR;
			*varValue.m_pchVal = 0;
			break;

		case XDBVT_SHORT:
			varValue.m_pshVal = new XSHORT;
			*varValue.m_pshVal = 0;
			break;

		case XDBVT_LONG:
			varValue.m_plVal = new XLONG;
			*varValue.m_plVal = 0;
			break;

		case XDBVT_SINGLE:
			varValue.m_pfltVal = new XSINGLE;
			*varValue.m_pfltVal = 0.0;
			break;

		case XDBVT_DOUBLE:
			varValue.m_pdblVal = new XDOUBLE;
			*varValue.m_pdblVal = 0.0;
			break;

		case XDBVT_LONGLONG:
			varValue.m_pllVal = new XLONGLONG;
			*varValue.m_pllVal = 0;
			break;

		case XDBVT_DATE:
			varValue.m_pdateVal = new XDATE;
			break;

		case XDBVT_TIME:
			varValue.m_ptimeVal = new XTIME;
			break;

		case XDBVT_TIMESTAMP:
			varValue.m_ptsVal = new XTIMESTAMP;
			break;

		case XDBVT_STRING:
			varValue.m_pstringVal = new XSTRING();
			if( !varValue.m_pstringVal->AllocBuffer(GetTextLen(m_fieldList.at(i).m_nSQLType,m_fieldList.at(i).m_lPrecision)))
			{
				XODBCError error;
				error.SetErrorText("字段绑定值在为字符串分配内存时失败");
				AfxThrowXODBCException(error);
			}
			break;

		case XDBVT_WSTRING:
			varValue.m_pwstringVal = new XWSTRING();
			if( !varValue.m_pwstringVal->AllocBuffer(GetTextLen(m_fieldList.at(i).m_nSQLType,m_fieldList.at(i).m_lPrecision)/2))
			{
				XODBCError error;
				error.SetErrorText("字段绑定值在为unicode字符串分配内存时失败");
				AfxThrowXODBCException(error);
			}
			break;

		case XDBVT_BINARY:

			varValue.m_pbinaryVal = new XBINARY();
			if( !varValue.m_pbinaryVal->AllocBuffer(GetTextLen(m_fieldList.at(i).m_nSQLType,m_fieldList.at(i).m_lPrecision)))
			{
				XODBCError error;
				error.SetErrorText("字段绑定值在为二进制值分配内存时失败");
				AfxThrowXODBCException(error);
			}
			break;
		default:
			break;
		}
		m_varList.push_back(varValue);

	}
}

void * XODBCRecordset::GetFieldBuffer(SQLUSMALLINT nIndex, SQLUINTEGER &lLength)
{
	void *pvData = NULL;
	XODBCVariant varValue;
	if( m_varList.size() != m_nResultCols)
	{
		XODBCError error;
		error.SetErrorText("字段未绑定完全");
		AfxThrowXODBCException(error);
	}

	varValue = m_varList.at(nIndex);
	switch(varValue.m_nType)
	{
		case XDBVT_BOOL:
			pvData = varValue.m_pboolVal; 
			break;

		case XDBVT_UCHAR:
			pvData = varValue.m_pchVal;
			break;

		case XDBVT_SHORT:
			pvData = varValue.m_pshVal;
			break;

		case XDBVT_LONG:
			pvData = varValue.m_plVal;
			break;

		case XDBVT_SINGLE:
			pvData = varValue.m_pfltVal;
			break;

		case XDBVT_DOUBLE:
			pvData = varValue.m_pdblVal;
			break;
		case XDBVT_LONGLONG:
			pvData = varValue.m_pllVal;
			break;
		case XDBVT_DATE:
			pvData = varValue.m_pdateVal;
			break;
		case XDBVT_TIME:
			pvData = varValue.m_ptimeVal;
			break;
		case XDBVT_TIMESTAMP:
			pvData = varValue.m_ptsVal;
			break;

		case XDBVT_STRING:
			pvData = varValue.m_pstringVal->GetBuffer();
			break;

		case XDBVT_WSTRING:
			pvData = varValue.m_pwstringVal->GetBuffer();
			break;

		case XDBVT_BINARY:
			pvData = varValue.m_pbinaryVal->GetBuffer();
			break;
		default:
			break;
	}
	
	lLength = GetTextLen(m_fieldList.at(nIndex).m_nSQLType,m_fieldList.at(nIndex).m_lPrecision);
	
	return pvData;
}

void  XODBCRecordset::BindFieldValue()
{
	void       * pvData  = NULL;
	SQLUINTEGER  lLength = 0;
	SQLUSMALLINT i;
	FreeFieldValueList();
	m_varList.clear();
	if( m_nResultCols == 0)
	{
		return;
	}
	AllocFieldValueList();
	
	for( i = 0; i < m_nResultCols; i++)
	{
		pvData = GetFieldBuffer( i, lLength);
		short nCType = GetCTypeFromSqlType( m_fieldList.at(i).m_nSQLType );
		m_nRetcode = SQLBindCol( m_hstmt, i+1, nCType, pvData, lLength, &m_fieldList.at(i).m_nLength);
		if( !Check(m_nRetcode))
		{
			SetLastError(StatementError);
			AfxThrowXODBCException(m_XError[1]);
		}
	}
}

void XODBCRecordset::GetFieldValue(int nColIndex, XDBVariant &varValue)
{
	if( nColIndex < 0 || nColIndex >= m_nResultCols)
	{
		XODBCError error;
		error.SetErrorText("字段下标越界!");
		AfxThrowXODBCException(error);
	}
	m_varList.at(nColIndex).SetXDBVariant(varValue,m_fieldList.at(nColIndex).m_nLength);
}

void XODBCRecordset::GetFieldValue(string strColName, XDBVariant &varValue)
{
	int nColIndex = -1;
	if( m_nResultCols <= 0)
	{
		return;
	}
	nColIndex = GetFieldIndexByName(strColName);
	if( nColIndex < 0 || nColIndex > (int)m_fieldList.size())
	{
		XODBCError error;
		error.SetErrorText("找不到匹配的字段名");
		AfxThrowXODBCException(error);
	}
	GetFieldValue(nColIndex,varValue);
}
	
void XODBCRecordset::GetFieldValue(int nColIndex, string &strValue)
{
	if( nColIndex < 0 || nColIndex >= m_nResultCols)
	{
		XODBCError error;
		error.SetErrorText("字段下标越界!");
		AfxThrowXODBCException(error);
	}
	XDBVariant varValue;
	XODBCVariant xodbcValue = m_varList.at(nColIndex);
	xodbcValue.SetXDBVariant(varValue,m_fieldList.at(nColIndex).m_nLength);
	if( m_fieldList.at(nColIndex).m_nLength == -1)
	{
		strValue = "<NULL>";
	}
	else
	{
		strValue = varValue.AsString();
	}
	varValue.Clear();
}
	
void XODBCRecordset::GetFieldValue(string strColName, string &strValue)
{
	int nColIndex = -1;
	if( m_nResultCols <= 0)
	{
		return;
	}
	nColIndex = GetFieldIndexByName(strColName);
	if( nColIndex < 0 || nColIndex > (int)m_fieldList.size())
	{
		XODBCError error;
		error.SetErrorText("找不到匹配的字段名");
		AfxThrowXODBCException(error);
	}
	GetFieldValue(nColIndex,strValue);
}

void XODBCRecordset::GetFieldValue(int nColIndex, wstring &wstrValue)
{
	if( nColIndex < 0 || nColIndex >= m_nResultCols)
	{
		XODBCError error;
		error.SetErrorText("字段下标越界!");
		AfxThrowXODBCException(error);
	}
	XDBVariant varValue;
	XODBCVariant xodbcValue = m_varList.at(nColIndex);
	xodbcValue.SetXDBVariant(varValue,m_fieldList.at(nColIndex).m_nLength);

	if( m_fieldList.at(nColIndex).m_nLength == -1)
	{
		wstrValue = L"<NULL>";
	}
	else
	{
		wstrValue = varValue.AsWString();
	}
	varValue.Clear();
}
	
void XODBCRecordset::GetFieldValue(string strColName, wstring &wstrValue)
{
	int nColIndex = -1;
	if( m_nResultCols <= 0)
	{
		return;
	}
	nColIndex = GetFieldIndexByName(strColName);
	if( nColIndex < 0 || nColIndex > (int)m_fieldList.size())
	{
		XODBCError error;
		error.SetErrorText("找不到匹配的字段名");
		AfxThrowXODBCException(error);
	}
	GetFieldValue(nColIndex,wstrValue);
}

void XODBCRecordset::SetFieldValue(int nColIndex, XDBVariant varValue)
{
	if( nColIndex < 0 || nColIndex >= m_nResultCols)
	{
		XODBCError error;
		error.SetErrorText("字段下标越界!");
		AfxThrowXODBCException(error);
	}

	XODBCVariant xodbcValue = m_varList.at(nColIndex);
	bool  bPointValid = true;

	if( varValue.m_nType != xodbcValue.m_nType)
	{
		XODBCError error;
		error.SetErrorText("字段类型不匹配!");
		AfxThrowXODBCException(error);
	}

	/*switch( varValue.m_nType )
	{
	case XDBVT_STRING:
		if( varValue.m_pstringVal == NULL)
		{
			bPointValid = false;
		}
		break;

	case XDBVT_WSTRING:
		if( varValue.m_pwstringVal == NULL)
		{
			bPointValid = false;
		}
		break;

	case XDBVT_BINARY:
		if( varValue.m_pbinaryVal == NULL)
		{
			bPointValid = false;
		}
		break;
	default:
		break;
	}

	if( !bPointValid )
	{
		XODBCError error;
		error.SetErrorText("字段值无效!");
		AfxThrowXODBCException(error);
	}
*/
	if( !xodbcValue.SetValue(varValue) )
	{
		XODBCError error;
		error.SetErrorText("字段值长度过长!");
		AfxThrowXODBCException(error);
	}
}

void XODBCRecordset::SetFieldValue(string strColName, XDBVariant varValue)
{
	int nColIndex = -1;
	if( m_nResultCols <= 0)
	{
		return;
	}
	nColIndex = GetFieldIndexByName(strColName);
	if( nColIndex < 0 || nColIndex > (int)m_fieldList.size())
	{
		XODBCError error;
		error.SetErrorText("找不到匹配的字段名");
		AfxThrowXODBCException(error);
	}
	SetFieldValue( nColIndex,varValue);
}


void XODBCRecordset::AddNew() 
{
	//添加记录
	m_nRetcode = SQLSetPos(m_hstmt,1,SQL_ADD,SQL_LOCK_NO_CHANGE);
	if( !Check(m_nRetcode) )
	{
		SetLastError( StatementError);
		AfxThrowXODBCException(m_XError[1]);
	}
}


void XODBCRecordset::Update()
{
	/*//加锁该行
	m_nRetcode = SQLSetPos(m_hstmt,1,SQL_POSITION,SQL_LOCK_EXCLUSIVE);
	if( !Check(m_nRetcode) )
	{
		SetLastError( StatementError);
		AfxThrowXODBCException(m_XError[1]);
	}*/

	//更新记录
	m_nRetcode = SQLSetPos(m_hstmt,1,SQL_UPDATE,SQL_LOCK_NO_CHANGE);
	if( !Check(m_nRetcode) )
	{
		SetLastError( StatementError);
		AfxThrowXODBCException(m_XError[1]);
	}

	/*
	//解锁该行
	m_nRetcode = SQLSetPos(m_hstmt,1,SQL_POSITION,SQL_LOCK_UNLOCK);
	if( !Check(m_nRetcode) )
	{
		SetLastError( StatementError);
		AfxThrowXODBCException(m_XError[1]);
	}
*/

}

void XODBCRecordset::Delete()
{
	//删除记录
	m_nRetcode = SQLSetPos(m_hstmt,1,SQL_DELETE,SQL_LOCK_NO_CHANGE);
	if( !Check(m_nRetcode) )
	{
		SetLastError( StatementError);
		AfxThrowXODBCException(m_XError[1]);
	}
}


bool XODBCRecordset::Check(SQLRETURN nRetcode) const
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

void XODBCRecordset::GetLastError(XErrorType nErrorType, XODBCError &XError)
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


bool XODBCRecordset::SetLastError(XErrorType nErrorType, SQLHSTMT hstmt)
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
			retcode = SQLError(NULL,m_pDatabase->m_hdbc,NULL,(unsigned char*)szState,&lNativeError,(unsigned char*)lpszError,256,0);
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

