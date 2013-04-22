#ifndef DW_XML_CONFIG_H_
#define DW_XML_CONFIG_H_

#include <string>
#include <vector>
#include "DWElement.h"

class DWConfig
{
	friend class DWConfiguration;
public:
	bool initialize(const std::string & file);
	void reset();   
	std::string getName();
	XElement * getRoot();
	void print();
	std::vector<std::string> getValueVect(std::string name);
	std::string getValue(std::string name);
protected:
	DWConfig();
	DWConfig(const std::string & name,const std::string & file);
	DWConfig(const DWConfig &);	
	DWConfig & operator=(const DWConfig &);	
	~DWConfig();
private:
	std::string mFile; 
	std::string name_;
    XElement * xelement_;
};
#endif