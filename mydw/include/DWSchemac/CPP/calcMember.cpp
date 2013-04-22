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


#include "DWSchemac/XCube.h"
#include "DWSchemac/calcMember.h"
#include "DWSchemac/DWXML.h"




DWSCHEMA_CPP_NAMESPACE_BEGIN

using namespace xercesc;

void calcMember::print()
{
	std::cout<<"< calcMember Name="<<this->_name;
	std::cout<<" Formula="<<this->_formula;
	std::cout<<" FormatString="<<this->_format<<" >\n";
}
void calcMember::setParentCube(XCube *pcube)
{
	this->_parentcube=pcube;
}

XCube* calcMember::getCube()
{
	return this->_parentcube;
}

const std::string& calcMember::getFormula()
{
	return this->_formula;
}

const std::string& calcMember::getFormat()
{
	return this->_format;
}
calcMember& calcMember::operator =(const calcMember& cm)
{
	this->_format=cm._format;
	this->_formula=cm._formula;
	this->_name=cm._name;
	this->_parentcube=cm._parentcube;
	return *(this);
}

bool calcMember::operator < (const calcMember & c)  const
{
	return true;
}

bool calcMember::operator == (const calcMember & c) const
{
	if(_name==c.getName())
	{
		return true;
	}
	else
	{
		return false;
	}
}

const std::string& calcMember::getName()const
{
	return this->_name;
}

bool calcMember::parserCalMember(XCube* pcube,xercesc::DOMElement* element)
{
	this->_parentcube=pcube; 
	if(element)
	{
		    DOMNamedNodeMap *attributes;
			DOMNodeList *children =element->getChildNodes();
			DOMNode *tmpnode;
			std::string tmpstr=XMLString::transcode(element->getNodeName());
			if(tmpstr!="CalculatedMember")
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
					if(tmpstr=="name")
					{
						this->_name=XMLString::transcode(tmpnode->getNodeValue());
					}
					else if(tmpstr=="formatString")
					{
						this->_format =XMLString::transcode(tmpnode->getNodeValue());
					}
					else if(tmpstr=="formula")
					{
						this->_formula=XMLString::transcode(tmpnode->getNodeValue());
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
		
		return true;
	}
	return true;
}

xercesc::DOMElement *calcMember::recursiveXML(xercesc::DOMDocument* doc)
{
	DOMElement* calcMemberElem = doc->createElement(XMLString::transcode("calcMember"));

	if(this->_name != "")
		calcMemberElem->setAttribute(XMLString::transcode("name"),XMLString::transcode(this->_name.c_str()));
	if(this->_format != "")
		calcMemberElem->setAttribute(XMLString::transcode("format"),XMLString::transcode(this->_format.c_str()));	
	if(this->_formula != "")
		calcMemberElem->setAttribute(XMLString::transcode("formula"),XMLString::transcode(this->_formula.c_str()));	

	return calcMemberElem;
}

bool calcMember::writeXML(const std::string &outputfile)
{
	DWXML xml;
	xercesc::XercesDOMParser *m_DOMXmlParser1=xml.getDOMParser();

	m_DOMXmlParser1->setValidationScheme( XercesDOMParser::Val_Auto );
	m_DOMXmlParser1->setDoNamespaces( false );
	m_DOMXmlParser1->setDoSchema( false );
	m_DOMXmlParser1->setLoadExternalDTD( false );


	XMLCh temp2[100];
	XMLString::transcode("Core", temp2, 99);
    DOMImplementation* impl2 =  DOMImplementationRegistry::getDOMImplementation(temp2);
	DOMDocument* doc  = impl2->createDocument(
                           0,                    // root element namespace URI.
						   XMLString::transcode("Schema"),         // root element name
                           0);                   // document type object (DTD).
	if (impl2 != NULL)
       {
           try
           {
			   if(XCube *tempcube =this->getCube())
			   {
				     
					DOMElement* calcMemberElem = doc->createElement(XMLString::transcode("Measure"));

					if(this->_name != "")
					calcMemberElem->setAttribute(XMLString::transcode("name"),XMLString::transcode(this->_name.c_str()));
					if(this->_format != "")
					calcMemberElem->setAttribute(XMLString::transcode("formatString"),XMLString::transcode(this->_format.c_str()));	
					if(this->_formula != "")
					calcMemberElem->setAttribute(XMLString::transcode("formula"),XMLString::transcode(this->_formula.c_str()));	
					
					if(tempcube->wrapXML(doc,calcMemberElem) == false)
					{
						cout<<"fail";
						return false;
					}
			   }
		   }
		   catch (const OutOfMemoryException &)
           {
               XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl;
               return false;
           }
	  
		   
           catch (const DOMException& e)
           {
               XERCES_STD_QUALIFIER cerr << "DOMException code is:  " << e.code << XERCES_STD_QUALIFIER endl;
               return false;
           }
           catch (...)
           {
               XERCES_STD_QUALIFIER cerr << "An error occurred creating the document" << XERCES_STD_QUALIFIER endl;
				 return false;
           }
	   }
	  else
	  {return false;}

	  //use DOMwriter for export XML file

	  //Writer Ini
	 bool bRet = true;
	 XMLCh tempStr[100];
     XMLString::transcode("LS", tempStr, 99);
	 DOMImplementation *impl         = DOMImplementationRegistry::getDOMImplementation(tempStr);
     DOMWriter         *m_pWriter = ((DOMImplementationLS*)impl)->createDOMWriter();

	 //set XML File in "UTF-8"
	 XMLCh *encoding = XMLString::transcode("UTF-8");

	 m_pWriter -> setEncoding(encoding);

     // DOMDocument*                m_pDoc;
	 const char * outfile = outputfile.c_str();
     XMLFormatTarget*  m_pFormatTarget = new LocalFileFormatTarget(outfile);

	 

     // construct the LocalFileFormatTarget
     // m_pFormatTarget = new LocalFileFormatTarget(szPath);
    
     // serialize a DOMNode to the local file "myXMLFile.xml"
	 //Write File in UTF-8
     bRet = m_pWriter->writeNode(m_pFormatTarget, *doc);

     if (bRet == false)
     {
        return false;
     }
 	 else
	 {
		try
		{
			// optionally, you can flush the buffer to ensure all contents are written
			m_pFormatTarget->flush();
			delete m_pFormatTarget;
			delete m_DOMXmlParser1;
			delete m_pWriter;
			doc->release();
			XMLPlatformUtils::Terminate();
            
			return true;
		}
		catch (const OutOfMemoryException&)
        {
            XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl;
		    
			return false;
        }
        catch (XMLException& e)
        {
            XERCES_STD_QUALIFIER cerr << "An error occurred during creation of output transcoder. Msg is:"
                << XERCES_STD_QUALIFIER endl
                << XMLString::transcode(e.getMessage()) << XERCES_STD_QUALIFIER endl;
			return false;
        }
	}
}

DWSCHEMA_CPP_NAMESPACE_END