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

#include "Decimal.hpp"

Decimal::Decimal()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Decimal", "Decimal", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Decimal", "Decimal", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

Decimal::~Decimal()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Decimal", "~Decimal", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Decimal", "~Decimal", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

Decimal::Decimal(const xsd__decimal* value)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Decimal", "Decimal", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__decimal), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    if (value)
    {
        setNil(false);
        serialize(value);
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Decimal", "Decimal", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

XSDTYPE Decimal::getType()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Decimal", "getType", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			XSDTYPE traceRet = (XSD_DECIMAL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Decimal", "getType", this, 0,
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return XSD_DECIMAL;
		#endif
	}

}

xsd__decimal* Decimal::getDecimal()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Decimal", "getDecimal", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    if (isNil())
    {
        	{
		#ifdef ENABLE_AXISTRACE
			xsd__decimal* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Decimal", "getDecimal", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__decimal), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
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
			xsd__decimal* traceRet = (deserializeDecimal(m_Buf));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Decimal", "getDecimal", this, 2,
					TRACETYPE_POINTER, sizeof(xsd__decimal), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return deserializeDecimal(m_Buf);
		#endif
	}

    }
}

void * Decimal::getValue()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Decimal", "getValue", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			void* traceRet = ((void*) getDecimal());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Decimal", "getValue", this, 0,
					TRACETYPE_POINTER, 1, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (void*) getDecimal();
		#endif
	}

}

AxisChar* Decimal::serialize(const xsd__decimal* value) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Decimal", "serialize", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__decimal), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    MinInclusive* minInclusive = getMinInclusive();
    if (minInclusive->isSet())
    {
        if ( *value < minInclusive->getMinInclusiveAsDouble() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than MinInclusive specified for this type.  MinInclusive = ";
            AxisChar* length = new AxisChar[25];
            sprintf(length, "%f", minInclusive->getMinInclusiveAsDouble());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, "%f", *value);
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
        if ( *value <= minExclusive->getMinExclusiveAsDouble() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than or equal to MinExclusive specified for this type.  MinExclusive = ";
            AxisChar* length = new AxisChar[25];
            sprintf(length, "%f", minExclusive->getMinExclusiveAsDouble());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, "%f", *value);
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
        if ( *value > maxInclusive->getMaxInclusiveAsDouble() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is greater than MaxInclusive specified for this type.  MaxInclusive = ";
            AxisChar* length = new AxisChar[25];
            sprintf(length, "%f", maxInclusive->getMaxInclusiveAsDouble());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, "%f", *value);
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
        if ( *value >= maxExclusive->getMaxExclusiveAsDouble() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is greater than or equal to MaxExclusive specified for this type.  MaxExclusive = ";
            AxisChar* length = new AxisChar[25];
            sprintf(length, "%f", maxExclusive->getMaxExclusiveAsDouble());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, "%f", *value);
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
    
    FractionDigits* fractionDigits = getFractionDigits();
    if (fractionDigits->isSet())
    {
        formatSpecifier += ".";
        AxisChar* digits = new char[10];
        AxisSprintf (digits, 10, "%i", fractionDigits->getFractionDigits());
        formatSpecifier += digits;
        delete [] digits;
    }
    delete fractionDigits;
    
    formatSpecifier += "f";
    AxisChar* serializedValue = new char[valueSize];
    AxisSprintf (serializedValue, valueSize, formatSpecifier.c_str(), *value);
    
	
    IAnySimpleType::serialize(serializedValue);
    delete [] serializedValue;        
    	{
		#ifdef ENABLE_AXISTRACE
			AxisChar* traceRet = (m_Buf);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Decimal", "serialize", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_Buf;
		#endif
	}

}

xsd__decimal* Decimal::deserializeDecimal(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Decimal", "deserializeDecimal", this, 1,
					TRACETYPE_STRING, 0, ((void*)&valueAsChar));	  /* AUTOINSERTED TRACE */
	#endif

	AxisChar* end;
   
	xsd__decimal * value = new xsd__decimal;
	*value = strtod (valueAsChar, &end);
	
		{
		#ifdef ENABLE_AXISTRACE
			xsd__decimal* traceRet = (value);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Decimal", "deserializeDecimal", this, 0,
					TRACETYPE_POINTER, sizeof(xsd__decimal), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return value;
		#endif
	}

}

WhiteSpace* Decimal::getWhiteSpace()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Decimal", "getWhiteSpace", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			WhiteSpace* traceRet = (new WhiteSpace(COLLAPSE));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Decimal", "getWhiteSpace", this, 0,
					TRACETYPE_POINTER, sizeof(WhiteSpace), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new WhiteSpace(COLLAPSE);
		#endif
	}

}

MinInclusive* Decimal::getMinInclusive()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Decimal", "getMinInclusive", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			MinInclusive* traceRet = (new MinInclusive());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Decimal", "getMinInclusive", this, 0,
					TRACETYPE_POINTER, sizeof(MinInclusive), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MinInclusive();
		#endif
	}

}

MinExclusive* Decimal::getMinExclusive()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Decimal", "getMinExclusive", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			MinExclusive* traceRet = (new MinExclusive());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Decimal", "getMinExclusive", this, 0,
					TRACETYPE_POINTER, sizeof(MinExclusive), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MinExclusive();
		#endif
	}

}

MaxInclusive* Decimal::getMaxInclusive()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Decimal", "getMaxInclusive", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			MaxInclusive* traceRet = (new MaxInclusive());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Decimal", "getMaxInclusive", this, 0,
					TRACETYPE_POINTER, sizeof(MaxInclusive), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MaxInclusive();
		#endif
	}

}

MaxExclusive* Decimal::getMaxExclusive()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Decimal", "getMaxExclusive", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			MaxExclusive* traceRet = (new MaxExclusive());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Decimal", "getMaxExclusive", this, 0,
					TRACETYPE_POINTER, sizeof(MaxExclusive), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MaxExclusive();
		#endif
	}

}

TotalDigits* Decimal::getTotalDigits()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Decimal", "getTotalDigits", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			TotalDigits* traceRet = (new TotalDigits());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Decimal", "getTotalDigits", this, 0,
					TRACETYPE_POINTER, sizeof(TotalDigits), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new TotalDigits();
		#endif
	}

}

FractionDigits* Decimal::getFractionDigits()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Decimal", "getFractionDigits", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			FractionDigits* traceRet = (new FractionDigits());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Decimal", "getFractionDigits", this, 0,
					TRACETYPE_POINTER, sizeof(FractionDigits), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new FractionDigits();
		#endif
	}

}

