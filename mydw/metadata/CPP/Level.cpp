#include <iostream>
#include <string>
#include <stdio.h>
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

#include "DWSchemac/XProperty.h"
#include "DWSchemac/Member.h"
#include "DWSchemac/Level.h"
#include "DWSchemac/Dimension.h"
#include "DWSchemac/Hierarchy.h"
#include "DWSchemac/DWXML.h"
#include "DWSchemac/DataSource.h"
#include "DWSchemac/XCube.h"
#include "DWSchemac/XSchema.h"

using namespace xercesc;
using namespace xodbc;

DWSCHEMA_CPP_NAMESPACE_BEGIN

std::vector<Member *> & Level::getMembers()
{
	return this->_members;
}


std::vector<Member *>  Level::getMember(Member* parent)
{
	std::vector<Member *> tmpmembers;
	Member *m=NULL;

	if(this->_depth ==1)
	{
		return this->_members;
	}
	if(!parent)
	{
		return tmpmembers;
	}

	for(int i=0;i<this->_members.size();i++)
	{
		m=this->_members[i];		
	    Member * p=this->_members[i]->getParent();
		if(m&&p==parent)
		{
			tmpmembers.push_back(m);
		}
	
	}
	return tmpmembers;
}

Member * Level::getMember(std::string key,Member* parent)
{
	
	Member *m=NULL;
	for(int i=0;i<this->_members.size();i++)
	{
		m=this->_members[i];
		if(!parent)
		{
				if(m->getKey()==key)
				{
					return m;
				}
		}
		else
		{
			    Member * p=this->_members[i]->getParent();
				if(m->getKey()==key&&p==parent)
				{
					return m;
				}
		}
	}
	return NULL;
}

void Level::printMembers()
{
	for(int i=0;i<this->_members.size();i++)
	{
		if(this->_members[i])
		{
			this->_members[i]->printMe();
		}
	}
}

Level* Level::getChildLevel()
{	
	std::vector<Level*> tmplevels=this->getHierarchy()->getLeveles();
	int i =0;
	if(tmplevels.size()<=1)
	{
		return NULL;
	}

	for(i=0;i<tmplevels.size();i++)
	{
		if((this->_depth+1)==((Level*)(tmplevels[i]))->getDepth())
		{
			return tmplevels[i];
		}
	}
	return NULL;
}


void Level::LoadMembers(Member* pm)
{	
	if(LoadMemberStuts)
	{
		return;
	}

	XODBCError XError;
	XODBCDatabase XDB;
	std::string strSQL;
    Dimension * dm=this->getHierarchy()->getDimension();
	std::string connectstring ="";
	if(dm->getCube())
	{
		connectstring=dm->getCube()->getSchema()->getDataSource()->getURL();
	}
	else
	{
		connectstring=dm->getSchema()->getDataSource()->getURL();
	}
	
	
	try
	{
		XDB.OpenEx(connectstring,XODBCDatabase::openReadOnly);		
	}
    catch(XODBCException e)
	{
		XODBCError error;
		e.GetError(error);
		std::cout<<error.GetErrorText().c_str()<<std::endl;
		std::cout<<error.GetState()<<std::endl;
		return;
	}
	XODBCRecordset XRS(&XDB); 
	try
	{
		XRS.SetMaxRecordCount(10);
	     strSQL = "Select distinct("+this->_column+") from "+this->getHierarchy()->getDimension()->getFactTable();
		if(pm)
		{
			   XDBVariant varValue1=pm->getValue();
			   if( varValue1.m_nType<=0)
				{
				   return;
				}
			     switch(varValue1.m_nType)
				 {
			   case XDBVT_BOOL:
					strSQL = strSQL+"  where "+ this->getParentLeval()->getColumn()+" ="+pm->getKey();
					break;

				case XDBVT_UCHAR:
				    strSQL = strSQL+"  where "+ this->getParentLeval()->getColumn()+" ="+pm->getKey();
					break;

				case XDBVT_SHORT:
					strSQL = strSQL+"  where "+ this->getParentLeval()->getColumn()+" ="+pm->getKey();
					break;

				case XDBVT_LONG:
			    	strSQL = strSQL+"  where "+ this->getParentLeval()->getColumn()+" ="+pm->getKey();
					break;

				case XDBVT_SINGLE:
				    strSQL = strSQL+"  where "+ this->getParentLeval()->getColumn()+" ="+pm->getKey();
					break;

				case XDBVT_DOUBLE:
					strSQL = strSQL+"  where "+ this->getParentLeval()->getColumn()+" ="+pm->getKey();
					break;
				case XDBVT_LONGLONG:
					strSQL = strSQL+"  where "+ this->getParentLeval()->getColumn()+" ="+pm->getKey();
					break;
				case XDBVT_DATE:
					strSQL = strSQL+"  where "+ this->getParentLeval()->getColumn()+" ='"+pm->getKey()+"'";
					break;
				case XDBVT_TIME:
					strSQL = strSQL+"  where "+ this->getParentLeval()->getColumn()+" ='"+pm->getKey()+"'";
					break;
				case XDBVT_TIMESTAMP:
					strSQL = strSQL+"  where "+ this->getParentLeval()->getColumn()+" ='"+pm->getKey()+"'";
					break;

				case XDBVT_STRING:
					strSQL = strSQL+"  where "+ this->getParentLeval()->getColumn()+" ='"+pm->getKey()+"'";
					break;

				case XDBVT_WSTRING:
					strSQL = strSQL+"  where "+ this->getParentLeval()->getColumn()+" ='"+pm->getKey()+"'";
					break;
				default:
					strSQL = strSQL+"  where "+ this->getParentLeval()->getColumn();
					break;
			}
	           
			   
		}
        
		if( XRS.Open(XODBCRecordset::snapshot,strSQL) )
		{
			XFieldInfo xfInfo;
			XDBVariant varValue;
			int i=0;
			if(XRS.GetFieldCount()>0)
			{
				XRS.GetFieldInfo(i,xfInfo);				
			}
			else
			{
				return;
			}  		    
		//	cout<<"******************* GetFieldValue as XDBVariant ************************"<<endl;
			do
			{
				for( i = 0; i < XRS.GetFieldCount();i++ )
				{				 
					XRS.GetFieldValue((short)i,varValue);
					string strValue;
					XRS.GetFieldValue((short)i,strValue);
					//std::cout<<strValue.c_str()<<std::endl;
			        if(varValue.m_nType>0)
					{
						Member * m=NULL;
						if(pm)
						{
								m=new Member(xfInfo,varValue,this,pm,strValue);
						}
						else
						{
								m=new Member(xfInfo,varValue,this,NULL,strValue);
						}
						
						Level * child=this->getChildLevel();

						this->_members.push_back(m);
						int num=_members.size();
						m=this->_members[num-1];
						//m->printMe();
						if(child)
						{			
							child->LoadMembers(m);
						}						
						m=NULL;	
					}
					varValue.Clear();
				}			 
				XRS.MoveNext();
			}while( !XRS.IsEOF() );	
		
			LoadMemberStuts = true;
		}
		else
		{
			return;
		}
	}
	catch(XODBCException e)
	{
		XODBCError error;
		e.GetError(error);
		std::cout<<error.GetErrorText().c_str()<<std::endl;
		std::cout<<error.GetState()<<std::endl;
	}

	if( XRS.IsOpen())
	{
		XRS.Close();
	}
	
}


Level& Level::operator=(const Level& l)
{
	this->_column=l._column;
	this->_depth=l._depth;
	this->_hierarchy=NULL;
	this->_name=l._name;
	this->_parentlevel=NULL;	
	this->LoadMemberStuts=l.LoadMemberStuts;
	for(int i=0;i<l._xproperties.size();i++)
	{
		XProperty *tmpp=new XProperty;
		*tmpp=*(l._xproperties[i]);
	    tmpp->setLevel(this); 
		this->_xproperties.push_back(tmpp);
	}
    return *(this);
}


void Level::setHierarchy(Hierarchy *h)
{
	this->_hierarchy=h;
}

void Level::setParentLevel(Level *h)
{
	this->_parentlevel=h;
}

int Level::getDepth()
{
	return this->_depth;
}

//get the parent hierarchy
Hierarchy* Level::getHierarchy()
{
	return this->_hierarchy;
}

void  Level::print()
{
	std::cout<<" Level Name="<<this->_name;
	std::cout<<" Column="<<this->_column;
	std::cout<<" Depth="<<this->_depth<<" >"<<std::endl;
	int i=0;
	for(i=0;i<this->_xproperties.size();i++)
	{
		this->_xproperties[i]->print();
	}
}

XProperty* Level::getProperty(const std::string &pname)
{
	for(int i=0;i<this->_xproperties.size();i++)
	{
		if(this->_xproperties[i]->getName()==pname)
		{
			return _xproperties[i];
		}
	}
	return NULL;
}

//get the level's properties
std::vector<XProperty*>& Level::getProperties()
{
	return this->_xproperties; 
}

//get the Level's parent Level
Level* Level::getParentLeval()
{
	return this->_parentlevel;
}

bool Level::operator < (const Level & c) const 
{
	return true;
}

bool Level::operator == (const Level & c) const
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

const std::string& Level::getName()const
{
	return _name;
}

bool Level::parserLevel(Hierarchy* phierarchy,Level * plevel,int depth,xercesc::DOMElement* element)
{
	this->_hierarchy=phierarchy;
	this->_parentlevel=plevel;
    this->_depth=depth;
	//std::string tmpstr;
	if(element)
	{
		    DOMNamedNodeMap *attributes;
			DOMNodeList *children =element->getChildNodes();
			DOMNode *tmpnode;
			std::string tmpstr=XMLString::transcode(element->getNodeName());
			if(tmpstr!="Level")
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
						if(tmpstr=="Property")
						{
					       XProperty *xproperty=new XProperty;
						   if(xproperty->parserProperty(this,tmpelement))
						   {
							   this->_xproperties.push_back(xproperty);
						   }
						   else
						   {
							   return false;
						   }
						}						
					}
				}	 
			}	
	}
	else
	{
		return false;
	}
	LoadMemberStuts = false;
	return true;
}

const std::string& Level::getColumn()
{
	return this->_column;
}

void Level::CleanMembers()
{
	LoadMemberStuts =false;
	int i=0;
	for(;i<this->_members.size();i++)
	{

		delete _members[i];
		_members[i]=NULL;		
	}
	_members.erase(_members.begin(),_members.end());
}

void Level::Dispose()
{
	int i=0;
	for(i=0;i<this->_xproperties.size();i++)
	{
		delete _xproperties[i];
		_xproperties[i]=NULL;
		_xproperties.pop_back();
	}

	LoadMemberStuts =false;
	for(i=0;i<this->_members.size();i++)
	{
		
		delete _members[i];
		 _members[i]=NULL;
        _members.pop_back();  
	}
}

xercesc::DOMElement *Level::recursiveXML(xercesc::DOMDocument *doc)
{
	DOMElement* levelElem = doc->createElement(XMLString::transcode("Level"));//this->getName().c_str()));

 	if(this->_name != "")
	{
		levelElem->setAttribute(XMLString::transcode("name"),XMLString::transcode(this->_name.c_str()));
	}
	if(this->_column !="")
	{
		levelElem->setAttribute(XMLString::transcode("column"),XMLString::transcode(this->_column.c_str()));	
	}
	XProperty *tempProperty;
	if(this->_xproperties.size() > 0)
	{
		
		for(int i = 0;i < this->_xproperties.size() ;i++)
		{
			tempProperty = this->getProperty(_xproperties[i]->getName());
			levelElem->appendChild(tempProperty->recursiveXML(doc));

		}

	}
	return levelElem;
}

bool Level::wrapXML(xercesc::DOMDocument *doc,xercesc::DOMElement *tempProperty)
{
	DOMElement* levelElem = doc->createElement(XMLString::transcode("Level"));//this->getName().c_str()));

 	if(this->_name != "")
		levelElem->setAttribute(XMLString::transcode("name"),XMLString::transcode(this->_name.c_str()));
	if(this->_column !="")
		levelElem->setAttribute(XMLString::transcode("column"),XMLString::transcode(this->_column.c_str()));	

	levelElem->appendChild(tempProperty);

	if(Hierarchy *tempHierarchy = this->getHierarchy())
	{
		
		if(tempHierarchy->wrapXML(doc,levelElem))
			return true;
	}
 
		return false;
 
    
}

bool Level::writeXML(const std::string &outputfile)
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
			   DOMElement* levelElem = doc->createElement(XMLString::transcode("Level"));//this->getName().c_str()));

				if(this->_name != "")
					levelElem->setAttribute(XMLString::transcode("name"),XMLString::transcode(this->_name.c_str()));
				if(this->_column !="")
					levelElem->setAttribute(XMLString::transcode("column"),XMLString::transcode(this->_column.c_str()));	

				if(this->_xproperties.size() > 0)
				{
					
					for(int i = 0; i < this->_xproperties.size(); i ++)
					{
						XProperty *tempproperty = this->getProperty(this->_xproperties[i]->getName());
						levelElem->appendChild(tempproperty->recursiveXML(doc));
					}
				}

				if(Hierarchy *temphierarchy = this->getHierarchy())
				{
		
					if(temphierarchy->wrapXML(doc,levelElem) == false)
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