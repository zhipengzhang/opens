#pragma warning (disable : 4786)
#ifndef XDATASOURCE_H
#define XDATASOURCE_H

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


class SCHEMA_EXPORT DataSource
{
public:
	enum CUBETYPE
	{
		DATABASETYPE = 1,
		FILETYPE = 2		
	};
public:
	
	CUBETYPE getDSType();

	//get the  URL
	const std::string&  getURL() ;	 

	const std::string&  getUserName() ;	 

	const std::string&  getPassWord() ;	 

 	XSchema* getSchema(); 

	//parser DataSource  
	bool parserDataSource(XSchema* pschema,xercesc::DOMElement* element);
     
	void print();

	// XSchema write itself
	xercesc::DOMElement * recursiveXML(xercesc::DOMDocument* doc);

private:
	
    CUBETYPE type_;

	std::string _URL;

	std::string _UserName;

	std::string _psword;
	
	XSchema* parentschema;

public:
	//constructor 
	DataSource();

	//copy constructor
	DataSource(const DataSource &);

public:
	 DataSource& operator=(const DataSource &);
	 bool operator < (const DataSource & c)  const;
     bool operator == (const DataSource & c) const;
};

EXPORT_STL_VECTOR(SCHEMA_EXPORT,DataSource)

DWSCHEMA_CPP_NAMESPACE_END

#endif