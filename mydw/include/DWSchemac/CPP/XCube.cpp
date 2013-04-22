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
#include "DWSchemac/XCube.h"
#include "DWSchemac/Dimension.h"
#include "DWSchemac/calcMember.h"
#include "DWSchemac/Measure.h"
#include "DWSchemac/DWXML.h"

using namespace xercesc;

using namespace std;

DWSCHEMA_CPP_NAMESPACE_BEGIN

XCube::XCube(const XCube& c)
{
	this->_calcmembers=c._calcmembers;
	this->_dimensions=c._dimensions;
	this->_fact=c._fact;
	this->_measures=c._measures;
	this->_name=c._name;
	this->_parentschema=c._parentschema; 
}

XCube& XCube::operator=(const XCube& c)
{
	this->_calcmembers=c._calcmembers;
	this->_dimensions=c._dimensions;
	this->_fact=c._fact;
	this->_measures=c._measures;
	this->_name=c._name;
	this->_parentschema=c._parentschema;
	return *(this);
}

bool XCube::operator < (const XCube & c) const 
{
	return true;
}

bool XCube::operator == (const XCube & c) const
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

	//get the cube fact table
const std::string& XCube::getFactTable()
{
	return this->_fact;		
}

//get the parent Schema of cube
XSchema* XCube::getSchema()
{
	return this->_parentschema;
}

//get the dimensiones  of cube
std::vector<Dimension*>& XCube::getDimensions()
{
	return this->_dimensions;
}

//get the measures of cube
std::vector<Measure*>& XCube::getMeasures()
{
	return this->_measures;
}

//get the calculate members of cube
std::vector<calcMember *>& XCube::getCalMembers()
{
	return this->_calcmembers;
}

//get the dimension in cube which named dimensionname
Dimension* XCube::getDimension(const std::string & dimensioname)
{
	for(int i=0;i<this->_dimensions.size();i++)
	{
		if(_dimensions[i]->getName()==dimensioname)
		{
			return _dimensions[i];
		}
	}
	return NULL;
}

//get the measure in cube which named measurename
Measure* XCube::getMeasure(const std::string& measurename)
{
	for(int i=0;i<this->_measures.size();i++)
	{
		if(this->_measures[i]->getName()==measurename)
		{
			return _measures[i];
		}
	}
	return NULL;
}

//get the calculate in cube which named calmembername
calcMember* XCube::getCalMember(const std::string& calmembername)
{
	for(int i=0;i<this->_calcmembers.size();i++)
	{
		if(this->_calcmembers[i]->getName()==calmembername)
		{
			return _calcmembers[i];
		}
	}
	return NULL;
}

//add dimension into cube if add success return true else return false
bool XCube::addDimension(const Dimension& dimension)
{
    if(this->getDimension(dimension.getName()))
	{
		Dimension *tmpdimension=new Dimension;
		*tmpdimension=dimension;
		tmpdimension->setCubeDimension(this);
		this->_dimensions.push_back(tmpdimension);
		return true;
	}
	return false;
}


void XCube::Dispose()
{
	int i=0;
	int count=this->_dimensions.size();
	for(i=0;i<count;i++)
	{
		this->_dimensions[i]->Dispose();
		delete _dimensions[i];
		_dimensions[i]=NULL;
		this->_dimensions.pop_back();
	}

	count=this->_measures.size();
	for(i=0;i<count;i++)
	{
		delete _measures[i];
		_measures[i]=NULL;
        _measures.pop_back();
	}

	count = this->_calcmembers.size();
	for(i=0;i<count;i++)
	{
		delete _calcmembers[i];
		_calcmembers[i]=NULL;
		_calcmembers.pop_back();
	}
}

//add measure into cube if add success return true else return false
bool XCube::addMeasure(const Measure& measure)
{
	if(this->getMeasure(measure.getName()))
	{
		Measure *tmpmeasure=new Measure;
		*tmpmeasure=measure;
		tmpmeasure->setParentCube(this);
		this->_measures.push_back(tmpmeasure);
		return true;
	}
	return false;
}

//add calcMember into cube if add success return true else return false
bool XCube::addMember(const calcMember & calmember)
{
	if(this->getCalMember(calmember.getName()))
	{
		calcMember *tmpcalcmember=new calcMember;
		*tmpcalcmember=calmember;
		tmpcalcmember->setParentCube(this);
		this->_calcmembers.push_back(tmpcalcmember);
		return true;
	}
	return false;
}


void XCube::setParentSchema(XSchema* pschema)
{
	this->_parentschema=pschema;
}

const std::string& XCube::getName()const
{
	return _name;
}

bool XCube::parserCube(XSchema* pschema,xercesc::DOMElement* element)
{
	this->_parentschema=pschema;
	if(element)
	{
		    DOMNamedNodeMap *attributes;
			DOMNodeList *children =element->getChildNodes();
			DOMNode *tmpnode;
			std::string tmpstr=XMLString::transcode(element->getNodeName());
			if(tmpstr!="Cube")
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
						this->_fact=XMLString::transcode(tmpnode->getNodeValue());
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
						if(tmpstr=="Dimension")
						{
						   Dimension *dimension=new Dimension;	
						   if(dimension->parserDimension(this,tmpelement))
						   {
								this->_dimensions.push_back(dimension);
						   }
						   else
						   {
							   return false;
						   }
						}
						else if(tmpstr=="DimensionUsage")
						{
						   Dimension* dimension=NULL;						   
						   attributes=tmpelement->getAttributes();
						   if(attributes)
						   {
								for(int j=0;j<attributes->getLength();j++)
								{
									DOMNode *tmpnode=attributes->item(j);
									tmpstr=XMLString::transcode(tmpnode->getNodeName());
								//	std::string dname1=XMLString::transcode(tmpnode->getNodeValue());
									if(tmpstr=="source")
									{
										std::string dname=XMLString::transcode(tmpnode->getNodeValue());
										dimension=this->getSchema()->getShareDimension(dname);
									}
								}
								if(dimension)
								{	
									Dimension *tmpdmen=new Dimension;
									*tmpdmen=*dimension;
									for(int j=0;j<attributes->getLength();j++)
									{
										DOMNode *tmpnode=attributes->item(j);
										tmpstr=XMLString::transcode(tmpnode->getNodeName());
										if(tmpstr=="name")
										{
											std::string dname=XMLString::transcode(tmpnode->getNodeValue());
											tmpdmen->setName(dname);
										}
										else if(tmpstr=="foreignKey")
										{
											std::string fkey=XMLString::transcode(tmpnode->getNodeValue());
                                            tmpdmen->setForeignKey(fkey);
										}
									}
									tmpdmen->setCubeDimension(this);
									this->_dimensions.push_back(tmpdmen);	
								}
							}				  
						}
						else if(tmpstr=="Measure")
						{
						 	Measure *measure=new Measure;					
							if(measure->parserMeasure(this,tmpelement))
							{
								this->_measures.push_back(measure);
							}
							else
							{
								return false;
							}
						}
						else if(tmpstr=="CalculatedMember")
						{
						    calcMember *calmember=new calcMember;	
							if(calmember->parserCalMember(this,tmpelement))
							{
								this->_calcmembers.push_back(calmember);
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

void XCube::print()
{
	std::cout<<"< Cube Name="<<this->_name;
	std::cout<<" FactTable="<<this->_fact<<" >\n";
	int i=0;
	for(i=0;i<this->_dimensions.size();i++)
	{
		this->_dimensions[i]->print();
	}

	for(i=0;i<this->_measures.size();i++)
	{
		this->_measures[i]->print();
	}

	for(i=0;i<this->_calcmembers.size();i++)
	{
		this->_calcmembers[i]->print();
	}
}

xercesc::DOMElement *XCube::recursiveXML(xercesc::DOMDocument* doc)
{
	DOMElement *cubeElem = doc->createElement(XMLString::transcode("Cube"));

	if(this->_name != "")
		cubeElem->setAttribute(XMLString::transcode("name"),XMLString::transcode(this->_name.c_str()));
	if(this->_fact != "")
		cubeElem->setAttribute(XMLString::transcode("tablename"),XMLString::transcode(this->_fact.c_str()));

	if(this->_dimensions.size() > 0)
	{
		Dimension *tempdimension;
		for(int i = 0;i < this->_dimensions.size() ;i++)
		{
			tempdimension = this->getDimension(_dimensions[i]->getName());
			cubeElem->appendChild(tempdimension->recursiveXML(doc));

		}

	}

	if(this->_measures.size() > 0)
	{
		Measure *tempMeasures;
		for(int i = 0;i < this->_measures.size() ;i++)
		{
			tempMeasures = this->getMeasure(_measures[i]->getName());
			cubeElem->appendChild(tempMeasures->recursiveXML(doc));

		}

	}

	if(this->_calcmembers.size() > 0)
	{
		calcMember *tempCalcmember;
		for(int i = 0;i < this->_calcmembers.size() ;i++)
		{
			tempCalcmember = this->getCalMember(_calcmembers[i]->getName());
			cubeElem->appendChild(tempCalcmember->recursiveXML(doc));

		}

	}

	return cubeElem;
}

bool XCube::wrapXML(xercesc::DOMDocument *doc,xercesc::DOMElement *tempElem)
{
	DOMElement *cubeElem = doc->createElement(XMLString::transcode("Cube"));

	if(this->_name != "")
		cubeElem->setAttribute(XMLString::transcode("name"),XMLString::transcode(this->_name.c_str()));
	if(this->_fact != "")
		cubeElem->setAttribute(XMLString::transcode("tablename"),XMLString::transcode(this->_fact.c_str()));

	cubeElem->appendChild(tempElem);

	XSchema *tempschema = this->getSchema();
	
	DOMElement* schemaElem = doc->getDocumentElement();//create root
	
		
	if(DataSource *tempDS = tempschema->getDataSource())
	{				
			schemaElem -> appendChild(tempDS->recursiveXML(doc));
	}
	schemaElem -> appendChild(cubeElem);
	return true;
		

}

bool XCube::writeXML(const std::string &outputfile)
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
			   DOMElement *cubeElem = doc->createElement(XMLString::transcode("Cube"));

				if(this->_name != "")
					cubeElem->setAttribute(XMLString::transcode("name"),XMLString::transcode(this->_name.c_str()));
				if(this->_fact != "")
					cubeElem->setAttribute(XMLString::transcode("tablename"),XMLString::transcode(this->_fact.c_str()));

				if(this->_dimensions.size() > 0)
				{
					for(int i = 0; i < this->_dimensions.size(); i ++)
					{
					Dimension *tempDimension = this->getDimension(this->_dimensions[i]->getName());
						cubeElem->appendChild(tempDimension->recursiveXML(doc));
					}
				}

				XSchema *tempschema = this->getSchema();
	
				DOMElement* schemaElem = doc->getDocumentElement();//create root
	
		
				if(DataSource *tempDS = tempschema->getDataSource())
				{				
					schemaElem -> appendChild(tempDS->recursiveXML(doc));
				}
				schemaElem -> appendChild(cubeElem);

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