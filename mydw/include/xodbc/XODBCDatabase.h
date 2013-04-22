#ifndef XODBCDATABASE_H_
#define XODBCDATABASE_H_


#include "XODBCGlobal.h"
#include "XODBCError.h"
#include "XODBCException.h"


namespace xodbc{

class XODBCDatabase
{
// Constructors
public:
	XODBCDatabase();
public:
	~XODBCDatabase();

	enum DbOpenOptions
	{
		openReadOnly    =   0x0001, // Open database read only
	    openCanUpdate   =   0x0002, // Can update the database 
		useCursorLib    =   0x0004, // Use ODBC cursor lib
		noOdbcDialog    =   0x0008, // Don't display ODBC Connect dialog
		forceOdbcDialog =   0x0010, // Always display ODBC connect dialog
	};

	virtual bool Open(string strDSN, string strUser = "", string strPasshort = "", long lOption = openCanUpdate );
	virtual bool OpenEx(string strDSNConnectString = "DSN=ODBC;UID=;PWD=", long lOption = openCanUpdate );
	virtual void Close();
	

// Attributes
public:
	HENV m_henv;
	HDBC  m_hdbc;
	HSTMT m_hstmt;
	
	bool IsOpen() const;        // Database successfully opened?
	bool CanUpdate() const;     // Database can Updated?
	bool CanTransact() const;   // Are Transactions supported?

	const string GetDatabaseName() ; // Get Database Name
	const string GetConnectString() const;      // Get Connection string 
	const string GetDSName(); //Get DSN Name


// Operations
public:
	void SetLoginTimeout(long lSeconds); 
	void SetQueryTimeout(long lSeconds);

	// transaction control 
	bool BeginTrans();    // Begin Transaction
	bool CommitTrans();   // Commit Transaction
	bool Rollback();      // Roll back Transaction

	void ExecuteSQL(string strSQL); //Execute SQL Statement
	long GetEffectCount();          //Get the Effected count of Insert¡¢Delete and Update SQL 
	
	// general error process
	void GetLastError(XErrorType nErrorType, XODBCError &XError); //Get the last Connection or Statement
	virtual void BindParameters(HSTMT);
	
// Attributes
protected:
	XODBCError      m_XError[2];
	SQLRETURN       m_nRetcode;
	string          m_strConnect;

	
	bool            m_bOpen;
	bool            m_bUpdatable;
	bool			m_bTransactions;
	bool            m_bStripTrailingSpaces;
	bool            m_bIncRecordCountOnAdd;
	bool            m_bAddForUpdate;
 
	long            m_lLoginTimeout;
	long            m_lQueryTimeout;

    char            m_szchIDQuoteChar;
	short           m_nCursorCommitBehavior;
	short	        m_nCursorRollbackBehavior;
	
	unsigned long   m_lUpdateOptions;
	unsigned long   m_lBookmarkAttributes;   // cache driver bookmark persistence
	long            m_lRowCount;

	vector<XODBCRecordset *>    m_listRecordsets; //XODBCRecordset List of this XODBCDatabase

//Operations
protected:

//Connect
	void Free();
	void AllocConnect(long lOption);
	bool Connect(string strDSN, string strUser, string strPasshort);
	bool DriverConnect(string strDSNString,long lOption);
	void VerifyConnect();
	void GetConnectInfo();

//Error process
	bool Check(SQLRETURN nRetcode) const;
	bool SetLastError(XErrorType nErrorType, SQLHSTMT hstmt = NULL);
//
	long GetBookmarkPersistence();
	void OnSetOptions(HSTMT hstmt);

//friend class
protected:
	friend class XODBCRecordset;

//Operations
protected:
	;
};

}

#endif 