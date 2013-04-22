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

#include "ENTITIES.hpp"

ENTITIES::ENTITIES()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ENTITIES", "ENTITIES", this, 0);	  /* AUTOINSERTED TRACE */
	#endif
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ENTITIES", "ENTITIES", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

ENTITIES::ENTITIES(const xsd__ENTITIES value)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ENTITIES", "ENTITIES", this, 1,
					TRACETYPE_DATA, sizeof(xsd__ENTITIES), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

	if (value)
    {
        setNil(false);
        serialize(value);
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ENTITIES", "ENTITIES", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

XSDTYPE ENTITIES::getType()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ENTITIES", "getType", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			XSDTYPE traceRet = (XSD_ENTITIES);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ENTITIES", "getType", this, 0,
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return XSD_ENTITIES;
		#endif
	}

}

xsd__ENTITIES ENTITIES::getENTITIES()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ENTITIES", "getENTITIES", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    if (isNil())
    {
        	{
		#ifdef ENABLE_AXISTRACE
			xsd__ENTITIES traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ENTITIES", "getENTITIES", this, 1,
					TRACETYPE_DATA, sizeof(xsd__ENTITIES), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
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
			xsd__ENTITIES traceRet = (deserializeENTITIES(m_Buf));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ENTITIES", "getENTITIES", this, 2,
					TRACETYPE_DATA, sizeof(xsd__ENTITIES), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return deserializeENTITIES(m_Buf);
		#endif
	}

    }
}

void * ENTITIES::getValue()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ENTITIES", "getValue", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			void* traceRet = ((void*) getENTITIES());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ENTITIES", "getValue", this, 0,
					TRACETYPE_POINTER, 1, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (void*) getENTITIES();
		#endif
	}

}

xsd__ENTITIES ENTITIES::deserializeENTITIES(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ENTITIES", "deserializeENTITIES", this, 1,
					TRACETYPE_STRING, 0, ((void*)&valueAsChar));	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			xsd__ENTITIES traceRet = ((xsd__ENTITIES) deserializeENTITY(valueAsChar));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ENTITIES", "deserializeENTITIES", this, 0,
					TRACETYPE_DATA, sizeof(xsd__ENTITIES), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (xsd__ENTITIES) deserializeENTITY(valueAsChar);
		#endif
	}

}


