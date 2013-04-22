#ifdef ENABLE_AXISTRACE
/* TRACE ADDED BY THE TRACE INSTRUMENTOR TOOL */
#include "../../../common/AxisTrace.h"
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

#include "MaxInclusive.hpp"


    MaxInclusive::MaxInclusive(LONGLONG maxInclusive)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MaxInclusive", "MaxInclusive", this, 1,
					TRACETYPE_DATA, sizeof(LONGLONG), ((void*)&maxInclusive));	  /* AUTOINSERTED TRACE */
	#endif

        m_MaxInclusive.longlongMaxInclusive = maxInclusive;
        m_isSet = true;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MaxInclusive", "MaxInclusive", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    MaxInclusive::MaxInclusive(unsigned LONGLONG maxInclusive)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MaxInclusive", "MaxInclusive", this, 1,
					TRACETYPE_DATA, sizeof(unsigned LONGLONG), ((void*)&maxInclusive));	  /* AUTOINSERTED TRACE */
	#endif

        m_MaxInclusive.unsignedLongLongMaxInclusive = maxInclusive;
        m_isSet = true;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MaxInclusive", "MaxInclusive", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    MaxInclusive::MaxInclusive(double maxInclusive)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MaxInclusive", "MaxInclusive", this, 1,
					TRACETYPE_DOUBLE, 0, ((void*)&maxInclusive));	  /* AUTOINSERTED TRACE */
	#endif

        m_MaxInclusive.doubleMaxInclusive = maxInclusive;
        m_isSet = true;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MaxInclusive", "MaxInclusive", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    
    MaxInclusive::MaxInclusive(struct tm maxInclusive)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MaxInclusive", "MaxInclusive", this, 1,
					TRACETYPE_DATA, sizeof(struct tm), ((void*)&maxInclusive));	  /* AUTOINSERTED TRACE */
	#endif

        m_MaxInclusive.structTMMaxInclusive = maxInclusive;
        m_isSet = true;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MaxInclusive", "MaxInclusive", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    MaxInclusive::MaxInclusive()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MaxInclusive", "MaxInclusive", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        m_isSet = false;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MaxInclusive", "MaxInclusive", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    
    LONGLONG MaxInclusive::getMaxInclusiveAsLONGLONG()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MaxInclusive", "getMaxInclusiveAsLONGLONG", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			LONGLONG traceRet = (m_MaxInclusive.longlongMaxInclusive);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MaxInclusive", "getMaxInclusiveAsLONGLONG", this, 0,
					TRACETYPE_DATA, sizeof(LONGLONG), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_MaxInclusive.longlongMaxInclusive;
		#endif
	}

    }
    unsigned LONGLONG MaxInclusive::getMaxInclusiveAsUnsignedLONGLONG()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MaxInclusive", "getMaxInclusiveAsUnsignedLONGLONG", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			unsigned LONGLONG traceRet = (m_MaxInclusive.unsignedLongLongMaxInclusive);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MaxInclusive", "getMaxInclusiveAsUnsignedLONGLONG", this, 0,
					TRACETYPE_DATA, sizeof(unsigned LONGLONG), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_MaxInclusive.unsignedLongLongMaxInclusive;
		#endif
	}

    }
    
    double MaxInclusive::getMaxInclusiveAsDouble()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MaxInclusive", "getMaxInclusiveAsDouble", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			double traceRet = (m_MaxInclusive.doubleMaxInclusive);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MaxInclusive", "getMaxInclusiveAsDouble", this, 0,
					TRACETYPE_DOUBLE, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_MaxInclusive.doubleMaxInclusive;
		#endif
	}

    }
    
    struct tm MaxInclusive::getMaxInclusiveAsStructTM()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MaxInclusive", "getMaxInclusiveAsStructTM", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			struct tm traceRet = (m_MaxInclusive.structTMMaxInclusive);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MaxInclusive", "getMaxInclusiveAsStructTM", this, 0,
					TRACETYPE_DATA, sizeof(struct tm), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_MaxInclusive.structTMMaxInclusive;
		#endif
	}

    }
   

