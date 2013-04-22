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

#include "MinInclusive.hpp"

    MinInclusive::MinInclusive(LONGLONG minInclusive)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MinInclusive", "MinInclusive", this, 1,
					TRACETYPE_DATA, sizeof(LONGLONG), ((void*)&minInclusive));	  /* AUTOINSERTED TRACE */
	#endif

        m_MinInclusive.longlongMinInclusive = minInclusive;
        m_isSet = true;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MinInclusive", "MinInclusive", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    MinInclusive::MinInclusive(unsigned LONGLONG minInclusive)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MinInclusive", "MinInclusive", this, 1,
					TRACETYPE_DATA, sizeof(unsigned LONGLONG), ((void*)&minInclusive));	  /* AUTOINSERTED TRACE */
	#endif

        m_MinInclusive.unsignedLongLongMinInclusive = minInclusive;
        m_isSet = true;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MinInclusive", "MinInclusive", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    MinInclusive::MinInclusive(double minInclusive)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MinInclusive", "MinInclusive", this, 1,
					TRACETYPE_DOUBLE, 0, ((void*)&minInclusive));	  /* AUTOINSERTED TRACE */
	#endif

        m_MinInclusive.doubleMinInclusive = minInclusive;
        m_isSet = true;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MinInclusive", "MinInclusive", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    
    MinInclusive::MinInclusive(struct tm minInclusive)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MinInclusive", "MinInclusive", this, 1,
					TRACETYPE_DATA, sizeof(struct tm), ((void*)&minInclusive));	  /* AUTOINSERTED TRACE */
	#endif

        m_MinInclusive.structTMMinInclusive = minInclusive;
        m_isSet = true;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MinInclusive", "MinInclusive", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    MinInclusive::MinInclusive()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MinInclusive", "MinInclusive", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        m_isSet = false;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MinInclusive", "MinInclusive", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    
    LONGLONG MinInclusive::getMinInclusiveAsLONGLONG()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MinInclusive", "getMinInclusiveAsLONGLONG", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			LONGLONG traceRet = (m_MinInclusive.longlongMinInclusive);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MinInclusive", "getMinInclusiveAsLONGLONG", this, 0,
					TRACETYPE_DATA, sizeof(LONGLONG), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_MinInclusive.longlongMinInclusive;
		#endif
	}

    }
    unsigned LONGLONG MinInclusive::getMinInclusiveAsUnsignedLONGLONG()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MinInclusive", "getMinInclusiveAsUnsignedLONGLONG", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			unsigned LONGLONG traceRet = (m_MinInclusive.unsignedLongLongMinInclusive);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MinInclusive", "getMinInclusiveAsUnsignedLONGLONG", this, 0,
					TRACETYPE_DATA, sizeof(unsigned LONGLONG), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_MinInclusive.unsignedLongLongMinInclusive;
		#endif
	}

    }
    
    double MinInclusive::getMinInclusiveAsDouble()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MinInclusive", "getMinInclusiveAsDouble", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			double traceRet = (m_MinInclusive.doubleMinInclusive);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MinInclusive", "getMinInclusiveAsDouble", this, 0,
					TRACETYPE_DOUBLE, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_MinInclusive.doubleMinInclusive;
		#endif
	}

    }
    
    struct tm MinInclusive::getMinInclusiveAsStructTM()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("MinInclusive", "getMinInclusiveAsStructTM", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			struct tm traceRet = (m_MinInclusive.structTMMinInclusive);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("MinInclusive", "getMinInclusiveAsStructTM", this, 0,
					TRACETYPE_DATA, sizeof(struct tm), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_MinInclusive.structTMMinInclusive;
		#endif
	}

    }
   

