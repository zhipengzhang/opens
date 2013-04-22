// MDSCHEMA_PROPERTIES.h: interface for the MDSCHEMA_PROPERTIES class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDSCHEMA_PROPERTIES_H__3379B6FF_1B17_47AC_A9DB_2F2A27F3DE0D__INCLUDED_)
#define AFX_MDSCHEMA_PROPERTIES_H__3379B6FF_1B17_47AC_A9DB_2F2A27F3DE0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Rowset.h"

#include <DWSchemac/XSchemas.h>
#include <DWSchemac/XSchema.h>
#include <DWSchemac/Dimension.h>
#include <DWSchemac/XCube.h>
#include <DWSchemac/Hierarchy.h>
#include <DWSchemac/Measure.h>

using namespace dwschemac;

class MDSCHEMA_PROPERTIES :public Rowset
{
public:
	MDSCHEMA_PROPERTIES(Properties properties);
	virtual ~MDSCHEMA_PROPERTIES();

	void serialize(SoapSerializer * SoapSer);
	bool processValue(Restrictions restrictions,Properties properties);
	void processProperties(Properties properties);
	
private:
	
	Row getRow(Dimension* dimension);

};

#endif // !defined(AFX_MDSCHEMA_PROPERTIES_H__3379B6FF_1B17_47AC_A9DB_2F2A27F3DE0D__INCLUDED_)
