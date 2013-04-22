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
 *
 */

/* HeaderBlock.cpp: implementation of the HeaderBlock class. */

#ifdef WIN32

#pragma warning (disable : 4786)

#endif

#include "HeaderBlock.h"

#include "SoapSerializer.h"

#include <axis/GDefine.hpp>

#include <axis/BasicNode.hpp>

#include "ComplexElement.h"

#include "CharacterElement.h"

#include "Namespace.h"

#include <iostream>

extern SoapEnvVersionsStruct gs_SoapEnvVersionsStruct[VERSION_LAST];

HeaderBlock::HeaderBlock()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "HeaderBlock", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    iNoOFChildren = 0;
	m_sPrefix = "";
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "HeaderBlock", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

HeaderBlock::HeaderBlock(const AxisChar *pachLocalName, const AxisChar *pachUri)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "HeaderBlock", this, 2,
					TRACETYPE_STRING, 0, ((void*)&pachLocalName),
					TRACETYPE_STRING, 0, ((void*)&pachUri));	  /* AUTOINSERTED TRACE */
	#endif

    iNoOFChildren = 0;
    m_localname = pachLocalName;
    m_uri = pachUri;
    m_sPrefix = "";
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "HeaderBlock", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

HeaderBlock::HeaderBlock(const HeaderBlock& rCopy):
IHeaderBlock(rCopy), iNoOFChildren(rCopy.iNoOFChildren), m_localname(rCopy.m_localname),
m_sPrefix(rCopy.m_sPrefix), m_uri(rCopy.m_uri)  
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "HeaderBlock", this, 1,
					TRACETYPE_DATA, sizeof(HeaderBlock&), ((void*)&rCopy));	  /* AUTOINSERTED TRACE */
	#endif

    list<BasicNode*>::const_iterator itCurrChild= rCopy.m_children.begin();
    while(itCurrChild != rCopy.m_children.end())
    {        
        this->m_children.push_back( (*itCurrChild)->clone() );
        itCurrChild++;        
    }
    list<Attribute*>::const_iterator itCurrAttribute= rCopy.m_attributes.begin();
    while(itCurrAttribute != rCopy.m_attributes.end())
    {        
        this->m_attributes.push_back( (*itCurrAttribute)->clone() );
        itCurrAttribute++;        
    }
	/* TO DO: check whether we have to do this 
	*
	list<Namespace*>::const_iterator itCurrNamespace= rCopy.m_namespaceDecls.begin();
    while(itCurrNamespace != rCopy.m_namespaceDecls.end())
    {        
        this->m_namespaceDecls.push_back( (*itCurrNamespace)->clone() );
        itCurrNamespace++;        
    }
	*/
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "HeaderBlock", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

IHeaderBlock* HeaderBlock::clone()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "clone", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			IHeaderBlock* traceRet = (new HeaderBlock(*this));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "clone", this, 0,
					TRACETYPE_POINTER, sizeof(IHeaderBlock), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new HeaderBlock(*this);
		#endif
	}

}

HeaderBlock::~HeaderBlock()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "~HeaderBlock", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    // Clear the Attributes
    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();
    while(itCurrAttribute != m_attributes.end())
    {        
        delete (*itCurrAttribute);
        itCurrAttribute++;        
    }
    m_attributes.clear();
    // Clear the Namespaces
    list<Namespace*>::iterator itCurrNamespace= m_namespaceDecls.begin();
    while(itCurrNamespace != m_namespaceDecls.end())
    {        
        delete (*itCurrNamespace);
        itCurrNamespace++;        
    }
    m_namespaceDecls.clear();
    // Clear the children
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
				axiscpp::AxisTrace::traceExit("HeaderBlock", "~HeaderBlock", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

int HeaderBlock::setLocalName(const AxisChar* localname)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "setLocalName", this, 1,
					TRACETYPE_STRING, 0, ((void*)&localname));	  /* AUTOINSERTED TRACE */
	#endif

	if(localname==NULL)
	{
			{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "setLocalName", this, 1,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}

	}
    m_localname=localname;
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "setLocalName", this, 2,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

const AxisChar * HeaderBlock::getLocalName()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "getLocalName", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (m_localname.c_str());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "getLocalName", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_localname.c_str();
		#endif
	}

}

/*
 *  Commented by Susantha - 21/06/2004
 * The prefix should be decided by the Serializer at runtime
 *
 * Uncommented by Mark Whitlock - 24/8/04 after discussion 
 * on the mailing list agreed to add back in this method.
 * Jira issue AXISCPP-135
 */

int HeaderBlock::setPrefix(const AxisChar* prefix)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "setPrefix", this, 1,
					TRACETYPE_STRING, 0, ((void*)&prefix));	  /* AUTOINSERTED TRACE */
	#endif

	if(prefix)
	{
	    m_sPrefix= prefix;
	}
	else
	{
		m_sPrefix="";
	}
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "setPrefix", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

int HeaderBlock::setURI(const AxisChar* uri)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "setURI", this, 1,
					TRACETYPE_STRING, 0, ((void*)&uri));	  /* AUTOINSERTED TRACE */
	#endif

	if(uri)
	{
	    m_uri= uri;
	}
	else
	{
		m_uri="";
	}
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "setURI", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

int HeaderBlock::addAttribute(Attribute* pAttr)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "addAttribute", this, 1,
					TRACETYPE_POINTER, sizeof(Attribute), ((void*)&pAttr));	  /* AUTOINSERTED TRACE */
	#endif

    if (pAttr)
    {
        m_attributes.push_back(pAttr);
        	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "addAttribute", this, 1,
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
				axiscpp::AxisTrace::traceExit("HeaderBlock", "addAttribute", this, 2,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}

    }
}

int HeaderBlock::serialize(SoapSerializer& pSZ)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "serialize", this, 1,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ));	  /* AUTOINSERTED TRACE */
	#endif

	
    /*
     *In the code we don't look whether the m_sPrefix is available or
     *    not. Instead directly insert it. The reason is that the SOAP
     *  1.1 spec says that "All immediate child elements of the SOAP 
     *  Header element MUST be namespace-qualified".
     */
    int iStatus= AXIS_SUCCESS;
    list<AxisChar*> lstTmpNameSpaceStack;
    bool blnIsNewNamespace = false;
    do
    {
        /*
         * TO DO: ReWrite the following logic to deal with name spaces
         */
        pSZ.serialize("<", NULL);
        if(m_sPrefix.length() == 0)
        {
            m_sPrefix = pSZ.getNamespacePrefix(m_uri.c_str(),
                blnIsNewNamespace);
            if (blnIsNewNamespace)
            {
                lstTmpNameSpaceStack.push_back((AxisChar*)m_uri.c_str());
            }
        } else {
			/* The use has specified his/her own prefix. Therefore this is 
			taken as a new namespace and will be declared as a namespace 
			declaration.
			*/
			blnIsNewNamespace = true;
			/* Adding to the Serializers namespace list b'cas the child 
			elements of this HeaderBlock might use this namespace, so that they
			can get the correct corrosponding prefix from the Serializer.
			 */
			pSZ.addNamespaceToNamespaceList(m_uri.c_str(), m_sPrefix.c_str());
			/* Adding this namespace to the temprory namespace list b'cas we
			have to remove this namespce from the Serializer at the end of this
			HeaderBlock serialization.
			*/
			lstTmpNameSpaceStack.push_back((AxisChar*)m_uri.c_str());
		}
        pSZ.serialize(m_sPrefix.c_str(), ":", m_localname.c_str(), NULL);
		
		if (blnIsNewNamespace) {
			pSZ.serialize(" xmlns:", m_sPrefix.c_str(), "=\"", m_uri.c_str(), "\"", NULL);
		}
        iStatus= attrSerialize(pSZ, lstTmpNameSpaceStack);
        if(iStatus==AXIS_FAIL)
        {
            break;
        }
        iStatus= serializeNamespaceDecl(pSZ, lstTmpNameSpaceStack);
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
        pSZ.serialize("</", m_sPrefix.c_str(), ":", m_localname.c_str(), ">",
            NULL);
        /*
         * Removing the namespace list of this headerblock from the stack.
         */
        list<AxisChar*>::iterator itCurrentNamespace = 
            lstTmpNameSpaceStack.begin();
        while (itCurrentNamespace != lstTmpNameSpaceStack.end())
        {
            pSZ.removeNamespacePrefix(*itCurrentNamespace);
            itCurrentNamespace++;
        }
            
    } while(0);
	m_sPrefix = "";
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (iStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "serialize", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return iStatus;
		#endif
	}

}

int HeaderBlock::attrSerialize(SoapSerializer& pSZ,
                               list<AxisChar*>& lstTmpNameSpaceStack)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "attrSerialize", NULL, 2,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ),
					TRACETYPE_DATA, sizeof(list<AxisChar* >&), ((void*)&lstTmpNameSpaceStack));	  /* AUTOINSERTED TRACE */
	#endif

    int iStatus= AXIS_SUCCESS;
    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();
    while(itCurrAttribute != m_attributes.end())
    {    
		// See if this prefix matches a namespace within this headerblock
		const AxisChar *uri = NULL;
		Attribute *attr = *itCurrAttribute;
		const AxisChar *attrPrefix = attr->getPrefix();
		if (NULL != attrPrefix)
		{
			list<Namespace*>::iterator itNs = m_namespaceDecls.begin();
			while (itNs != m_namespaceDecls.end())
			{
				if (0 == strcmp((*itNs)->getPrefix(), attrPrefix))
				{
					uri = (*itNs)->getURI();
					break;
				}
				itNs++;
			}
		}
        iStatus= (*itCurrAttribute)->serialize(pSZ, lstTmpNameSpaceStack, uri);
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
				axiscpp::AxisTrace::traceExit("HeaderBlock", "attrSerialize", NULL, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return iStatus;
		#endif
	}

}

bool HeaderBlock::isSerializable()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "isSerializable", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    bool bStatus= true;
    if(m_localname.length() == 0)
    {
        bStatus= false;
    }
    else
    {
        if(m_sPrefix.length() == 0)
        {
            if(m_uri.length() != 0)
            {
                bStatus= false;
            }
        }
        else
        {
            if(m_uri.length() == 0)
            {
                bStatus= false;
            }
        }
    }
    	{
		#ifdef ENABLE_AXISTRACE
			bool traceRet = (bStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "isSerializable", this, 0,
					TRACETYPE_BOOL, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return bStatus;
		#endif
	}

}

int HeaderBlock::addChild(BasicNode *pBasicNode)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "addChild", this, 1,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&pBasicNode));	  /* AUTOINSERTED TRACE */
	#endif

    if (pBasicNode)
    {
        m_children.push_back(pBasicNode);
        iNoOFChildren++;
        	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "addChild", this, 1,
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
				axiscpp::AxisTrace::traceExit("HeaderBlock", "addChild", this, 2,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}

    }
}

int HeaderBlock::serializeChildren(SoapSerializer& pSZ,
                                   list<AxisChar *>& lstTmpNameSpaceStack)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "serializeChildren", NULL, 2,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ),
					TRACETYPE_DATA, sizeof(list<AxisChar* >&), ((void*)&lstTmpNameSpaceStack));	  /* AUTOINSERTED TRACE */
	#endif

    int iStatus = AXIS_SUCCESS;
// SOAP serialiser does not have an == operator so can't check it
    list<BasicNode*>::iterator itCurrBasicNode = m_children.begin();
    while( itCurrBasicNode != m_children.end() && iStatus == AXIS_SUCCESS)
    {
        if ((*itCurrBasicNode)->getNodeType() == ELEMENT_NODE)
        {
// Processing for ELEMENT_NODE types
            iStatus = (*itCurrBasicNode)->serialize( pSZ, lstTmpNameSpaceStack);
        }
        else
        {
// Processing for CHARACTER_NODE types
            iStatus = (*itCurrBasicNode)->serialize( pSZ);
        }
        itCurrBasicNode++;
    }
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (iStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "serializeChildren", NULL, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return iStatus;
		#endif
	}

}

INamespace* HeaderBlock::createNamespaceDecl( const AxisChar * pPrefix, const AxisChar * pURI) 
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "createNamespaceDecl", this, 2,
					TRACETYPE_STRING, 0, ((void*)&pPrefix),
					TRACETYPE_STRING, 0, ((void*)&pURI));	  /* AUTOINSERTED TRACE */
	#endif

// Check that the prefix and uri are valid pointers and that the string is not
// empty.
	if( pPrefix != NULL && strlen( pPrefix) > 0 &&
		pURI != NULL && strlen( pURI) > 0)
	{
// Iterate through the namespaces checking that the prefix does not already
// exist.
		bool						bNameFound = false;
		list<Namespace*>::iterator	itCurrNamespaceDecl = m_namespaceDecls.begin();
		while( itCurrNamespaceDecl != m_namespaceDecls.end() && !bNameFound)
		{
			if( !(bNameFound = !strcmp( (*itCurrNamespaceDecl)->getPrefix(), pPrefix)))
			{
				itCurrNamespaceDecl++;
			}
		}    
// If the prefix is found in the declared namespace list, then update the uri
// for the prefix and return a pointer to that namespace.
		if( bNameFound)
		{
			(*itCurrNamespaceDecl)->setURI( pURI);
				{
		#ifdef ENABLE_AXISTRACE
			INamespace* traceRet = ((INamespace *) *itCurrNamespaceDecl);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "createNamespaceDecl", this, 1,
					TRACETYPE_POINTER, sizeof(INamespace), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (INamespace *) *itCurrNamespaceDecl;
		#endif
	}

		}
// If the prefix was not found, then create a new namespace for the prefix/uri
// pair and return the pointer to the new namespace.
		Namespace *	pNamespace = new Namespace( pPrefix, pURI);
		m_namespaceDecls.push_back( pNamespace);
			{
		#ifdef ENABLE_AXISTRACE
			INamespace* traceRet = ((INamespace *) pNamespace);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "createNamespaceDecl", this, 2,
					TRACETYPE_POINTER, sizeof(INamespace), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (INamespace *) pNamespace;
		#endif
	}
 
	}
	else
	{
			{
		#ifdef ENABLE_AXISTRACE
			INamespace* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "createNamespaceDecl", this, 3,
					TRACETYPE_POINTER, sizeof(INamespace), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

	}
}

int HeaderBlock::serializeNamespaceDecl(SoapSerializer &pSZ, std::list<AxisChar*>& lstTmpNameSpaceStack)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "serializeNamespaceDecl", this, 2,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ),
					TRACETYPE_DATA, sizeof(std:: list<AxisChar* >&), ((void*)&lstTmpNameSpaceStack));	  /* AUTOINSERTED TRACE */
	#endif

    list<Namespace*>::iterator itCurrNamespaceDecl= m_namespaceDecls.begin();
    while(itCurrNamespaceDecl != m_namespaceDecls.end())
    {        
        (*itCurrNamespaceDecl)->serialize(pSZ, lstTmpNameSpaceStack);
        itCurrNamespaceDecl++;        
    }    
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "serializeNamespaceDecl", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

BasicNode* HeaderBlock::getLastChild()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "getLastChild", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    list<BasicNode*>::reverse_iterator ritCurrBasicNode= m_children.rbegin();
    if (ritCurrBasicNode != m_children.rend())
    {        
        	{
		#ifdef ENABLE_AXISTRACE
			BasicNode* traceRet = ((*ritCurrBasicNode));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "getLastChild", this, 1,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (*ritCurrBasicNode);
		#endif
	}

    }    
    	{
		#ifdef ENABLE_AXISTRACE
			BasicNode* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "getLastChild", this, 2,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

}

BasicNode* HeaderBlock::getChild(int iChildPosition)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "getChild", this, 1,
					TRACETYPE_INT, 0, ((void*)&iChildPosition));	  /* AUTOINSERTED TRACE */
	#endif

    if ( (iChildPosition<=0) || (iChildPosition > iNoOFChildren) )
    {
        	{
		#ifdef ENABLE_AXISTRACE
			BasicNode* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "getChild", this, 1,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

    }
    else
    {
        list<BasicNode*>::iterator itCurrBasicNode= m_children.begin();
        /* The following is done since the previous line already takes the
         * iterator one step forward
         */
        iChildPosition--;
        /* Takes the iterator to the relavent positon */
        for (int i=0; i<iChildPosition; i++)
        {
            itCurrBasicNode++;
        }
        if (itCurrBasicNode != m_children.end())
        {
            	{
		#ifdef ENABLE_AXISTRACE
			BasicNode* traceRet = (*itCurrBasicNode);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "getChild", this, 2,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return *itCurrBasicNode;
		#endif
	}

        }
        else
        {
            	{
		#ifdef ENABLE_AXISTRACE
			BasicNode* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "getChild", this, 3,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

        }
    }
}

BasicNode* HeaderBlock::createChild(NODE_TYPE eNODE_TYPE)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "createChild", this, 1,
					TRACETYPE_DATA, sizeof(NODE_TYPE), ((void*)&eNODE_TYPE));	  /* AUTOINSERTED TRACE */
	#endif

    BasicNode* pBasicNode = NULL;
    if(eNODE_TYPE==CHARACTER_NODE)
    {
        pBasicNode = new CharacterElement();
    }
    else if (eNODE_TYPE==ELEMENT_NODE)
    {
        pBasicNode = new ComplexElement();
    }
    	{
		#ifdef ENABLE_AXISTRACE
			BasicNode* traceRet = (pBasicNode);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "createChild", this, 0,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return pBasicNode;
		#endif
	}

}

bool HeaderBlock::operator ==( const HeaderBlock &objHeaderBlock)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "operator==", this, 1,
					TRACETYPE_DATA, sizeof(HeaderBlock&), ((void*)&objHeaderBlock));	  /* AUTOINSERTED TRACE */
	#endif

    /*
     * TODO : the logic
     */
    	{
		#ifdef ENABLE_AXISTRACE
			bool traceRet = (true);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "operator==", this, 0,
					TRACETYPE_BOOL, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return true;
		#endif
	}

}

BasicNode* HeaderBlock::createImmediateChild(NODE_TYPE eNODE_TYPE)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "createImmediateChild", this, 1,
					TRACETYPE_DATA, sizeof(NODE_TYPE), ((void*)&eNODE_TYPE));	  /* AUTOINSERTED TRACE */
	#endif

		{
		#ifdef ENABLE_AXISTRACE
			BasicNode* traceRet = (createImmediateChild(eNODE_TYPE, "", "", "", ""));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "createImmediateChild", this, 0,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return createImmediateChild(eNODE_TYPE, "", "", "", "");
		#endif
	}

}

/**
 * The localname must be specified, but all other input parameters are optional.
 */

IAttribute* HeaderBlock::createAttribute(const AxisChar *localname,
                                        const AxisChar *prefix,
                                        const AxisChar *value)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "createAttribute", this, 3,
					TRACETYPE_STRING, 0, ((void*)&localname),
					TRACETYPE_STRING, 0, ((void*)&prefix),
					TRACETYPE_STRING, 0, ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (createAttribute(localname, prefix, NULL, value));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "createAttribute", this, 0,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return createAttribute(localname, prefix, NULL, value);
		#endif
	}

}

/**
 * The localname must be specified, but all other input parameters are optional.
 */

IAttribute* HeaderBlock::createAttribute(const AxisChar * pLocalName,
                                         const AxisChar * pPrefix,
                                         const AxisChar * pURI,
                                         const AxisChar * pValue)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "createAttribute", this, 4,
					TRACETYPE_STRING, 0, ((void*)&pLocalName),
					TRACETYPE_STRING, 0, ((void*)&pPrefix),
					TRACETYPE_STRING, 0, ((void*)&pURI),
					TRACETYPE_STRING, 0, ((void*)&pValue));	  /* AUTOINSERTED TRACE */
	#endif

// Check that the contents of the passed parameters are valid.
	if( NULL == pLocalName || 0 == strlen( pLocalName))
	{
			{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "createAttribute", this, 1,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

	}
	if( !pPrefix)
	{
		pPrefix = "";
	}
	if( !pURI)
	{
		pURI = "";
	}
	if( !pValue)
	{
		pValue = "";
	}
// Check that the local name and prefix have not already been defined.  If
// they have, then return NULL indicating that the prefix/localname pair have
// already been defined.
	list<Attribute*>::iterator	itCurrAttribute= m_attributes.begin();
	while( itCurrAttribute != m_attributes.end())
	{        
		if( (strcmp( (*itCurrAttribute)->getLocalName(), pLocalName) == 0) && 
			(strcmp( (*itCurrAttribute)->getPrefix(), pPrefix) == 0))
		{
				{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "createAttribute", this, 2,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

		}
		else
		{
			itCurrAttribute++;
		}
	}    
// Check that the prefix has not already been defined in the namespace
// declarations.  If it has, then return NULL indicating that the
// prefix/localname pair has already been defined and 'copy down' the
// namespace decl into the attribute list as this will help in the
// serialisation.
	list<Namespace*>::iterator	itCurrNamespaceDecls = m_namespaceDecls.begin();
	while( itCurrNamespaceDecls != m_namespaceDecls.end())
	{        
		if( !strcmp( (*itCurrNamespaceDecls)->getPrefix(), pPrefix))
		{
			Attribute *	pAttribute = new Attribute( m_attributes, pLocalName,
													pPrefix,
													(*itCurrNamespaceDecls)->getURI(),
													pValue);
			m_attributes.push_back( pAttribute);
				{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (pAttribute);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "createAttribute", this, 3,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return pAttribute;
		#endif
	}

		}
		else
		{
			itCurrNamespaceDecls++;
		}
	}    
// If the prefix/localname pair have not previously been defined, then create
// and return the attribute.
	Attribute *	pAttribute = new Attribute( m_attributes, pLocalName, pPrefix, pURI, pValue);
	m_attributes.push_back( pAttribute);
		{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (pAttribute);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "createAttribute", this, 4,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return pAttribute;
		#endif
	}

}

IAttribute* HeaderBlock::createStdAttribute(HEADER_BLOCK_STD_ATTR_TYPE 
                                           eStdAttrType, 
                                           SOAP_VERSION eSOAP_VERSION)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "createStdAttribute", this, 2,
					TRACETYPE_DATA, sizeof(HEADER_BLOCK_STD_ATTR_TYPE), ((void*)&eStdAttrType),
					TRACETYPE_DATA, sizeof(SOAP_VERSION), ((void*)&eSOAP_VERSION));	  /* AUTOINSERTED TRACE */
	#endif

    Attribute* pAttribute = NULL;
    bool blnStatus = true;
    do
    {
        switch(eSOAP_VERSION)
        {
            case VERSION_LAST:
                blnStatus = false;
                break;
            case SOAP_VER_1_1:
                switch(eStdAttrType)
                {
                    case ACTOR:
                        pAttribute = new Attribute(m_attributes, "actor",
                            gs_SoapEnvVersionsStruct[SOAP_VER_1_1].pchPrefix,
                            "","http://schemas.xmlsoap.org/soap/actor/next");
                        break;
                    case MUST_UNDERSTAND_TRUE:
                        pAttribute = new Attribute(m_attributes, "mustUnderstand",
                            gs_SoapEnvVersionsStruct
                            [SOAP_VER_1_1].pchPrefix,"","1");
                        break;
                    case MUST_UNDERSTAND_FALSE:
                        pAttribute = new Attribute(m_attributes, "mustUnderstand",
                            gs_SoapEnvVersionsStruct
                            [SOAP_VER_1_1].pchPrefix,"","0");
                        break;
                    default:
                        blnStatus = false;
                        break;
                }
                break;
            case SOAP_VER_1_2:
                switch(eStdAttrType)
                {
                    case ROLE_NEXT:
                        pAttribute = new Attribute(m_attributes, "role",
                            gs_SoapEnvVersionsStruct[SOAP_VER_1_2].pchPrefix,
                            "", "http://www.w3.org/2003/05/soap-envelope/role/next");
                        break;
                    case ROLE_NONE:
                        pAttribute = new Attribute(m_attributes, "role",
                            gs_SoapEnvVersionsStruct[SOAP_VER_1_2].pchPrefix,
                            "", "http://www.w3.org/2003/05/soap-envelope/role/none");
                        break;
                    case ROLE_ULTIMATE_RECEIVER:
                        pAttribute = new Attribute(m_attributes, "role",
                            gs_SoapEnvVersionsStruct[SOAP_VER_1_2].pchPrefix,
                            "", "http://www.w3.org/2003/05/soap-envelope/role/ultimateReceiver");
                        break;
                    case MUST_UNDERSTAND_TRUE:
                        pAttribute = new Attribute(m_attributes, "mustUnderstand",
                            gs_SoapEnvVersionsStruct[SOAP_VER_1_2].pchPrefix,
                            "","true");
                        break;
                    case MUST_UNDERSTAND_FALSE:
                        pAttribute = new Attribute(m_attributes, "mustUnderstand",
                            gs_SoapEnvVersionsStruct[SOAP_VER_1_2].pchPrefix,
                            "","false");
                        break;
                    default:
                        blnStatus = false;
                        break;
                }
                break;
            default:
                blnStatus = false;
                break;
        }
    } while (0);
    
    if (blnStatus)
    {
        // Samisa: AXISCPP-452 - got to check for duplicate attributes
        list<Attribute*>::iterator itAttr = m_attributes.begin();
        while (itAttr != m_attributes.end())
        {
                Attribute* pCurrentAttribute = *itAttr;
                if (!strcmp(pCurrentAttribute->getLocalName(),pAttribute->getLocalName() ) &&
                        !strcmp(pCurrentAttribute->getPrefix(), pAttribute->getPrefix() ) )
                        {
                            // we have the attribute set already, so only change the value
                            pCurrentAttribute->setValue( pAttribute->getValue() );
                            delete pAttribute;
                            	{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (pCurrentAttribute);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "createStdAttribute", this, 1,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return pCurrentAttribute;
		#endif
	}
 // return the currently set attributes pointer
                                                      // job done
                        }
                itAttr++;
        }
        // we do not have the attribute set already, hence add it
        m_attributes.push_back(pAttribute);
        	{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (pAttribute);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "createStdAttribute", this, 2,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return pAttribute;
		#endif
	}

    }
    else
    {
        	{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "createStdAttribute", this, 3,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

    }
}

const AxisChar* HeaderBlock::getAttributeValue(const AxisChar *localname,
                                         const AxisChar *prefix)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "getAttributeValue", this, 2,
					TRACETYPE_STRING, 0, ((void*)&localname),
					TRACETYPE_STRING, 0, ((void*)&prefix));	  /* AUTOINSERTED TRACE */
	#endif

     if(!localname)
     {
        localname="";
     }
     if(!prefix)
     {
        prefix="";
     }
 
   	list<Attribute*>::iterator itAttr = m_attributes.begin();
 	while (itAttr != m_attributes.end()) 
 	{
 		Attribute* pAttribute = *itAttr;
 		if (!strcmp(pAttribute->getLocalName(),localname) &&
 			!strcmp(pAttribute->getPrefix(),prefix)) 
 			{
 					{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (pAttribute->getValue());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "getAttributeValue", this, 1,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return pAttribute->getValue();
		#endif
	}

 			}
 		itAttr++;
 	}
    	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "getAttributeValue", this, 2,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

}
 
const AxisChar * HeaderBlock::getAttributeUri( const AxisChar * localname,
											   const AxisChar * prefix)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "getAttributeUri", this, 2,
					TRACETYPE_STRING, 0, ((void*)&localname),
					TRACETYPE_STRING, 0, ((void*)&prefix));	  /* AUTOINSERTED TRACE */
	#endif

	list<Attribute*>::iterator itAttr = m_attributes.begin();
	while( itAttr != m_attributes.end()) 
	{
		Attribute * pAttribute = *itAttr;
		if( !strcmp( pAttribute->getLocalName(),localname) &&
			!strcmp( pAttribute->getPrefix(),prefix)) 
		{
				{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (pAttribute->getURI());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "getAttributeUri", this, 1,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return pAttribute->getURI();
		#endif
	}

		}
		
		if( strlen( localname) == 0 &&
			!strcmp( pAttribute->getPrefix(), prefix)) 
		{
				{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (pAttribute->getURI());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "getAttributeUri", this, 2,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return pAttribute->getURI();
		#endif
	}

		}
		itAttr++;
	}
		{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "getAttributeUri", this, 3,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

}

BasicNode* HeaderBlock::createImmediateChild(NODE_TYPE eNODE_TYPE,
                                             AxisChar *pachLocalName,
                                             AxisChar *pachPrefix,
                                             AxisChar *pachUri,
                                             AxisChar* pachValue)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "createImmediateChild", this, 5,
					TRACETYPE_DATA, sizeof(NODE_TYPE), ((void*)&eNODE_TYPE),
					TRACETYPE_STRING, 0, ((void*)&pachLocalName),
					TRACETYPE_STRING, 0, ((void*)&pachPrefix),
					TRACETYPE_STRING, 0, ((void*)&pachUri),
					TRACETYPE_STRING, 0, ((void*)&pachValue));	  /* AUTOINSERTED TRACE */
	#endif

    BasicNode* pBasicNode = NULL;
    if(!pachLocalName)
    {
     pachLocalName="";
    }
    if(!pachPrefix)
    {
     pachPrefix="";
    }
    if(!pachUri)
    {
     pachUri="";
    }
    if(!pachValue)
    {
     pachValue="";
    }
    
    do
    {
        if(eNODE_TYPE==CHARACTER_NODE)
        {
            pBasicNode = new CharacterElement(pachValue);
        }
        else if (eNODE_TYPE==ELEMENT_NODE)
        {
            if ( (pachLocalName) && (pachUri) )
            {
                pBasicNode = new ComplexElement(pachLocalName, pachPrefix,
                    pachUri);
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
        if (pBasicNode)
        {
            m_children.push_back(pBasicNode);
            iNoOFChildren++;
        }
    } while (0);
    	{
		#ifdef ENABLE_AXISTRACE
			BasicNode* traceRet = (pBasicNode);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "createImmediateChild", this, 0,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return pBasicNode;
		#endif
	}

}

BasicNode* HeaderBlock::createChild(NODE_TYPE eNODE_TYPE,
                                    AxisChar *pachLocalName,
                                    AxisChar *pachPrefix, 
                                    AxisChar *pachUri,
                                    AxisChar *pachValue)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "createChild", this, 5,
					TRACETYPE_DATA, sizeof(NODE_TYPE), ((void*)&eNODE_TYPE),
					TRACETYPE_STRING, 0, ((void*)&pachLocalName),
					TRACETYPE_STRING, 0, ((void*)&pachPrefix),
					TRACETYPE_STRING, 0, ((void*)&pachUri),
					TRACETYPE_STRING, 0, ((void*)&pachValue));	  /* AUTOINSERTED TRACE */
	#endif

    BasicNode* pBasicNode = NULL;
    if(!pachLocalName)
    {
     pachLocalName="";
    }
    if(!pachPrefix)
    {
     pachPrefix="";
    }
    if(!pachUri)
    {
     pachUri="";
    }
    if(!pachValue)
    {
     pachValue="";
    }
    do
    {
        if(eNODE_TYPE==CHARACTER_NODE)
        {
            pBasicNode = new CharacterElement(pachValue);
        }
        else if (eNODE_TYPE==ELEMENT_NODE)
        {
            pBasicNode = new ComplexElement(pachLocalName, pachPrefix,
                pachUri);
        }
        else
        {
            break;
        }
    } while (0);
    	{
		#ifdef ENABLE_AXISTRACE
			BasicNode* traceRet = (pBasicNode);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "createChild", this, 0,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return pBasicNode;
		#endif
	}

}

int HeaderBlock::getNoOfChildren()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "getNoOfChildren", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (iNoOFChildren);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "getNoOfChildren", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return iNoOFChildren;
		#endif
	}

}

BasicNode* HeaderBlock::getFirstChild()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "getFirstChild", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    list<BasicNode*>::iterator itCurrBasicNode= m_children.begin();
    
    if (itCurrBasicNode != m_children.end())
    {        
        	{
		#ifdef ENABLE_AXISTRACE
			BasicNode* traceRet = ((*itCurrBasicNode));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "getFirstChild", this, 1,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (*itCurrBasicNode);
		#endif
	}

    }
    	{
		#ifdef ENABLE_AXISTRACE
			BasicNode* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "getFirstChild", this, 2,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}

}

HeaderBlock::HeaderBlock(const AxisChar *pachLocalName, const AxisChar *pachUri, const AxisChar *pachPrefix)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HeaderBlock", "HeaderBlock", this, 3,
					TRACETYPE_STRING, 0, ((void*)&pachLocalName),
					TRACETYPE_STRING, 0, ((void*)&pachUri),
					TRACETYPE_STRING, 0, ((void*)&pachPrefix));	  /* AUTOINSERTED TRACE */
	#endif

	iNoOFChildren = 0;
    m_localname = pachLocalName;
    m_uri = pachUri;
    m_sPrefix = pachPrefix;
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HeaderBlock", "HeaderBlock", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

