// ResultsetBuilder.h: interface for the ResultsetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESULTSETBUILDER_H__B86E8E65_FFE0_4750_ACF1_DD23282D2037__INCLUDED_)
#define AFX_RESULTSETBUILDER_H__B86E8E65_FFE0_4750_ACF1_DD23282D2037__INCLUDED_

#ifdef WIN32
#pragma warning (disable : 4786)
#pragma warning (disable : 4275)
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Rowset.h"
#include "DISCOVER_DATASOURCES.h"
#include "DISCOVER_ENUMERATORS.h"
#include "DISCOVER_KEYWORDS.h"
#include "DISCOVER_LITERALS.h"
#include "DISCOVER_PROPERTIES.h"
#include "DISCOVER_SCHEMA_ROWSETS.h"
#include "MDSCHEMA_ACTIONS.h"
#include "MDSCHEMA_CUBES.h"
#include "MDSCHEMA_DIMENSIONS.h"
#include "MDSCHEMA_HIERARCHIES.h"
#include "MDSCHEMA_LEVELS.h"
#include "MDSCHEMA_MEASURES.h"
#include "MDSCHEMA_PROPERTIES.h"
#include "MDSCHEMA_SETS.h"
#include "MDSCHEMA_MEMBERS.h"
#include <DWSchemac/XSchemas.h>
#include <string>
#include <vector>
using namespace std;

class RowsetBuilder  
{
public:
	RowsetBuilder();
	virtual ~RowsetBuilder();
	static Rowset* getRowset(DISCOVER_RequestType RequestType,Restrictions restrictions,Properties properties);
	static Rowset* getRowset(DISCOVER_RequestType RequestType,Properties properties);
};

#endif // !defined(AFX_RESULTSETBUILDER_H__B86E8E65_FFE0_4750_ACF1_DD23282D2037__INCLUDED_)
