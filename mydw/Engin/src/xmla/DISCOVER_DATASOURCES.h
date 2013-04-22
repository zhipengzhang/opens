// DISCOVER_DATASOURCES.h: interface for the DISCOVER_DATASOURCES class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISCOVER_DATASOURCES_H__75A55132_B49F_4A3B_A8A0_9AC5E1B67116__INCLUDED_)
#define AFX_DISCOVER_DATASOURCES_H__75A55132_B49F_4A3B_A8A0_9AC5E1B67116__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "../soap/SoapSerializer.h"

#include "Rowset.h"

#include <string>

using namespace std;




//返回服务器或 Web 服务上可用的 XML for Analysis 数据源列表。
class DISCOVER_DATASOURCES:public Rowset
{
public:
	DISCOVER_DATASOURCES(Properties properties);
	virtual ~DISCOVER_DATASOURCES();
	void serialize(SoapSerializer * SoapSer);
	bool processValue(Restrictions restrictions,Properties properties);
	void processProperties(Properties properties);
	AxisChar* DataSourceName;
	AxisChar* DataSourceDescription;
	AxisChar* URL;
	AxisChar* DataSourceInfo;
	AxisChar* ProviderName;
	AxisChar* ProviderType;
	AxisChar* AuthenticationMode;
};

#endif // !defined(AFX_DISCOVER_DATASOURCES_H__75A55132_B49F_4A3B_A8A0_9AC5E1B67116__INCLUDED_)
