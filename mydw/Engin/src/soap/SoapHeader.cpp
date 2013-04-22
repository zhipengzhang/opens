#ifdef ENABLE_AXISTRACE
/* TRACE ADDED BY THE TRACE INSTRUMENTOR TOOL */
#include "../common/AxisTrace.h"
#endif
/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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
 * @author Roshan Weerasuriya (roshanw@jkcsworld.com, roshan@opensource.lk)
 */

/*
 * Revision 1.1 2004/07/01 roshan
 * Added code to the following methods to deal with NULL values.
 *  addNamespaceDecl(Attribute *pAttribute)
 *  addAttribute(Attribute *pAttribute)
 *  addHeaderBlock(HeaderBlock* pHeaderBlock)
 */

#ifdef WIN32

#pragma warning (disable : 4786)

#endif

#include "SoapHeader.h"

#include "SoapSerializer.h"

#include <axis/GDefine.hpp>

#include "Attribute.h"

#include "HeaderBlock.h"

extern SoapEnvVersionsStruct gs_SoapEnvVersionsStruct[VERSION_LAST];

SoapHeader::SoapHeader()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapHeader", "SoapHeader", this, 0);	  /* AUTOINSERTED TRACE */
	#endif
	
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapHeader", "SoapHeader", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

SoapHeader::~SoapHeader()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapHeader", "~SoapHeader", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    // Header blocks are not deleted here any more. Its the responsibility of
    // either a handler or stub etc to delete any header block created by them
    // Here we will just clear the list of header block pointers
    m_headerBlocks.clear();
    // deletion of attributes 
    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();
    while(itCurrAttribute != m_attributes.end())
    {        
        delete *itCurrAttribute;
        itCurrAttribute++;
    }
    m_attributes.clear();
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapHeader", "~SoapHeader", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

void SoapHeader::addHeaderBlock(IHeaderBlock* pHeaderBlock)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapHeader", "addHeaderBlock", this, 1,
					TRACETYPE_POINTER, sizeof(IHeaderBlock), ((void*)&pHeaderBlock));	  /* AUTOINSERTED TRACE */
	#endif

    if (pHeaderBlock)
    {
        m_headerBlocks.push_back(pHeaderBlock);
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapHeader", "addHeaderBlock", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

int SoapHeader::serialize(SoapSerializer& pSZ, SOAP_VERSION eSoapVersion)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapHeader", "serialize", this, 2,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ),
					TRACETYPE_DATA, sizeof(SOAP_VERSION), ((void*)&eSoapVersion));	  /* AUTOINSERTED TRACE */
	#endif
    
    int iStatus= AXIS_SUCCESS;
    do
    {
		if (0 == m_headerBlocks.size()) break;
        
        pSZ.serialize("<", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix,
            ":", gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_HEADER],
            NULL);
        iStatus= serializeNamespaceDecl(pSZ);
        iStatus= serializeAttributes(pSZ);
        if(iStatus==AXIS_FAIL)
        {
            break;
        }
        
        pSZ.serialize(">", NULL);
        list<IHeaderBlock*>::iterator itCurrHeaderBlock= m_headerBlocks.begin();
        while(itCurrHeaderBlock != m_headerBlocks.end())
        {
            iStatus= ((HeaderBlock*)(*itCurrHeaderBlock))->serialize(pSZ);
            if(iStatus==AXIS_FAIL)
            {
                break;
            }
            itCurrHeaderBlock++;            
        }
        if(iStatus==AXIS_FAIL)
        {
            break;
        }
        
        pSZ.serialize("</", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix,
            ":", gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_HEADER],
            ">\n", NULL);
        
    } while(0);
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (iStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapHeader", "serialize", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return iStatus;
		#endif
	}

}

int SoapHeader::addAttribute(Attribute *pAttribute)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapHeader", "addAttribute", this, 1,
					TRACETYPE_POINTER, sizeof(Attribute), ((void*)&pAttribute));	  /* AUTOINSERTED TRACE */
	#endif

    if (pAttribute)
    {
        m_attributes.push_back(pAttribute);
        	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapHeader", "addAttribute", this, 1,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

    }
    else
    {
        	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapHeader", "addAttribute", this, 2,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}

    }
}

int SoapHeader::serializeAttributes(SoapSerializer& pSZ)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapHeader", "serializeAttributes", this, 1,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ));	  /* AUTOINSERTED TRACE */
	#endif

    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();
    while(itCurrAttribute != m_attributes.end())
    {
        (*itCurrAttribute)->serialize(pSZ);
        itCurrAttribute++;        
    }    
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapHeader", "serializeAttributes", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}
    
}

int SoapHeader::addNamespaceDecl(Attribute *pAttribute)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapHeader", "addNamespaceDecl", this, 1,
					TRACETYPE_POINTER, sizeof(Attribute), ((void*)&pAttribute));	  /* AUTOINSERTED TRACE */
	#endif

    if (pAttribute)
    {
        m_namespaceDecls.push_back(pAttribute);
        	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapHeader", "addNamespaceDecl", this, 1,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

    }
    else
    {
        	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapHeader", "addNamespaceDecl", this, 2,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}

    }
}

int SoapHeader::serializeNamespaceDecl(SoapSerializer& pSZ)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapHeader", "serializeNamespaceDecl", this, 1,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ));	  /* AUTOINSERTED TRACE */
	#endif

    list<Attribute*>::iterator itCurrNamespaceDecl= m_namespaceDecls.begin();
    while(itCurrNamespaceDecl != m_namespaceDecls.end())
    {
        (*itCurrNamespaceDecl)->serialize(pSZ);
        itCurrNamespaceDecl++;        
    }    
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapHeader", "serializeNamespaceDecl", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

IHeaderBlock* SoapHeader::getHeaderBlock(bool bRemoveOrNot)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapHeader", "getHeaderBlock", this, 1,
					TRACETYPE_BOOL, 0, ((void*)&bRemoveOrNot));	  /* AUTOINSERTED TRACE */
	#endif

    IHeaderBlock* tmpHeaderBlock = NULL;
    list<IHeaderBlock*>::iterator itCurrHeaderBlock= m_headerBlocks.begin();
    if(itCurrHeaderBlock != m_headerBlocks.end())
    {
        tmpHeaderBlock = (*itCurrHeaderBlock);
		if (bRemoveOrNot == true) {
			m_headerBlocks.pop_front();
		}
    }
    	{
		#ifdef ENABLE_AXISTRACE
			IHeaderBlock* traceRet = (tmpHeaderBlock);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapHeader", "getHeaderBlock", this, 0,
					TRACETYPE_POINTER, sizeof(IHeaderBlock), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return tmpHeaderBlock;
		#endif
	}

}

int SoapHeader::setPrefix(const char* pcPrefix)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapHeader", "setPrefix", this, 1,
					TRACETYPE_STRING, 0, ((void*)&pcPrefix));	  /* AUTOINSERTED TRACE */
	#endif

    m_pcPrefix = pcPrefix;
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapHeader", "setPrefix", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

IHeaderBlock* SoapHeader::getHeaderBlock(const AxisChar *pName,
                                         const AxisChar *pNamespace, 
										 bool bRemoveOrNot)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapHeader", "getHeaderBlock", this, 3,
					TRACETYPE_STRING, 0, ((void*)&pName),
					TRACETYPE_STRING, 0, ((void*)&pNamespace),
					TRACETYPE_BOOL, 0, ((void*)&bRemoveOrNot));	  /* AUTOINSERTED TRACE */
	#endif

    HeaderBlock* tmpHeaderBlock = NULL;
    list<IHeaderBlock*>::iterator itCurrHeaderBlock= m_headerBlocks.begin();
    bool blnFoundStatus = false;
    while (itCurrHeaderBlock != m_headerBlocks.end())
    {
        tmpHeaderBlock = (HeaderBlock*)(*itCurrHeaderBlock);
        if ((strcmp(((tmpHeaderBlock)->m_localname).c_str(), pName) == 0) && 
                (strcmp(((tmpHeaderBlock)->m_uri).c_str(), pNamespace) == 0))
        {
            blnFoundStatus = true;
			if (bRemoveOrNot == true) {
				m_headerBlocks.remove(tmpHeaderBlock);
			}
            break;
        }
        else
        {
            itCurrHeaderBlock++;
        }
    }
    if (blnFoundStatus == true)
    {
        	{
		#ifdef ENABLE_AXISTRACE
			IHeaderBlock* traceRet = (tmpHeaderBlock);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapHeader", "getHeaderBlock", this, 1,
					TRACETYPE_POINTER, sizeof(IHeaderBlock), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return tmpHeaderBlock;
		#endif
	}

    }
    else
    {
        	{
		#ifdef ENABLE_AXISTRACE
			IHeaderBlock* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapHeader", "getHeaderBlock", this, 2,
					TRACETYPE_POINTER, sizeof(IHeaderBlock), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

    }
}
 
IHeaderBlock* SoapHeader::getFirstHeaderBlock() 
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapHeader", "getFirstHeaderBlock", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

	m_itHeaderBlocks = m_headerBlocks.begin();
	IHeaderBlock* tmpIHeaderBlock=NULL;
	if (m_itHeaderBlocks != m_headerBlocks.end())
		tmpIHeaderBlock = *m_itHeaderBlocks;
		{
		#ifdef ENABLE_AXISTRACE
			IHeaderBlock* traceRet = (tmpIHeaderBlock);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapHeader", "getFirstHeaderBlock", this, 0,
					TRACETYPE_POINTER, sizeof(IHeaderBlock), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return tmpIHeaderBlock;
		#endif
	}

}

IHeaderBlock* SoapHeader::getNextHeaderBlock() 
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapHeader", "getNextHeaderBlock", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

	m_itHeaderBlocks++;
	IHeaderBlock* tmpIHeaderBlock=NULL;
	if (m_itHeaderBlocks != m_headerBlocks.end())
		tmpIHeaderBlock = *m_itHeaderBlocks;
		{
		#ifdef ENABLE_AXISTRACE
			IHeaderBlock* traceRet = (tmpIHeaderBlock);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapHeader", "getNextHeaderBlock", this, 0,
					TRACETYPE_POINTER, sizeof(IHeaderBlock), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return tmpIHeaderBlock;
		#endif
	}

}

IHeaderBlock* SoapHeader::getCurrentHeaderBlock()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapHeader", "getCurrentHeaderBlock", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

	IHeaderBlock* tmpIHeaderBlock=NULL;
	if (m_itHeaderBlocks != m_headerBlocks.end())
		tmpIHeaderBlock = *m_itHeaderBlocks;
		{
		#ifdef ENABLE_AXISTRACE
			IHeaderBlock* traceRet = (tmpIHeaderBlock);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapHeader", "getCurrentHeaderBlock", this, 0,
					TRACETYPE_POINTER, sizeof(IHeaderBlock), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return tmpIHeaderBlock;
		#endif
	}

}

int SoapHeader::deleteHeaderBlock(const AxisChar *pName,
                                         const AxisChar *pNamespace)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapHeader", "deleteHeaderBlock", this, 2,
					TRACETYPE_STRING, 0, ((void*)&pName),
					TRACETYPE_STRING, 0, ((void*)&pNamespace));	  /* AUTOINSERTED TRACE */
	#endif

    int iStatus = AXIS_SUCCESS;
    HeaderBlock* tmpHeaderBlock = NULL;
    list<IHeaderBlock*>::iterator itCurrHeaderBlock= m_headerBlocks.begin();
    
    while (itCurrHeaderBlock != m_headerBlocks.end())
    {
        tmpHeaderBlock = (HeaderBlock*)(*itCurrHeaderBlock);
        if ((strcmp(((tmpHeaderBlock)->m_localname).c_str(), pName) == 0) && 
                (strcmp(((tmpHeaderBlock)->m_uri).c_str(), pNamespace) == 0))
        {
            m_headerBlocks.remove(tmpHeaderBlock);            
            break; 
        }
        else
        {
            itCurrHeaderBlock++;
        }
    
    }
    if (m_headerBlocks.empty())
    {
        iStatus = AXIS_NO_REMAINING_SOAP_HEADERS;                     
    }
    
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (iStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapHeader", "deleteHeaderBlock", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return iStatus;
		#endif
	}

}

void SoapHeader::clear()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapHeader", "clear", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    // Header blocks are not deleted here. Its the responsibility of
    // either a handler or stub etc to delete any header block created by them
    // Here we will just clear the list of header block pointers
    m_headerBlocks.clear();
    // deletion of attributes 
    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();
    while(itCurrAttribute != m_attributes.end())
    {
        delete *itCurrAttribute;
        itCurrAttribute++;
    }
    m_attributes.clear();
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapHeader", "clear", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}
