
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
#include <xercesc/util/XMLString.hpp> 
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>

using namespace xercesc;

#include "DWSchemac/DWXML.h"
#include "DWSchemac/Level.h"
#include "DWSchemac/XProperty.h"

using namespace std;



DWSCHEMA_CPP_NAMESPACE_BEGIN

XProperty & XProperty::operator =(const XProperty & p)
{
	this->_column=p._column;
	this->_name=p._name;
	this->_parentLevel=NULL;
	this->_type=p._type;
	return *(this);
}

void XProperty::setLevel(Level* l)
{
	this->_parentLevel=l;
}

bool XProperty::operator < (const XProperty & c)  const
{
	return true;
}

bool XProperty::operator == (const XProperty & c) const
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

XProperty::XProperty()
{
		_name="";
		_column="";
		_type="";
}

XProperty::XProperty(const XProperty & oP)
{		
	this->_column=oP._column;
	this->_name=oP._name;
	this->_parentLevel=oP._parentLevel;
	this->_type=oP._type;
}

const std::string& XProperty::getName()const
{
	return this->_name; 
}

Level* XProperty::getLevel()
{
	return this->_parentLevel;
}

const std::string& XProperty::getColumn()
{
	return this->_column ;
}

const std::string& XProperty::getType()
{
	return this->_type; 
}


void XProperty::print()
{
	std::cout<<"< Property Name="<<this->_name;
	std::cout<<" Column="<<this->_column;
	std::cout<<" Type="<<this->_type<<" >\n";
}

bool XProperty::parserProperty(Level * plevel,xercesc::DOMElement* element)
{
	this->_parentLevel=plevel;
	std::string tmpstr;
	if(element)
	{
		    DOMNamedNodeMap *attributes;
			DOMNodeList *children =element->getChildNodes();
			DOMNode *tmpnode;
			std::string tmpstr=XMLString::transcode(element->getNodeName());
			if(tmpstr!="Property")
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
					else if(tmpstr=="column")
					{
						this->_column=XMLString::transcode(tmpnode->getNodeValue());
					}
					else if(tmpstr=="type")
					{
						this->_type=XMLString::transcode(tmpnode->getNodeValue());
					}	
				}			
			}			
	}
	else
	{
		
		return false;
	}
	return true;
}

xercesc::DOMElement *XProperty::recursiveXML(xercesc::DOMDocument *doc)
{
	DOMElement* PropertyElem = doc->createElement(XMLString::transcode("Property"));

	if(this->_name != "")
		PropertyElem->setAttribute(XMLString::transcode("name"),XMLString::transcode(this->_name.c_str()));
	if(this->_column != "")
		PropertyElem->setAttribute(XMLString::transcode("column"),XMLString::transcode(this->_column.c_str()));	
	if(this->_type != "")
		PropertyElem->setAttribute(XMLString::transcode("type"),XMLString::transcode(this->_type.c_str()));	


	return PropertyElem;

}

bool XProperty::writeXML(const std::string &outputfile)
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
			   if(Level *templevel =this->getLevel())
			   {
				     
					DOMElement* PropertyElem = doc->createElement(XMLString::transcode("Property"));

					if(this->_name != "")
					PropertyElem->setAttribute(XMLString::transcode("name"),XMLString::transcode(this->_name.c_str()));
					if(this->_column != "")
					PropertyElem->setAttribute(XMLString::transcode("column"),XMLString::transcode(this->_column.c_str()));	
					if(this->_type != "")
					PropertyElem->setAttribute(XMLString::transcode("type"),XMLString::transcode(this->_type.c_str()));	
					
					if(templevel->wrapXML(doc,PropertyElem) == false)
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