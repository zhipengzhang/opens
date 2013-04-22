// SoapParser.cpp: implementation of the SoapParser class.
//
//////////////////////////////////////////////////////////////////////

#include "SoapParser.h"
#include "../engine/SoapServer.h"
#include "../common/ComplexObjectHandler.h"
#include "../soap/SoapEngineMethod.h"
#include "../xmla/Rowset.h"
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>

/*
static const char*  gXMLInMemBuf=
"\
<soap-env:Envelope a=\"b\" xmlns:soap-env=\"http://schemas.xmlsoap.org/soap/envelope/\">\
<soap-env:Header>\
</soap-env:Header>\
<soap-env:Body>\
<Discover xmlns=\"urn:schemas-microsoft-com:xml-analysis\">\
<RequestType xmlns=\"\">DISCOVER_DATASOURCES</RequestType>\
<Restrictions><RestrictionList></RestrictionList></Restrictions>\
<Properties><PropertyList><Content>Data</Content></PropertyList></Properties>\
</Discover>\
</soap-env:Body>\
</soap-env:Envelope>\
";

static const char*  gMemBufId = "prodInfo";*/


SoapParser::SoapParser()
{	
	initialize();
	SoapKeywordMapping::initialize();
		// Instantiate the DOM parser.
    static const XMLCh gLS[] = { chLatin_L, chLatin_S, chNull };
    DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(gLS);
    parser = ((DOMImplementationLS*)impl)->createDOMBuilder(DOMImplementationLS::MODE_SYNCHRONOUS, 0);
	m_nsCounter=0;
/*
	m_SoapEnv=NULL;
	m_header=NULL;
	m_body=NULL;
	m_method=NULL;*/

	m_nSoapVersion=VERSION_LAST;
}

SoapParser::~SoapParser()
{
	//
    //  Delete the parser itself.  Must be done prior to calling Terminate, below.
    //
    parser->release();

    // And call the termination method
    XMLPlatformUtils::Terminate();

/*
	if(m_SoapEnv)
		delete m_SoapEnv;*/

}
 

void  SoapParser::initialize(){
	// Initialize the XML4C system
    try
    {
        XMLPlatformUtils::Initialize();  
    }

    catch (const XMLException& toCatch)
    {
         cerr << "Error during initialization! :\n"
              << StrX(toCatch.getMessage()) << endl;
         return ;
    }

}

auto_ptr<SoapEnvelope> SoapParser::parse(char const * const xmlChar){
	
	auto_ptr<SoapEnvelope> m_pEnvl(new SoapEnvelope);

	DOMDocument *doc=getDocument(xmlChar);
	
	if(!doc){
		return m_pEnvl;
	}
	
	DOMNode *envNode=doc->getFirstChild();

	if(!envNode)
		return m_pEnvl;
	
	if(0==strcmp(StrX(envNode->getLocalName()).localForm(),SoapKeywordMapping::map (SOAP_VER_1_2).
		pchWords[SKW_ENVELOPE])){
		
		/* set all attributes and namespaces of SoapEnvelope */
		if(envNode->getNamespaceURI()){
			//set the soap version based on the namespace uri

			Attribute *pNameSpace = NULL;
			std::list<Attribute*> attributeList;
			
			if(0==strcmp(StrX(envNode->getNamespaceURI()).localForm(),SoapKeywordMapping::map (SOAP_VER_1_1).pchNamespaceUri)){
				m_nSoapVersion = SOAP_VER_1_1;
				pNameSpace = new Attribute(attributeList,SoapKeywordMapping::map (SOAP_VER_1_1).pchPrefix,"xmlns",SoapKeywordMapping::map (SOAP_VER_1_1).pchNamespaceUri);
			}
			else if(0==strcmp(StrX(envNode->getNamespaceURI()).localForm(),SoapKeywordMapping::map (SOAP_VER_1_2).pchNamespaceUri)){
				m_nSoapVersion = SOAP_VER_1_2;
				pNameSpace = new Attribute(attributeList,SoapKeywordMapping::map (SOAP_VER_1_2).pchPrefix,"xmlns",SoapKeywordMapping::map (SOAP_VER_1_2).pchNamespaceUri);
			}
			else {
				m_nSoapVersion = VERSION_LAST;
				pNameSpace = new Attribute(attributeList,SoapKeywordMapping::map (VERSION_LAST).pchPrefix,"xmlns",SoapKeywordMapping::map (VERSION_LAST).pchNamespaceUri);
			}
		
			m_pEnvl->addNamespaceDecl (pNameSpace);
		}
		else
			//err log
			return m_pEnvl;
		
		if(envNode->getAttributes()->getLength()>1){
			//there is some attributes
			DOMNamedNodeMap * nnmap=envNode->getAttributes();
			for(int i=0;i<nnmap->getLength();i++){
			//namespace,skip it!
			if(nnmap->item(i)->getPrefix()&&0==strcmp(StrX(nnmap->item(i)->getPrefix()).localForm(),"xmlns"))
				continue;
			Attribute *attr = NULL;
			std::list<Attribute*> attributeList0;
			if(nnmap->item(i)->getPrefix())
				attr=new Attribute(attributeList0,StrX(nnmap->item(i)->getNodeName()).localForm(),StrX(nnmap->item(i)->getPrefix()).localForm(),StrX(nnmap->item(i)->getNodeValue()).localForm());	
			else	
				attr=new Attribute(attributeList0,StrX(nnmap->item(i)->getNodeName()).localForm(),"",StrX(nnmap->item(i)->getNodeValue()).localForm());
			m_pEnvl->addAttribute(attr);
			}
					
		}

		//header and body
		DOMNode* curnode=envNode->getFirstChild();
		
		if(!curnode)
			return m_pEnvl;

		if(curnode->getNodeType()!=DOMNode::NodeType::ELEMENT_NODE)
			curnode=getNextSiblingNotNull(curnode,DOMNode::NodeType::ELEMENT_NODE);
		if(!curnode)

			return m_pEnvl;
		
		if(0 == strcmp (StrX(curnode->getLocalName()).localForm(),SoapKeywordMapping::map (m_nSoapVersion).pchWords[SKW_HEADER])){
			//handle soap header
			SoapHeader * m_pHead=parseHeader(curnode);

			m_pEnvl->setSoapHeader(m_pHead);
			
			curnode=getNextSiblingNotNull(curnode,DOMNode::NodeType::ELEMENT_NODE);
			
			if(!curnode)
				//no soap body£¬err log
				return m_pEnvl;
		}
			
					
		if(0 == strcmp (StrX(curnode->getLocalName()).localForm(),SoapKeywordMapping::map (m_nSoapVersion).pchWords[SKW_BODY])){
			//handle soap body
			SoapBody *m_pBody=parseBody(curnode);

			m_pEnvl->setSoapBody(m_pBody);
			
		}
			
		else{
			//not soap body£¬err log
			return m_pEnvl;
		}
					
		if(getNextSiblingNotNull(curnode,DOMNode::NodeType::ELEMENT_NODE))
			//there is some element,err log
			return m_pEnvl;

//		this->m_SoapEnv=m_pEnvl;
		return m_pEnvl;
	}

	else
	return m_pEnvl;


}

DOMDocument * SoapParser::getDocument(const char  * const xmlChar){
	
	parser->setFeature(XMLUni::fgDOMNamespaces, true);
    parser->setFeature(XMLUni::fgXercesSchema, false);
	
	// And create our error handler and install it
    DOMCountErrorHandler errorHandler;
    parser->setErrorHandler(&errorHandler);

	//reset error count first
    errorHandler.resetErrors();

	DOMDocument *doc = 0;

	MemBufInputSource memBufIS((const XMLByte*)xmlChar, strlen(xmlChar), "prodInfo", false);

	Wrapper4InputSource wInputS(&memBufIS,false);
	
    try
    {
		// reset document pool
        parser->resetDocumentPool();   
        doc = parser->parse(wInputS);
     }

     catch (const XMLException& toCatch)
     {
            cerr << "\nError during parsing: '" << xmlChar << "'\n"
                 << "Exception message is:  \n"
                 << StrX(toCatch.getMessage()) << "\n" << endl;
	
			return NULL;
     }
     catch (const DOMException& toCatch)
     {
            const unsigned int maxChars = 2047;
            XMLCh errText[maxChars + 1];

            cerr << "\nDOM Error during parsing: '" << xmlChar << "'\n"
                 << "DOMException code is:  " << toCatch.code << endl;

            if (DOMImplementation::loadDOMExceptionMsg(toCatch.code, errText, maxChars))
                 cerr << "Message is: " << StrX(errText) << endl;

           	return NULL;
			
        }
        catch (...)
        {
            cerr << "\nUnexpected exception during parsing: '" << xmlChar << "'\n";
            return NULL;
        }
		return doc;
}



DOMCountErrorHandler::DOMCountErrorHandler() :

    fSawErrors(false)
{
}

DOMCountErrorHandler::~DOMCountErrorHandler()
{
}


// ---------------------------------------------------------------------------
//  DOMCountHandlers: Overrides of the DOM ErrorHandler interface
// ---------------------------------------------------------------------------
bool DOMCountErrorHandler::handleError(const DOMError& domError)
{
    fSawErrors = true;
    if (domError.getSeverity() == DOMError::DOM_SEVERITY_WARNING)
        cerr << "\nWarning at file ";
    else if (domError.getSeverity() == DOMError::DOM_SEVERITY_ERROR)
        cerr << "\nError at file ";
    else
        cerr << "\nFatal Error at file ";

    cerr << StrX(domError.getLocation()->getURI())
         << ", line " << domError.getLocation()->getLineNumber()
         << ", char " << domError.getLocation()->getColumnNumber()
         << "\n  Message: " << StrX(domError.getMessage()) << endl;

    return true;
}

void DOMCountErrorHandler::resetErrors()
{
    fSawErrors = false;
}

SoapHeader * SoapParser::parseHeader(const DOMNode *headnode)
{
	//to be finished
	SoapHeader* soapheader=new SoapHeader();
//	m_header=soapheader;
	return soapheader;
}

//½âÎösoap body
SoapBody * SoapParser::parseBody(const DOMNode * bodynode){
	SoapBody *soapbody=new SoapBody();
	DOMNode* mthnode=bodynode->getFirstChild();
	if(!mthnode)
		//err log here
		return soapbody;
	if(mthnode->getNodeType()!=DOMNode::NodeType::ELEMENT_NODE)
		mthnode=getNextSiblingNotNull(mthnode,DOMNode::NodeType::ELEMENT_NODE);
	if(!mthnode)
		//err log here
		return soapbody;

	SoapMethod * soapmethod=new SoapMethod();
	
	soapbody->setSoapMethod(soapmethod);
	
	soapmethod->setReturn(false);

	//set local name/prefix/namespaceURI

	soapmethod->setLocalName(StrX(mthnode->getLocalName()).localForm());
	
	if(mthnode->getNamespaceURI()){
		soapmethod->setURI(StrX(mthnode->getNamespaceURI()).localForm());

		if(mthnode->getPrefix())
			soapmethod->setPrefix(StrX(mthnode->getPrefix()).localForm());
		else
			soapmethod->setPrefix(getDefaultNamespacePrefix().c_str());
	}
	else if(mthnode->getPrefix())
		soapmethod->setPrefix(StrX(mthnode->getPrefix()).localForm());
	
	
	//set attributes
	if(mthnode->getAttributes()->getLength()>1){
		//there is some attributes
		DOMNamedNodeMap * nnmap=mthnode->getAttributes();
		for(int i=0;i<nnmap->getLength();i++){
		//namespace,skip it!
		if(nnmap->item(i)->getPrefix()&&0==strcmp(StrX(nnmap->item(i)->getPrefix()).localForm(),"xmlns"))
			continue;
		Attribute *attr = NULL;
		std::list<Attribute*> attributeList0;
		if(nnmap->item(i)->getPrefix())
			attr=new Attribute(attributeList0,StrX(nnmap->item(i)->getNodeName()).localForm(),StrX(nnmap->item(i)->getPrefix()).localForm(),StrX(nnmap->item(i)->getNodeValue()).localForm());	
		else	
			attr=new Attribute(attributeList0,StrX(nnmap->item(i)->getNodeName()).localForm(),"",StrX(nnmap->item(i)->getNodeValue()).localForm());
		soapmethod->addAttribute(attr);
		}
	}
	
	SoapEngineMethod *seMethod=SoapServer::instance()->findMethod(soapmethod->getMethodName());

	if(!seMethod)
		//err log here
		return soapbody;

	//handle Params
	DOMNode *paramNode =mthnode->getFirstChild();
	while(true){
		if(!paramNode)
			break;
		if(paramNode->getNodeType()!=DOMNode::NodeType::ELEMENT_NODE)
		paramNode=getNextSiblingNotNull(paramNode,DOMNode::NodeType::ELEMENT_NODE);
		if(!paramNode)
			break;
		//handle a Param

		string paramName=StrX(paramNode->getLocalName()).localForm();
		AXIS_DESERIALIZE_FUNCT de_fun=seMethod->findDeMethod(paramName);
		AXIS_SERIALIZE_FUNCT se_fun=seMethod->findSeMethod(paramName);
		void * mObject=NULL;
		
		if(de_fun){

			if(AXIS_FAIL==de_fun(&mObject,paramNode))
				//err log here
				return soapbody;
		}
		else{
			//err log here
			return soapbody;
		}

		Param pParam;
	
		pParam.m_Value.pCplxObj = new ComplexObjectHandler();
		pParam.m_Value.pCplxObj->pObject = mObject;
		pParam.m_Value.pCplxObj->pSZFunct = (AXIS_SERIALIZE_FUNCT) se_fun;
		pParam.m_Value.pCplxObj->pDelFunct =NULL;

		//set name,prefix,namespace
		pParam.setName(paramName.c_str());

		soapmethod->addOutputParam(pParam);

		if(paramNode->getNamespaceURI()){
			pParam.setURI(StrX(paramNode->getNamespaceURI()).localForm());
		}
		if(paramNode->getPrefix()){
			pParam.setPrefix(StrX(paramNode->getPrefix()).localForm());
		}

		//next dom node
		paramNode=paramNode->getNextSibling();
	}
	
	//not to handle the leaving element behind

	return soapbody;
}


DOMNode * SoapParser::getNextSiblingNotNull(DOMNode * node,DOMNode::NodeType ntype){
	if(!node)
		return NULL;
	
	DOMNode *rnode=node;

	while(true){
		rnode=rnode->getNextSibling();
		//the last node
		if(!rnode)
			return NULL;

		if(rnode->getNodeType()==ntype)
			return rnode;
		
	}
	
}

//return a default Namespace Prefix
std::string SoapParser::getDefaultNamespacePrefix()
{
	m_nsCounter++;
	AxisChar m_Buf[32];
    AxisSprintf(m_Buf, 8, "ns%d", m_nsCounter);  
	std::string ns=m_Buf;
	return ns;
}