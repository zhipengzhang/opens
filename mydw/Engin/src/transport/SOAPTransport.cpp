// SoapTransport.cpp: implementation of the SoapTransport class.
//
//////////////////////////////////////////////////////////////////////

#include <axis/GDefine.hpp>

#include "SoapTransport.h"

#include <FSTREAM>

using namespace XmlRpc;

SoapTransport::SoapTransport()
{
	//init();
}

SoapTransport::~SoapTransport()
{
	
}

void SoapTransport::sendBytes(const char* pcSendBuffer){
	
	m_strBytesToSend += std::string (pcSendBuffer);

	if(m_strBytesToSend.size()>2048){
		mv.push_back(m_strBytesToSend);
		m_strBytesToSend="";
	}
}

bool SoapTransport::flushOutput(int sockConn){

	int st1=0;
	int *start1=&st1;
	bool flag=true;
	
	string buf="";
	for(int i=0;i<mv.size();i++){
//		cout<<mv[i];
		buf=buf+mv[i];
	}
	buf+=m_strBytesToSend;
	flag=XmlRpcSocket::nbWrite(sockConn,buf,start1);
	
	static int j=0;

	char stri[10];
	itoa(++j,stri,10);
	std::string filep=".\\log\\write"+string(stri)+".txt";
	std::ofstream logFile(filep.c_str());
	std::streambuf *outbuf = std::cout.rdbuf(logFile.rdbuf());
	std::cout<<"send:\n================================================================================\n"<<buf<<"\n";

	std::cout.rdbuf(outbuf);
	std::cout<<"send:++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"<<buf<<"\n";
	std::cout<<"send...\n";
	mv.clear();
	m_strBytesToSend="";
	m_vHTTPHeaders.clear();
	return flag;
}

int SoapTransport::setTransportProperty(const char *pcKey, const char *pcValue){
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("HTTPTransport", "setTransportProperty", this, 2,
					TRACETYPE_STRING, 0, ((void*)&pcKey),
					TRACETYPE_STRING, 0, ((void*)&pcValue));	  /* AUTOINSERTED TRACE */
	#endif

    if( !pcKey || !pcValue)	// Samisa - fix for AXISCPP-295. We must check for valid values here.
	{
			{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HTTPTransport", "setTransportProperty", this, 1,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

	}
    bool b_KeyFound = false;
    // Check for well known headers that we add on in every iteration
    if( strcmp( pcKey, "SOAPAction") == 0 || strcmp( pcKey, "Content-Length") == 0)
    {
		std::string strKeyToFind = std::string( pcKey);
		for (unsigned int i = 0; i < m_vHTTPHeaders.size(); i++)
		{
		    if (m_vHTTPHeaders[i].first == strKeyToFind)
			{
				m_vHTTPHeaders[i].second = (string) pcValue;
				b_KeyFound = true;
				break;
		    }
		}
    }
//    else
//    {
//        if(strcmp(pcKey, "Cookie")==0)
//        {
//        	{
//		#ifdef ENABLE_AXISTRACE
//			int traceRet = (addCookie(pcValue));
//			if (axiscpp::AxisTrace::isTraceOn())
//				axiscpp::AxisTrace::traceExit("HTTPTransport", "setTransportProperty", this, 2,
//					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
//			return traceRet;
//		#else
//			return addCookie(pcValue);
//		#endif
//	}
//
//        }
//    }
    if( !b_KeyFound)
    {
  		m_vHTTPHeaders.push_back( std::make_pair( (string) pcKey, (string) pcValue));
    }
		{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("HTTPTransport", "setTransportProperty", this, 3,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}
}

void SoapTransport::processHttpHeader(){
	std::string m_strHeaderBytesToSend="";
	m_strHeaderBytesToSend += "HTTP/1.1 200 OK\r\n";
	// Set other HTTP headers but not cookies as they are put in afterwards.
    for (unsigned int i = 0; i < m_vHTTPHeaders.size (); i++)
    {
        if( strcmp(m_vHTTPHeaders[i].first.c_str(), "Cookie")!=0)
        {
          m_strHeaderBytesToSend += m_vHTTPHeaders[i].first;
		  m_strHeaderBytesToSend += ": ";
		  m_strHeaderBytesToSend += m_vHTTPHeaders[i].second;
		  m_strHeaderBytesToSend += "\r\n";
        }
    }
	//对http的body进行分块
	char buff[24];

	int length=0;
	for(int j=0;j<mv.size();j++){
		length+=mv[j].length();
	}
	length+=m_strBytesToSend.length();
	
	sprintf( buff, "%x", length);

	if(mv.size()>0)
		mv[0]=m_strHeaderBytesToSend+"\r\n"+(std::string)buff+"\r\n"+mv[0];
	else
		m_strBytesToSend=m_strHeaderBytesToSend+"\r\n"+(std::string)buff+"\r\n"+m_strBytesToSend;
	//结束标志
	m_strBytesToSend+="\r\n0\r\n\r\n";
}
	

bool SoapTransport::init(int port,int backlog)
{
	XmlRpc::setVerbosity(5);
	
	fd = XmlRpcSocket::socket();
	if (fd < 0)
	{
		XmlRpcUtil::error("XmlRpcServer::bindAndListen: Could not create socket (%s).", XmlRpcSocket::getErrorMsg().c_str());
		return false;
	}

	  // Allow this port to be re-bound immediately so server re-starts are not delayed
  if ( ! XmlRpcSocket::setReuseAddr(fd))
  {
//    this->close();
    XmlRpcUtil::error("XmlRpcServer::bindAndListen: Could not set SO_REUSEADDR socket option (%s).", XmlRpcSocket::getErrorMsg().c_str());
    return false;
  }

  // Bind to the specified port on the default interface
  if ( ! XmlRpcSocket::bind(fd, port))
  {
//    this->close();
    XmlRpcUtil::error("XmlRpcServer::bindAndListen: Could not bind to specified port (%s).", XmlRpcSocket::getErrorMsg().c_str());
    return false;
  }

  // Set in listening mode
  if ( ! XmlRpcSocket::listen(fd, backlog))
  {
//    this->close();
   XmlRpcUtil::error("XmlRpcServer::bindAndListen: Could not set socket in listening mode (%s).", XmlRpcSocket::getErrorMsg().c_str());
    return false;
 }

	XmlRpcUtil::log(2, "XmlRpcServer::bindAndListen: server listening on port %d fd %d", port, fd);
  
	XmlRpcUtil::log(2, "XmlRpcServer::work: waiting for a connection");

	return true;
}

int SoapTransport::accept(){

	int socket = XmlRpcSocket::accept(fd);

	XmlRpcUtil::log(2, "XmlRpcServer::acceptConnection: socket %d", socket);
	if (socket < 0)
	{
		//this->close();
		XmlRpcUtil::error("XmlRpcServer::acceptConnection: Could not accept connection (%s).", XmlRpcSocket::getErrorMsg().c_str());
	}
	else  // Notify the dispatcher to listen for input on this source when we are in work()
	{
		XmlRpcUtil::log(2, "XmlRpcServer::acceptConnection: creating a connection");
		//_disp.addSource(this->createConnection(s), XmlRpcDispatch::ReadableEvent);
	}

	return socket;
}

int SoapTransport::closeClientSocket(int sockConn){
	XmlRpcSocket::close(sockConn);
	return 1;
}

int SoapTransport::closeServerSocket()
{
	XmlRpcSocket::close(fd);
	return 1;
}

bool SoapTransport::ReadARequest(int sock,string &recstr){
	
	recstr="";
	int ctlen;

	//循环直至找到Content-Length

	while(true){
		string tmp;
		if(!Read(sock,tmp)){
			
		//todo
			return false;
		}
		recstr=recstr+tmp;
		HTTPParser httpParser;
		httpParser.parse(recstr);
		HTTPContext hc=httpParser.getHc();
		ctlen=this->getContentLength(hc.header);
		
		if(ctlen==-1)
			continue;
		else
			break;
	}

	
	while(true){

		HTTPParser hparser;
		hparser.parse(recstr);
		HTTPContext hc=hparser.getHc();
		if(hc.body.length()==ctlen)
			return true;

		string temp;
		if(!Read(sock,temp)){
			
		//todo
			return false;
		}
		recstr=recstr+temp;
	}

	return true;
}

int SoapTransport::getContentLength(HTTPHeader header){
		//find the Content-Length Header
		HTTPHeader::iterator p_it;


	/*
		for(HTTPHeader::iterator it=header.begin();it!=header.end();it++){
				cout<<it->first<<" "<<it->second<<"\n";
	
			}*/
	
		p_it=header.find("content-length");
		if(p_it==header.end())
			return -1;

		//found
		else {
			string lenStr=p_it->second;
			int len=atoi(lenStr.c_str());
			return len;
		}
}

bool SoapTransport::Read(int sock,string &recstr)
{
    bool eof;
	static int i=0;
    bool flag=XmlRpcSocket::Read(sock,recstr,&eof);
	
	int errortype=XmlRpcSocket::getError();

	char stri[10];
	itoa(++i,stri,10);
	std::string filep=".\\log\\read"+string(stri)+".txt";
	std::ofstream logFile(filep.c_str());
	std::streambuf *outbuf = std::cout.rdbuf(logFile.rdbuf());
	std::cout<<"Read:"<<errortype<<"\n================================================================================\n"<<recstr<<"\n";

	std::cout.rdbuf(outbuf);

    std::cout<<"Read:\n================================================================================\n"<<recstr<<"\n";

	if(recstr.size()==0)
		flag=false;
	
	return flag;
}


