#ifdef ENABLE_AXISTRACE
/* TRACE ADDED BY THE TRACE INSTRUMENTOR TOOL */
#include "../common/AxisTrace.h"
#endif
/* -*- C++ -*- */

/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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
 *
 */

#include <stdio.h>

#include "BasicTypeSerializer.h"

#include "../soap/apr_base64.h"

#include "../soap/HexCoder.h"


BasicTypeSerializer::BasicTypeSerializer ()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("BasicTypeSerializer", "BasicTypeSerializer", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    m_sSZ = "";
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "BasicTypeSerializer", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

BasicTypeSerializer::~BasicTypeSerializer ()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("BasicTypeSerializer", "~BasicTypeSerializer", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "~BasicTypeSerializer", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

const AxisChar* BasicTypeSerializer::serializeAsElement (const AxisChar* pName,
    IAnySimpleType* pSimpleType)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("BasicTypeSerializer", "serializeAsElement", this, 2,
					TRACETYPE_STRING, 0, ((void*)&pName),
					TRACETYPE_POINTER, sizeof(IAnySimpleType), ((void*)&pSimpleType));	  /* AUTOINSERTED TRACE */
	#endif

		{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (serializeAsElement(pName, NULL, pSimpleType));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "serializeAsElement", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return serializeAsElement(pName, NULL, pSimpleType);
		#endif
	}

}

const AxisChar* BasicTypeSerializer::serializeAsElement (const AxisChar* pName,
    const AxisChar* pPrefix, IAnySimpleType* pSimpleType)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("BasicTypeSerializer", "serializeAsElement", this, 3,
					TRACETYPE_STRING, 0, ((void*)&pName),
					TRACETYPE_STRING, 0, ((void*)&pPrefix),
					TRACETYPE_POINTER, sizeof(IAnySimpleType), ((void*)&pSimpleType));	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (serializeAsElement(pName, pPrefix, NULL, pSimpleType));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "serializeAsElement", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return serializeAsElement(pName, pPrefix, NULL, pSimpleType);
		#endif
	}

}

const AxisChar* BasicTypeSerializer::serializeAsElement (const AxisChar* pName,
    const AxisChar* pPrefix, const AxisChar* pNamespace, IAnySimpleType* pSimpleType)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("BasicTypeSerializer", "serializeAsElement", this, 4,
					TRACETYPE_STRING, 0, ((void*)&pName),
					TRACETYPE_STRING, 0, ((void*)&pPrefix),
					TRACETYPE_STRING, 0, ((void*)&pNamespace),
					TRACETYPE_POINTER, sizeof(IAnySimpleType), ((void*)&pSimpleType));	  /* AUTOINSERTED TRACE */
	#endif

    m_sSZ = "<";
	if (NULL != pPrefix) { 
		m_sSZ += pPrefix;
		m_sSZ += ":";
	}
    
    m_sSZ += pName;
    if (NULL != pNamespace)
    {
        m_sSZ += " xmlns:";
        m_sSZ += pPrefix;
        m_sSZ += "=\"";
        m_sSZ += pNamespace;
        m_sSZ += "\"";
    }
    if (RPC_ENCODED == m_nStyle)
    {
        m_sSZ += " xsi:type=\"xsd:";
        m_sSZ += basicTypeStr (pSimpleType->getType());
        m_sSZ += "\"";
    }
    m_sSZ += ">";
    
    if (pSimpleType->isNil())
    {
        /*
         * It is a null value not an empty value.
         */
        m_sSZ = "<";
        if (NULL != pPrefix)
        { 
            m_sSZ += pPrefix;
            m_sSZ += ":";
        }
        m_sSZ += pName;
        
        if (NULL != pNamespace)
        {
            m_sSZ += " xmlns:";
            m_sSZ += pPrefix;
            m_sSZ += "=\"";
            m_sSZ += pNamespace;
            m_sSZ += "\"";
        }
        m_sSZ += " xsi:nil=\"true\">";
    }
    else
    {
        m_sSZ += pSimpleType->serialize();
    }
    m_sSZ += "</";
	if (NULL != pPrefix) {
		m_sSZ += pPrefix;
		m_sSZ += ":";
	}
    m_sSZ += pName;
    m_sSZ += ">\n";
    	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (m_sSZ.c_str ());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "serializeAsElement", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_sSZ.c_str ();
		#endif
	}

}

const AxisChar* BasicTypeSerializer::serializeAsAttribute 
    (const AxisChar* pName, const AxisChar* pPrefix,
    IAnySimpleType* pSimpleType)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("BasicTypeSerializer", "serializeAsAttribute", this, 3,
					TRACETYPE_STRING, 0, ((void*)&pName),
					TRACETYPE_STRING, 0, ((void*)&pPrefix),
					TRACETYPE_POINTER, sizeof(IAnySimpleType), ((void*)&pSimpleType));	  /* AUTOINSERTED TRACE */
	#endif

    m_sSZ = ' ';
    if (pPrefix)
    {
        m_sSZ += pPrefix;
        m_sSZ += ':';
    }
    m_sSZ += pName;
    m_sSZ += '=';
    m_sSZ += '"';
    
    m_sSZ += pSimpleType->serialize();
    m_sSZ += '"';
    	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (m_sSZ.c_str ());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "serializeAsAttribute", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_sSZ.c_str ();
		#endif
	}

}

const AxisChar* BasicTypeSerializer::basicTypeStr (XSDTYPE type)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("BasicTypeSerializer", "basicTypeStr", NULL, 1,
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&type));	  /* AUTOINSERTED TRACE */
	#endif

    switch (type)
    {
        case XSD_DURATION:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("duration");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 1,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "duration";
		#endif
	}

        case XSD_DATETIME:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("dateTime");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 2,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "dateTime";
		#endif
	}

        case XSD_TIME:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("time");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 3,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "time";
		#endif
	}

        case XSD_DATE:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("date");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 4,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "date";
		#endif
	}

        case XSD_GYEARMONTH:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("gYearMonth");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 5,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "gYearMonth";
		#endif
	}

        case XSD_GYEAR:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("gYear");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 6,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "gYear";
		#endif
	}

        case XSD_GMONTHDAY:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("gMonthDay");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 7,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "gMonthDay";
		#endif
	}

        case XSD_GDAY:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("gDay");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 8,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "gDay";
		#endif
	}

        case XSD_GMONTH:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("gMonth");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 9,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "gMonth";
		#endif
	}

        case XSD_STRING:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("string");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 10,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "string";
		#endif
	}

        case XSD_BOOLEAN:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("boolean");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 11,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "boolean";
		#endif
	}

        case XSD_BASE64BINARY:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("base64Binary");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 12,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "base64Binary";
		#endif
	}

        case XSD_HEXBINARY:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("hexBinary");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 13,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "hexBinary";
		#endif
	}

        case XSD_FLOAT:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("float");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 14,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "float";
		#endif
	}

        case XSD_DECIMAL:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("decimal");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 15,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "decimal";
		#endif
	}

        case XSD_INTEGER:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("integer");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 16,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "integer";
		#endif
	}

        case XSD_NONPOSITIVEINTEGER:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("nonPositiveInteger");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 17,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "nonPositiveInteger";
		#endif
	}

        case XSD_NEGATIVEINTEGER:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("negativeInteger");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 18,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "negativeInteger";
		#endif
	}

        case XSD_LONG:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("long");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 19,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "long";
		#endif
	}

        case XSD_INT:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("int");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 20,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "int";
		#endif
	}

        case XSD_SHORT:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("short");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 21,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "short";
		#endif
	}

        case XSD_BYTE:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("byte");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 22,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "byte";
		#endif
	}

        case XSD_NONNEGATIVEINTEGER:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("nonNegativeInteger");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 23,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "nonNegativeInteger";
		#endif
	}

        case XSD_UNSIGNEDLONG:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("unsignedLong");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 24,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "unsignedLong";
		#endif
	}

        case XSD_UNSIGNEDINT:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("unsignedInt");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 25,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "unsignedInt";
		#endif
	}

        case XSD_UNSIGNEDSHORT:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("unsignedShort");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 26,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "unsignedShort";
		#endif
	}

        case XSD_UNSIGNEDBYTE:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("unsignedByte");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 27,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "unsignedByte";
		#endif
	}

        case XSD_POSITIVEINTEGER:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("positiveInteger");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 28,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "positiveInteger";
		#endif
	}

        case XSD_DOUBLE:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("double");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 29,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "double";
		#endif
	}

        case XSD_ANYURI:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("anyURI");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 30,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "anyURI";
		#endif
	}

        case XSD_QNAME:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("QName");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 31,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "QName";
		#endif
	}

        case XSD_NOTATION:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = ("NOTATION");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 32,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "NOTATION";
		#endif
	}

        default:
            	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (" ");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "basicTypeStr", NULL, 33,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return " ";
		#endif
	}

    }
}

