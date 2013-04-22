// ExecuteMethod.cpp: implementation of the ExecuteMethod class.
//
//////////////////////////////////////////////////////////////////////

#include "ExecuteMethod.h"

int execute(ResultSet* rsSet, SoapSerializer *serializer, bool bArray){
	serializer->serialize(">\r\n",NULL);
	rsSet->serialize(serializer);
	return AXIS_SUCCESS;
}

int deCommand(void * *mObject,const  void * paramNode){

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

	if(0!=strcmp("Statement",StrX(node->getLocalName()).localForm()))
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
	Command *cmd=new Command(value); 

	if(!*mObject)
		*mObject=cmd;
	else{
		delete cmd;
		//err log here
		return AXIS_FAIL;
	}

	return AXIS_SUCCESS;
}

int seCommand(void * rs, SoapSerializer *serializer, bool bArray){

	serializer->serialize(">\r\n",NULL);

	Command * cmd=static_cast<Command*>(rs);
	
	if(!cmd)
		return AXIS_FAIL;

//	serializer->serialize("<Command>\r\n",NULL);

	serializer->serialize("<Statement>\r\n",NULL);

	serializer->serialize(cmd->c_str(),"\r\n",NULL);

	serializer->serialize("</Statement>\r\n",NULL);

//	serializer->serialize("</Command>\r\n",NULL);

	return AXIS_SUCCESS;
}

ExecuteMethod::~ExecuteMethod()
{

}
 
int ExecuteMethod::invoke(list<Param> params,void ** pResult,void ** pSZFunct,string &mURI,string &rURI){
	mURI="urn:schemas-microsoft-com:xml-analysis";
	rURI="urn:schemas-microsoft-com:xml-analysis:mddataset";
	
	list<Param>::iterator it= params.begin();
	Param pParam=*it;
	Command *cmd=(Command*)(pParam.m_Value.pCplxObj->pObject);
	 
	it++;
	pParam=*it;
	Properties *properties=(Properties*)(pParam.m_Value.pCplxObj->pObject);
	
	cout<<"Executing:\n"<<*cmd<<"\n";
	ResultSet *rsSet=new ResultSet(*cmd,*properties,"./data/Sales");
 
	if(!*pResult)
		*pResult=rsSet;
	else{
		return AXIS_FAIL;
	}

	*pSZFunct=execute;

	return AXIS_SUCCESS;
}

void ExecuteMethod::setUserTypeSeAndDeMethod(){
	
	setSeMethod("Command",seCommand);
	setDeMethod("Command",deCommand);
	
	setSeMethod("Properties",seProperties);
	setDeMethod("Properties",deProperties);
     
}

void  ExecuteMethod::setBasicSeAndDeMethod(){
	
}
