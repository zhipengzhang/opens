#include <iostream>
#include <string>

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
#include <xercesc/framework/XMLFormatter.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/util/XMLString.hpp> 
#include <xercesc/util/OutOfMemoryException.hpp>

#include <xercesc/util/XMLUni.hpp>
#include <xercesc/framework/XMLFormatter.hpp>
#include <xercesc/util/XMLString.hpp> 
#include "DWSchemac/DataSource.h"


using namespace xercesc;
DWSCHEMA_CPP_NAMESPACE_BEGIN

DataSource& DataSource::operator=(const DataSource & c)
{
    this->_psword=c._psword;
	this->_URL=c._URL;
	this->_UserName=c._UserName;
	return *(this);
}

bool DataSource::operator < (const DataSource & c)  const
{
	return true;
}

bool DataSource::operator == (const DataSource & c) const
{
	if(this->_URL==c._URL)
	{
		return true;
	}
	else
	{
		return false;
	}
} 

DataSource::CUBETYPE DataSource::getDSType()
{
	return type_;
}


//get the parent schema
XSchema* DataSource::getSchema()
{
	return this->parentschema;
}
 
const std::string& DataSource::getPassWord()
{
	return this->_psword;
}

	//get the fact table
const std::string& DataSource::getURL()
{
	return this->_URL;
}
 
	//get the fact table
const std::string& DataSource::getUserName()
{
	return this->_UserName;
}  

void DataSource::print()
{
	std::cout<<"< DataSource type="<<this->type_;
	std::cout<<" url="<<this->_URL;
	std::cout<<" userName="<<this->_UserName;
	std::cout<<" passWord="<<this->_psword<<" >"<<std::endl;
}
 
bool DataSource::parserDataSource(XSchema* pschema,xercesc::DOMElement* element)
{
	this->parentschema=pschema;

	if(element)
	{
		    DOMNamedNodeMap *attributes;
			DOMNodeList *children =element->getChildNodes();
			DOMNode *tmpnode;
			std::string tmpstr=XMLString::transcode(element->getNodeName());
			if(tmpstr!="DataSource")
			{
				return false;
			}

			attributes=element->getAttributes();

			if(attributes)
			{
				for(int j=0;j<attributes->getLength();j++)
				{
					tmpnode=attributes->item(j);
					tmpstr=XMLString::transcode(tmpnode->getNodeName());
					if(tmpstr == "type")
					{
						this->type_ = (DataSource::CUBETYPE) atoi(XMLString::transcode(tmpnode->getNodeValue()));
						
					}
					else if(tmpstr=="url")
					{
						this->_URL=XMLString::transcode(tmpnode->getNodeValue());
					}
					else if(tmpstr=="passWord")
					{
						this->_psword=XMLString::transcode(tmpnode->getNodeValue());
					}
					else if(tmpstr=="userName")
					{
						this->_UserName =XMLString::transcode(tmpnode->getNodeValue());
					}
				}			
			}
			else
			{
				return false;
			}			 
	}
	else
	{
		
		return false;
	}
	return true;
}
 
xercesc::DOMElement *DataSource::recursiveXML(xercesc::DOMDocument* doc)
{
		DOMElement * DSElem = doc->createElement(XMLString::transcode("DataSource"));

		char buf[32];
        itoa(this->type_,buf,10); 
		DSElem -> setAttribute(XMLString::transcode("type"),XMLString::transcode(buf));
		if(this->_URL !="")
		DSElem -> setAttribute(XMLString::transcode("URL"),XMLString::transcode(this->_URL.c_str()));
		if(this->_UserName != "")
		DSElem -> setAttribute(XMLString::transcode("UserName"),XMLString::transcode(this->_UserName.c_str()));
		if(this->_psword != "")
		DSElem -> setAttribute(XMLString::transcode("passWord"),XMLString::transcode(this->_psword.c_str()));
					   
	return DSElem;
}

DataSource::DataSource()
{
	this->parentschema=NULL;
	this->_psword="";
	this->_URL="";
	this->_UserName="";
	this->type_ =DATABASETYPE;
}

DataSource::DataSource(const DataSource& d)
{
	this->_psword=d._psword;
	this->_URL=d._URL;
	this->_UserName=d._UserName;
	this->type_=d.type_;
}

DWSCHEMA_CPP_NAMESPACE_END