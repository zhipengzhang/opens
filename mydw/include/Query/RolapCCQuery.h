#ifndef __CCROLAPQUERY_H_INCLUDE__
#define __CCROLAPQUERY_H_INCLUDE__

#include "Common.h"
#include "AggDBReader.h"
#include "AggReader.h"
#include "MolapQueryComputationBase.h"
#include "QueryResult.h"

#include "./MdxParser/ParsedMDX.h"

#include "QueryCmptException.h"

#include "./DWSchemac/XSchemas.h"
#include "./DWSchemac/DataSource.h"
#include "./DWSchemac/XSchema.h"


using namespace dwschemac;
using namespace std;
class ParsedMDX;

namespace QueryComputationMethods
{

class RolapCCQuery: public MolapQueryComputationBase
{
private:
	inline void pointQuery( int *qry );

protected:
	void setCacheUpper(vector< string > upper);		//设置某个查询缓存的上界
	vector<string> getCacheUpper() const;			//获得某个查询缓存的上界
	
public:
	explicit RolapCCQuery(ParsedMDX *parsedMDX );
	explicit RolapCCQuery(ParsedMDX *parsedMDX, string partitionNum );
	virtual ~RolapCCQuery();
	
	CellSet query();
	vector<Cell> Cellquery();

};

};

#endif