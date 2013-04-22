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

#include "Enumeration.hpp"

    Enumeration::Enumeration():m_Enumeration(NULL), m_NumberOfValues(0)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Enumeration", "Enumeration", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        m_isSet = false;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Enumeration", "Enumeration", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    Enumeration::Enumeration(AxisChar** enumeration, int numberOfValues)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Enumeration", "Enumeration", this, 2,
					TRACETYPE_POINTER, sizeof(AxisChar*), ((void*)&enumeration),
					TRACETYPE_INT, 0, ((void*)&numberOfValues));	  /* AUTOINSERTED TRACE */
	#endif

        m_Enumeration = new AxisChar*[numberOfValues];
        memcpy(m_Enumeration, enumeration, (numberOfValues * sizeof(AxisChar*)));
        m_NumberOfValues = numberOfValues;
        m_isSet = true;
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Enumeration", "Enumeration", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    
    Enumeration::~Enumeration()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Enumeration", "~Enumeration", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

        if(m_Enumeration)
        {
            delete [] m_Enumeration;
            m_Enumeration = NULL;
        }
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Enumeration", "~Enumeration", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
    void Enumeration::validateEnumeration(const AxisChar* value) throw (AxisSoapException)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Enumeration", "validateEnumeration", this, 1,
					TRACETYPE_STRING, 0, ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

        for ( int count = 0 ; count < m_NumberOfValues ; count++)
        {
            if ( strcmp ( m_Enumeration[count], value ) == 0 )
            {
                	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Enumeration", "validateEnumeration", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}

            }
        }
        
        /*
         * If we got this far we didn't find a matching value
         * So throw an AxisSoapException
         */
        AxisString exceptionMessage =
        "Value to be serialized does not match any of the values specified by Enmeration for this type.  MinInclusive = ";
        for ( int element = 0 ; element < m_NumberOfValues ; element++)
        {
            exceptionMessage += m_Enumeration[element];
            exceptionMessage += ", ";
        }
        exceptionMessage += "Value = ";
        exceptionMessage += value;
        exceptionMessage += ".";
        
        throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
            const_cast<AxisChar*>(exceptionMessage.c_str()));
    	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Enumeration", "validateEnumeration", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

