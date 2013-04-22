#ifdef ENABLE_AXISTRACE
/* TRACE ADDED BY THE TRACE INSTRUMENTOR TOOL */
#include "../../common/AxisTrace.h"
#endif
// Copyright 2003-2004 The Apache Software Foundation.

// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved

// 

// Licensed under the Apache License, Version 2.0 (the "License");

// you may not use this file except in compliance with the License.

// You may obtain a copy of the License at

// 

//        http://www.apache.org/licenses/LICENSE-2.0

// 

// Unless required by applicable law or agreed to in writing, software

// distributed under the License is distributed on an "AS IS" BASIS,

// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

// See the License for the specific language governing permissions and

// limitations under the License.

#include "NCName.hpp"

NCName::NCName()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NCName", "NCName", this, 0);	  /* AUTOINSERTED TRACE */
	#endif
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NCName", "NCName", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

NCName::NCName(const xsd__NCName value)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NCName", "NCName", this, 1,
					TRACETYPE_DATA, sizeof(xsd__NCName), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    if (value)
    {
        setNil(false);
        serialize(value);
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NCName", "NCName", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

XSDTYPE NCName::getType()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NCName", "getType", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			XSDTYPE traceRet = (XSD_NCNAME);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NCName", "getType", this, 0,
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return XSD_NCNAME;
		#endif
	}

}

xsd__NCName NCName::getNCName()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NCName", "getNCName", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    if (isNil())
    {
        	{
		#ifdef ENABLE_AXISTRACE
			xsd__NCName traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NCName", "getNCName", this, 1,
					TRACETYPE_DATA, sizeof(xsd__NCName), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

    }
    else
    {
        	{
		#ifdef ENABLE_AXISTRACE
			xsd__NCName traceRet = (deserializeNCName(m_Buf));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NCName", "getNCName", this, 2,
					TRACETYPE_DATA, sizeof(xsd__NCName), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return deserializeNCName(m_Buf);
		#endif
	}

    }
}

void * NCName::getValue()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NCName", "getValue", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			void* traceRet = ((void*) getNCName());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NCName", "getValue", this, 0,
					TRACETYPE_POINTER, 1, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (void*) getNCName();
		#endif
	}

}

xsd__NCName NCName::deserializeNCName(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NCName", "deserializeNCName", this, 1,
					TRACETYPE_STRING, 0, ((void*)&valueAsChar));	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			xsd__NCName traceRet = ((xsd__NCName) deserializeName(valueAsChar));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NCName", "deserializeNCName", this, 0,
					TRACETYPE_DATA, sizeof(xsd__NCName), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (xsd__NCName) deserializeName(valueAsChar);
		#endif
	}

}

