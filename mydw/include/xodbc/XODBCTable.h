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

	/*   设置XODBCTable对象的表名，不管table存不存在*/
	void SetTableName(string strTableName);

	/*  以自定义SQL语句创建表  */
	bool XODBCTable::CreateTable(string strSql);
	/*  以用字段信息列表参数建表  */
	bool CreateTable(vector<XFieldInfo> fieldInfoList);
    
	/*  增加一列 */
	bool AddColumn(XFieldInfo fieldInfo);

	/*  修改一列*/
    bool UpdateColumn(XFieldInfo fieldInfo);

	/*  删除一列*/
    bool DeleteColumn(string strColumnName);

	/* 创建非UNIQUE索引 作用于多个字段 */
	bool CreateIndex(vector<string> strColumnNameList,string strIndexName = "",int nIndexType = INDEX_OTHER);
    /* 创建非UNIQUE索引 作用于单个字段 */
	bool CreateIndex(string strColumnName,string strIndexName = "",int nIndexType = INDEX_OTHER);

	/* 删除非UNIQUE索引 */
 	bool DeleteIndexByIndexName(string strIndexName);
	bool DeleteIndexByColumnName(string strColumnName);
	
    
	/* 创建NIQUE索引 作用于单个字段*/
	bool CreateUniqueIndex(vector<string> strColumnNameList,string strIndexName = "",int nIndexType = INDEX_OTHER);
	bool CreateUniqueIndex(string strColumnName,string strIndexName = "",int nIndexType = INDEX_OTHER);

	/* 删除UNIQUE索引 */
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