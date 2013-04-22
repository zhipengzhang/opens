/*============================================================================
  File:    AggFileReader.cpp

  Summary: The implement of reading and writing  upper setdata

  Copyright(c) 2007 by DBNC Lab, South China University of Technology, Guangzhou, Guangdong, P.R.C. 

------------------------------------------------------------------------------
  Modification history:
  2007.01.31 Version 1.0 by Yuhong Xiao
============================================================================*/

#include "./Query/AggFileReader.h"

namespace QueryComputationMethods
{

AggFileReader::AggFileReader( string cubeDir )
:cubeDir(cubeDir)
{
	cout<<"INFO: class AggFileReader--Constructor"<<endl;

	loadHdrData();
	loadMapData();
	loadNumPerLayer();
}

AggFileReader::~AggFileReader()
{
	cout<<"INFO: class AggFileReader--Destructor"<<endl;
	delete []mapTables;
}

string AggFileReader::getCubeDir()
{
	return cubeDir;
}

//加载头文件
bool AggFileReader::loadHdrData()
{
	string fileName = cubeDir + "/hdr.txt";
	
	int k = 0;
	ifstream infile(fileName.c_str());
	if(!infile)
	{
		string errorMessage = "open " + fileName + " failed";
		throw QueryCmptException(errorMessage);
	}

	string line = "";
	getline(infile,line,'\n');
	string::size_type u = 0;
	string::size_type d = 0;
	line.append(",");
	while( d != line.length()-1)
	{
		d = line.find_first_of(',',u);
		hdrTable.insert( pair<string,int>( line.substr(u,d-u), k++ ) );
		cout<<line.substr(u,d-u)<<endl;
		if ( line.substr(u,d-u).find( "Measures." ) != string::npos )
		{
			msrsNum++;
		}	
		else
		{
			dimsNum++;
		}
		u = d+1;
	}
	infile.close();

	return true;
}

bool AggFileReader::loadNumPerLayer()
{
	string aggRecsNumPerLayer = cubeDir + "/aggsNumPerLayer.dat"; 
	
	FILE* filehandle = NULL;
	if ( !(filehandle = fopen( aggRecsNumPerLayer.c_str(),"rb")) )
	{
		string errorMessage = "open " + aggRecsNumPerLayer + " failed";
		throw QueryCmptException(errorMessage);
	}
	int* aggRecsNum = new int[dimsNum+1];
	fread( aggRecsNum,sizeof(int),dimsNum+1,filehandle);
	
	for ( int i = 0; i < dimsNum+1; ++i )
	{
		aggNumPerLayer.push_back(aggRecsNum[i]);
	}
	delete[] aggRecsNum;

	fclose(filehandle);

	return true;
}


void AggFileReader::loadAggData( int layer, int *&dimData, double *&msrData )
{
	string aggDimPath = cubeDir + "/aggDimData" + itos(layer) + ".dat";
	string aggMsrPath = cubeDir + "/aggMsrData" + itos(layer) + ".dat";
	FILE* df[2];
	if ( !(df[0] = fopen( aggDimPath.c_str(), "rb" )) )
	{
		string errorMessage = "open "+aggDimPath+" failed";
		throw QueryCmptException(errorMessage);
	}
	if ( !(df[1] = fopen( aggMsrPath.c_str(), "rb" )) )
	{
		string errorMessage = "open "+aggMsrPath+" failed";
		throw QueryCmptException(errorMessage);
	}

	dimData = new int [aggNumPerLayer[layer]*dimsNum];
	msrData = new double [aggNumPerLayer[layer]*msrsNum];
	fread( dimData, sizeof(int), aggNumPerLayer[layer]*dimsNum, df[0]);
	fread( msrData, sizeof(double), aggNumPerLayer[layer]*msrsNum, df[1]);
	
	fclose(df[0]);
	fclose(df[1]);

}


bool AggFileReader::loadMapData()
{
	int i = 0;
	int j = 0;
	mapsVals.resize(dimsNum);
	vector<string> temp;
	mapTables = new MapTable[dimsNum];
	for ( i = 0; i < dimsNum; ++i )
	{
		j = 0;
		mapsVals.push_back(temp);
		string filePath = cubeDir + "/map" + itos(i) + ".txt";
		ifstream infile(filePath.c_str());
		if(!infile)
		{
			string errorMessage = "open "+filePath+" failed";
			throw QueryCmptException(errorMessage);
		}

		string line = "";
		while(getline(infile,line,'\n'))
		{
			mapsVals[i].push_back(line);
			mapTables[i].insert( pair<string,int>( line, ++j ) );
		}
		infile.close();
	}

	return true;

}

};
