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

#include "HexBinary.hpp"

    HexBinary::HexBinary()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HexBinary", "HexBinary", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HexBinary", "HexBinary", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    HexBinary::~HexBinary()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HexBinary", "~HexBinary", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HexBinary", "~HexBinary", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    HexBinary::HexBinary(const xsd__hexBinary* value)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HexBinary", "HexBinary", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__hexBinary), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

        if (value)
        {
            setNil(false);
            serialize(value);
        }
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HexBinary", "HexBinary", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    
    XSDTYPE HexBinary::getType()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HexBinary", "getType", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			XSDTYPE traceRet = (XSD_HEXBINARY);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HexBinary", "getType", this, 0,
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return XSD_HEXBINARY;
		#endif
	}

    }
    xsd__hexBinary* HexBinary::getHexBinary()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HexBinary", "getHexBinary", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        if (isNil())
        {
            	{
		#ifdef ENABLE_AXISTRACE
			xsd__hexBinary* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HexBinary", "getHexBinary", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__hexBinary), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
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
			xsd__hexBinary* traceRet = (deserializeHexBinary(m_Buf));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HexBinary", "getHexBinary", this, 2,
					TRACETYPE_POINTER, sizeof(xsd__hexBinary), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return deserializeHexBinary(m_Buf);
		#endif
	}

        }
    }
    void * HexBinary::getValue()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HexBinary", "getValue", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			void* traceRet = ((void*) getHexBinary());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HexBinary", "getValue", this, 0,
					TRACETYPE_POINTER, 1, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (void*) getHexBinary();
		#endif
	}

    }    
    AxisChar* HexBinary::serialize(const xsd__hexBinary * value) throw (AxisSoapException)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HexBinary", "serialize", this, 1,
					TRACETYPE_POINTER, sizeof(xsd__hexBinary), ((void*)&value));	  /* AUTOINSERTED TRACE */
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
     
		char* serializedValue = new char[value->getSize() * 2 + 1];
		int size = 0;
		xsd__unsignedByte * pTemp = value->get(size);
	    Hex_Encode (serializedValue, pTemp, size);
	    serializedValue[value->getSize() * 2] = 0;
	    
        IAnySimpleType::serialize(serializedValue);
        delete [] serializedValue;
	    	{
		#ifdef ENABLE_AXISTRACE
			AxisChar* traceRet = (m_Buf);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HexBinary", "serialize", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_Buf;
		#endif
	}

    }
	
    xsd__hexBinary * HexBinary::deserializeHexBinary(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HexBinary", "deserializeHexBinary", this, 1,
					TRACETYPE_STRING, 0, ((void*)&valueAsChar));	  /* AUTOINSERTED TRACE */
	#endif

    	xsd__hexBinary * value = new xsd__hexBinary();    	
	    int size = strlen (valueAsChar) / 2;
		xsd__unsignedByte * pTemp = new xsd__unsignedByte[size + 1];
	    Hex_Decode (pTemp, valueAsChar);
	    pTemp[size] = 0; // Null terminate so it could be used as a string
		value->set(pTemp, size);
		delete [] pTemp;
	    	{
		#ifdef ENABLE_AXISTRACE
			xsd__hexBinary* traceRet = (value);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HexBinary", "deserializeHexBinary", this, 0,
					TRACETYPE_POINTER, sizeof(xsd__hexBinary), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return value;
		#endif
	}

    }
    MinLength* HexBinary::getMinLength()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HexBinary", "getMinLength", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			MinLength* traceRet = (new MinLength());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HexBinary", "getMinLength", this, 0,
					TRACETYPE_POINTER, sizeof(MinLength), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MinLength();
		#endif
	}

    }
    
    MaxLength* HexBinary::getMaxLength()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HexBinary", "getMaxLength", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			MaxLength* traceRet = (new MaxLength());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HexBinary", "getMaxLength", this, 0,
					TRACETYPE_POINTER, sizeof(MaxLength), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new MaxLength();
		#endif
	}

    }
    Length* HexBinary::getLength()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HexBinary", "getLength", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			Length* traceRet = (new Length());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HexBinary", "getLength", this, 0,
					TRACETYPE_POINTER, sizeof(Length), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new Length();
		#endif
	}

    }

