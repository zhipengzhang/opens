// PreComputeMethod.cpp: implementation of the PreComputeMethod class.
//
//////////////////////////////////////////////////////////////////////


#include "PreComputeMethod.h"

#include "time.h"

#include <PreComputation/PreComputation.h>

using namespace PreCmpt;

int preCompute(string * rsSet, SoapSerializer *serializer, bool bArray){

	serializer->serialize(">\r\n",NULL);
	serializer->serialize("<PreCmptRetFlag>\r\n",NULL);
	serializer->serialize(rsSet->c_str(),"\r\n",NULL);
	serializer->serialize("</PreCmptRetFlag>\r\n",NULL);

	return AXIS_SUCCESS;
}

int deSchemaName(void * *mObject,const  void * paramNode){
	
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

	string * s=new string(value);
	
	if(!*mObject)
		*mObject=s;
	else{
		delete s;
		//err log here
		return AXIS_FAIL;
	}
	return AXIS_SUCCESS;
}

int deCubeName(void * *mObject,const  void * paramNode){
	
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

	string * s=new string(value);
	
	if(!*mObject)
		*mObject=s;
	else{
		delete s;
		//err log here
		return AXIS_FAIL;
	}
	return AXIS_SUCCESS;
}

int seSchemaName(void * rs, SoapSerializer *serializer, bool bArray){
	
	string *str;
	str=static_cast<string*>(rs);
	
	serializer->serialize(">\r\n",NULL);
	if(!str)
		return AXIS_FAIL;
	serializer->serialize(str->c_str(),"\r\n",NULL);

	return AXIS_SUCCESS;
}

int seCubeName(void * rs, SoapSerializer *serializer, bool bArray){
	
	string *str;
	str=static_cast<string*>(rs);
	
	serializer->serialize(">\r\n",NULL);
	if(!str)
		return AXIS_FAIL;
	serializer->serialize(str->c_str(),"\r\n",NULL);

	return AXIS_SUCCESS;
}




PreComputeMethod::~PreComputeMethod()
{

}
  
int PreComputeMethod::invoke(list<Param> params,void ** pResult,void ** pSZFunct,string &mURI,string &rURI){
	PreComputation p;
	
	list<Param>::iterator it= params.begin();
	
	Param pParam=*it;
	string * schemaName=(string *)(pParam.m_Value.pCplxObj->pObject);
	
	it++;
	pParam=*it;
	string *cubeName=(string *)(pParam.m_Value.pCplxObj->pObject);
	
//    string rets = p.preCompute(*schemaName, *cubeName);
	
	time_t start_time, cur_time; // ±äÁ¿ÉùÃ÷ 


time(&start_time); 
do { time(&cur_time); 
} while((cur_time - start_time) < 15);
 


	string rets="result";

	string * ret=new string(rets);

	if(!*pResult)
		*pResult=ret;
	else{
		delete ret;
		//err log here
		return AXIS_FAIL;
	}

	*pSZFunct=preCompute;
	
	return AXIS_SUCCESS;

}
 
void PreComputeMethod::setUserTypeSeAndDeMethod(){
	
	setSeMethod("schemaname",seSchemaName);
	setDeMethod("schemaname",deSchemaName);
	
	setSeMethod("cubename",seCubeName);
	setDeMethod("cubename",deCubeName);

}

void  PreComputeMethod::setBasicSeAndDeMethod(){
	
}
