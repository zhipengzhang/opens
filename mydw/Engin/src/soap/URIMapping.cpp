#ifdef ENABLE_AXISTRACE
/* TRACE ADDED BY THE TRACE INSTRUMENTOR TOOL */
#include "../common/AxisTrace.h"
#endif
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
 */

/*
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */

#include "URIMapping.h"

#include "../common/AxisUtils.h"

#define __TRC(X) AxisUtils::Convert(X)

using namespace std;

map<AxisXMLString, URITYPE> URIMapping::m_sURIMap;

volatile bool URIMapping::m_bInit = false;

URIMapping::URIMapping()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("URIMapping", "URIMapping", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("URIMapping", "URIMapping", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

URIMapping::~URIMapping()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("URIMapping", "~URIMapping", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("URIMapping", "~URIMapping", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

void URIMapping::initialize()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("URIMapping", "initialize", NULL, 0);	  /* AUTOINSERTED TRACE */
	#endif

    if (!m_bInit)
    {
        m_sURIMap[std::string("http://www.w3.org/2001/XMLSchema")] = URI_XSD;
        m_sURIMap[std::string("http://www.w3.org/2001/XMLSchema-instance")] = 
            URI_XSI;
        m_sURIMap[std::string("http://www.w3.org/2001/06/soap-encoding")] = URI_ENC;
		m_sURIMap[std::string("http://schemas.xmlsoap.org/soap/encoding/")] = URI_ENC;
        m_sURIMap[std::string("http://schemas.xmlsoap.org/soap/envelope/")] = 
            URI_ENVELOPE;
        m_sURIMap[std::string("http://www.w3.org/1999/XMLSchema")] = URI_XSD;
        m_sURIMap[std::string("http://www.w3.org/1999/XMLSchema-instance")] = 
            URI_XSI;
        m_bInit = true;
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("URIMapping", "initialize", NULL, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

void URIMapping::uninitialize()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("URIMapping", "uninitialize", NULL, 0);	  /* AUTOINSERTED TRACE */
	#endif

    if (m_bInit)
    {
		m_sURIMap.clear();
        m_bInit = false;
	}
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("URIMapping", "uninitialize", NULL, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

URITYPE URIMapping::getURI(const AxisXMLCh* uri)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("URIMapping", "getURI", NULL, 1,
					TRACETYPE_POINTER, sizeof(AxisXMLCh), ((void*)&uri));	  /* AUTOINSERTED TRACE */
	#endif

	if (m_sURIMap.find(std::string(uri)) != m_sURIMap.end())
    {
        	{
		#ifdef ENABLE_AXISTRACE
			URITYPE traceRet = (m_sURIMap[std::string(uri)]);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("URIMapping", "getURI", NULL, 1,
					TRACETYPE_DATA, sizeof(URITYPE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_sURIMap[std::string(uri)];
		#endif
	}

    }
    	{
		#ifdef ENABLE_AXISTRACE
			URITYPE traceRet = (URI_UNKNOWN);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("URIMapping", "getURI", NULL, 2,
					TRACETYPE_DATA, sizeof(URITYPE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return URI_UNKNOWN;
		#endif
	}

}

