#pragma warning (disable : 4786)
#ifndef XSCHEMA_H
#define XSCHEMA_H

#include <stdlib.h>
#include <string>
#include <vector>
#include <stdexcept>
#include "DWSchemac/VCAPPDefs.h"
#include "DWSchemac/DataSource.h"

using namespace std;
 


DWSCHEMA_CPP_NAMESPACE_BEGIN

class Dimension;
class XCube;

class SCHEMA_EXPORT XSchema
{
	
public:
	//get the schema name
	const std::string&  getName()const;

	//remove the cube named by cubename from the schema;
	bool removeCube(const std::string& cubename,XCube&);

	//remove the share  dimension named by dimensionname from schema
    bool removeShareDimension(const std::string& dimensionname,Dimension&);

	//get the named cube of cubename from schema
	XCube* getCube(const std::string& cubename);

	XCube* getCube(const char* cubename);

	//get dimension which name is dimensionname from schema 
	Dimension* getShareDimension(const std::string& dimensionname);

	//add cube into schema
    bool addCube(const XCube& cube);

	//add share dimension into schema
	bool addShareDimension(const Dimension& dimension);

	//parser schema by xml file which file path is xmlfile.
	bool parserSchema(const std::string& xmlFile);
     
	void print();

	void Dispose();

	DataSource* getDataSource();

	// XSchema write itself
	bool writeXML(const std::string &outputfile);
    
	std::vector<Dimension *> getDimensions();

	std::vector<XCube *> getCubes();

private:
	//schema name
	std::string _name;
    
	std::string _xmlstring;

	// the vector of share dimension in schema
	std::vector<Dimension *> _sharedimensiones;

	//the vector of cube in schema
	std::vector<XCube *> _cubes;

	DataSource* _datasource;
    
public:
	//constructor 
	XSchema(){_name="";_xmlstring="";}
	std::string getSchemaString(const std::string & name);
	//copy constructor
	XSchema(const XSchema &);

public:
	 XSchema& operator=(const XSchema &);
	 bool operator < (const XSchema & c)  const;
     bool operator == (const XSchema & c) const;
};

EXPORT_STL_VECTOR(SCHEMA_EXPORT,XSchema)

DWSCHEMA_CPP_NAMESPACE_END

#endif