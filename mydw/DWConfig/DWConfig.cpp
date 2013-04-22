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
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include "dwxml.h"
#include "DWConfig/DWConfiguration.h"
#include "DWConfig/DWConfig.h"
#include "DWConfig/DWElement.h"
#include "DWElementImpl.h"

using namespace std;
using namespace xercesc;

std::string DWConfig::getValue(std::string name)
{
   std::vector<std::string> result = DWConfig::getValueVect(name);
   if(result.size()>1)
   {
	   return "";
   }
   else
   {
	   return result[0];
   }

}

std::vector<std::string> DWConfig::getValueVect(std::string name)
{
	std::vector<std::string> result;
	if(name == "" || this->xelement_ == NULL)
	{
		return result;
	}

	std::string tempstr = name;
	XElement * tmpel = xelement_;
	XElementList* li1 = NULL;  
	if(tempstr.find_first_of(".")>=0)
	{
		tempstr= tempstr.substr(tempstr.find_first_of(".")+1,tempstr.length());
		while(tempstr.length()>0)
		{   
			li1 = tmpel->getChildNodes();
			if(li1 == NULL)
			{
				break;
			}		
			tmpel =  li1->getElement(tempstr.substr(0,tempstr.find_first_of(".")));			
			if(tmpel == NULL)
			{
				break;		
			}
			int idx = tempstr.find_first_of(".");
			if(idx >= 0)
			{
				tempstr = tempstr.substr(idx+1,tempstr.length());
			}
			else
			{
				tempstr ="";
			}		
		}
	}
	

	if(tmpel!=NULL)
	{
		XElementList* li = tmpel->getChildNodes();
		if(tmpel->hasChildNodes())
		{
			for(int i=1;i<=li->getLength();i++)
			{
				result.push_back(li->item(i)->getNodeName());
			}
		}
		else
		{
			result.push_back(tmpel->getNodeValue());
		}
	}

	return result;
}

bool DWConfig::initialize(const std::string & file)
{
	if(file == "")
	{
		return false;
	}
    DWXML xml;
	DOMElement *element=xml.xmlParser(file);
	if(!element)
	{
		return false;
	}
    
	xelement_ = new XElementImpl(element);
	return true;
}

void DWConfig::reset()
{
	if(xelement_)
	{
		delete xelement_;
		xelement_ = NULL;
	}
	DWXML xml;
	DOMElement *element=xml.xmlParser(mFile);
	xelement_ = (new XElementImpl(element));
}

DWConfig::~DWConfig()
{
	delete xelement_;
	xelement_ = NULL;
}

std::string DWConfig::getName()
{
	return name_;
}
void DWConfig::print()
{
	if(xelement_)
	{
		xelement_->print();
	}
	else
	{
		cout<<"None"<<endl;
	}
}

XElement * DWConfig::getRoot()
{
	return xelement_;
}

DWConfig::DWConfig():mFile(""),name_(""),xelement_(NULL)
{
}

DWConfig::DWConfig(const std::string & name,const std::string & file):name_(name),
		                            mFile(file),xelement_(NULL)
{		
}
 
 
 


