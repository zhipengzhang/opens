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
/* 数据源类型，对应于后续函数中的n_DSNType。                            */
/* USER_DSN表示用户数据源，SYSTEM_DSN表示系统数据源，BOTH_DSN表示两种数 */
/* 据源兼而有之，在搜寻的顺序是先查找用户数据源，然后再查找系统数据源。 */
/************************************************************************/  

#define BOTH_DSN         ODBC_BOTH_DSN
#define USER_DSN         ODBC_USER_DSN		
#define SYSTEM_DSN	     ODBC_SYSTEM_DSN	

/************************************************************************/
/*                          数据库类型                                  */
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

/*   字段是否可为空   */
#define NO_NULLS            SQL_NO_NULLS           //不能为空
#define NULLABLE            SQL_NULLABLE           //可为空
#define NULLABLE_UNKNOWN    SQL_NULLABLE_UNKNOWN   //未知,一般默认为可为空

/*   字段是否为主键  */
#define NO_PRIMARYKEY       0   //是主键
#define PRIMARYKEY          1   //不是主键
#define PRIMARYKEY_UNKNOWN  2   //未知，一般默认为非主键

/*   字段是否为外键  */
#define NO_FOREIGNKEY       0   //是外键
#define FOREIGNKEY          1   //非外键
#define FOREIGNKEY_UNKNOWN  2   //未知，一般默认为非外键
 
/*   索引类型  */
#define INDEX_UNIQUE     SQL_INDEX_UNIQUE       //UNIQUE
#define INDEX_CLUSTERED  SQL_INDEX_CLUSTERED    //聚簇索引
#define INDEX_HASHED     SQL_INDEX_HASHED       //哈希索引
#define INDEX_OTHER      SQL_INDEX_OTHER        //其他索引
//#define INDEX_BTREE      4                     //BTREE索引


}







#endif