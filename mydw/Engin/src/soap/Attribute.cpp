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
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */

/*
 * Revision 1.1  2004/05/25 samisa
 * Added copy constructor
 */

#ifdef WIN32

#pragma warning (disable : 4786)

#endif

#include "Attribute.h"

#include "SoapSerializer.h"

Attribute::Attribute( list<Attribute*> attribute)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Attribute", "Attribute", this, 1,
					TRACETYPE_DATA, sizeof(list<Attribute* >), ((void*)&attribute));	  /* AUTOINSERTED TRACE */
	#endif

	if( (void *) &attribute != NULL && !attribute.empty())
	{
		list<Attribute*>::iterator itAttributeList = attribute.begin();
		while( itAttributeList != attribute.end())
		{
			m_PrefixList.push_back( (*itAttributeList)->getPrefix());
			itAttributeList++;
		}
	}
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Attribute", "Attribute", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

Attribute::~Attribute()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Attribute", "~Attribute", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

	m_PrefixList.clear();
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Attribute", "~Attribute", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

int Attribute::setLocalName(const AxisChar* localname)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Attribute", "setLocalName", this, 1,
					TRACETYPE_STRING, 0, ((void*)&localname));	  /* AUTOINSERTED TRACE */
	#endif

	if(NULL==localname)
	{
        localname="";
	}
    m_localname= localname;
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Attribute", "setLocalName", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

int Attribute::setPrefix(const AxisChar* prefix)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Attribute", "setPrefix", this, 1,
					TRACETYPE_STRING, 0, ((void*)&prefix));	  /* AUTOINSERTED TRACE */
	#endif

	if( NULL == prefix)
	{
        prefix = "";
	}
	if( (void *) &m_PrefixList != NULL && !m_PrefixList.empty())
	{
		list<const char*>::iterator itPrefixList = m_PrefixList.begin();
		while( itPrefixList != m_PrefixList.end())
		{
			if( !strcmp( (*itPrefixList), prefix))
			{
					{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Attribute", "setPrefix", this, 1,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}

			}
			else
			{
				itPrefixList++;
			}
		}
	}
	m_prefix = prefix;
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Attribute", "setPrefix", this, 2,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

int Attribute::setURI(const AxisChar* uri)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Attribute", "setURI", this, 1,
					TRACETYPE_STRING, 0, ((void*)&uri));	  /* AUTOINSERTED TRACE */
	#endif

	if(NULL==uri)
	{
        uri="";
	}
    
	/**
	 * sets the prefix according to the URI
	 */
	
	if(m_prefix != "")
	{
		
		bool bPrefixFound = false;
		list<Namespace*>::iterator	itCurrNamespaceDecl = m_namespaceDecls.begin();
		while( itCurrNamespaceDecl != m_namespaceDecls.end() && !bPrefixFound)
		{
			if( !(bPrefixFound = !strcmp( (*itCurrNamespaceDecl)->getURI(), uri)))
			{
				itCurrNamespaceDecl++;
			}
		}    
		
		if( bPrefixFound)
		{
			setPrefix((*itCurrNamespaceDecl)->getPrefix());
		}
		else
		{
			setPrefix(NULL);
		}
	}
		
	m_uri= uri;
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Attribute", "setURI", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

int Attribute::setValue(const AxisChar* value)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Attribute", "setValue", this, 1,
					TRACETYPE_STRING, 0, ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

	if(NULL==value)
	{
        value="";
	}
    m_value= value;
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Attribute", "setValue", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

const AxisChar* Attribute::getLocalName()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Attribute", "getLocalName", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

		{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (m_localname.c_str());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Attribute", "getLocalName", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_localname.c_str();
		#endif
	}

}

const AxisChar* Attribute::getPrefix()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Attribute", "getPrefix", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

		{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (m_prefix.c_str());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Attribute", "getPrefix", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_prefix.c_str();
		#endif
	}

}

const AxisChar* Attribute::getURI()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Attribute", "getURI", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

		{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (m_uri.c_str());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Attribute", "getURI", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_uri.c_str();
		#endif
	}

}

const AxisChar* Attribute::getValue()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Attribute", "getValue", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

		{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (m_value.c_str());
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Attribute", "getValue", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_value.c_str();
		#endif
	}

}

Attribute::Attribute(){
}
 
Attribute::Attribute(list<Attribute*> attribute, const AxisChar* localname, const AxisChar* prefix, 
                     const AxisChar* uri, const AxisChar* value)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Attribute", "Attribute", this, 5,
					TRACETYPE_DATA, sizeof(list<Attribute* >), ((void*)&attribute),
					TRACETYPE_STRING, 0, ((void*)&localname),
					TRACETYPE_STRING, 0, ((void*)&prefix),
					TRACETYPE_STRING, 0, ((void*)&uri),
					TRACETYPE_STRING, 0, ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    m_localname= localname;
    m_prefix= prefix;
    m_uri= uri;
	if (NULL==value)
		m_value = "";
	else
	    m_value= value;
	if( (void *) &attribute != NULL && !attribute.empty())
	{
		list<Attribute*>::iterator itAttributeList = attribute.begin();
		while( itAttributeList != attribute.end())
		{
			m_PrefixList.push_back( (*itAttributeList)->getPrefix());
			itAttributeList++;
		}
	}
	if( prefix != NULL && strlen( prefix) > 0)
	{
		m_PrefixList.push_back( prefix);
	}
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Attribute", "Attribute", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

Attribute::Attribute(list<Attribute*> attribute, const AxisChar *localname, const AxisChar *prefix, 
                     const AxisChar *value)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Attribute", "Attribute", this, 4,
					TRACETYPE_DATA, sizeof(list<Attribute* >), ((void*)&attribute),
					TRACETYPE_STRING, 0, ((void*)&localname),
					TRACETYPE_STRING, 0, ((void*)&prefix),
					TRACETYPE_STRING, 0, ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif

    m_localname= localname;
    m_prefix= prefix;
    m_uri= "";
	if (NULL==value)
		m_value = "";
	else
	    m_value= value;
	if( (void *) &attribute != NULL && !attribute.empty())
	{
		list<Attribute*>::iterator itAttributeList = attribute.begin();
		while( itAttributeList != attribute.end())
		{
			m_PrefixList.push_back( (*itAttributeList)->getPrefix());
			itAttributeList++;
		}
	}
	if( prefix != NULL && strlen( prefix) > 0)
	{
		m_PrefixList.push_back( prefix);
	}
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Attribute", "Attribute", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

Attribute::Attribute(list<Attribute*> attribute, const Attribute& rCopy)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Attribute", "Attribute", this, 2,
					TRACETYPE_DATA, sizeof(list<Attribute* >), ((void*)&attribute),
					TRACETYPE_DATA, sizeof(Attribute&), ((void*)&rCopy));	  /* AUTOINSERTED TRACE */
	#endif

    //in case sting is changed to char* use new[] and strcpy here
    this->m_localname= rCopy.m_localname; 
    this->m_prefix= rCopy.m_prefix;
    this->m_uri= rCopy.m_uri;
    this->m_value= rCopy.m_value;
	if( (void *) &attribute != NULL && !attribute.empty())
	{
		list<Attribute*>::iterator itAttributeList = attribute.begin();
		while( itAttributeList != attribute.end())
		{
			m_PrefixList.push_back( (*itAttributeList)->getPrefix());
			itAttributeList++;
		}
	}
	if( rCopy.m_prefix.length() > 0)
	{
		m_PrefixList.push_back( rCopy.m_prefix.c_str());
	}
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Attribute", "Attribute", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

Attribute* Attribute::clone()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Attribute", "clone", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			Attribute* traceRet = (new Attribute(*this));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Attribute", "clone", this, 0,
					TRACETYPE_POINTER, sizeof(Attribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new Attribute(*this);
		#endif
	}

}

/*
 *
 */

int Attribute::serialize(SoapSerializer& pSZ) const
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Attribute", "serialize", this, 1,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ));	  /* AUTOINSERTED TRACE */
	#endif
    
    int intStatus= AXIS_FAIL;
    if (isSerializable())
    {        
        pSZ.serialize(" ", NULL);
        if(!m_prefix.empty())
        {            
            pSZ.serialize(m_prefix.c_str(), ":", NULL);
        }
        pSZ.serialize(m_localname.c_str(), "=\"", m_value.c_str(), "\"", NULL);
        intStatus= AXIS_SUCCESS;
    }
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (intStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Attribute", "serialize", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return intStatus;
		#endif
	}
    
}

int Attribute::serialize(SoapSerializer& pSZ, 
                         list<AxisChar*>& lstTmpNameSpaceStack,
						 const AxisChar *uri)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Attribute", "serialize", this, 3,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ),
					TRACETYPE_DATA, sizeof(list<AxisChar* >&), ((void*)&lstTmpNameSpaceStack),
					TRACETYPE_STRING, 0, ((void*)&uri));	  /* AUTOINSERTED TRACE */
	#endif
    
    int intStatus= AXIS_FAIL;
    if (isSerializable() && (!pSZ.getNamespaceURL( m_prefix).empty() || NULL!=uri))
    {        
        pSZ.serialize(" ", NULL);
        /*
         * User has provided the prefix. So we just have to serialilze. We will
		 *  not worry to declare the namespace at all. Because it is the users
		 *  responsibiltiy to add his/her namespace declaration seperately.
         */
        if(!m_prefix.empty() || NULL!=uri)
        {            
            pSZ.serialize(m_prefix.c_str(), ":", NULL);
        }
		/*
         * User hasn't provided the prefix. So we have to do the following.
		 *  - get the prefix from the Serializer
		 *  - if this is a new namespace, then also declare the namespace.
         */
        else if (!m_uri.empty())
        {
            bool blnIsNewNamespace = false;
            m_prefix = pSZ.getNamespacePrefix(m_uri.c_str(), 
                blnIsNewNamespace);
            if (blnIsNewNamespace)
            {
                lstTmpNameSpaceStack.push_back((AxisChar*)m_uri.c_str());
				pSZ.serialize("xmlns:", m_prefix.c_str(), "=\"", m_uri.c_str(), "\" ", NULL);
            }
            pSZ.serialize(m_prefix.c_str(), ":", NULL);
        }
        pSZ.serialize(m_localname.c_str(), "=\"", m_value.c_str(), "\"", NULL);
        intStatus= AXIS_SUCCESS;
    }
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (intStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Attribute", "serialize", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return intStatus;
		#endif
	}
    
}

bool Attribute::isSerializable() const
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Attribute", "isSerializable", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    bool bStatus= true;
    if(m_localname.empty())
    {
        bStatus= false;
    }
    	{
		#ifdef ENABLE_AXISTRACE
			bool traceRet = (bStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Attribute", "isSerializable", this, 0,
					TRACETYPE_BOOL, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return bStatus;
		#endif
	}

}

#ifdef UNIT_TESTING_ON

int Attribute::initializeForTesting()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("Attribute", "initializeForTesting", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    m_prefix = "pr";
    m_localname = "age";
    m_uri = "http://myurl.com";
    m_value = "25";
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("Attribute", "initializeForTesting", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

#endif

