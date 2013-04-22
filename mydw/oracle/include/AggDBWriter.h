#ifndef __AGGDBWRITER_H_INCLUDE__
#define __AGGDBWRITER_H_INCLUDE__

#include "AggWriter.h"
#include "xodbc/XODBCDatabase.h"
#include "xodbc/XODBCRecordset.h"
#include "Common.h"
#include "PreCmptException.h"

using namespace xodbc;

namespace PreCmpt{

class AggDBWriter:public AggWriter
{
protected:
	XODBCDatabase* pDB;
	string hdrtbName;
	string numPerLayertbName;
	string schemaName;
	string cubeName;
	string partitionNum;

	vector<string> maptbNames;
	vector<string> ucltbNames;
	
	inline void createHdrTable();
	inline void createUclNumPerLayerTable();
	inline void createMapTable();
	inline void createUclTable();

	
	inline void createTable( string t_tableName, 
							 vector<string> t_attrName, 
							 vector<string> t_attrType );

public:
	explicit AggDBWriter( XODBCDatabase* t_pDB, 
						  int t_dimsNum, 
						  int t_msrsNum, 
						  string t_schemaName, 
						  string t_cubeName );

	explicit AggDBWriter( XODBCDatabase* t_pDB,
						  int t_dimsNum,
						  int t_msrsNum,
						  string t_schemaName,
						  string t_cubeName,
						  string t_partitionNum );

	virtual ~AggDBWriter();

	virtual void insertHdrData( vector<string>& hdrData );
	virtual void insertUclData( int* dimData, double* msrData, int layer );
	virtual void insertNumPerLayer( vector<int>& aggNumPerLayer );
	virtual void insertMapData( string& mapData, int dim );
	
};

}
#endif