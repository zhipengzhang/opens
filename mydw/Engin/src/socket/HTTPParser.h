// HTTPParser.h: interface for the HTTPParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTTPPARSER_H__C0092F0D_CC65_406B_A4DA_B4BA07A83AFF__INCLUDED_)
#define AFX_HTTPPARSER_H__C0092F0D_CC65_406B_A4DA_B4BA07A83AFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "HTTPContext.h"
#include <map>
#include <string>


class HTTPParser  
{
public:
	bool parse(const std::string httpstr);
	
	HTTPContext getHc();
	HTTPParser();
	virtual ~HTTPParser();
	
private:
	bool handleInitialLine(std::string line);
	//the member of hc can be null or empty
	HTTPContext hc;
	bool handleHeaderLine(std::string line);
};

#endif // !defined(AFX_HTTPPARSER_H__C0092F0D_CC65_406B_A4DA_B4BA07A83AFF__INCLUDED_)
