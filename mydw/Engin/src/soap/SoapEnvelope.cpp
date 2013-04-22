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
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk)
 * @author Samisa Abeysinghe (samisa.abeysinghe@gmail.com)
 */

#ifdef WIN32

#pragma warning (disable : 4786)

#endif

#include "SoapEnvelope.h"

#include <axis/GDefine.hpp>

#include "SoapSerializer.h"

#include <stdio.h>

//#include "../common/AxisTrace.h"

#include "Attribute.h"

extern SoapEnvVersionsStruct gs_SoapEnvVersionsStruct[VERSION_LAST];

SoapEnvelope::SoapEnvelope()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapEnvelope", "SoapEnvelope", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    m_pSoapHeader= NULL;
    m_pSoapBody= NULL;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapEnvelope", "SoapEnvelope", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

SoapEnvelope::~SoapEnvelope()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapEnvelope", "~SoapEnvelope", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    // deletion of attributes 
    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();
    while (itCurrAttribute != m_attributes.end())
    {        
        delete *itCurrAttribute;
        itCurrAttribute++;
    }
    m_attributes.clear();
    // deletion of namespace declerations 
    list<Attribute*>::iterator itCurrNamespaceDecls= m_namespaceDecls.begin();
    while (itCurrNamespaceDecls != m_namespaceDecls.end())
    {        
        delete *itCurrNamespaceDecls;
        itCurrNamespaceDecls++;
    }
    m_namespaceDecls.clear();
    // deletion of soap header 
    if (m_pSoapHeader)
    {
        delete m_pSoapHeader;
    }
    // deletion of soap body 
    if (m_pSoapBody)
    {
        delete m_pSoapBody;
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapEnvelope", "~SoapEnvelope", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

void SoapEnvelope::setSoapHeader(SoapHeader* soapHeader)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapEnvelope", "setSoapHeader", this, 1,
					TRACETYPE_POINTER, sizeof(SoapHeader), ((void*)&soapHeader));	  /* AUTOINSERTED TRACE */
	#endif

    m_pSoapHeader= soapHeader;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapEnvelope", "setSoapHeader", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

void SoapEnvelope::setSoapBody(SoapBody* soapBody)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapEnvelope", "setSoapBody", this, 1,
					TRACETYPE_POINTER, sizeof(SoapBody), ((void*)&soapBody));	  /* AUTOINSERTED TRACE */
	#endif

    m_pSoapBody= soapBody;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapEnvelope", "setSoapBody", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

int SoapEnvelope::serialize(SoapSerializer& pSZ, SOAP_VERSION eSoapVersion)
{    
    int iStatus= AXIS_SUCCESS;
    do
    {            
        pSZ.serialize("<", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix,
            ":", gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_ENVELOPE],
            NULL);    
        serializeStandardNamespaceDecl(pSZ);
        serializeNamespaceDecl(pSZ);
        serializeAttributes(pSZ);
        pSZ.serialize(">\r\n", NULL);
        if (m_pSoapHeader!=NULL)
        {
            iStatus= m_pSoapHeader->serialize(pSZ, eSoapVersion);
            if (iStatus == AXIS_FAIL)
            {
                break;
            }
        }
        if (m_pSoapBody!=NULL)
        {
            iStatus= m_pSoapBody->serialize(pSZ, eSoapVersion);
            if (iStatus == AXIS_FAIL)
            {
                break;
            }
        }
        else
        {
             iStatus = AXIS_FAIL;
        }
                
        pSZ.serialize("</", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix,
            ":", gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_ENVELOPE],">", NULL); 
    } while (0);
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (iStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapEnvelope", "serialize", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return iStatus;
		#endif
	}

}

int SoapEnvelope::addAttribute(Attribute *pAttribute)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapEnvelope", "addAttribute", this, 1,
					TRACETYPE_POINTER, sizeof(Attribute), ((void*)&pAttribute));	  /* AUTOINSERTED TRACE */
	#endif

    m_attributes.push_back(pAttribute);
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapEnvelope", "addAttribute", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

int SoapEnvelope::addNamespaceDecl(Attribute *pAttribute)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapEnvelope", "addNamespaceDecl", this, 1,
					TRACETYPE_POINTER, sizeof(Attribute), ((void*)&pAttribute));	  /* AUTOINSERTED TRACE */
	#endif

    m_namespaceDecls.push_back(pAttribute);
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapEnvelope", "addNamespaceDecl", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

int SoapEnvelope::serializeAttributes(SoapSerializer& pSZ)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapEnvelope", "serializeAttributes", this, 1,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ));	  /* AUTOINSERTED TRACE */
	#endif
    
    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();
    while (itCurrAttribute != m_attributes.end())
    {
        (*itCurrAttribute)->serialize(pSZ);
        itCurrAttribute++;        
    }    
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapEnvelope", "serializeAttributes", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}
    
}

int SoapEnvelope::serializeNamespaceDecl(SoapSerializer& pSZ)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapEnvelope", "serializeNamespaceDecl", this, 1,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ));	  /* AUTOINSERTED TRACE */
	#endif
    
    list<Attribute*>::iterator itCurrNamespaceDecl= m_namespaceDecls.begin();
    while (itCurrNamespaceDecl != m_namespaceDecls.end())
    {            
        (*itCurrNamespaceDecl)->serialize(pSZ);
        itCurrNamespaceDecl++;        
    }    
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapEnvelope", "serializeNamespaceDecl", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

int SoapEnvelope::setPrefix(const AxisChar* prefix)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapEnvelope", "setPrefix", this, 1,
					TRACETYPE_STRING, 0, ((void*)&prefix));	  /* AUTOINSERTED TRACE */
	#endif

    m_sPrefix= prefix;
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapEnvelope", "setPrefix", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

int SoapEnvelope::addStandardNamespaceDecl(const Attribute *pAttribute)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapEnvelope", "addStandardNamespaceDecl", this, 1,
					TRACETYPE_POINTER, sizeof(Attribute), ((void*)&pAttribute));	  /* AUTOINSERTED TRACE */
	#endif

    m_StandardNamespaceDecls.push_back(pAttribute);
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapEnvelope", "addStandardNamespaceDecl", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

void SoapEnvelope::clearStandardNamespaceDecl()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapEnvelope", "clearStandardNamespaceDecl", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    m_StandardNamespaceDecls.clear();
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapEnvelope", "clearStandardNamespaceDecl", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

int SoapEnvelope::serializeStandardNamespaceDecl(SoapSerializer &pSZ)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapEnvelope", "serializeStandardNamespaceDecl", this, 1,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ));	  /* AUTOINSERTED TRACE */
	#endif

    list<const Attribute*>::iterator itCurrNamespaceDecl= 
        m_StandardNamespaceDecls.begin();
    while (itCurrNamespaceDecl != m_StandardNamespaceDecls.end()) 
    {            
        (*itCurrNamespaceDecl)->serialize(pSZ);
        itCurrNamespaceDecl++;        
    }    
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapEnvelope", "serializeStandardNamespaceDecl", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

SoapBody *SoapEnvelope::getSoapBody(){
	return this->m_pSoapBody;
}

SoapMethod *SoapEnvelope::getSoapMethod(){
	return this->m_pSoapBody->getSoapMethod();
}

