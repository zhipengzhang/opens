#ifndef __PRECMPTEXCEPTION_H_INCLUDE__
#define __PRECMPTEXCEPTION_H_INCLUDE__

#include "Common.h"

namespace PreCmpt
{
typedef enum _EXECUTESTATE
{
	SUCCEEDED=0,
	CONN_DA_FAILED,
	DB_OPER_FAILED,
	FILE_OPER_FAILED,
	SYSTEM_OPEN_FAILED,
	LOCAL_OPEN_FAILED,
	SYSTEM_GET_FAILED,
	LOCAL_GET_FAILED,
	SCHEMA_CANNOT_FIND,
	CUBE_CANNOT_FIND,
	LOAD_DATA_FAILED
} EXECUTESTATE;

class PreCmptException  
{
public:
	PreCmptException( string error );
	virtual ~PreCmptException();
	
	void SetError( string error );
	string GetError();
private:
	string _error;
};


}


#endif
 