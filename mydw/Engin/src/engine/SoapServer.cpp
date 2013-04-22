#include <assert.h>
#include "SoapServer.h"

#include "../soap/SoapEngineMethod.h"

SoapServer::SoapServer()
{
	
}

SoapServer::~SoapServer()
{
	if(instance_)
		delete instance_;
	
	_methods.clear();
}


SoapServer* SoapServer::instance()
{
	if(instance_==NULL)
		{
			instance_=new SoapServer;
		}
	
	return instance_;
}



// Look up a method by name
SoapEngineMethod* SoapServer::findMethod(const std::string& name) const
{
	MethodMap::const_iterator i = _methods.find(name);
	if (i == _methods.end())
    return NULL;	
	return i->second;
}


SoapServer* SoapServer::instance_=0;


// Add a command to the Soap server
void SoapServer::addMethod(SoapEngineMethod* method)
{
	string s = method->name();

	_methods.insert(make_pair(s,method));
}

// Remove a command from the Soap server
void SoapServer::removeMethod(SoapEngineMethod* method)
{
	MethodMap::iterator i = _methods.find(method->name());
	if (i != _methods.end())
    _methods.erase(i);
}

// Remove a command from the Soap server by name
void SoapServer::removeMethod(const std::string& methodName)
{
	MethodMap::iterator i = _methods.find(methodName);
	if (i != _methods.end())
		_methods.erase(i);
}

void SoapServer::process(int port,int backlog){
	
	SoapTransport soaptransport;
	soaptransport.init(port,backlog);

	while(true){

 	int sockConn=soaptransport.accept();

	while(true){
		
	string reStr;

	if(!soaptransport.ReadARequest(sockConn,reStr)){
		//todo
		cout<<"ReadARequest false!\n";
		soaptransport.closeClientSocket(sockConn);
		break;
	}
		

	HTTPParser httpp;

	if(!httpp.parse(reStr)){
		//todo
		cout<<"Can't parsed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		
		soaptransport.flushOutput(sockConn);
		continue;
	}
	

	HTTPContext hc= httpp.getHc();

	SoapParser soapParser;


/*
	if(hc.body.length()<10){

		cout<<"<<<<<<<<<<<<<<<<<<<<<<<<10\n";
		string rrr;
		soaptransport.Read(sockConn,rrr);
		cout<<"rrr:"<<rrr<<"\n";
	}*/


	auto_ptr<SoapEnvelope> m_Evp=soapParser.parse(hc.body.c_str());

	//调出服务器部署的相应方法
	SoapMethod *smethod=m_Evp->getSoapMethod();
	
	if(smethod){
		//todo
	}

	string metdName=smethod->getMethodName();
	
	SoapEngineMethod *egnMethod=this->findMethod(metdName);

	if(!egnMethod){
		//todo
	}
	void * pResult=NULL;
	void * pSZFunct=NULL;
	string mURI="http://localhost/"+metdName+"/";
	string rURI="http://localhost/"+metdName+"/";
	
	list<Param> lp=smethod->getParams();

	if(!egnMethod->invoke(lp,&pResult,&pSZFunct,mURI,rURI)){
		//todo
	}
	
	SoapSerializer serializer;
	serializer.init();
	serializer.createSoapMethod((metdName+"Response").c_str(),mURI.c_str(),true);
	serializer.addOutputCmplxParam(pResult,pSZFunct,NULL,"root",rURI.c_str());
	
	soaptransport.setTransportProperty("Server","Microsoft-IIS/5.1");
	soaptransport.setTransportProperty("Date","Tue, 26 Dec 2006 12:13:11 GMT");
	soaptransport.setTransportProperty("Content-Type","text/xml");
	soaptransport.setTransportProperty("charset","\"utf-8\"");
	soaptransport.setTransportProperty("Transfer-encoding","chunked");
    

	//将待发送字符添加到缓存
	serializer.setOutputStream(&soaptransport);
	//处理HTTP Header
	soaptransport.processHttpHeader();
	//发送
	soaptransport.flushOutput(sockConn);

	}//while

	}//while
	
}
