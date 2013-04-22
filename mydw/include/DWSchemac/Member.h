#pragma warning (disable : 4786)
#ifndef MEMBER_H
#define MEMBER_H

#include <vector>
#include <XODBC/XODBCRecordset.h>
#include <XODBC/XODBCDataSource.h>
#include <XODBC/XODBCDatabase.h>
#include "DWSchemac/VCAPPDefs.h"

using namespace std;

DWSCHEMA_CPP_NAMESPACE_BEGIN

class Level;


class SCHEMA_EXPORT Member
{
	 friend class Hierarchy;
protected: 
   void setParentMem(Member * pm);
private :
   xodbc::XFieldInfo  TubeInfo;  
   xodbc::XDBVariant  _value;
   Level* parentLevel;
   Member* parentMember;
   std::string key;
   unsigned long ordinal_;
public:
    const xodbc::XFieldInfo& getInfo();
	xodbc::XDBVariant& getValue();
	Level* getLevel();
	Member* getParent();
	void printMe();
	std::string& getKey();
	std::vector<Member*> getAllParents();
    unsigned long getOrdinal(); 
	void setOrdinal(unsigned long ordinal);
public:
	Member();

	Member(Level* l,Member* pm,std::string& str):parentLevel(l),parentMember(pm),key(str){}

	Member(const xodbc::XFieldInfo&  info,const xodbc::XDBVariant & value,Level* l,Member* pm,std::string& str);

	Member(const Member& m);

	Member& operator=(const Member & m);

	bool operator < (const Member & m) const;

    bool operator == (const Member & m) const;

	vector<Member*> getChildrenMember();
};


EXPORT_STL_VECTOR(SCHEMA_EXPORT,Member)

DWSCHEMA_CPP_NAMESPACE_END
#endif