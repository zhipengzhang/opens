
#ifndef __CUBINGFILEREADER_H_INCLUDE__
#define __CUBINGFILEREADER_H_INCLUDE__

#include "Common.h"
#include "AggReader.h"
#include "QueryCmptException.h"

namespace QueryComputationMethods
{

class AggFileReader:public AggReader
{
private:
	string cubeDir;                               

	bool loadNumPerLayer();
	bool loadHdrData();
	bool loadMapData();
public:
	explicit AggFileReader(string cubeDir);
	virtual ~AggFileReader();

	string getCubeDir();

	void loadAggData( int layer, int *&dimData, double *&msrData );
}; 

};
#endif
