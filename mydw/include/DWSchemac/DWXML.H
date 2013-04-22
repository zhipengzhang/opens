//DWXML.h
#pragma warning (disable : 4786)
#ifndef XSCHEMAS_H
#define XSCHEMAS_H

#include <stdlib.h>
#include <string>
#include <vector>
#include <stdexcept>
#include "DWSchemac/VCAPPDefs.h"

using namespace std;

class xercesc::DOMElement;
class xercesc::XercesDOMParser;
class xercesc::XMLTransService;

DWSCHEMA_CPP_NAMESPACE_BEGIN


class DWXML
{
public:
     DWXML();
     ~DWXML();

	 xercesc::DOMElement* xmlParser(const std::string&) throw(std::runtime_error);
     void printElement(xercesc::DOMElement *element);
     xercesc::XercesDOMParser * getDOMParser();
     //DOMElement getSchemaEleMent();
private:
	xercesc::XMLTransService::Codes tranServiceCode;  
    xercesc::XercesDOMParser *m_DOMXmlParser;   //定义解析对象
};

DWSCHEMA_CPP_NAMESPACE_END

#endif