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

#include "UnsignedInt.hpp"

UnsignedInt::UnsignedInt()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedInt", "UnsignedInt", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedInt", "UnsignedInt", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

UnsignedInt::UnsignedInt(const xsd__unsignedInt* value)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedInt", "UnsignedInt", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__unsignedInt), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    if (value)
    {
        setNil(false);
        serialize(value);
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedInt", "UnsignedInt", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

UnsignedInt::~UnsignedInt()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedInt", "~UnsignedInt", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedInt", "~UnsignedInt", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

XSDTYPE UnsignedInt::getType()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedInt", "getType", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			XSDTYPE traceRet = (XSD_UNSIGNEDINT);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedInt", "getType", this, 0,
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return XSD_UNSIGNEDINT;
		#endif
	}

}

xsd__unsignedInt* UnsignedInt::getUnsignedInt()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedInt", "getUnsignedInt", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    if (isNil())
    {
        	{
		#ifdef ENABLE_AXISTRACE
			xsd__unsignedInt* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedInt", "getUnsignedInt", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__unsignedInt), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
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
			xsd__unsignedInt* traceRet = (deserializeUnsignedInt(m_Buf));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedInt", "getUnsignedInt", this, 2,
					TRACETYPE_POINTER, sizeof(xsd__unsignedInt), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return deserializeUnsignedInt(m_Buf);
		#endif
	}

    }
}

void * UnsignedInt::getValue()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedInt", "getValue", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			void* traceRet = ((void*) getUnsignedInt());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedInt", "getValue", this, 0,
					TRACETYPE_POINTER, 1, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (void*) getUnsignedInt();
		#endif
	}

}

AxisChar* UnsignedInt::serialize(const xsd__unsignedInt* value) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedInt", "serialize", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__unsignedInt), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    xsd__unsignedLong valueAsLong = static_cast<xsd__unsignedLong>(*value);
    	{
		#ifdef ENABLE_AXISTRACE
			AxisChar* traceRet = (UnsignedLong::serialize(&valueAsLong));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedInt", "serialize", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return UnsignedLong::serialize(&valueAsLong);
		#endif
	}

}

xsd__unsignedInt* UnsignedInt::deserializeUnsignedInt(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedInt", "deserializeUnsignedInt", this, 1,
					TRACETYPE_STRING, 0, ((void*)&valueAsChar));	  /* AUTOINSERTED TRACE */
	#endif

    xsd__unsignedLong* returnValue = UnsignedLong::deserializeUnsignedLong(valueAsChar);
 
    xsd__unsignedInt * value = new xsd__unsignedInt;
    *value = static_cast<xsd__unsignedInt> (*returnValue);
    delete returnValue;
    	{
		#ifdef ENABLE_AXISTRACE
			xsd__unsignedInt* traceRet = (value);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedInt", "deserializeUnsignedInt", this, 0,
					TRACETYPE_POINTER, sizeof(xsd__unsignedInt), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return value;
		#endif
	}

}

MaxInclusive* UnsignedInt::getMaxInclusive()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedInt", "getMaxInclusive", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    LONGLONG maxInclusive = LONGLONGVALUE(4294967295);
    
    	{
		#ifdef ENABLE_AXISTRACE
			MaxInclusive* traceRet = (new MaxInclusive(maxInclusive));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedInt", "getMaxInclusive", this, 0,
					TRACETYPE_POINTER, sizeof(MaxInclusive), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MaxInclusive(maxInclusive);
		#endif
	}

}

