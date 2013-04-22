#include <assert.h>
#include "DWConfig/DWConfig.h"
#include "DWConfig/DWConfiguration.h"

DWConfiguration DWConfiguration::instance_;


DWConfiguration& DWConfiguration::instance()
{
	return instance_;
}

void DWConfiguration::addConfig(const std::string& name,const std::string file)
{
    assert(name !="" || file != "");
	for(int i =0 ; i<configs_.size();i++)
	{
		if(name == configs_[i]->getName())
		{
			return ;
		}
	}
	
	DWConfig * conf = new DWConfig(name,file);
	if(conf!=NULL)
	{
		if(!conf->initialize(file))
		{
			delete conf;
			conf = NULL;
			return ;
		}
		configs_.push_back(conf);
	}
   
}

void DWConfiguration::removeConfig(const std::string & name)
{
	if(name == "")return ;

	std::vector<DWConfig *>::iterator itb = configs_.begin();
	for(;itb!= configs_.end();itb++)
	{
		if(name == ((DWConfig*)itb)->getName())
		{
			configs_.erase(itb);
			return ;
		}
	}
}

DWConfig* DWConfiguration::getConfig(const std::string & name)
{
	for(int i=0;i<configs_.size();i++)
	{
		if(name == configs_[i]->getName())
		{
			return configs_[i];
		}
	}
	return NULL;
}

DWConfiguration::DWConfiguration()
{
}

DWConfiguration::~DWConfiguration()
{
  for(int i=0;i<configs_.size();i++)
  {
	  delete configs_[i];
  }
  configs_.clear();
}
