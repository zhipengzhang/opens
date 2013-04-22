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
 * @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 */

#include "SoapFault.h"

#include "SoapSerializer.h"

//llh #include "SoapDeSerializer.h"

#include <axis/SoapEnvVersions.hpp>

#include <axis/GDefine.hpp>

//llh #include "../common/AxisTrace.h"

//llh #include "../common/AxisConfig.h"

// This array of structure is used to store all the soap faults

// which are used in Axis C++. Each time a fault object is needed it is

// created using this array, in SoapFault class.

static SoapFaultStruct* s_parrSoapFaultStruct;

//extern AxisConfig* g_pConfig;

extern SoapEnvVersionsStruct gs_SoapEnvVersionsStruct[VERSION_LAST];

volatile bool SoapFault::m_bInit = false;

SoapFault::SoapFault()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapFault", "SoapFault", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    m_bIsSimpleDetail = false;
    m_pFaultDetail = NULL;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "SoapFault", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

SoapFault::~SoapFault()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapFault", "~SoapFault", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    delete m_pFaultcodeParam;
    delete m_pFaultstringParam;
    delete m_pFaultactorParam;
    if (NULL!=m_pFaultDetail) delete m_pFaultDetail;
    m_pFaultcodeParam = NULL;
    m_pFaultstringParam = NULL;
    m_pFaultactorParam = NULL;
    m_pFaultDetail = NULL;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "~SoapFault", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

int SoapFault::serialize(SoapSerializer& pSZ, SOAP_VERSION eSoapVersion)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapFault", "serialize", this, 2,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ),
					TRACETYPE_DATA, sizeof(SOAP_VERSION), ((void*)&eSoapVersion));	  /* AUTOINSERTED TRACE */
	#endif

    // written according to SOAP Version 1.1 
    int iStatus= AXIS_SUCCESS;
    if(m_bIsSimpleDetail)
    {
        pSZ.setStyle(DOC_LITERAL);
    pSZ.serialize("<", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix, ":",
        gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_FAULT], ">\n", NULL); 
	
    m_pFaultcodeParam->serialize(pSZ);
    m_pFaultstringParam->serialize(pSZ);
    if(m_pFaultactorParam)
    {        
        m_pFaultactorParam->serialize(pSZ);
    } 
	
	if(m_pFaultDetail) 
	{ 
		pSZ.serialize("<detail>", NULL); 
		m_pFaultDetail->serialize(pSZ); 
		pSZ.serialize("</detail>\n", NULL); 
	} 
    
	pSZ.serialize("</", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix, ":",
		gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_FAULT], ">\n", NULL); 
    }
    else
    {
        pSZ.serialize("<", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix, ":",
        gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_FAULT], ">\n", NULL);
    m_pFaultcodeParam->serialize(pSZ);
    m_pFaultstringParam->serialize(pSZ);
    if(m_pFaultactorParam)
    {
        m_pFaultactorParam->serialize(pSZ);
    }
	//Chinthana:Changed the code to solved Issue AXISCPP-706. 
    /*if(m_pFaultDetail)
    {
         pSZ.serialize("<detail>", NULL);
            m_pFaultDetail->serialize(pSZ);
            pSZ.serialize("</detail>\n", NULL);
    }*/
	if(m_pFaultDetail) 
	{ 
		pSZ.serialize("<detail><appSpecific>", NULL); 
		m_pFaultDetail->serialize(pSZ); 
		pSZ.serialize("</appSpecific></detail>\n", NULL); 
	} 
	//22/06/2005.........................................
        pSZ.serialize("</", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix, ":",
                gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_FAULT], ">\n", NULL);
    }
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (iStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "serialize", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return iStatus;
		#endif
	}

}

void SoapFault::initialize()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapFault", "initialize", NULL, 0);	  /* AUTOINSERTED TRACE */
	#endif

    if (!m_bInit)
    {
        static SoapFaultStruct s_arrLocalFaultStruct[FAULT_LAST] = 
        {
            /*VersionMismatch faults */
        /*0*/    {"VersionMismatch", "Soap Version Mismatch error", "", ""},
            /*MustUnderstand faults */ 
        /*1*/    {"MustUnderstand", "Soap Must Understand  error", "", ""},
            /*Client faults */
        /*2*/    {"Client", "Soap message is incorrect or incomplete", "", ""},
        /*3*/    {"Client", "Soap Action header empty", "", ""},
        /*4*/    {"Client", "Soap content is not valid", "", ""},
        /*5*/    {"Client", "No method to invoke", "", ""},
        /*6*/    {"Client", "Content is not Soap", "", ""},
        /*7*/    {"Client", "Requested service is not registered at the server", "", ""},
        /*8*/    {"Client", "Soap method is not allowed to invoke", "", ""},
        /*9*/    {"Client", "Parameter type mismatch", "", ""},
        /*10*/    {"Client", "A client handler failed", "", ""},
        /*11*/    {"Client", "Client transport exception", "", ""},
        /*12*/    {"Client", "Client transport open connection failed", "", ""},
        /*13*/    {"Client", "Client transport type mismatch", "", ""},
        /*14*/    {"Client", "Client transport has no unsecure transport layer", "", ""},
        /*15*/    {"Client", "Client transport has no secure transport layer", "", ""},
        /*16*/    {"Client", "Client SSL channel reception error", "", ""},
        /*17*/    {"Client", "Client SSL channel sending error", "", ""},
        /*18*/    {"Client", "Client SSL channel init error", "", ""},
        /*19*/    {"Client", "Client SSL channel socket create error", "", ""},
        /*20*/    {"Client", "Client SSL channel socket connect error", "", ""},
        /*21*/    {"Client", "Client SSL channel invalid socket error", "", ""},
        /*22*/    {"Client", "Client SSL channel context create error", "", ""},
        /*23*/    {"Client", "Client SSL channel error", "", ""},
        /*24*/    {"Client", "Client MIME content ID not unique", "", ""},
            /*Server faults */
        /*25*/    {"Server", "Unknown Server Engine Exception", "", ""},
        /*26*/    {"Server", "Cannot load web service", "", ""},
        /*27*/    {"Server", "Cannot load service handlers", "", ""},
        /*28*/    {"Server", "DLOPEN FAILED in loading transport library", "", ""},
        /*29*/    {"Server", "DLOPEN FAILED in loading parser library", "", ""},
        /*30*/    {"Server", "A service handler failed", "", ""},
        /*31*/    {"Server", "Webservice failed", "", ""},
        /*32*/    {"Server", "Handler initialization failed", "", ""},
        /*33*/    {"Server", "Handler creation failed", "", ""},
        /*34*/    {"Server", "Library loading failed", "", ""},
        /*35*/    {"Server", "Handler not loaded", "", ""},
        /*36*/    {"Server", "Handler is being used", "", ""},
        /*37*/    {"Server", "Get hander failed", "", ""},
        /*38*/    {"Server", "Wrong handler type", "", ""},
        /*39*/    {"Server", "Unknown Axis Configuration Exception", "", ""},
        /*40*/    {"Server", "Transport configuration error", "", ""},
        /*41*/    {"Server", "Library path is empty", "", ""},
        /*42*/    {"Server", "Wsdd file not found", "", ""},
        /*43*/    {"Server", "Unknown Wsdd Exception", "", ""},
        /*44*/    {"Server", "No handlers configured", "", ""},
        /*45*/    {"Server", "Unknown Soap Exception", "", ""},
        /*46*/    {"Server", "Unknown Transport Exception", "", ""},
        /*47*/    {"Server", "Receive from transport failed", "", ""},
        /*48*/    {"Server", "Send to transport failed", "", ""},
        /*49*/    {"Server", "HTTP Error, cannot process response message", "", ""},
        /*50*/    {"Server", "Unnknown HTTP response, cannot process response message", "", ""},
        /*51*/    {"Server", "Http transport exception", "", ""},
        /*52*/    {"Server", "Unexpected string", "", ""},
        /*53*/    {"Server", "Cannot initialize a channel to the remote end", "", ""},
        /*54*/    {"Server", "Sockets error Couldn't create socket", "", ""},
        /*55*/    {"Server", "Cannot open a channel to the remote end, shutting down the channel", "", ""},
        /*56*/    {"Server", "Invalid socket. Socket may not be open", "", ""},
        /*57*/    {"Server", "Output streaming error on Channel while writing data", "", ""},
        /*58*/    {"Server", "Input streaming error while getting data", "", ""},
        /*59*/    {"Server", "Channel error while waiting for timeout", "", ""},
        /*60*/    {"Server", "Channel error connection timeout before receving", "", ""},
        /*61*/    {"Server", "Loading SSL channel failed", "", ""},
        /*62*/    {"Server", "Loading channel failed", "", ""},
        /*63*/    {"Server", "Transport buffer is empty", "", ""},
        /*64*/    {"Server", "Buffer received from the parser is empty", "", ""},
        /*65*/    {"Server", "XML_STATUS_ERROR thrown from parser", "", ""},
        /*66*/    {"Server", "Error when getting the byte stream from the transport", "", ""},
        /*67*/    {"Server", "Test exception", "", ""},
        /*68*/    {"Server", "Unknown exception", "", ""},
        /*69*/    {"Server", "Server and Client engines mismatch", "", ""},
            
        /*70*/    {"AXISC", "Service thrown exception", "", ""},
        /*71*/    {"AXISC", "Unknown element exception", "", ""},
        /*72*/    {"AXISC", "Node value mismatch exception", "", ""},
        /*73*/    {"AXISC", "Configuration read exception", "", ""}
        };
        s_parrSoapFaultStruct = s_arrLocalFaultStruct;
        m_bInit = true;
    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "initialize", NULL, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

/*the caller of the SoapFault::getSoapFault(int) has to delete the 
 * returned SoapFault pointer
 */

SoapFault* SoapFault::getSoapFault(int iFaultCode)
{
//	#ifdef ENABLE_AXISTRACE
//		if (axiscpp::AxisTrace::isTraceOn())
//			axiscpp::AxisTrace::traceEntry("SoapFault", "getSoapFault", NULL, 1,
//					TRACETYPE_INT, 0, ((void*)&iFaultCode));	  /* AUTOINSERTED TRACE */
//	#endif
//   
//    SoapFault* pSoapFault= NULL;
//    // fill the soap fault object 
//    pSoapFault= new SoapFault();
//        
//    /* TODO *********************************************** */
//    /* the soap envelope namespace prefix to be obtained from 
//     * gs_SoapEnvVersionsStruct should depend on the relevant SOAP VERSION
//     */
//     string strFaultcode = s_parrSoapFaultStruct[iFaultCode].pcFaultcode;
//     string strSoapEnvVerStruct = gs_SoapEnvVersionsStruct[SOAP_VER_1_1].pchPrefix;
//     pSoapFault->setFaultcode((strSoapEnvVerStruct + ":" + strFaultcode).c_str());
//     pSoapFault->setFaultstring(s_parrSoapFaultStruct[iFaultCode].pcFaultstring);
//     /* Fault actor should be set to the node url in which Axis C++ running.
//      * Currently it is hardcoded to localhost
//      */
//    char* pcNodeName = g_pConfig->getAxisConfProperty(AXCONF_NODENAME);
//    char* pcPort = g_pConfig->getAxisConfProperty(AXCONF_LISTENPORT);
//    string strUrl = pcNodeName;
//    strUrl += ":";
//    strUrl += string(pcPort);
//    pSoapFault->setFaultactor(strUrl.c_str());			 
//    pSoapFault->setFaultDetail(s_parrSoapFaultStruct[iFaultCode].pcFaultDetail);
//    
//	{
//		#ifdef ENABLE_AXISTRACE
//			SoapFault* traceRet = (pSoapFault);
//			if (axiscpp::AxisTrace::isTraceOn())
//				axiscpp::AxisTrace::traceExit("SoapFault", "getSoapFault", NULL, 0,
//					TRACETYPE_POINTER, sizeof(SoapFault), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
//			return traceRet;
//		#else
//			return pSoapFault;
//		#endif
//	}
return NULL;
}

SoapFault::SoapFault(string sFaultcode, string sFaultstring, string sFaultactor, string sDetail) 
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapFault", "SoapFault", this, 4,
					TRACETYPE_STLSTRING, 0, ((void*)&sFaultcode),
					TRACETYPE_STLSTRING, 0, ((void*)&sFaultstring),
					TRACETYPE_STLSTRING, 0, ((void*)&sFaultactor),
					TRACETYPE_STLSTRING, 0, ((void*)&sDetail));	  /* AUTOINSERTED TRACE */
	#endif

    m_sFaultcode= sFaultcode;
    m_sFaultstring= sFaultstring;
    m_sFaultactor= sFaultactor;
    m_sFaultDetail= sDetail;    
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "SoapFault", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

int SoapFault::setParam(Param* pParam, const AxisChar* pchName, const void* pValue, XSDTYPE type)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapFault", "setParam", this, 4,
					TRACETYPE_POINTER, sizeof(Param), ((void*)&pParam),
					TRACETYPE_STRING, 0, ((void*)&pchName),
					TRACETYPE_POINTER, 1, ((void*)&pValue),
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&type));	  /* AUTOINSERTED TRACE */
	#endif

    if (!pParam) 	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "setParam", this, 1,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}

    pParam->m_sName = pchName;
    pParam->setValue( type , (IAnySimpleType*) pValue);
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "setParam", this, 2,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

int SoapFault::setFaultcode(const AxisChar* sFaultcode)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapFault", "setFaultcode", this, 1,
					TRACETYPE_STRING, 0, ((void*)&sFaultcode));	  /* AUTOINSERTED TRACE */
	#endif

    m_pFaultcodeParam = new Param();
	setParam(m_pFaultcodeParam, "faultcode", new String((xsd__string)sFaultcode), XSD_STRING); 
    m_sFaultcode= sFaultcode;
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "setFaultcode", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

int SoapFault::setFaultstring(const AxisChar* sFaultstring)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapFault", "setFaultstring", this, 1,
					TRACETYPE_STRING, 0, ((void*)&sFaultstring));	  /* AUTOINSERTED TRACE */
	#endif

    m_pFaultstringParam = new Param();
    setParam(m_pFaultstringParam, "faultstring", new String((xsd__string)sFaultstring), XSD_STRING); 
    m_sFaultstring= sFaultstring;
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "setFaultstring", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

int SoapFault::setFaultactor(const AxisChar* sFaultactor)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapFault", "setFaultactor", this, 1,
					TRACETYPE_STRING, 0, ((void*)&sFaultactor));	  /* AUTOINSERTED TRACE */
	#endif

    m_pFaultactorParam = new Param();
    setParam(m_pFaultactorParam, "faultactor", new String((xsd__string)sFaultactor), XSD_STRING); 
    m_sFaultactor = sFaultactor;
    
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "setFaultactor", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

int SoapFault::setFaultDetail(const AxisChar* sFaultDetail)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapFault", "setFaultDetail", this, 1,
					TRACETYPE_STRING, 0, ((void*)&sFaultDetail));	  /* AUTOINSERTED TRACE */
	#endif

    m_pFaultDetail = new Param();
    setParam(m_pFaultDetail, "appSpecific", new String((xsd__string)sFaultDetail), XSD_STRING);
    m_sFaultDetail = sFaultDetail;
    m_bIsSimpleDetail = true;
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "setFaultDetail", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

int SoapFault::setFaultDetail(const Param* pFaultDetail)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapFault", "setFaultDetail", this, 1,
					TRACETYPE_POINTER, sizeof(Param), ((void*)&pFaultDetail));	  /* AUTOINSERTED TRACE */
	#endif

    m_pFaultDetail = (Param*) pFaultDetail;
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "setFaultDetail", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

int SoapFault::setCmplxFaultObjectName(const string& sCmplxFaultObjectName)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapFault", "setCmplxFaultObjectName", this, 1,
					TRACETYPE_STLSTRING, 0, ((void*)&sCmplxFaultObjectName));	  /* AUTOINSERTED TRACE */
	#endif

    m_sCmplxFaultObjectName = sCmplxFaultObjectName;
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "setCmplxFaultObjectName", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

int SoapFault::setCmplxFaultObject(const void* pCmplxFaultObject)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapFault", "setCmplxFaultObject", this, 1,
					TRACETYPE_POINTER, 1, ((void*)&pCmplxFaultObject));	  /* AUTOINSERTED TRACE */
	#endif

    m_pCmplxFaultObject = pCmplxFaultObject;
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "setCmplxFaultObject", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

void SoapFault::setPrefix(const AxisChar* prefix)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapFault", "setPrefix", this, 1,
					TRACETYPE_STRING, 0, ((void*)&prefix));	  /* AUTOINSERTED TRACE */
	#endif

    m_strPrefix = prefix;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "setPrefix", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

void SoapFault::setLocalName(const AxisChar* localname)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapFault", "setLocalName", this, 1,
					TRACETYPE_STRING, 0, ((void*)&localname));	  /* AUTOINSERTED TRACE */
	#endif

    m_strLocalname = localname;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "setLocalName", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

void SoapFault::setURI(const AxisChar* uri)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapFault", "setURI", this, 1,
					TRACETYPE_STRING, 0, ((void*)&uri));	  /* AUTOINSERTED TRACE */
	#endif

    m_strUri = uri;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "setURI", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

void SoapFault::setDeSerializer(SoapDeSerializer* pDZ)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapFault", "setDeSerializer", this, 1,
					TRACETYPE_POINTER, sizeof(SoapDeSerializer), ((void*)&pDZ));	  /* AUTOINSERTED TRACE */
	#endif

    m_pDZ = pDZ;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "setDeSerializer", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

const char* SoapFault::getSoapString()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapFault", "getSoapString", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			const char* traceRet = (m_sFaultstring.c_str());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "getSoapString", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_sFaultstring.c_str();
		#endif
	}
 
}

const AxisChar* SoapFault::getFaultcode()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapFault", "getFaultcode", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (m_sFaultcode.c_str());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "getFaultcode", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_sFaultcode.c_str();
		#endif
	}

}

const AxisChar* SoapFault::getFaultstring()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapFault", "getFaultstring", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (m_sFaultstring.c_str());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "getFaultstring", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_sFaultstring.c_str();
		#endif
	}

}

const AxisChar* SoapFault::getFaultactor()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapFault", "getFaultactor", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (m_sFaultactor.c_str());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "getFaultactor", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_sFaultactor.c_str();
		#endif
	}

}

const AxisChar* SoapFault::getSimpleFaultDetail()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapFault", "getSimpleFaultDetail", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (m_sFaultDetail.c_str());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "getSimpleFaultDetail", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_sFaultDetail.c_str();
		#endif
	}

}

const AxisChar* SoapFault::getCmplxFaultObjectName()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapFault", "getCmplxFaultObjectName", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (m_sCmplxFaultObjectName.c_str());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "getCmplxFaultObjectName", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_sCmplxFaultObjectName.c_str();
		#endif
	}

}

void* SoapFault::getCmplxFaultObject(void* pDZFunct, void* pCreFunct, void* pDelFunct,
        const AxisChar* pName, const AxisChar* pNamespace)
{
//	#ifdef ENABLE_AXISTRACE
//		if (axiscpp::AxisTrace::isTraceOn())
//			axiscpp::AxisTrace::traceEntry("SoapFault", "getCmplxFaultObject", this, 5,
//					TRACETYPE_POINTER, 1, ((void*)&pDZFunct),
//					TRACETYPE_POINTER, 1, ((void*)&pCreFunct),
//					TRACETYPE_POINTER, 1, ((void*)&pDelFunct),
//					TRACETYPE_STRING, 0, ((void*)&pName),
//					TRACETYPE_STRING, 0, ((void*)&pNamespace));	  /* AUTOINSERTED TRACE */
//	#endif
// 
//    	{
//		#ifdef ENABLE_AXISTRACE
//			void* traceRet = (m_pDZ->getCmplxFaultObject (pDZFunct, pCreFunct, pDelFunct, pName,
//        pNamespace));
//			if (axiscpp::AxisTrace::isTraceOn())
//				axiscpp::AxisTrace::traceExit("SoapFault", "getCmplxFaultObject", this, 0,
//					TRACETYPE_POINTER, 1, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
//			return traceRet;
//		#else
//			return m_pDZ->getCmplxFaultObject (pDZFunct, pCreFunct, pDelFunct, pName,
//        pNamespace);
//		#endif
//	}
return NULL;
}

const void* SoapFault::getCmplxFaultObject()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapFault", "getCmplxFaultObject", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

		{
		#ifdef ENABLE_AXISTRACE
			const void* traceRet = (m_pCmplxFaultObject);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "getCmplxFaultObject", this, 0,
					TRACETYPE_POINTER, 1, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_pCmplxFaultObject;
		#endif
	}

}

bool SoapFault::operator ==(const SoapFault &objSoapFault)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapFault", "operator==", this, 1,
					TRACETYPE_DATA, sizeof(SoapFault&), ((void*)&objSoapFault));	  /* AUTOINSERTED TRACE */
	#endif

    if ((m_sFaultcode == objSoapFault.m_sFaultcode) &&
        (m_sFaultstring == objSoapFault.m_sFaultstring) &&
        (m_sFaultactor == objSoapFault.m_sFaultactor) &&
        (m_sFaultDetail == objSoapFault.m_sFaultDetail))
    {
        	{
		#ifdef ENABLE_AXISTRACE
			bool traceRet = (true);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "operator==", this, 1,
					TRACETYPE_BOOL, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return true;
		#endif
	}

    }
    	{
		#ifdef ENABLE_AXISTRACE
			bool traceRet = (false);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapFault", "operator==", this, 2,
					TRACETYPE_BOOL, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return false;
		#endif
	}

}

