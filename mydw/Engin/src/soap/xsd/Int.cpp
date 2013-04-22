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

#include "Int.hpp"


Int::Int()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Int", "Int", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Int", "Int", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

Int::~Int()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Int", "~Int", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Int", "~Int", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

Int::Int(const xsd__int* value)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Int", "Int", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__int), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    if (value)
    {
        setNil(false);
        serialize(value);
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Int", "Int", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

XSDTYPE Int::getType()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Int", "getType", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			XSDTYPE traceRet = (XSD_INT);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Int", "getType", this, 0,
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return XSD_INT;
		#endif
	}

}

xsd__int* Int::getInt()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Int", "getInt", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    if (isNil())
    {
        	{
		#ifdef ENABLE_AXISTRACE
			xsd__int* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Int", "getInt", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__int), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
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
			xsd__int* traceRet = (deserializeInt(m_Buf));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Int", "getInt", this, 2,
					TRACETYPE_POINTER, sizeof(xsd__int), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return deserializeInt(m_Buf);
		#endif
	}

    }
}

void * Int::getValue()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Int", "getValue", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			void* traceRet = ((void*) getInt());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Int", "getValue", this, 0,
					TRACETYPE_POINTER, 1, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (void*) getInt();
		#endif
	}

}

AxisChar* Int::serialize(const xsd__int* value) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Int", "serialize", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__int), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    xsd__long valueAsLong = static_cast<xsd__long>(*value);
    	{
		#ifdef ENABLE_AXISTRACE
			AxisChar* traceRet = (Long::serialize(&valueAsLong));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Int", "serialize", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return Long::serialize(&valueAsLong);
		#endif
	}

}

xsd__int* Int::deserializeInt(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Int", "deserializeInt", this, 1,
					TRACETYPE_STRING, 0, ((void*)&valueAsChar));	  /* AUTOINSERTED TRACE */
	#endif

    xsd__long* returnValue = Long::deserializeLong(valueAsChar);
 
    xsd__int * value = new xsd__int;
    *value = static_cast<xsd__int> (*returnValue);
 // cb 07/07/05 : delete here is inconsistent with other data types
 // (which don't do it here), but maybe a good idea   
 // Samisa: we got to delete returnValue here, else there will be a memory leak :-(
    delete returnValue; // Samisa - need to clean this memory
    	{
		#ifdef ENABLE_AXISTRACE
			xsd__int* traceRet = (value);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Int", "deserializeInt", this, 0,
					TRACETYPE_POINTER, sizeof(xsd__int), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return value;
		#endif
	}

}

MinInclusive* Int::getMinInclusive()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Int", "getMinInclusive", this, 0);	  /* AUTOINSERTED TRACE */
	#endif
   
    LONGLONG minInclusive = -LONGLONGVALUE(2147483648);
    
    	{
		#ifdef ENABLE_AXISTRACE
			MinInclusive* traceRet = (new MinInclusive(minInclusive));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Int", "getMinInclusive", this, 0,
					TRACETYPE_POINTER, sizeof(MinInclusive), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MinInclusive(minInclusive);
		#endif
	}

}

MinExclusive* Int::getMinExclusive()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Int", "getMinExclusive", this, 0);	  /* AUTOINSERTED TRACE */
	#endif
   
    LONGLONG minExclusive = -LONGLONGVALUE(2147483649);
    	{
		#ifdef ENABLE_AXISTRACE
			MinExclusive* traceRet = (new MinExclusive(minExclusive));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Int", "getMinExclusive", this, 0,
					TRACETYPE_POINTER, sizeof(MinExclusive), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MinExclusive(minExclusive);
		#endif
	}

}

MaxInclusive* Int::getMaxInclusive()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Int", "getMaxInclusive", this, 0);	  /* AUTOINSERTED TRACE */
	#endif
   
    LONGLONG maxInclusive = LONGLONGVALUE(2147483647);
    
    	{
		#ifdef ENABLE_AXISTRACE
			MaxInclusive* traceRet = (new MaxInclusive(maxInclusive));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Int", "getMaxInclusive", this, 0,
					TRACETYPE_POINTER, sizeof(MaxInclusive), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MaxInclusive(maxInclusive);
		#endif
	}

}

MaxExclusive* Int::getMaxExclusive()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Int", "getMaxExclusive", this, 0);	  /* AUTOINSERTED TRACE */
	#endif
   
    LONGLONG maxExclusive = LONGLONGVALUE(2147483648);
    
    	{
		#ifdef ENABLE_AXISTRACE
			MaxExclusive* traceRet = (new MaxExclusive(maxExclusive));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Int", "getMaxExclusive", this, 0,
					TRACETYPE_POINTER, sizeof(MaxExclusive), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MaxExclusive(maxExclusive);
		#endif
	}

}


