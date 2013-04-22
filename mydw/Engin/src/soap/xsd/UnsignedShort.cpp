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

#include "UnsignedShort.hpp"

UnsignedShort::UnsignedShort()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedShort", "UnsignedShort", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedShort", "UnsignedShort", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

UnsignedShort::UnsignedShort(const xsd__unsignedShort* value)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedShort", "UnsignedShort", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__unsignedShort), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    if (value)
    {
        setNil(false);
        serialize(value);
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedShort", "UnsignedShort", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

UnsignedShort::~UnsignedShort()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedShort", "~UnsignedShort", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedShort", "~UnsignedShort", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

XSDTYPE UnsignedShort::getType()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedShort", "getType", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			XSDTYPE traceRet = (XSD_UNSIGNEDSHORT);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedShort", "getType", this, 0,
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return XSD_UNSIGNEDSHORT;
		#endif
	}

}

xsd__unsignedShort* UnsignedShort::getUnsignedShort()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedShort", "getUnsignedShort", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    if (isNil())
    {
        	{
		#ifdef ENABLE_AXISTRACE
			xsd__unsignedShort* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedShort", "getUnsignedShort", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__unsignedShort), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
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
			xsd__unsignedShort* traceRet = (deserializeUnsignedShort(m_Buf));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedShort", "getUnsignedShort", this, 2,
					TRACETYPE_POINTER, sizeof(xsd__unsignedShort), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return deserializeUnsignedShort(m_Buf);
		#endif
	}

    }
}

void * UnsignedShort::getValue()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedShort", "getValue", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			void* traceRet = ((void*) getUnsignedShort());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedShort", "getValue", this, 0,
					TRACETYPE_POINTER, 1, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (void*) getUnsignedShort();
		#endif
	}

}

AxisChar* UnsignedShort::serialize(const xsd__unsignedShort * value) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedShort", "serialize", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__unsignedShort), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    xsd__unsignedInt valueAsInt = static_cast<xsd__unsignedInt>(*value);
    	{
		#ifdef ENABLE_AXISTRACE
			AxisChar* traceRet = (UnsignedInt::serialize(&valueAsInt));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedShort", "serialize", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return UnsignedInt::serialize(&valueAsInt);
		#endif
	}

}

xsd__unsignedShort* UnsignedShort::deserializeUnsignedShort(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedShort", "deserializeUnsignedShort", this, 1,
					TRACETYPE_STRING, 0, ((void*)&valueAsChar));	  /* AUTOINSERTED TRACE */
	#endif

    xsd__unsignedInt* returnValue = UnsignedInt::deserializeUnsignedInt(valueAsChar);
 
    xsd__unsignedShort * value = new xsd__unsignedShort;
    *value = static_cast<xsd__unsignedShort> (*returnValue);
    delete returnValue;
    	{
		#ifdef ENABLE_AXISTRACE
			xsd__unsignedShort* traceRet = (value);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedShort", "deserializeUnsignedShort", this, 0,
					TRACETYPE_POINTER, sizeof(xsd__unsignedShort), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return value;
		#endif
	}

}

MaxInclusive* UnsignedShort::getMaxInclusive()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedShort", "getMaxInclusive", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    LONGLONG maxInclusive = LONGLONGVALUE(65535);
    
    	{
		#ifdef ENABLE_AXISTRACE
			MaxInclusive* traceRet = (new MaxInclusive(maxInclusive));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedShort", "getMaxInclusive", this, 0,
					TRACETYPE_POINTER, sizeof(MaxInclusive), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MaxInclusive(maxInclusive);
		#endif
	}

}

