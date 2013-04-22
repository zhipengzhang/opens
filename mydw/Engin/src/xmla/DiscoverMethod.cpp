// DiscoverMethod.cpp: implementation of the DiscoverMethod class.
//
//////////////////////////////////////////////////////////////////////

#include "DiscoverMethod.h"


int discover(Rowset* rsSet, SoapSerializer *serializer, bool bArray){
	serializer->serialize(">\r\n",NULL);
	rsSet->serialize(serializer);
	return AXIS_SUCCESS;
}

int deRequestType(void * *mObject,const  void * paramNode){
	
	DOMNode * node=(DOMNode *)paramNode;
	node=node->getFirstChild();
	if(!node)
		//err log here
		return AXIS_FAIL;
	if(node->getNodeType()!=DOMNode::NodeType::TEXT_NODE)
	node=SoapParser::getNextSiblingNotNull(node,DOMNode::NodeType::TEXT_NODE);
	if(!node)
		//err log here
		return AXIS_FAIL;

	string value=StrX(node->getNodeValue()).localForm();

	DISCOVER_RequestType *dr=new DISCOVER_RequestType();

	*dr=Rowset::Str2DR(value);
	
	if(*dr==NULLorErr){
		delete dr;
		//err log here
		return AXIS_FAIL;
	}
	
	if(!*mObject)
		*mObject=dr;
	else{
		delete dr;
		//err log here
		return AXIS_FAIL;
	}

	return AXIS_SUCCESS;
}


int deRestrictions(void * *mObject,const void * paramNode){
	
	DOMNode * node=(DOMNode *)paramNode;
	node=node->getFirstChild();
	if(!node)
	//err log here
		return AXIS_FAIL;
	if(node->getNodeType()!=DOMNode::NodeType::ELEMENT_NODE)
	node=SoapParser::getNextSiblingNotNull(node,DOMNode::NodeType::ELEMENT_NODE);
	if(!node)
		//err log here
		return AXIS_FAIL;

	if(0!=strcmp("RestrictionList",StrX(node->getLocalName()).localForm()))
		//err log here
		return AXIS_FAIL;

	
	//if there is next element node,err!
	DOMNode * nextnode=node->getNextSibling();
	if(nextnode){
		if(nextnode->getNodeType()==DOMNode::NodeType::ELEMENT_NODE)
			//err log here
			return AXIS_FAIL;
		else
			nextnode=SoapParser::getNextSiblingNotNull(node,DOMNode::NodeType::ELEMENT_NODE);
			if(nextnode)
				//err log here
				return AXIS_FAIL;		
	}

	Properties *res=new Properties(); 

	node=node->getFirstChild();

	while(true){
		if(!node)
			break;
		if(node->getNodeType()!=DOMNode::NodeType::ELEMENT_NODE)
		node=SoapParser::getNextSiblingNotNull(node,DOMNode::NodeType::ELEMENT_NODE);
		if(!node)
			break;
		string value=Util::getValue(node);
		if(value!=""){
			string name=StrX(node->getLocalName()).localForm();
			res->insert(pair<string,string>(name,value));
		}
		else{
			//err log here
			delete res;
			return AXIS_FAIL;
		}
		node=node->getNextSibling();
	}

	if(!*mObject)
		*mObject=res;
	else{
		delete res;
		//err log here
		return AXIS_FAIL;
	}
	
	return AXIS_SUCCESS;
}

int deProperties(void * *mObject,const void * paramNode){

	DOMNode * node=(DOMNode *)paramNode;
	node=node->getFirstChild();
	if(!node)
	//err log here
		return AXIS_FAIL;
	if(node->getNodeType()!=DOMNode::NodeType::ELEMENT_NODE)
	node=SoapParser::getNextSiblingNotNull(node,DOMNode::NodeType::ELEMENT_NODE);
	if(!node)
		//err log here
		return AXIS_FAIL;

	if(0!=strcmp("PropertyList",StrX(node->getLocalName()).localForm()))
		//err log here
		return AXIS_FAIL;

	
	//if there is next element node,err!
	DOMNode * nextnode=node->getNextSibling();
	if(nextnode){
		if(nextnode->getNodeType()==DOMNode::NodeType::ELEMENT_NODE)
			//err log here
			return AXIS_FAIL;
		else
			nextnode=SoapParser::getNextSiblingNotNull(node,DOMNode::NodeType::ELEMENT_NODE);
			if(nextnode)
				//err log here
				return AXIS_FAIL;		
	}

	Properties *porps=new Properties(); 

	node=node->getFirstChild();

	while(true){
		if(!node)
			break;
		if(node->getNodeType()!=DOMNode::NodeType::ELEMENT_NODE)
		node=SoapParser::getNextSiblingNotNull(node,DOMNode::NodeType::ELEMENT_NODE);
		if(!node)
			break;
		string value=Util::getValue(node);
		if(value!=""){
			string name=StrX(node->getLocalName()).localForm();
			porps->insert(pair<string,string>(name,value));
		}
		else{
			//err log here
			delete porps;
			return AXIS_FAIL;
		}
		node=node->getNextSibling();
	}

	if(!*mObject)
		*mObject=porps;
	else{
		delete porps;
		//err log here
		return AXIS_FAIL;
	}

	return AXIS_SUCCESS;
}

int seRequestType(void * rs, SoapSerializer *serializer, bool bArray){
	
	DISCOVER_RequestType *dr;
	dr=static_cast<DISCOVER_RequestType*>(rs);
    DISCOVER_RequestType drObject=*dr;

	string RequestTypeStr;
	
	RequestTypeStr= Rowset::DR2Str(drObject);
	
	serializer->serialize(">\r\n",NULL);

	if(RequestTypeStr==""){
		return AXIS_FAIL;
	}

	serializer->serialize(RequestTypeStr.c_str(),"\r\n",NULL);

	return AXIS_SUCCESS;
}

int seRestrictions(void * rs, SoapSerializer *serializer, bool bArray){

	Restrictions *res=static_cast<Restrictions*>(rs);

	serializer->serialize(">\r\n",NULL);
	
	serializer->serialize("<RestrictionList>\r\n",NULL);
	
	if(!res)
		return AXIS_FAIL;
	
	Properties::iterator i=res->begin();
	
	while(i!=res->end()){
		string name=i->first;
		string value=i->second;
		serializer->serialize("<",name.c_str(),">",value.c_str(),"</",name.c_str(),">\r\n",NULL);
		i++;
	}
	
	serializer->serialize("</RestrictionList>\r\n",NULL);

	return AXIS_SUCCESS;
}


int seProperties(void * rs, SoapSerializer *serializer, bool bArray){

	serializer->serialize(">\r\n",NULL);

	Properties *props=static_cast<Properties*>(rs);

	if(!props)
	return AXIS_FAIL;
	
	serializer->serialize("<PropertyList>\r\n",NULL);

	Properties::iterator i=props->begin();
	
	while(i!=props->end()){
		string name=i->first;
		string value=i->second;
		serializer->serialize("<",name.c_str(),">",value.c_str(),"</",name.c_str(),">\r\n",NULL);
		i++;
	}
	
	serializer->serialize("</PropertyList>\r\n",NULL);

	return AXIS_SUCCESS;
}


DiscoverMethod::~DiscoverMethod()
{
	
}

//params:为传入参数;
//pResult:为经过客户代码计算所得的结果;
//pSZFunct:为结果的串行化函数;
//mURI表示返回方法Response的命名空间
//rURI表示root元素的命名空间

int DiscoverMethod::invoke(list<Param> params,void ** pResult,void ** pSZFunct,string &mURI,string &rURI){

	mURI="urn:schemas-microsoft-com:xml-analysis";
	rURI="urn:schemas-microsoft-com:xml-analysis:rowset";
	
	list<Param>::iterator it= params.begin();
	
	Param pParam=*it;
	DISCOVER_RequestType *drt=(DISCOVER_RequestType*)(pParam.m_Value.pCplxObj->pObject);
	
	it++;
	pParam=*it;
	Restrictions *restrictions=(Restrictions *)(pParam.m_Value.pCplxObj->pObject);
	
	it++;
	pParam=*it;
	Properties *properties=(Properties*)(pParam.m_Value.pCplxObj->pObject);
	
	//获取Resultset
	Rowset* rsSet=RowsetBuilder::getRowset(*drt,*restrictions,*properties);
	
	if(!*pResult)
		*pResult=rsSet;
	else{
		delete rsSet;
		//err log here
		return AXIS_FAIL;
	}

	*pSZFunct=discover;
	return AXIS_SUCCESS;
}


void DiscoverMethod::setUserTypeSeAndDeMethod(){
	
	setSeMethod("RequestType",seRequestType);
	setDeMethod("RequestType",deRequestType);

	setSeMethod("Restrictions",seRestrictions);
	setDeMethod("Restrictions",deRestrictions);

	setSeMethod("Properties",seProperties);
	setDeMethod("Properties",deProperties);
}

void  DiscoverMethod::setBasicSeAndDeMethod(){
	
}




