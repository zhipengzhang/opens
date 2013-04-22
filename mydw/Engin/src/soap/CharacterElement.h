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
 *
 */

/*
 * Revision 1.1  2004/05/25 samisa
 * Added copy constructure and clone for copy constructing derived classes
 */

/*
 * Revision 1.2  2004/06/13 roshan
 * Added doxygen comments to help autobuild API docs
 */

/*
 * Revision 1.3  2004/07/28 roshan
 * Added the method getLocalName().
 */

#if !defined(_CHARACTERELEMENT_H____OF_AXIS_INCLUDED_)

#define _CHARACTERELEMENT_H____OF_AXIS_INCLUDED_

#ifdef WIN32

#pragma warning (disable : 4786)

#endif

#include <axis/BasicNode.hpp>

#include "SoapSerializer.h"

/**
 * @class CharacterElement
 * @brief interface for the CharacterElement class.
 *
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */

class SoapSerializer;

class CharacterElement : public BasicNode
{

public:
    /**
      * This method is overridden to always return NULL because this is a 
      * CharacterElement. A user of a CharacterElement should not use this 
      * method.
      */
    IAttribute* getAttribute(AxisChar* pachPrefix, AxisChar* pachURI,
	    AxisChar* pachLocalname)
	{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "getAttribute", NULL, 3,
					TRACETYPE_STRING, 0, ((void*)&pachPrefix),
					TRACETYPE_STRING, 0, ((void*)&pachURI),
					TRACETYPE_STRING, 0, ((void*)&pachLocalname));	  /* AUTOINSERTED TRACE */
	#endif
	{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "getAttribute", NULL, 0,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}
}
    /**
      * This method is overridden to always return NULL because this is a CharacterElement.
      * A user of a CharacterElement should not use this method
      */
    IAttribute* getFirstAttribute()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "getFirstAttribute", NULL, 0);	  /* AUTOINSERTED TRACE */
	#endif
 	{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "getFirstAttribute", NULL, 0,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}
 }
                                                                                                                                                                            
    /**
      * This method is overridden to always return NULL because this is a CharacterElement.
      * A user of a CharacterElement should not use this method
      */    
    IAttribute* getLastAttribute()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "getLastAttribute", NULL, 0);	  /* AUTOINSERTED TRACE */
	#endif
 	{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "getLastAttribute", NULL, 0,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}
 }
                                                                                                                                                                            
    /**
      * This method is overridden to always return NULL because this is a CharacterElement.
      * A user of a CharacterElement should not use this method
      */    
    IAttribute* getNextAttribute()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "getNextAttribute", NULL, 0);	  /* AUTOINSERTED TRACE */
	#endif
 	{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "getNextAttribute", NULL, 0,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}
 }
    /**
      * This method is overridden to always return NULL because this is a CharacterElement.
      * A user of a CharacterElement should not use this method
      */
    IAttribute* getCurrentAttribute()
    {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "getCurrentAttribute", NULL, 0);	  /* AUTOINSERTED TRACE */
	#endif
 	{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "getCurrentAttribute", NULL, 0,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}
 }
    /** 
      * This method is overridden to always return NULL because this is a CharacterElement. 
      * A user of a CharacterElement should not use this method 
      * 
      * @param localname The local name of the attribute. 
      * @param prefix The prefix of the attribute. 
      * @param uri The namespace uri of the attribute. 
      * @param value The value of the attribute. 
      * 
      * @return Will always return NULL 
      */
    IAttribute* createAttribute(const AxisChar* localname,
            const AxisChar* prefix, const AxisChar* uri, const AxisChar* value) 
            {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "createAttribute", NULL, 4,
					TRACETYPE_STRING, 0, ((void*)&localname),
					TRACETYPE_STRING, 0, ((void*)&prefix),
					TRACETYPE_STRING, 0, ((void*)&uri),
					TRACETYPE_STRING, 0, ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif
 	{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "createAttribute", NULL, 0,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}
 }
    /** 
      * This method is overridden to always return NULL because this is a CharacterElement. 
      * A user of a CharacterElement should not use this method 
      * 
      * @param localname The local name of the attribute. 
      * @param prefix The prefix of the attribute. 
      * @param value The value of the attribute. 
      * 
      * @return Will always return NULL 
      */ 
    IAttribute* createAttribute(const AxisChar* localname,
            const AxisChar* prefix, const AxisChar* value) {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "createAttribute", NULL, 3,
					TRACETYPE_STRING, 0, ((void*)&localname),
					TRACETYPE_STRING, 0, ((void*)&prefix),
					TRACETYPE_STRING, 0, ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif
 	{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "createAttribute", NULL, 0,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}
 }
    /**
      * This method is overridden to always return NULL because this is a CharacterElement.
      * A user of a CharacterElement should not use this method
      *
      * @param localname The local name of the attribute.
      * @param value The value of the attribute.
      *
      * @return Will always return NULL
      */
    IAttribute* createAttribute(const AxisChar* localname,
            const AxisChar* value) {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "createAttribute", NULL, 2,
					TRACETYPE_STRING, 0, ((void*)&localname),
					TRACETYPE_STRING, 0, ((void*)&value));	  /* AUTOINSERTED TRACE */
	#endif
 	{
		#ifdef ENABLE_AXISTRACE
			IAttribute* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "createAttribute", NULL, 0,
					TRACETYPE_POINTER, sizeof(IAttribute), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}
 }
    bool operator ==( const CharacterElement &objChEle);
    /**
      * Sets the value of this Character Element
      *
      * @param pachValue The value to be set
      * @return AXIS_SUCCESS to indicate success.
      */    
    int setValue(const AxisChar* pachValue);
    /**
      * Gets and return the value of this Character Element
      *
      * @return The value of this Character Element.
      */    
    const AxisChar* getValue() const;
    /**
      * This method is overridden to return 0 always because this 
      * is a CharacterElement. 
      * A user of a CharacterElement should not use this method.
      *
      * @return Always return 0.
      */
    int getNoOfChildren() {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "getNoOfChildren", NULL, 0);	  /* AUTOINSERTED TRACE */
	#endif
	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (0);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "getNoOfChildren", NULL, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return 0;
		#endif
	}
}
    /**
      * This method is overridden to return NULL always because this 
      * is a CharacterElement. 
      * A user of a CharacterElement should not use this method.
      *
      * @return Always return NULL to indicate unsuccessfull operation.
      */
     BasicNode* getFirstChild() {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "getFirstChild", NULL, 0);	  /* AUTOINSERTED TRACE */
	#endif
	{
		#ifdef ENABLE_AXISTRACE
			BasicNode* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "getFirstChild", NULL, 0,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}
}
    /**
      * This method is overridden to return NULL always because this 
      * is a CharacterElement. 
      * A user of a CharacterElement should not use this method.
      *
      * @return Always return NULL to indicate unsuccessfull operation.
      */
    BasicNode* getLastChild() {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "getLastChild", NULL, 0);	  /* AUTOINSERTED TRACE */
	#endif
	{
		#ifdef ENABLE_AXISTRACE
			BasicNode* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "getLastChild", NULL, 0,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}
}
    /**
      * This method is overridden to return NULL always because this 
      * is a CharacterElement. 
      * A user of a CharacterElement should not use this method.
      *
      * @param iChildPosition The child position.
      * @return Always return NULL to indicate unsuccessfull operation.
      */
    BasicNode* getChild(int iChildPosition) {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "getChild", NULL, 1,
					TRACETYPE_INT, 0, ((void*)&iChildPosition));	  /* AUTOINSERTED TRACE */
	#endif
	{
		#ifdef ENABLE_AXISTRACE
			BasicNode* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "getChild", NULL, 0,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}
}
    /**
      * This method is overridden to return fail(AXIS_FAIL) always because this 
      * is a CharacterElement. 
      * A user of a CharacterElement should not use this method.
      *
      * @param sURI The namespace URI.
      * @return Always return fail (AXIS_FAIL) to indicate unsuccessfull 
      * operation.
      */
    int setURI(const AxisChar* sURI) {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "setURI", NULL, 1,
					TRACETYPE_STRING, 0, ((void*)&sURI));	  /* AUTOINSERTED TRACE */
	#endif
	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "setURI", NULL, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}
}
    /**
      * This method is overridden to return fail(AXIS_FAIL) always because this 
      * is a CharacterElement. 
      * A user of a CharacterElement should not use this method.
      *
      * @param pBasicNode The child to be added.
      * @return Always return fail (AXIS_FAIL) to indicate unsuccessfull 
      * operation.
      */
    int addChild(BasicNode* pBasicNode) {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "addChild", NULL, 1,
					TRACETYPE_POINTER, sizeof(BasicNode), ((void*)&pBasicNode));	  /* AUTOINSERTED TRACE */
	#endif
	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "addChild", NULL, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}
}
    /**
      * This method is overridden to return fail(AXIS_FAIL) always because this 
      * is a CharacterElement. 
      * A user of a CharacterElement should not use this method.
      *
      * @param sLocalName The localname.
      * @return Always return fail (AXIS_FAIL) to indicate unsuccessfull 
      * operation.
      */
    int setLocalName(const AxisChar* sLocalName) {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "setLocalName", NULL, 1,
					TRACETYPE_STRING, 0, ((void*)&sLocalName));	  /* AUTOINSERTED TRACE */
	#endif
	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "setLocalName", NULL, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}
}
    /**
      * This method is overridden to return fail(AXIS_FAIL) always because this 
      * is a CharacterElement. 
      * A user of a CharacterElement should not use this method.
      *
      * @param sPrefix The prefix.
      * @return Always return fail (AXIS_FAIL) to indicate unsuccessfull 
      * operation.
      */
    int setPrefix(const AxisChar* sPrefix) {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "setPrefix", NULL, 1,
					TRACETYPE_STRING, 0, ((void*)&sPrefix));	  /* AUTOINSERTED TRACE */
	#endif
	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_FAIL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "setPrefix", NULL, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_FAIL;
		#endif
	}
}
    int serialize(SoapSerializer& pSZ);
    /**
      * This method is actualy not used in this class. This method was just
      * included to adhere its interface.
      */
    int serialize(SoapSerializer& pSZ, 
        std::list<AxisChar*>& lstTmpNameSpaceStack) {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "serialize", NULL, 2,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ),
					TRACETYPE_DATA, sizeof(std:: list<AxisChar* >&), ((void*)&lstTmpNameSpaceStack));	  /* AUTOINSERTED TRACE */
	#endif
	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "serialize", NULL, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}
}
    /**
      * Returns the Node Type of this Character Element, which is 
      * CHARACTER_NODE.
      *
      * @return The Node Type of this Character Element, which is 
      * CHARACTER_NODE
      */
    NODE_TYPE getNodeType() const;
    /**
      * This method is overridden to return NULL always. A user of a 
      *  CharacterElement should not use this method.
      *
      * @return Returns NULL.
      */
    const AxisChar* getLocalName() {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "getLocalName", NULL, 0);	  /* AUTOINSERTED TRACE */
	#endif
	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "getLocalName", NULL, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}
}
    /**
      * This method is overridden to return NULL always. A user of a
      *  CharacterElement should not use this method.
      *
      * @return Returns NULL.
      */
    const AxisChar* getURI() {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "getURI", NULL, 0);	  /* AUTOINSERTED TRACE */
	#endif
	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "getURI", NULL, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}
}
    /**
      * This method is overridden to return NULL always. A user of a
      *  CharacterElement should not use this method.
      *
      * @return Returns NULL.
      */
    const AxisChar* getPrefix() {
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("CharacterElement", "getPrefix", NULL, 0);	  /* AUTOINSERTED TRACE */
	#endif
	{
		#ifdef ENABLE_AXISTRACE
			const AxisChar* traceRet = (NULL);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("CharacterElement", "getPrefix", NULL, 0,
					TRACETYPE_STRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return NULL;
		#endif
	}
}
    /**
      * The Constructor.
      *
      * @param sValue The value of the Character Element.
      */
    CharacterElement(const AxisChar* sValue);
    /**
      * The Constructor.
      */
    CharacterElement();
    CharacterElement(const CharacterElement& rCopy); 
    BasicNode* clone();   
    /**
      * The Destructor.
      */
    virtual ~CharacterElement();

};

#endif 

