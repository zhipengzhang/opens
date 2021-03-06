#ifdef ENABLE_AXISTRACE
/* TRACE ADDED BY THE TRACE INSTRUMENTOR TOOL */
#include "../common/AxisTrace.h"
#endif
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
 */

/**
 * @file BasicTypeSerializer.h
 *
 * This file contains the BasicTypeSerializer class which has the functions
 * that the Serializer uses to serialize all xsd basic types.
 *
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 */
  
#if !defined(_BASICTYPESERIALIZER_H____OF_AXIS_INCLUDED_)

#define _BASICTYPESERIALIZER_H____OF_AXIS_INCLUDED_

#include <axis/TypeMapping.hpp>

#include <string>

#include "AxisUtils.h"

using namespace std;

#define BTS_BUFFSIZE 32

const AxisChar XML_ENTITY_REFERENCE_CAHRS[]    = "<>&\"\'";

/* Entity reference characters */

//const AxisChar ENCODED_LESSER_STR[]            = "&lt;";    
/* Encoded string for less than character */

const AxisChar ENCODED_GREATOR_STR[]        = "&gt;";    
/* Encoded string for greator than character */

//llh const AxisChar ENCODED_AMPERSAND_STR[]        = "&amp;";    
/* Encoded string for ampersand character */

//llh const AxisChar ENCODED_DBL_QUOTE_STR[]        = "&quot;";    
/* Encoded string for single quote character */

//llh const AxisChar ENCODED_SGL_QUOTE_STR[]        = "&apos;";    
/* Encoded string for double quote character */

/*
 *   @class BasicTypeSerializer
 *   @brief interface for the BasicTypeSerializer class.
 *
 *   @author Susantha Kumara (skumara@virtusa.com)
 */

class BasicTypeSerializer
{
    friend class SoapSerializer;

public:
    BasicTypeSerializer();
    virtual ~BasicTypeSerializer();
    /**
     * Serializes a SOAP Element.
     * 
     * This is essentially serializeAsElement(const AxisChar* pName, const AxisChar* pPrefix, IAnySimpleType* pSimpleType, XSDTYPE type)
     * with pPrefix = NULL;
     * 
     * @param pName the name gives for this element.
     * @param pSimpleType the value for this element.
     */
    const AxisChar* serializeAsElement(const AxisChar* pName, 
        IAnySimpleType* pSimpleType);
    /**
     * Serializes a SOAP Element.
     * 
     * This is essentially serializeAsElement(const AxisChar* pName, const AxisChar* pPrefix, const AxisChar* pNamespace, IAnySimpleType* pSimpleType, XSDTYPE type)
     * with pNamespace = NULL;
     * 
     * @param pName the name gives for this element.
     * @param pPrefix the optional prefix for this element.
     * @param pSimpleType the value for this element.
     */
	const AxisChar* serializeAsElement(const AxisChar* pName, 
        const AxisChar* pPrefix, IAnySimpleType* pSimpleType);
    /**
     * Serializes a SOAP Element.
     * If a namespace is provided, it will be declared, so ensure appropriate
     * checks have taken place before providing a namespace.
     * 
     * @param pName the name gives for this element.
     * @param pPrefix the optional prefix for this element.
     * @param pNamespace the namespace uri to be used for this element and prefix.
     * @param pSimpleType the value for this element.
     */
    const AxisChar* serializeAsElement(const AxisChar* pName, 
        const AxisChar* pPrefix, const AxisChar* pNamespace, IAnySimpleType* pSimpleType);
    const AxisChar* serializeAsAttribute(const AxisChar* pName, 
        const AxisChar* pPrefix, IAnySimpleType* pSimpleType);
    void setStyle(AXIS_BINDING_STYLE nStyle){
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("BasicTypeSerializer", "setStyle", NULL, 1,
					TRACETYPE_DATA, sizeof(AXIS_BINDING_STYLE), ((void*)&nStyle));	  /* AUTOINSERTED TRACE */
	#endif
 m_nStyle = nStyle;	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("BasicTypeSerializer", "setStyle", NULL, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
};
    static const AxisChar* basicTypeStr(XSDTYPE type);

private:
    enum
    {
        GREATOR_THAN_CHAR    =    '>',    /* Greator than character */
        LESSER_THAN_CHAR    =    '<',    /* Less than character */
        SINGLE_QUOTE_CHAR    =    '\'',    /* Single quotation character */
        DOUBLE_QUOTE_CHAR    =    '\"',    /* Double quotation character */
        AMPERSAND_CHAR        =    '&'    /* Ampersand character */
    };

private:
    AxisString m_sSZ;
    /* Current Serialization Style */
    AXIS_BINDING_STYLE m_nStyle;

};

#endif 

