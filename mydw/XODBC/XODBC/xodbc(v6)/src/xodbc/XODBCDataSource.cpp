#include <XODBC/XODBCDataSource.h>
#include <xodbc/XODBCError.h>
#include <xodbc/XODBCException.h>

#include  <iostream>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMWriter.hpp>
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/DOMWriterFilter.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>
#include <xercesc/dom/DOMDocument.hpp>

XERCES_CPP_NAMESPACE_USE


namespace xodbc{

	HENV     XODBCDataSource:: m_henv;
	HDBC     XODBCDataSource:: m_hdbc;
	RETCODE  XODBCDataSource:: m_nRetcode;
	XDBTYPE  XODBCDataSource:: m_nCurrentDBType;

	STODBCMap XODBCDataSource:: m_stTableByODBC;
	STDBMap XODBCDataSource:: m_stTableByDb;

	

	string Transcode(const XMLCh* pxmlStr)
	{
		string str;
		//str += "#begin#";
		if(pxmlStr != NULL)
		{

			char* psz = XMLString::transcode( pxmlStr );
			str += psz;
			if( str.find("#text") != -1)
			{
				str = "";
			}
			XMLString::release( &psz );         
		}
		else
		{
			str = "";
		}
		//str += "#croco#";
		return str;
	}

XODBCDataSource::XODBCDataSource()
{

}

XODBCDataSource::~XODBCDataSource()
{
	
}

bool XODBCDataSource::InitEnv()
{
	m_nRetcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_henv);
	if( m_nRetcode != SQL_SUCCESS && m_nRetcode != SQL_SUCCESS_WITH_INFO )
	{
		return false;
	}
	m_nRetcode = SQLSetEnvAttr(m_henv,SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC3,0);
	if( m_nRetcode != SQL_SUCCESS && m_nRetcode != SQL_SUCCESS_WITH_INFO )
	{
		SQLSetEnvAttr(m_henv,SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC2,0);
	} 
	if( m_nRetcode != SQL_SUCCESS && m_nRetcode != SQL_SUCCESS_WITH_INFO )
	{
		return false;
	}
	return true;

}
	
void XODBCDataSource::FreeEnv()
{
	SQLFreeHandle( SQL_HANDLE_ENV, m_henv);
}


vector<string> XODBCDataSource::GetODBCDriverList()
{
	vector<string> strDriverList;
	SQLCHAR * szDriver= new SQLCHAR[256];
	SQLSMALLINT pcbDriver;
	SQLCHAR * szDesc= new SQLCHAR[256];
	SQLSMALLINT pcbDesc;

	strDriverList.clear();
	if(!InitEnv())
	{
		return strDriverList;
	}

	while( SQLDrivers(m_henv,SQL_FETCH_NEXT,szDriver,256,&pcbDriver,szDesc,256,&pcbDesc) == SQL_SUCCESS)
		{
			strDriverList.push_back((char *)szDriver); 
		}

	FreeEnv();
	delete szDriver;
	delete szDesc;

	return strDriverList;
}
	
vector<string> XODBCDataSource::GetAllDataSourceList()
{
	vector<string> strDSNList;
	SQLCHAR * szDSN= new SQLCHAR[256];
	SQLSMALLINT pcbDSN;
	SQLCHAR * szDesc= new SQLCHAR[256];
	SQLSMALLINT pcbDesc;

	strDSNList.clear();
	if(!InitEnv())
	{
		return strDSNList;
	}

	while( SQLDataSources(m_henv,SQL_FETCH_NEXT,szDSN,256,&pcbDSN,szDesc,256,&pcbDesc) == SQL_SUCCESS)
		{
			strDSNList.push_back((char *)szDSN); 
		}
		
	FreeEnv();
	delete szDSN;
	delete szDesc;
	
	return strDSNList;

}
	
vector<string> XODBCDataSource::GetDataSourceList(string strDriverName)
{
	vector<string> strDSNList;

	SQLCHAR * szDSN= new SQLCHAR[256];
	SQLSMALLINT pcbDSN;
	SQLCHAR * szDesc= new SQLCHAR[256];
	SQLSMALLINT pcbDesc;
	char * szDriver= new char[256];

	strDSNList.clear();
	if(!InitEnv())
	{
		return strDSNList;
	}

	while( SQLDataSources(m_henv,SQL_FETCH_NEXT,szDSN,256,&pcbDSN,szDesc,256,&pcbDesc) == SQL_SUCCESS)
		{	
			if (SQLGetPrivateProfileString("ODBC Data Sources",(char *)szDSN,"",szDriver,256,"ODBC.INI"))
			{
				
				if( !lstrcmpi(szDriver,(char *)strDriverName.c_str()) )
				{
					strDSNList.push_back((char *)szDSN); 
				}
			} 
	
		}
	
	FreeEnv();

	delete szDSN;
	delete szDesc;
	delete  szDriver;

	
	return strDSNList;
}


bool XODBCDataSource::AddDataSource(short nDSNType, string strDriverName, const char* strDSNString)
{
	if(SQLConfigDataSource(NULL,nDSNType,(char *)strDriverName.c_str(),strDSNString))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//************************************************************************************************//
//SQL Server;  Driver,Description,Server,Database,LastUser,在手动添加数据源时虽然有写密码，       //
//             但是注册表中没有出现密码这个键，程序中设置为Password                               //
//..MySQL..:   Driver,Description,Server,Database,User,Password                                   //
//Orcle:       Driver,Description,SERVER,UID,PWD,  但没有涉及到数据库或者路径，目录之类           //
//..Access..:  Driver,Description, DBQ,UID,   没有涉及到服务器和密码，但程序中设置有PWD这个键     //
//..dBase.. :  Driver,Description,DefaultDir,UID  没有涉及到服务器和密码,但程序中设置有PWD这个键  //
//..Excel.. :  Driver,Description, DBQ,UID,   没有涉及到服务器和密码,但程序中设置有PWD这个键      //
//..Para(dox)..: Driver,Description,DefaultDir,UID 没有涉及到服务器和密码,但程序中设置有PWD这个键 //
//..Text..:    Driver,Description,DefaultDir,UID   没有涉及到服务器和密码,但程序中设置有PWD这个键 //
//..Foxpro..:  Driver,Description,SourceDB    没有涉及到服务器,用户名和密码                       //
//************************************************************************************************//
bool  XODBCDataSource::AddDataSource(short nDSNType, string strDriverName, string strDSName, 
		                          string strDBName,string strServerName, string strUserName, 
								 string strPassword, string strDesc)
{
	if(!SQLSetConfigMode(nDSNType))
	{
		return false;
	}

	//检测驱动程序是否正确

	int i = 0;
	int flag = 0;
	vector<string> strDriverList = GetODBCDriverList();
	for( i = 0; i < (int)strDriverList.size(); i++)
	{
		if( strDriverList.at(i) == strDriverName)
		{
			flag = 1;
			break;
		}
	}

	if( flag == 0)
	{
		return false;
	}

	flag = 0;
	//检测是否已存在相应的数据源，如果存在则返回失败

	vector<string> strDataSourceList;
	strDataSourceList = GetAllDataSourceList();
	for( i = 0; i < (int)strDataSourceList.size(); i++)
	{
		if( strDataSourceList.at(i) == strDSName)
		{
			flag = 1;
			break;
		}
	}

    if( flag == 1)
	{
		return false;
	}
	
    
	if(!SQLWritePrivateProfileString("ODBC Data Sources",(char *)strDSName.c_str(),(char *)strDriverName.c_str(),"ODBC.INI"))
	{
		return false;
	}
//	添加驱动程序
	if(!SQLWritePrivateProfileString((char *)strDSName.c_str(),"Driver",(char *)strDriverName.c_str(),"ODBC.INI"))
	{
		 return false;
	}
//	添加描述
	if(!SQLWritePrivateProfileString((char *)strDSName.c_str(),"Description",(char *)strDesc.c_str(),"ODBC.INI"))
	{
		 return false;
	}
//	添加服务器
	if(strServerName !="")
	{
		if(!SQLWritePrivateProfileString((char *)strDSName.c_str(),"Server",(char *)strServerName.c_str(),"ODBC.INI"))
			return false;
	}
//	添加用户，密码
	if(strDriverName=="SQL Server")      //SQL Server
	{
		if(!SQLWritePrivateProfileString((char *)strDSName.c_str(),"LastUser",(char *)strUserName.c_str(),"ODBC.INI"))
		{
			return false;
		}
		if(!SQLWritePrivateProfileString((char *)strDSName.c_str(),"Password",(char *)strPassword.c_str(),"ODBC.INI"))
		{
			return false;
		}
	}
	else if(strDriverName.find("MySQL")!= -1)      //..MySQL..
	{
		if(!SQLWritePrivateProfileString((char *)strDSName.c_str(),"User",(char *)strUserName.c_str(),"ODBC.INI"))
		{
			return false;
		}
		if(!SQLWritePrivateProfileString((char *)strDSName.c_str(),"Password",(char *)strPassword.c_str(),"ODBC.INI"))
		{
			return false;
		}
	}
		else if(strDriverName.find("FoxPro")== -1)   //除了..FoxPro..外的其他的
		{
			if(!SQLWritePrivateProfileString((char *)strDSName.c_str(),"UID",(char *)strUserName.c_str(),"ODBC.INI"))
			{
				return false;
			}
			if(!SQLWritePrivateProfileString((char *)strDSName.c_str(),"PWD",(char *)strPassword.c_str(),"ODBC.INI"))
			{
				return false;
			}
		}
//	添加数据库
	if(strDriverName =="SQL Server" || strDriverName.find("MySQL")!= -1)  //"SQL Server"或者..MySQL..
	{
		if(!SQLWritePrivateProfileString((char *)strDSName.c_str(),"Database",(char *)strDBName.c_str(),"ODBC.INI"))
		{
			return false;
		}
	}
	else if(strDriverName.find("FoxPro")!= -1)    //..FoxPro..
	{
		if(!SQLWritePrivateProfileString((char *)strDSName.c_str(),"SourceDB",(char *)strDBName.c_str(),"ODBC.INI"))
		{
			return false;
		}
	}
		else if(strDriverName.find("Access")!= -1 || strDriverName.find("Excel")!= -1)//..Access..和..Excel..
		{
			if(!SQLWritePrivateProfileString((char *)strDSName.c_str(),"DBQ",(char *)strDBName.c_str(),"ODBC.INI"))
			{
				return false;
			}
		}
			else if(strDBName !="")  //oracle外其他的（因为orcle没有涉及数据库这个键，所以不用添加该键）
			{
				if(!SQLWritePrivateProfileString((char *)strDSName.c_str(),"DefaultDir",(char *)strDBName.c_str(),"ODBC.INI"))
				{
					return false;
				}
			}
	return true;
}

bool XODBCDataSource::UpdateDataSource(short nDSNType, string strDSName,string strDriverName, 
								 string strNewDSName, string strServerName, string strDBName, string strUserName, 
								 string strPassword, string strDesc)
{
	bool check= false;
    if(RemoveDataSource(nDSNType,strDSName))
	{
		check=AddDataSource(nDSNType,strDriverName,strNewDSName,strDBName,strServerName,strUserName,strPassword,strDesc);
	}
	return check;
}


bool XODBCDataSource::RemoveDataSource(short nDSNType,string strDSName)
{
	if(SQLSetConfigMode(nDSNType))
	{
		if(SQLRemoveDSNFromIni((char *)strDSName.c_str()))
		{
			return true;
		}
	}
	return false;
}

string  XODBCDataSource::GetDriverName(short nDSNType,string strDSName)
{
  	char* szBuffer=new char[256];
	szBuffer[0] = 0;
	string drivername;
	SQLSetConfigMode(nDSNType);	
	SQLGetPrivateProfileString("ODBC Data Sources",(char *)strDSName.c_str(),"",szBuffer,256,"ODBC.INI");	
//	SQLGetPrivateProfileString((char *)strDSName.c_str(),"Driver","",szBuffer,256,"ODBC.INI");
	drivername = szBuffer;
	delete szBuffer;
	return drivername;
}

string	XODBCDataSource::GetServerName(short nDSNType,string strDSName)
{
	char* szBuffer=new char[256];
	szBuffer[0] = 0;
	string servername;
	SQLSetConfigMode(nDSNType);
	if( !SQLGetPrivateProfileString((char *)strDSName.c_str(), "Server", "", szBuffer, 256, "ODBC.INI") )
	{
		if( SQLGetPrivateProfileString((char *)strDSName.c_str(), "ServerName", "", szBuffer, 256, "ODBC.INI") )
		{
			SQLGetPrivateProfileString((char *)strDSName.c_str(), "NetworkAddress", "", szBuffer, 256, "ODBC.INI");
		}
	}
	servername= szBuffer;
	delete szBuffer;
	return servername;
}

string XODBCDataSource::GetDBName(short nDSNType,string strDSName)
{
	char* szBuffer=new char[256];
	szBuffer[0] = 0;
	string DBname;
	SQLSetConfigMode(nDSNType);
	while(1)
	{
		if(SQLGetPrivateProfileString((char *)strDSName.c_str(), "Database", "",szBuffer,256, "ODBC.INI"))
		{ break; }
		if(SQLGetPrivateProfileString((char *)strDSName.c_str(), "DBQ", "",szBuffer,256, "ODBC.INI"))
		{ break; }
		if(SQLGetPrivateProfileString((char *)strDSName.c_str(), "SourceDB", "",szBuffer,256, "ODBC.INI"))
		{ break; }
		if(SQLGetPrivateProfileString((char *)strDSName.c_str(),"DefaultDir", "",szBuffer,256, "ODBC.INI"))
		{ break; }
		break;
	}
	DBname= szBuffer;
	delete szBuffer;
	return DBname;
}

string	XODBCDataSource::GetUserName(short nDSNType,string strDSName)
{
	char* szBuffer=new char[256];
	szBuffer[0] = 0;
	string userName;
	SQLSetConfigMode(nDSNType);
	while(1)
	{
		if(SQLGetPrivateProfileString((char *)strDSName.c_str(), "LastUser", "",szBuffer,256, "ODBC.INI"))
		{ break; }
		if(SQLGetPrivateProfileString((char *)strDSName.c_str(), "UID", "",szBuffer,256, "ODBC.INI"))
		{ break; }
		if(SQLGetPrivateProfileString((char *)strDSName.c_str(), "User", "",szBuffer,256, "ODBC.INI"))
		{ break; }
		if(SQLGetPrivateProfileString((char *)strDSName.c_str(), "UserID", "",szBuffer,256, "ODBC.INI"))
		{ break; }
		break;
	}
	userName= szBuffer;
	delete szBuffer;
	return userName;
}

string	XODBCDataSource::GetPassword(short nDSNType,string strDSName)
{
	char* szBuffer=new char[256];
	szBuffer[0] = 0;
	string password;
	SQLSetConfigMode(nDSNType);
	if(!SQLGetPrivateProfileString((char *)strDSName.c_str(), "Password", "", szBuffer, 256, "ODBC.INI"))
	{
		SQLGetPrivateProfileString((char *)strDSName.c_str(), "PWD", "", szBuffer, 256, "ODBC.INI");
	}
	password= szBuffer;
	delete szBuffer;
	return password;
}

string	XODBCDataSource::GetDesc(short nDSNType,string strDSName)
{
	char* szBuffer=new char[256];
	szBuffer[0] = 0;
	string description;
	SQLSetConfigMode(nDSNType);
	SQLGetPrivateProfileString((char *)strDSName.c_str(), "Description", "", szBuffer, 256, "ODBC.INI");
	description= szBuffer;
	delete szBuffer;
	return description;
}


bool XODBCDataSource::GetDataSourceInfo(short nDSNType,string strDSName,string &strDriverName,
									string &strServerName, string &strDBName, string &strUserName, 
								    string &strPassword, string &strDesc)
{
  	strDriverName = GetDriverName(nDSNType, strDSName);
	strServerName = GetServerName(nDSNType, strDSName);
	strDBName     = GetDBName(nDSNType, strDSName);
	strUserName   = GetUserName(nDSNType, strDSName);
	strPassword   = GetPassword(nDSNType, strDSName);
	strDesc       = GetDesc(nDSNType, strDSName);
	return true;
}

bool XODBCDataSource::TestDataSource(short nDSNType, string strDSName, string UserName , string strPassword)
{
	bool check = true;
	if(!InitEnv())
	{
		return false;
	}

	m_nRetcode = SQLAllocHandle(SQL_HANDLE_DBC, m_henv, &m_hdbc);
	if (m_nRetcode != SQL_SUCCESS && m_nRetcode !=SQL_SUCCESS_WITH_INFO)
	{
		check = false;
		FreeEnv();
		return check;
	}

	SQLSetConfigMode(nDSNType);

	m_nRetcode= SQLConnect(m_hdbc,(unsigned char *)strDSName.c_str(),SQL_NTS,(unsigned char *)UserName.c_str(),SQL_NTS,
		  (unsigned char *)strPassword.c_str(),SQL_NTS);
	if (m_nRetcode == SQL_SUCCESS || m_nRetcode ==SQL_SUCCESS_WITH_INFO)
	{
		check = true;
		SQLDisconnect(m_hdbc);
	}
	else
	{
		check = false;
	}

	/* 因为sqlserver的连接太快断开会出错，所以暂时的解决办法是假设遇到sqlserver的驱动程序 则不断开  */

	if( GetDBType(BOTH_DSN,strDSName) != DB_SQLSERVER)
	{
		SQLFreeHandle( SQL_HANDLE_DBC, m_hdbc);	
	}

	FreeEnv();
	return check;
}

XDBTYPE XODBCDataSource::GetDBType(short nDSNType, string strDSName)
{	
	//需要重新写,直接从XODBCDatabase中获取
	string strDriverName;
	strDriverName = GetDriverName(nDSNType,strDSName);
	if( strDriverName == "" )
	{
		return DB_ERROR;
	}

	if(strDriverName.find("MySQL") != -1)
	{
		return DB_MYSQL;
	}
	if(strDriverName.find("SQL Server") != -1)
	{
		return DB_SQLSERVER;
	}
	if(strDriverName.find("DB2") != -1)
	{
		return DB_DB2;
	}
	if(strDriverName.find("Oracle") != -1)
	{
		return DB_ORACLE;
	}
	if(strDriverName.find("DB2") != -1)
	{
		return DB_DB2;
	}
	if(strDriverName.find("Sybase") != -1)
	{
		return DB_SYBASE;
	}
	if(strDriverName.find("Access") != -1)
	{
		return DB_ACCESS;
	}
	return DB_UNKNOWN;
}


string XODBCDataSource::GetSQLType(XDBTYPE nDBType,short nSQLType)
{
	InitSQLTypeTable(nDBType);
	return LookUpSQLTypeTable(nSQLType);
}


void XODBCDataSource:: InitSQLTypeTable(XDBTYPE nDBType)
{
	InitSQLTypeTableByODBC();
	if( m_nCurrentDBType == nDBType)
	{
		return;
	}
	m_stTableByDb.clear();
	m_nCurrentDBType = nDBType;
	switch(nDBType)
	{
		case xodbc::DB_MYSQL:
			InitSQLTypeTableFromXml("DB_MYSQL");
			break;
		case xodbc::DB_SQLSERVER:
			InitSQLTypeTableFromXml("DB_SQLSERVER");
			break;
		case xodbc::DB_DB2:
			InitSQLTypeTableFromXml("DB_DB2");
			break;
		case xodbc::DB_ORACLE:
			InitSQLTypeTableFromXml("DB_ORACLE");
			break;
		case xodbc::DB_SYBASE:
			InitSQLTypeTableFromXml("DB_SYBASE");
			break;
		case xodbc::DB_ACCESS:
			InitSQLTypeTableFromXml("DB_ACCESS");
			break;
		default:
			InitSQLTypeTableFromXml("");
			break;
	}
}

void  XODBCDataSource:: InitSQLTypeTableByODBC()
{
	if(m_stTableByODBC.size() <= 0)
	{
		m_stTableByODBC[SQL_CHAR]          = "SQL_CHAR";
		m_stTableByODBC[SQL_VARCHAR]       = "SQL_VARCHAR";
		m_stTableByODBC[SQL_LONGVARCHAR]   = "SQL_LONGVARCHAR";
		m_stTableByODBC[SQL_WCHAR]         = "SQL_WCHAR";
		m_stTableByODBC[SQL_WVARCHAR]      = "SQL_WVARCHAR";
		m_stTableByODBC[SQL_WLONGVARCHAR]  = "SQL_WLONGVARCHAR";
		m_stTableByODBC[SQL_DECIMAL]       = "SQL_DECIMAL";
		m_stTableByODBC[SQL_NUMERIC]       = "SQL_NUMERIC";
		m_stTableByODBC[SQL_BIT]		   = "SQL_BIT";
		m_stTableByODBC[SQL_TINYINT]       = "SQL_TINYINT";
		m_stTableByODBC[SQL_SMALLINT]	   = "SQL_SMALLINT";
		m_stTableByODBC[SQL_INTEGER]       = "SQL_INTEGER";
		m_stTableByODBC[SQL_GUID]          = "SQL_GUID";
		m_stTableByODBC[SQL_BIGINT]        = "SQL_BIGINT";
		m_stTableByODBC[SQL_REAL]		   = "SQL_REAL";
		m_stTableByODBC[SQL_FLOAT]         = "SQL_FLOAT";
		m_stTableByODBC[SQL_DOUBLE]        = "SQL_DOUBLE";
		m_stTableByODBC[SQL_BINARY]        = "SQL_BINARY";
		m_stTableByODBC[SQL_VARBINARY]     = "SQL_VARBINARY";
		m_stTableByODBC[SQL_LONGVARBINARY] = "SQL_LONGVARBINARY";
		m_stTableByODBC[SQL_TYPE_DATE]     = "SQL_TYPE_DATE";
		m_stTableByODBC[SQL_DATE]          = "SQL_DATE";
		m_stTableByODBC[SQL_TYPE_TIME]     = "SQL_TYPE_TIME";
		m_stTableByODBC[SQL_TIME]          = "SQL_TIME";
		m_stTableByODBC[SQL_TYPE_TIMESTAMP]= "SQL_TYPE_TIMESTAMP";
		m_stTableByODBC[SQL_TIMESTAMP]     = "SQL_TIMESTAMP";
	}
}

void  XODBCDataSource:: InitSQLTypeTableFromXml(string strDBType)
{
	XMLPlatformUtils::Initialize();
	try
	{
		static const XMLCh gLS[] = { chLatin_L, chLatin_S, chNull };
		DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(gLS);
		DOMBuilder        *parser = ( ( DOMImplementationLS* )impl )->createDOMBuilder ( DOMImplementationLS::MODE_SYNCHRONOUS, 0);

		// 解析XML文件

		xercesc::DOMDocument* doc = (xercesc::DOMDocument*)parser->parseURI( "xml/sqltype.xml" );
		//void * doc = NULL;

		// 通过DOM操纵XML文件
		// 获得XML文件根节点
		if(doc != NULL)
		{
			DOMNode* root = doc->getDocumentElement();

			if(root != NULL)
			{
				const XMLCh* pxml; 
				if(root->hasChildNodes())
				{
					DOMNode* dbTypeNode = root->getFirstChild();
					for(; dbTypeNode ; dbTypeNode = dbTypeNode->getNextSibling())
					{
						if(dbTypeNode->hasAttributes())
						{
							DOMNamedNodeMap* pAttrs = dbTypeNode->getAttributes();
							DOMNode* pAttr = pAttrs->item(0);
							pxml = pAttr->getNodeValue();
							string strType = Transcode(pxml);
							if(strDBType == strType)
							{
								//cout<<strDBType.c_str()<<endl;
								//system("pause");
								if(dbTypeNode->hasChildNodes())
								{
									DOMNode* dataTypeNode = dbTypeNode->getFirstChild();
									for(;dataTypeNode;dataTypeNode = dataTypeNode->getNextSibling())
									{
										pxml = dataTypeNode->getNodeName();
										string strODBCType = Transcode(pxml);
										if(strODBCType == "")
										{
											continue;
										}
										pxml = dataTypeNode->getTextContent();
										string strSQLType = Transcode(pxml);
										m_stTableByDb[strODBCType] = strSQLType;

									}
								}
							}
						}
					}
				}
				
			}
			// 最后要释放DOM Parser
		}
		else
		{
			//cout<<"读取XML文档失败"<<endl;
		}
		parser->release();
	}
	catch(...)
	{
		cout<<"加载xml文件出错！"<<endl;
	}
	XMLPlatformUtils::Terminate();
}

string  XODBCDataSource::LookUpSQLTypeTable(short nSQLType)
{
	return m_stTableByDb[m_stTableByODBC[nSQLType]];
}

string XODBCDataSource::GetDSNameFromDSNString(const string &strDSNString)
{
	string   strDSName;
	if( strDSNString.empty())
	{
		strDSName = "";
		return strDSName;
	}
	
	const char * p = strDSNString.c_str();
	char * q = strstr(p,"DSN=");
	if( q  == NULL)
	{
		strDSName = "";
		return strDSName;
	}
	q = q + 4;
	char * s = strstr((const char *)q,",");
	char * t = strstr((const char *)q,";");
	if( s == NULL && t ==NULL )
	{
		s = q + strlen(q);
	}
	else if( s != NULL && t != NULL)
	{
		//取较短的字串
		if( s - q > t - q )
		{
			s = t;
		}
	}
	else if( s == NULL)
	{
		s = t;
	}
	
	char * temp = new char[s - q + 1];
	strncpy(temp , q, s - q);
	temp[s - q] = 0;
	strDSName = temp;
	delete temp;

	return strDSName;
}

string XODBCDataSource::GetUserNameFromDSNString(const string &strDSNString)
{
	string   strUserName;
	if( strDSNString.empty())
	{
		strUserName = "";
		return strUserName;
	}
	
	const char * p = strDSNString.c_str();
	char * q = strstr(p,"UID=");
	if( q  != NULL)
	{
		q = q + 4;
	}
	else 
	{
		q = strstr(p,"User=");
		if(  q != NULL )
		{
			q = q + 5;
		}
		else
		{
			strUserName = "";
			return strUserName;
		}
	}

	char * s = strstr((const char *)q,",");
	char * t = strstr((const char *)q,";");
	if( s == NULL && t ==NULL )
	{
		s = q + strlen(q);
	}
	else if( s != NULL && t != NULL)
	{
		//取较短的字串
		if( s - q > t - q )
		{
			s = t;
		}
	}
	else if( s == NULL)
	{
		s = t;
	}
	
	char * temp = new char[s - q + 1];
	strncpy(temp , q, s - q);
	temp[s - q] = 0;
	strUserName = temp;
	delete temp;

	return strUserName;
}

string XODBCDataSource::GetPasswordFromDSNString(const string &strDSNString)
{
	string   strPassword;
	if( strDSNString.empty())
	{
		strPassword = "";
		return strPassword;
	}
	
	const char * p = strDSNString.c_str();
	char * q = strstr(p,"PWD=");
	if( q  != NULL)
	{
		q = q + 4;
	}
	else 
	{
		q = strstr(p,"Password=");
		if(  q != NULL )
		{
			q = q + 9;
		}
		else
		{
			strPassword = "";
			return strPassword;
		}
	}
	
	char * s = strstr((const char *)q,",");
	char * t = strstr((const char *)q,";");
	if( s == NULL && t ==NULL )
	{
		s = q + strlen(q);
	}
	else if( s != NULL && t != NULL)
	{
		//取较短的字串
		if( s - q > t - q )
		{
			s = t;
		}
	}
	else if( s == NULL)
	{
		s = t;
	}
	
	char * temp = new char[s - q + 1];
	strncpy(temp , q, s - q);
	temp[s - q] = 0;
	strPassword = temp;
	delete temp;

	return strPassword;
}



}

