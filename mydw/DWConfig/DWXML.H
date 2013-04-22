//DWXML.h
#pragma warning (disable : 4786)
#ifndef XSCHEMAS_H
#define XSCHEMAS_H

#include <stdlib.h>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

class xercesc::DOMElement;
class xercesc::XercesDOMParser;
class xercesc::XMLTransService;

class XStrX
{
public :
    XStrX(const XMLCh* const toTranscode)
    {
        fLocalForm = xercesc::XMLString::transcode(toTranscode);
		xercesc::XMLString::trim(fLocalForm);
    }

    ~XStrX()
    {
		xercesc::XMLString::release(&fLocalForm);
    }

	static std::string toLower(std::string  rhs)
	{
		const size_t size = rhs.size();

		  std::string result = rhs;
		  for(int i=0;i<size;i++)
		  {
			 if(rhs[i]>='A'&&rhs[i]<='Z')
			 {
				 result[i]='a'+rhs[i]-'A';
			 }
		  }

		return result;
	}

	std::string  localForm() const
    {

		if(localForm=='\0')
		{
			return "";
		}
		else
		{
			return std::string(fLocalForm);
		}
    }
private :   
    char*   fLocalForm;
};

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


#endif