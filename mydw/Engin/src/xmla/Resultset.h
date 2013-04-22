// ResultSet.h: interface for the ResultSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESULTSET_H__96473C06_509B_4917_8CA7_49960A6DCD11__INCLUDED_)
#define AFX_RESULTSET_H__96473C06_509B_4917_8CA7_49960A6DCD11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <MEMORY>
#include "../soap/SoapSerializer.h"
#include "../xmla/Rowset.h"

#include <DWSchemac/XSchemas.h>
#include <DWSchemac/XSchema.h>
#include <DWSchemac/Dimension.h>
#include <DWSchemac/XCube.h>
#include <DWSchemac/Hierarchy.h>
#include <DWSchemac/Measure.h>
#include <DWSchemac/Level.h>
#include <Query/Common.h>
#include <Query/QueryComputationBase.h>
#include <Query/CCInvertListQuery.h>
#include <Query/MolpQueryComputationBase.h>
#include <Query/QueryResult.h>
#include <Query/QueryComputation.h>
#include <MdxParser/ParsedMDX.h>
using namespace dwschemac;
using namespace QueryComputationMethods;
	

typedef string Command;

class ResultSet  
{
public:
	
	ResultSet(std::string MDXString,Properties props,std::string cubeDir);
	virtual ~ResultSet();
	void serialize(SoapSerializer * SoapSer);
	

  
private:
	void serializeSchema(SoapSerializer * SoapSer);
	void serializeOlapInfo(SoapSerializer * SoapSer);
	void serializeAxesTF(SoapSerializer * SoapSer);
	void serializeCellData(SoapSerializer * SoapSer);

	string getUName(const QueryMember *member);
	string getLName(const QueryMember *member);
	string getLNum(const QueryMember *member);
	string getDisplayInfo(const QueryMember *member);

	string getValue(const Cell cell);
	CellSet cellset;
	ParsedMDX * parsedMDX;
	auto_ptr<QueryComputation> queryCom;
 
//	Properties
	string AxisFormat;
	string BeginRange;
	string EndRange;
	string Catalog;
	string Content;
	string DataSourceInfo;
	string Format;
	string LocaleIdentifier;
	string Password;
	string Timeout;
	string UserName;

};

#endif // !defined(AFX_RESULTSET_H__96473C06_509B_4917_8CA7_49960A6DCD11__INCLUDED_)
