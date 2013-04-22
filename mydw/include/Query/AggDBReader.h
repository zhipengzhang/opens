#ifndef __CUBINGDBREADER_H_INCLUDE__
#define __CUBINGDBREADER_H_INCLUDE__

#include "AggReader.h"
#include "Common.h"
#include "xodbc/XODBCDatabase.h"
#include "xodbc/XODBCRecordset.h"

#include "./dwconfig/DWConfig.h"
#include "./dwconfig/DWConfiguration.h"
#include "./dwconfig/DWElement.h"

#include "QueryCmptException.h"


using namespace xodbc;

namespace QueryComputationMethods
{

class AggDBReader:public AggReader
{
private:
	XODBCDatabase* pDB;
	XODBCRecordset* XRSforLookUp;
	string schemaName;
	string cubeName;
	string partitionNum;

	bool loadNumPerLayer();
	bool loadHdrData();
	bool loadMapData();
public:
	explicit AggDBReader( XODBCDatabase* pDB, string schemaName_t, string cubeName_t );
	explicit AggDBReader( XODBCDatabase* pDB, string schemaName_t, string cubeName_t, string partitionNum_t );
	virtual ~AggDBReader();

	bool lookupPoint( int* queryPoint, vector<int>& dimsVal, vector<double>& msrsVal );
};

};
#endif
