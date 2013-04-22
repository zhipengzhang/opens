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

#include "XSD_QName.hpp"

    XSD_QName::XSD_QName()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("XSD_QName", "XSD_QName", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("XSD_QName", "XSD_QName", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    XSD_QName::XSD_QName(const xsd__QName value)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("XSD_QName", "XSD_QName", this, 1,
					TRACETYPE_DATA, sizeof(xsd__QName), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

        if (value)
        {
            setNil(false);
            serialize(value);
        }
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("XSD_QName", "XSD_QName", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    
    XSDTYPE XSD_QName::getType()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("XSD_QName", "getType", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			XSDTYPE traceRet = (XSD_QNAME);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("XSD_QName", "getType", this, 0,
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return XSD_QNAME;
		#endif
	}

    }
    
    xsd__QName XSD_QName::getQName()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("XSD_QName", "getQName", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        if (isNil())
        {
            	{
		#ifdef ENABLE_AXISTRACE
			xsd__QName traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("XSD_QName", "getQName", this, 1,
					TRACETYPE_DATA, sizeof(xsd__QName), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
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
			xsd__QName traceRet = (deserializeQName(m_Buf));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("XSD_QName", "getQName", this, 2,
					TRACETYPE_DATA, sizeof(xsd__QName), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return deserializeQName(m_Buf);
		#endif
	}

        }
    }
    void * XSD_QName::getValue()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("XSD_QName", "getValue", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			void* traceRet = ((void*) getQName());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("XSD_QName", "getValue", this, 0,
					TRACETYPE_POINTER, 1, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (void*) getQName();
		#endif
	}

    }
    
    AxisChar* XSD_QName::serialize(const xsd__QName value) throw (AxisSoapException)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("XSD_QName", "serialize", this, 1,
					TRACETYPE_DATA, sizeof(xsd__QName), ((void*)&value));	  /* AUTOINSERTED TRACE */
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
				axiscpp::AxisTrace::traceExit("XSD_QName", "serialize", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_Buf;
		#endif
	}

    }
	
    xsd__QName XSD_QName::deserializeQName(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("XSD_QName", "deserializeQName", this, 1,
					TRACETYPE_STRING, 0, ((void*)&valueAsChar));	  /* AUTOINSERTED TRACE */
	#endif

		xsd__QName value = new char[strlen (valueAsChar) + 1];
		strcpy (value, valueAsChar);
			{
		#ifdef ENABLE_AXISTRACE
			xsd__QName traceRet = (value);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("XSD_QName", "deserializeQName", this, 0,
					TRACETYPE_DATA, sizeof(xsd__QName), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return value;
		#endif
	}

    }
    WhiteSpace* XSD_QName::getWhiteSpace()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("XSD_QName", "getWhiteSpace", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			WhiteSpace* traceRet = (new WhiteSpace(COLLAPSE));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("XSD_QName", "getWhiteSpace", this, 0,
					TRACETYPE_POINTER, sizeof(WhiteSpace), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new WhiteSpace(COLLAPSE);
		#endif
	}

    }
    
    MinLength* XSD_QName::getMinLength()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("XSD_QName", "getMinLength", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			MinLength* traceRet = (new MinLength());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("XSD_QName", "getMinLength", this, 0,
					TRACETYPE_POINTER, sizeof(MinLength), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MinLength();
		#endif
	}

    }
    
    MaxLength* XSD_QName::getMaxLength()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("XSD_QName", "getMaxLength", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			MaxLength* traceRet = (new MaxLength());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("XSD_QName", "getMaxLength", this, 0,
					TRACETYPE_POINTER, sizeof(MaxLength), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MaxLength();
		#endif
	}

    }   
    Length* XSD_QName::getLength()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("XSD_QName", "getLength", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			Length* traceRet = (new Length());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("XSD_QName", "getLength", this, 0,
					TRACETYPE_POINTER, sizeof(Length), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new Length();
		#endif
	}

    }


