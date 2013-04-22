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
	/*       ��ʼ�� XODBCDataSource ����                                    */
	/************************************************************************/
	XODBCDataSource();

	/************************************************************************/
	/*       ��� XODBCDataSource����                                       */
	/************************************************************************/ 
	~XODBCDataSource();

	/************************************************************************/
	/*       ��ȡϵͳ������ODBC�����������Ƶ��б�                           */
	/************************************************************************/              
	static vector<string> GetODBCDriverList();

	/************************************************************************/
	/*        ��ȡ��������Դ���Ƶ��б�                                      */
	/************************************************************************/
	static vector<string> GetAllDataSourceList();

	/************************************************************************/
	/*        ��ȡָ���������������Դ�б�                                  */
	/************************************************************************/
	static vector<string> GetDataSourceList(string strDriverName);


	/************************************************************************/
	/*             ��DSN�ַ�����������Դ                                    */
	/************************************************************************/
	static bool AddDataSource(short nDSNType, string strDriverName, const char * strDSNString);

	/************************************************************************/
	/*             �ö������ʽ��������Դ                                   */
	/************************************************************************/
	static bool AddDataSource(short nDSNType, string strDriverName, string strDSName, 
		                         string strDBName,string strServerName="", string strUserName = "", 
								 string strPassword = "", string strDesc = "");

	/************************************************************************/
	/*             ���´��ڵ�����Դ                                         */
	/************************************************************************/
	static bool UpdateDataSource(short nDSNType, string strDSName,string strDriverName, 
								 string strNewDSName, string strServerName, string strDBName, string strUserName, 
								 string strPassword, string strDesc);

	/************************************************************************/
	/*             �Ƴ�����Դ                                               */
	/************************************************************************/
	static bool	RemoveDataSource(short nDSNType,string strDSName);

	/************************************************************************/
	/*            ��ȡ����Դ�����Ϣ                                        */
	/************************************************************************/
	static bool GetDataSourceInfo(short nDSNType,string strDSName,string &strDriverName,
								string &strServerName, string &strDBName, string &strUserName, 
								string &strPassword, string &strDesc);

	/************************************************************************/
	/*             ��ȡָ������Դ������������                               */
	/************************************************************************/
	static string GetDriverName(short nDSNType,string strDSName);

	/************************************************************************/
	/*             ��ȡָ������Դ�ķ�������                                 */
	/************************************************************************/
	static string GetServerName(short nDSNType,string strDSName);

	/************************************************************************/
	/*             ��ȡָ������Դ�����ݿ���                                 */
	/************************************************************************/
	static string GetDBName(short nDSNType,string strDSName);

	/************************************************************************/
	/*             ��ȡָ������Դ���û���                                   */
	/************************************************************************/
	static string GetUserName(short nDSNType,string strDSName);

	/************************************************************************/
	/*             ��ȡָ������Դ������                                     */
	/************************************************************************/
	static string GetPassword(short nDSNType,string strDSName);

	/************************************************************************/
	/*             ��ȡָ������Դ������                                     */
	/************************************************************************/
	static string GetDesc(short nDSNType,string strDSName);

	/************************************************************************/
	/*             ��������Դ�Ƿ����ӳɹ�                                   */
	/************************************************************************/
	static bool  TestDataSource(short nDSNType, string strDSName, string UserName = "", string strPassword = "");

    /************************************************************************/
	/*             ����ָ������Դ�����ݿ�����                               */
	/************************************************************************/
	static XDBTYPE GetDBType(short nDSNType, string strDSName);

    /************************************************************************/
	/*             ��ODBC SQL����ת��Ϊָ�����ݿ��ʵ������                 */
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
