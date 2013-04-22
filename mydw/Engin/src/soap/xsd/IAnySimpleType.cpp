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

#include "IAnySimpleType.hpp"

IAnySimpleType::IAnySimpleType():m_Buf(NULL), m_isNil(true)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("IAnySimpleType", "IAnySimpleType", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("IAnySimpleType", "IAnySimpleType", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

IAnySimpleType::~IAnySimpleType()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("IAnySimpleType", "~IAnySimpleType", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    if (m_Buf)
    {
        delete [] m_Buf;
        m_Buf = NULL;
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("IAnySimpleType", "~IAnySimpleType", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

bool IAnySimpleType::isNil()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("IAnySimpleType", "isNil", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			bool traceRet = (m_isNil);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("IAnySimpleType", "isNil", this, 0,
					TRACETYPE_BOOL, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_isNil;
		#endif
	}

}

void IAnySimpleType::setNil(bool nil)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("IAnySimpleType", "setNil", this, 1,
					TRACETYPE_BOOL, 0, ((void*)&nil));	  /* AUTOINSERTED TRACE */
	#endif

    m_isNil = nil;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("IAnySimpleType", "setNil", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

AxisChar* IAnySimpleType::serialize()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("IAnySimpleType", "serialize", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			AxisChar* traceRet = (m_Buf);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("IAnySimpleType", "serialize", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_Buf;
		#endif
	}

}

void IAnySimpleType::deserialize(const AxisChar* value)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("IAnySimpleType", "deserialize", this, 1,
					TRACETYPE_STRING, 0, ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    if (m_Buf)
    {
        delete [] m_Buf;
        m_Buf = NULL;
    }
 
    if (value)
    {
        setNil(false);        
        m_Buf = new char[strlen (value) + 1];
        strcpy (m_Buf, value);
    }
    else
    {
        setNil(true);
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("IAnySimpleType", "deserialize", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

AxisChar* IAnySimpleType::serialize(const AxisChar* value) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("IAnySimpleType", "serialize", this, 1,
					TRACETYPE_STRING, 0, ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    WhiteSpace* whiteSpace = getWhiteSpace();
    const AxisChar* serializedValue = whiteSpace->processWhiteSpace(value);
    Pattern* pattern = getPattern();
    if(pattern->isSet())
    {
        pattern->validatePattern(serializedValue);
    }
    delete pattern;
    Enumeration* enumeration = getEnumeration();
    if (enumeration->isSet())
    {
        enumeration->validateEnumeration(serializedValue);
    }
    delete enumeration;
    if (m_Buf)
    {
        delete [] m_Buf;
        m_Buf = NULL;
    } 
    m_Buf = new char[strlen (serializedValue) + 1];
    strcpy (m_Buf, serializedValue);
    delete whiteSpace;
    	{
		#ifdef ENABLE_AXISTRACE
			AxisChar* traceRet = (m_Buf);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("IAnySimpleType", "serialize", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_Buf;
		#endif
	}

}

const AxisString& IAnySimpleType::replaceReservedCharacters(AxisString &value)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("IAnySimpleType", "replaceReservedCharacters", this, 1,
					TRACETYPE_STLSTRING, 0, ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    m_strReturnVal = "";
    if (value.empty ())
    {
        	{
		#ifdef ENABLE_AXISTRACE
			const AxisString& traceRet = (value);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("IAnySimpleType", "replaceReservedCharacters", this, 1,
					TRACETYPE_STLSTRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return value;
		#endif
	}

    }
    /* Find entity reference characters and returns the first any of chars find
     * position
     */ 
    unsigned long nPos = value.find_first_of (XML_ENTITY_REFERENCE_CHARS);
    /* Check for position validity */
    if (AxisString::npos == nPos)
    {
        	{
		#ifdef ENABLE_AXISTRACE
			const AxisString& traceRet = (value);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("IAnySimpleType", "replaceReservedCharacters", this, 2,
					TRACETYPE_STLSTRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return value;
		#endif
	}

    }
    unsigned long nOldIdx = 0;            // Counter value
    while (AxisString::npos != nPos)
    {                         // Get pointered character
        switch (value.at (nPos))
        {
            case LESSER_THAN_CHAR:     // Process < character
                m_strReturnVal.append (value.substr (nOldIdx, nPos - nOldIdx));
                m_strReturnVal.append (ENCODED_LESSER_STR);
                break;
            case GREATER_THAN_CHAR:    // Process > character
                m_strReturnVal.append (value.substr (nOldIdx, nPos - nOldIdx));
                m_strReturnVal.append (ENCODED_GREATER_STR);
                break;
            case AMPERSAND_CHAR:       // Process & character
                m_strReturnVal.append (value.substr (nOldIdx, nPos - nOldIdx));
                m_strReturnVal.append (ENCODED_AMPERSAND_STR);
                break;
            case DOUBLE_QUOTE_CHAR:    // Process " character
                m_strReturnVal.append (value.substr (nOldIdx, nPos - nOldIdx));
                m_strReturnVal.append (ENCODED_DBL_QUOTE_STR);
                break;
            case SINGLE_QUOTE_CHAR:    // Process ' character
                m_strReturnVal.append (value.substr (nOldIdx, nPos - nOldIdx));
                m_strReturnVal.append (ENCODED_SGL_QUOTE_STR);
                break;
        }
        nOldIdx = ++nPos;     // Get old position
    /* Find the next entity reference characters from previous found 
	 * position,
	 */ 
        nPos = value.find_first_of (XML_ENTITY_REFERENCE_CHARS, nPos);
    }
    unsigned long nDataLen = value.length ();    // Get the length of the field value
    unsigned long nLen = nDataLen - nOldIdx;      // Get remaining number of characters   
    if (nLen > 0)
    {
        m_strReturnVal += value.substr (nOldIdx, nLen); /* Apend the remaining
							  * data
							  */ 
    }
    	{
		#ifdef ENABLE_AXISTRACE
			const AxisString& traceRet = (m_strReturnVal);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("IAnySimpleType", "replaceReservedCharacters", this, 3,
					TRACETYPE_STLSTRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_strReturnVal;
		#endif
	}

}

WhiteSpace* IAnySimpleType::getWhiteSpace()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("IAnySimpleType", "getWhiteSpace", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			WhiteSpace* traceRet = (new WhiteSpace(PRESERVE));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("IAnySimpleType", "getWhiteSpace", this, 0,
					TRACETYPE_POINTER, sizeof(WhiteSpace), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new WhiteSpace(PRESERVE);
		#endif
	}

}

Pattern* IAnySimpleType::getPattern()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("IAnySimpleType", "getPattern", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			Pattern* traceRet = (new Pattern());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("IAnySimpleType", "getPattern", this, 0,
					TRACETYPE_POINTER, sizeof(Pattern), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new Pattern();
		#endif
	}

}

Enumeration* IAnySimpleType::getEnumeration()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("IAnySimpleType", "getEnumeration", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			Enumeration* traceRet = (new Enumeration());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("IAnySimpleType", "getEnumeration", this, 0,
					TRACETYPE_POINTER, sizeof(Enumeration), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new Enumeration();
		#endif
	}

}

