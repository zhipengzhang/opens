#include <iostream>
#include <fstream>
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

#include "DWSchemac/Dimension.h"
#include "DWSchemac/XCube.h"
#include "DWSchemac/XSchema.h"
#include "DWSchemac/DWXML.h"

using namespace xercesc;

DWSCHEMA_CPP_NAMESPACE_BEGIN


std::vector<Dimension *> XSchema::getDimensions()
{
	return this->_sharedimensiones;
}

std::vector<XCube *> XSchema::getCubes()
{
	return this->_cubes;
}

std::string XSchema::getSchemaString(const std::string & name)
{
	return this->_xmlstring;
}

void XSchema::print()
{
	std::cout<<endl;
	std::cout<<"<Schema ";
	std::cout<<" Name="<<this->_name<<" >"<<std::endl;
	int i=0;
	this->_datasource->print();
	for(i=0;i<this->_sharedimensiones.size();i++)
	{
		_sharedimensiones[i]->print();
	}
	for(i=0;i<this->_cubes.size();i++)
	{
		_cubes[i]->print();
	}
}

XSchema& XSchema::operator=(const XSchema & schema)
{
	this->_cubes=schema._cubes;
	this->_name=schema._name;
	this->_sharedimensiones=schema._sharedimensiones;
	return  *(this);
}

bool XSchema::operator < (const XSchema & c)  const
 {
	return true;
 }

bool XSchema::operator == (const XSchema & c) const
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

XSchema::XSchema(const XSchema &schema)
{
	this->_name=schema._name;
	this->_cubes =schema._cubes;
	this->_sharedimensiones=schema._sharedimensiones; 
	this->_xmlstring=schema._xmlstring;
}

const std::string&  XSchema::getName()const{ return _name;}


bool XSchema::removeCube(const std::string& cubename,XCube& cube)
{
	
	for(int i=0;i<this->_cubes.size();i++)
	{
		if(_cubes[i]->getName()==cubename)
		{
			cube=*_cubes[i];
			return true;
		}
	}
	 return false;
}

XCube* XSchema::getCube(const std::string& cubename)
{	
	for(int i=0;i<this->_cubes.size();i++)
	{
		if(_cubes[i]->getName()==cubename)
		{
			return _cubes[i];			
		}
	}
	 return NULL;
}

XCube* XSchema::getCube(const char* cubename)
{
	for(int i=0;i<this->_cubes.size();i++)
	{
		if(_cubes[i]->getName()==std::string(cubename))
		{
			return _cubes[i];			
		}
	}
	 return NULL;
}


bool XSchema::removeShareDimension(const std::string& dimensionname,Dimension& dimension)
{
	 for(int i=0;i<this->_sharedimensiones.size();i++)
	{
		if(_sharedimensiones[i]->getName()==dimensionname)
		{
			dimension=*_sharedimensiones[i];
			return true;
		}
	}
	return false;
}

bool XSchema::parserSchema(const std::string& xmlFile)
{
	DWXML xml;
    std::string tmpstr; 
	DOMElement *element=xml.xmlParser(xmlFile);
	if(element)
	{
		    DOMNamedNodeMap *attributes;
			DOMNodeList *children =element->getChildNodes();
			DOMNode *tmpnode;
			std::string tmpstr=XMLString::transcode(element->getNodeName());
			if(tmpstr!="Schema")
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
						break;
					}					
				}
				if(j==attributes->getLength())
				{
					return false;
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
						if(tmpstr=="Dimension")
						{
						   Dimension *dimension=new Dimension;	
						   if(dimension->parserDimension(this,tmpelement))
						   {
								this->_sharedimensiones.push_back(dimension);
						   }
						   else
						   {
							   return false;
						   }
						}
						else if(tmpstr=="Cube")
						{
							XCube *cube=new XCube;						
							if(cube->parserCube(this,tmpelement))
							{
								this->_cubes.push_back(cube);	
							}
							else
							{
								return false;
							}
						}
						else if(tmpstr=="DataSource")
						{
							DataSource *ds=new DataSource;						
							if(ds->parserDataSource(this,tmpelement))
							{
								this->_datasource=ds;	
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
    string s;
	string line;
    ifstream in;
	in.open(xmlFile.c_str());
	while(getline(in,line))
	{
		s+=line;
		s+="\n";
	}
	in.close();
    this->_xmlstring=s;
	return true;
}

DataSource* XSchema::getDataSource()
{
	return this->_datasource;
}

void XSchema::Dispose()
{
	int i=0;
	int count =this->_cubes.size();
	for(i=0;i<count;i++)
	{
		this->_cubes[i]->Dispose();
		delete _cubes[i];
		_cubes[i]=NULL;	
		this->_cubes.pop_back();
	}

	count=this->_sharedimensiones.size();
	for(i=0;i<this->_sharedimensiones.size();i++)
	{
		this->_sharedimensiones[i]->Dispose();
		delete _sharedimensiones[i];
		_sharedimensiones[i]=NULL;
		this->_sharedimensiones.pop_back();
	}

	delete _datasource;
	_datasource=NULL;

}

Dimension* XSchema::getShareDimension(const std::string& dimensionname)
{
    for(int i=0;i<this->_sharedimensiones.size();i++)
	{
		if(_sharedimensiones[i]->getName()==dimensionname)
		{
			return _sharedimensiones[i];
		}
	}
	return NULL;
}

bool XSchema::addCube(const XCube& cube)
{
	if(this->getCube(cube.getName()))
	{
		XCube *tmpcube=new XCube;
		*tmpcube=cube;
		tmpcube->setParentSchema(this);
		this->_cubes.push_back(tmpcube);
		return true;
	}	
	return false;
}

bool XSchema::addShareDimension(const Dimension& dimension)
{
	if(this->getShareDimension(dimension.getName()))
	{
		Dimension *tmpdimension= new Dimension;
		*tmpdimension=dimension;
		tmpdimension->setParentSchema(this);
		this->_sharedimensiones.push_back(tmpdimension);
		return true;
	}
	return false;
}

bool XSchema::writeXML(const std::string &outputfile)
{
	//DOMXMLparser for Ini
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
			   DOMElement* schemaElem = doc->getDocumentElement();//create root

			   if(this->getDataSource())
			   {
				   
					
					   DataSource *tempDS;
					   if(tempDS = this->getDataSource())
					   {
						   schemaElem->appendChild(tempDS->recursiveXML(doc));
					   }
				   

			   }

				if(this->_cubes.size() > 0)
				{
				    for(int i= 0 ; i<this->_cubes.size(); i++)
					{
						XCube *tempCube;
						if(tempCube = this->getCube(_cubes[i]->getName()))
						{
						
						schemaElem->appendChild(tempCube->recursiveXML(doc));

						if(this->_name != "")
						schemaElem->setAttribute(XMLString::transcode("name"),XMLString::transcode(this->_name.c_str()));	
						}
					}
				}
				if(this->_sharedimensiones.size() > 0)
				{
				    for(int i= 0 ; i<this->_sharedimensiones.size(); i++)
					{
						Dimension *tempDimen;
						if(tempDimen = this->getShareDimension(_sharedimensiones[i]->getName()))
						{
						
							schemaElem->appendChild(tempDimen->recursiveXML(doc));
						}
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
