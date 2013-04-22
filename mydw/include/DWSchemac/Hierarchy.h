#pragma warning (disable : 4786)

#ifndef XHIERARCHY_H
#define XHIERARCHY_H



#include <stdlib.h>
#include <string>
#include <vector>
#include <stdexcept>
#include "DWSchemac/VCAPPDefs.h"


using namespace std;

class xercesc::DOMElement;
class xercesc::DOMDocument;


DWSCHEMA_CPP_NAMESPACE_BEGIN

class Member;
class Dimension;
class Level;

class SCHEMA_EXPORT Hierarchy
{
private :
	std::string _name;
	std::vector<Level *> _leveles;
	std::string			_primarykey;
	Dimension*			_parentdimension;
	std::string			_allmembername;
	bool				_hasAll;
	std::string			_defaultmember;
	
	std::string _facttable;
	bool LoadMemberStuts;

public: 

	size_t getMemberCount();
	
	//get the fact table
	const std::string &getFactTable();

	//todo
	std::string  getAllMemberName();

	//todo
	std::auto_ptr<Member> getDefaultMember();

    static unsigned int getMemberOrdinal(bool flag = true);

	void printMembers();

	void LoadMembers();
	void print();
	//get the Hierarchy name
	std::string getName()const ;

	//get the level named olevelname in hierarchy
	Level* getLevel(const std::string& olevelname);

	//get the primarykey of hierarchy
	const std::string& getPrimaryKey();

	//get if has all
	bool hasAll();
    
	void setDimension(Dimension* dp);
	std::vector<Level*> getLeveles();

	//get the parent dimension of hierarchy
	Dimension* getDimension();

	//parser hierarchy 
	bool parserHierarchy(Dimension* pdimension,xercesc::DOMElement* element);

	void Dispose();
	void CleanMembers();

	xercesc::DOMElement *recursiveXML(xercesc::DOMDocument* doc);

	bool wrapXML(xercesc::DOMDocument *doc,xercesc::DOMElement *templevel);

	bool writeXML(const std::string &outputfile);
public:
	 Hierarchy& operator=(const Hierarchy&);

	 bool operator < (const Hierarchy & c) const; 

     bool operator == (const Hierarchy & c) const;
};


EXPORT_STL_VECTOR(SCHEMA_EXPORT,Hierarchy)


DWSCHEMA_CPP_NAMESPACE_END
#endif