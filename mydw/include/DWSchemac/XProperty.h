#pragma warning (disable : 4786)
#ifndef XPROPERTY_H
#define XPROPERTY_H


#include <stdlib.h>
#include <string>
#include <vector>
#include <stdexcept>
#include "DWSchemac/VCAPPDefs.h"

using namespace std;




DWSCHEMA_CPP_NAMESPACE_BEGIN


class xercesc::DOMElement;

class xercesc::DOMDocument;

class Level;


class SCHEMA_EXPORT XProperty
{
private :
	std::string _name;
	std::string _column;
	std::string _type;
	Level* _parentLevel;
public:
	XProperty();
	XProperty(const XProperty & oP);
    
	const std::string& getName()const;
	const std::string& getColumn();
	const std::string& getType();

	void setLevel(Level* l);

	Level* getLevel();

	bool parserProperty(Level * plevel,xercesc::DOMElement* element);

	void print();

	xercesc::DOMElement *recursiveXML(xercesc::DOMDocument *doc);

	bool writeXML(const std::string &outputfile);
public:
	XProperty& operator=(const XProperty&);

	bool operator < (const XProperty & c)  const;
   
	bool operator == (const XProperty & c) const;
      
 
};


EXPORT_STL_VECTOR(SCHEMA_EXPORT,XProperty)

DWSCHEMA_CPP_NAMESPACE_END
#endif