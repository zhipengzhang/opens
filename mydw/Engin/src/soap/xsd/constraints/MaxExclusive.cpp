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

#include "MaxExclusive.hpp"


    MaxExclusive::MaxExclusive(LONGLONG maxExclusive)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MaxExclusive", "MaxExclusive", this, 1,
					TRACETYPE_DATA, sizeof(LONGLONG), ((void*)&maxExclusive));	  /* AUTOINSERTED TRACE */
	#endif

        m_MaxExclusive.longlongMaxExclusive = maxExclusive;
        m_isSet = true;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MaxExclusive", "MaxExclusive", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    MaxExclusive::MaxExclusive(unsigned LONGLONG maxExclusive)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MaxExclusive", "MaxExclusive", this, 1,
					TRACETYPE_DATA, sizeof(unsigned LONGLONG), ((void*)&maxExclusive));	  /* AUTOINSERTED TRACE */
	#endif

        m_MaxExclusive.unsignedLongLongMaxExclusive = maxExclusive;
        m_isSet = true;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MaxExclusive", "MaxExclusive", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    MaxExclusive::MaxExclusive(double maxExclusive)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MaxExclusive", "MaxExclusive", this, 1,
					TRACETYPE_DOUBLE, 0, ((void*)&maxExclusive));	  /* AUTOINSERTED TRACE */
	#endif

        m_MaxExclusive.doubleMaxExclusive = maxExclusive;
        m_isSet = true;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MaxExclusive", "MaxExclusive", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    
    MaxExclusive::MaxExclusive(struct tm maxExclusive)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MaxExclusive", "MaxExclusive", this, 1,
					TRACETYPE_DATA, sizeof(struct tm), ((void*)&maxExclusive));	  /* AUTOINSERTED TRACE */
	#endif

        m_MaxExclusive.structTMMaxExclusive = maxExclusive;
        m_isSet = true;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MaxExclusive", "MaxExclusive", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    MaxExclusive::MaxExclusive()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MaxExclusive", "MaxExclusive", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        m_isSet = false;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MaxExclusive", "MaxExclusive", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    
    LONGLONG MaxExclusive::getMaxExclusiveAsLONGLONG()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MaxExclusive", "getMaxExclusiveAsLONGLONG", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			LONGLONG traceRet = (m_MaxExclusive.longlongMaxExclusive);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MaxExclusive", "getMaxExclusiveAsLONGLONG", this, 0,
					TRACETYPE_DATA, sizeof(LONGLONG), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_MaxExclusive.longlongMaxExclusive;
		#endif
	}

    }
    unsigned LONGLONG MaxExclusive::getMaxExclusiveAsUnsignedLONGLONG()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MaxExclusive", "getMaxExclusiveAsUnsignedLONGLONG", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			unsigned LONGLONG traceRet = (m_MaxExclusive.unsignedLongLongMaxExclusive);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MaxExclusive", "getMaxExclusiveAsUnsignedLONGLONG", this, 0,
					TRACETYPE_DATA, sizeof(unsigned LONGLONG), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_MaxExclusive.unsignedLongLongMaxExclusive;
		#endif
	}

    }
    
    double MaxExclusive::getMaxExclusiveAsDouble()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MaxExclusive", "getMaxExclusiveAsDouble", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			double traceRet = (m_MaxExclusive.doubleMaxExclusive);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MaxExclusive", "getMaxExclusiveAsDouble", this, 0,
					TRACETYPE_DOUBLE, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_MaxExclusive.doubleMaxExclusive;
		#endif
	}

    }
    
    struct tm MaxExclusive::getMaxExclusiveAsStructTM()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MaxExclusive", "getMaxExclusiveAsStructTM", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			struct tm traceRet = (m_MaxExclusive.structTMMaxExclusive);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MaxExclusive", "getMaxExclusiveAsStructTM", this, 0,
					TRACETYPE_DATA, sizeof(struct tm), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_MaxExclusive.structTMMaxExclusive;
		#endif
	}

    }
    

