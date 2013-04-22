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


#include "DWSchemac/XSchema.h"
#include "DWSchemac/DataSource.h"
#include "DWSchemac/Level.h"
#include "DWSchemac/XCube.h"
#include "DWSchemac/Hierarchy.h"
#include "DWSchemac/Dimension.h"
#include "DWSchemac/Level.h"
#include "DWSchemac/DWXML.h"



DWSCHEMA_CPP_NAMESPACE_BEGIN

using namespace xercesc;


void Hierarchy::LoadMembers()
{
	if(this->getDimension()->getCube()->getSchema()->getDataSource()->getDSType()==DataSource::FILETYPE)
	{
		return ;
	}

	for(int i=0;i<this->_leveles.size();i++)
	{
		if(this->_leveles[i]&&((Level*)(this->_leveles[i]))->getDepth()==1)
		{
			this->_leveles[i]->LoadMembers(NULL);
			return;
		}
	}
}

Hierarchy& Hierarchy::operator=(const Hierarchy& h)
{
	this->_allmembername=h._allmembername;
	this->_name=h._name;
	this->_parentdimension=NULL;
	this->_primarykey=h._primarykey;
	for(int i=0;i<h._leveles.size();i++)
	{
		Level * tmpl=new Level;
		*tmpl=*(h._leveles[i]);
		if(i>0)
		{
			tmpl->setParentLevel(this->_leveles[i-1]);
		}
		tmpl->setHierarchy(this);
        this->_leveles.push_back(tmpl);
	}

	return *(this);
}


void Hierarchy::setDimension(Dimension* dp)
{
	this->_parentdimension=dp;
}

void Hierarchy::print()
{
	std::cout<<"< Hierarchy Name="<<this->_name;
	std::cout<<" hasAll="<<this->_allmembername;
	std::cout<<" PrimaryKey="<<this->_primarykey;
	std::cout<<" >"<<std::endl;
	int i=0;
	for(i=0;i<this->_leveles.size();i++)
	{
		this->_leveles[i]->print();
	}
}


bool Hierarchy::operator < (const Hierarchy & c) const 
{
	return true;
}

bool Hierarchy::operator == (const Hierarchy & c) const
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

const std::string& Hierarchy::getName()const
{
	return _name;
}


//get the leveles in hierarchy
/*std::vector<Level*>& Hierarchy::getLeveles()
{
	return this->_leveles;
}*/

//get the level named olevelname in hierarchy
Level* Hierarchy::getLevel(const std::string& olevelname)
{
	for(int i=0;i<this->_leveles.size();i++)
	{
		if(this->_leveles[i]->getName()==olevelname)
		{
			return _leveles[i];
		}
	}
	return NULL;
}


std::vector<Level*> Hierarchy::getLeveles()
{
	 	return _leveles;
 
}


	//get the primarykey of hierarchy
const std::string& Hierarchy::getPrimaryKey()
{
	return this->_primarykey;
}

	//get if has all
const std::string& Hierarchy::getHasAll()
{
	return this->_allmembername;
}

	//get the parent dimension of hierarchy
Dimension* Hierarchy::getDimension()
{
	return this->_parentdimension;
}


bool Hierarchy::parserHierarchy(Dimension* pdimension,xercesc::DOMElement* element)
{
    this->_parentdimension=pdimension;
	//std::string tmpstr;
	if(element)
	{
		    DOMNamedNodeMap *attributes;
			DOMNodeList *children =element->getChildNodes();
			DOMNode *tmpnode;
			std::string tmpstr=XMLString::transcode(element->getNodeName());
			if(tmpstr!="Hierarchy")
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
					else if(tmpstr=="hasAll")
					{
						this->_allmembername=XMLString::transcode(tmpnode->getNodeValue());
					}
					else if(tmpstr=="primaryKey")
					{
						this->_primarykey =XMLString::transcode(tmpnode->getNodeValue());
					}
				}			
			}
			else
			{
				return false;
			}
			if(element->hasChildNodes())
			{	
				int depth=1;
				Level *level;
				for(int k=0;k<children->getLength();k++)
				{
					if(children->item(k)->getNodeType()==1)
					{   
						DOMElement* tmpelement=(DOMElement*)children->item(k);
						tmpstr=XMLString::transcode(tmpelement->getNodeName());
						if(tmpstr=="Level")
						{
					       if(depth==1)
						   {
							   level=NULL;
						   }
						   Level *clevel=new Level;
						   if(clevel->parserLevel(this,level,depth,tmpelement))
						   {								
								this->_leveles.push_back(clevel);
								level=_leveles[depth-1];
								depth++;
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

void Hierarchy::printMembers()
{
	for(int i =0;i<this->_leveles.size();i++)
	{
		if(this->_leveles[i])
		{
			this->_leveles[i]->printMembers();
		}
	}
}

void Hierarchy::CleanMembers()
{
	int i=0;
	int count=this->_leveles.size();
	for(i=0;i<count;i++)
	{
		this->_leveles[i]->CleanMembers();		 
	}
}

void Hierarchy::Dispose()
{
	int i=0;
	int count=this->_leveles.size();
	for(i=0;i<count;i++)
	{
		this->_leveles[i]->Dispose();
		delete _leveles[i];
		 _leveles[i]=NULL;
		_leveles.pop_back();
	}
}

xercesc::DOMElement *Hierarchy::recursiveXML(xercesc::DOMDocument *doc)
{
	DOMElement* hierarchyElem = doc->createElement(XMLString::transcode("Hierarchy"));

	if(this->_name != "")
	{
		hierarchyElem->setAttribute(XMLString::transcode("name"),XMLString::transcode(this->_name.c_str()));
	}
	if(this->_allmembername != "")
	{
		hierarchyElem->setAttribute(XMLString::transcode("hasAll"),XMLString::transcode(this->_allmembername.c_str()));	
	}
	if(this->_primarykey != "")
	{
		hierarchyElem->setAttribute(XMLString::transcode("primaryKey"),XMLString::transcode(this->_primarykey.c_str()));	
	}

	Level *templevel;
	if(this->_leveles.size() > 0)
	{
		
		for(int i = 0;i < this->_leveles.size() ;i++)
		{
			templevel = this->getLevel(_leveles[i]->getName());
			hierarchyElem->appendChild(templevel->recursiveXML(doc));

		}

	}
	return hierarchyElem;
}

bool Hierarchy::wrapXML(xercesc::DOMDocument *doc,xercesc::DOMElement *templevel)
{
	DOMElement* hierarchyElem = doc->createElement(XMLString::transcode("Hierarchy"));

	if(this->_name != "")
	{
		hierarchyElem->setAttribute(XMLString::transcode("name"),XMLString::transcode(this->_name.c_str()));
	}
	if(this->_allmembername != "")
	{
		hierarchyElem->setAttribute(XMLString::transcode("hasAll"),XMLString::transcode(this->_allmembername.c_str()));	
	}
	if(this->_primarykey != "")
	{
		hierarchyElem->setAttribute(XMLString::transcode("primaryKey"),XMLString::transcode(this->_primarykey.c_str()));	
	}

	hierarchyElem->appendChild(templevel);
	if(Dimension *tempDimension = this->getDimension())
	{
		
		if(tempDimension->wrapXML(doc,hierarchyElem))
			return true;
	}
 
		return false;
 

}

bool Hierarchy::writeXML(const std::string &outputfile)
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
			   DOMElement* hierarchyElem = doc->createElement(XMLString::transcode("Hierarchy"));

				if(this->_name != "")
				{
					hierarchyElem->setAttribute(XMLString::transcode("name"),XMLString::transcode(this->_name.c_str()));
				}
				if(this->_allmembername != "")
				{
					hierarchyElem->setAttribute(XMLString::transcode("hasAll"),XMLString::transcode(this->_allmembername.c_str()));	
				}
				if(this->_primarykey != "")
				{
					hierarchyElem->setAttribute(XMLString::transcode("primaryKey"),XMLString::transcode(this->_primarykey.c_str()));	
				}

				if(this->_leveles.size() > 0)
				{
					
					for(int i = 0; i < this->_leveles.size(); i ++)
					{
						Level *templevel = this->getLevel(this->_leveles[i]->getName());
						hierarchyElem->appendChild(templevel->recursiveXML(doc));
					}
				}

				if(Dimension *tempdimension = this->getDimension())
				{
		
					if(tempdimension->wrapXML(doc,hierarchyElem) == false)
						return false;
					
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