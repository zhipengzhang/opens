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

#include "FractionDigits.hpp"

    FractionDigits::FractionDigits():m_FractionDigits(0)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("FractionDigits", "FractionDigits", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        m_isSet = false;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("FractionDigits", "FractionDigits", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    FractionDigits::FractionDigits(int fractionDigits)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("FractionDigits", "FractionDigits", this, 1,
					TRACETYPE_INT, 0, ((void*)&fractionDigits));	  /* AUTOINSERTED TRACE */
	#endif

        m_FractionDigits = fractionDigits;
        m_isSet = true;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("FractionDigits", "FractionDigits", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    int FractionDigits::getFractionDigits()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("FractionDigits", "getFractionDigits", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (m_FractionDigits);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("FractionDigits", "getFractionDigits", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_FractionDigits;
		#endif
	}

    }


