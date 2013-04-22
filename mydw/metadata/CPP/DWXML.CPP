//CXML.cpp
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
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
#include "DWSchemac/DWXML.h"

using namespace xercesc;


DWSCHEMA_CPP_NAMESPACE_BEGIN

DWXML::DWXML()
{
    try
    {   
        // Initialize Xerces-C++ library
        XMLPlatformUtils::Initialize();
    }
    catch(xercesc::XMLException & excp)  
    {
        char* msg = XMLString::transcode(excp.getMessage());
		std::cout<<"XML toolkit initialization error: "<<msg<<"\n";
        XMLString::release(&msg);
    }   
    
    //���� XercesDOMParser �������ڽ����ĵ� 
    m_DOMXmlParser = new XercesDOMParser;
}


xercesc::XercesDOMParser * DWXML::getDOMParser()
{
	return this->m_DOMXmlParser;
}

DWXML::~DWXML()
{
    try
    {        
        XMLPlatformUtils::Terminate();
    }
    catch(XMLException& excp)
    {
        char* msg = XMLString::transcode(excp.getMessage());
		std::cout<<"XML toolkit terminate error: "<<msg<<"\n";
        XMLString::release(&msg);
    } 
}

xercesc::DOMElement* DWXML::xmlParser(const std::string & xmlFile) throw( std::runtime_error )
{
//��ȡ�ļ���Ϣ״̬    
    
    //����DOMParser
    m_DOMXmlParser->setValidationScheme( XercesDOMParser::Val_Auto );
    m_DOMXmlParser->setDoNamespaces( false );
    m_DOMXmlParser->setDoSchema( false );
    m_DOMXmlParser->setLoadExternalDTD( false );
    
    try
    {
        //���� Xerces C++ ����ṩ�Ľ����ӿ� 
        m_DOMXmlParser->parse(xmlFile.c_str()) ;
        
        //���DOM��
		DOMDocument* xmlDoc = m_DOMXmlParser->getDocument();
	    DOMElement*  pRoot = xmlDoc->getDocumentElement();
		if (!pRoot )
		{
			throw(std::runtime_error( "empty XML document" ));
		}
		return pRoot;
	}
	catch( xercesc::XMLException& excp )
	{
		char* msg = xercesc::XMLString::transcode( excp.getMessage() );
		ostringstream errBuf;
		errBuf << "Error parsing file: " << msg << flush;
		XMLString::release( &msg );
	} 
	return NULL;
}

void DWXML::printElement(xercesc::DOMElement *element)
{
	int k;
	DOMNamedNodeMap *attributes;
    DOMNodeList *children =element->getChildNodes();
	DOMNode *tmpnode;
	std::cout<<"< "<<XMLString::transcode(element->getNodeName());
	attributes=element->getAttributes();
	int r= children->getLength();
	if(attributes)
	{
		for(int j=0;j<attributes->getLength();j++)
		{
			tmpnode=attributes->item(j);
			std::cout<<" "<<XMLString::transcode(tmpnode->getNodeName());
			std::cout<<"=";
			std::cout<<" "<<XMLString::transcode(tmpnode->getNodeValue());
		}
	}
	std::cout<<" >";
	if(element->hasChildNodes())
	{
		std::cout<<std::endl;
		std::cout<<"children.length:"<<r<<std::endl;
		for( k=0;k<children->getLength();k++)
		{
			std::cout<<k<<"="<<"type: "<<children->item(k)->getNodeType()<<std::endl;;
			if(children->item(k)->getNodeType()==1)
			{
				printElement((DOMElement *)children->item(k));
			}
			else if(children->item(k)->getNodeType()== 3)
			{			    
				cout<<" "<<XMLString::transcode(children->item(k)->getNodeValue());
			}
		}
	}
}

  
DWSCHEMA_CPP_NAMESPACE_END