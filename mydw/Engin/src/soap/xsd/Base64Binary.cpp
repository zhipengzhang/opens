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

#include "Base64Binary.hpp"

    Base64Binary::Base64Binary()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Base64Binary", "Base64Binary", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Base64Binary", "Base64Binary", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    
    Base64Binary::~Base64Binary()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Base64Binary", "~Base64Binary", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Base64Binary", "~Base64Binary", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    Base64Binary::Base64Binary(const xsd__base64Binary* value)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Base64Binary", "Base64Binary", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__base64Binary), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

        if (value)
        {
            setNil(false);
            serialize(value);
        }
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Base64Binary", "Base64Binary", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    XSDTYPE Base64Binary::getType()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Base64Binary", "getType", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			XSDTYPE traceRet = (XSD_BASE64BINARY);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Base64Binary", "getType", this, 0,
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return XSD_BASE64BINARY;
		#endif
	}

    }
    xsd__base64Binary* Base64Binary::getBase64Binary()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Base64Binary", "getBase64Binary", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        if (isNil())
        {
            	{
		#ifdef ENABLE_AXISTRACE
			xsd__base64Binary* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Base64Binary", "getBase64Binary", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__base64Binary), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
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
			xsd__base64Binary* traceRet = (deserializeBase64Binary(m_Buf));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Base64Binary", "getBase64Binary", this, 2,
					TRACETYPE_POINTER, sizeof(xsd__base64Binary), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return deserializeBase64Binary(m_Buf);
		#endif
	}

        }
    }
    void * Base64Binary::getValue()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Base64Binary", "getValue", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			void* traceRet = ((void*) getBase64Binary());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Base64Binary", "getValue", this, 0,
					TRACETYPE_POINTER, 1, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (void*) getBase64Binary();
		#endif
	}

    }
    
    AxisChar* Base64Binary::serialize(const xsd__base64Binary * value) throw (AxisSoapException)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Base64Binary", "serialize", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__base64Binary), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

        MinLength* minLength= getMinLength();
        if (minLength->isSet())
        {
            if (value->getSize() < minLength->getMinLength())
            {
                AxisString exceptionMessage =
                "Length of value to be serialized is shorter than MinLength specified for this type.  Minlength = ";
                AxisChar* length = new AxisChar[10];
                sprintf(length, "%d", minLength->getMinLength());
                exceptionMessage += length;
                exceptionMessage += ", Length of value = ";
                sprintf(length, "%d", value->getSize());
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
            if (value->getSize() > maxLength->getMaxLength())
            {
                AxisString exceptionMessage =
                "Length of value to be serialized is longer than MaxLength specified for this type.  Maxlength = ";
                AxisChar* length = new AxisChar[10];
                sprintf(length, "%d", maxLength->getMaxLength());
                exceptionMessage += length;
                exceptionMessage += ", Length of value = ";
                sprintf(length, "%d", value->getSize());
                exceptionMessage += length;
                exceptionMessage += ".";
                delete [] length;
                
                throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                    const_cast<AxisChar*>(exceptionMessage.c_str()));
            }
        }
        delete maxLength;
        Length* length= getLength();
        if (length->isSet())
        {
            if (value->getSize() != length->getLength())
            {
                AxisString exceptionMessage =
                "Length of value to be serialized is not the same as Length specified for this type.  Length = ";
                AxisChar* lengthAsString = new AxisChar[10];
                sprintf(lengthAsString, "%d", length->getLength());
                exceptionMessage += lengthAsString;
                exceptionMessage += ", Length of value = ";
                sprintf(lengthAsString, "%d", value->getSize());
                exceptionMessage += lengthAsString;
                exceptionMessage += ".";
                delete [] lengthAsString;
                
                throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                    const_cast<AxisChar*>(exceptionMessage.c_str()));
            }
        }
        delete length;
     
	    int len = apr_base64_encode_len (value->getSize());	    
	    AxisChar* serializedValue = new AxisChar[len + 1];
		int size = 0;
		xsd__unsignedByte * pTemp = value->get(size);
	    len = apr_base64_encode_binary (serializedValue, pTemp, size);
	    serializedValue[len] = 0;
	    	    
        IAnySimpleType::serialize(serializedValue);
        delete [] serializedValue;        
			{
		#ifdef ENABLE_AXISTRACE
			AxisChar* traceRet = (m_Buf);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Base64Binary", "serialize", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_Buf;
		#endif
	}

    }
	
    xsd__base64Binary * Base64Binary::deserializeBase64Binary(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Base64Binary", "deserializeBase64Binary", this, 1,
					TRACETYPE_STRING, 0, ((void*)&valueAsChar));	  /* AUTOINSERTED TRACE */
	#endif

    	xsd__base64Binary * value = new xsd__base64Binary();
	    xsd__int size = apr_base64_decode_len (valueAsChar);
	    xsd__unsignedByte * pTemp = new xsd__unsignedByte[size + 1];
	    size = apr_base64_decode_binary (pTemp, valueAsChar);
	    pTemp[size] = 0; // Null terminate so it could be used as a string
		value->set(pTemp, size);
		delete [] pTemp;
	    	{
		#ifdef ENABLE_AXISTRACE
			xsd__base64Binary* traceRet = (value);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Base64Binary", "deserializeBase64Binary", this, 0,
					TRACETYPE_POINTER, sizeof(xsd__base64Binary), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return value;
		#endif
	}

    }
    MinLength* Base64Binary::getMinLength()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Base64Binary", "getMinLength", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			MinLength* traceRet = (new MinLength());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Base64Binary", "getMinLength", this, 0,
					TRACETYPE_POINTER, sizeof(MinLength), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MinLength();
		#endif
	}

    }
    
    MaxLength* Base64Binary::getMaxLength()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Base64Binary", "getMaxLength", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			MaxLength* traceRet = (new MaxLength());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Base64Binary", "getMaxLength", this, 0,
					TRACETYPE_POINTER, sizeof(MaxLength), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MaxLength();
		#endif
	}

    }
    Length* Base64Binary::getLength()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Base64Binary", "getLength", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			Length* traceRet = (new Length());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Base64Binary", "getLength", this, 0,
					TRACETYPE_POINTER, sizeof(Length), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new Length();
		#endif
	}

    }
    
    WhiteSpace* Base64Binary::getWhiteSpace()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Base64Binary", "getWhiteSpace", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			WhiteSpace* traceRet = (new WhiteSpace(COLLAPSE));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Base64Binary", "getWhiteSpace", this, 0,
					TRACETYPE_POINTER, sizeof(WhiteSpace), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new WhiteSpace(COLLAPSE);
		#endif
	}

    }


