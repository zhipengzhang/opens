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

#include "NonNegativeInteger.hpp"

NonNegativeInteger::NonNegativeInteger()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NonNegativeInteger", "NonNegativeInteger", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NonNegativeInteger", "NonNegativeInteger", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

NonNegativeInteger::NonNegativeInteger(const xsd__nonNegativeInteger* value) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NonNegativeInteger", "NonNegativeInteger", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__nonNegativeInteger), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    if (value)
    {
        if((*value) < 0) // the value must be non negative, hence validate and fix
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR, "NonNegativeInteger value must be non negative");
        setNil(false);
        serialize(value);
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NonNegativeInteger", "NonNegativeInteger", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

NonNegativeInteger::~NonNegativeInteger()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NonNegativeInteger", "~NonNegativeInteger", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NonNegativeInteger", "~NonNegativeInteger", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

XSDTYPE NonNegativeInteger::getType()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NonNegativeInteger", "getType", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			XSDTYPE traceRet = (XSD_NONNEGATIVEINTEGER);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NonNegativeInteger", "getType", this, 0,
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return XSD_NONNEGATIVEINTEGER;
		#endif
	}

}

xsd__nonNegativeInteger* NonNegativeInteger::getNonNegativeInteger()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NonNegativeInteger", "getNonNegativeInteger", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    if (isNil())
    {
        	{
		#ifdef ENABLE_AXISTRACE
			xsd__nonNegativeInteger* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NonNegativeInteger", "getNonNegativeInteger", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__nonNegativeInteger), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
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
			xsd__nonNegativeInteger* traceRet = (deserializeNonNegativeInteger(m_Buf));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NonNegativeInteger", "getNonNegativeInteger", this, 2,
					TRACETYPE_POINTER, sizeof(xsd__nonNegativeInteger), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return deserializeNonNegativeInteger(m_Buf);
		#endif
	}

    }
}

void * NonNegativeInteger::getValue()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NonNegativeInteger", "getValue", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			void* traceRet = ((void*) getNonNegativeInteger());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NonNegativeInteger", "getValue", this, 0,
					TRACETYPE_POINTER, 1, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (void*) getNonNegativeInteger();
		#endif
	}

}

AxisChar* NonNegativeInteger::serialize(const xsd__nonNegativeInteger* value) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NonNegativeInteger", "serialize", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__nonNegativeInteger), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    MinInclusive* minInclusive = getMinInclusive();
    if (minInclusive->isSet())
    {
        if ( *value < minInclusive->getMinInclusiveAsUnsignedLONGLONG() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than MinInclusive specified for this type.  MinInclusive = ";
            AxisChar* length = new AxisChar[25];
            sprintf(length, PRINTF_UNSIGNED_LONGLONG_FORMAT_SPECIFIER, minInclusive->getMinInclusiveAsUnsignedLONGLONG());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, PRINTF_UNSIGNED_LONGLONG_FORMAT_SPECIFIER, *value);
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
        if ( *value <= minExclusive->getMinExclusiveAsUnsignedLONGLONG() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than or equal to MinExclusive specified for this type.  MinExclusive = ";
            AxisChar* length = new AxisChar[25];
            sprintf(length, PRINTF_UNSIGNED_LONGLONG_FORMAT_SPECIFIER, minExclusive->getMinExclusiveAsUnsignedLONGLONG());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, PRINTF_UNSIGNED_LONGLONG_FORMAT_SPECIFIER, *value);
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
        if ( *value > maxInclusive->getMaxInclusiveAsUnsignedLONGLONG() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than MaxInclusive specified for this type.  MaxInclusive = ";
            AxisChar* length = new AxisChar[25];
            sprintf(length, PRINTF_UNSIGNED_LONGLONG_FORMAT_SPECIFIER, maxInclusive->getMaxInclusiveAsUnsignedLONGLONG());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, PRINTF_UNSIGNED_LONGLONG_FORMAT_SPECIFIER, *value);
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
        if ( *value >= maxExclusive->getMaxExclusiveAsUnsignedLONGLONG() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than or equal to MaxExclusive specified for this type.  MaxExclusive = ";
            AxisChar* length = new AxisChar[25];
            sprintf(length, PRINTF_UNSIGNED_LONGLONG_FORMAT_SPECIFIER, maxExclusive->getMaxExclusiveAsUnsignedLONGLONG());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, PRINTF_UNSIGNED_LONGLONG_FORMAT_SPECIFIER, *value);
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
    
    formatSpecifier += PRINTF_UNSIGNED_LONGLONG_FORMAT_SPECIFIER_CHARS;
    AxisChar* serializedValue = new char[valueSize];
    AxisSprintf (serializedValue, valueSize, formatSpecifier.c_str(), *value);
  
    IAnySimpleType::serialize(serializedValue);
    delete [] serializedValue;        
    	{
		#ifdef ENABLE_AXISTRACE
			AxisChar* traceRet = (m_Buf);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NonNegativeInteger", "serialize", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_Buf;
		#endif
	}

}

xsd__nonNegativeInteger* NonNegativeInteger::deserializeNonNegativeInteger(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NonNegativeInteger", "deserializeNonNegativeInteger", this, 1,
					TRACETYPE_STRING, 0, ((void*)&valueAsChar));	  /* AUTOINSERTED TRACE */
	#endif

    xsd__nonNegativeInteger * value = new xsd__nonNegativeInteger;
    *value = 0;
    AxisChar currentNumber[] = {'\0', '\0'};
    int stringLength = strlen(valueAsChar);
    
    if (stringLength > 0)
    {
        int count = 0;
        
        for ( ; count < stringLength ;  count ++)
        {
            *value *= 10;
    		currentNumber[0] = valueAsChar[count];
            *value += atoi(currentNumber);
        }
    }
    	{
		#ifdef ENABLE_AXISTRACE
			xsd__nonNegativeInteger* traceRet = (value);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NonNegativeInteger", "deserializeNonNegativeInteger", this, 0,
					TRACETYPE_POINTER, sizeof(xsd__nonNegativeInteger), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return value;
		#endif
	}

}

MinInclusive* NonNegativeInteger::getMinInclusive()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NonNegativeInteger", "getMinInclusive", this, 0);	  /* AUTOINSERTED TRACE */
	#endif
   
    	{
		#ifdef ENABLE_AXISTRACE
			MinInclusive* traceRet = (new MinInclusive((unsigned LONGLONG) 0));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NonNegativeInteger", "getMinInclusive", this, 0,
					TRACETYPE_POINTER, sizeof(MinInclusive), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MinInclusive((unsigned LONGLONG) 0);
		#endif
	}

}

