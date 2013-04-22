#ifndef XODBCGLOBAL_H_
#define XODBCGLOBAL_H_

#pragma   warning(disable:4786)

#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include <odbcinst.h>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;



/////////////////////////////////////////////////////////////////////////////
// Global data


const char  _gParamCall[] = "{?";
const char  _gSelect[]    = "SELECT ";
const char  _gFrom[]      = " FROM ";
const char  _gWhere[]     = " WHERE ";
const char  _gOrderBy[]   = " ORDER BY ";
const char  _gForUpdate[] = " FOR UPDATE ";

const char _gRowFetch[]      = "State:01S01";
const char _gDataTruncated[] = "State:01004";
const char _gInfoRange[]     = "State:S1096";
const char _gOutOfSequence[] = "State:S1010";
const char _gDriverNotCapable[] = "State:S1C00";
const char _gFunctionSequenceError[] = "S1010";



/////////////////////////////////////////////////////////////////////////////
// ODBC API AND ODBC SETUP API LIB

#pragma comment(lib, "odbc32.lib")
#pragma comment(lib, "odbccp32.lib")

namespace xodbc{
////////////////////////////////////////////////////////////////////////////
// XODBC CLASS LIST

class XODBCDatabase;

class XODBCRecordset;

class XODBCError;

class XODBCException;

class XFieldInfo;

class XParamInfo;

class XWSTRING;

class XSTRING;

class XDBVariant;

class XODBCVariant;

class XODBCDataSource;

// Max display length in chars of timestamp (date & time) value
#define TIMESTAMP_PRECISION 23
#ifndef INT_MAX      
#define INT_MAX       2147483647
#endif


//  Miscellaneous sizing info
#define MAX_CURRENCY     30     // Max size of Currency($) string
#define MAX_TNAME_LEN    256     // Max size of table names
#define MAX_FNAME_LEN    256    // Max size of field names
#define MAX_DBNAME_LEN   256     // Max size of a database name
#define MAX_DNAME_LEN    256        // Max size of Recordset names
#define MAX_CONNECT_LEN  512        // Max size of Connect string
#define MAX_CURSOR_NAME  64    // Max size of a cursor name
#define DEFAULT_FIELD_TYPE SQL_TYPE_NULL // pick "C" data type to match SQL data type

// Timeout and net wait defaults
#define DEFAULT_LOGIN_TIMEOUT 15    // seconds to before fail on connect
#define DEFAULT_QUERY_TIMEOUT 15    // seconds to before fail waiting for results

#define RECORDSET_STATUS_OPEN    (+1L)
#define RECORDSET_STATUS_CLOSED  0L
#define RECORDSET_STATUS_UNKNOWN (-1L)

#define DB_USE_DEFAULT_TYPE      0xffffffff
#define SQL_SETPOSUPDATES        0x0001
#define SQL_POSITIONEDSQL        0x0002
#define SQL_GDBOUND              0x0004



#define CURRENT_RECORD_UNDEFINED (-1)
#define CURRENT_RECORD_BOF       (0)

#define FETCH_RELATIVE       SQL_FETCH_RELATIVE
#define FETCH_ABSOLUTE       SQL_FETCH_ABSOLUTE
#define INDEX_CLUSTERED      SQL_INDEX_CLUSTERED 
#define INDEX_HASHED         SQL_INDEX_HASHED
#define INDEX_OTHER			 SQL_INDEX_OTHER


#define XSHOW_TRACE_ERROR(ErrorText) cout<<"Program error at \nFile: "<<__FILE__\
	                                     <<"\nLine: "<<__LINE__\
										 <<"\nError: "<<ErrorText<<endl

#define XODBC_TRY	        try
#define XODBC_CATCH			catch(...)	
							         
/************************************************************************/
/* ����Դ���ͣ���Ӧ�ں��������е�n_DSNType��                            */
/* USER_DSN��ʾ�û�����Դ��SYSTEM_DSN��ʾϵͳ����Դ��BOTH_DSN��ʾ������ */
/* ��Դ�����֮������Ѱ��˳�����Ȳ����û�����Դ��Ȼ���ٲ���ϵͳ����Դ�� */
/************************************************************************/  

#define BOTH_DSN         ODBC_BOTH_DSN
#define USER_DSN         ODBC_USER_DSN		
#define SYSTEM_DSN	     ODBC_SYSTEM_DSN	

/************************************************************************/
/*                          ���ݿ�����                                  */
/************************************************************************/
enum XDBTYPE
{
	DB_ERROR   = 0,
	DB_MYSQL,
	DB_SQLSERVER,
	DB_DB2,
	DB_ORACLE,
	DB_SYBASE,
	DB_ACCESS,
	DB_UNKNOWN
};

/*   �ֶ��Ƿ��Ϊ��   */
#define NO_NULLS            SQL_NO_NULLS           //����Ϊ��
#define NULLABLE            SQL_NULLABLE           //��Ϊ��
#define NULLABLE_UNKNOWN    SQL_NULLABLE_UNKNOWN   //δ֪,һ��Ĭ��Ϊ��Ϊ��

/*   �ֶ��Ƿ�Ϊ����  */
#define NO_PRIMARYKEY       0   //������
#define PRIMARYKEY          1   //��������
#define PRIMARYKEY_UNKNOWN  2   //δ֪��һ��Ĭ��Ϊ������

/*   �ֶ��Ƿ�Ϊ���  */
#define NO_FOREIGNKEY       0   //�����
#define FOREIGNKEY          1   //�����
#define FOREIGNKEY_UNKNOWN  2   //δ֪��һ��Ĭ��Ϊ�����
 
/*   ��������  */
#define INDEX_UNIQUE     SQL_INDEX_UNIQUE       //UNIQUE
#define INDEX_CLUSTERED  SQL_INDEX_CLUSTERED    //�۴�����
#define INDEX_HASHED     SQL_INDEX_HASHED       //��ϣ����
#define INDEX_OTHER      SQL_INDEX_OTHER        //��������
//#define INDEX_BTREE      4                     //BTREE����


}







#endif