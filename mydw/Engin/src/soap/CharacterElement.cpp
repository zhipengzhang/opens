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
 * Added copy constructure and clone for copy constructing derived classes
 * Also changed the constructor to call the base class constructer, 
 * rahter than working on base class attribute from derived class
 */
 
/* CharacterElement.cpp: implementation of the CharacterElement class. */

#include "CharacterElement.h"

#include "SoapSerializer.h"

#include <axis/GDefine.hpp>

CharacterElement::CharacterElement():BasicNode( NULL, CHARACTER_NODE) 
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "CharacterElement", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "CharacterElement", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

CharacterElement::CharacterElement(const AxisChar* pachValue):BasicNode(pachValue, CHARACTER_NODE) 
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "CharacterElement", this, 1,
					TRACETYPE_STRING, 0, ((void*)&pachValue));	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "CharacterElement", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

CharacterElement::CharacterElement(const CharacterElement& rCopy):BasicNode(rCopy)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "CharacterElement", this, 1,
					TRACETYPE_DATA, sizeof(CharacterElement&), ((void*)&rCopy));	  /* AUTOINSERTED TRACE */
	#endif
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "CharacterElement", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

BasicNode* CharacterElement::clone()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "clone", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			BasicNode* traceRet = (new CharacterElement(*this));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "clone", this, 0,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return new CharacterElement(*this);
		#endif
	}

}

CharacterElement::~CharacterElement()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "~CharacterElement", this, 0);	  /* AUTOINSERTED TRACE */
	#endif


	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "~CharacterElement", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

NODE_TYPE CharacterElement::getNodeType() const
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "getNodeType", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			NODE_TYPE traceRet = (m_iNodeType);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "getNodeType", this, 0,
					TRACETYPE_DATA, sizeof(NODE_TYPE), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_iNodeType;
		#endif
	}

}

int CharacterElement::serialize(SoapSerializer& pSZ)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "serialize", this, 1,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ));	  /* AUTOINSERTED TRACE */
	#endif

    if (m_pachValue != NULL)
    {
        pSZ.serialize(m_pachValue, NULL);
        	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "serialize", this, 1,
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
				axiscpp::AxisTrace::traceExit("CharacterElement", "serialize", this, 2,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}

    }
}

const AxisChar* CharacterElement::getValue() const
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "getValue", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (m_pachValue);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "getValue", this, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_pachValue;
		#endif
	}

}

int CharacterElement::setValue(const AxisChar* pachValue)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "setValue", this, 1,
					TRACETYPE_STRING, 0, ((void*)&pachValue));	  /* AUTOINSERTED TRACE */
	#endif

   if (pachValue !=NULL){
    m_pachValue = new AxisChar[strlen(pachValue)+1];
    strcpy(m_pachValue, pachValue);
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "setValue", this, 1,
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
				axiscpp::AxisTrace::traceExit("CharacterElement", "setValue", this, 2,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}

   }
}

bool CharacterElement::operator == ( const CharacterElement &objChEle) 
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "operator==", this, 1,
					TRACETYPE_DATA, sizeof(CharacterElement&), ((void*)&objChEle));	  /* AUTOINSERTED TRACE */
	#endif

    if (strcmp(objChEle.m_pachValue , m_pachValue) == 0)
    {
        	{
		#ifdef ENABLE_AXISTRACE
			bool traceRet = (true);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "operator==", this, 1,
					TRACETYPE_BOOL, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return true;
		#endif
	}

    }
    else
    {
        	{
		#ifdef ENABLE_AXISTRACE
			bool traceRet = (false);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "operator==", this, 2,
					TRACETYPE_BOOL, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return false;
		#endif
	}

    }
}

