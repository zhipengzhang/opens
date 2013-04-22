#ifndef __AGGFILEWRITER_H_INCLUDE__
#define __AGGFILEWRITER_H_INCLUDE__

#include "Common.h"
#include "AggWriter.h"
#include "PreCmptException.h"

namespace PreCmpt{

class AggFileWriter:public AggWriter
{
protected:
	string cubeDir;                             ///<存放目录
	string partitionNum;                        ///<分区号

	FILE* numPerLayerHandle;                 
	FILE* hdrHandle;
	FILE** dimHandles;
	FILE** msrHandles;
	FILE** mapHandles;

	inline void obtainNumPerLayerHandle();
	inline void obtainHdrHandle();
	inline void obtainMapHandle();
	inline void obtainDimHandle();
	inline void obtainMsrHandle();

	inline void releaseNumPerLayerHandle();
	inline void releaseHdrHandle();
	inline void releaseMapHandle();
	inline void releaseDimHandle();
	inline void releaseMsrHandle();

public:
	explicit AggFileWriter( string t_cubeDir, int t_dimsNum, int t_msrsNum );
	explicit AggFileWriter( string t_cubeDir, int t_dimsNum, int t_msrsNum, string t_partitionNum );

	virtual ~AggFileWriter();

	virtual void insertMapData( string& mapData, int dim );
	virtual void insertHdrData( vector<string>& hdrData );
	virtual void insertUclData( int* dimData, double* msrData, int layer );
	virtual void insertNumPerLayer( vector<int>& aggNumPerLayer );
};

}
#endif