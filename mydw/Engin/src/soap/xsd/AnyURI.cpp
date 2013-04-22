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

#include "AnyURI.hpp"

    AnyURI::AnyURI()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AnyURI", "AnyURI", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AnyURI", "AnyURI", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    AnyURI::AnyURI(const xsd__anyURI value)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AnyURI", "AnyURI", this, 1,
					TRACETYPE_DATA, sizeof(xsd__anyURI), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

        if (value)
        {
            setNil(false);            
            serialize(value);
        }
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AnyURI", "AnyURI", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    
    XSDTYPE AnyURI::getType()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AnyURI", "getType", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			XSDTYPE traceRet = (XSD_ANYURI);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AnyURI", "getType", this, 0,
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return XSD_ANYURI;
		#endif
	}

    }
    xsd__anyURI AnyURI::getAnyURI()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AnyURI", "getAnyURI", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        if (isNil())
        {
            	{
		#ifdef ENABLE_AXISTRACE
			xsd__anyURI traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AnyURI", "getAnyURI", this, 1,
					TRACETYPE_DATA, sizeof(xsd__anyURI), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
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
			xsd__anyURI traceRet = (deserializeAnyURI(m_Buf));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AnyURI", "getAnyURI", this, 2,
					TRACETYPE_DATA, sizeof(xsd__anyURI), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return deserializeAnyURI(m_Buf);
		#endif
	}

        }
    }
    void * AnyURI::getValue()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AnyURI", "getValue", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			void* traceRet = ((void*) getAnyURI());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AnyURI", "getValue", this, 0,
					TRACETYPE_POINTER, 1, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (void*) getAnyURI();
		#endif
	}

    }
    AxisChar* AnyURI::serialize(const xsd__anyURI value) throw (AxisSoapException)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AnyURI", "serialize", this, 1,
					TRACETYPE_DATA, sizeof(xsd__anyURI), ((void*)&value));	  /* AUTOINSERTED TRACE */
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
				axiscpp::AxisTrace::traceExit("AnyURI", "serialize", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_Buf;
		#endif
	}

    }
	
    xsd__anyURI AnyURI::deserializeAnyURI(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AnyURI", "deserializeAnyURI", this, 1,
					TRACETYPE_STRING, 0, ((void*)&valueAsChar));	  /* AUTOINSERTED TRACE */
	#endif

        xsd__anyURI value = new char[strlen (valueAsChar) + 1];
		strcpy (value, valueAsChar);
			{
		#ifdef ENABLE_AXISTRACE
			xsd__anyURI traceRet = (value);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AnyURI", "deserializeAnyURI", this, 0,
					TRACETYPE_DATA, sizeof(xsd__anyURI), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return value;
		#endif
	}

    }
    WhiteSpace* AnyURI::getWhiteSpace()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AnyURI", "getWhiteSpace", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			WhiteSpace* traceRet = (new WhiteSpace(REPLACE));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AnyURI", "getWhiteSpace", this, 0,
					TRACETYPE_POINTER, sizeof(WhiteSpace), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new WhiteSpace(REPLACE);
		#endif
	}

    }
    MinLength* AnyURI::getMinLength()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AnyURI", "getMinLength", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			MinLength* traceRet = (new MinLength());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AnyURI", "getMinLength", this, 0,
					TRACETYPE_POINTER, sizeof(MinLength), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MinLength();
		#endif
	}

    }
    
    MaxLength* AnyURI::getMaxLength()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AnyURI", "getMaxLength", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			MaxLength* traceRet = (new MaxLength());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AnyURI", "getMaxLength", this, 0,
					TRACETYPE_POINTER, sizeof(MaxLength), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MaxLength();
		#endif
	}

    }
    Length* AnyURI::getLength()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AnyURI", "getLength", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			Length* traceRet = (new Length());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AnyURI", "getLength", this, 0,
					TRACETYPE_POINTER, sizeof(Length), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new Length();
		#endif
	}

    }

