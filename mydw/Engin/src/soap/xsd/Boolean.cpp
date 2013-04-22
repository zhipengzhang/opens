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

#include "Boolean.hpp"

Boolean::Boolean()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Boolean", "Boolean", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Boolean", "Boolean", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

Boolean::Boolean(const xsd__boolean* value)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Boolean", "Boolean", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__boolean), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    if (value)
    {
        setNil(false);
        serialize(value);
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Boolean", "Boolean", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

Boolean::~Boolean()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Boolean", "~Boolean", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Boolean", "~Boolean", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

XSDTYPE Boolean::getType()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Boolean", "getType", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			XSDTYPE traceRet = (XSD_BOOLEAN);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Boolean", "getType", this, 0,
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return XSD_BOOLEAN;
		#endif
	}

}

xsd__boolean* Boolean::getBoolean()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Boolean", "getBoolean", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    if (isNil())
    {
        	{
		#ifdef ENABLE_AXISTRACE
			xsd__boolean* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Boolean", "getBoolean", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__boolean), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
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
			xsd__boolean* traceRet = (deserializeBoolean(m_Buf));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Boolean", "getBoolean", this, 2,
					TRACETYPE_POINTER, sizeof(xsd__boolean), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return deserializeBoolean(m_Buf);
		#endif
	}

    }
}

void * Boolean::getValue()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Boolean", "getValue", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			void* traceRet = ((void*) getBoolean());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Boolean", "getValue", this, 0,
					TRACETYPE_POINTER, 1, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (void*) getBoolean();
		#endif
	}

}

/**
 * Serialize boolean value to it's on-the-wire string form.
 * @param value The boolean value to be serialized.
 * @return Serialized form of boolean value.
 */

AxisChar* Boolean::serialize(const xsd__boolean * value) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Boolean", "serialize", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__boolean), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    AxisChar* serializedValue = new char[6];
	AxisSprintf (serializedValue, 6, "%s",
            (*((int *) (value)) == false_) ? "false" : "true");
    
    IAnySimpleType::serialize(serializedValue);
    delete [] serializedValue;        
    	{
		#ifdef ENABLE_AXISTRACE
			AxisChar* traceRet = (m_Buf);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Boolean", "serialize", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_Buf;
		#endif
	}

}

/**
 * Deserialize boolean value from it's on-the-wire string form.
 * @param valueAsChar Serialized form of boolean value.
 * @return Deserialized boolean value.
 */

xsd__boolean * Boolean::deserializeBoolean(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Boolean", "deserializeBoolean", this, 1,
					TRACETYPE_STRING, 0, ((void*)&valueAsChar));	  /* AUTOINSERTED TRACE */
	#endif

    xsd__boolean * value = new xsd__boolean;
 
	if ( 0 == strcmp (valueAsChar, "true") || 0 == strcmp (valueAsChar, "1"))
	{
		*value = true_;
	}
	else
	{
		*value =  false_;
	}
    
    	{
		#ifdef ENABLE_AXISTRACE
			xsd__boolean* traceRet = (value);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Boolean", "deserializeBoolean", this, 0,
					TRACETYPE_POINTER, sizeof(xsd__boolean), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return value;
		#endif
	}

}

WhiteSpace* Boolean::getWhiteSpace()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Boolean", "getWhiteSpace", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			WhiteSpace* traceRet = (new WhiteSpace(COLLAPSE));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Boolean", "getWhiteSpace", this, 0,
					TRACETYPE_POINTER, sizeof(WhiteSpace), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new WhiteSpace(COLLAPSE);
		#endif
	}

}

Enumeration* Boolean::getEnumeration()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Boolean", "getEnumeration", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    static AxisChar* BooleanEnumerationValue1 = "true";
    static AxisChar* BooleanEnumerationValue2 = "false";
    static AxisChar* BooleanEnumerationValue3 = "1";
    static AxisChar* BooleanEnumerationValue4 = "0";
    AxisChar* enumerationValues[] = 
        {
         BooleanEnumerationValue1,
         BooleanEnumerationValue2,
         BooleanEnumerationValue3,
         BooleanEnumerationValue4
        };
    	{
		#ifdef ENABLE_AXISTRACE
			Enumeration* traceRet = (new Enumeration(enumerationValues, sizeof(enumerationValues)/sizeof(AxisChar*)));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Boolean", "getEnumeration", this, 0,
					TRACETYPE_POINTER, sizeof(Enumeration), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new Enumeration(enumerationValues, sizeof(enumerationValues)/sizeof(AxisChar*));
		#endif
	}

}

