#include "./PreComputation/AggFileWriter.h"

namespace PreCmpt{

extern EXECUTESTATE PreErrorNo;

AggFileWriter::AggFileWriter( string t_cubeDir, int t_dimsNum, int t_msrsNum )
:AggWriter(t_dimsNum,t_msrsNum),cubeDir(t_cubeDir)
{
	cout<<"INFO: class AggFileWriter--Constructor"<<endl;
	
	assert( cubeDir != "" );

	mkdir( cubeDir.c_str() );	

	obtainHdrHandle();
	obtainMapHandle();
}

AggFileWriter::AggFileWriter( string t_cubeDir, int t_dimsNum, int t_msrsNum, string t_partitionNum )
:AggWriter(t_dimsNum,t_msrsNum),cubeDir(t_cubeDir),partitionNum(t_partitionNum)
{
	cout<<"INFO: class AggFileWriter--Constructor partition"<<endl;

	assert( cubeDir != "" && partitionNum != "" );
	
	//create parent directory
	mkdir( cubeDir.c_str() );
	
	//create partition directory
	cubeDir += string("/")+partitionNum;
	mkdir( cubeDir.c_str() );		

	obtainHdrHandle();
	obtainMapHandle();
}


AggFileWriter::~AggFileWriter()
{
	cout<<"INFO: class AggFileWriter--Destructor"<<endl;

	releaseHdrHandle();
	releaseMapHandle();
}

void AggFileWriter::obtainDimHandle()
{
	cout<<"INFO: class AggFileWriter--obtainDimHandle"<<endl;

	dimHandles = new FILE* [dimsNum+1];
	for ( int i = 0; i < dimsNum+1; ++i )
	{
		string filename = cubeDir + "/aggDimData" + itos(i) + ".dat";

		if ( !(dimHandles[i] = fopen( filename.c_str(), "wb" )) )
		{
			PreErrorNo = FILE_OPER_FAILED;
			string errorMessage = "Open "+filename+" failed";
			throw PreCmptException(errorMessage);
		}
	}	
}

void AggFileWriter::obtainMsrHandle()
{
	cout<<"INFO: class AggFileWriter--obtainMsrHandle"<<endl;

	msrHandles = new FILE* [dimsNum+1];
	for ( int i = 0; i < dimsNum+1; ++i )
	{
		string filename = cubeDir + "/aggMsrData" + itos(i) + ".dat";
		
		if ( !(msrHandles[i]=fopen(filename.c_str(),"wb")) )
		{
			PreErrorNo = FILE_OPER_FAILED;
			string errorMessage = "Open "+filename+" failed";
			throw PreCmptException(errorMessage);
		}
	}
}

void AggFileWriter::obtainHdrHandle()
{
	cout<<"INFO: class AggFileWriter--obtainHdrHandle"<<endl;

	string filename = cubeDir + "/hdr.txt";
	if ( !( hdrHandle=fopen(filename.c_str(),"w") ) )
	{
		PreErrorNo = FILE_OPER_FAILED;
		string errorMessage = "Open "+filename+" failed";
		throw PreCmptException(errorMessage);
	}
}

void AggFileWriter::obtainMapHandle()
{
	cout<<"INFO: class AggFileWriter--obtainMapHandle"<<endl;

	mapHandles = new FILE* [dimsNum];
	for ( int i = 0; i < dimsNum; ++i )
	{
		string filename = cubeDir + "/map" + itos(i) + ".txt";
		if ( !( mapHandles[i]=fopen(filename.c_str(), "w") ) )
		{
			PreErrorNo = FILE_OPER_FAILED;
			string errorMessage = "Open "+filename+" failed";
			throw PreCmptException(errorMessage);
		}
	}
}

void AggFileWriter::obtainNumPerLayerHandle()
{
	cout<<"INFO: class AggFileWriter--obtainNumPerLayerHandle"<<endl;

	string filename = cubeDir + "/aggNumPerLayer.dat";
	if ( !(numPerLayerHandle=fopen(filename.c_str(), "wb")) )
	{	
		PreErrorNo = FILE_OPER_FAILED;
		string errorMessage = "Open "+filename+" failed";
		throw PreCmptException(errorMessage);
	}	
}

void AggFileWriter::releaseDimHandle()
{
	cout<<"INFO: class AggFileWriter--releaseDimHandle"<<endl;

	for ( int i = 0; i < dimsNum+1; ++i )
		fclose(dimHandles[i]);
	delete[] dimHandles;
}

void AggFileWriter::releaseHdrHandle()
{
	cout<<"INFO: class AggFileWriter--releaseHdrHandle"<<endl;

	fclose(hdrHandle);
}

void AggFileWriter::releaseMapHandle()
{
	cout<<"INFO: class AggFileWriter--releaseMapHandle"<<endl;

	for ( int i = 0; i < dimsNum; ++i )
		fclose(mapHandles[i]);
	delete[] mapHandles;
}

void AggFileWriter::releaseMsrHandle()
{
	cout<<"INFO: class AggFileWriter--releaseMsrHandle"<<endl;

	for ( int i = 0; i < dimsNum + 1; ++i )
		fclose( msrHandles[i] );
	delete[] msrHandles;
}

void AggFileWriter::releaseNumPerLayerHandle()
{
	cout<<"INFO: class AggFileWriter--releaseNumPerLayerHandle"<<endl;

	fclose( numPerLayerHandle );
}

void AggFileWriter::insertHdrData( vector<string>& hdrData )
{
//	cout<<"INFO: class AggFileWriter--insertHdrData"<<endl;

	assert( hdrData.size() > 0 );

	string hdrDataStr = "";
	for ( int i = 0; i < hdrData.size(); i++ )
	{
		hdrDataStr += hdrData[i] + ",";
	}
	hdrDataStr = hdrDataStr.substr(0,hdrDataStr.length()-1);
	if ( fwrite( hdrDataStr.c_str(),strlen(hdrDataStr.c_str()),1,hdrHandle) != 1 )
	{
		PreErrorNo = FILE_OPER_FAILED;
		string errorMessage = "writer hdr data error";
		throw PreCmptException(errorMessage);
	}

}

void AggFileWriter::insertMapData( string& mapData, int dim )
{

	assert( dim >= 0 && dim < dimsNum );
	assert( mapData != "" );

	if( fwrite( mapData.c_str(),strlen(mapData.c_str()),1,mapHandles[dim] ) != 1 )
	{	
		PreErrorNo = FILE_OPER_FAILED;
		string errorMessage = "write map data error";
		throw PreCmptException(errorMessage);
	}

}

void AggFileWriter::insertUclData( int* dimData, double* msrData, int layer )
{	
	assert( layer >= 0 && layer < dimsNum);
	assert( dimData && msrData );

	if( fwrite( dimData, sizeof(int)*dimsNum, 1, dimHandles[layer] ) != 1 )
	{
		PreErrorNo = FILE_OPER_FAILED;
		string errorMessage = "write dim data error";
		throw PreCmptException(errorMessage);
	}

	if( fwrite( msrData, sizeof(double)*msrsNum, 1, msrHandles[layer] ) != 1 )
	{
		PreErrorNo = FILE_OPER_FAILED;
		string errorMessage = "write msr data error";
		throw PreCmptException(errorMessage);
	}	
}

void AggFileWriter::insertNumPerLayer( vector<int>& aggNumPerLayer )
{
	cout<<"INFO: class AggFileWriter--aggNumPerLayer"<<endl;

	if ( fwrite( aggNumPerLayer.begin(),sizeof(int)*aggNumPerLayer.size(),1,numPerLayerHandle ) != 1 )
	{
		PreErrorNo = FILE_OPER_FAILED;
		string errorMessage = "write aggNumPerLayer data error";
		throw PreCmptException(errorMessage);
	}
}

}