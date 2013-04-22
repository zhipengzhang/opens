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

#include "UnsignedLong.hpp"

UnsignedLong::UnsignedLong()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedLong", "UnsignedLong", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedLong", "UnsignedLong", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

UnsignedLong::UnsignedLong(const xsd__unsignedLong* value)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedLong", "UnsignedLong", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__unsignedLong), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    if (value)
    {
        setNil(false);
        serialize(value);
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedLong", "UnsignedLong", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

UnsignedLong::~UnsignedLong()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedLong", "~UnsignedLong", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedLong", "~UnsignedLong", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

XSDTYPE UnsignedLong::getType()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedLong", "getType", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			XSDTYPE traceRet = (XSD_UNSIGNEDLONG);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedLong", "getType", this, 0,
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return XSD_UNSIGNEDLONG;
		#endif
	}

}

xsd__unsignedLong* UnsignedLong::getUnsignedLong()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedLong", "getUnsignedLong", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    if (isNil())
    {
        	{
		#ifdef ENABLE_AXISTRACE
			xsd__unsignedLong* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedLong", "getUnsignedLong", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__unsignedLong), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
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
			xsd__unsignedLong* traceRet = (deserializeUnsignedLong(m_Buf));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedLong", "getUnsignedLong", this, 2,
					TRACETYPE_POINTER, sizeof(xsd__unsignedLong), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return deserializeUnsignedLong(m_Buf);
		#endif
	}

    }
}

void * UnsignedLong::getValue()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedLong", "getValue", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			void* traceRet = ((void*) getUnsignedLong());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedLong", "getValue", this, 0,
					TRACETYPE_POINTER, 1, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (void*) getUnsignedLong();
		#endif
	}

}

AxisChar* UnsignedLong::serialize(const xsd__unsignedLong* value) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedLong", "serialize", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__unsignedLong), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    xsd__nonNegativeInteger valueAsLong = static_cast<xsd__nonNegativeInteger>(*value);
    	{
		#ifdef ENABLE_AXISTRACE
			AxisChar* traceRet = (NonNegativeInteger::serialize(&valueAsLong));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedLong", "serialize", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NonNegativeInteger::serialize(&valueAsLong);
		#endif
	}

}

xsd__unsignedLong* UnsignedLong::deserializeUnsignedLong(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedLong", "deserializeUnsignedLong", this, 1,
					TRACETYPE_STRING, 0, ((void*)&valueAsChar));	  /* AUTOINSERTED TRACE */
	#endif

    xsd__nonNegativeInteger* returnValue = NonNegativeInteger::deserializeNonNegativeInteger(valueAsChar);
 
    xsd__unsignedLong * value = new xsd__unsignedLong;
    *value = static_cast<xsd__unsignedLong> (*returnValue);
    delete returnValue;
    	{
		#ifdef ENABLE_AXISTRACE
			xsd__unsignedLong* traceRet = (value);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedLong", "deserializeUnsignedLong", this, 0,
					TRACETYPE_POINTER, sizeof(xsd__unsignedLong), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return value;
		#endif
	}

}

MaxInclusive* UnsignedLong::getMaxInclusive()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("UnsignedLong", "getMaxInclusive", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

 /*
  * The actual value for this is 18446744073709551615, but as this is also the
  * physical limit of an unsigned 64bit integer, we don't actually need to check
  * this.
  */
    	{
		#ifdef ENABLE_AXISTRACE
			MaxInclusive* traceRet = (new MaxInclusive(UNSIGNED_LONGLONGVALUE(18446744073709551615)));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("UnsignedLong", "getMaxInclusive", this, 0,
					TRACETYPE_POINTER, sizeof(MaxInclusive), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MaxInclusive(UNSIGNED_LONGLONGVALUE(18446744073709551615));
		#endif
	}

}


