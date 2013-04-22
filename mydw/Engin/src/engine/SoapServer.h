
#if !defined(AFX_SOAPSERVER_H__264E36B1_8B48_4BD4_A2AB_14D468BF0671__INCLUDED_)
#define AFX_SOAPSERVER_H__264E36B1_8B48_4BD4_A2AB_14D468BF0671__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#include "../transport/SOAPTransport.h"
#include "../socket/HTTPParser.h"
#include "../socket/HTTPContext.h"
#include "../soap/SoapParser.h"

#include <string>
#include <map>

using namespace std;

class SoapServer;
class SoapEngineMethod;

class SoapServer  
{
public:

    static SoapServer* instance();
	
	SoapServer();
	virtual ~SoapServer();
	 
	SoapEngineMethod* findMethod(const std::string& name) const;

	void addMethod(SoapEngineMethod* method);

	//! Remove a command from the Soap server
    void removeMethod(SoapEngineMethod* method);

    //! Remove a command from the Soap server by name
    void removeMethod(const std::string& methodName);

	void process(int port,int backlog);
	
private:
	// Collection of methods. This could be a set keyed on method name if we wanted...
    typedef std::map< std::string, SoapEngineMethod* > MethodMap;
	
	static SoapServer* instance_;

    MethodMap _methods;

	
};



#endif // !defined(AFX_SOAPSERVER_H__264E36B1_8B48_4BD4_A2AB_14D468BF0671__INCLUDED_)
