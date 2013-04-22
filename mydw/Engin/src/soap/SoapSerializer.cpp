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
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 * @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 *
 */

/*
 * Revision 1.1  2005/01/09 Roshan
 * Added cleanup of SoapAttachments to the Destructor.
 */

#ifdef WIN32

#pragma warning (disable : 4786)

#endif

#include <axis/GDefine.hpp>

#include "SoapEnvelope.h"

#include "SoapSerializer.h"

#include "HeaderBlock.h"

#include "../socket/XmlRpcSocket.h"

//#include "../common/ArrayBean.h"

//#include "../common/BasicTypeSerializer.h"

//#include "SoapKeywordMapping.h"

//#include "SoapAttachmentReference.hpp"

#include "AxisSoapException.h"

#include <stdio.h>

#include <stdarg.h>

#include <IOSTREAM>

//#include "../common/AxisTrace.h"

//#include "../common/AxisConfig.h"

//extern AXIS_CPP_NAMESPACE_PREFIX AxisConfig* g_pConfig;

#define MIMEBOUNDARY	"------=MIME_BOUNDARY"

extern SoapEnvVersionsStruct gs_SoapEnvVersionsStruct[VERSION_LAST];

SoapSerializer::SoapSerializer()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "SoapSerializer", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    m_pSoapEnvelope = NULL;
    m_iSoapVersion = SOAP_VER_1_1;
    m_pOutputStream = NULL;
	m_pNamespace = NULL;
//llh	m_pContentIdSet = NULL;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "SoapSerializer", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

SoapSerializer::~SoapSerializer()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "~SoapSerializer", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    if( m_pSoapEnvelope)
	{
		delete m_pSoapEnvelope;
	}
	/* Cleaning the memory allocated to the SoapAttachments */       
//llh	map<AxisXMLString, ISoapAttachment*>::iterator itCurrAttach= m_SoapAttachments.begin();
//	while( itCurrAttach != m_SoapAttachments.end())
//    {        
//        delete( (SoapAttachment*)((*itCurrAttach).second));		
//        itCurrAttach++;
//    }
//	m_SoapAttachments.clear();
//	list<SoapAttachmentReference*>::iterator itAttRef= m_attachmentRefs.begin();
//	while(itAttRef != m_attachmentRefs.end())
//    {        
//        delete *itAttRef;
//        itAttRef++;
//    }
//	m_attachmentRefs.clear();

//llh	delete m_pOutputStream;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "~SoapSerializer", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

int SoapSerializer::setSoapEnvelope( SoapEnvelope * pSoapEnvelope)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "setSoapEnvelope", this, 1,
					TRACETYPE_POINTER, sizeof(SoapEnvelope), ((void*)&pSoapEnvelope));	  /* AUTOINSERTED TRACE */
	#endif

    m_pSoapEnvelope = pSoapEnvelope;
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "setSoapEnvelope", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

int SoapSerializer::setSoapHeader( SoapHeader * pSoapHeader)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "setSoapHeader", this, 1,
					TRACETYPE_POINTER, sizeof(SoapHeader), ((void*)&pSoapHeader));	  /* AUTOINSERTED TRACE */
	#endif

    int intStatus = AXIS_FAIL;
    if( m_pSoapEnvelope)
    {
        if( (m_pSoapEnvelope) && (m_pSoapEnvelope->m_pSoapHeader))
        {
            /* no need to create a SOAP Header, it already exists */
            intStatus = AXIS_OBJECT_ALREADY_EXISTS;
        }
        else
        {
            m_pSoapEnvelope->setSoapHeader( pSoapHeader);
            intStatus= AXIS_SUCCESS;
        }
    }
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (intStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "setSoapHeader", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return intStatus;
		#endif
	}

}

int SoapSerializer::setSoapBody( SoapBody * pSoapBody)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "setSoapBody", this, 1,
					TRACETYPE_POINTER, sizeof(SoapBody), ((void*)&pSoapBody));	  /* AUTOINSERTED TRACE */
	#endif

    int intStatus = AXIS_FAIL;
    if(m_pSoapEnvelope)
    {
        m_pSoapEnvelope->setSoapBody( pSoapBody);
        intStatus = AXIS_SUCCESS;
    }
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (intStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "setSoapBody", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return intStatus;
		#endif
	}

}

int SoapSerializer::setSoapMethod( SoapMethod *pSoapMethod)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "setSoapMethod", this, 1,
					TRACETYPE_POINTER, sizeof(SoapMethod), ((void*)&pSoapMethod));	  /* AUTOINSERTED TRACE */
	#endif

    int intStatus = AXIS_FAIL;
    if( m_pSoapEnvelope && (m_pSoapEnvelope->m_pSoapBody))
    {
		if( !(m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod))
		{
			m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod = pSoapMethod;
		}
			
		intStatus = AXIS_SUCCESS;
    }
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (intStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "setSoapMethod", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return intStatus;
		#endif
	}

}

//int SoapSerializer::addOutputBasicArrayParam( const Axis_Array * pArray, 
//                                              XSDTYPE nType,
//                                              const AxisChar * pName)
//{
//	#ifdef ENABLE_AXISTRACE
//		if (axiscpp::AxisTrace::isTraceOn())
//			axiscpp::AxisTrace::traceEntry("SoapSerializer", "addOutputBasicArrayParam", this, 3,
//					TRACETYPE_POINTER, sizeof(Axis_Array), ((void*)&pArray),
//					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&nType),
//					TRACETYPE_STRING, 0, ((void*)&pName));	  /* AUTOINSERTED TRACE */
//	#endif
//
//	int	iSuccess = AXIS_SUCCESS;
//    Axis_Array * pLocalArray = pArray->clone();
//    ArrayBean * pAb = makeArrayBean( nType, (void**) (pLocalArray->m_Array));
//    pAb->SetDimension(pLocalArray->m_Size);
//    /*
//     * We're now finished with the local array object, so it can be deleted
//     * However, we need to de-couple from the internal array, which is now owned
//     * by the ArrayBean.
//     */
//    pLocalArray->m_Array = NULL;
//    pLocalArray->m_Size = 0;
//    delete pLocalArray;
//    pLocalArray = NULL;
//    Param* pParam = new Param();
//    if( RPC_ENCODED == m_nStyle)
//    {
//        pAb->SetItemName("item");
//        pParam->setName(pName);
//    }
//    else
//    {
//        pAb->SetItemName(pName);
//        pParam->setName("array");        
//    }
//    pParam->m_Value.pArray = pAb;
//    pParam->m_Type = XSD_ARRAY;
//    if( m_pSoapEnvelope && (m_pSoapEnvelope->m_pSoapBody) && 
//        (m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod)) 
//    {
//        m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod->addOutputParam( pParam);
//    }
//    	{
//		#ifdef ENABLE_AXISTRACE
//			int traceRet = (iSuccess);
//			if (axiscpp::AxisTrace::isTraceOn())
//				axiscpp::AxisTrace::traceExit("SoapSerializer", "addOutputBasicArrayParam", this, 0,
//					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
//			return traceRet;
//		#else
//			return iSuccess;
//		#endif
//	}
//  // Can it only be successful?
//}

//int SoapSerializer::addOutputCmplxArrayParam( const Axis_Array * pArray, 
//                                              void * pSZFunct,
//											  void * pDelFunct,
//                                              void * pSizeFunct, 
//                                              const AxisChar * pName, 
//                                              const AxisChar * pNamespace)
//{
//	#ifdef ENABLE_AXISTRACE
//		if (axiscpp::AxisTrace::isTraceOn())
//			axiscpp::AxisTrace::traceEntry("SoapSerializer", "addOutputCmplxArrayParam", this, 6,
//					TRACETYPE_POINTER, sizeof(Axis_Array), ((void*)&pArray),
//					TRACETYPE_POINTER, 1, ((void*)&pSZFunct),
//					TRACETYPE_POINTER, 1, ((void*)&pDelFunct),
//					TRACETYPE_POINTER, 1, ((void*)&pSizeFunct),
//					TRACETYPE_STRING, 0, ((void*)&pName),
//					TRACETYPE_STRING, 0, ((void*)&pNamespace));	  /* AUTOINSERTED TRACE */
//	#endif
//
//	int	iSuccess = AXIS_SUCCESS;
//    Axis_Array * pLocalArray = pArray->clone();
//    ArrayBean* pAb = makeArrayBean( pLocalArray->m_Array, pSZFunct,
//									 pDelFunct,
//									 pSizeFunct);
//    pAb->SetDimension( pLocalArray->m_Size);
//    
//    /*
//     * We're now finished with the local array object, so it can be deleted
//     * However, we need to de-couple from the internal array, which is now owned
//     * by the ArrayBean.
//     */
//    pLocalArray->m_Array = NULL;
//    pLocalArray->m_Size = 0;
//    delete pLocalArray;
//    pLocalArray = NULL;
//    Param * pParam = new Param();
//    if( RPC_ENCODED == m_nStyle)
//    {
//        pAb->SetItemName( "item");
//        pAb->SetTypeName( pName);
//        pAb->SetUri( pNamespace);
//        pParam->setName( pName);
//    }
//    else
//    {
//        pAb->SetItemName( pName);
//	    if( NULL != pNamespace)
//		{
//		    pParam->setURI( pNamespace);
//		}
//        pParam->setName( "array");        
//    }
//    pParam->m_Value.pArray = pAb;
//    pParam->m_Type = XSD_ARRAY;
//    if( m_pSoapEnvelope &&
//		(m_pSoapEnvelope->m_pSoapBody) &&
//		(m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod)) 
//    {
//        m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod->addOutputParam( pParam);
//    }
//    pParam->setName( pName);
//    	{
//		#ifdef ENABLE_AXISTRACE
//			int traceRet = (iSuccess);
//			if (axiscpp::AxisTrace::isTraceOn())
//				axiscpp::AxisTrace::traceExit("SoapSerializer", "addOutputCmplxArrayParam", this, 0,
//					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
//			return traceRet;
//		#else
//			return iSuccess;
//		#endif
//	}
//  // Can it only be successful?
//}

int SoapSerializer::addOutputCmplxParam( void * pObject,
										 void * pSZFunct, 
                                         void * pDelFunct,
										 const AxisChar * pName,
                                         const AxisChar * pNamespace)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "addOutputCmplxParam", this, 5,
					TRACETYPE_POINTER, 1, ((void*)&pObject),
					TRACETYPE_POINTER, 1, ((void*)&pSZFunct),
					TRACETYPE_POINTER, 1, ((void*)&pDelFunct),
					TRACETYPE_STRING, 0, ((void*)&pName),
					TRACETYPE_STRING, 0, ((void*)&pNamespace));	  /* AUTOINSERTED TRACE */
	#endif
 
	int	iSuccess = AXIS_SUCCESS;
    Param pParam;

	/*llh 07/05/21*/
	pParam.setPrefix(getNamespacePrefix(pNamespace));
	pParam.setURI(pNamespace);
	/*llh 07/05/21*/

    pParam.setName(pName);
	
    pParam.m_Value.pCplxObj = new ComplexObjectHandler;
    pParam.m_Value.pCplxObj->pObject = pObject;
    pParam.m_Value.pCplxObj->pSZFunct = (AXIS_SERIALIZE_FUNCT) pSZFunct;
    pParam.m_Value.pCplxObj->pDelFunct = (AXIS_OBJECT_DELETE_FUNCT) pDelFunct;
	if( m_pSoapEnvelope &&
		(m_pSoapEnvelope->m_pSoapBody) &&
		(m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod)) 
    {
        m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod->addOutputParam(pParam);
    }
    
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (iSuccess);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "addOutputCmplxParam", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return iSuccess;
		#endif
	}
  // Can it only be successful?
}

int SoapSerializer::addFaultDetail( void * pObject,
								    void * pSZFunct, 
                                    void * pDelFunct,
									const AxisChar * pName,
                                    const AxisChar * pNamespace)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "addFaultDetail", this, 5,
					TRACETYPE_POINTER, 1, ((void*)&pObject),
					TRACETYPE_POINTER, 1, ((void*)&pSZFunct),
					TRACETYPE_POINTER, 1, ((void*)&pDelFunct),
					TRACETYPE_STRING, 0, ((void*)&pName),
					TRACETYPE_STRING, 0, ((void*)&pNamespace));	  /* AUTOINSERTED TRACE */
	#endif
 
	int	iSuccess = AXIS_SUCCESS;
    Param * pParam = new Param();
    pParam->m_Value.pCplxObj = new ComplexObjectHandler;
    pParam->m_Value.pCplxObj->pObject = pObject;
    pParam->m_Value.pCplxObj->pSZFunct = (AXIS_SERIALIZE_FUNCT) pSZFunct;
    pParam->m_Value.pCplxObj->pDelFunct = (AXIS_OBJECT_DELETE_FUNCT) pDelFunct;
    if( m_pSoapEnvelope &&
		(m_pSoapEnvelope->m_pSoapBody) &&
		(m_pSoapEnvelope->m_pSoapBody->m_pSoapFault)) 
    {
        iSuccess = m_pSoapEnvelope->m_pSoapBody->m_pSoapFault->setFaultDetail(pParam);
    }
    pParam->setName( pName);
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (iSuccess);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "addFaultDetail", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return iSuccess;
		#endif
	}

}

int SoapSerializer::setSoapFault( SoapFault * pSoapFault)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "setSoapFault", this, 1,
					TRACETYPE_POINTER, sizeof(SoapFault), ((void*)&pSoapFault));	  /* AUTOINSERTED TRACE */
	#endif

    int intStatus = AXIS_FAIL;
    if( m_pSoapEnvelope && (m_pSoapEnvelope->m_pSoapBody))
    {
		if(m_pSoapEnvelope->m_pSoapBody->m_pSoapFault)
			delete m_pSoapEnvelope->m_pSoapBody->m_pSoapFault;
        m_pSoapEnvelope->m_pSoapBody->m_pSoapFault = pSoapFault;
        intStatus = AXIS_SUCCESS;
    }
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (intStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "setSoapFault", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return intStatus;
		#endif
	}

}

int SoapSerializer::setOutputStream( SoapTransport * pStream)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "setOutputStream", this, 1,
					TRACETYPE_POINTER, sizeof(SOAPTransport), ((void*)&pStream));	  /* AUTOINSERTED TRACE */
	#endif

    int	iStatus = AXIS_SUCCESS;
    m_pOutputStream = pStream;
    try
    {
	    if( m_pSoapEnvelope)
		{
//			if( checkAttachmentAvailability())
//			{
//				char *pszSOAPMimeHeaders = pStream->getIncomingSOAPMimeHeaders();
//				if (NULL != pszSOAPMimeHeaders) 
//				{	// Server code
//					string asSOAPMimeHeaders = pszSOAPMimeHeaders;
//					int		start			= asSOAPMimeHeaders.find( AXIS_CONTENT_TYPE);
//					int		startPosIdValue = asSOAPMimeHeaders.find( "<", start + strlen( AXIS_CONTENT_ID ":")) + 1;
//					int		endPosIdValue   = asSOAPMimeHeaders.find( ">", start + strlen( AXIS_CONTENT_TYPE));
//					int		length          = endPosIdValue - startPosIdValue ;	
//					string asStartID = asSOAPMimeHeaders.substr (startPosIdValue,length); 
//					string asContentType( "multipart/related; type=\"text/xml\"; start=\"<");
//					asContentType = asContentType + asStartID + ">\"";
//					asContentType = asContentType + ";  boundary=\"" MIMEBOUNDARY "\"";
//					pStream->setTransportProperty( CONTENT_TYPE, asContentType.c_str()); 
//					serialize( "\r\n" MIMEBOUNDARY "\r\n", NULL);
//					serialize( pStream->getIncomingSOAPMimeHeaders(), "\r\n\r\n", NULL);
//				}
//				else
//				{	// Client code
//					const char *id = m_pContentIdSet->generateId();
//					string ctype = "multipart/related; type=\"text/xml\"; boundary=\"";
//					ctype += MIMEBOUNDARY;
//					ctype += "\"; start=\"<";
//					ctype += id;
//					ctype += ">\"";
//					pStream->deleteTransportProperty(AXIS_CONTENT_TYPE); // Never want 2 Content-Type HTTP headers
//					pStream->setTransportProperty(AXIS_CONTENT_TYPE, ctype.c_str());
//					serialize("\r\n--" MIMEBOUNDARY "\r\n", NULL);
//                    serialize(AXIS_CONTENT_TYPE ": text/xml; charset=UTF-8\r\n", NULL);
//                    serialize(AXIS_CONTENT_TRANSFER_ENCODING ": binary\r\n", NULL);
//					string cid = AXIS_CONTENT_ID;
//					cid += ": <";
//					cid += id;
//					cid += ">\r\n\r\n";		// Extra \r\n terminates headers
//                    serialize(cid.c_str(), NULL);
//				}
//			}
			serialize( "<?xml version=\"1.0\"?>\r\n", NULL);
			if( (iStatus = m_pSoapEnvelope->serialize( *this, (SOAP_VERSION) m_iSoapVersion)) == AXIS_FAIL)
			{
				throw AxisSoapException( CLIENT_SOAP_MESSAGE_INCOMPLETE, "The SOAP serializer has detected errors in the header or envelope. Transmission has been aborted.");
			}
//			if( checkAttachmentAvailability())
//			{
//				serializeAttachments( *this);
//			}
		}
	}
	catch( AxisSoapException& e)
	{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceCatch("SoapSerializer", "setOutputStream", this, 1,
					TRACETYPE_AXISEXCEPTION, sizeof(AxisSoapException&), ((void*)&e));	  /* AUTOINSERTED TRACE */
	#endif

		e = e;
		throw;
	}
	catch( AxisException& e)
	{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceCatch("SoapSerializer", "setOutputStream", this, 2,
					TRACETYPE_AXISEXCEPTION, sizeof(AxisException&), ((void*)&e));	  /* AUTOINSERTED TRACE */
	#endif

		e = e;
		throw;
	}
	catch( ...)
	{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceCatch("SoapSerializer", "setOutputStream", this, 3 );	  /* AUTOINSERTED TRACE */
	#endif

		throw;
	}
		{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (iStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "setOutputStream", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return iStatus;
		#endif
	}

}

/*
 * Some client side transport layer may wait until the end of buffers is 
 * acknowladged. Use this function to do that.
 */

//void SoapSerializer::markEndOfStream()
//{
//	#ifdef ENABLE_AXISTRACE
//		if (axiscpp::AxisTrace::isTraceOn())
//			axiscpp::AxisTrace::traceEntry("SoapSerializer", "markEndOfStream", this, 0);	  /* AUTOINSERTED TRACE */
//	#endif
//
//    m_pOutputStream->flushOutput();
//	{
//		#ifdef ENABLE_AXISTRACE
//			if (axiscpp::AxisTrace::isTraceOn())
//				axiscpp::AxisTrace::traceExit("SoapSerializer", "markEndOfStream", this, 0);	  /* AUTOINSERTED TRACE */
//		#endif
//		return;
//	}
//}

/*
 * Initializing the members of the class. This is needed since
 * the same object instance of this class, may be used to server
 * several SOAP requests.
 */

int SoapSerializer::init()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "init", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    m_nStatus = AXIS_SUCCESS;
    if( m_pSoapEnvelope)
    {
        delete m_pSoapEnvelope;
        m_pSoapEnvelope= NULL;
    }
    /* Adding SoapEnvelop and SoapBody to Serializer */
    m_pSoapEnvelope = new SoapEnvelope();
	addNamespaceToEnvelope((AxisChar *)gs_SoapEnvVersionsStruct[m_iSoapVersion].pchNamespaceUri,(AxisChar *)gs_SoapEnvVersionsStruct[m_iSoapVersion].pchPrefix);
    m_pSoapEnvelope->setSoapBody( new SoapBody());
    
    m_nCounter=0;
    m_NsStack.clear();
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (m_nStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "init", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_nStatus;
		#endif
	}

}

//int SoapSerializer::setSoapVersion( SOAP_VERSION nSoapVersion)
//{
//	#ifdef ENABLE_AXISTRACE
//		if (axiscpp::AxisTrace::isTraceOn())
//			axiscpp::AxisTrace::traceEntry("SoapSerializer", "setSoapVersion", NULL, 1,
//					TRACETYPE_DATA, sizeof(SOAP_VERSION), ((void*)&nSoapVersion));	  /* AUTOINSERTED TRACE */
//	#endif
//
//    m_iSoapVersion = nSoapVersion;
//    m_pSoapEnvelope->clearStandardNamespaceDecl(); // Samisa : AXISCPP-368
//    /* here the default namespaces of the SoapEnvelop should be added and 
//     * intialized as well. 
//     */
//    m_pSoapEnvelope->addStandardNamespaceDecl( SoapKeywordMapping::map(nSoapVersion).pEnv);
//    m_pSoapEnvelope->addStandardNamespaceDecl( SoapKeywordMapping::map(nSoapVersion).pXsd);
//    m_pSoapEnvelope->addStandardNamespaceDecl( SoapKeywordMapping::map(nSoapVersion).pXsi);
//    /* Adding the standard SOAP namespace to the namespace stack */
//    m_NsStack[SoapKeywordMapping::map(nSoapVersion).pchNamespaceUri] = 
//        SoapKeywordMapping::map(nSoapVersion).pchPrefix;
//    	{
//		#ifdef ENABLE_AXISTRACE
//			int traceRet = (AXIS_SUCCESS);
//			if (axiscpp::AxisTrace::isTraceOn())
//				axiscpp::AxisTrace::traceExit("SoapSerializer", "setSoapVersion", NULL, 0,
//					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
//			return traceRet;
//		#else
//			return AXIS_SUCCESS;
//		#endif
//	}
//
//}

void SoapSerializer::removeNamespacePrefix( const AxisChar * pNamespace)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "removeNamespacePrefix", this, 1,
					TRACETYPE_STRING, 0, ((void*)&pNamespace));	  /* AUTOINSERTED TRACE */
	#endif

    if( m_NsStack.find( pNamespace) != m_NsStack.end())
    {
        m_NsStack.erase( pNamespace);
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "removeNamespacePrefix", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

const AxisChar * SoapSerializer::getNamespacePrefix( const AxisChar * pNamespace)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "getNamespacePrefix", this, 1,
					TRACETYPE_STRING, 0, ((void*)&pNamespace));	  /* AUTOINSERTED TRACE */
	#endif

    if( m_NsStack.find( pNamespace) == m_NsStack.end())
    {
        m_nCounter++;
        AxisSprintf(m_Buf, 8, "ns%d", m_nCounter);
        m_NsStack[pNamespace] = m_Buf;
    }
    	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (m_NsStack[pNamespace].c_str());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "getNamespacePrefix", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_NsStack[pNamespace].c_str();
		#endif
	}

}

const AxisChar * SoapSerializer::getNamespacePrefix( const AxisChar * pNamespace, 
                                                     bool & blnIsNewPrefix)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "getNamespacePrefix", this, 2,
					TRACETYPE_STRING, 0, ((void*)&pNamespace),
					TRACETYPE_BOOL, 0, ((void*)&blnIsNewPrefix));	  /* AUTOINSERTED TRACE */
	#endif

    if( m_NsStack.find( pNamespace) == m_NsStack.end())
    {
        m_nCounter++;
        AxisSprintf(m_Buf, 8, "ns%d", m_nCounter);
        m_NsStack[pNamespace] = m_Buf;
        blnIsNewPrefix = true;
    }
    	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (m_NsStack[pNamespace].c_str());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "getNamespacePrefix", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_NsStack[pNamespace].c_str();
		#endif
	}

}

//IWrapperSoapSerializer  llh
SoapSerializer& SoapSerializer::operator << (const AxisChar * cSerialized)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "operator<<", this, 1,
					TRACETYPE_STRING, 0, ((void*)&cSerialized));	  /* AUTOINSERTED TRACE */
	#endif

    if( AXIS_SUCCESS != m_nStatus) 
    {
        // some thing has gone wrong. So do nothing 
        	{
		#ifdef ENABLE_AXISTRACE
			IWrapperSoapSerializer& traceRet = (*this);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "operator<<", this, 1,
					TRACETYPE_DATA, sizeof(IWrapperSoapSerializer&), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return *this;
		#endif
	}

    }
    try
    {
      // send everything to transport layer, it should handle bufferization itself 
		m_pOutputStream->sendBytes( cSerialized);//llh
//		std::cout<<cSerialized;
    }
    catch(AxisSoapException& e)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceCatch("SoapSerializer", "operator<<", this, 1,
					TRACETYPE_AXISEXCEPTION, sizeof(AxisSoapException&), ((void*)&e));	  /* AUTOINSERTED TRACE */
	#endif

        e = e;
        throw;
    }
    catch(AxisException& e)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceCatch("SoapSerializer", "operator<<", this, 2,
					TRACETYPE_AXISEXCEPTION, sizeof(AxisException&), ((void*)&e));	  /* AUTOINSERTED TRACE */
	#endif

        e = e;
        throw;
    }
    catch(...)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceCatch("SoapSerializer", "operator<<", this, 3 );	  /* AUTOINSERTED TRACE */
	#endif

        throw;
    }
    	{
		#ifdef ENABLE_AXISTRACE
			IWrapperSoapSerializer& traceRet = (*this);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "operator<<", this, 2,
					TRACETYPE_DATA, sizeof(IWrapperSoapSerializer&), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return *this;
		#endif
	}

}

int SoapSerializer::createSoapMethod( const AxisChar * sLocalName, 
                                      const AxisChar * sURI
									  ,bool isResponse
									  )
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "createSoapMethod", this, 2,
					TRACETYPE_STRING, 0, ((void*)&sLocalName),
					TRACETYPE_STRING, 0, ((void*)&sURI));	  /* AUTOINSERTED TRACE */
	#endif

    SoapMethod * pMethod = NULL;
    if( !(m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod))
    {
        pMethod = new SoapMethod();
		if(isResponse)
			pMethod->setReturn(true);
		else pMethod->setReturn(false);
        setSoapMethod( pMethod);
    }
    else
    {
        pMethod = m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod;
        pMethod->clearOutParams();
    }
    pMethod->setLocalName( sLocalName);
    pMethod->setPrefix( getNamespacePrefix( sURI));
    pMethod->setURI( sURI);
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "createSoapMethod", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}
  // Can it only be successful?
}

//int SoapSerializer::createSoapFault( const AxisChar * sLocalName, 
//                                     const AxisChar * sURI,
//								     const AxisChar * sFaultCode,
//								     const AxisChar * sFaultString)
//{
//	#ifdef ENABLE_AXISTRACE
//		if (axiscpp::AxisTrace::isTraceOn())
//			axiscpp::AxisTrace::traceEntry("SoapSerializer", "createSoapFault", this, 4,
//					TRACETYPE_STRING, 0, ((void*)&sLocalName),
//					TRACETYPE_STRING, 0, ((void*)&sURI),
//					TRACETYPE_STRING, 0, ((void*)&sFaultCode),
//					TRACETYPE_STRING, 0, ((void*)&sFaultString));	  /* AUTOINSERTED TRACE */
//	#endif
//
//    SoapFault * pSoapFault = new SoapFault();
//    setSoapFault( pSoapFault);
//    pSoapFault->setLocalName( sLocalName);
//    pSoapFault->setPrefix( getNamespacePrefix( sURI));
//    pSoapFault->setURI( sURI);
//    pSoapFault->setFaultcode( sFaultCode);
//    pSoapFault->setFaultstring( sFaultString);
//    char* pcNodeName = g_pConfig->getAxisConfProperty( AXCONF_NODENAME);
//    char* pcPort = g_pConfig->getAxisConfProperty(AXCONF_LISTENPORT);
//    string strUrl = pcNodeName;
//    strUrl += ":";
//    strUrl += string( pcPort);
//    pSoapFault->setFaultactor( strUrl.c_str());
//    
//    	{
//		#ifdef ENABLE_AXISTRACE
//			int traceRet = (AXIS_SUCCESS);
//			if (axiscpp::AxisTrace::isTraceOn())
//				axiscpp::AxisTrace::traceExit("SoapSerializer", "createSoapFault", this, 0,
//					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
//			return traceRet;
//		#else
//			return AXIS_SUCCESS;
//		#endif
//	}
//  // Can it only be successful?
//}

/*
 * Used to create an ArrayBean when the return type of a method is an array
 * of basic types
 */

//ArrayBean * SoapSerializer::makeArrayBean( XSDTYPE nType, void ** pArray)
//{
//	#ifdef ENABLE_AXISTRACE
//		if (axiscpp::AxisTrace::isTraceOn())
//			axiscpp::AxisTrace::traceEntry("SoapSerializer", "makeArrayBean", this, 2,
//					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&nType),
//					TRACETYPE_POINTER, sizeof(void*), ((void*)&pArray));	  /* AUTOINSERTED TRACE */
//	#endif
//
//    ArrayBean* pAb = new ArrayBean();
//    pAb->m_type = nType;
//    pAb->m_value.sta = pArray;
//    	{
//		#ifdef ENABLE_AXISTRACE
//			ArrayBean* traceRet = (pAb);
//			if (axiscpp::AxisTrace::isTraceOn())
//				axiscpp::AxisTrace::traceExit("SoapSerializer", "makeArrayBean", this, 0,
//					TRACETYPE_POINTER, sizeof(ArrayBean), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
//			return traceRet;
//		#else
//			return pAb;
//		#endif
//	}
//
//}

/*
 * Used to create an ArrayBean when the return type of a method is an array
 * of complex types
 */

//ArrayBean * SoapSerializer::makeArrayBean(void ** pObject,
//										   void * pSZFunct, 
//                                           void * pDelFunct,
//										   void * pSizeFunct)
//{
//	#ifdef ENABLE_AXISTRACE
//		if (axiscpp::AxisTrace::isTraceOn())
//			axiscpp::AxisTrace::traceEntry("SoapSerializer", "makeArrayBean", this, 4,
//					TRACETYPE_POINTER, sizeof(void*), ((void*)&pObject),
//					TRACETYPE_POINTER, 1, ((void*)&pSZFunct),
//					TRACETYPE_POINTER, 1, ((void*)&pDelFunct),
//					TRACETYPE_POINTER, 1, ((void*)&pSizeFunct));	  /* AUTOINSERTED TRACE */
//	#endif
//
//    ArrayBean* pAb = new ArrayBean();
//    pAb->m_type = USER_TYPE;
//    pAb->m_value.cta = new ComplexObjectHandler;
//    pAb->m_value.cta->pSZFunct = (AXIS_SERIALIZE_FUNCT) pSZFunct;
//    pAb->m_value.cta->pDelFunct = (AXIS_OBJECT_DELETE_FUNCT) pDelFunct;
//    pAb->m_value.cta->pSizeFunct = (AXIS_OBJECT_SIZE_FUNCT) pSizeFunct;
//    pAb->m_value.cta->pObject = pObject;
//    	{
//		#ifdef ENABLE_AXISTRACE
//			ArrayBean* traceRet = (pAb);
//			if (axiscpp::AxisTrace::isTraceOn())
//				axiscpp::AxisTrace::traceExit("SoapSerializer", "makeArrayBean", this, 0,
//					TRACETYPE_POINTER, sizeof(ArrayBean), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
//			return traceRet;
//		#else
//			return pAb;
//		#endif
//	}
//
//}

IHeaderBlock * SoapSerializer::createHeaderBlock()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "createHeaderBlock", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    HeaderBlock * pHeaderBlock= new HeaderBlock();
    setHeaderBlock( pHeaderBlock);
    	{
		#ifdef ENABLE_AXISTRACE
			IHeaderBlock* traceRet = (pHeaderBlock);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "createHeaderBlock", this, 0,
					TRACETYPE_POINTER, sizeof(IHeaderBlock), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return pHeaderBlock;
		#endif
	}

}

int SoapSerializer::setHeaderBlock( HeaderBlock * pHeaderBlock)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "setHeaderBlock", this, 1,
					TRACETYPE_POINTER, sizeof(HeaderBlock), ((void*)&pHeaderBlock));	  /* AUTOINSERTED TRACE */
	#endif

    int intStatus = AXIS_FAIL;
    if( (m_pSoapEnvelope) && (m_pSoapEnvelope->m_pSoapHeader))
    {
        /* no need to create a SOAP Header, it already exists */
    }
    else
    {
        SoapHeader * pSoapHeader = new SoapHeader();
        setSoapHeader( pSoapHeader);
    }
    m_pSoapEnvelope->m_pSoapHeader->addHeaderBlock( pHeaderBlock);
    intStatus = AXIS_SUCCESS;
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (intStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "setHeaderBlock", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return intStatus;
		#endif
	}

}

/*
 * This method not only removes the existing SoapHeader, but also removes
 * all the existing HeaderBlocks which are associated with this SoapHeader.
 * Therefore the caller of this method has to be exactly sure whether he wants
 * to do this.
 */

int SoapSerializer::removeSoapHeader()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "removeSoapHeader", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    delete m_pSoapEnvelope->m_pSoapHeader;
    m_pSoapEnvelope->m_pSoapHeader= NULL;
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "removeSoapHeader", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}
  // Can it only be successful?
}

/*
 * Used to Serialize an array of complex types inside a complex type. Called 
 * from within the Serialize wrapper method of the complex type.
 */

//int SoapSerializer::serializeCmplxArray( const Axis_Array * pArray, 
//                                         void * pSZFunct,
//										 void * pDelFunct,
//                                         void * pSizeFunct, 
//                                         const AxisChar * pName, 
//                                         const AxisChar * pNamespace)
//{
//	#ifdef ENABLE_AXISTRACE
//		if (axiscpp::AxisTrace::isTraceOn())
//			axiscpp::AxisTrace::traceEntry("SoapSerializer", "serializeCmplxArray", this, 6,
//					TRACETYPE_POINTER, sizeof(Axis_Array), ((void*)&pArray),
//					TRACETYPE_POINTER, 1, ((void*)&pSZFunct),
//					TRACETYPE_POINTER, 1, ((void*)&pDelFunct),
//					TRACETYPE_POINTER, 1, ((void*)&pSizeFunct),
//					TRACETYPE_STRING, 0, ((void*)&pName),
//					TRACETYPE_STRING, 0, ((void*)&pNamespace));	  /* AUTOINSERTED TRACE */
//	#endif
//
//    ArrayBean * pAb = (ArrayBean*) makeArrayBean( pArray->m_Array, 
//											      pSZFunct,
//												  pDelFunct,
//												  pSizeFunct);
//    pAb->SetDimension( pArray->m_Size);
//    Param * pParam = new Param();
//    if( RPC_ENCODED == m_nStyle)
//    {
//        pAb->SetItemName( "item");
//        pAb->SetTypeName( pName);
//        pAb->SetUri( pNamespace);
//        pParam->setName( pName);
//    }
//    else
//    {
//        pAb->SetItemName( pName);
//        pParam->setName( "array");        
//    }
//    pParam->m_Value.pArray = pAb;
//    pParam->m_Type = XSD_ARRAY;
//	if( pNamespace != NULL)
//    {
//        bool blnIsNewNamespacePrefix = false;
//        const AxisChar* np = getNamespacePrefix( pNamespace, blnIsNewNamespacePrefix);
//        const AxisChar* originalNamespace = getNamespace(); // Store original namespace
//        pParam->setPrefix( np);
//        if( blnIsNewNamespacePrefix)
//        {
//            removeNamespacePrefix( pNamespace);
//        }
//        setNamespace( pNamespace);
//        pParam->serialize( *this);
//        setNamespace( originalNamespace); // Revert back original namespace
//    }
//    else
//    {
//        pParam->serialize( *this);
//    }
//    /* Remove pointer to the array from the ArrayBean to avoid deleting the 
//     * array when ArrayBean is deleted. Array will be deleted when the complex
//     * type that contains this array is deleted */
//    pAb->RemoveArrayPointer();
//    delete pParam;
//    	{
//		#ifdef ENABLE_AXISTRACE
//			int traceRet = (AXIS_SUCCESS);
//			if (axiscpp::AxisTrace::isTraceOn())
//				axiscpp::AxisTrace::traceExit("SoapSerializer", "serializeCmplxArray", this, 0,
//					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
//			return traceRet;
//		#else
//			return AXIS_SUCCESS;
//		#endif
//	}
//  // Can it only be successful?
//}

/*
 * Used to Serialize an array of basic types inside a complex type. Called from
 * within the Serialize wrapper method of the complex type.
 */

//int SoapSerializer::serializeBasicArray( const Axis_Array * pArray, 
//                                         XSDTYPE nType,
//										 const AxisChar * pName)
//{
//	#ifdef ENABLE_AXISTRACE
//		if (axiscpp::AxisTrace::isTraceOn())
//			axiscpp::AxisTrace::traceEntry("SoapSerializer", "serializeBasicArray", this, 3,
//					TRACETYPE_POINTER, sizeof(Axis_Array), ((void*)&pArray),
//					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&nType),
//					TRACETYPE_STRING, 0, ((void*)&pName));	  /* AUTOINSERTED TRACE */
//	#endif
//
//		{
//		#ifdef ENABLE_AXISTRACE
//			int traceRet = (serializeBasicArray( pArray, NULL, nType, pName));
//			if (axiscpp::AxisTrace::isTraceOn())
//				axiscpp::AxisTrace::traceExit("SoapSerializer", "serializeBasicArray", this, 0,
//					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
//			return traceRet;
//		#else
//			return serializeBasicArray( pArray, NULL, nType, pName);
//		#endif
//	}
//
//}

/*
 * Used to Serialize an array of basic types inside a complex type. Contains 
 * the namespace so that it can be serialized. Called from within the Serialize
 * wrapper method of the complex type.
 */

//int SoapSerializer::serializeBasicArray(const Axis_Array* pArray, 
//										const AxisChar* pNamespace, 
//                                        XSDTYPE nType, const AxisChar* pName)
//{
//	#ifdef ENABLE_AXISTRACE
//		if (axiscpp::AxisTrace::isTraceOn())
//			axiscpp::AxisTrace::traceEntry("SoapSerializer", "serializeBasicArray", this, 4,
//					TRACETYPE_POINTER, sizeof(Axis_Array), ((void*)&pArray),
//					TRACETYPE_STRING, 0, ((void*)&pNamespace),
//					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&nType),
//					TRACETYPE_STRING, 0, ((void*)&pName));	  /* AUTOINSERTED TRACE */
//	#endif
//
//	ArrayBean * pAb = (ArrayBean *) makeArrayBean( nType, pArray->m_Array);
//    pAb->SetDimension( pArray->m_Size);
//    Param * pParam = new Param();
//    if( RPC_ENCODED == m_nStyle)
//    {
//        pAb->SetItemName( "item");
//        pParam->setName( pName);
//    }
//    else
//    {
//        pAb->SetItemName( pName);
//        pParam->setName( "array");        
//    }
//    pParam->m_Value.pArray = pAb;
//    pParam->m_Type = XSD_ARRAY;
//    
//    if( pNamespace != NULL)
//    {
//        bool blnIsNewNamespacePrefix = false;
//        const AxisChar * np = getNamespacePrefix( pNamespace, blnIsNewNamespacePrefix);
//        const AxisChar * originalNamespace = getNamespace(); // Store original namespace
//        pParam->setPrefix( np);
//        if( blnIsNewNamespacePrefix)
//        {
//            removeNamespacePrefix( pNamespace);
//        }
//        setNamespace( pNamespace);
//        pParam->serialize( *this);
//        setNamespace( originalNamespace); // Revert back original namespace
//    }
//    else
//    {
//        pParam->serialize( *this);
//    }
//    /* Remove pointer to the array from the ArrayBean to avoid deleting the
//     * array when ArrayBean is deleted. Array will be deleted when the complex
//     * type that contains this array is deleted
//     */
//    pAb->RemoveArrayPointer();
//    delete pParam;
//    	{
//		#ifdef ENABLE_AXISTRACE
//			int traceRet = (AXIS_SUCCESS);
//			if (axiscpp::AxisTrace::isTraceOn())
//				axiscpp::AxisTrace::traceExit("SoapSerializer", "serializeBasicArray", this, 0,
//					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
//			return traceRet;
//		#else
//			return AXIS_SUCCESS;
//		#endif
//	}
//  // Can it only be successful?
//}

#ifdef UNIT_TESTING_ON

int SoapSerializer::setOutputStreamForTesting(SOAPTransport* pStream)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "setOutputStreamForTesting", this, 1,
					TRACETYPE_POINTER, sizeof(SOAPTransport), ((void*)&pStream));	  /* AUTOINSERTED TRACE */
	#endif

    m_pOutputStream = pStream;
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "setOutputStreamForTesting", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

#endif

/*
 * Basic output parameter going to be serialized as an Element later
 */

int SoapSerializer::addOutputParam( const AxisChar * pchName,
								    void * pValue, 
                                    XSDTYPE type)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "addOutputParam", this, 3,
					TRACETYPE_STRING, 0, ((void*)&pchName),
					TRACETYPE_POINTER, 1, ((void*)&pValue),
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&type));	  /* AUTOINSERTED TRACE */
	#endif

    IAnySimpleType* xsdValue = AxisUtils::createSimpleTypeObject(pValue, type);
    
    Param pParam ;
//    if( !pParam)
	{
			{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "addOutputParam", this, 1,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}

	}
    pParam.m_Type = type;
    pParam.m_sName = pchName;
    pParam.setValue(type, xsdValue);
    
    if( m_pSoapEnvelope &&
		(m_pSoapEnvelope->m_pSoapBody) &&
		(m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod)) 
    {
        m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod->addOutputParam(pParam);
    }
    else
    {
//        delete pParam;
        	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "addOutputParam", this, 2,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}

    }
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "addOutputParam", this, 3,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}
  // Can it only be successful?
}


int SoapSerializer::serializeAsElement( const AxisChar * pName,
                                        void * pValue, 
                                        XSDTYPE type)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "serializeAsElement", this, 3,
					TRACETYPE_STRING, 0, ((void*)&pName),
					TRACETYPE_POINTER, 1, ((void*)&pValue),
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&type));	  /* AUTOINSERTED TRACE */
	#endif

  	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (serializeAsElement( pName, NULL, pValue, type));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "serializeAsElement", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return serializeAsElement( pName, NULL, pValue, type);
		#endif
	}

}
int SoapSerializer::serializeAsElement( const AxisChar * pName, 
                                        const AxisChar * pNamespace,
                                        void * pValue, 
                                        XSDTYPE type) 
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "serializeAsElement", this, 4,
					TRACETYPE_STRING, 0, ((void*)&pName),
					TRACETYPE_STRING, 0, ((void*)&pNamespace),
					TRACETYPE_POINTER, 1, ((void*)&pValue),
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&type));	  /* AUTOINSERTED TRACE */
	#endif

    IAnySimpleType* pSimpleType = AxisUtils::createSimpleTypeObject(pValue, type);
    int ret;
    ret = serializeAsElement(pName, pNamespace, pSimpleType);
    // Samisa: got to clean memory allocated in AxisUtils::createSimpleTypeObject
    delete pSimpleType;
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (ret);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "serializeAsElement", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return ret;
		#endif
	}

}

int SoapSerializer::serializeAsElement( const AxisChar * pName,
									    IAnySimpleType * pSimpleType)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "serializeAsElement", this, 2,
					TRACETYPE_STRING, 0, ((void*)&pName),
					TRACETYPE_POINTER, sizeof(IAnySimpleType), ((void*)&pSimpleType));	  /* AUTOINSERTED TRACE */
	#endif

		{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (serializeAsElement( pName, NULL, pSimpleType));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "serializeAsElement", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return serializeAsElement( pName, NULL, pSimpleType);
		#endif
	}

}

int SoapSerializer::serializeAsElement( const AxisChar * pName, 
									    const AxisChar * pNamespace,
									    IAnySimpleType * pSimpleType) 
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "serializeAsElement", this, 3,
					TRACETYPE_STRING, 0, ((void*)&pName),
					TRACETYPE_STRING, 0, ((void*)&pNamespace),
					TRACETYPE_POINTER, sizeof(IAnySimpleType), ((void*)&pSimpleType));	  /* AUTOINSERTED TRACE */
	#endif

    const AxisChar* pPrefix = NULL;
    bool blnIsNewPrefix = false;
    if( pNamespace)
	{
        pPrefix = getNamespacePrefix( pNamespace, blnIsNewPrefix);
    }
    
    const AxisChar * pSerialized = NULL;
    if( blnIsNewPrefix)
    {
        pSerialized = m_BTSZ.serializeAsElement( pName, pPrefix, pNamespace, pSimpleType);
        
		removeNamespacePrefix( pNamespace);
    }
    else
    {
        pSerialized = m_BTSZ.serializeAsElement( pName, pPrefix, pSimpleType);
    }
    if( pSerialized)
    {
        *this << pSerialized;
        	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "serializeAsElement", this, 1,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}
  // Can it only be successful?
    }
		{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "serializeAsElement", this, 2,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}
  // Can it only be unsuccessful?
} 


int SoapSerializer::serializeAsAttribute( const AxisChar * pName,
                                          const AxisChar * pNamespace,
                                          void * pValue,
                                          XSDTYPE type)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "serializeAsAttribute", this, 4,
					TRACETYPE_STRING, 0, ((void*)&pName),
					TRACETYPE_STRING, 0, ((void*)&pNamespace),
					TRACETYPE_POINTER, 1, ((void*)&pValue),
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&type));	  /* AUTOINSERTED TRACE */
	#endif

    IAnySimpleType* pSimpleType = AxisUtils::createSimpleTypeObject(pValue, type);
    
    int status = serializeAsAttribute(pName, pNamespace, pSimpleType);
    delete pSimpleType;
    
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (status);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "serializeAsAttribute", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return status;
		#endif
	}

}

int SoapSerializer::serializeAsAttribute( const AxisChar * pName, 
                                          const AxisChar * pNamespace, 
                                          IAnySimpleType* pSimpleType)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "serializeAsAttribute", this, 3,
					TRACETYPE_STRING, 0, ((void*)&pName),
					TRACETYPE_STRING, 0, ((void*)&pNamespace),
					TRACETYPE_POINTER, sizeof(IAnySimpleType), ((void*)&pSimpleType));	  /* AUTOINSERTED TRACE */
	#endif

    const AxisChar * pPrefix = NULL;
    if( pNamespace)
    {
        pPrefix = getNamespacePrefix( pNamespace);
    }
    const AxisChar * pSerialized = m_BTSZ.serializeAsAttribute(pName, pPrefix, pSimpleType);
    if( pSerialized)
    {
        *this << pSerialized;
        	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "serializeAsAttribute", this, 1,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}
   // Can it only be successful?
    }
		{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "serializeAsAttribute", this, 2,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}
  // Can it only be unsuccessful?
}

void SoapSerializer::serializeVargs( int count, const char ** args)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "serializeVargs", this, 2,
					TRACETYPE_INT, 0, ((void*)&count),
					TRACETYPE_POINTER, sizeof(char*), ((void*)&args));	  /* AUTOINSERTED TRACE */
	#endif

    for (int i=0; i<count; i++)
    {
        if (NULL != args[i])
            *this << args[i];
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "serializeVargs", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

void SoapSerializer::serialize( const char * pFirst, ...)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "serialize", this, 1,
					TRACETYPE_STRING, 0, ((void*)&pFirst) );	  /* AUTOINSERTED TRACE */
	#endif

    va_list vList;
    va_start( vList, pFirst );     /* Initialize variable arguments. */
    
	const char * pArg;
    
	if( pFirst)
	{
		*this << pFirst;
	}
    do
    {
        pArg = va_arg( vList, const char*);
        if( pArg)
		{
            *this << pArg;
		}
    } while( pArg != NULL);
    va_end( vList);              /* Reset variable arguments.      */
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "serialize", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

/*
 * Used probably by a handler to add a header block to the Serializer. 
 */

int SoapSerializer::addHeaderBlock( IHeaderBlock * pBlk)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "addHeaderBlock", this, 1,
					TRACETYPE_POINTER, sizeof(IHeaderBlock), ((void*)&pBlk));	  /* AUTOINSERTED TRACE */
	#endif

    if( m_pSoapEnvelope)
    {
        if( !m_pSoapEnvelope->m_pSoapHeader)
		{
			m_pSoapEnvelope->m_pSoapHeader = new SoapHeader();
		}
    }
    else /* error : by this time there should be an envelope */
    {
        	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "addHeaderBlock", this, 1,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}

    }
    m_pSoapEnvelope->m_pSoapHeader->addHeaderBlock( (HeaderBlock *) pBlk);
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "addHeaderBlock", this, 2,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}
  // Can it only be successful?
}

int SoapSerializer::setBodyAsHexBinary( xsd__hexBinary body)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "setBodyAsHexBinary", this, 1,
					TRACETYPE_DATA, sizeof(xsd__hexBinary), ((void*)&body));	  /* AUTOINSERTED TRACE */
	#endif

    /* TODO */
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "setBodyAsHexBinary", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}
int SoapSerializer::setBodyAsBase64Binary( xsd__base64Binary body)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "setBodyAsBase64Binary", this, 1,
					TRACETYPE_DATA, sizeof(xsd__base64Binary), ((void*)&body));	  /* AUTOINSERTED TRACE */
	#endif

    /* TODO */    
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "setBodyAsBase64Binary", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

const AxisChar* SoapSerializer::getBodyAsString()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "getBodyAsString", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    /* TODO */    
    	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "getBodyAsString", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

}

/* following two functions are needed by serializer functions of complex types
 * for RPC style web services
 */

void SoapSerializer::serializeStartElementOfType( const AxisChar * pName, 
                                                  const AxisChar * pNamespace, 
                                                  const AxisChar * pPrefix)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "serializeStartElementOfType", this, 3,
					TRACETYPE_STRING, 0, ((void*)&pName),
					TRACETYPE_STRING, 0, ((void*)&pNamespace),
					TRACETYPE_STRING, 0, ((void*)&pPrefix));	  /* AUTOINSERTED TRACE */
	#endif

    if( pPrefix)
    {
        serialize( "<",
				   pName,
				   " xsi:type=\"",
				   pPrefix,
				   ":",
				   pName,
				   "\" xmlns:",
				   pPrefix,
				   "=\"",
				   pNamespace,
				   "\">",
				   NULL);
    }
    else
    {
        serialize( "<", pName, ">", NULL);
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "serializeStartElementOfType", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

void SoapSerializer::serializeEndElementOfType( const AxisChar * pName)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "serializeEndElementOfType", this, 1,
					TRACETYPE_STRING, 0, ((void*)&pName));	  /* AUTOINSERTED TRACE */
	#endif

    serialize( "</", pName, ">", NULL);
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "serializeEndElementOfType", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

IHeaderBlock * SoapSerializer::createHeaderBlock( const AxisChar * pachLocalName, 
                                                  const AxisChar * pachUri)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "createHeaderBlock", this, 2,
					TRACETYPE_STRING, 0, ((void*)&pachLocalName),
					TRACETYPE_STRING, 0, ((void*)&pachUri));	  /* AUTOINSERTED TRACE */
	#endif

    HeaderBlock * pHeaderBlock= new HeaderBlock( pachLocalName, pachUri);
    setHeaderBlock( pHeaderBlock);
    	{
		#ifdef ENABLE_AXISTRACE
			IHeaderBlock* traceRet = (pHeaderBlock);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "createHeaderBlock", this, 0,
					TRACETYPE_POINTER, sizeof(IHeaderBlock), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return pHeaderBlock;
		#endif
	}
    
}

SoapMethod * SoapSerializer::getSOAPMethod()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "getSOAPMethod", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

	/*
	 *TODO
	 * return the SOAPMethod object if one is available. If not available create a SOAPMethod and set it and return it.
	 */
		{
		#ifdef ENABLE_AXISTRACE
			SoapMethod* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "getSOAPMethod", this, 0,
					TRACETYPE_POINTER, sizeof(SoapMethod), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

}

int SoapSerializer::setSOAPMethodAttribute( Attribute * pAttribute)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "setSOAPMethodAttribute", this, 1,
					TRACETYPE_POINTER, sizeof(Attribute), ((void*)&pAttribute));	  /* AUTOINSERTED TRACE */
	#endif

	if( m_pSoapEnvelope &&
		(m_pSoapEnvelope->m_pSoapBody) &&
		(m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod))
    {
		m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod->addAttribute( pAttribute);
			{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "setSOAPMethodAttribute", this, 1,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}
  // Can it only be successful?
	}
		{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "setSOAPMethodAttribute", this, 2,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}

}

int SoapSerializer::serializeAnyObject( AnyType * pAnyObject)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "serializeAnyObject", this, 1,
					TRACETYPE_POINTER, sizeof(AnyType), ((void*)&pAnyObject));	  /* AUTOINSERTED TRACE */
	#endif

    for( int i = 0; i < pAnyObject->_size; i++)
    {
        serialize( pAnyObject->_array[i], 0);
    }
		{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "serializeAnyObject", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}
  // Can it only be successful?
}

int SoapSerializer::addOutputAnyObject( AnyType * pAnyObject)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "addOutputAnyObject", this, 1,
					TRACETYPE_POINTER, sizeof(AnyType), ((void*)&pAnyObject));	  /* AUTOINSERTED TRACE */
	#endif

    Param pParam;
    pParam.m_Type = XSD_ANY;
    pParam.m_Value.pAnyObject = pAnyObject;
    if( m_pSoapEnvelope &&
		(m_pSoapEnvelope->m_pSoapBody) &&
		(m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod))
    {
        m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod->addOutputParam(pParam);
    }
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "addOutputAnyObject", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}
  // Can it only be successful?
}

/*
 * TODO: Have to remove this method. Date logged 13Jan2005
 
IHeaderBlock* SoapSerializer::getHeaderBlock()
{
    if ((!m_pSoapEnvelope) || (!m_pSoapEnvelope->m_pSoapHeader)) return NULL;
    return (HeaderBlock*)m_pSoapEnvelope->m_pSoapHeader->getHeaderBlock(false);	
}
*/

IHeaderBlock * SoapSerializer::getHeaderBlock( const AxisChar * pcName, 
											   const AxisChar * pcNamespace)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "getHeaderBlock", this, 2,
					TRACETYPE_STRING, 0, ((void*)&pcName),
					TRACETYPE_STRING, 0, ((void*)&pcNamespace));	  /* AUTOINSERTED TRACE */
	#endif

    if( (!m_pSoapEnvelope) ||
		(!m_pSoapEnvelope->m_pSoapHeader))
	{
			{
		#ifdef ENABLE_AXISTRACE
			IHeaderBlock* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "getHeaderBlock", this, 1,
					TRACETYPE_POINTER, sizeof(IHeaderBlock), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}
 
	}
	// there has been no <Header> element so there can be no Header blocks
    	{
		#ifdef ENABLE_AXISTRACE
			IHeaderBlock* traceRet = (m_pSoapEnvelope->m_pSoapHeader->getHeaderBlock( pcName, pcNamespace, false));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "getHeaderBlock", this, 2,
					TRACETYPE_POINTER, sizeof(IHeaderBlock), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_pSoapEnvelope->m_pSoapHeader->getHeaderBlock( pcName, pcNamespace, false);
		#endif
	}

}

IHeaderBlock * SoapSerializer::getFirstHeaderBlock()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "getFirstHeaderBlock", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

		{
		#ifdef ENABLE_AXISTRACE
			IHeaderBlock* traceRet = (m_pSoapEnvelope->m_pSoapHeader->getFirstHeaderBlock());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "getFirstHeaderBlock", this, 0,
					TRACETYPE_POINTER, sizeof(IHeaderBlock), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_pSoapEnvelope->m_pSoapHeader->getFirstHeaderBlock();
		#endif
	}

}

IHeaderBlock * SoapSerializer::getNextHeaderBlock()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "getNextHeaderBlock", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

		{
		#ifdef ENABLE_AXISTRACE
			IHeaderBlock* traceRet = (m_pSoapEnvelope->m_pSoapHeader->getNextHeaderBlock());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "getNextHeaderBlock", this, 0,
					TRACETYPE_POINTER, sizeof(IHeaderBlock), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_pSoapEnvelope->m_pSoapHeader->getNextHeaderBlock();
		#endif
	}

}

int SoapSerializer::serializeAsChardata( void * pValue, XSDTYPE type)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "serializeAsChardata", this, 2,
					TRACETYPE_POINTER, 1, ((void*)&pValue),
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&type));	  /* AUTOINSERTED TRACE */
	#endif

    char * pStr = m_Buf;
    IAnySimpleType* pSimpleType = AxisUtils::createSimpleTypeObject(pValue, type);
    pStr = pSimpleType->serialize();
    *this << pStr;
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "serializeAsChardata", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}
  // Can it only be successful?
}

//void SoapSerializer::serializeAttachments( SoapSerializer &pSZ)
//{
//	#ifdef ENABLE_AXISTRACE
//		if (axiscpp::AxisTrace::isTraceOn())
//			axiscpp::AxisTrace::traceEntry("SoapSerializer", "serializeAttachments", this, 1,
//					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ));	  /* AUTOINSERTED TRACE */
//	#endif
//
//	/*serializing the attachments*/
//	map<AxisXMLString, ISoapAttachment*>::iterator itCurrAttach= m_SoapAttachments.begin();
//	while( itCurrAttach != m_SoapAttachments.end())
//    {
//		SoapAttachment *att = ((SoapAttachment *) ((*itCurrAttach).second));
//		if (NULL != att->getBody())
//		{
//			serialize( "\r\n--" MIMEBOUNDARY, NULL);
//			att->serialize(pSZ);
//		}
//        itCurrAttach++;
//    }
//	pSZ.serialize("\r\n--" MIMEBOUNDARY "--\r\n", NULL);
//	{
//		#ifdef ENABLE_AXISTRACE
//			if (axiscpp::AxisTrace::isTraceOn())
//				axiscpp::AxisTrace::traceExit("SoapSerializer", "serializeAttachments", this, 0);	  /* AUTOINSERTED TRACE */
//		#endif
//		return;
//	}
//}

//void SoapSerializer::addAttachment( const AxisChar * achId, ISoapAttachment * pAttach)
//{
//	#ifdef ENABLE_AXISTRACE
//		if (axiscpp::AxisTrace::isTraceOn())
//			axiscpp::AxisTrace::traceEntry("SoapSerializer", "addAttachment", this, 2,
//					TRACETYPE_STRING, 0, ((void*)&achId),
//					TRACETYPE_POINTER, sizeof(ISoapAttachment), ((void*)&pAttach));	  /* AUTOINSERTED TRACE */
//	#endif
//
//	m_SoapAttachments[achId] = pAttach;
//	{
//		#ifdef ENABLE_AXISTRACE
//			if (axiscpp::AxisTrace::isTraceOn())
//				axiscpp::AxisTrace::traceExit("SoapSerializer", "addAttachment", this, 0);	  /* AUTOINSERTED TRACE */
//		#endif
//		return;
//	}
//}

//void SoapSerializer::addAttachments(ISoapAttachment** pAttach, int iAttchArraySize)
//{
//	#ifdef ENABLE_AXISTRACE
//		if (axiscpp::AxisTrace::isTraceOn())
//			axiscpp::AxisTrace::traceEntry("SoapSerializer", "addAttachments", this, 2,
//					TRACETYPE_POINTER, sizeof(ISoapAttachment*), ((void*)&pAttach),
//					TRACETYPE_INT, 0, ((void*)&iAttchArraySize));	  /* AUTOINSERTED TRACE */
//	#endif
//   
//     for (int i=0; i < iAttchArraySize; i++)
//    {
//         const char *id = ((ISoapAttachment*)pAttach[i])->getAttachmentId();
//         m_SoapAttachments[id] = pAttach[i];
//      
//    }
// 
//	{
//		#ifdef ENABLE_AXISTRACE
//			if (axiscpp::AxisTrace::isTraceOn())
//				axiscpp::AxisTrace::traceExit("SoapSerializer", "addAttachments", this, 0);	  /* AUTOINSERTED TRACE */
//		#endif
//		return;
//	}
//}

//void SoapSerializer::addAttachmentHeader(const AxisChar * achId,
//										 const AxisChar * achHeaderName,
//										 const AxisChar * achHeaderValue)
//{
//	#ifdef ENABLE_AXISTRACE
//		if (axiscpp::AxisTrace::isTraceOn())
//			axiscpp::AxisTrace::traceEntry("SoapSerializer", "addAttachmentHeader", this, 3,
//					TRACETYPE_STRING, 0, ((void*)&achId),
//					TRACETYPE_STRING, 0, ((void*)&achHeaderName),
//					TRACETYPE_STRING, 0, ((void*)&achHeaderValue));	  /* AUTOINSERTED TRACE */
//	#endif
//
//	if (m_SoapAttachments[achId] == NULL)
//	{
//		m_SoapAttachments[achId] = new SoapAttachment(m_pContentIdSet);		
//	}
//	m_SoapAttachments[achId]->addHeader( achHeaderName, achHeaderValue);
//	{
//		#ifdef ENABLE_AXISTRACE
//			if (axiscpp::AxisTrace::isTraceOn())
//				axiscpp::AxisTrace::traceExit("SoapSerializer", "addAttachmentHeader", this, 0);	  /* AUTOINSERTED TRACE */
//		#endif
//		return;
//	}
//}

//void SoapSerializer::addAttachmentBody( const AxisChar * achId,
//									    xsd__base64Binary * pAttchBody)
//{
//	#ifdef ENABLE_AXISTRACE
//		if (axiscpp::AxisTrace::isTraceOn())
//			axiscpp::AxisTrace::traceEntry("SoapSerializer", "addAttachmentBody", this, 2,
//					TRACETYPE_STRING, 0, ((void*)&achId),
//					TRACETYPE_POINTER, sizeof(xsd__base64Binary), ((void*)&pAttchBody));	  /* AUTOINSERTED TRACE */
//	#endif
//
//	if( m_SoapAttachments[achId] == NULL)
//	{
//		m_SoapAttachments[achId] = new SoapAttachment(m_pContentIdSet);		
//	}
//	m_SoapAttachments[achId]->addBody( pAttchBody);
//	{
//		#ifdef ENABLE_AXISTRACE
//			if (axiscpp::AxisTrace::isTraceOn())
//				axiscpp::AxisTrace::traceExit("SoapSerializer", "addAttachmentBody", this, 0);	  /* AUTOINSERTED TRACE */
//		#endif
//		return;
//	}
//}

void SoapSerializer::addNamespaceToEnvelope( AxisChar * pachNamespaceURI,
											 AxisChar * pachPrefix)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "addNamespaceToEnvelope", this, 2,
					TRACETYPE_STRING, 0, ((void*)&pachNamespaceURI),
					TRACETYPE_STRING, 0, ((void*)&pachPrefix));	  /* AUTOINSERTED TRACE */
	#endif

        std::list<Attribute*> attributeList;
	Attribute * pNameSpace = new Attribute( attributeList,
											pachPrefix,
											"xmlns",
											pachNamespaceURI);
	m_pSoapEnvelope->addNamespaceDecl( pNameSpace);
	addNamespaceToNamespaceList( pachNamespaceURI, pachPrefix);
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "addNamespaceToEnvelope", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

void SoapSerializer::addNamespaceToNamespaceList( const AxisChar * pachNamespaceURI,
												  const AxisChar * pachPrefix)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "addNamespaceToNamespaceList", this, 2,
					TRACETYPE_STRING, 0, ((void*)&pachNamespaceURI),
					TRACETYPE_STRING, 0, ((void*)&pachPrefix));	  /* AUTOINSERTED TRACE */
	#endif

	m_NsStack[pachNamespaceURI] = pachPrefix;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "addNamespaceToNamespaceList", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

//ISoapAttachment* SoapSerializer::createSoapAttachment()
//{
//	#ifdef ENABLE_AXISTRACE
//		if (axiscpp::AxisTrace::isTraceOn())
//			axiscpp::AxisTrace::traceEntry("SoapSerializer", "createSoapAttachment", this, 0);	  /* AUTOINSERTED TRACE */
//	#endif
//
//		{
//		#ifdef ENABLE_AXISTRACE
//			ISoapAttachment* traceRet = (new SoapAttachment(m_pContentIdSet));
//			if (axiscpp::AxisTrace::isTraceOn())
//				axiscpp::AxisTrace::traceExit("SoapSerializer", "createSoapAttachment", this, 0,
//					TRACETYPE_POINTER, sizeof(ISoapAttachment), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
//			return traceRet;
//		#else
//			return new SoapAttachment(m_pContentIdSet);
//		#endif
//	}
//
//}

//void SoapSerializer::setContentIdSet(ContentIdSet *pContentIdSet) 
//{
//	#ifdef ENABLE_AXISTRACE
//		if (axiscpp::AxisTrace::isTraceOn())
//			axiscpp::AxisTrace::traceEntry("SoapSerializer", "setContentIdSet", this, 1,
//					TRACETYPE_POINTER, sizeof(ContentIdSet), ((void*)&pContentIdSet));	  /* AUTOINSERTED TRACE */
//	#endif
//
//	m_pContentIdSet = pContentIdSet;
//	{
//		#ifdef ENABLE_AXISTRACE
//			if (axiscpp::AxisTrace::isTraceOn())
//				axiscpp::AxisTrace::traceExit("SoapSerializer", "setContentIdSet", this, 0);	  /* AUTOINSERTED TRACE */
//		#endif
//		return;
//	}
//}

//bool SoapSerializer::checkAttachmentAvailability()
//{
//	#ifdef ENABLE_AXISTRACE
//		if (axiscpp::AxisTrace::isTraceOn())
//			axiscpp::AxisTrace::traceEntry("SoapSerializer", "checkAttachmentAvailability", this, 0);	  /* AUTOINSERTED TRACE */
//	#endif
//
//	map<AxisXMLString, ISoapAttachment*>::iterator itCurrAttach= m_SoapAttachments.begin();
//	if( itCurrAttach != m_SoapAttachments.end())
//	{
//			{
//		#ifdef ENABLE_AXISTRACE
//			bool traceRet = (true);
//			if (axiscpp::AxisTrace::isTraceOn())
//				axiscpp::AxisTrace::traceExit("SoapSerializer", "checkAttachmentAvailability", this, 1,
//					TRACETYPE_BOOL, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
//			return traceRet;
//		#else
//			return true;
//		#endif
//	}
//
//	}
//		{
//		#ifdef ENABLE_AXISTRACE
//			bool traceRet = (false);
//			if (axiscpp::AxisTrace::isTraceOn())
//				axiscpp::AxisTrace::traceExit("SoapSerializer", "checkAttachmentAvailability", this, 2,
//					TRACETYPE_BOOL, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
//			return traceRet;
//		#else
//			return false;
//		#endif
//	}
//
//}

//void SoapSerializer::addAttachmentParameter(ISoapAttachment* att, const char* pName, IAttribute **attributes, int nAttributes)
//{
//	#ifdef ENABLE_AXISTRACE
//		if (axiscpp::AxisTrace::isTraceOn())
//			axiscpp::AxisTrace::traceEntry("SoapSerializer", "addAttachmentParameter", this, 4,
//					TRACETYPE_POINTER, sizeof(ISoapAttachment), ((void*)&att),
//					TRACETYPE_STRING, 0, ((void*)&pName),
//					TRACETYPE_POINTER, sizeof(IAttribute*), ((void*)&attributes),
//					TRACETYPE_INT, 0, ((void*)&nAttributes));	  /* AUTOINSERTED TRACE */
//	#endif
//
//	if (NULL==att)
//		att = static_cast<ISoapAttachment*>(new SoapAttachment(m_pContentIdSet));
//	SoapAttachmentReference *ref = new SoapAttachmentReference(static_cast<SoapAttachment*>(att));
//	m_attachmentRefs.push_back(ref);
//    Param *pParam = new Param();
//    pParam->m_Value.pAttachmentRef = ref;
//	pParam->m_Type = ATTACHMENT;
//	if (NULL!=attributes && nAttributes>0) 
//		ref->addAttributes(attributes,nAttributes);
//	
//	if (m_pSoapEnvelope &&
//		(m_pSoapEnvelope->m_pSoapBody) &&
//		(m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod)) 
//	{
//		m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod->addOutputParam(pParam);
//	}
//	pParam->setName(pName);
//	m_SoapAttachments[att->getAttachmentId()] = att;
//	{
//		#ifdef ENABLE_AXISTRACE
//			if (axiscpp::AxisTrace::isTraceOn())
//				axiscpp::AxisTrace::traceExit("SoapSerializer", "addAttachmentParameter", this, 0);	  /* AUTOINSERTED TRACE */
//		#endif
//		return;
//	}
//}

IHeaderBlock * SoapSerializer::getCurrentHeaderBlock()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "getCurrentHeaderBlock", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

		{
		#ifdef ENABLE_AXISTRACE
			IHeaderBlock* traceRet = (m_pSoapEnvelope->m_pSoapHeader->getCurrentHeaderBlock());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "getCurrentHeaderBlock", this, 0,
					TRACETYPE_POINTER, sizeof(IHeaderBlock), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_pSoapEnvelope->m_pSoapHeader->getCurrentHeaderBlock();
		#endif
	}

}

AxisXMLString SoapSerializer::getNamespaceURL( string sNameSpace)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "getNamespaceURL", this, 1,
					TRACETYPE_STLSTRING, 0, ((void*)&sNameSpace));	  /* AUTOINSERTED TRACE */
	#endif

// Check that the namespace value is not empty.  If it is then return as
// there is nothing to do!
	if( sNameSpace.empty())
	{
			{
		#ifdef ENABLE_AXISTRACE
			AxisXMLString traceRet = ("nothing to do");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "getNamespaceURL", this, 1,
					TRACETYPE_STLSTRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "nothing to do";
		#endif
	}

	}
// Iterate through the namespace stack.  If the namespace can be found, then
// return the associated uri.
	map <AxisXMLString, AxisXMLString>::iterator	iterator = m_NsStack.begin();
	while( iterator != m_NsStack.end())
	{
		AxisXMLString	sIt_URI = iterator->first;
		AxisXMLString	sIt_NameSpace = iterator->second;
		if( sNameSpace == sIt_NameSpace)
		{
				{
		#ifdef ENABLE_AXISTRACE
			AxisXMLString traceRet = (iterator->first);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "getNamespaceURL", this, 2,
					TRACETYPE_STLSTRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return iterator->first;
		#endif
	}

		}
		else
		{
			iterator++;
		}
	}
	if (NULL==m_pSoapEnvelope->m_pSoapHeader) 	{
		#ifdef ENABLE_AXISTRACE
			AxisXMLString traceRet = ("");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "getNamespaceURL", this, 3,
					TRACETYPE_STLSTRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "";
		#endif
	}

// Couldn't find the namespace in the namespace list.  Try trawling through the
// SOAP headers looking to see if any of their children have defined any
// namespaces.
	IHeaderBlock *	pHeaderBlock = m_pSoapEnvelope->m_pSoapHeader->getFirstHeaderBlock();
	while( pHeaderBlock != NULL)
	{
		for( int iChildIndex = 0; iChildIndex < pHeaderBlock->getNoOfChildren(); iChildIndex++)
		{
			BasicNode *	pChild = pHeaderBlock->getChild( iChildIndex + 1);
			if( pChild != NULL)
			{
				if( !strcmp( sNameSpace.c_str(), pChild->getPrefix()))
				{
						{
		#ifdef ENABLE_AXISTRACE
			AxisXMLString traceRet = (pChild->getURI());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "getNamespaceURL", this, 4,
					TRACETYPE_STLSTRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return pChild->getURI();
		#endif
	}

				}
			}
		}
		pHeaderBlock = m_pSoapEnvelope->m_pSoapHeader->getNextHeaderBlock();
	}
// Couldn't find the namespace in the namespace list or in children.  Try
// trawling through the SOAP headers looking to see if any of their attributes
// have defined any namespaces.
	char *	pszNameSpace = (char *) sNameSpace.c_str();
	char *	pszValue = NULL;
	pHeaderBlock = m_pSoapEnvelope->m_pSoapHeader->getFirstHeaderBlock();
	while( pHeaderBlock != NULL && pszValue == NULL)
	{
		pszValue = (char *) pHeaderBlock->getAttributeUri( "", pszNameSpace);
		pHeaderBlock = m_pSoapEnvelope->m_pSoapHeader->getNextHeaderBlock();
	}
	if( pszValue == NULL)
	{
			{
		#ifdef ENABLE_AXISTRACE
			AxisXMLString traceRet = ("");
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "getNamespaceURL", this, 5,
					TRACETYPE_STLSTRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return "";
		#endif
	}

	}
		{
		#ifdef ENABLE_AXISTRACE
			AxisXMLString traceRet = (pszValue);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "getNamespaceURL", this, 6,
					TRACETYPE_STLSTRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return pszValue;
		#endif
	}

}

int SoapSerializer::deleteHeaderBlock( const AxisChar * pName, 
									   const AxisChar * pNamespace)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "deleteHeaderBlock", this, 2,
					TRACETYPE_STRING, 0, ((void*)&pName),
					TRACETYPE_STRING, 0, ((void*)&pNamespace));	  /* AUTOINSERTED TRACE */
	#endif

   
    int iStatus = AXIS_SUCCESS;
    iStatus = m_pSoapEnvelope->m_pSoapHeader->deleteHeaderBlock( pName, pNamespace);
    //No remaining soap header blocks, so will delete the SoapHeader    
    if( iStatus == AXIS_NO_REMAINING_SOAP_HEADERS)     
    {
        delete m_pSoapEnvelope->m_pSoapHeader;
        m_pSoapEnvelope->m_pSoapHeader = NULL;
        iStatus = AXIS_SUCCESS;
    }
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (iStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "deleteHeaderBlock", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return iStatus;
		#endif
	}
 // Can it only be successful?
}

void SoapSerializer::reset()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "reset", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    m_nCounter = 0; // reset namespace prifix counter 
    if( m_pSoapEnvelope && (m_pSoapEnvelope->m_pSoapBody) && (m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod))
    {
        m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod->clearOutParams();    
    }
    if( m_pSoapEnvelope && m_pSoapEnvelope->m_pSoapHeader )
    {
        m_pSoapEnvelope->m_pSoapHeader->clear();
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "reset", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

