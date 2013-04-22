#include <iostream>
#include <xercesc/util/TransService.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/util/XMLString.hpp> 
#include "DWSchemac/Level.h"
#include "DWSchemac/Member.h"

using namespace std;
using namespace xodbc;

DWSCHEMA_CPP_NAMESPACE_BEGIN

const XFieldInfo& Member::getInfo()
{
	return this->TubeInfo;
}



std::string& Member::getKey()
{
	return this->key;
}
 

void Member::printMe()
{ 
	std::cout<<this->key<<std::endl;
}

Member::Member(const xodbc::XFieldInfo&  info,const xodbc::XDBVariant & value,Level* l,Member* pm,std::string& str)
{
	    this->TubeInfo=info;
		this->_value=value;
		this->key=str;
		parentLevel=l;
		parentMember=pm;
}

xodbc::XDBVariant& Member::getValue()
{
	return (this->_value);
}

Level* Member::getLevel()
{
	return this->parentLevel;
}

std::vector<Member*> Member::getAllParents()
{
	std::vector<Member*> allparents;
    Member *tempparent=getParent();
	while(tempparent)
	{
		allparents.push_back(tempparent);
		tempparent=tempparent->getParent();
	}

	return allparents;
}

vector<Member*> Member::getChildrenMember()
{
	Level* temp=this->parentLevel->getChildLevel();
	if(temp)
	{
		return temp->getMember(this);
	}
	else
	{
		vector<Member*> ok;
		return ok;
	}
}

Member* Member::getParent()
{
	return this->parentMember;
}

Member::Member()
{
		parentLevel=NULL;
		parentMember=NULL;
}

Member::Member(const Member& m)
{
	this->_value=m._value;
	this->key=m.key;
	this->TubeInfo=m.TubeInfo;
	this->parentLevel=m.parentLevel;
	this->parentMember=m.parentMember;
}
Member& Member::operator=(const Member & m)
{
	if(&m==this)
	{
		return *this;
	}
	else
	{
		this->_value=m._value;
		this->TubeInfo=m.TubeInfo;
		this->parentLevel=m.parentLevel;
		this->parentMember=m.parentMember;
		this->key=m.key;
	}
	return *this;
}

bool Member::operator < (const Member & m) const
{
	return true;
}

bool Member::operator == (const Member & m) const
{
	return false;
}


DWSCHEMA_CPP_NAMESPACE_END