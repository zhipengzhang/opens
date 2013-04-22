#ifndef __AGGWRITER_H_INCLUDE__
#define __AGGWRITER_H_INCLUDE__

#include "Common.h"
#include "PreCmptException.h"

namespace PreCmpt{

class AggWriter
{
protected:
	int dimsNum;
	int msrsNum;

public:
	AggWriter( int dimsNum, int msrsNum );
	virtual ~AggWriter();
	
	virtual void insertHdrData( vector<string>& hdrData )=0;
	virtual void insertMapData( string& mapData, int dim )=0;
	virtual void insertNumPerLayer( vector<int>& aggNumPerLayer )=0;
};

}
#endif