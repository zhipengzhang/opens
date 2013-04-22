#ifndef XODBCDATASOURCE_H_
#define XODBCDATASOURCE_H_

#include <xodbc/XODBCGlobal.h>
#include <map>

namespace xodbc{


typedef map<int,string>     STODBCMap;
typedef map<string,string>  STDBMap;

class XODBCDataSource
{
public:

	/************************************************************************/
	/*       初始化 XODBCDataSource 环境                                    */
	/************************************************************************/
	XODBCDataSource();

	/************************************************************************/
	/*       清空 XODBCDataSource环境                                       */
	/************************************************************************/ 
	~XODBCDataSource();

	/************************************************************************/
	/*       获取系统中所有ODBC驱动程序名称的列表                           */
	/************************************************************************/              
	static vector<string> GetODBCDriverList();

	/************************************************************************/
	/*        获取所有数据源名称的列表                                      */
	/************************************************************************/
	static vector<string> GetAllDataSourceList();

	/************************************************************************/
	/*        获取指定驱动程序的数据源列表                                  */
	/************************************************************************/
	static vector<string> GetDataSourceList(string strDriverName);


	/************************************************************************/
	/*             用DSN字符串创建数据源                                    */
	/************************************************************************/
	static bool AddDataSource(short nDSNType, string strDriverName, const char * strDSNString);

	/************************************************************************/
	/*             用多参数形式创建数据源                                   */
	/************************************************************************/
	static bool AddDataSource(short nDSNType, string strDriverName, string strDSName, 
		                         string strDBName,string strServerName="", string strUserName = "", 
								 string strPassword = "", string strDesc = "");

	/************************************************************************/
	/*             更新存在的数据源                                         */
	/************************************************************************/
	static bool UpdateDataSource(short nDSNType, string strDSName,string strDriverName, 
								 string strNewDSName, string strServerName, string strDBName, string strUserName, 
								 string strPassword, string strDesc);

	/************************************************************************/
	/*             移除数据源                                               */
	/************************************************************************/
	static bool	RemoveDataSource(short nDSNType,string strDSName);

	/************************************************************************/
	/*            获取数据源相关信息                                        */
	/************************************************************************/
	static bool GetDataSourceInfo(short nDSNType,string strDSName,string &strDriverName,
								string &strServerName, string &strDBName, string &strUserName, 
								string &strPassword, string &strDesc);

	/************************************************************************/
	/*             获取指定数据源的驱动程序名                               */
	/************************************************************************/
	static string GetDriverName(short nDSNType,string strDSName);

	/************************************************************************/
	/*             获取指定数据源的服务器名                                 */
	/************************************************************************/
	static string GetServerName(short nDSNType,string strDSName);

	/************************************************************************/
	/*             获取指定数据源的数据库名                                 */
	/************************************************************************/
	static string GetDBName(short nDSNType,string strDSName);

	/************************************************************************/
	/*             获取指定数据源的用户名                                   */
	/************************************************************************/
	static string GetUserName(short nDSNType,string strDSName);

	/************************************************************************/
	/*             获取指定数据源的密码                                     */
	/************************************************************************/
	static string GetPassword(short nDSNType,string strDSName);

	/************************************************************************/
	/*             获取指定数据源的描述                                     */
	/************************************************************************/
	static string GetDesc(short nDSNType,string strDSName);

	/************************************************************************/
	/*             测试数据源是否连接成功                                   */
	/************************************************************************/
	static bool  TestDataSource(short nDSNType, string strDSName, string UserName = "", string strPassword = "");

    /************************************************************************/
	/*             返回指定数据源的数据库类型                               */
	/************************************************************************/
	static XDBTYPE GetDBType(short nDSNType, string strDSName);

    /************************************************************************/
	/*             将ODBC SQL类型转化为指定数据库的实际类型                 */
	/************************************************************************/
	static string GetSQLType(XDBTYPE nDBType,short nSQLType);

	static string GetDSNameFromDSNString(const string &strDSNString);

	static string GetUserNameFromDSNString(const string &strDSNString);

	static string GetPasswordFromDSNString(const string &strDSNString);

private:
    
	static void    InitSQLTypeTable(XDBTYPE nDBType);
    static void    InitSQLTypeTableByODBC();
	static void    InitSQLTypeTableFromXml(string strDbType);
	static string  LookUpSQLTypeTable(short nSQLType);

	static bool    InitEnv();
	static void    FreeEnv();
private:

	static HENV     m_henv;
	static HDBC     m_hdbc;
	static RETCODE  m_nRetcode;
	static XDBTYPE  m_nCurrentDBType;
	
	static STODBCMap  m_stTableByODBC;
	static STDBMap    m_stTableByDb;


};

}

#endif
