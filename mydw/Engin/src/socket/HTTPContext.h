// HTTPContext.h: interface for the HTTPContext class.
//
//////////////////////////////////////////////////////////////////////
#ifdef _MSC_VER
#pragma warning(disable: 4786)
#pragma warning(disable: 4503)
#endif

#if !defined(AFX_HTTPCONTEXT_H__4E33DB55_85AD_4478_B369_FEAAB38F81D4__INCLUDED_)
#define AFX_HTTPCONTEXT_H__4E33DB55_85AD_4478_B369_FEAAB38F81D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <string>

using namespace std;

typedef map<string,string> HTTPHeader;

struct HTTPContext  
{

	//HTTP method name
	std::string methodname;
	//the local path of the requested resource
	std::string path;
	//the version of HTTP being used
	std::string version;
	//Header Lines
	HTTPHeader header;
	//The Message Body
	string body;

};

#endif // !defined(AFX_HTTPCONTEXT_H__4E33DB55_85AD_4478_B369_FEAAB38F81D4__INCLUDED_)
