#ifdef ENABLE_AXISTRACE
/* TRACE ADDED BY THE TRACE INSTRUMENTOR TOOL */
#include "../common/AxisTrace.h"
#endif
/* -*- C++ -*- */

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
 *
 *
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */

#include <axis/AxisUserAPI.hpp>

//#include "../engine/AxisEngine.h"

#include "Param.h"

//#include "ArrayBean.h"

//#include "BasicTypeSerializer.h"

//#include "AxisUtils.h"

//#include "AxisTrace.h"

//#include "../soap/SoapAttachmentReference.hpp"

#include <stdlib.h>

#include <stdio.h>

//int AxisEngine::m_bServer;

int defSerMethod(void* rs, SoapSerializer *serializer, bool bArray){
	serializer->serialize(">\r\n",NULL);

	return AXIS_SUCCESS;
}

//Param::~Param ()
//{
//	#ifdef ENABLE_AXISTRACE
//		if (axiscpp::AxisTrace::isTraceOn())
//			axiscpp::AxisTrace::traceEntry("Param", "~Param", this, 0);	  /* AUTOINSERTED TRACE */
//	#endif
//
//    if (m_AnySimpleType)
//    {
//        delete m_AnySimpleType;
//        m_AnySimpleType = NULL;
//    }
//    
//    switch (m_Type)
//    {
////llh        case XSD_ARRAY:
////            if (m_Value.pArray)
////                delete m_Value.pArray;
////            break;
//        case USER_TYPE:
//			if(m_Value.pCplxObj)
//            delete m_Value.pCplxObj;
//			m_Value.pCplxObj=NULL;
//            break;
//        case XSD_ANY:
//			// Do not delete the m_Value.pAnyObject here because it is the
//			// application's storage. The AnyObject has never been cloned.
//            break;
//        default:;
//    }
//	{
//		#ifdef ENABLE_AXISTRACE
//			if (axiscpp::AxisTrace::isTraceOn())
//				axiscpp::AxisTrace::traceExit("Param", "~Param", this, 0);	  /* AUTOINSERTED TRACE */
//		#endif
//		return;
//	}
//}

int Param::serialize (SoapSerializer &pSZ)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Param", "serialize", this, 1,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ));	  /* AUTOINSERTED TRACE */
	#endif

    AxisString ATprefix;
    switch (m_Type)
    {
//        case XSD_ARRAY:
//            /* pSZ.serialize("<abc:ArrayOfPhoneNumbers 
//	     * xmlns:abc="http://example.org/2001/06/numbers"
//	     * xmlns:enc="http://www.w3.org/2001/06/soap-encoding" 
//	     * enc:arrayType="abc:phoneNumberType[2]" >";
//	     */
//	    if (!m_Value.pArray)
//                	{
//		#ifdef ENABLE_AXISTRACE
//			int traceRet = (AXIS_FAIL);
//			if (axiscpp::AxisTrace::isTraceOn())
//				axiscpp::AxisTrace::traceExit("Param", "serialize", this, 1,
//					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
//			return traceRet;
//		#else
//			return AXIS_FAIL;
//		#endif
//	}
// // error condition
//            if (RPC_ENCODED == pSZ.getStyle ())
//            {
//                pSZ.serialize ("<", NULL);
//                if (!m_strPrefix.empty ())
//                {
//                    pSZ.serialize (m_strPrefix.c_str (), ":", m_sName.c_str (),
//                        "Array", " xmlns:", m_strPrefix.c_str (), "=\"",
//                        m_strUri.c_str (), "\"", NULL);
//                }
//                else
//                {
//                    pSZ.serialize (m_sName.c_str (), "Array", NULL);
//                }
//                // get a prefix from Serializer
//                ATprefix =
//                    pSZ.getNamespacePrefix (m_Value.pArray->m_URI.c_str ());
//                pSZ.serialize (" xmlns:enc", NULL);
//                pSZ.serialize
//                    ("=\"http://www.w3.org/2001/06/soap-encoding\" ", NULL);
//                if (m_Value.pArray->m_type == USER_TYPE)
//                {
//                    pSZ.serialize ("xmlns:", ATprefix.c_str (), "=\"",
//                        m_Value.pArray->m_URI.c_str (), "\" ", NULL);
//                }
//                pSZ.serialize ("enc:arrayType=\"", NULL);
//                if (m_Value.pArray->m_type == USER_TYPE)
//                {
//                    pSZ.serialize (ATprefix.c_str (), ":",
//                        m_Value.pArray->m_TypeName.c_str (), NULL);
//                }
//                else //basic type array
//                {
//                    pSZ.serialize ("xsd:", BasicTypeSerializer::
//                        basicTypeStr (m_Value.pArray->m_type), NULL);
//                }
//                {
//                    char Buf[10]; //maximum array dimension is 99999999
//                    sprintf (Buf, "[%d]", m_Value.pArray->m_nSize);
//                    pSZ.serialize (Buf, NULL);
//                }
//                pSZ.serialize ("\">\n", NULL);
//                m_Value.pArray->Serialize (pSZ); //Only serializes the inner items
//                pSZ.serialize ("</", NULL);
//                if (!m_strPrefix.empty ())
//                {
//                    pSZ.serialize (m_strPrefix.c_str (), ":", m_sName.c_str (),
//                        "Array", NULL);
//                }
//                else
//                {
//                    pSZ.serialize (m_sName.c_str (), "Array", NULL);
//                }
//                pSZ.removeNamespacePrefix (m_Value.pArray->m_URI.c_str ());
//                pSZ.serialize (">\n", NULL);
//            }
//            else /* no wrapper element in doc/lit style. 
//		  * So directly call Array Serializer 
//		  */
//            {
//				if (!m_strUri.empty())
//					pSZ.setNamespace(m_strUri.c_str());
//                m_Value.pArray->Serialize (pSZ); /* Only serializes the inner 
//						  * items
//						  */ 
//				if (!m_strUri.empty())
//					pSZ.setNamespace(NULL);
//            }
//            break;
        
	case USER_TYPE:
            if (RPC_ENCODED == pSZ.getStyle ())
            {
//				TRACE_SERIALIZE_FUNCT_ENTRY(m_Value.pCplxObj->pSZFunct, m_Value.pCplxObj->pObject, &pSZ, false);
                int stat = AXIS_FAIL;
                stat = m_Value.pCplxObj->pSZFunct (m_Value.pCplxObj->pObject, &pSZ, false);
//				TRACE_SERIALIZE_FUNCT_EXIT(m_Value.pCplxObj->pSZFunct, stat);
            }
            else
            {			
				/*llh 07-05-22 I have add the ns declared */ 
				if(!m_strUri.empty()){
				
					pSZ.serialize("<",m_sName.c_str()," xmlns","=","\"",m_strUri.c_str(),"\"",NULL);
				}
				/*llh 07-05-22*/
				else
                pSZ.serialize ("<",m_sName.c_str (), NULL); 
                /* note : ">" is not serialized to enable the type's serializer
                 * to add attributes 
                 */

                int stat = AXIS_FAIL;
				//set default method if pSZFunct is null 
				if(!m_Value.pCplxObj->pSZFunct)
					m_Value.pCplxObj->pSZFunct=(AXIS_SERIALIZE_FUNCT)(void *)defSerMethod;

                stat = m_Value.pCplxObj->pSZFunct (m_Value.pCplxObj->pObject, &pSZ, false);


				/*llh 07-05-22*/
					/*llh 07-05-22 I have add the ns declared */ 
				if(!m_strUri.empty()){
				//pSZ.serialize("</",m_strPrefix.c_str(),":",m_sName.c_str(),">\r\n",NULL);
				pSZ.serialize("</",m_sName.c_str(),">\r\n",NULL);
				}
				else 
					pSZ.serialize ("</",m_sName.c_str (),">\r\n", NULL); 
				/*llh 07-05-22*/
			
				
            }
            break;
      case XSD_ANY:
             pSZ.serializeAnyObject(m_Value.pAnyObject);
             break;
//      case ATTACHMENT:
//            m_Value.pAttachmentRef->serialize(pSZ,m_sName.c_str());
//            break;
      default:
            pSZ.serializeAsElement((AxisChar*) m_sName.c_str (), (IAnySimpleType*) m_AnySimpleType);
            break;
    }
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Param", "serialize", this, 2,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}
}

void Param::setValue( XSDTYPE nType, IAnySimpleType* value)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Param", "setValue", this, 2,
					TRACETYPE_DATA, sizeof(XSDTYPE), ((void*)&nType),
					TRACETYPE_POINTER, sizeof(IAnySimpleType), ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    m_Type = nType;
    m_AnySimpleType = value;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Param", "setValue", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

void Param::setPrefix (const AxisChar* prefix)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Param", "setPrefix", this, 1,
					TRACETYPE_STRING, 0, ((void*)&prefix));	  /* AUTOINSERTED TRACE */
	#endif

    m_strPrefix = prefix;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Param", "setPrefix", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

void Param::setURI (const AxisChar* uri)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Param", "setURI", this, 1,
					TRACETYPE_STRING, 0, ((void*)&uri));	  /* AUTOINSERTED TRACE */
	#endif

    m_strUri = uri;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Param", "setURI", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

int Param::setUserType (void* pObject, AXIS_DESERIALIZE_FUNCT pDZFunct,
    AXIS_OBJECT_DELETE_FUNCT pDelFunct)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Param", "setUserType", this, 3,
					TRACETYPE_POINTER, 1, ((void*)&pObject),
					TRACETYPE_DATA, sizeof(AXIS_DESERIALIZE_FUNCT), ((void*)&pDZFunct),
					TRACETYPE_DATA, sizeof(AXIS_OBJECT_DELETE_FUNCT), ((void*)&pDelFunct));	  /* AUTOINSERTED TRACE */
	#endif

    if (m_Type != USER_TYPE)
    {
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Param", "setUserType", this, 1,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}

    m_Value.pCplxObj = new ComplexObjectHandler;
    m_Value.pCplxObj->pObject = pObject;
    m_Value.pCplxObj->pDZFunct = pDZFunct;
    m_Value.pCplxObj->pDelFunct = pDelFunct;
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Param", "setUserType", this, 2,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

/*
int Param::setArrayElements (void* pElements)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Param", "setArrayElements", this, 1,
					TRACETYPE_POINTER, 1, ((void*)&pElements));	  / * AUTOINSERTED TRACE * /
	#endif

    if (m_Type != XSD_ARRAY)
        	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Param", "setArrayElements", this, 1,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  / * AUTOINSERTED TRACE * /
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}

    if (m_Value.pArray)
    {
        if (m_Value.pArray->m_type != USER_TYPE)
        {
            m_Value.pArray->m_value.sta = pElements;
            	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Param", "setArrayElements", this, 2,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  / * AUTOINSERTED TRACE * /
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

        }
        else // unexpected situation
        {
            	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Param", "setArrayElements", this, 3,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  / * AUTOINSERTED TRACE * /
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}

        }
    }
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Param", "setArrayElements", this, 4,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  / * AUTOINSERTED TRACE * /
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}
//	return 0;
}*/


// following function is called to set array of user types.

/*
int Param::setArrayElements (void* pObject, AXIS_DESERIALIZE_FUNCT pDZFunct,
    AXIS_OBJECT_DELETE_FUNCT pDelFunct, AXIS_OBJECT_SIZE_FUNCT pSizeFunct)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Param", "setArrayElements", this, 4,
					TRACETYPE_POINTER, 1, ((void*)&pObject),
					TRACETYPE_DATA, sizeof(AXIS_DESERIALIZE_FUNCT), ((void*)&pDZFunct),
					TRACETYPE_DATA, sizeof(AXIS_OBJECT_DELETE_FUNCT), ((void*)&pDelFunct),
					TRACETYPE_DATA, sizeof(AXIS_OBJECT_SIZE_FUNCT), ((void*)&pSizeFunct));	  / * AUTOINSERTED TRACE * /
	#endif

    if (m_Type != XSD_ARRAY)
        	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Param", "setArrayElements", this, 1,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  / * AUTOINSERTED TRACE * /
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}

    if (m_Value.pArray)
    {
        if (m_Value.pArray->m_type == USER_TYPE)
        {
            m_Value.pArray->m_value.cta = new ComplexObjectHandler;
            m_Value.pArray->m_value.cta->pDZFunct = pDZFunct;
            m_Value.pArray->m_value.cta->pDelFunct = pDelFunct;
            m_Value.pArray->m_value.cta->pSizeFunct = pSizeFunct;
            m_Value.pArray->m_value.cta->pObject = pObject;
            	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Param", "setArrayElements", this, 2,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  / * AUTOINSERTED TRACE * /
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

        }
        else                  //unexpected situation
        {
            	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Param", "setArrayElements", this, 3,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  / * AUTOINSERTED TRACE * /
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}

        }
    }
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Param", "setArrayElements", this, 4,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  / * AUTOINSERTED TRACE * /
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}
//return 0;
}*/


void Param::setName (const AxisChar* sName)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Param", "setName", this, 1,
					TRACETYPE_STRING, 0, ((void*)&sName));	  /* AUTOINSERTED TRACE */
	#endif

    m_sName = sName;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Param", "setName", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

// ComplexObjectHandler functions

ComplexObjectHandler::ComplexObjectHandler ()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexObjectHandler", "ComplexObjectHandler", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    init ();
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexObjectHandler", "ComplexObjectHandler", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

ComplexObjectHandler::~ComplexObjectHandler ()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexObjectHandler", "~ComplexObjectHandler", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    /* At client side we do not delete either output or return objects */
//llh    if (AxisEngine::m_bServer)
//    {
        if (pObject && pDelFunct)
		{
//			TRACE_OBJECT_DELETE_FUNCT_ENTRY(pDelFunct, pObject, false, 0);
			pDelFunct(pObject, false, 0);
//			TRACE_OBJECT_DELETE_FUNCT_EXIT(pDelFunct);
		}
//    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexObjectHandler", "~ComplexObjectHandler", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

void ComplexObjectHandler::init ()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexObjectHandler", "init", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    pObject = NULL;
    pSZFunct = NULL;
    pDelFunct = NULL;
    pDZFunct = NULL;
    pSizeFunct = NULL;
    m_TypeName = "";
    m_URI = "";
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexObjectHandler", "init", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

