#ifdef ENABLE_AXISTRACE
/* TRACE ADDED BY THE TRACE INSTRUMENTOR TOOL */
#include "../common/AxisTrace.h"
#endif
/* -*- C++ -*- */

/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 *
 * @author Susantha Kumara (skumara@virtusa.com)
 * @author Roshan Weerasuriya (roshanw@jkcsworld.com, roshan@opensource.lk, roshan_444@yahoo.com)
 *
 */

/*
 * Revision 1.1  2005/01/19 roshan
 * Added decodeFromBase64Binary
 */

#include "AxisUtils.h"

#include <axis/AxisUserAPI.hpp>

#include "../soap/apr_base64.h"

AxisXMLCh AxisUtils::m_Buffer[CONVERT_BUFFER_SIZE];

AxisUtils::AxisUtils ()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AxisUtils", "AxisUtils", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AxisUtils", "AxisUtils", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

AxisUtils::~AxisUtils ()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AxisUtils", "~AxisUtils", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AxisUtils", "~AxisUtils", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

const AxisXMLCh* AxisUtils::ToAxisXMLCh (const AxisChar* pch)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AxisUtils", "ToAxisXMLCh", NULL, 1,
					TRACETYPE_STRING, 0, ((void*)&pch));	  /* AUTOINSERTED TRACE */
	#endif

    /* return XMLString::transcode(pch); 
     *     this is ok as long as we use xerces library.
     */
    	{
		#ifdef ENABLE_AXISTRACE
			const AxisXMLCh* traceRet = (pch);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AxisUtils", "ToAxisXMLCh", NULL, 0,
					TRACETYPE_POINTER, sizeof(AxisXMLCh), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return pch;
		#endif
	}

}

void AxisUtils::initialize ()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AxisUtils", "initialize", NULL, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AxisUtils", "initialize", NULL, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

/* following functions is not thread safe and should only be used 
 * for initialization purposes.
 */

const AxisXMLCh *
AxisUtils::Convert (const AxisChar * pch)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AxisUtils", "Convert", NULL, 1,
					TRACETYPE_STRING, 0, ((void*)&pch));	  /* AUTOINSERTED TRACE */
	#endif

/*    if (XMLString::transcode(pch, m_Buffer, CONVERT_BUFFER_SIZE))
 *        return m_Buffer;
 *    return NULL;
 */
    	{
		#ifdef ENABLE_AXISTRACE
			const AxisXMLCh* traceRet = (pch);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AxisUtils", "Convert", NULL, 0,
					TRACETYPE_POINTER, sizeof(AxisXMLCh), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return pch;
		#endif
	}

}

int AxisUtils::clearArray (char* arrCh, int iSize)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AxisUtils", "clearArray", NULL, 2,
					TRACETYPE_STRING, 0, ((void*)&arrCh),
					TRACETYPE_INT, 0, ((void*)&iSize));	  /* AUTOINSERTED TRACE */
	#endif

    for (int iTmp = 0; iTmp < iSize; iTmp++)
    {
        arrCh[iTmp] = '\0';
    }
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AxisUtils", "clearArray", NULL, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

bool AxisUtils::isCharacterAvailable (const string &sString,
    const char cCharacter)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AxisUtils", "isCharacterAvailable", NULL, 2,
					TRACETYPE_STLSTRING, 0, ((void*)&sString),
					TRACETYPE_CHAR, 0, ((void*)&cCharacter));	  /* AUTOINSERTED TRACE */
	#endif

    bool bFoundStatus = false;
    if ((sString.find (cCharacter, 0)) != string::npos)
    {
        bFoundStatus = true;
    }
    	{
		#ifdef ENABLE_AXISTRACE
			bool traceRet = (bFoundStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AxisUtils", "isCharacterAvailable", NULL, 0,
					TRACETYPE_BOOL, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return bFoundStatus;
		#endif
	}

}

bool AxisUtils::isCharacterAvailable (const char* pchStringToSearch,
    const char cCharacter)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AxisUtils", "isCharacterAvailable", NULL, 2,
					TRACETYPE_STRING, 0, ((void*)&pchStringToSearch),
					TRACETYPE_CHAR, 0, ((void*)&cCharacter));	  /* AUTOINSERTED TRACE */
	#endif

    bool bFoundStatus = false;
    if (strchr (pchStringToSearch, cCharacter))
    {
        bFoundStatus = true;
    }
    	{
		#ifdef ENABLE_AXISTRACE
			bool traceRet = (bFoundStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AxisUtils", "isCharacterAvailable", NULL, 0,
					TRACETYPE_BOOL, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return bFoundStatus;
		#endif
	}

}

string AxisUtils::toUpperCase (const string sWord)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AxisUtils", "toUpperCase", NULL, 1,
					TRACETYPE_STLSTRING, 0, ((void*)&sWord));	  /* AUTOINSERTED TRACE */
	#endif

    /* Fill the code */
    	{
		#ifdef ENABLE_AXISTRACE
			string traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AxisUtils", "toUpperCase", NULL, 0,
					TRACETYPE_STLSTRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

}

char* AxisUtils::toUpperCase (const char* pchWord)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AxisUtils", "toUpperCase", NULL, 1,
					TRACETYPE_STRING, 0, ((void*)&pchWord));	  /* AUTOINSERTED TRACE */
	#endif

    /* Fill the code */
    	{
		#ifdef ENABLE_AXISTRACE
			char* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AxisUtils", "toUpperCase", NULL, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

}

string AxisUtils::toLowerCase (const string sWord)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AxisUtils", "toLowerCase", NULL, 1,
					TRACETYPE_STLSTRING, 0, ((void*)&sWord));	  /* AUTOINSERTED TRACE */
	#endif

    /* Fill the code */
    	{
		#ifdef ENABLE_AXISTRACE
			string traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AxisUtils", "toLowerCase", NULL, 0,
					TRACETYPE_STLSTRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

}

char* AxisUtils::toLowerCase (const char* pchWord)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AxisUtils", "toLowerCase", NULL, 1,
					TRACETYPE_STRING, 0, ((void*)&pchWord));	  /* AUTOINSERTED TRACE */
	#endif

    /* Fill the code */
    	{
		#ifdef ENABLE_AXISTRACE
			char* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AxisUtils", "toLowerCase", NULL, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

}

xsd__base64Binary * AxisUtils::decodeFromBase64Binary(const AxisChar *pValue)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AxisUtils", "decodeFromBase64Binary", NULL, 1,
					TRACETYPE_STRING, 0, ((void*)&pValue));	  /* AUTOINSERTED TRACE */
	#endif

    xsd__base64Binary* value = new xsd__base64Binary();
	int size = apr_base64_decode_len (pValue);
	xsd__unsignedByte * pTemp = new unsigned char[size + 1];
	size = apr_base64_decode_binary (pTemp, pValue);
	pTemp[size] = 0; // Null terminate so it could be used as a string
	value->set(pTemp, size);
	delete [] pTemp;
    	{
		#ifdef ENABLE_AXISTRACE
			xsd__base64Binary* traceRet = (value);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AxisUtils", "decodeFromBase64Binary", NULL, 0,
					TRACETYPE_POINTER, sizeof(xsd__base64Binary), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return value;
		#endif
	}

}

bool AxisUtils::isStringOnlyWithSpaces(const char* pchWord)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AxisUtils", "isStringOnlyWithSpaces", NULL, 1,
					TRACETYPE_STRING, 0, ((void*)&pchWord));	  /* AUTOINSERTED TRACE */
	#endif

	bool blnStatus = true;
	int iLen = strlen(pchWord);
	for (int i=0; i<iLen; i++) {	
		if (pchWord[i] != ' ') {
			blnStatus = false;	
			break;
		}
	}
		{
		#ifdef ENABLE_AXISTRACE
			bool traceRet = (blnStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AxisUtils", "isStringOnlyWithSpaces", NULL, 0,
					TRACETYPE_BOOL, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return blnStatus;
		#endif
	}

}

IAnySimpleType* AxisUtils::createSimpleTypeObject(XSDTYPE type)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AxisUtils", "createSimpleTypeObject", NULL, 1,
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&type));	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			IAnySimpleType* traceRet = (createSimpleTypeObject(NULL, type));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AxisUtils", "createSimpleTypeObject", NULL, 0,
					TRACETYPE_POINTER, sizeof(IAnySimpleType), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return createSimpleTypeObject(NULL, type);
		#endif
	}

}

IAnySimpleType* AxisUtils::createSimpleTypeObject(void * pValue, XSDTYPE type)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AxisUtils", "createSimpleTypeObject", NULL, 2,
					TRACETYPE_POINTER, 1, ((void*)&pValue),
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&type));	  /* AUTOINSERTED TRACE */
	#endif

    IAnySimpleType* xsdValue = NULL;
    switch (type)
    {
        case XSD_FLOAT:
            xsdValue = new Float((xsd__float*) pValue);
            break;
        case XSD_BOOLEAN:
            xsdValue = new Boolean((xsd__boolean*) pValue);
            break;
        case XSD_DOUBLE:
            xsdValue = new Double((xsd__double*) pValue);
            break;
        case XSD_DURATION:
            xsdValue = new Duration((xsd__duration*) pValue);
            break;
        case XSD_DATETIME:
            xsdValue = new DateTime((xsd__dateTime*) pValue);
            break;
        case XSD_TIME:
            xsdValue = new Time((xsd__time*) pValue);
            break;
        case XSD_DATE:
            xsdValue = new Date((xsd__date*) pValue);
            break;
        case XSD_GYEARMONTH:
            xsdValue = new GYearMonth((xsd__gYearMonth*) pValue);
            break;
        case XSD_GYEAR:
            xsdValue = new GYear((xsd__gYear*) pValue);
            break;
        case XSD_GMONTHDAY:
            xsdValue = new GMonthDay((xsd__gMonthDay*) pValue);
            break;
        case XSD_GDAY:
            xsdValue = new GDay((xsd__gDay*) pValue);
            break;
        case XSD_GMONTH:
            xsdValue = new GMonth((xsd__gMonth*) pValue);
            break;
        case XSD_HEXBINARY:
            xsdValue = new HexBinary((xsd__hexBinary*) pValue);
            break;
        case XSD_BASE64BINARY:
            xsdValue = new Base64Binary((xsd__base64Binary*) pValue);
            break;
        case XSD_ANYURI:
            xsdValue = new AnyURI((xsd__anyURI) pValue);
            break;
        case XSD_QNAME:
            xsdValue = new XSD_QName((xsd__QName) pValue);
            break;
        case XSD_NOTATION:
            xsdValue = new NOTATION((xsd__NOTATION) pValue);
            break;
        case XSD_DECIMAL:
            xsdValue = new Decimal((xsd__decimal*) pValue);
            break;
        case XSD_INTEGER:
            xsdValue = new Integer((xsd__integer*) pValue);
            break;
        case XSD_LONG:
            xsdValue = new Long((xsd__long*) pValue);
            break;
        case XSD_INT:
            xsdValue = new Int((xsd__int*) pValue);
            break;
        case XSD_SHORT:
            xsdValue = new Short((xsd__short*) pValue);
            break;
        case XSD_BYTE:
            xsdValue = new Byte((xsd__byte*) pValue);
            break;
        case XSD_NONNEGATIVEINTEGER:
            xsdValue = new NonNegativeInteger((xsd__nonNegativeInteger*) pValue);
            break;
        case XSD_UNSIGNEDLONG:
            xsdValue = new UnsignedLong((xsd__unsignedLong*) pValue);
            break;
        case XSD_UNSIGNEDINT:
            xsdValue = new UnsignedInt((xsd__unsignedInt*) pValue);
            break;
        case XSD_UNSIGNEDSHORT:
            xsdValue = new UnsignedShort((xsd__unsignedShort*) pValue);
            break;
        case XSD_UNSIGNEDBYTE:
            xsdValue = new UnsignedByte((xsd__unsignedByte*) pValue);
            break;
        case XSD_POSITIVEINTEGER:
            xsdValue = new PositiveInteger((xsd__positiveInteger*) pValue);
            break;
        case XSD_NONPOSITIVEINTEGER:
            xsdValue = new NonPositiveInteger((xsd__nonPositiveInteger*) pValue);
            break;
        case XSD_NEGATIVEINTEGER:
            xsdValue = new NegativeInteger((xsd__negativeInteger*) pValue);
            break;
        case XSD_STRING:
            xsdValue = new String((xsd__string) pValue);
            break;
        case XSD_NORMALIZEDSTRING:
            xsdValue = new NormalizedString((xsd__normalizedString) pValue);
            break;
        case XSD_TOKEN:
            xsdValue = new Tokens((xsd__token) pValue);
            break;
        case XSD_LANGUAGE:
            xsdValue = new Language((xsd__language) pValue);
            break;
        case XSD_NAME:
            xsdValue = new Name((xsd__Name) pValue);
            break;
        case XSD_NCNAME:
            xsdValue = new NCName((xsd__NCName) pValue);
            break;
        case XSD_ID:
            xsdValue = new ID((xsd__ID) pValue);
            break;
        case XSD_IDREF:
            xsdValue = new IDREF((xsd__IDREF) pValue);
            break;
        case XSD_IDREFS:
            xsdValue = new IDREFS((xsd__IDREFS) pValue);
            break;
        case XSD_ENTITY:
            xsdValue = new ENTITY((xsd__ENTITY) pValue);
            break;
        case XSD_ENTITIES:
            xsdValue = new ENTITIES((xsd__ENTITIES) pValue);
            break;
        case XSD_NMTOKEN:
            xsdValue = new NMTOKEN((xsd__NMTOKEN) pValue);
            break;
        case XSD_NMTOKENS:
            xsdValue = new NMTOKENS((xsd__NMTOKENS) pValue);
            break;
        default:
            break;
    }
    
    	{
		#ifdef ENABLE_AXISTRACE
			IAnySimpleType* traceRet = (xsdValue);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AxisUtils", "createSimpleTypeObject", NULL, 0,
					TRACETYPE_POINTER, sizeof(IAnySimpleType), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return xsdValue;
		#endif
	}

}

