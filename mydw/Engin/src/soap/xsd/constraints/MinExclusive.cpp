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

#include "MinExclusive.hpp"


    MinExclusive::MinExclusive(LONGLONG minExclusive)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MinExclusive", "MinExclusive", this, 1,
					TRACETYPE_DATA, sizeof(LONGLONG), ((void*)&minExclusive));	  /* AUTOINSERTED TRACE */
	#endif

        m_MinExclusive.longlongMinExclusive = minExclusive;
        m_isSet = true;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MinExclusive", "MinExclusive", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    MinExclusive::MinExclusive(unsigned LONGLONG minExclusive)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MinExclusive", "MinExclusive", this, 1,
					TRACETYPE_DATA, sizeof(unsigned LONGLONG), ((void*)&minExclusive));	  /* AUTOINSERTED TRACE */
	#endif

        m_MinExclusive.unsignedLongLongMinExclusive = minExclusive;
        m_isSet = true;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MinExclusive", "MinExclusive", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    MinExclusive::MinExclusive(double minExclusive)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MinExclusive", "MinExclusive", this, 1,
					TRACETYPE_DOUBLE, 0, ((void*)&minExclusive));	  /* AUTOINSERTED TRACE */
	#endif

        m_MinExclusive.doubleMinExclusive = minExclusive;
        m_isSet = true;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MinExclusive", "MinExclusive", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    
    MinExclusive::MinExclusive(struct tm minExclusive)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MinExclusive", "MinExclusive", this, 1,
					TRACETYPE_DATA, sizeof(struct tm), ((void*)&minExclusive));	  /* AUTOINSERTED TRACE */
	#endif

        m_MinExclusive.structTMMinExclusive = minExclusive;
        m_isSet = true;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MinExclusive", "MinExclusive", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    MinExclusive::MinExclusive()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MinExclusive", "MinExclusive", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        m_isSet = false;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MinExclusive", "MinExclusive", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    
    LONGLONG MinExclusive::getMinExclusiveAsLONGLONG()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MinExclusive", "getMinExclusiveAsLONGLONG", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			LONGLONG traceRet = (m_MinExclusive.longlongMinExclusive);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MinExclusive", "getMinExclusiveAsLONGLONG", this, 0,
					TRACETYPE_DATA, sizeof(LONGLONG), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_MinExclusive.longlongMinExclusive;
		#endif
	}

    }
    unsigned LONGLONG MinExclusive::getMinExclusiveAsUnsignedLONGLONG()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MinExclusive", "getMinExclusiveAsUnsignedLONGLONG", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			unsigned LONGLONG traceRet = (m_MinExclusive.unsignedLongLongMinExclusive);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MinExclusive", "getMinExclusiveAsUnsignedLONGLONG", this, 0,
					TRACETYPE_DATA, sizeof(unsigned LONGLONG), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_MinExclusive.unsignedLongLongMinExclusive;
		#endif
	}

    }
    
    double MinExclusive::getMinExclusiveAsDouble()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MinExclusive", "getMinExclusiveAsDouble", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			double traceRet = (m_MinExclusive.doubleMinExclusive);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MinExclusive", "getMinExclusiveAsDouble", this, 0,
					TRACETYPE_DOUBLE, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_MinExclusive.doubleMinExclusive;
		#endif
	}

    }
    
    struct tm MinExclusive::getMinExclusiveAsStructTM()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MinExclusive", "getMinExclusiveAsStructTM", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			struct tm traceRet = (m_MinExclusive.structTMMinExclusive);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MinExclusive", "getMinExclusiveAsStructTM", this, 0,
					TRACETYPE_DATA, sizeof(struct tm), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_MinExclusive.structTMMinExclusive;
		#endif
	}

    }


