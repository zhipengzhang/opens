#pragma warning (disable : 4786)
#ifndef XMEASURE_H
#define XMEASURE_H

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

class SCHEMA_EXPORT Measure
{
private :
	std::string _name;
	XCube* _parentcube;
	std::string _format;
	std::string _aggregator;
	std::string _column;
public: 
	const std::string& getName()const;
	XCube* getcube();
	const std::string& getFormat();
	const std::string& getAggregator();
	const std::string& getColumn();
	bool parserMeasure(XCube* pcube,xercesc::DOMElement* element);
	void setParentCube(XCube*);
	void print();
	xercesc::DOMElement *recursiveXML(xercesc::DOMDocument* doc);
	bool writeXML(const std::string &outputfile);
public:
   Measure& operator=(const Measure&);

   bool operator < (const Measure & c) const;

   bool operator == (const Measure & c) const;
       
};


EXPORT_STL_VECTOR(SCHEMA_EXPORT,Measure)

DWSCHEMA_CPP_NAMESPACE_END
#endif