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

#include "NonPositiveInteger.hpp"

NonPositiveInteger::NonPositiveInteger()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NonPositiveInteger", "NonPositiveInteger", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NonPositiveInteger", "NonPositiveInteger", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

NonPositiveInteger::NonPositiveInteger(const xsd__nonPositiveInteger* value) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NonPositiveInteger", "NonPositiveInteger", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__nonPositiveInteger), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    if (value)
    {
        setNil(false);
        serialize(value);
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NonPositiveInteger", "NonPositiveInteger", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

NonPositiveInteger::~NonPositiveInteger()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NonPositiveInteger", "~NonPositiveInteger", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NonPositiveInteger", "~NonPositiveInteger", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

XSDTYPE NonPositiveInteger::getType()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NonPositiveInteger", "getType", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			XSDTYPE traceRet = (XSD_NONPOSITIVEINTEGER);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NonPositiveInteger", "getType", this, 0,
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return XSD_NONPOSITIVEINTEGER;
		#endif
	}

}

xsd__nonPositiveInteger* NonPositiveInteger::getNonPositiveInteger()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NonPositiveInteger", "getNonPositiveInteger", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    if (isNil())
    {
        	{
		#ifdef ENABLE_AXISTRACE
			xsd__nonPositiveInteger* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NonPositiveInteger", "getNonPositiveInteger", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__nonPositiveInteger), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
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
			xsd__nonPositiveInteger* traceRet = (deserializeNonPositiveInteger(m_Buf));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NonPositiveInteger", "getNonPositiveInteger", this, 2,
					TRACETYPE_POINTER, sizeof(xsd__nonPositiveInteger), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return deserializeNonPositiveInteger(m_Buf);
		#endif
	}

    }
}

void * NonPositiveInteger::getValue()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NonPositiveInteger", "getValue", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			void* traceRet = ((void*) getNonPositiveInteger());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NonPositiveInteger", "getValue", this, 0,
					TRACETYPE_POINTER, 1, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (void*) getNonPositiveInteger();
		#endif
	}

}

xsd__nonPositiveInteger* NonPositiveInteger::deserializeNonPositiveInteger(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NonPositiveInteger", "deserializeNonPositiveInteger", this, 1,
					TRACETYPE_STRING, 0, ((void*)&valueAsChar));	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			xsd__nonPositiveInteger* traceRet = ((xsd__negativeInteger*) deserializeInteger(valueAsChar));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NonPositiveInteger", "deserializeNonPositiveInteger", this, 0,
					TRACETYPE_POINTER, sizeof(xsd__nonPositiveInteger), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (xsd__negativeInteger*) deserializeInteger(valueAsChar);
		#endif
	}

}

MaxInclusive* NonPositiveInteger::getMaxInclusive()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NonPositiveInteger", "getMaxInclusive", this, 0);	  /* AUTOINSERTED TRACE */
	#endif
   
    	{
		#ifdef ENABLE_AXISTRACE
			MaxInclusive* traceRet = (new MaxInclusive((LONGLONG) 0));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NonPositiveInteger", "getMaxInclusive", this, 0,
					TRACETYPE_POINTER, sizeof(MaxInclusive), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MaxInclusive((LONGLONG) 0);
		#endif
	}

}

