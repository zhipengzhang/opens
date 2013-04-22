#ifndef VCAPPDEFS_H
#define VCAPPDEFS_H


#ifdef DWSCHEMA_EXPORTS
#define SCHEMA_EXPORT
#else
#define SCHEMA_EXPORT
#endif
// __declspec(dllexport)
// __declspec(dllimport)
#include <xercesc/util/TransService.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/framework/XMLFormatter.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/util/XMLString.hpp> 
#include <xercesc/util/OutOfMemoryException.hpp>
#include <string>


using namespace xercesc;

class StrX
{
public :
    StrX(const XMLCh* const toTranscode)
    {
        fLocalForm = XMLString::transcode(toTranscode);
    }

    ~StrX()
    {
        XMLString::release(&fLocalForm);
    }

    const char* localForm() const
    {
        return fLocalForm;
    }
private :   
    char*   fLocalForm;
};


class DWSMQString
{
private:
	DWSMQString();
public:
	static std::string toLower(std::string  rhs);
	 
};


#define DWSCHEMA_CPP_NAMESPACE_BEGIN namespace DWSCHEMA_CPP_NAMESPACE {
#define DWSCHEMA_CPP_NAMESPACE_END  }
namespace DWSCHEMA_CPP_NAMESPACE { }
namespace dwschemac = DWSCHEMA_CPP_NAMESPACE;

#define EXPORT_STL_VECTOR( dllmacro, vectype ) ;/* \
  template class dllmacro std::allocator< vectype >; \
  template class dllmacro std::vector<vectype, \
    std::allocator< vectype > >;*/
#endif