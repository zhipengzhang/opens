#pragma warning (disable : 4786)

#ifndef XCALCMEMBER_H
#define XCALCMEMBER_H



#include <stdlib.h>
#include <string>
#include <vector>
#include <stdexcept>
#include "DWSchemac/VCAPPDefs.h"

using namespace std;

class xercesc::DOMElement;
class xercesc::DOMDocument;

DWSCHEMA_CPP_NAMESPACE_BEGIN

class XCube;



class SCHEMA_EXPORT calcMember
{
private :
	std::string _name;
	XCube* _parentcube;
	std::string _formula;
	std::string _format;

public: 
	const std::string& getName()const;
	XCube* getCube();
	const std::string& getFormula();
	const std::string& getFormat();
	bool parserCalMember(XCube* pcube,xercesc::DOMElement* element);
	void setParentCube(XCube *);

	void print();
	xercesc::DOMElement *recursiveXML(xercesc::DOMDocument* doc);

	bool writeXML(const std::string &outputfile);
public:
	 calcMember& operator=(const calcMember&); 

	 bool operator < (const calcMember & c)  const;
     
     bool operator == (const calcMember & c) const;
};


EXPORT_STL_VECTOR(SCHEMA_EXPORT,calcMember)

DWSCHEMA_CPP_NAMESPACE_END
#endif