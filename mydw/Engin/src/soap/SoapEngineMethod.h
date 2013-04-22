#if !defined(AFX_SOAPENGINEMETHOD_H__A642AB90_3E0C_4FF4_9B32_E25617789D90__INCLUDED_)
#define AFX_SOAPENGINEMETHOD_H__A642AB90_3E0C_4FF4_9B32_E25617789D90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "../common/Param.h"
#include "../engine/SoapServer.h"
#include <string>
#include <map>
#include <list>
#include <axis/AxisWrapperAPI.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMNodeList.hpp>

using namespace std;


class SoapEngineMethod  
{
public:

	SoapEngineMethod(std::string const& name,SoapServer* server){
		this->_name=name;
		_server=server;
		if(_server)
		_server->addMethod(this);		
	}

	virtual ~SoapEngineMethod();

	//! Returns the name of the method
    std::string& name() { return _name; }

	//! Returns a help string for the method.
    //! Subclasses should define this method if introspection is being used.
    virtual std::string help() { return std::string(); }

	//! invoke the method. Subclasses must provide a definition for this method.
	//return true if execute success,else false
	virtual int invoke(list<Param> params,void ** pResult,void ** pSZFunct,string &mURI,string &rURI)=0;

	// Look up a deserialize method by name
	AXIS_DESERIALIZE_FUNCT findDeMethod(const std::string& name) const
	{
		map<std::string,AXIS_DESERIALIZE_FUNCT>::const_iterator i = deserialize_functs.find(name);
		if (i == deserialize_functs.end())
			return NULL;
			return i->second;
	}

	// Look up a serialize method by name
	AXIS_SERIALIZE_FUNCT findSeMethod(const std::string& name) const
	{
		map<std::string,AXIS_SERIALIZE_FUNCT>::const_iterator i = serialize_functs.find(name);
		if (i == serialize_functs.end())
			return NULL;
			return i->second;
	}

	void setDeMethod(const std::string name,void * pDeFunct)
	{
		deserialize_functs[name]=(AXIS_DESERIALIZE_FUNCT)pDeFunct;
	}
	
	void setSeMethod(const std::string name,void * pSeFunct)
	{
		serialize_functs[name]=(AXIS_SERIALIZE_FUNCT)pSeFunct;
	}
	
protected:
    std::string _name;
	SoapServer * _server;

	map<std::string,AXIS_DESERIALIZE_FUNCT>  deserialize_functs;
	map<std::string,AXIS_SERIALIZE_FUNCT> serialize_functs;
	
	//todo
	//set the basic type's DelMethod and SerMethod
	virtual void setBasicSeAndDeMethod(){
	}
	virtual void setUserTypeSeAndDeMethod(){
	}
};



#endif // !defined(AFX_SOAPENGINEMETHOD_H__A642AB90_3E0C_4FF4_9B32_E25617789D90__INCLUDED_)
