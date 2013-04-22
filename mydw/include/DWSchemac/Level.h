#pragma warning (disable : 4786)

#ifndef XLEVEL_H
#define XLEVEL_H


#include <stdlib.h>
#include <string>
#include <vector>
#include <stdexcept>
#include "DWSchemac/VCAPPDefs.h"


using namespace std;

class xercesc::DOMDocument;
class xercesc::DOMElement;

DWSCHEMA_CPP_NAMESPACE_BEGIN


class Hierarchy;
class Member;
class Hierarchy;
class XProperty;


class SCHEMA_EXPORT Level
{
private :
	std::string _name;
	int _depth;
	Hierarchy* _hierarchy;
	std::string _column;
	std::vector<XProperty *> _xproperties;
	Level* _parentlevel;
	std::vector<Member *> _members;
public:
	enum LevelType
	{		
		NORMALLEVEL =1,
		ALLLEVEL = 2
	};

	LevelType _type;
public: 

	bool isAllLevel();
	//todo 
	unsigned long getMemberCount();
	

	Level* getChildLevel();
	std::vector<Member *> & getMembers();
    
	Member * getMember(std::string key,Member* parent);    
	std::vector<Member *>  getMember(Member* parent);

	void LoadMembers(Member* pm);

	void print();

	void printMembers();
    //get the name of the  Level
	const std::string& getName()const ;

	//get the Level depth in hierarchy
	int getDepth();

    //get the parent hierarchy
	Hierarchy* getHierarchy();

	//get the Level column in dimension table
	const std::string& getColumn();

	//get the level's properties
	std::vector<XProperty*>& getProperties();
    
	//get the property named pname
	XProperty* getProperty(const std::string &pname);
	//get the Level's parent Level
	Level* getParentLeval();
    
	void Dispose();
	void CleanMembers();
     
	void setHierarchy(Hierarchy *h);

	void setParentLevel(Level *h);
	//parser Level
	bool parserLevel(Hierarchy* phierarchy,Level * plevel,int depth,xercesc::DOMElement* element);

	xercesc::DOMElement *recursiveXML(xercesc::DOMDocument *doc);

	bool wrapXML(xercesc::DOMDocument *doc,xercesc::DOMElement *tempProperty);

	bool writeXML(const std::string &outputfile);

 
public:
	 Level & operator=(const Level&);
	 bool operator < (const Level & c) const; 
     
     bool operator == (const Level & c) const;
     
};


EXPORT_STL_VECTOR(SCHEMA_EXPORT,Level)

DWSCHEMA_CPP_NAMESPACE_END
#endif