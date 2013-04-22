// SOAPTransport.h: interface for the SOAPTransport class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOAPTRANSPORT_H__4B1782F1_3D8E_4D78_A9F6_23D8079845CF__INCLUDED_)
#define AFX_SOAPTRANSPORT_H__4B1782F1_3D8E_4D78_A9F6_23D8079845CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "../socket/XmlRpcSocket.h"
#include "../socket/XmlRpcUtil.h"
#include "../socket/XmlRpc.h"
#include "../socket/HTTPParser.h"

using namespace std;

class SoapTransport  
{
public:

	SoapTransport();
	virtual ~SoapTransport();
	void sendBytes(const char* pcSendBuffer);
	bool flushOutput(int sockConn);
	int setTransportProperty(const char *pcKey, const char *pcValue);
	void processHttpHeader();

	std::string m_strBytesToSend;
	
	vector<string> mv;

	bool init(int port,int backlog);
//	bool reuseAddr();
//	bool bind();
//	bool listen();
	int accept();

	
	bool ReadARequest(int sock,string &recstr);
	bool Read(int sock,string &recstr);
	int closeServerSocket();

	int closeClientSocket(int sockConn);

private:
	int getContentLength(HTTPHeader header);
//	int sock;
	int fd;
//	int port;
//	int backlog;
	/**
    * Vector to hold HTTP header key/value pairs
    */
    std::vector < std::pair < std::string, std::string > >m_vHTTPHeaders;
	
};

#endif // !defined(AFX_SOAPTRANSPORT_H__4B1782F1_3D8E_4D78_A9F6_23D8079845CF__INCLUDED_)
