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

#include "PositiveInteger.hpp"

PositiveInteger::PositiveInteger()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("PositiveInteger", "PositiveInteger", this, 0);	  /* AUTOINSERTED TRACE */
	#endif
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("PositiveInteger", "PositiveInteger", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

PositiveInteger::PositiveInteger(const xsd__positiveInteger* value) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("PositiveInteger", "PositiveInteger", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__positiveInteger), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    if (value)
    {
        setNil(false);
        serialize(value);
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("PositiveInteger", "PositiveInteger", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

XSDTYPE PositiveInteger::getType()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("PositiveInteger", "getType", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			XSDTYPE traceRet = (XSD_POSITIVEINTEGER);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("PositiveInteger", "getType", this, 0,
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return XSD_POSITIVEINTEGER;
		#endif
	}

}

xsd__positiveInteger* PositiveInteger::getPositiveInteger()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("PositiveInteger", "getPositiveInteger", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    if (isNil())
    {
        	{
		#ifdef ENABLE_AXISTRACE
			xsd__positiveInteger* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("PositiveInteger", "getPositiveInteger", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__positiveInteger), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
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
			xsd__positiveInteger* traceRet = (deserializePositiveInteger(m_Buf));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("PositiveInteger", "getPositiveInteger", this, 2,
					TRACETYPE_POINTER, sizeof(xsd__positiveInteger), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return deserializePositiveInteger(m_Buf);
		#endif
	}

    }
}

void * PositiveInteger::getValue()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("PositiveInteger", "getValue", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			void* traceRet = ((void*) getPositiveInteger());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("PositiveInteger", "getValue", this, 0,
					TRACETYPE_POINTER, 1, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (void*) getPositiveInteger();
		#endif
	}

}

xsd__positiveInteger* PositiveInteger::deserializePositiveInteger(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("PositiveInteger", "deserializePositiveInteger", this, 1,
					TRACETYPE_STRING, 0, ((void*)&valueAsChar));	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			xsd__positiveInteger* traceRet = ((xsd__positiveInteger*) deserializeNonNegativeInteger(valueAsChar));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("PositiveInteger", "deserializePositiveInteger", this, 0,
					TRACETYPE_POINTER, sizeof(xsd__positiveInteger), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (xsd__positiveInteger*) deserializeNonNegativeInteger(valueAsChar);
		#endif
	}

}

MinInclusive* PositiveInteger::getMinInclusive()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("PositiveInteger", "getMinInclusive", this, 0);	  /* AUTOINSERTED TRACE */
	#endif
   
    	{
		#ifdef ENABLE_AXISTRACE
			MinInclusive* traceRet = (new MinInclusive((unsigned LONGLONG) 1));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("PositiveInteger", "getMinInclusive", this, 0,
					TRACETYPE_POINTER, sizeof(MinInclusive), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MinInclusive((unsigned LONGLONG) 1);
		#endif
	}

}

