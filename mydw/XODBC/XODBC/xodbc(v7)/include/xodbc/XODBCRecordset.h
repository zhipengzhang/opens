#ifndef XODBCRECORDSET_H_
#define XODBCRECORDSET_H_

#include <xodbc/XODBCDatabase.h>

///////////////////////////////////////////////////////
// ����SQL �������;��Ⱥ�С��λ��һЩ˵��

/*
	һ����ֵ�������͵��еĴ�С�������Ĵ�С�����л����ʹ�õ����������е�����ʮ������������ݵľ�����������
	�ַ�����         �����е��ַ��ĳ��ȣ�
	��������         �еĴ�С����Ϊ������λ�Ĵ�С��
    DECIMAL          NUMERIC��10��3) ����Ϊ10
    BIT              1
	TINYINT          3
	SMALLINT         5
	INTEGER          10
	BIGINT           �з���Ϊ19���޷���Ϊ20
	REAL             7
	FLOAT            15
	DOUBLE           15
	DATE             10��yyyy-mm-dd��ʽ�����ַ�����
	TIME             8��hh-mm-ss��ʽ�����ַ�������9+s(hh:mm:ss[.fff...] ��ʽ�����ַ�����s���뾫��)
	TIMESTAMP        19(yyyy-mm-dd hh:mm:ss��ʽ�����ַ���)��20+s(yyyy-mm-dd hh:mm:ss[.fff...] ��ʽ�����ַ�����s���뾫��)
*/

/*
     SQL����                     �л������С��Ӧ������������
	 ���е��ַ��Ͷ���������      LENGTH
	 ���е��ַ�����              PRECISION
	 ���е�����ʱ�̺ͼ������    LENGTH
	 SQL-BIT                     LENGTH
	*/

namespace xodbc{

#define NO_NULLS           SQL_NO_NULLS           
#define	NULLABLE           SQL_NULLABLE          
#define NULLABLE_UNKNOWN   SQL_NULLABLE_UNKNOWN 

#define NO_PRIMARYKEY      0          
#define	PRIMARYKEY         1          
#define PRIMARYKEY_UNKNOWN 2 

#define NO_FOREIGNKEY      0           
#define	FOREIGNKEY         1          
#define FOREIGNKEY_UNKNOWN 2

class XFieldInfo
{
public:		
	string             m_strName; //����
	short              m_nSQLType;   //SQL��������
	long               m_nLength;    //�ֶ�ʵ�ʳ���
	unsigned long      m_lPrecision;//����
	short			   m_nScale;     //С��λ��С
	short			   m_nNullability; //��Ϊ��ֵNULLABLE,����Ϊ��ֵNO_NULLS��δ֪ NULLABLE_UNKNOWN
	 
	short			   m_nPrimaryKey;//������PRIMARYKEY��������NO_PRIMARYKEY��δ֪PRIMARYKEY_UNKNOWN

    short			   m_nForeignKey;//�����FOREIGNKEY�������NO_FOREIGNKEY��δ֪FOREIGNKEY_UNKNOWN

//Constructor
public:
	XFieldInfo();
	~XFieldInfo();
	void SetFieldInfo(XFieldInfo fieldInfo);

};

class XParamInfo
{
public:
	short m_nSQLType;           // SQL����
	unsigned long m_nPrecision; // ����
	short m_nScale;             // С��λ��С
	short m_nNullability; // �Ƿ��Ϊ��
      
//Constructor
    XParamInfo();
	~XParamInfo();
};


class XWSTRING
{
	public:
	XWSTRING();
	bool     AllocBuffer(long lLength); //Alloc String Buffer
	wchar_t  *GetBuffer(); //Get String Buffer
	long     GetLength();
	void     Free();
	private:
	wchar_t *m_wstrBuffer; // String Buffer
    long     m_lLength;   // String Length
};


class XSTRING
{
public:
	XSTRING();
	bool   AllocBuffer(long lLength); //Alloc String Buffer
	char  *GetBuffer(); //Get String Buffer
	long   GetLength();
	void   Free();
private:
	char * m_strBuffer; // String Buffer
    long   m_lLength;   // String Length
};


class XBINARY
{
// Constructors
public:
	XBINARY();
	bool   AllocBuffer(long lDataLength); //Alloc Buffer
	void * GetBuffer();               //Get  Buffer
	long   GetLength();               //Get Buffer Length
	void   Free();

//Attribute
public:
	long  m_lDataLength; //���ݳ���
	void * m_pData;     //���ݴ洢


};


#define  XNULL              NULL
#define  XBOOL              int
#define  XUCHAR             unsigned char
#define  XSHORT             short
#define  XINTEGER           int
#define  XLONG              long
#define  XSINGLE            float
#define  XDOUBLE            double
#define  XLONGLONG          SQLBIGINT
#define  XDATE              DATE_STRUCT
#define  XTIME              TIME_STRUCT
#define  XTIMESTAMP         TIMESTAMP_STRUCT
#define  XODBCSTRING        string
#define  XODBCWSTRING       wstring

//#define  XBINARY          XBINARY 

#define	 XDBVT_NULL          0
#define  XDBVT_BOOL          1
#define	 XDBVT_UCHAR         2
#define  XDBVT_SHORT         3
#define  XDBVT_LONG          4
#define  XDBVT_SINGLE        5
#define  XDBVT_DOUBLE        6
#define  XDBVT_LONGLONG      7
#define  XDBVT_DATE          8
#define  XDBVT_TIME          9
#define  XDBVT_TIMESTAMP     10
#define  XDBVT_STRING        11
#define  XDBVT_WSTRING       12
#define  XDBVT_BINARY        13


//XDBVaraint

class XDBVariant
{
public:
	short m_nType;
	union
	{
		XBOOL         m_boolVal;
		XUCHAR        m_chVal;
		XSHORT        m_shVal;
		XLONG         m_lVal;
		XSINGLE       m_fltVal;
		XDOUBLE       m_dblVal;
		XLONGLONG     m_llVal;
		XDATE         m_dateVal;
		XTIME         m_timeVal;
		XTIMESTAMP    m_tsVal;
	};
	XODBCSTRING		  m_stringVal;
	XODBCWSTRING      m_wstringVal;
	XBINARY           m_binaryVal;

	bool m_bNull; //ֵ�Ƿ�Ϊ�գ�
	XDBVariant();
	~XDBVariant();
	string AsString();
	wstring AsWString();
	void Clear();
};

//XODBCVariant

class XODBCVariant
{
public:
	short m_nType;

	union
	{
		XBOOL         *m_pboolVal;
    	XUCHAR        *m_pchVal;
        XSHORT        *m_pshVal;
	    XLONG         *m_plVal;
	    XSINGLE       *m_pfltVal;
	    XDOUBLE       *m_pdblVal;
        XLONGLONG     *m_pllVal;
	    XDATE         *m_pdateVal;
        XTIME         *m_ptimeVal;
	    XTIMESTAMP    *m_ptsVal;
	    XSTRING       *m_pstringVal;
		XWSTRING      *m_pwstringVal;
	    XBINARY       *m_pbinaryVal;
    };
	XODBCVariant();
	~XODBCVariant();
	void SetXDBVariant(XDBVariant &varValue, long lLength = 0);
	bool SetValue(XDBVariant varValue);
	void Clear();
};


struct XTableDesc
{
string m_strServerName;
string m_strCatalogName;
string m_strSchemaName;
string m_strTableName;
};

struct XIndexInfo
{
	string              m_strName;     // Primary
	vector<XFieldInfo>  m_fieldInfos;  // Primary
	bool                m_bPrimary;                    // Secondary
	bool                m_bUnique;                     // Secondary
	bool                m_bClustered;                  // Secondary
	bool                m_bHashed;
	//bool                m_bIgnoreNulls;                // Secondary
	//	BOOL m_bRequired;                   // Secondary
	//	BOOL m_bForeign;                    // Secondary
	//	long m_lDistinctCount;              // All
};

class XODBCRecordset
{
//Constructor
public:
    XODBCRecordset(XODBCDatabase * pDatabase);
	XODBCRecordset(string strDSN, string strUser = "", string strPassword = "", long lOption = XODBCDatabase::openReadOnly);
	XODBCRecordset(string strDSNString = "DSN=ODBC;strUser=;strPassword = ",long lOption = XODBCDatabase::openReadOnly);

public:
	~XODBCRecordset();

	enum OpenType
	{
		dynaset,        // uses SQLExtendedFetch, keyset driven cursor
		snapshot,       // uses SQLExtendedFetch, static cursor
		forwardOnly,    // uses SQLFetch
		dynamic,        // uses SQLExtendedFetch, dynamic cursor
	};

	enum OpenOptions
	{
		none =                      0x0,
		readOnly =                  0x0004,
		appendOnly =                0x0008,

		skipDeletedRecords =        0x0010, // turn on skipping of deleted records, Will slow Move(n).
		noDirtyFieldCheck =         0x0020, // disable automatic dirty field checking
		useBookmarks =              0x0100, // turn on bookmark support
		useMultiRowFetch =          0x0200, // turn on multi-row fetch model
		userAllocMultiRowBuffers =  0x0400, // if multi-row fetch on, user will alloc memory for buffers

		useExtendedFetch =          0x0800, // use SQLExtendedFetch with forwardOnly type recordsets
		executeDirect =             0x2000, // Directly execute SQL rather than prepared execute

		optimizeBulkAdd =           0x4000, // Use prepared HSTMT for multiple AddNews, dirty fields must not change.
		firstBulkAdd =              0x8000, // INTERNAL to MFC, don't specify on Open.
	};

	void  SetMaxRecordCount(long lCount);

	//Overridables 
	virtual bool Open(int nOpenType = snapshot,string strSQL = "", long lOpenOption = none);
	virtual void Close();


//Recordset Status
	
struct XODBCRecordsetStatus
{
	long m_lCurrentRecord;   // -2=Unknown,-1=BOF,0=1st record. . .
	bool m_bRecordCountFinal; // Have we counted all records?
};



//Attribute
public:
	HSTMT  m_hstmt;
	XODBCDatabase * m_pDatabase;
	string strFilter;
	string strSort;

	bool CanAppend() const;     // Can AddNew be called?
    bool CanUpdate() const;     // Can Edit/AddNew/Delete be called?
    bool CanTransact() const;   // Are Transactions supported?

	bool IsDeleted() const;     // Overridables

	bool CanScroll() const;
	bool CanRestart() const;
	bool CanBookmark() const;


	const string GetSQL() const;
    void  GetStatus(XODBCRecordsetStatus & rStatus) const;
	virtual const string GetTableName() const;
	const short  GetFieldCount() const;
	const long   GetEffectCount() const; //ֻ����ִ�з�select���ʱ�ſ�����
    
	bool IsOpen();        // Recordset successfully opened?
	bool IsBOF() const;     // Beginning Of Recordset
	bool IsEOF() const;     // End Of Recordset 
    
	//Calolog
	vector<XTableDesc> GetTableDescList();  // �������ݿ��б�ı��������б�(�������ݿ�����ģʽ���Լ���������������Ĭ��Ϊ��)

	vector<string> GetTableList();   // �������ݿ��б�ı����б�

	vector<string> GetIndexList(string strTableName, vector<string> &strColumnNameList,vector<short> &nIsUniqueList, vector<short> &nIndexTypeList);
	//����ָ�������������ֶ������б���������

	vector<string> GetPrimaryKeyList(string strTableName);           //����ָ�����������ֶ����б�

	vector<string> GetForeignKeyList(string strTableName,vector<string> &strPKTableNameList);
	//����ָ�����������б�����������õ�����������ı����б�
    

//Operation:
public:
//Cursor Operation:
    void MoveNext();
	void MovePrev();
	void MoveFirst();
	void MoveLast();
	void Move(long lRows, short nFetchType = FETCH_ABSOLUTE);
	bool Requery();


	void Cancel();              // Cancels an asynchronous operation or a process from a second thread
	bool FlushResultSet();      // For More Recordsets

	//FieldInfo
    void GetFieldInfo(int nColIndex, XFieldInfo &fieldInfo);
	void GetFieldInfo(string strColName, XFieldInfo &fieldInfo);

	//GetFieldValue
	void GetFieldValue(int nColIndex, XDBVariant &varValue);
	void GetFieldValue(string strColName, XDBVariant &varValue);
	void GetFieldValue(int nColIndex, string &strValue);
	void GetFieldValue(string strColName, string &strValue);
	void GetFieldValue(int nColIndex, wstring &wstrValue);
	void GetFieldValue(string strColName, wstring &wstrValue);

	//SetFieldValue
	void SetFieldValue(int nColIndex, XDBVariant varValue);
	void SetFieldValue(string strColName, XDBVariant varValue);

	// Edit buffer operations;Overridables
	void AddNew();      // add new record at the end
	void Update();      // update it
	void Delete();      // delete the current record
	void CancelUpdate(); // cancel pending Edit/AddNew




//Utility
	short GetXODBCTypeFromSqlType( short nSqlType);

//general error process
	void GetLastError(XErrorType nErrorType, XODBCError &XError); //Get the last Connection or Statement
 
//Attributes
private:
    
    vector<XFieldInfo>     m_fieldList;
	vector<XODBCVariant>   m_varList;
	XODBCError             m_XError[2];
	SQLRETURN              m_nRetcode;
	XODBCRecordsetStatus   m_RecordsetStatus;


public:

	

//Attribute  

protected:
	unsigned int m_nOpenType;
	unsigned int m_nDefaultType;

	long         m_lOptions;
	bool         m_bAppendable;
	bool         m_bUpdatable;
	bool         m_bScrollable;

	enum EditMode
	{
		noMode,
		edit,
		addnew
	};

	enum LockMode
	{
		optimistic,
		pessimistic,
	};

	long         m_lOpen;
	unsigned int m_nEditMode;
	bool         m_bEOFSeen;
	bool         m_bRecordsetDb;
	long         m_lRecordCount;
	short        m_nResultCols;
	long         m_lCurrentRecord;
	long         m_lEffectCount;

	SQLUSMALLINT* m_rgRowStatus;     // row status used by SQLExtendedFetch and SQLSetPos
	SQLUINTEGER  m_lRowsFetched;     // number of rows fetched by SQLExtendedFetch
	SQLUINTEGER  m_lRowsetSize;
	SQLUINTEGER  m_lAllocatedRowsetSize; 		
	bool         m_bLongBinaryColumns;

		
	bool         m_bCheckCacheForDirtyFields;
    bool         m_bDeleted;
	bool         m_bUseUpdateSQL;
	bool         m_bRebindParams;


	bool         m_bBOF;
	bool         m_bEOF;

    string       m_strSQL;       // SQL statement for recordset
	string       m_strCursorName;
	string       m_strTableName;
	SQLHSTMT     m_hstmtUpdate;


	// Perform operation based on m_nEditMode

	unsigned int  m_nLockMode;       // Control concurrency for Edit()
	unsigned long m_lDriverConcurrency;   // driver supported concurrency types
	unsigned long m_lConcurrency; // requested concurrency type


	int            m_nFieldsBound;
	unsigned char* m_pbFieldFlags;
	unsigned char* m_pbParamFlags;
	long         * m_plParamLength;


    string m_strRequerySQL;    // archive SQL string for use in Requery()
	string m_strRequeryFilter; // archive filter string for use in Requery()
	string m_strRequerySort;   // archive sort string for use in Requery()





//Operations
protected:
//Initialization
	void  Initiate();
	void  SetState(int nOpenType, string strSQL, long lOptions);
	void  OnSetOptions(HSTMT hstmt);
	void  AllocHstmt();
	void  BuildSQL(string strSQL);
	void  PrepareAndExecute();

//Reset
	void  ResetAttribute();
	void  ResetCursor();
	void  FreeHstmt();

//Construct SQL Statement
	void  BuildSelectSQL();
	void  AppendFilterAndSortSQL();
	bool  IsRecordsetUpdatable();

//Set Options
	void  VerifyDriverBehavior();
	unsigned long VerifyCursorSupport();
	void EnableBookmarks();
	void SetUpdateMethod();
	void SetConcurrencyAndCursorType(HSTMT hstmt, long lScrollOptions);

	
//FieldExchange

	bool UpdateInsertDelete();
	void FreeDataCache();
	


//FieldInfo
	void   InitFieldInfo();
	short  GetFieldIndexByName(string strColName);
	string GetFieldNameByIndex(short  nIndex);
	short  GetCTypeFromSqlType( short nSqlType);
	long   GetTextLen(short nSQLType, SQLUINTEGER lPrecision);

//FieldValue
	void  FreeFieldValueList();
	void  AllocFieldValueList();
	void *GetFieldBuffer(SQLUSMALLINT nIndex, SQLUINTEGER &lLength);
	void  BindFieldValue();

//Cursor
	void  CheckRowsetCurrencyStatus(short nFetchType, long lRows);
	void  AllocRowset();
	void  SetRowsetSize(long lNewRowsetSize);
	void  FreeRowset();
	RETCODE  FetchData(short nFetchType, long lRow, SQLUINTEGER *plRowsFetched);
	SQLUSMALLINT GetRowStatus( SQLUSMALLINT nRow);
	void  SetRowsetCurrencyStatus(RETCODE nRetcode,SQLUSMALLINT nFetchType, long lRows, SQLUINTEGER lRowsFetched);

//Error 
	bool Check(SQLRETURN nRetCode) const;
	bool SetLastError(XErrorType nErrorType,SQLHSTMT hstmt = SQL_NULL_HSTMT);
	
};

}

#endif 