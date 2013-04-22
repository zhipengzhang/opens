#ifndef __CUBINGREADER_H_INCLUDE__
#define __CUBINGREADER_H_INCLUDE__

#include "Common.h"

#include "QueryCmptException.h"

namespace QueryComputationMethods{

typedef map< string, int > MapTable;

class AggReader
{
protected:
	int dimsNum;
	int msrsNum;
	MapTable hdrTable;
	MapTable* mapTables;
	vector<int> aggNumPerLayer;
	vector< vector<string> > mapsVals;

public:
	AggReader();
	virtual ~AggReader();

	MapTable& getHdrData();
	MapTable*& getMapTable();
	vector<int>& getNumPerLayer();
	vector< vector<string> >& getMapsVals();
	
	int getMsrsNum();
	int getDimsNum();
};

};
#endif