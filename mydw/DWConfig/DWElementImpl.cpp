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
#include <xercesc/framework/XMLFormatter.hpp>
#include <xercesc/util/XMLString.hpp>  
#include "dwxml.h"
#include "DWELementImpl.h"
#include "DWConfig/DWElement.h"

using namespace std;
using namespace xercesc;

void XElementImpl::setValue(std::string value)
{
	value_ = value;
}

XElementImpl::XElementImpl():name_(""),value_(""),nodetype_(XELEMENT_NODE)
{
}

XElementImpl::XElementImpl(xercesc::DOMElement * element)
{	
	if(element==NULL)return;
	std::string tmpstr = XStrX(element->getNodeName()).localForm();
	nodetype_ = XELEMENT_NODE;
	this->name_ = tmpstr; 
	DOMNamedNodeMap *attributes;
	attributes=element->getAttributes();
	

	if(attributes)
	{
		for(int j=0;j<attributes->getLength();j++)
		{	
			DOMNode *tmpnode = NULL;
			tmpnode=attributes->item(j);
			tmpstr=XStrX((tmpnode->getNodeName())).localForm();
			attrs.setAttribute(tmpstr,XStrX(tmpnode->getNodeValue()).localForm());						
		}			
	}
	DOMNodeList *children =element->getChildNodes();
	if(element->hasChildNodes())
	{	 
		for(int k=0;k<children->getLength();k++)
		{
			if(children->item(k)->getNodeType()==3)
			{ 
			      std::string cc = XStrX(children->item(k)->getNodeValue()).localForm();				
				  if(cc=="")
				  {
				  }
				  else
				  {
					  this->value_ = std::string(cc);
				  }				  
			}

			if(children->item(k)->getNodeType()==1)
			{   	
				XElementImpl * tm =  new XElementImpl((DOMElement*)children->item(k));
				elements.addElement((tm));
			}
		}	 
	}
 
}

XElementImpl::~XElementImpl()
{
	if(hasAttributes())
	{
		for(int i=1;i<=getAttributes()->getLength();i++)
		{
			delete (XElementImpl *)(getAttributes()->item(i));
		}
	}

	if(hasChildNodes())
	{
		for(int i=1;i<=getChildNodes()->getLength();i++)
		{
			delete (XElementImpl*)(getChildNodes()->item(i));
		}
	}
}

XElementImpl::XElementImpl(std::string name,std::string value,XElement::XNodeType type):name_(name),
                                        value_(value),nodetype_(type)
{
}

std::string    XElementImpl::getNodeName() 
{
	return this->name_;
}

std::string    XElementImpl::getNodeValue() 
{
	return this->value_;
}

XElement::XNodeType   XElementImpl::getNodeType() 
{
	return this->nodetype_;
}

XAttributes* XElementImpl::getAttributes ()  
{
	if(this->nodetype_ == XATTRIBUTE_NODE)
	{
		return NULL;
	}

	return &attrs;
}

XElementList*  XElementImpl::getChildNodes () 
{
	if(this->nodetype_ == XATTRIBUTE_NODE)
	{
		return NULL;
	}
	return &elements;
}


void XElementImpl::print()
{
	if(getNodeType()==XELEMENT_NODE)
	{
	   cout<<" "<<getNodeName()<<"="<<getNodeValue()<<" type="<<getNodeType()<<endl;
	}
	else if(getNodeType()==XATTRIBUTE_NODE)
	{
		cout<<" "<<getNodeName()<<"="<<getNodeValue()<<" type="<<getNodeType()<<endl;
	}

	if(hasAttributes())
	{
			for(int i=1;i<=getAttributes()->getLength();i++)
			{
				getAttributes()->item(i)->print() ;
			}
	}

	if(hasChildNodes())
	{
		for(int i=1;i<=getChildNodes()->getLength();i++)
		{
			getChildNodes()->item(i)->print();
		}
	}
}

bool XElementImpl::hasAttributes()
{
	return attrs.getLength()>0?true:false;
}
bool XElementImpl::hasChildNodes()
{
	return elements.getLength()>0?true:false;
}

void XElementImpl::appendChildNode(XElement * rhs)
{
	assert(rhs!=NULL);
	switch(rhs->getNodeType())
	{
	case 	XELEMENT_NODE:
		{
			elements.addElement(rhs);
			break;
		}
	default:
		break;
	}	
}

void XElementImpl::removeChildNode(XElement * rhs)
{
	assert(rhs!=NULL);
	switch(rhs->getNodeType())
	{
	case 	XELEMENT_NODE:
		{
			elements.removeElement(rhs->getNodeName());

			break;
		}
	default:
		break;
	}

}

void XElementImpl::setAttribute(std::string name,std::string value)
{
	if(this->nodetype_ == XATTRIBUTE_NODE)
	{
		return ;
	}
    attrs.setAttribute(name,value);
}

void XElementImpl::removeAttribute(std::string name)
{
	if(this->nodetype_ == XATTRIBUTE_NODE)
	{
		return ;
	}
    attrs.removeAttribute(name);
}
