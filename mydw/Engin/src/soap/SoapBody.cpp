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
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 *
 */

/* SoapBody.cpp: implementation of the SoapBody class. */

#include "SoapBody.h"

#include "SoapSerializer.h"

#include <axis/GDefine.hpp>

#include "Attribute.h"

//#include "../common/AxisTrace.h"

extern SoapEnvVersionsStruct gs_SoapEnvVersionsStruct[VERSION_LAST];

SoapBody::SoapBody()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapBody", "SoapBody", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    m_pSoapMethod= NULL;
    m_pSoapFault= NULL;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapBody", "SoapBody", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

SoapBody::~SoapBody()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapBody", "~SoapBody", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    if(m_pSoapMethod)
    {
        delete m_pSoapMethod;
    }
    if(m_pSoapFault)
    {
        delete m_pSoapFault;
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapBody", "~SoapBody", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

void SoapBody::setSoapMethod(SoapMethod* ptrSoapMethod)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapBody", "setSoapMethod", this, 1,
					TRACETYPE_POINTER, sizeof(SoapMethod), ((void*)&ptrSoapMethod));	  /* AUTOINSERTED TRACE */
	#endif

    m_pSoapMethod= ptrSoapMethod;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapBody", "setSoapMethod", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

void SoapBody::setSoapFault(SoapFault *pSoapFault)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapBody", "setSoapFault", this, 1,
					TRACETYPE_POINTER, sizeof(SoapFault), ((void*)&pSoapFault));	  /* AUTOINSERTED TRACE */
	#endif

    m_pSoapFault= pSoapFault;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapBody", "setSoapFault", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

int SoapBody::serialize(SoapSerializer& pSZ, SOAP_VERSION eSoapVersion)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapBody", "serialize", this, 2,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ),
					TRACETYPE_DATA, sizeof(SOAP_VERSION), ((void*)&eSoapVersion));	  /* AUTOINSERTED TRACE */
	#endif

    int iStatus= AXIS_SUCCESS;
    do
    {        
        pSZ.serialize("<", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix,
            ":", gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_BODY],
            NULL);
        iStatus= serializeAttributes(pSZ);
        if(iStatus==AXIS_FAIL)
        {
            break;
        }
        
        pSZ.serialize(">\r\n", NULL);
        if(NULL != m_pSoapFault) 
        {        
            iStatus= m_pSoapFault->serialize(pSZ, eSoapVersion);
            if(iStatus==AXIS_FAIL)
            {
                break;
            }
        }
        else if(NULL != m_pSoapMethod)
        {
            iStatus= m_pSoapMethod->serialize(pSZ);
            if(iStatus==AXIS_FAIL)
            {
                break;
            }
        } 
        else
        {
            m_pSoapFault = SoapFault::getSoapFault(SERVER_ENGINE_WEBSERVICE_FAILED);
            if(m_pSoapFault!=NULL) 
            {        
                iStatus= m_pSoapFault->serialize(pSZ, eSoapVersion);
                if(iStatus==AXIS_FAIL) 
                    break;
            }
        }
        
        pSZ.serialize("</", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix,
            ":", gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_BODY],
            ">\r\n", NULL);
    } while(0);
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (iStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapBody", "serialize", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return iStatus;
		#endif
	}

}

void SoapBody::addAttribute(Attribute *attr)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapBody", "addAttribute", this, 1,
					TRACETYPE_POINTER, sizeof(Attribute), ((void*)&attr));	  /* AUTOINSERTED TRACE */
	#endif

    m_attributes.push_back(attr);
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapBody", "addAttribute", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

int SoapBody::serializeAttributes(SoapSerializer& pSZ)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapBody", "serializeAttributes", this, 1,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ));	  /* AUTOINSERTED TRACE */
	#endif

    int iStatus= AXIS_SUCCESS;
    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();
    while(itCurrAttribute != m_attributes.end())
    {        
        iStatus= (*itCurrAttribute)->serialize(pSZ);
        if(iStatus==AXIS_FAIL)
        {
            break;
        }
        itCurrAttribute++;        
    }    
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (iStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapBody", "serializeAttributes", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return iStatus;
		#endif
	}

}

SoapMethod * SoapBody::getSoapMethod(){
	return this->m_pSoapMethod;
}

