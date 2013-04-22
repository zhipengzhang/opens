#ifndef XELEMENT_H_
#define XELEMENT_H_

#include <string>
#include <vector>

class XElementList;
class XAttributes;


class XElement 
{
	friend class DWConfig;
public:
	virtual void print()=0;
public:
	enum XNodeType
	{		   
		XELEMENT_NODE   = 1,
		XATTRIBUTE_NODE = 2, 
	};

	virtual std::string    getNodeName()=0 ;
	virtual std::string    getNodeValue()=0 ;
	virtual XNodeType      getNodeType()=0;
	virtual XAttributes *  getAttributes ()=0 ; 
	virtual XElementList*  getChildNodes ()=0 ;

	virtual bool hasAttributes()=0;
	virtual bool hasChildNodes()=0;
    virtual void appendChildNode(XElement * rhs)=0;
    virtual void removeChildNode(XElement * rhs)=0;
    virtual void setAttribute(std::string name,std::string value)=0;
	virtual void removeAttribute(std::string name)=0;
	virtual void setValue(std::string value)=0;
    static XElement* createElement(std::string name,std::string value,XNodeType type);

protected:
	virtual ~XElement(){};
};



class XAttributes
{
public:
    XElement* item(unsigned int it);
	unsigned int  getLength();
	bool hasAttributes();
	std::string getAttribute(std::string name);    
	void setAttribute(std::string name,std::string value);
	void removeAttribute(std::string name);
private:
	std::vector<XElement*> attributes_;
};

class XElementList
{
public:
    XElement* item(unsigned int it);
	unsigned int  getLength();
	bool hasChildNodes();
	XElement* getElement(std::string name);
	void addElement(XElement* rhs);
	void removeElement(std::string name);
private:
	std::vector<XElement*> elements_;
};
#endif