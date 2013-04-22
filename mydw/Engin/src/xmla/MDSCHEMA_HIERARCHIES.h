// MDSCHEMA_HIERARCHIES.h: interface for the MDSCHEMA_HIERARCHIES class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDSCHEMA_HIERARCHIES_H__8D2DB045_2A63_4EE7_8BD3_F45F494F79CC__INCLUDED_)
#define AFX_MDSCHEMA_HIERARCHIES_H__8D2DB045_2A63_4EE7_8BD3_F45F494F79CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Rowset.h"
#include <DWSchemac/XSchemas.h>
#include <DWSchemac/XSchema.h>
#include <DWSchemac/Dimension.h>
#include <DWSchemac/XCube.h>
#include <DWSchemac/Hierarchy.h>
#include <DWSchemac/Member.h>
#include <DWSchemac/Measure.h>

using namespace dwschemac;

class MDSCHEMA_HIERARCHIES :public Rowset
{
public:
	MDSCHEMA_HIERARCHIES(Properties properties);
	virtual ~MDSCHEMA_HIERARCHIES();

	void serialize(SoapSerializer * SoapSer);
	bool processValue(Restrictions restrictions,Properties properties);
	void processProperties(Properties properties);

private:

	vector<Hierarchy*> getRestrictHierarchy(Restrictions &restrictions);
	Row getRow(Hierarchy* hierarchy);
	Row getRowM(MeasureList measureList);
};

#endif // !defined(AFX_MDSCHEMA_HIERARCHIES_H__8D2DB045_2A63_4EE7_8BD3_F45F494F79CC__INCLUDED_)
