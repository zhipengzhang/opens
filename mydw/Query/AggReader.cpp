#include "./Query/AggReader.h"

namespace QueryComputationMethods{

AggReader::AggReader()
:dimsNum(0),msrsNum(0),mapTables(NULL)
{
}

AggReader::~AggReader()
{
}

int AggReader::getDimsNum()
{
	return dimsNum;
}

int AggReader::getMsrsNum()
{
	return msrsNum;
}

MapTable& AggReader::getHdrData()
{
	return hdrTable;
}

MapTable*& AggReader::getMapTable()
{
	return mapTables;
}

vector<int>& AggReader::getNumPerLayer()
{
	return aggNumPerLayer;
}

vector< vector<string> >& AggReader::getMapsVals()
{
	return mapsVals;
}

};