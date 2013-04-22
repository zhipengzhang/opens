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

#include "UnsignedByte.hpp"

UnsignedByte::UnsignedByte()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedByte", "UnsignedByte", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedByte", "UnsignedByte", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

UnsignedByte::UnsignedByte(const xsd__unsignedByte* value)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedByte", "UnsignedByte", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__unsignedByte), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    if (value)
    {
        setNil(false);
        serialize(value);
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedByte", "UnsignedByte", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

UnsignedByte::~UnsignedByte()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedByte", "~UnsignedByte", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedByte", "~UnsignedByte", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

XSDTYPE UnsignedByte::getType()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedByte", "getType", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			XSDTYPE traceRet = (XSD_UNSIGNEDBYTE);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedByte", "getType", this, 0,
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return XSD_UNSIGNEDBYTE;
		#endif
	}

}

xsd__unsignedByte* UnsignedByte::getUnsignedByte()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedByte", "getUnsignedByte", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    if (isNil())
    {
        	{
		#ifdef ENABLE_AXISTRACE
			xsd__unsignedByte* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedByte", "getUnsignedByte", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__unsignedByte), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
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
			xsd__unsignedByte* traceRet = (deserializeUnsignedByte(m_Buf));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedByte", "getUnsignedByte", this, 2,
					TRACETYPE_POINTER, sizeof(xsd__unsignedByte), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return deserializeUnsignedByte(m_Buf);
		#endif
	}

    }
}

void * UnsignedByte::getValue()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedByte", "getValue", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			void* traceRet = ((void*) getUnsignedByte());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedByte", "getValue", this, 0,
					TRACETYPE_POINTER, 1, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (void*) getUnsignedByte();
		#endif
	}

}

AxisChar* UnsignedByte::serialize(const xsd__unsignedByte* value) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedByte", "serialize", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__unsignedByte), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    xsd__unsignedShort valueAsShort = static_cast<xsd__unsignedShort>(*value);
    	{
		#ifdef ENABLE_AXISTRACE
			AxisChar* traceRet = (UnsignedShort::serialize(&valueAsShort));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedByte", "serialize", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return UnsignedShort::serialize(&valueAsShort);
		#endif
	}

}

xsd__unsignedByte* UnsignedByte::deserializeUnsignedByte(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedByte", "deserializeUnsignedByte", this, 1,
					TRACETYPE_STRING, 0, ((void*)&valueAsChar));	  /* AUTOINSERTED TRACE */
	#endif

    xsd__unsignedShort* returnValue = UnsignedShort::deserializeUnsignedShort(valueAsChar);
 
    xsd__unsignedByte * value = new xsd__unsignedByte;
    *value = static_cast<xsd__unsignedByte> (*returnValue);
    delete returnValue;
    	{
		#ifdef ENABLE_AXISTRACE
			xsd__unsignedByte* traceRet = (value);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedByte", "deserializeUnsignedByte", this, 0,
					TRACETYPE_POINTER, sizeof(xsd__unsignedByte), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return value;
		#endif
	}

}

MaxInclusive* UnsignedByte::getMaxInclusive()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedByte", "getMaxInclusive", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    LONGLONG maxInclusive = LONGLONGVALUE(255);
    
    	{
		#ifdef ENABLE_AXISTRACE
			MaxInclusive* traceRet = (new MaxInclusive(maxInclusive));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedByte", "getMaxInclusive", this, 0,
					TRACETYPE_POINTER, sizeof(MaxInclusive), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MaxInclusive(maxInclusive);
		#endif
	}

}

