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
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 *
 *
 *
 * @author Roshan Weerasuriya (roshanw@jkcsworld.com, roshan@opensource.lk)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */

/*
 * Revision 1.1  2004/05/25 samisa
 * Added copy constructure and clone for copy constructing derived classes
 */

/*
 * Revision 1.2  2004/07/01 roshan
 * Added code to addChild(BasicNode *pBasicNode) method to deal with NULL
 *  values.
 */

/* ComplexElement.cpp: implementation of the ComplexElement class. */

#include <axis/GDefine.hpp>

#include "Attribute.h"

#include "ComplexElement.h"

#include "SoapSerializer.h"

ComplexElement::ComplexElement():m_pParent(NULL)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "ComplexElement", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

	m_pachPrefix = NULL;
    m_pachLocalName = NULL;
    m_pachURI = NULL;
    m_iNodeType= ELEMENT_NODE;
    iNoOfChildren = 0;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "ComplexElement", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

ComplexElement::ComplexElement(AxisChar *pachLocalName, AxisChar *pachPrefix,
                               AxisChar *pachUri): m_pParent(NULL)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "ComplexElement", this, 3,
					TRACETYPE_STRING, 0, ((void*)&pachLocalName),
					TRACETYPE_STRING, 0, ((void*)&pachPrefix),
					TRACETYPE_STRING, 0, ((void*)&pachUri));	  /* AUTOINSERTED TRACE */
	#endif

    m_pachLocalName = new AxisChar[strlen(pachLocalName)+1];
    strcpy(m_pachLocalName, pachLocalName);
    m_pachPrefix = new AxisChar[strlen(pachPrefix)+1];
    strcpy(m_pachPrefix, pachPrefix);
    m_pachURI = new AxisChar[strlen(pachUri)+1];
    strcpy(m_pachURI, pachUri);
    m_iNodeType= ELEMENT_NODE;
    iNoOfChildren = 0;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "ComplexElement", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

ComplexElement::ComplexElement(const ComplexElement& rCopy)
:BasicNode(rCopy), m_pachPrefix(NULL), m_pachLocalName(NULL), m_pachURI(NULL), m_pParent(NULL)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "ComplexElement", this, 1,
					TRACETYPE_DATA, sizeof(ComplexElement&), ((void*)&rCopy));	  /* AUTOINSERTED TRACE */
	#endif

    this->iNoOfChildren = rCopy.iNoOfChildren;
    
    list<BasicNode*>::const_iterator itCurrBasicNode= rCopy.m_children.begin();
    while(itCurrBasicNode != rCopy.m_children.end())
    {
        this->m_children.push_back((*itCurrBasicNode)->clone());	
        itCurrBasicNode++;        
    } 
    
    if(rCopy.m_pachPrefix) {
    	  this->m_pachPrefix = new char[strlen(rCopy.m_pachPrefix)+1];
        strcpy(this->m_pachPrefix,rCopy.m_pachPrefix);
    }
    if(rCopy.m_pachLocalName) {
    	  this->m_pachLocalName = new char[strlen(rCopy.m_pachLocalName)+1];
        strcpy(this->m_pachLocalName,rCopy.m_pachLocalName);
    }
    if(rCopy.m_pachURI) {
    	  this->m_pachURI = new char[strlen(rCopy.m_pachURI)+1];
        strcpy(this->m_pachURI,rCopy.m_pachURI);
    }
    this->m_iNodeType= rCopy.m_iNodeType;
    this->iNoOfChildren = rCopy.iNoOfChildren;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "ComplexElement", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

BasicNode* ComplexElement::clone()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "clone", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			BasicNode* traceRet = (new ComplexElement(*this));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "clone", this, 0,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new ComplexElement(*this);
		#endif
	}

}

ComplexElement::~ComplexElement()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "~ComplexElement", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

	if (NULL != m_pachPrefix)
	    delete [] m_pachPrefix;
	m_pachPrefix = NULL;
	if (NULL != m_pachLocalName)
	    delete [] m_pachLocalName;
	m_pachLocalName = NULL;
	if (NULL != m_pachURI)
	    delete [] m_pachURI;
	m_pachURI = NULL;
    m_pParent = NULL;
    /* 
     *Clear the Attributes 
     */
    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();
    while(itCurrAttribute != m_attributes.end())
    {
        delete (*itCurrAttribute);
        itCurrAttribute++;
    }
    m_attributes.clear();
    /* Clear the children */
    list<BasicNode*>::iterator itCurrChild= m_children.begin();
    while(itCurrChild != m_children.end())
    {        
        delete (*itCurrChild);
        itCurrChild++;        
    }
    m_children.clear();
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "~ComplexElement", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

IAttribute* ComplexElement::createAttribute(const AxisChar *localname,
        const AxisChar *prefix,
        const AxisChar *value)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "createAttribute", this, 3,
					TRACETYPE_STRING, 0, ((void*)&localname),
					TRACETYPE_STRING, 0, ((void*)&prefix),
					TRACETYPE_STRING, 0, ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    Attribute* pAttribute = new Attribute(m_attributes, localname, prefix, value);
    m_attributes.push_back(pAttribute);
    
    	{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = ((IAttribute*)pAttribute);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "createAttribute", this, 0,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (IAttribute*)pAttribute;
		#endif
	}

}

IAttribute* ComplexElement::createAttribute(const AxisChar *localname,
        const AxisChar *prefix,
        const AxisChar *uri,
        const AxisChar *value)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "createAttribute", this, 4,
					TRACETYPE_STRING, 0, ((void*)&localname),
					TRACETYPE_STRING, 0, ((void*)&prefix),
					TRACETYPE_STRING, 0, ((void*)&uri),
					TRACETYPE_STRING, 0, ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    Attribute* pAttribute = new Attribute(m_attributes, localname, prefix, uri, value);
    m_attributes.push_back(pAttribute);
   
    	{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = ((IAttribute*)pAttribute);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "createAttribute", this, 0,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (IAttribute*)pAttribute;
		#endif
	}

}

IAttribute* ComplexElement::createAttribute(const AxisChar *localname,
        const AxisChar *value)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "createAttribute", this, 2,
					TRACETYPE_STRING, 0, ((void*)&localname),
					TRACETYPE_STRING, 0, ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    Attribute* pAttribute = new Attribute(m_attributes, localname, "", value);
    m_attributes.push_back(pAttribute);
                                                                                                                                                                            
    	{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = ((IAttribute*)pAttribute);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "createAttribute", this, 0,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (IAttribute*)pAttribute;
		#endif
	}

}

int ComplexElement::setPrefix(const AxisChar* pachPrefix)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "setPrefix", this, 1,
					TRACETYPE_STRING, 0, ((void*)&pachPrefix));	  /* AUTOINSERTED TRACE */
	#endif

	if (NULL==pachPrefix)
			{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "setPrefix", this, 1,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}

	if (NULL != m_pachPrefix) 
		delete [] m_pachPrefix;
    m_pachPrefix = new AxisChar[strlen(pachPrefix)+1];
    strcpy(m_pachPrefix, pachPrefix);
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "setPrefix", this, 2,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

int ComplexElement::setLocalName(const AxisChar* pachLocalName)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "setLocalName", this, 1,
					TRACETYPE_STRING, 0, ((void*)&pachLocalName));	  /* AUTOINSERTED TRACE */
	#endif

	if (NULL==pachLocalName)
			{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "setLocalName", this, 1,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}

	if (NULL != m_pachLocalName) 
		delete [] m_pachLocalName;
    m_pachLocalName = new AxisChar[strlen(pachLocalName)+1];
    strcpy(m_pachLocalName, pachLocalName);
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "setLocalName", this, 2,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

int ComplexElement::addChild(BasicNode *pBasicNode)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "addChild", this, 1,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&pBasicNode));	  /* AUTOINSERTED TRACE */
	#endif

    if (pBasicNode)
    {
        if (pBasicNode->getNodeType() == ELEMENT_NODE)
        {
            ComplexElement *pComplexElement = static_cast<ComplexElement*>(pBasicNode);
            pComplexElement->setParent(this);
        }
        m_children.push_back(pBasicNode);
        iNoOfChildren++;
        	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "addChild", this, 1,
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
				axiscpp::AxisTrace::traceExit("ComplexElement", "addChild", this, 2,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}

    }
}

int ComplexElement::serialize(SoapSerializer& pSZ)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "serialize", this, 1,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ));	  /* AUTOINSERTED TRACE */
	#endif

    int iStatus= AXIS_SUCCESS;
    do
    {
        if(isSerializable()) 
        {    
            pSZ.serialize("<", NULL);    
            if((NULL!=m_pachPrefix) && (strlen(m_pachPrefix)!=0))
            {                
                pSZ.serialize(m_pachPrefix, ":", NULL);
            }
            pSZ.serialize(m_pachLocalName, NULL);
            if ((NULL!=m_pachPrefix) && (strlen(m_pachPrefix)!=0) && 
				(NULL!=m_pachURI) && (strlen(m_pachURI)!=0))
            {
                pSZ.serialize(" xmlns:", m_pachPrefix, "=\"", m_pachURI, "\"",
                    NULL);
            }
            pSZ.serialize(">", NULL);
            iStatus= serializeChildren(pSZ);
            if(iStatus==AXIS_FAIL)
            {
                break;
            }
            pSZ.serialize("</", NULL);
            if((NULL!=m_pachPrefix) && (strlen(m_pachPrefix)!=0))
            {
                pSZ.serialize(m_pachPrefix, ":", NULL);
            }
            pSZ.serialize(m_pachLocalName, ">", NULL);
            iStatus= AXIS_SUCCESS;
        } 
        else
        {
            iStatus= AXIS_FAIL;
        }
    } while(0);    
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (iStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "serialize", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return iStatus;
		#endif
	}

}

int ComplexElement::serialize(SoapSerializer& pSZ,
                              list<AxisChar*>& lstTmpNameSpaceStack)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "serialize", NULL, 2,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ),
					TRACETYPE_DATA, sizeof(list<AxisChar* >&), ((void*)&lstTmpNameSpaceStack));	  /* AUTOINSERTED TRACE */
	#endif

    int iStatus= AXIS_SUCCESS;
    do
    {
        if(isSerializable()) 
        {    
            bool blnIsNewNamespace = false;
            // Check if we have no namespace prefix, but do have a namespace URI
            if ( (m_pachPrefix == NULL || strlen(m_pachPrefix) == 0)
                && (m_pachURI != NULL && strlen(m_pachURI) != 0))
            {
                // Is this a child node?
                if (m_pParent != NULL)
                {
                    // Does the parent uses the same namespace URI?
                    if ( m_pParent->getURI() != NULL 
                        && strlen(m_pParent->getURI()) != 0
                        && strcmp(m_pachURI, m_pParent->getURI()) == 0)
                    {
                        // Does the parent have a namespace prefix?
                        if (m_pParent->getPrefix() != NULL && strlen(m_pParent->getPrefix()) != 0)
                        {
                            setPrefix(m_pParent->getPrefix());
                            setURI("");
                        }
                    }
                }
            }
            
            pSZ.serialize("<", NULL);    
            if( (m_pachPrefix != NULL) && (strlen(m_pachPrefix) != 0))
            {                
                pSZ.serialize(m_pachPrefix, ":", NULL);
                blnIsNewNamespace = true;
            }
            else if ( (m_pachURI != NULL) && (strlen(m_pachURI) != 0))
            {
                const AxisChar* pachTmp = pSZ.getNamespacePrefix(m_pachURI,
                    blnIsNewNamespace);
				if (NULL!=m_pachPrefix)
					delete [] m_pachPrefix;
                m_pachPrefix = new AxisChar[strlen(pachTmp)+1];
                strcpy(m_pachPrefix , pachTmp);
                if (blnIsNewNamespace)
                {
                    lstTmpNameSpaceStack.push_back(m_pachURI);
                }
                pSZ.serialize(m_pachPrefix, ":", NULL);
            }
            pSZ.serialize(m_pachLocalName, NULL);
            if(((m_pachPrefix != NULL) && (strlen(m_pachPrefix) != 0)) && 
                    ( (m_pachURI != NULL) && (strlen(m_pachURI) != 0)) && 
                    (blnIsNewNamespace))
            {
                pSZ.serialize(" xmlns:", m_pachPrefix, "=\"", m_pachURI, "\"",
                    NULL);
            }
	    iStatus= attrSerialize(pSZ, lstTmpNameSpaceStack);
   	    if(iStatus==AXIS_FAIL)
	    {
		break;
	    }
       	    iStatus= serializeNamespaceDecl(pSZ);
 	    if(iStatus==AXIS_FAIL)
	    {
		break;
	    }
            pSZ.serialize(">", NULL);
            iStatus= serializeChildren(pSZ, lstTmpNameSpaceStack);
            if(iStatus==AXIS_FAIL)
            {
                break;
            }
            pSZ.serialize("</", NULL);
            if((m_pachPrefix!=NULL) && (strlen(m_pachPrefix) != 0))
            {
                pSZ.serialize(m_pachPrefix, ":", NULL);
            }
            pSZ.serialize(m_pachLocalName, ">", NULL);
            iStatus= AXIS_SUCCESS;
        } 
        else
        {
            iStatus= AXIS_FAIL;
        }
    } while(0);    
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (iStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "serialize", NULL, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return iStatus;
		#endif
	}

}

int ComplexElement::attrSerialize(SoapSerializer& pSZ,
        list<AxisChar*>& lstTmpNameSpaceStack)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "attrSerialize", NULL, 2,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ),
					TRACETYPE_DATA, sizeof(list<AxisChar* >&), ((void*)&lstTmpNameSpaceStack));	  /* AUTOINSERTED TRACE */
	#endif

    int iStatus= AXIS_SUCCESS;
    
    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();
    while(itCurrAttribute != m_attributes.end())
    {
        iStatus= (*itCurrAttribute)->serialize(pSZ, lstTmpNameSpaceStack);
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
				axiscpp::AxisTrace::traceExit("ComplexElement", "attrSerialize", NULL, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return iStatus;
		#endif
	}

}

int ComplexElement::serializeNamespaceDecl(SoapSerializer &pSZ)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "serializeNamespaceDecl", this, 1,
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
				axiscpp::AxisTrace::traceExit("ComplexElement", "serializeNamespaceDecl", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

bool ComplexElement::isSerializable()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "isSerializable", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    bool bStatus= true;
    do
    {
        if((NULL==m_pachLocalName) || (strlen(m_pachLocalName)==0))
        {
            bStatus= false;
            break;
        }
    }while(0);
    	{
		#ifdef ENABLE_AXISTRACE
			bool traceRet = (bStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "isSerializable", this, 0,
					TRACETYPE_BOOL, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return bStatus;
		#endif
	}

}

int ComplexElement::setURI(const AxisChar* pachURI)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "setURI", this, 1,
					TRACETYPE_STRING, 0, ((void*)&pachURI));	  /* AUTOINSERTED TRACE */
	#endif

	if (NULL!=m_pachURI)
		delete [] m_pachURI;
    m_pachURI = new AxisChar[strlen(pachURI)+1];
    strcpy(m_pachURI, pachURI);
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "setURI", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

void ComplexElement::setParent(ComplexElement *parent)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "setParent", this, 1,
					TRACETYPE_POINTER, sizeof(ComplexElement), ((void*)&parent));	  /* AUTOINSERTED TRACE */
	#endif

    m_pParent = parent;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "setParent", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

int ComplexElement::serializeChildren(SoapSerializer& pSZ)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "serializeChildren", this, 1,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ));	  /* AUTOINSERTED TRACE */
	#endif

    list<BasicNode*>::iterator itCurrBasicNode= m_children.begin();
    while(itCurrBasicNode != m_children.end())
    {
        
        (*itCurrBasicNode)->serialize(pSZ);
        
        itCurrBasicNode++;        
    }    
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "serializeChildren", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

int ComplexElement::serializeChildren(SoapSerializer& pSZ,
                                      list<AxisChar*>& lstTmpNameSpaceStack)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "serializeChildren", NULL, 2,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ),
					TRACETYPE_DATA, sizeof(list<AxisChar* >&), ((void*)&lstTmpNameSpaceStack));	  /* AUTOINSERTED TRACE */
	#endif

    list<BasicNode*>::iterator itCurrBasicNode= m_children.begin();
    while(itCurrBasicNode != m_children.end())
    {
        if ((*itCurrBasicNode)->getNodeType() == ELEMENT_NODE)
        {
            (*itCurrBasicNode)->serialize(pSZ, lstTmpNameSpaceStack);    
        }
        else
        {
            /* for CHARACTER_NODE */
            (*itCurrBasicNode)->serialize(pSZ);
        }
        itCurrBasicNode++;        
    }    
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "serializeChildren", NULL, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

NODE_TYPE ComplexElement::getNodeType() const
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "getNodeType", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			NODE_TYPE traceRet = (m_iNodeType);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getNodeType", this, 0,
					TRACETYPE_DATA, sizeof(NODE_TYPE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_iNodeType;
		#endif
	}

}

BasicNode* ComplexElement::getFirstChild()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "getFirstChild", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    list<BasicNode*>::const_iterator itCurrChild= m_children.begin();
    if (itCurrChild != m_children.end())
    {        
        	{
		#ifdef ENABLE_AXISTRACE
			BasicNode* traceRet = ((*itCurrChild));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getFirstChild", this, 1,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (*itCurrChild);
		#endif
	}

    }    
    	{
		#ifdef ENABLE_AXISTRACE
			BasicNode* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getFirstChild", this, 2,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

}

BasicNode* ComplexElement::getLastChild()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "getLastChild", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    list<BasicNode*>::reverse_iterator ritCurrChild= m_children.rbegin();
    if (ritCurrChild != m_children.rend())
    {        
        	{
		#ifdef ENABLE_AXISTRACE
			BasicNode* traceRet = ((*ritCurrChild));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getLastChild", this, 1,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (*ritCurrChild);
		#endif
	}

    }    
    	{
		#ifdef ENABLE_AXISTRACE
			BasicNode* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getLastChild", this, 2,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

}

BasicNode* ComplexElement::getChild(int iChildPosition)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "getChild", this, 1,
					TRACETYPE_INT, 0, ((void*)&iChildPosition));	  /* AUTOINSERTED TRACE */
	#endif

    if (iChildPosition > iNoOfChildren)
    {
        	{
		#ifdef ENABLE_AXISTRACE
			BasicNode* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getChild", this, 1,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

    }
    else
    {
        list<BasicNode*>::const_iterator itCurrChild= m_children.begin();
        /* The following is done since the previous line already takes the 
         * iterator one step forward
         */
        iChildPosition--;
        /* Takes the iterator to the relavent positon */
        for (int i=0; i<iChildPosition; i++)
        {
            itCurrChild++;
        }
        if (itCurrChild != m_children.end())
        {
            	{
		#ifdef ENABLE_AXISTRACE
			BasicNode* traceRet = (*itCurrChild);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getChild", this, 2,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return *itCurrChild;
		#endif
	}

        }
        else
        {
            	{
		#ifdef ENABLE_AXISTRACE
			BasicNode* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getChild", this, 3,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

        }
    }
}

int ComplexElement::getNoOfChildren()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "getNoOfChildren", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (iNoOfChildren);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getNoOfChildren", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return iNoOfChildren;
		#endif
	}

}

//<<<<<<< ComplexElement.cpp

const AxisChar* ComplexElement::getLocalName() {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "getLocalName", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (m_pachLocalName);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getLocalName", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_pachLocalName;
		#endif
	}
 
}

const AxisChar* ComplexElement::getURI() {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "getURI", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    if ((m_pachURI == NULL || strlen(m_pachURI) == 0) && m_pParent != NULL)
    {
        	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (m_pParent->getURI());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getURI", this, 1,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_pParent->getURI();
		#endif
	}

    }
    	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (m_pachURI);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getURI", this, 2,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_pachURI;
		#endif
	}

}

const AxisChar* ComplexElement::getPrefix() {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "getPrefix", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (m_pachPrefix);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getPrefix", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_pachPrefix;
		#endif
	}

}

IAttribute* ComplexElement::getFirstAttribute()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "getFirstAttribute", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    m_viCurrentAttribute = m_attributes.begin();
    if ( m_viCurrentAttribute == m_attributes.end())
        	{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getFirstAttribute", this, 1,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

    else
        	{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (((IAttribute*)*m_viCurrentAttribute));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getFirstAttribute", this, 2,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return ((IAttribute*)*m_viCurrentAttribute);
		#endif
	}
                                                                                                                                                                           
}
                                                                                                                                                                            
IAttribute* ComplexElement::getLastAttribute()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "getLastAttribute", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    /*To do : check the logic
    */
/*    m_viCurrentAttribute = m_attributes.end();
    if ( m_viCurrentAttribute == m_attributes.end())
        return NULL;
    else
        return ((IAttribute*)*m_viCurrentAttribute);
*/
    list <Attribute*>::reverse_iterator iAttributeReverseIte = m_attributes.rbegin();
    if (iAttributeReverseIte == m_attributes.rend()) {
         m_viCurrentAttribute = m_attributes.end();
		{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getLastAttribute", this, 1,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

    } else {
	m_viCurrentAttribute = m_attributes.end();
  		{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (((IAttribute*)*iAttributeReverseIte));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getLastAttribute", this, 2,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return ((IAttribute*)*iAttributeReverseIte);
		#endif
	}

    }
}
                                                                                                                                                                            
IAttribute* ComplexElement::getNextAttribute()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "getNextAttribute", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    //already at the end?
    if (m_viCurrentAttribute == m_attributes.end())
        	{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getNextAttribute", this, 1,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

                                                                                                                                                                            
    m_viCurrentAttribute++;
    if ( m_viCurrentAttribute == m_attributes.end())
        	{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getNextAttribute", this, 2,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

    else
        	{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (((IAttribute*)*m_viCurrentAttribute));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getNextAttribute", this, 3,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return ((IAttribute*)*m_viCurrentAttribute);
		#endif
	}

}

IAttribute* ComplexElement::getCurrentAttribute()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "getCurrentAttribute", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    //already at the end?
    if ( m_viCurrentAttribute == m_attributes.end())
        	{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getCurrentAttribute", this, 1,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

    else
        	{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (((IAttribute*)*m_viCurrentAttribute));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getCurrentAttribute", this, 2,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return ((IAttribute*)*m_viCurrentAttribute);
		#endif
	}

}

IAttribute* ComplexElement::getAttribute(AxisChar* pachPrefix,
										 AxisChar* pachURI,
										 AxisChar* pachLocalname)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("ComplexElement", "getAttribute", this, 3,
					TRACETYPE_STRING, 0, ((void*)&pachPrefix),
					TRACETYPE_STRING, 0, ((void*)&pachURI),
					TRACETYPE_STRING, 0, ((void*)&pachLocalname));	  /* AUTOINSERTED TRACE */
	#endif

	// Create local enumeration for valid parameters.
	typedef enum
	{
		eParamHasURI = 1,
		eParamHasPrefix = 2,
		eParamHasLocalName = 4
	} EPARAMS_USED;
	// Keep a list of valid parameters.
	int	iValidParams = 0;
	// For each parameter, test its validity by checking that the pointer is
	// not null and then (and only then) that the string pointed to by the
	// non-null pointer is not empty (string length is greater than zero). Iff
	// the test remains valid, add the enumerated equivalent of the parameter
	// to the list of valid parameters.
	if( (pachURI != NULL) && (strlen( pachURI) > 0))
	{
		iValidParams += eParamHasURI;
	}
	if( (pachPrefix != NULL) && (strlen( pachPrefix) > 0))
	{
		iValidParams += eParamHasPrefix;
	}
	if( (pachLocalname != NULL) && (strlen( pachLocalname) > 0))
	{
		iValidParams += eParamHasLocalName;
	}
	// Get the pointer to the start of the attribute list.
    list<Attribute*>::iterator it_m_attributes = m_attributes.begin();
	// Depending on the list of valid parameters, choose which case is
	// appropriate and then perform the search using those valid parameters.
	// NB: Currently, the first match is returned in all cases.
	switch( iValidParams)
	{
	// Parameter list contains a valid URI
	case eParamHasURI:
		{
    		while( it_m_attributes != m_attributes.end())
			{
				if( !strcmp( (*it_m_attributes)->getURI(), pachURI))
				{
	    				{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = ((IAttribute*) (*it_m_attributes));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getAttribute", this, 1,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (IAttribute*) (*it_m_attributes);
		#endif
	}

				}
				else
				{
		    		it_m_attributes++;
				}
    		}
			break;
		}
	// Parameter list contains a valid Prefix
	case eParamHasPrefix:
		{
    		while( it_m_attributes != m_attributes.end())
			{
				if( !strcmp( (*it_m_attributes)->getPrefix(), pachPrefix))
				{
	    				{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = ((IAttribute*) (*it_m_attributes));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getAttribute", this, 2,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (IAttribute*) (*it_m_attributes);
		#endif
	}

				}
				else
				{
		    		it_m_attributes++;
				}
    		}
			break;
		}
	// Parameter list contains a valid URI and Prefix
	case eParamHasURI + eParamHasPrefix:
		{
    		while( it_m_attributes != m_attributes.end())
			{
				if( !strcmp( (*it_m_attributes)->getURI(), pachURI) &&
					!strcmp( (*it_m_attributes)->getPrefix(), pachPrefix))
				{
	    				{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = ((IAttribute*) (*it_m_attributes));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getAttribute", this, 3,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (IAttribute*) (*it_m_attributes);
		#endif
	}

				}
				else
				{
		    		it_m_attributes++;
				}
    		}
			break;
		}
	// Parameter list contains a valid LocalName
		case eParamHasLocalName:
		{
    		while( it_m_attributes != m_attributes.end())
			{
				if( !strcmp( (*it_m_attributes)->getLocalName(), pachLocalname))
				{
	    				{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = ((IAttribute*) (*it_m_attributes));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getAttribute", this, 4,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (IAttribute*) (*it_m_attributes);
		#endif
	}

				}
				else
				{
		    		it_m_attributes++;
				}
    		}
			break;
		}
	// Parameter list contains a valid LocalName and URI
		case eParamHasLocalName + eParamHasURI:
		{
    		while( it_m_attributes != m_attributes.end())
			{
				if( !strcmp( (*it_m_attributes)->getLocalName(), pachLocalname) &&
					!strcmp( (*it_m_attributes)->getURI(), pachURI))
				{
	    				{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = ((IAttribute*) (*it_m_attributes));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getAttribute", this, 5,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (IAttribute*) (*it_m_attributes);
		#endif
	}

				}
				else
				{
		    		it_m_attributes++;
				}
    		}
			break;
		}
	// Parameter list contains a valid LocalName and Prefix
		case eParamHasLocalName + eParamHasPrefix:
		{
    		while( it_m_attributes != m_attributes.end())
			{
				if( !strcmp( (*it_m_attributes)->getLocalName(), pachLocalname) &&
					!strcmp( (*it_m_attributes)->getPrefix(), pachPrefix))
				{
	    				{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = ((IAttribute*) (*it_m_attributes));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getAttribute", this, 6,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (IAttribute*) (*it_m_attributes);
		#endif
	}

				}
				else
				{
		    		it_m_attributes++;
				}
    		}
			break;
		}
	// Parameter list contains a valid LocalName, URI and Prefix
		case eParamHasLocalName + eParamHasPrefix + eParamHasURI:
		{
    		while( it_m_attributes != m_attributes.end())
			{
				if( !strcmp( (*it_m_attributes)->getLocalName(), pachLocalname) &&
					!strcmp( (*it_m_attributes)->getURI(), pachURI) &&
					!strcmp( (*it_m_attributes)->getPrefix(), pachPrefix))
				{
	    				{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = ((IAttribute*) (*it_m_attributes));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getAttribute", this, 7,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (IAttribute*) (*it_m_attributes);
		#endif
	}

				}
				else
				{
		    		it_m_attributes++;
				}
    		}
			break;
		}
	// Parameter list contains no valid parameters
		default:
		{
			break;
		}
	}
    	{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("ComplexElement", "getAttribute", this, 8,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

}

//=======
//>>>>>>> 1.18.12.1

