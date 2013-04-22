#pragma warning (disable : 4786)

#ifndef XCUBE_H
#define XCUBE_H


#include <stdlib.h>
#include <string>
#include <vector>
#include <stdexcept>
#include "DWSchemac/VCAPPDefs.h"


using namespace std;

class xercesc::DOMDocument;
class xercesc::DOMElement;


DWSCHEMA_CPP_NAMESPACE_BEGIN


class XSchema;
class Dimension;
class Measure;
class calcMember;


class SCHEMA_EXPORT XCube
{
private :
	//cube name
	std::string _name;

	//cube fact table
	std::string _fact;

	//the vector of dimension in cube
	std::vector<Dimension *> _dimensions;

	//the vector of measure in cube
	std::vector<Measure *> _measures;

	//the vector of calcmember in cube
	std::vector<calcMember *> _calcmembers;

	// the cube's parent schema
	XSchema* _parentschema;

	//todo defaultmeasure;
	std::string  _defaultMesure;


public:
	XCube(){};
	XCube(const XCube&);

	size_t getMeasureMemberCount()const;

public:
	//todo
	Dimension* getTimeDimension();

	//todo 
	Measure* getDefaultMeasure();

	//todo
	std::vector<Dimension*> getSharedDimension();

	//get the name of the cube
	const std::string& getName()const;

	//get the cube fact table
	const std::string& getFactTable();

	//get the parent Schema of cube
	XSchema* getSchema();

	//get the dimensiones  of cube
	std::vector<Dimension*>& getDimensions();

	//get the measures of cube
	std::vector<Measure*>& getMeasures();

	//get the calculate members of cube
	std::vector<calcMember*>& getCalMembers();

	//get the dimension in cube which named dimensionname
    Dimension* getDimension(const std::string & dimensioname);

	//get the measure in cube which named measurename
	Measure* getMeasure(const std::string& measurename);

	//get the calculate in cube which named calmembername
	calcMember* getCalMember(const std::string& calmembername);

	//add dimension into cube if add success return true else return false
    bool addDimension(const Dimension&);

	//reallocate All resources which had been allocated
	void Dispose();

	//add measure into cube if add success return true else return false
	bool addMeasure(const Measure&);

	//add calcMember into cube if add success return true else return false
	bool addMember(const calcMember &);

	//parser cube with apache xerces c  DOMElement
	bool parserCube(XSchema* pschema,xercesc::DOMElement* element);

	void print();

	xercesc::DOMElement *recursiveXML(xercesc::DOMDocument* doc);

	bool wrapXML(xercesc::DOMDocument *doc,xercesc::DOMElement *tempElem);

	bool writeXML(const std::string &outputfile);
public:
	XCube& operator=(const XCube& c);

	bool operator < (const XCube & c) const; 
 
    bool operator == (const XCube & c) const;

protected:

	//set the cube parent schema
    void setParentSchema(XSchema*);

	friend class XSchema;
};
 

EXPORT_STL_VECTOR(SCHEMA_EXPORT,XCube)

DWSCHEMA_CPP_NAMESPACE_END
#endif