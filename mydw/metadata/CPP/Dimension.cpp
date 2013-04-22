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

#include "DWSchemac/Hierarchy.h"
#include "DWSchemac/Dimension.h"
#include "DWSchemac/XCube.h"
#include "DWSchemac/DataSource.h"
#include "DWSchemac/XSchema.h"
#include "DWSchemac/DWXML.h"

using namespace xercesc;

DWSCHEMA_CPP_NAMESPACE_BEGIN

Dimension& Dimension::operator=(const Dimension & c)
{
	this->_facttable=c._facttable;
	this->_foreignkey=c._foreignkey;   
	this->_name=c._name;
	this->_parentcube=c._parentcube;
	this->_parentschema=c._parentschema;
	for(int i=0;i<c._hierarchyies.size();i++)
	{

	        Hierarchy * tmph=new Hierarchy; 	   
			*tmph=*(c._hierarchyies[i]);
			tmph->setDimension(this);
            this->_hierarchyies.push_back(tmph);
	}
	return *(this);
}

bool Dimension::operator < (const Dimension & c)  const
{
	return true;
}

bool Dimension::operator == (const Dimension & c) const
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
void Dimension::Dispose()
{
	int i=0;
	int count=this->_hierarchyies.size();
	for(i=0;i<count;i++)
	{
		this->_hierarchyies[i]->Dispose();
		delete _hierarchyies[i];
		_hierarchyies[i]=NULL;
		_hierarchyies.pop_back();
	}
}

//get the parent schema
XSchema* Dimension::getSchema()
{
	return this->_parentschema;
}

	//get the parent cube
XCube* Dimension::getCube()
{
	return this->_parentcube;
}

	//get the foreign key
const std::string& Dimension::getForeignKey()
{
	return this->_foreignkey;
}

	//get the fact table
const std::string& Dimension::getFactTable()
{
	return this->_facttable;
}

Hierarchy* Dimension::getHierarchy(const std::string& oname)
{
	for(int i=0;i<this->_hierarchyies.size();i++)
	{
		if(this->_hierarchyies[i]->getName()==oname)
		{
			return _hierarchyies[i];
		}
	}
	return NULL;
}


std::vector<Hierarchy *> Dimension::getHierarchies()
{
 	return _hierarchyies; 
}


void Dimension::setForeignKey(const std::string& foreignKey)
{
	_foreignkey=foreignKey;
}

void Dimension::setName(const std::string& name)
{
	_name=name;
}
void Dimension::setCubeDimension(XCube * cube)
{
	_parentcube=cube;
	_parentschema=NULL;
}

void Dimension::print()
{
	std::cout<<"< Dimension Name="<<this->_name;
	std::cout<<" TableName="<<this->_facttable;
	std::cout<<" ForeignKey="<<this->_foreignkey<<" >"<<std::endl;
	int i=0;
	for(i=0;i<this->_hierarchyies.size();i++)
	{
		this->_hierarchyies[i]->print();
	}
}
void Dimension::setParentSchema(XSchema* pschema)
{
	this->_parentcube=NULL;
	this->_parentschema=pschema;
}

const std::string& Dimension::getName()const
{
	return _name;
}

bool Dimension::parserDimension(XSchema* pschema,xercesc::DOMElement* element)
{
	this->_parentschema=pschema;
	this->_parentcube=NULL;

	if(element)
	{
		    DOMNamedNodeMap *attributes;
			DOMNodeList *children =element->getChildNodes();
			DOMNode *tmpnode;
			std::string tmpstr=XMLString::transcode(element->getNodeName());
			if(tmpstr!="Dimension")
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
					else if(tmpstr=="tableName")
					{
						this->_facttable=XMLString::transcode(tmpnode->getNodeValue());
					}
					else if(tmpstr=="foreignKey")
					{
						this->_foreignkey =XMLString::transcode(tmpnode->getNodeValue());
					}
				}			
			}
			else
			{
				return false;
			}

			if(element->hasChildNodes())
			{	 
				for(int k=0;k<children->getLength();k++)
				{
					if(children->item(k)->getNodeType()==1)
					{   
						DOMElement* tmpelement=(DOMElement*)children->item(k);
						tmpstr=XMLString::transcode(tmpelement->getNodeName());
						if(tmpstr=="Hierarchy")
						{
						   Hierarchy *hierarchy=new Hierarchy;	
						   if(hierarchy->parserHierarchy(this,tmpelement))
						   {
								this->_hierarchyies.push_back(hierarchy);
						   }
						   else
						   {
							   return false;
						   }
						}						
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

bool Dimension::parserDimension(XCube* pcube,xercesc::DOMElement* element)
{
	this->_parentschema=NULL;
	this->_parentcube=pcube;
	if(element)
	{
		    DOMNamedNodeMap *attributes;
			DOMNodeList *children =element->getChildNodes();
			DOMNode *tmpnode;
			std::string tmpstr=XMLString::transcode(element->getNodeName());
			if(tmpstr!="Dimension")
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
					else if(tmpstr=="tableName")
					{
						this->_facttable=XMLString::transcode(tmpnode->getNodeValue());
					}
					else if(tmpstr=="foreignKey")
					{
						this->_foreignkey =XMLString::transcode(tmpnode->getNodeValue());
					}
				}			
			}
			else
			{
				return false;
			}
			if(element->hasChildNodes())
			{	 
				for(int k=0;k<children->getLength();k++)
				{
					if(children->item(k)->getNodeType()==1)
					{   
						DOMElement* tmpelement=(DOMElement*)children->item(k);
						tmpstr=XMLString::transcode(tmpelement->getNodeName());
						if(tmpstr=="Hierarchy")
						{
						   Hierarchy *hierarchy=new Hierarchy;	
						   if(hierarchy->parserHierarchy(this,tmpelement))
						   {
								this->_hierarchyies.push_back(hierarchy);
						   }
						   else
						   {
							   return false;
						   }
						}						
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

xercesc::DOMElement *Dimension::recursiveXML(xercesc::DOMDocument *doc)
{
	DOMElement* dimenElem = doc->createElement(XMLString::transcode("Dimension"));

	if(this->getName() != "")
	{
		dimenElem->setAttribute(XMLString::transcode("name"),XMLString::transcode(this->_name.c_str()));
	}
	if(this->getFactTable() != "")
	{
		dimenElem->setAttribute(XMLString::transcode("tabelname"),XMLString::transcode(this->_facttable.c_str()));	
	}
	if(this->getForeignKey() != "")
	{
		dimenElem->setAttribute(XMLString::transcode("foreignKey"),XMLString::transcode(this->_foreignkey.c_str()));	
	}

	
	Hierarchy *temphierarchy;
	if(this->_hierarchyies.size() > 0)
	{
		for(int i = 0;i < this->_hierarchyies.size() ;i++)
		{
			temphierarchy = this->getHierarchy(_hierarchyies[i]->getName());
			dimenElem->appendChild(temphierarchy->recursiveXML(doc));

		}

	}
	return dimenElem;
}


bool Dimension::wrapXML(xercesc::DOMDocument *doc,xercesc::DOMElement *hierarchyelem)
{
	DOMElement* dimenElem = doc->createElement(XMLString::transcode("Dimension"));

	if(this->getName() != "")
	{
		dimenElem->setAttribute(XMLString::transcode("name"),XMLString::transcode(this->_name.c_str()));
	}
	if(this->getFactTable() != "")
	{
		dimenElem->setAttribute(XMLString::transcode("tabelname"),XMLString::transcode(this->_facttable.c_str()));	
	}
	if(this->getForeignKey() != "")
	{
		dimenElem->setAttribute(XMLString::transcode("foreignKey"),XMLString::transcode(this->_foreignkey.c_str()));	
	}

	dimenElem->appendChild(hierarchyelem);

	if(XCube *tempcube = this->getCube())
	{
		
		if(tempcube->wrapXML(doc,dimenElem))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		XSchema *tempschema = this->getSchema();
	
		DOMElement* schemaElem = doc->getDocumentElement();//create root
	
		
		if(DataSource *tempDS = tempschema->getDataSource())
		{				
				schemaElem -> appendChild(tempDS->recursiveXML(doc));
		}
		schemaElem -> appendChild(dimenElem);
		return true;
	}
	
}

bool Dimension::writeXML(const std::string &outputfile)
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
			   DOMElement* dimenElem = doc->createElement(XMLString::transcode("Dimension"));

			if(this->getName() != "")
				dimenElem->setAttribute(XMLString::transcode("name"),XMLString::transcode(this->_name.c_str()));

			if(this->getFactTable() != "")
				dimenElem->setAttribute(XMLString::transcode("tabelname"),XMLString::transcode(this->_facttable.c_str()));	

			if(this->getForeignKey() != "")
				dimenElem->setAttribute(XMLString::transcode("foreignKey"),XMLString::transcode(this->_foreignkey.c_str()));	


			if(this->_hierarchyies.size() > 0)
				{
					
					for(int i = 0; i < this->_hierarchyies.size(); i ++)
					{
						Hierarchy *tempHierarchy = this->getHierarchy(this->_hierarchyies[i]->getName());
						dimenElem->appendChild(tempHierarchy->recursiveXML(doc));
					}
				}

			if(XCube *tempcube = this->getCube())
				{
		
					if(tempcube->wrapXML(doc,dimenElem) == false)
						return false;
					
				}
			else
				{
					XSchema *tempschema = this->getSchema();
	
					DOMElement* schemaElem = doc->getDocumentElement();//create root
	
		
						if(DataSource *tempDS = tempschema->getDataSource())
							{				
								schemaElem -> appendChild(tempDS->recursiveXML(doc));
							}
					schemaElem -> appendChild(dimenElem);
				
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