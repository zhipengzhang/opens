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

/*
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */

#include "SoapKeywordMapping.h"

//#include "../common/AxisUtils.h"

extern SoapEnvVersionsStruct gs_SoapEnvVersionsStruct[VERSION_LAST];

SoapKeywordStruct SoapKeywordMapping::m_Map[VERSION_LAST];

volatile bool SoapKeywordMapping::m_bInit = false;

#define __TRC(X) AxisUtils::ToAxisXMLCh(X)

SoapKeywordMapping::SoapKeywordMapping()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapKeywordMapping", "SoapKeywordMapping", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapKeywordMapping", "SoapKeywordMapping", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

SoapKeywordMapping::~SoapKeywordMapping()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapKeywordMapping", "~SoapKeywordMapping", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapKeywordMapping", "~SoapKeywordMapping", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

void SoapKeywordMapping::initialize()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapKeywordMapping", "initialize", NULL, 0);	  /* AUTOINSERTED TRACE */
	#endif

    if (!m_bInit)
    {
        for (int sv = SOAP_VER_1_1; sv < VERSION_LAST; sv++)
        {
            m_Map[sv].pchNamespaceUri = 
              __TRC(gs_SoapEnvVersionsStruct[sv].pchNamespaceUri);
            m_Map[sv].pchPrefix = 
                __TRC(gs_SoapEnvVersionsStruct[sv].pchPrefix);
            for (int sw = SKW_ENVELOPE; sw < SOAP_WORDS_LAST; sw++)
            {
                m_Map[sv].pchWords[sw] = 
                    __TRC(gs_SoapEnvVersionsStruct[sv].pchWords[sw]);
            }
        }
        std::list<Attribute*> attributeList;
        // soap 1.1 envelop attributes 
        m_Map[SOAP_VER_1_1].pEnv = new Attribute( attributeList, "SOAP-ENV","xmlns","",
            "http://schemas.xmlsoap.org/soap/envelope/");
        m_Map[SOAP_VER_1_1].pXsi = new Attribute( attributeList, "xsi","xmlns","",
            "http://www.w3.org/2001/XMLSchema-instance");
        m_Map[SOAP_VER_1_1].pXsd = new Attribute( attributeList, "xsd","xmlns","",
            "http://www.w3.org/2001/XMLSchema");
        // soap 1.2 envelop attributes 
        m_Map[SOAP_VER_1_2].pEnv = new Attribute( attributeList, "env","xmlns","",
            "http://www.w3.org/2003/05/soap-envelope");
        m_Map[SOAP_VER_1_2].pXsi = new Attribute( attributeList, "xsi","xmlns","",
            "http://www.w3.org/2001/XMLSchema-instance");
        m_Map[SOAP_VER_1_2].pXsd = new Attribute( attributeList, "xsd","xmlns","",
            "http://www.w3.org/2001/XMLSchema");
        m_bInit = true;
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapKeywordMapping", "initialize", NULL, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

void SoapKeywordMapping::uninitialize()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapKeywordMapping", "uninitialize", NULL, 0);	  /* AUTOINSERTED TRACE */
	#endif

    if (m_bInit)
    {
        // soap 1.1 envelop attributes 
        delete m_Map[SOAP_VER_1_1].pEnv;
        delete m_Map[SOAP_VER_1_1].pXsi;
        delete m_Map[SOAP_VER_1_1].pXsd;
        delete m_Map[SOAP_VER_1_2].pEnv;
        delete m_Map[SOAP_VER_1_2].pXsi;
        delete m_Map[SOAP_VER_1_2].pXsd;
        m_bInit = false;
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapKeywordMapping", "uninitialize", NULL, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

const SoapKeywordStruct& SoapKeywordMapping::map(int nVersion)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapKeywordMapping", "map", NULL, 1,
					TRACETYPE_INT, 0, ((void*)&nVersion));	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			const SoapKeywordStruct& traceRet = (m_Map[nVersion]);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapKeywordMapping", "map", NULL, 0,
					TRACETYPE_DATA, sizeof(SoapKeywordStruct&), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_Map[nVersion];
		#endif
	}

}	
