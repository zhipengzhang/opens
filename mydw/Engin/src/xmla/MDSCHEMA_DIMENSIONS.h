// MDSCHEMA_DIMENSIONS.h: interface for the MDSCHEMA_DIMENSIONS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDSCHEMA_DIMENSIONS_H__1593039E_29EF_40B4_A503_2488B97F1A65__INCLUDED_)
#define AFX_MDSCHEMA_DIMENSIONS_H__1593039E_29EF_40B4_A503_2488B97F1A65__INCLUDED_

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
#include <FSTREAM>
using namespace dwschemac;

class MDSCHEMA_DIMENSIONS:public Rowset
{
public:
	MDSCHEMA_DIMENSIONS(Properties properties);
	virtual ~MDSCHEMA_DIMENSIONS();
	void serialize(SoapSerializer * SoapSer);
	bool processValue(Restrictions restrictions,Properties properties);
	void processProperties(Properties properties);
	
private:
	vector<Dimension*> getRestrictDimension(Restrictions &restrictions,Properties properties);
	Row getRow(Dimension* dimension);
	Row getRowM(MeasureList measureList);

};

#endif // !defined(AFX_MDSCHEMA_DIMENSIONS_H__1593039E_29EF_40B4_A503_2488B97F1A65__INCLUDED_)
