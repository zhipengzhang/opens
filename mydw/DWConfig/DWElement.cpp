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
#include <xercesc/util/XMLString.hpp>  
#include <iostream>
#include <vector>
#include "DWConfig/DWElement.h"
#include "DWELementImpl.h"
#include "dwxml.h"

using namespace std;
using namespace xercesc;


XElement* XElement::createElement(std::string name,std::string value,XElement::XNodeType type)
 {
	 if(name == "")
	 {
		 return NULL;
	 }

	 return (XElement*)(new XElementImpl(name,value,type));
 }


XElement* XAttributes::item(unsigned int it)
{
	if(it<=attributes_.size() && it > 0)
	{
	    return attributes_[it-1];
	}
    else
	{
		return NULL;
	}
}

unsigned int  XAttributes::getLength()
{
	return attributes_.size();
}

bool XAttributes::hasAttributes()
{
	return attributes_.size()>0?true:false;
}

std::string XAttributes::getAttribute(std::string name)  
{
	if(name == "") return "";
	for(int i=0;i<attributes_.size();i++)
	{
		if(name == attributes_[i]->getNodeName())
		{
			return attributes_[i]->getNodeValue();
		}
	}

	return "";
}  

void XAttributes::setAttribute(std::string name,std::string value)
{
	if(name == "") return;
	for(int i=0;i<attributes_.size();i++)
	{
		if(name == attributes_[i]->getNodeName())
		{
			attributes_[i]->setValue(value);
		}
	}
   
	XElementImpl* temp = new XElementImpl(name,
		value,XElement::XATTRIBUTE_NODE);
	attributes_.push_back((temp));
}

void XAttributes::removeAttribute(std::string name)
{
	if(name == "") return;
	
	std::vector<XElement*>::iterator itb = attributes_.begin();
	for(;itb<attributes_.end();itb++)
	{
		if(name == ((XElement*)itb)->getNodeName())
		{
			 attributes_.erase(itb);
		}
	}
}
 

XElement* XElementList::item(unsigned int it)
{
	if(it<=elements_.size() && it > 0)
	{
	    return elements_[it-1];
	}
    else
	{
		return NULL;
	}
}
unsigned int  XElementList::getLength()
{
	return elements_.size();
}

bool XElementList::hasChildNodes()
{
	return elements_.size()>0?true:false;
}

XElement* XElementList::getElement(std::string name)
{
	if(name == "") return NULL;
	for(int i=0;i<elements_.size();i++)
	{
		if(XStrX::toLower(name) == XStrX::toLower(elements_[i]->getNodeName()))
		{
			return (XElement*)elements_[i];
		}
	}

	return NULL;
}

void XElementList::addElement(XElement* rhs)
{
	if(rhs==NULL) return;	 
	elements_.push_back(rhs);
}

void XElementList::removeElement(std::string name)
{

	if(name == "") return;
	
	std::vector<XElement*>::iterator itb = elements_.begin();
	for(;itb<elements_.end();itb++)
	{
		if(name == ((XElement*)itb)->getNodeName())
		{
			 elements_.erase(itb);
		}
	}
}
 