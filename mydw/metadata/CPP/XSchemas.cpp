#include <vector>
#include <stdexcept>
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

#include "DWSchemac/Level.h"
#include "DWSchemac/Dimension.h"
#include "DWSchemac/Hierarchy.h"
#include "DWSchemac/XCube.h"
#include "DWSchemac/XSchema.h"
#include "DWSchemac/XSchemas.h"




DWSCHEMA_CPP_NAMESPACE_BEGIN

string StringToLower(string & str)
{
	int size = str.size();
	string strr;
	for(int i=0 ; i<size ; i++)
	{
		strr.insert(i,str);
	}
	return strr;
}

XSchemas& XSchemas::operator=(const XSchemas& s)
{
		this->_xschemas=s._xschemas;
		return *(this);
}

//copy constuctor 
XSchemas::XSchemas(const XSchemas &schemas)
{
	this->_xschemas=schemas._xschemas;
}

std::string XSchemas::getSchemaString(const std::string & name)
{
	for(int i=0;i<_xschemas.size();i++)
	{
		if(_xschemas[i]->getName()==name)
		{            
			return _xschemas[i]->getSchemaString(name);
		}
	}
	return "";
}

bool XSchemas::createSchema(const std::string &xmlFile)
{
    XSchema *s=new XSchema;
    if(s->parserSchema(xmlFile))
	{
		_xschemas.push_back(s);
		return true;
	}
	else
	{
		return false;
	}	
}


XSchema* XSchemas::getSchema(const std::string &schemaname)
{
	for(int i=0;i<_xschemas.size();i++)
	{
	    
		if(_xschemas[i]->getName()==schemaname)
		{            
			return _xschemas[i];
		}
	}
	return NULL;
}

vector<XSchema*> XSchemas::getALLSchemas(){
	return this->_xschemas;
}


vector<XCube *> XSchemas::getCubes(string catalog){
	if(catalog!="")
		return getSchema(catalog)->getCubes();
	else{
		vector<XCube *> cubes;
		vector<XSchema*> xSchemas=getALLSchemas();
		for(int i=0;i<xSchemas.size();i++){
			vector<XCube *>::iterator itf=xSchemas[i]->getCubes().begin();
			vector<XCube *>::iterator itl=xSchemas[i]->getCubes().end();
			cubes.insert(cubes.end(),itf,itl);
		}
		return cubes;
	}
}

vector<Dimension *> XSchemas::getDimensions(string catalog,string cuben){
	vector<XCube *> cubes=getCubes(catalog);
	vector<XCube *> cubets;
	//根据cuben过滤cube
	if(cuben!=""){
		for(int i=0;i<cubes.size();i++){
			if(cubes[i]->getName()==cuben)
				cubets.push_back(cubes[i]);
		}
	}
	else {
		cubets=cubes;
	}
	//获取Dimension
	vector<Dimension *> dimensions;
	for(int j=0;j<cubets.size();j++){
		vector<Dimension *>::iterator itf=cubets[j]->getDimensions().begin();
		vector<Dimension *>::iterator itl=cubets[j]->getDimensions().end();
		dimensions.insert(dimensions.end(),itf,itl);
	}
	return dimensions;
}

vector<Hierarchy*> XSchemas::getHierarchies(string catalog,string cuben,string dimensionn){
	vector<Dimension *> dimensions=getDimensions(catalog,cuben);
	vector<Dimension *> dimensionts;
	//根据dimensionn过滤dimension
	if(dimensionn!=""){
		for(int i=0;i<dimensions.size();i++){
			if(dimensions[i]->getName()==dimensionn)
				dimensionts.push_back(dimensions[i]);
		}
	}
	else {
		dimensionts=dimensions;
	}
	//获取Dimension
	vector<Hierarchy *> hierarchys;
	for(int j=0;j<dimensionts.size();j++){
		vector<Hierarchy *>::iterator itf=dimensionts[j]->getHierarchies().begin();
		vector<Hierarchy *>::iterator itl=dimensionts[j]->getHierarchies().end();
		hierarchys.insert(hierarchys.end(),itf,itl);
	}
	return hierarchys;
}

vector<Level *> XSchemas::getLevels(string catalog,string cuben,string dimensionn,string leveln){
	vector<Hierarchy *> hierarchys=getHierarchies(catalog,cuben,dimensionn);
	vector<Hierarchy *> hierarchyts;
	//根据leveln过滤level
	if(leveln!=""){
		for(int i=0;i<hierarchys.size();i++){
			if(hierarchys[i]->getName()==leveln)
				hierarchyts.push_back(hierarchys[i]);
		}
	}
	else {
		hierarchyts=hierarchys;
	}
	//获取level
	vector<Level *> levels;
	for(int j=0;j<hierarchyts.size();j++){
		vector<Level *>::iterator itf=hierarchyts[j]->getLeveles().begin();
		vector<Level *>::iterator itl=hierarchyts[j]->getLeveles().end();
		levels.insert(levels.end(),itf,itl);
	}
	return levels;
}

bool XSchemas::removeSchema(const std::string &Schemaname)
{
	//add to 
	XSchema *s;
	for(int loopi=0;loopi<this->_xschemas.size();loopi++)
	{
		if(_xschemas[loopi]->getName()==Schemaname)
		{
			s=_xschemas[loopi];
			_xschemas[loopi]=_xschemas[_xschemas.size()-1];
			_xschemas[_xschemas.size()-1]=s;
			_xschemas.pop_back();
			s->Dispose();
			delete s;
			return true;
		}
	}
	return false;
}

void XSchemas::Dispose()
{
	int count=this->_xschemas.size();
	for(int i=0;i<count;i++)
	{

	    ((XSchema*)this->_xschemas[i])->Dispose();	
		delete this->_xschemas[i];	
		this->_xschemas[i]=NULL;
		this->_xschemas.pop_back();		
	}
}
DWSCHEMA_CPP_NAMESPACE_END