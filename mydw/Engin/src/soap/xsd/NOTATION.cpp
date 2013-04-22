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

#include "NOTATION.hpp"

NOTATION::NOTATION()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NOTATION", "NOTATION", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NOTATION", "NOTATION", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

NOTATION::NOTATION(const xsd__NOTATION value)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NOTATION", "NOTATION", this, 1,
					TRACETYPE_DATA, sizeof(xsd__NOTATION), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    if (value)
    {
        setNil(false);
        serialize(value);
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NOTATION", "NOTATION", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

XSDTYPE NOTATION::getType()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NOTATION", "getType", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			XSDTYPE traceRet = (XSD_NOTATION);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NOTATION", "getType", this, 0,
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return XSD_NOTATION;
		#endif
	}

}

xsd__NOTATION NOTATION::getNOTATION()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NOTATION", "getNOTATION", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    if (isNil())
    {
        	{
		#ifdef ENABLE_AXISTRACE
			xsd__NOTATION traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NOTATION", "getNOTATION", this, 1,
					TRACETYPE_DATA, sizeof(xsd__NOTATION), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
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
			xsd__NOTATION traceRet = (deserializeNOTATION(m_Buf));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NOTATION", "getNOTATION", this, 2,
					TRACETYPE_DATA, sizeof(xsd__NOTATION), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return deserializeNOTATION(m_Buf);
		#endif
	}

    }
}

void * NOTATION::getValue()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NOTATION", "getValue", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			void* traceRet = ((void*) getNOTATION());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NOTATION", "getValue", this, 0,
					TRACETYPE_POINTER, 1, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (void*) getNOTATION();
		#endif
	}

}

AxisChar* NOTATION::serialize(const xsd__NOTATION value) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NOTATION", "serialize", this, 1,
					TRACETYPE_DATA, sizeof(xsd__NOTATION), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    MinLength* minLength= getMinLength();
    if (minLength->isSet())
    {
        if (strlen(value) < (unsigned int) minLength->getMinLength())
        {
            AxisString exceptionMessage =
            "Length of value to be serialized is shorter than MinLength specified for this type.  Minlength = ";
            AxisChar* length = new AxisChar[10];
            sprintf(length, "%d", minLength->getMinLength());
            exceptionMessage += length;
            exceptionMessage += ", Length of value = ";
            sprintf(length, "%d", strlen(value));
            exceptionMessage += length;
            exceptionMessage += ".";
            delete [] length;
            
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    }
    delete minLength;
    
    MaxLength* maxLength = getMaxLength();
    if (maxLength->isSet())
    {
        if (strlen(value) > (unsigned int) maxLength->getMaxLength())
        {
            AxisString exceptionMessage =
            "Length of value to be serialized is longer than MaxLength specified for this type.  Maxlength = ";
            AxisChar* length = new AxisChar[10];
            sprintf(length, "%d", maxLength->getMaxLength());
            exceptionMessage += length;
            exceptionMessage += ", Length of value = ";
            sprintf(length, "%d", strlen(value));
            exceptionMessage += length;
            exceptionMessage += ".";
            delete [] length;
            
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    }
    delete maxLength;
    Length* length = getLength();
    if (length->isSet())
    {
        if (strlen(value) != (unsigned int) length->getLength())
        {
            AxisString exceptionMessage =
            "Length of value to be serialized is not the same as Length specified for this type.  Length = ";
            AxisChar* lengthAsString = new AxisChar[10];
            sprintf(lengthAsString, "%d", length->getLength());
            exceptionMessage += lengthAsString;
            exceptionMessage += ", Length of value = ";
            sprintf(lengthAsString, "%d", strlen(value));
            exceptionMessage += lengthAsString;
            exceptionMessage += ".";
            delete [] lengthAsString;
            
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    }
    delete length;
    
	AxisString valueAsString = value;
	AxisChar* serializedValue = (AxisChar*) replaceReservedCharacters(valueAsString).c_str();
    IAnySimpleType::serialize(serializedValue);
		{
		#ifdef ENABLE_AXISTRACE
			AxisChar* traceRet = (m_Buf);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NOTATION", "serialize", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_Buf;
		#endif
	}

}

xsd__NOTATION NOTATION::deserializeNOTATION(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NOTATION", "deserializeNOTATION", this, 1,
					TRACETYPE_STRING, 0, ((void*)&valueAsChar));	  /* AUTOINSERTED TRACE */
	#endif

	xsd__NOTATION value = new char[strlen (valueAsChar) + 1];
	strcpy (value, valueAsChar);
		{
		#ifdef ENABLE_AXISTRACE
			xsd__NOTATION traceRet = (value);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NOTATION", "deserializeNOTATION", this, 0,
					TRACETYPE_DATA, sizeof(xsd__NOTATION), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return value;
		#endif
	}

}

WhiteSpace* NOTATION::getWhiteSpace()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NOTATION", "getWhiteSpace", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			WhiteSpace* traceRet = (new WhiteSpace(PRESERVE));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NOTATION", "getWhiteSpace", this, 0,
					TRACETYPE_POINTER, sizeof(WhiteSpace), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new WhiteSpace(PRESERVE);
		#endif
	}

}

MinLength* NOTATION::getMinLength()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NOTATION", "getMinLength", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			MinLength* traceRet = (new MinLength());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NOTATION", "getMinLength", this, 0,
					TRACETYPE_POINTER, sizeof(MinLength), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MinLength();
		#endif
	}

}

MaxLength* NOTATION::getMaxLength()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NOTATION", "getMaxLength", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			MaxLength* traceRet = (new MaxLength());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NOTATION", "getMaxLength", this, 0,
					TRACETYPE_POINTER, sizeof(MaxLength), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MaxLength();
		#endif
	}

}

Length* NOTATION::getLength()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("NOTATION", "getLength", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			Length* traceRet = (new Length());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("NOTATION", "getLength", this, 0,
					TRACETYPE_POINTER, sizeof(Length), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new Length();
		#endif
	}

}

