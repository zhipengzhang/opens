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

#include "Short.hpp"

Short::Short()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Short", "Short", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Short", "Short", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

Short::~Short()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Short", "~Short", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Short", "~Short", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

Short::Short(const xsd__short* value)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Short", "Short", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__short), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    if (value)
    {
        setNil(false);
        serialize(value);
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Short", "Short", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

XSDTYPE Short::getType()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Short", "getType", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			XSDTYPE traceRet = (XSD_SHORT);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Short", "getType", this, 0,
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return XSD_SHORT;
		#endif
	}

}

xsd__short* Short::getShort()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Short", "getShort", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    if (isNil())
    {
        	{
		#ifdef ENABLE_AXISTRACE
			xsd__short* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Short", "getShort", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__short), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
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
			xsd__short* traceRet = (deserializeShort(m_Buf));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Short", "getShort", this, 2,
					TRACETYPE_POINTER, sizeof(xsd__short), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return deserializeShort(m_Buf);
		#endif
	}

    }
}

void * Short::getValue()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Short", "getValue", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			void* traceRet = ((void*) getShort());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Short", "getValue", this, 0,
					TRACETYPE_POINTER, 1, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (void*) getShort();
		#endif
	}

}

AxisChar* Short::serialize(const xsd__short* value) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Short", "serialize", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__short), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    xsd__int valueAsInt = static_cast<xsd__int>(*value);
    	{
		#ifdef ENABLE_AXISTRACE
			AxisChar* traceRet = (Int::serialize(&valueAsInt));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Short", "serialize", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return Int::serialize(&valueAsInt);
		#endif
	}

}

xsd__short* Short::deserializeShort(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Short", "deserializeShort", this, 1,
					TRACETYPE_STRING, 0, ((void*)&valueAsChar));	  /* AUTOINSERTED TRACE */
	#endif

    xsd__int* returnValue = Int::deserializeInt(valueAsChar);
 
    xsd__short * value = new xsd__short;
    *value = static_cast<xsd__short> (*returnValue);
    delete returnValue; // Samissa - need to clean this memory
    	{
		#ifdef ENABLE_AXISTRACE
			xsd__short* traceRet = (value);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Short", "deserializeShort", this, 0,
					TRACETYPE_POINTER, sizeof(xsd__short), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return value;
		#endif
	}

}

MinInclusive* Short::getMinInclusive()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Short", "getMinInclusive", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			MinInclusive* traceRet = (new MinInclusive(static_cast<LONGLONG>(-32768)));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Short", "getMinInclusive", this, 0,
					TRACETYPE_POINTER, sizeof(MinInclusive), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MinInclusive(static_cast<LONGLONG>(-32768));
		#endif
	}

}

MinExclusive* Short::getMinExclusive()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Short", "getMinExclusive", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			MinExclusive* traceRet = (new MinExclusive(static_cast<LONGLONG>(-32769)));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Short", "getMinExclusive", this, 0,
					TRACETYPE_POINTER, sizeof(MinExclusive), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MinExclusive(static_cast<LONGLONG>(-32769));
		#endif
	}

}

MaxInclusive* Short::getMaxInclusive()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Short", "getMaxInclusive", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			MaxInclusive* traceRet = (new MaxInclusive(static_cast<LONGLONG>(32767)));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Short", "getMaxInclusive", this, 0,
					TRACETYPE_POINTER, sizeof(MaxInclusive), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MaxInclusive(static_cast<LONGLONG>(32767));
		#endif
	}

}

MaxExclusive* Short::getMaxExclusive()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Short", "getMaxExclusive", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			MaxExclusive* traceRet = (new MaxExclusive(static_cast<LONGLONG>(32768)));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Short", "getMaxExclusive", this, 0,
					TRACETYPE_POINTER, sizeof(MaxExclusive), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MaxExclusive(static_cast<LONGLONG>(32768));
		#endif
	}

}

