#include "./PreComputation/PreCmptException.h"

namespace PreCmpt
{
	const char* StateMessage[] = 
	{
		"SUCCESS: PreComputation is complete !",
		"FAILED: Can't connect to dataSource !",
		"FAILED: Operate DataBase failed !",
		"FAILED: Operate data File failed !",
		"FAILED: Can't open system-config.xml file !",
		"FAILED: Can't open local-config.xml file !",
		"FAILED: Can't get attribute value in system-config.xml file !",
		"FAILED: Can't get attribute value in local-config.xml file !",
		"FAILED: Schema name can't find !",
		"FAILED: Cube name can't find !",
		"FAILED: Load Data Ambiguous!"
	};

	EXECUTESTATE PreErrorNo = SUCCEEDED;

}