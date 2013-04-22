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
 *  @author Roshan Weerasuriya (roshan@opensource.lk, roshan@jkcsworld.com, roshan_444@yahoo.com)
 */

#include "Namespace.h"

#include "SoapSerializer.h"

//////////////////////////////////////////////////////////////////////

// Construction/Destruction

//////////////////////////////////////////////////////////////////////

Namespace::Namespace()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Namespace", "Namespace", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Namespace", "Namespace", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

Namespace::~Namespace()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Namespace", "~Namespace", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Namespace", "~Namespace", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

Namespace::Namespace(const AxisChar* achPrefix, const AxisChar* achURI)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Namespace", "Namespace", this, 2,
					TRACETYPE_STRING, 0, ((void*)&achPrefix),
					TRACETYPE_STRING, 0, ((void*)&achURI));	  /* AUTOINSERTED TRACE */
	#endif

	m_asPrefix = achPrefix;
	m_asURI = achURI;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Namespace", "Namespace", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

int Namespace::setPrefix(const AxisChar* achPrefix)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Namespace", "setPrefix", this, 1,
					TRACETYPE_STRING, 0, ((void*)&achPrefix));	  /* AUTOINSERTED TRACE */
	#endif

    if (achPrefix)
    {
	   m_asPrefix = achPrefix;
       	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Namespace", "setPrefix", this, 1,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

    }
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Namespace", "setPrefix", this, 2,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}

}

int Namespace::setURI(const AxisChar* achURI)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Namespace", "setURI", this, 1,
					TRACETYPE_STRING, 0, ((void*)&achURI));	  /* AUTOINSERTED TRACE */
	#endif

    if (achURI)
    {
        m_asURI = achURI;
        	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Namespace", "setURI", this, 1,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

    }
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Namespace", "setURI", this, 2,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}

}

const AxisChar* Namespace::getURI()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Namespace", "getURI", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

		{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (m_asURI.c_str());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Namespace", "getURI", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_asURI.c_str();
		#endif
	}

}

const AxisChar* Namespace::getPrefix()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Namespace", "getPrefix", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

		{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (m_asPrefix.c_str());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Namespace", "getPrefix", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_asPrefix.c_str();
		#endif
	}

}

int Namespace::serialize(SoapSerializer& pSZ, list<AxisChar*>& lstTmpNameSpaceStack)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Namespace", "serialize", this, 2,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ),
					TRACETYPE_DATA, sizeof(list<AxisChar* >&), ((void*)&lstTmpNameSpaceStack));	  /* AUTOINSERTED TRACE */
	#endif

	/*Adding the new namespace to the Serializer*/
	pSZ.addNamespaceToNamespaceList(m_asURI.c_str(), m_asPrefix.c_str());
	/*Adding the namespace to the temporary stack, so that it will be removed
	*  at the end of the logical block. The logical block could be a HeaderBlock,
	*  a Soap Method etc.
	*/
	lstTmpNameSpaceStack.push_back((AxisChar*)m_asURI.c_str());
	pSZ.serialize(" xmlns:", m_asPrefix.c_str(), "=\"", m_asURI.c_str(), "\"", NULL);
		{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Namespace", "serialize", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

