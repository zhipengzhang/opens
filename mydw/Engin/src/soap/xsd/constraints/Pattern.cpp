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

#include "Pattern.hpp"

    Pattern::Pattern():m_Pattern(NULL)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Pattern", "Pattern", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        m_isSet = false;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Pattern", "Pattern", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    Pattern::Pattern(AxisChar* pattern)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Pattern", "Pattern", this, 1,
					TRACETYPE_STRING, 0, ((void*)&pattern));	  /* AUTOINSERTED TRACE */
	#endif

        if(m_Pattern)
        {
            delete [] m_Pattern;
            m_Pattern = NULL;
        }
        m_Pattern = pattern;
        m_isSet = true;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Pattern", "Pattern", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    
    Pattern::~Pattern()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Pattern", "~Pattern", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        if(m_Pattern)
        {
            delete [] m_Pattern;
            m_Pattern = NULL;
        }
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Pattern", "~Pattern", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    void Pattern::validatePattern(const AxisChar* value) throw (AxisSoapException)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Pattern", "validatePattern", this, 1,
					TRACETYPE_STRING, 0, ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

     /*
      * Currently has no effect.
      * Needs to validate the given string matches the regular expression
      * provided to the constructor.
      */
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Pattern", "validatePattern", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}


