#ifndef DWCONFIGURATION_H_
#define DWCONFIGURATION_H_

#include <string>
#include <vector>

class DWConfig;

class DWConfiguration
{
public:
   static DWConfiguration& instance();
   void addConfig(const std::string& name,const std::string file);
   void removeConfig(const std::string & name);
   DWConfig* getConfig(const std::string & name);
	~DWConfiguration();
private:
	DWConfiguration();
	DWConfiguration(const DWConfiguration& rhs);
	DWConfiguration& operator=(const DWConfiguration& rhs);
	static DWConfiguration instance_;
	std::vector<DWConfig*> configs_;
};
#endif