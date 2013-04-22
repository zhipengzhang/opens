// SoapParser.h: interface for the SoapParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOAPPARSER_H__4C953813_10E5_40BC_96C4_9D1A1FDB3377__INCLUDED_)
#define AFX_SOAPPARSER_H__4C953813_10E5_40BC_96C4_9D1A1FDB3377__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef WIN32

#pragma warning (disable : 4786)

#endif

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/AbstractDOMParser.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMBuilder.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMError.hpp>
#include <xercesc/dom/DOMLocator.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <DWSchemac/VCAPPDefs.h>

#include "SoapEnvelope.h"
#include "SoapKeywordMapping.h"
#include "SoapHeader.h"	// Added by ClassView

using namespace XERCES_CPP_NAMESPACE;
 
class SoapParser  
{
public:
	SoapParser();
	virtual ~SoapParser();
	
/*
	SoapEnvelope * getEnvelope() {return m_SoapEnv;}

	SoapHeader * getHeader(){return m_header;}

	SoapBody * getBody(){return m_body;}

	SoapMethod * getMethod(){return m_method;}*/


	SOAP_VERSION getVersion(){return m_nSoapVersion;}
	
	auto_ptr<SoapEnvelope> parse(char const * const xmlChar);

	static DOMNode * getNextSiblingNotNull(DOMNode * headnode,DOMNode::NodeType ntype);

private:
	SoapBody * parseBody(const DOMNode * bodynode);
	
	SoapHeader * parseHeader(const DOMNode * headnode);

	

	void initialize();

	DOMDocument * getDocument(const char  * const xmlChar);

	std::string getDefaultNamespacePrefix();

	int m_nsCounter;
	
	DOMBuilder *parser;

/*
	SoapEnvelope * m_SoapEnv;

	SoapBody * m_body;

	SoapHeader * m_header;

	SoapMethod * m_method;*/


	SOAP_VERSION m_nSoapVersion;
	
};

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
//  Simple error handler deriviative to install on parser
// ---------------------------------------------------------------------------
class DOMCountErrorHandler : public DOMErrorHandler
{
public:
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    DOMCountErrorHandler();
    ~DOMCountErrorHandler();


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    bool getSawErrors() const;


    // -----------------------------------------------------------------------
    //  Implementation of the DOM ErrorHandler interface
    // -----------------------------------------------------------------------
    bool handleError(const DOMError& domError);
    void resetErrors();


private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    DOMCountErrorHandler(const DOMCountErrorHandler&);
    void operator=(const DOMCountErrorHandler&);


    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fSawErrors
    //      This is set if we get any errors, and is queryable via a getter
    //      method. Its used by the main code to suppress output if there are
    //      errors.
    // -----------------------------------------------------------------------
    bool    fSawErrors;
};



// ---------------------------------------------------------------------------
//  This is a simple class that lets us do easy (though not terribly efficient)
//  trancoding of XMLCh data to local code page for display.
// ---------------------------------------------------------------------------
/*
class StrX
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    StrX(const XMLCh* const toTranscode)
    {
        // Call the private transcoding method
        fLocalForm = XMLString::transcode(toTranscode);
    }

    ~StrX()
    {
        XMLString::release(&fLocalForm);
    }


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    const char* localForm() const
    {
        return fLocalForm;
    }

private :
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fLocalForm
    //      This is the local code page form of the string.
    // -----------------------------------------------------------------------
    char*   fLocalForm;
};*/


inline ostream& operator<<(ostream& target, const StrX& toDump)
{
    target << toDump.localForm();
    return target;
}

inline bool DOMCountErrorHandler::getSawErrors() const
{
    return fSawErrors;
}


#endif // !defined(AFX_SOAPPARSER_H__4C953813_10E5_40BC_96C4_9D1A1FDB3377__INCLUDED_)
