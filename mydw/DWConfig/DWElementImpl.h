#ifndef DWELEMENTIMPL_H_
#define DWELEMENTIMPL_H_

#include "DWConfig/DWElement.h"

class XElementImpl:public XElement
 {
public:
     std::string    getNodeName() ;
	 std::string    getNodeValue() ;
	 XNodeType      getNodeType() ;
	 XAttributes *  getAttributes (); 
	 XElementList*  getChildNodes ();
	 bool hasAttributes();
	 bool hasChildNodes();
     void appendChildNode(XElement * rhs);
     void removeChildNode(XElement * rhs);
     void setAttribute(std::string name,std::string value);
	 virtual void removeAttribute(std::string name);
	 void setValue(std::string value);
	 void print();
public:
	 XElementImpl();
	 XElementImpl(xercesc::DOMElement * element);
	 XElementImpl(std::string name,std::string value,XElement::XNodeType type);
	 ~XElementImpl();
private:
	 XAttributes attrs;
	 XElementList elements;
	 std::string name_;
	 std::string value_;
	 XElement::XNodeType  nodetype_;
 };


#endif