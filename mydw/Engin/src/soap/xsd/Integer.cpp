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

#include "Integer.hpp"

Integer::Integer()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Integer", "Integer", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Integer", "Integer", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

Integer::~Integer()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Integer", "~Integer", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Integer", "~Integer", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

Integer::Integer(const xsd__integer* value)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Integer", "Integer", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__integer), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    if (value)
    {
        setNil(false);
        serialize(value);
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Integer", "Integer", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

XSDTYPE Integer::getType()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Integer", "getType", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			XSDTYPE traceRet = (XSD_INTEGER);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Integer", "getType", this, 0,
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return XSD_INTEGER;
		#endif
	}

}

xsd__integer* Integer::getInteger()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Integer", "getInteger", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    if (isNil())
    {
        	{
		#ifdef ENABLE_AXISTRACE
			xsd__integer* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Integer", "getInteger", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__integer), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
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
			xsd__integer* traceRet = (deserializeInteger(m_Buf));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Integer", "getInteger", this, 2,
					TRACETYPE_POINTER, sizeof(xsd__integer), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return deserializeInteger(m_Buf);
		#endif
	}

    }
}

void * Integer::getValue()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Integer", "getValue", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			void* traceRet = ((void*) getInteger());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Integer", "getValue", this, 0,
					TRACETYPE_POINTER, 1, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (void*) getInteger();
		#endif
	}

}

AxisChar* Integer::serialize(const xsd__integer* value) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Integer", "serialize", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__integer), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    MinInclusive* minInclusive = getMinInclusive();
    if (minInclusive->isSet())
    {
        if ( *value < minInclusive->getMinInclusiveAsLONGLONG() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than MinInclusive specified for this type.  MinInclusive = ";
            AxisChar* length = new AxisChar[25];
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, minInclusive->getMinInclusiveAsLONGLONG());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, *value);
            exceptionMessage += length;
            exceptionMessage += ".";
            delete [] length;
            
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    }
    delete minInclusive;
    MinExclusive* minExclusive = getMinExclusive();
    if (minExclusive->isSet())
    {
        if ( *value <= minExclusive->getMinExclusiveAsLONGLONG() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than or equal to MinExclusive specified for this type.  MinExclusive = ";
            AxisChar* length = new AxisChar[25];
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, minExclusive->getMinExclusiveAsLONGLONG());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, *value);
            exceptionMessage += length;
            exceptionMessage += ".";
            delete [] length;
            
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    }
    delete minExclusive;
    MaxInclusive* maxInclusive = getMaxInclusive();
    if (maxInclusive->isSet())
    {
        if ( *value > maxInclusive->getMaxInclusiveAsLONGLONG() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is greater than MaxInclusive specified for this type.  MaxInclusive = ";
            AxisChar* length = new AxisChar[25];
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, maxInclusive->getMaxInclusiveAsLONGLONG());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, *value);
            exceptionMessage += length;
            exceptionMessage += ".";
            delete [] length;
            
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    }
    delete maxInclusive;
    MaxExclusive* maxExclusive = getMaxExclusive();
    if (maxExclusive->isSet())
    {
        if ( *value >= maxExclusive->getMaxExclusiveAsLONGLONG() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is greater than or equal to MaxExclusive specified for this type.  MaxExclusive = ";
            AxisChar* length = new AxisChar[25];
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, maxExclusive->getMaxExclusiveAsLONGLONG());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, *value);
            exceptionMessage += length;
            exceptionMessage += ".";
            delete [] length;
            
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    }
    delete maxExclusive;
    AxisString formatSpecifier = "%";
    
    int valueSize = 80;
    TotalDigits* totalDigits = getTotalDigits();
    if (totalDigits->isSet())
    {
        valueSize = totalDigits->getTotalDigits() + 1;
        AxisChar* digits = new char[10];
        AxisSprintf (digits, 10, "%i", totalDigits->getTotalDigits());
        formatSpecifier += digits;
        delete [] digits;
    }
    delete totalDigits;
    
    formatSpecifier += PRINTF_LONGLONG_FORMAT_SPECIFIER_CHARS;
    AxisChar* serializedValue = new char[valueSize];
    AxisSprintf (serializedValue, valueSize, formatSpecifier.c_str(), *value);
    
    IAnySimpleType::serialize(serializedValue);
    delete [] serializedValue;        
    	{
		#ifdef ENABLE_AXISTRACE
			AxisChar* traceRet = (m_Buf);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Integer", "serialize", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_Buf;
		#endif
	}

}

xsd__integer* Integer::deserializeInteger(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Integer", "deserializeInteger", this, 1,
					TRACETYPE_STRING, 0, ((void*)&valueAsChar));	  /* AUTOINSERTED TRACE */
	#endif

    xsd__integer * value = new xsd__integer;
    *value = 0;
	AxisChar currentNumber[] = {'\0', '\0'};
    int stringLength = strlen(valueAsChar);
    
    if (stringLength > 0)
    {
        int count = 0;
        
        if (valueAsChar[0] == '-')
        {
            count = 1;
        }
        
        for ( ; count < stringLength ;  count ++)
        {
            *value *= 10;
    
    		currentNumber[0] = valueAsChar[count];
    
            *value += atoi(currentNumber);
        }
        
        if (valueAsChar[0] == '-')
        {
            *value *= -1;
        }
    }
    
    	{
		#ifdef ENABLE_AXISTRACE
			xsd__integer* traceRet = (value);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Integer", "deserializeInteger", this, 0,
					TRACETYPE_POINTER, sizeof(xsd__integer), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return value;
		#endif
	}

}

FractionDigits* Integer::getFractionDigits()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Integer", "getFractionDigits", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			FractionDigits* traceRet = (new FractionDigits(0));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Integer", "getFractionDigits", this, 0,
					TRACETYPE_POINTER, sizeof(FractionDigits), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new FractionDigits(0);
		#endif
	}

}

