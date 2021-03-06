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

#if !defined(_SOAPSERIALIZER_H____OF_AXIS_INCLUDED_)

#define _SOAPSERIALIZER_H____OF_AXIS_INCLUDED_

#include <axis/IHandlerSoapSerializer.hpp>

#include "../transport/SOAPTransport.h"

#include "../common/BasicTypeSerializer.h"

#include "../common/Param.h"

#include "../common/AxisUtils.h"

#include <axis/WSDDDefines.hpp>

#include <axis/IAttribute.hpp>

//#include "SoapAttachment.hpp"

#include <stdarg.h>

#include <cctype>

class SoapEnvelope;

class SoapHeader;

class SoapMethod;

class SoapBody;

class SoapFault;

class HeaderBlock;

//class ArrayBean;

class Attribute;

//class ISoapAttachment;

//class SoapAttachmentReference;

/**
 *  @class SoapSerializer
 *  @brief interface for the SoapSerializer class.
 *
 *
 *
 *  @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
 *  @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 */
class SoapSerializer //: public IHandlerSoapSerializer
{

private:
//	map<AxisString, ISoapAttachment*> m_SoapAttachments;
//	list<SoapAttachmentReference*> m_attachmentRefs;
    int m_nCounter;
    AxisChar m_Buf[32];
    SoapEnvelope* m_pSoapEnvelope;    	
    int m_iSoapVersion;
    /* Current Serialization Style */
    AXIS_BINDING_STYLE m_nStyle;
    /* Overall status of Serializer. If anything goes wrong this is not 
     * AXIS_SUCCESS 
     */
    int m_nStatus;
    /* Map that contains pairs of currently available namespaces and 
     * prefixes 
     */ 
    map<AxisXMLString, AxisXMLString> m_NsStack;
    /* Provider type of current service that uses this Serializer object */
    PROVIDERTYPE m_ProviderType;
	/* the local namespace for this serializer */
    AxisChar* m_pNamespace;
//	ContentIdSet *m_pContentIdSet;
//
public:
	inline const AxisChar* AXISCALL getNamespace() const {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "getNamespace", NULL, 0);	  /* AUTOINSERTED TRACE */
	#endif
	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (m_pNamespace);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "getNamespace", NULL, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_pNamespace;
		#endif
	}
}; 
	inline void AXISCALL setNamespace(const AxisChar* pNamespace) {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "setNamespace", NULL, 1,
					TRACETYPE_STRING, 0, ((void*)&pNamespace));	  /* AUTOINSERTED TRACE */
	#endif
m_pNamespace = (const_cast<AxisChar*>(pNamespace));	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "setNamespace", NULL, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}; 
#ifdef UNIT_TESTING_ON
    int setOutputStreamForTesting(SOAPTransport* pStream);

#endif
	//isResponse is true identify that it is a Response method  llh
    int AXISCALL createSoapMethod(const AxisChar* sLocalName, 
        const AxisChar* sURI,bool isResponse);
//    int AXISCALL createSoapFault(const AxisChar* sLocalName, 
//        const AxisChar* sURI, const AxisChar* sFaultCode,
//	const AxisChar* sFaultString);

/*    IWrapperSoapSerializer& operator<<(const char* cSerialized); llh*/
    SoapSerializer& operator<<(const AxisChar* cSerialized);
    /**
     * Returns the corrosponding namespace prefix.
     * @param pNamespace The namespace.
     * @return The corrosponding prefix.
     */
    const AxisChar* AXISCALL getNamespacePrefix(const AxisChar* pNamespace);
    /**
     * Returns the corrosponding namespace prefix. This method is 
     * called when the caller also wants to know whether this is a new 
     * namespace or not as appose to its overloaded other member.
     * @param pNamespace The namespace.
     * @param blnIsNewPrefix The boolean which behaves as 
     * a out parameter to indicate whether this is a new namespace or not.
     * @return The corrosponding prefix.
     */
    const AxisChar* AXISCALL getNamespacePrefix(const AxisChar* pNamespace,
        bool& blnIsNewPrefix);
    void AXISCALL removeNamespacePrefix(const AxisChar* pNamespace);
//    int setSoapVersion(SOAP_VERSION);
    int init();
    int setOutputStream(SoapTransport* pStream);
//    void markEndOfStream();
    int setSoapMethod(SoapMethod* pSoapMethod);
    int setSoapFault(SoapFault* pSoapFault);
    int setSoapBody(SoapBody* pSoapBody);
    int setSoapEnvelope(SoapEnvelope* pSoapEnvelope);
    SoapSerializer();
    virtual ~SoapSerializer();
//    /* for arrays of basic types */
//    int AXISCALL addOutputBasicArrayParam(const Axis_Array* pArray, 
//        XSDTYPE nType, const AxisChar* pName);
//    /* for arrays of complex types */
//    int AXISCALL addOutputCmplxArrayParam(const Axis_Array* pArray, 
//        void* pSZFunct, void* pDelFunct, void* pSizeFunct, 
//        const AxisChar* pName, const AxisChar* pNamespace);
//    /* for complex types */
    int AXISCALL addOutputCmplxParam(void* pObject, void* pSZFunct, 
        void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace);
    int AXISCALL addFaultDetail(void* pObject, void* pSZFunct,
        void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace );
//    int AXISCALL serializeCmplxArray(const Axis_Array* pArray, void* pSZFunct,
//        void* pDelFunct, void* pSizeFunct, const AxisChar* pName, 
//        const AxisChar* pNamespace);
//    int AXISCALL serializeBasicArray(const Axis_Array* pArray, XSDTYPE nType, 
//        const AxisChar* pName);
//	
//    int AXISCALL serializeBasicArray(const Axis_Array* pArray, const AxisChar* pNamespace,
//		XSDTYPE nType, const AxisChar* pName);
    /* following two functions are needed by serializer functions of complex 
     * types for RPC style web services 
     */
    void AXISCALL serializeStartElementOfType(const AxisChar* pName, 
        const AxisChar* pNamespace, const AxisChar* pPrefix);
    void AXISCALL serializeEndElementOfType(const AxisChar* pName);
    PROVIDERTYPE getCurrentProviderType() {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "getCurrentProviderType", NULL, 0);	  /* AUTOINSERTED TRACE */
	#endif
 	{
		#ifdef ENABLE_AXISTRACE
			PROVIDERTYPE traceRet = (m_ProviderType);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "getCurrentProviderType", NULL, 0,
					TRACETYPE_DATA, sizeof(PROVIDERTYPE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_ProviderType;
		#endif
	}
};
    void setCurrentProviderType(PROVIDERTYPE nType) {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "setCurrentProviderType", NULL, 1,
					TRACETYPE_DATA, sizeof(PROVIDERTYPE), ((void*)&nType));	  /* AUTOINSERTED TRACE */
	#endif
 m_ProviderType = nType;	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "setCurrentProviderType", NULL, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
};

private:
//    ArrayBean* makeArrayBean(XSDTYPE nType, void** pArray);
//    ArrayBean* makeArrayBean(void** pObject, void* pSZFunct, void* pDelFunct, 
//        void* pSizeFunct);
    int setSoapHeader(SoapHeader* pSoapHeader);
//
public: /* Basic Type Serializing methods */
    int removeSoapHeader();
    int setHeaderBlock(HeaderBlock* pHeaderBlock);
    IHeaderBlock* createHeaderBlock();
//    
private:
//	bool checkAttachmentAvailability();
//	void serializeAttachments(SoapSerializer &pSZ);
    BasicTypeSerializer m_BTSZ;
    SoapTransport* m_pOutputStream;
//
public:
	IHeaderBlock* getCurrentHeaderBlock();
//	ISoapAttachment* createSoapAttachment();
	void addNamespaceToNamespaceList(const AxisChar *pachNamespaceURI, const AxisChar* pachPrefix);
	void addNamespaceToEnvelope(AxisChar *pachNamespaceURI, AxisChar* pachPrefix);
//	void addAttachmentBody(const AxisChar* achId, xsd__base64Binary* pAttchBody);
//	void addAttachmentHeader(const AxisChar* achId, const AxisChar* achHeaderName, const AxisChar* achHeaderValue);
//	void addAttachment(const AxisChar* achId, ISoapAttachment* pAttach);
//    void addAttachments(ISoapAttachment** pAttach, int iAttchArraySize);
//	void setContentIdSet(ContentIdSet *pContentIdSet);
//	void addAttachmentParameter(ISoapAttachment* att, const char* pName, IAttribute **attributes, int nAttributes);
	IHeaderBlock* getHeaderBlock(const AxisChar* pcName, const AxisChar* pcNamespace);
	/*
	* TODO: Have to remove this method. Date logged 13Jan2005
	IHeaderBlock* getHeaderBlock();
	*/
	IHeaderBlock* getFirstHeaderBlock();
	IHeaderBlock* getNextHeaderBlock();
	int setSOAPMethodAttribute(Attribute* pAttribute);
	SoapMethod* getSOAPMethod();
    IHeaderBlock* createHeaderBlock(const AxisChar *pachLocalName,
        const AxisChar *pachUri);
//    /* to add a header block to the Serializer. Probably by a handler */
    int AXISCALL addHeaderBlock(IHeaderBlock* pBlk);
    int AXISCALL addOutputParam(const AxisChar* pchName, 
        void* pValue, XSDTYPE type);
    int AXISCALL serializeAsElement(const AxisChar* pchName, 
                                    void* pValue,
                                    XSDTYPE type);
    int AXISCALL serializeAsElement(const AxisChar* pchName,
                                    const AxisChar* pNamespace,
                                    void* pValue,
                                    XSDTYPE type);
    int AXISCALL serializeAsElement(const AxisChar* pchName,
                                    IAnySimpleType* pSimpleType);
	int AXISCALL serializeAsElement(const AxisChar* pchName,
                                    const AxisChar* pNamespace,
                                    IAnySimpleType* pSimpleType);
    int AXISCALL serializeAsAttribute(const AxisChar* pName,
                                      const AxisChar* pNamespace,
                                      void* pValue,
                                      XSDTYPE type);
    int AXISCALL serializeAsAttribute(const AxisChar* pName,
                                      const AxisChar* pNamespace,
                                      IAnySimpleType* pSimpleType);
    void AXISCALL serializeVargs(int count, const char** args);
    void AXISCALL serialize(const char* pFirst, ...);
    void setStyle(AXIS_BINDING_STYLE nStyle)
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "setStyle", NULL, 1,
					TRACETYPE_DATA, sizeof(AXIS_BINDING_STYLE), ((void*)&nStyle));	  /* AUTOINSERTED TRACE */
	#endif
 m_nStyle = nStyle; m_BTSZ.setStyle(nStyle);	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "setStyle", NULL, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
};
    AXIS_BINDING_STYLE getStyle(){
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapSerializer", "getStyle", NULL, 0);	  /* AUTOINSERTED TRACE */
	#endif
	{
		#ifdef ENABLE_AXISTRACE
			AXIS_BINDING_STYLE traceRet = (m_nStyle);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapSerializer", "getStyle", NULL, 0,
					TRACETYPE_DATA, sizeof(AXIS_BINDING_STYLE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_nStyle;
		#endif
	}
};
    int AXISCALL setBodyAsHexBinary(xsd__hexBinary body);
    int AXISCALL setBodyAsBase64Binary(xsd__base64Binary body);
    const AxisChar* AXISCALL getBodyAsString();
	int addOutputAnyObject(AnyType* pAnyObject);
	int serializeAnyObject(AnyType* pAnyObject);
    int serializeAsChardata(void* pValue, XSDTYPE type);
	AxisXMLString getNamespaceURL( string sNameSpace);
    int deleteHeaderBlock(const AxisChar* pName, const AxisChar* pNamespace);    
  /**
    * This methos will clear up all the current out params in preperation of a 
    * new method call
    */
    void reset();

};

#endif 

