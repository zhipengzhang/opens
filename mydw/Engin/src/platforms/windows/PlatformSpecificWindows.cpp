#ifdef ENABLE_AXISTRACE
/* TRACE ADDED BY THE TRACE INSTRUMENTOR TOOL */
#include "../../common/AxisTrace.h"
#endif
/*
 *   Copyright 2004-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#include "PlatformSpecificWindows.hpp"

#include <stdio.h>

std::string* getPlatformErrorMessage(long errorNumber)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry(NULL, "getPlatformErrorMessage", NULL, 1,
					TRACETYPE_LONG, 0, ((void*)&errorNumber));	  /* AUTOINSERTED TRACE */
	#endif

	std::string* returningString = new std::string();
    LPVOID lpMsgBuf;
	FormatMessage(
	FORMAT_MESSAGE_ALLOCATE_BUFFER | 
	FORMAT_MESSAGE_FROM_SYSTEM,
	NULL,
	errorNumber,
	MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
	(LPTSTR) &lpMsgBuf,
	0, NULL );
	returningString->append((LPTSTR)lpMsgBuf);
    LocalFree(lpMsgBuf);
		    
    	{
		#ifdef ENABLE_AXISTRACE
			std:: string* traceRet = (returningString);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit(NULL, "getPlatformErrorMessage", NULL, 0,
					TRACETYPE_POINTER, sizeof(std:: string), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return returningString;
		#endif
	}

}

HMODULE callLoadLib(LPCTSTR lib)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry(NULL, "callLoadLib", NULL, 1,
					TRACETYPE_DATA, sizeof(LPCTSTR), ((void*)&lib));	  /* AUTOINSERTED TRACE */
	#endif

        SetErrorMode(SEM_FAILCRITICALERRORS); //Disable display of the critical-error-handler message box
        	{
		#ifdef ENABLE_AXISTRACE
			HMODULE traceRet = (LoadLibrary(lib));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit(NULL, "callLoadLib", NULL, 0,
					TRACETYPE_DATA, sizeof(HMODULE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return LoadLibrary(lib);
		#endif
	}

}

