// DiscoverMethod.h: interface for the DiscoverMethod class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISCOVERMETHOD_H__8E625BD2_3DA4_4198_A00D_6DBE10A02ECC__INCLUDED_)
#define AFX_DISCOVERMETHOD_H__8E625BD2_3DA4_4198_A00D_6DBE10A02ECC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "../soap/SoapEngineMethod.h"
#include "Rowset.h"
#include "RowsetBuilder.h"
#include "../soap/SoapParser.h"
//#include "Util.h"
#include <string>

using namespace std;

class Util  
{

public:
	Util();
	virtual ~Util();
 

	//取得mnode节点的值
	static  string getValue(const DOMNode * mnode){
		DOMNode	*node=mnode->getFirstChild();
		if(!node)
			//err log here
			return "";
		if(node->getNodeType()!=DOMNode::NodeType::TEXT_NODE)
		node=SoapParser::getNextSiblingNotNull(node,DOMNode::NodeType::TEXT_NODE);
		if(!node)
			//err log here
			return "";
		string value=StrX(node->getNodeValue()).localForm();
		return value;
	}
};


class DiscoverMethod : public SoapEngineMethod
{  

public:
	DiscoverMethod(SoapServer * s):SoapEngineMethod("Discover",s){
		
		setBasicSeAndDeMethod();
		setUserTypeSeAndDeMethod();
	}
	virtual ~DiscoverMethod();

	int invoke(list<Param> params,void ** pResult,void ** pSZFunct,string &mURI,string &rURI);

protected:
	void setUserTypeSeAndDeMethod();
	void setBasicSeAndDeMethod();

} Discover(SoapServer::instance());

#endif // !defined(AFX_DISCOVERMETHOD_H__8E625BD2_3DA4_4198_A00D_6DBE10A02ECC__INCLUDED_)
