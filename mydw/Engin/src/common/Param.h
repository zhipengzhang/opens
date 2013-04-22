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

#ifdef WIN32

#pragma warning (disable : 4786)

#endif

#if !defined(_PARAM_H____OF_AXIS_INCLUDED_)

#define _PARAM_H____OF_AXIS_INCLUDED_

#include "ComplexObjectHandler.h"

#include "../soap/SoapSerializer.h"

#include "../platforms/PlatformAutoSense.hpp"

#include "../soap/xsd/IAnySimpleType.hpp"

//class ArrayBean;

//class SoapAttachmentReference;

class ParamValue
{

public:
//    ArrayBean* pArray; /* this is used to hold arrays */暂不支持数组
    ComplexObjectHandler* pCplxObj;
    AnyType* pAnyObject; /* used to hold AnyType struct for xsd:any */
//	SoapAttachmentReference* pAttachmentRef;暂不支持Attachment

/*
	virtual ~ParamValue(){
		if(pCplxObj)
			delete pCplxObj;
		if(pAnyObject)
			delete pAnyObject;
	}*/

};

/*
 *  @class Param
 *  @brief interface for the Param class.
 *
 *
 *  @author Susantha Kumara (skumara@virtusa.com)
 */

class Param
{
    friend class SoapSerializer;
    friend class SoapFault;
	friend class SoapParser;
	friend class SoapMethod;

public:
    Param(){
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Param", "Param", NULL, 0);	  /* AUTOINSERTED TRACE */
	#endif
		m_Type = USER_TYPE; 
		m_AnySimpleType = NULL;	
		{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Param", "Param", NULL, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}; 
    /* if there is no attribute that says the type */
//    virtual ~Param();
public:
	ParamValue m_Value;
private:
    
    AxisString m_sName; /* Name of the parameter */
    XSDTYPE m_Type; /* Type of the parameter */
    AxisString m_strPrefix; /* needed in serialization only */
    AxisString m_strUri; /* needed in serialization only */
    IAnySimpleType* m_AnySimpleType;

public: 
	
    void setValue(XSDTYPE nType, IAnySimpleType* value);
    int serialize(SoapSerializer& pSZ);
    void setPrefix(const AxisChar* prefix);
    void setURI(const AxisChar* uri);
//    int setArrayElements(void* pElements);
//    int setArrayElements(void* pObject, AXIS_DESERIALIZE_FUNCT pDZFunct, 
//        AXIS_OBJECT_DELETE_FUNCT pDelFunct, AXIS_OBJECT_SIZE_FUNCT pSizeFunct);
    int setUserType(void* pObject, AXIS_DESERIALIZE_FUNCT pDZFunct, 
        AXIS_OBJECT_DELETE_FUNCT pDelFunct);
    void setName(const AxisChar* sName);

};

#endif 

