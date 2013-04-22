#ifndef XODBC_H_TABLE
#define XODBC_H_TABLE

#include "testXODBC.h"

class XODBCTable :
	public XODBCRecordset
{
public:
	XODBCTable(XODBCDatabase * pDatabase = NULL ,string strTableName = "");
	~XODBCTable(void);

public:

	/*   ����XODBCTable����ı���������table�治����*/
	void SetTableName(string strTableName);

	/*  ���Զ���SQL��䴴����  */
	bool XODBCTable::CreateTable(string strSql);
	/*  �����ֶ���Ϣ�б��������  */
	bool CreateTable(vector<XFieldInfo> fieldInfoList);
    
	/*  ����һ�� */
	bool AddColumn(XFieldInfo fieldInfo);

	/*  �޸�һ��*/
    bool UpdateColumn(XFieldInfo fieldInfo);

	/*  ɾ��һ��*/
    bool DeleteColumn(string strColumnName);

	/* ������UNIQUE���� �����ڶ���ֶ� */
	bool CreateIndex(vector<string> strColumnNameList,string strIndexName = "",int nIndexType = INDEX_OTHER);
    /* ������UNIQUE���� �����ڵ����ֶ� */
	bool CreateIndex(string strColumnName,string strIndexName = "",int nIndexType = INDEX_OTHER);

	/* ɾ����UNIQUE���� */
 	bool DeleteIndexByIndexName(string strIndexName);
	bool DeleteIndexByColumnName(string strColumnName);
	
    
	/* ����NIQUE���� �����ڵ����ֶ�*/
	bool CreateUniqueIndex(vector<string> strColumnNameList,string strIndexName = "",int nIndexType = INDEX_OTHER);
	bool CreateUniqueIndex(string strColumnName,string strIndexName = "",int nIndexType = INDEX_OTHER);

	/* ɾ��UNIQUE���� */
    bool DeleteUniqueIndexByIndexName(string strIndexName);
	bool DeleteUniqueIndexByColumnName(string strColumnName);

    
	bool DeleteTable();

    vector<XFieldInfo> GetColumns();


private:
	string GetFieldStringOfOracle(XFieldInfo fieldInfo);
	string GetFieldStringOfMySQL(XFieldInfo fieldInfo);
	string GetFieldStringOfSQLServer(XFieldInfo fieldInfo);
	string GetFieldStringOfDB2(XFieldInfo fieldInfo);
	string GetFieldStringOfSybase(XFieldInfo fieldInfo);
	string GetFieldStringOfAccess(XFieldInfo fieldInfo);

	string GetFieldDataTypeOfDB2(XFieldInfo fieldInfo);

	bool ExecuteDDLSQL(string strSql);

	bool IsUniqueIndex(string strIndexName);
	bool DeleteIndex(string strIndexName);
	bool DeleteUniqueIndex(string strIndexName);

    //bool   GeneratefieldInfoList();
private:
	string                 m_strTableName;
	XDBTYPE                m_nDBType;
};

#endif