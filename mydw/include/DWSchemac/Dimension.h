#pragma warning (disable : 4786)

#ifndef XDIMENSION_H
#define XDIMENSION_H



#include <stdlib.h>
#include <string>
#include <vector>
#include <stdexcept>
#include "DWSchemac/VCAPPDefs.h"


using namespace std;

class xercesc::DOMElement;
class xercesc::DOMDocument;

DWSCHEMA_CPP_NAMESPACE_BEGIN

class XSchema;
class XCube;
class Hierarchy;

class SCHEMA_EXPORT Dimension
{

public:
	enum DimensionType
	{
		TimeDimension = 1,
		StandardDimension =3
	};
private :

	//is Shared dimension
	bool         _isShared;

	//dimension name
	std::string _name;

	//the dimension's parent schema
	XSchema* _parentschema;

	//the dimension's parent cube
	XCube* _parentcube;

	//dimension Type which one of the StandardDimension or TimeDimension
	DimensionType  _type;
	
	//foreignkey
	std::string _foreignkey;

	std::string _defHierarchy;
	//the hierarchies  in dimension
	std::vector<Hierarchy *> _hierarchyies;

	//dimension_ordinal
	size_t mOrdinal;
public: 
	size_t getOrdinal()const;

	//todo
	DimensionType getDimensionType()const;

	//todo 
	bool isSharedDimension();

	//todo
	bool isTimeDimension()const;

	//todo
	Hierarchy* getDefaultHierarchy();

	//todo
	Hierarchy* getHierarchy(const std::string & name);

	std::vector<Hierarchy *>  getHierarchies();

	//get the name of dimension
	const std::string& getName()const;

	//get the parent schema
	XSchema* getSchema();

	//get the parent cube
	XCube* getCube();

	//get the foreign key
	const std::string& getForeignKey();

	bool parserDimension(XSchema* pschema,xercesc::DOMElement* element,size_t ordinal);

	bool parserDimension(XCube* pcube,xercesc::DOMElement* element,size_t ordinal);

    void setForeignKey(const std::string& foreignKey);
	
    void setName(const std::string& name);
	
	void setCubeDimension(XCube * cube);

	void setParentSchema(XSchema*);

	void print();

	void Dispose();

	xercesc::DOMElement *recursiveXML(xercesc::DOMDocument* doc);

	bool wrapXML(xercesc::DOMDocument *doc,xercesc::DOMElement *hierarchyelem);

	bool writeXML(const std::string &outputfile);

    Dimension & operator=(const Dimension &);

	bool operator < (const Dimension & c)  const;

    bool operator == (const Dimension & c) const;
       
};


EXPORT_STL_VECTOR(SCHEMA_EXPORT,Dimension)

DWSCHEMA_CPP_NAMESPACE_END
#endif