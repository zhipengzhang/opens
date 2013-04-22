// MDSCHEMA_LEVELS.h: interface for the MDSCHEMA_LEVELS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDSCHEMA_LEVELS_H__F2FA645A_66E3_49FF_BB7B_D67F7F745020__INCLUDED_)
#define AFX_MDSCHEMA_LEVELS_H__F2FA645A_66E3_49FF_BB7B_D67F7F745020__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Rowset.h"
#include <DWSchemac/XSchemas.h>
#include <DWSchemac/XSchema.h>
#include <DWSchemac/Dimension.h>
#include <DWSchemac/XCube.h>
#include <DWSchemac/Hierarchy.h>
#include <DWSchemac/Level.h>
#include <DWSchemac/Measure.h>

using namespace dwschemac;


class MDSCHEMA_LEVELS:public Rowset
{
public:
	MDSCHEMA_LEVELS(Properties properties);
	virtual ~MDSCHEMA_LEVELS();
	void serialize(SoapSerializer * SoapSer);
	bool processValue(Restrictions restrictions,Properties properties);
	void processProperties(Properties properties);
	
private:
	vector<Level*> getRestrictLevel(Restrictions &restrictions);
	Row getRowM(MeasureList measureList);
	Row getRow(Level* level);
};

#endif // !defined(AFX_MDSCHEMA_LEVELS_H__F2FA645A_66E3_49FF_BB7B_D67F7F745020__INCLUDED_)
