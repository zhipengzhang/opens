// DISCOVER_DATASOURCES.cpp: implementation of the DISCOVER_DATASOURCES class.
//
//////////////////////////////////////////////////////////////////////
#ifdef WIN32

#pragma warning (disable : 4786)

#endif
 
#include <iostream>

#include "DISCOVER_DATASOURCES.h"

DISCOVER_DATASOURCES::DISCOVER_DATASOURCES(Properties properties):Rowset(properties)
{
	DataSourceName="Local Analysis Server";
	DataSourceDescription="SCUT LAB24 Analysis Server on local machine";
	URL="http://localhost:81";
	DataSourceInfo="Local Analysis Server";
//	ProviderName="SCUT LAB24 XML for Analysis";
	ProviderName="Microsoft XML for Analysis";
	//只支持MDP
	ProviderType="MDP";
	AuthenticationMode="Unauthenticated";
}

DISCOVER_DATASOURCES::~DISCOVER_DATASOURCES()
{
	
}

void DISCOVER_DATASOURCES::serialize(SoapSerializer * SoapSer){
	SoapSer->serialize("<row>",NULL);

	serializeAsElement("DataSourceName",DataSourceName,SoapSer);
	serializeAsElement("DataSourceDescription",DataSourceDescription,SoapSer);
	serializeAsElement("URL",URL,SoapSer);
	serializeAsElement("DataSourceInfo",DataSourceInfo,SoapSer);
	serializeAsElement("ProviderName",ProviderName,SoapSer);
	serializeAsElement("ProviderType",ProviderType,SoapSer);
	serializeAsElement("AuthenticationMode",AuthenticationMode,SoapSer);

	SoapSer->serialize("</row>",NULL);
}

//未实现
bool DISCOVER_DATASOURCES::processValue(Restrictions restrictions,Properties properties){
	
	return true;
}

void DISCOVER_DATASOURCES::processProperties(Properties properties){
	
}
