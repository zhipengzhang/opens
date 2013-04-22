#ifdef WIN32

#pragma warning (disable : 4786)

#endif

#ifndef XSCHEMAS_H
#define XSCHEMAS_H

#include <vector>
#include <map>
#include <string>
#include "DWSchemac/VCAPPDefs.h"

DWSCHEMA_CPP_NAMESPACE_BEGIN

class XSchema;
class XCube;
class Dimension;
class Hierarchy;
class Level;
class Measure;
class Member;

typedef vector<Measure*> MeasureList;

class SCHEMA_EXPORT XSchemas
{
private:
	//vactor of schema in XSchemas
	std::vector<XSchema *> _xschemas;	
	static XSchemas  instance_; 
	
	XSchemas& operator=(const XSchemas& s);

	//constructor
    XSchemas(){};

	//copy constructor
	XSchemas(const XSchemas &);


	void operator delete(void *);

	//release all resources of schemas which created by user.
   	void Dispose();
public:
	static XSchemas& instance();
	
	~XSchemas();

	//remove schema from schemas by @schemaname
	bool removeSchema(const std::string &schemaname);

	//create the schema by xml file which path is xmlFile
    bool createSchema(const std::string &xmlFile);

	//get the schema which named schemaname
	XSchema* getSchema(const std::string &schemaname);

	std::string getSchemaString(const std::string & name);

	//All functions belowed are use for XMLA protocol
	vector<XSchema*> getALLSchemas();

	std::vector<MeasureList> getMeasures(string catalog,string cuben);
	
	vector<XCube *> getCubes(string catalog);

	vector<Dimension *> getDimensions(string catalog,string cube);

	vector<Hierarchy*> getHierarchies(string catalog,string cuben,string dimension);

	vector<Level *> getLevels(string catalog,string cuben,string dimensionn,string leveln);

	vector<Member *> getMembers(string catalog,string cuben,string dimensionn,string leveln,string membern);
};

DWSCHEMA_CPP_NAMESPACE_END
#endif