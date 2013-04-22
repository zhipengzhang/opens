#include "./PreComputation/AggDBWriter.h"


namespace PreCmpt{

extern EXECUTESTATE PreErrorNo;

AggDBWriter::AggDBWriter( XODBCDatabase* t_pDB, 
						  int t_dimsNum, 
						  int t_msrsNum, 
						  string t_schemaName, 
						  string t_cubeName,
						  string t_partitionNum )
:AggWriter(t_dimsNum, t_msrsNum),
 pDB(t_pDB),
 schemaName(t_schemaName),
 cubeName(t_cubeName),
 partitionNum(t_partitionNum)
{	
	cout<<"INFO: class AggDBWriter--Constructor Partition"<<endl;

	createUclNumPerLayerTable();
	createHdrTable();
	createMapTable();
	createUclTable();
}


AggDBWriter::AggDBWriter( XODBCDatabase* t_pDB,
						  int t_dimsNum,
						  int t_msrsNum,
						  string t_schemaName,
						  string t_cubeName )
:AggWriter(t_dimsNum, t_msrsNum),
 pDB(t_pDB),
 schemaName(t_schemaName),
 cubeName(t_cubeName),
 partitionNum("")
{
	cout<<"INFO: class AggDBWriter--Constructor"<<endl;
	
	createUclNumPerLayerTable();
	createHdrTable();
	createMapTable();
	createUclTable();
}


AggDBWriter::~AggDBWriter()
{
	if ( pDB->IsOpen() )
	{
		pDB->Close();
	}
}


void AggDBWriter::createUclNumPerLayerTable()
{
	cout<<"INFO: class AggDBWriter--createUclNumPerLayerTable"<<endl;

	if ( partitionNum == "" )
		numPerLayertbName = string("agg")+schemaName+"_"+cubeName+"_"+string("numperlayer");
	else
		numPerLayertbName = string("agg")+schemaName+"_"+cubeName+"_"+partitionNum+"_"+string("numperlayer");
	
	numPerLayertbName = toLower(numPerLayertbName);

	vector<string> attrNames;
	vector<string> attrTypes;
	for ( int i = 0; i < dimsNum+1; ++i )
	{
		string attrName = string("layer") + itos(i);
		attrNames.push_back(attrName);
		attrTypes.push_back("int");
	}
	createTable(numPerLayertbName,attrNames,attrTypes);
}

void AggDBWriter::createHdrTable()
{
	cout<<"INFO: class AggDBWriter--createHdrTable"<<endl;

	if ( partitionNum == "" )
		hdrtbName = string("agg")+schemaName+"_"+cubeName+"_"+string("hdr");
	else
		hdrtbName = string("agg")+schemaName+"_"+cubeName+"_"+partitionNum+"_"+string("hdr");
	
	hdrtbName = toLower(hdrtbName);

	vector<string> hdrFieldName;
	vector<string> hdrFieldType;
	for ( int i = 0; i < dimsNum; ++i )
	{	
		hdrFieldName.push_back( string("dim") + itos(i+1) );
		hdrFieldType.push_back( "varchar(255)" );
	}
	for ( i = 0; i < msrsNum; ++i )
	{
		hdrFieldName.push_back( string("msr") + itos(i+1) );
		hdrFieldType.push_back( "varchar(255)" );
	}

	createTable( hdrtbName, hdrFieldName, hdrFieldType );
}

void AggDBWriter::createMapTable()
{
	cout<<"INFO: class AggDBWriter--createMapTable"<<endl;

	vector<string> mapFieldName;
	vector<string> mapFieldType;
	mapFieldName.push_back( "dimValue" );
	mapFieldName.push_back( "dimPos" );
	mapFieldType.push_back( "varchar(255)" );
	mapFieldType.push_back( "int" );

	for ( int i = 0; i < dimsNum; i++ )
	{
		string mapTableName = "";
		if ( partitionNum == "" )
			mapTableName = string("agg")+schemaName+"_"+cubeName+"_"+string("map")+itos(i+1);
		else
			mapTableName = string("agg")+schemaName+"_"+cubeName+"_"+partitionNum+"_"+string("map")+itos(i+1);
			
		mapTableName = toLower(mapTableName);
		maptbNames.push_back( mapTableName );
		createTable( mapTableName, mapFieldName, mapFieldType );
	}
}

void AggDBWriter::createUclTable()
{
	cout<<"INFO: class AggDBWriter--createUclTable"<<endl;

	int i = 0;
	vector<string> uclFieldName;
	vector<string> uclFieldType;
	for ( i = 0; i < dimsNum; ++i )
	{	
		uclFieldName.push_back( string("dim") + itos(i+1) );
		uclFieldType.push_back( "varchar(20)" );
	}
	for ( i = 0; i < msrsNum; ++i )
	{
		uclFieldName.push_back( string("msr") + itos(i+1) );
		uclFieldType.push_back( "varchar(20)" );
	}

	for ( i = 0; i <= dimsNum; ++i )
	{
		string uclTableName = "";
		if ( partitionNum == "" )
			uclTableName = string("agg")+schemaName+"_"+cubeName+"_"+string("ucl")+itos(i);
		else
			uclTableName = string("agg")+schemaName+"_"+cubeName+"_"+partitionNum+"_"+string("ucl")+itos(i);
		
		uclTableName = toLower(uclTableName);
		ucltbNames.push_back(uclTableName);
		
		createTable( uclTableName, uclFieldName, uclFieldType );
	}
}

void AggDBWriter::createTable( string tableName, vector<string> attrName, vector<string> attrType )
{
	cout<<"INFO: class AggDBWriter--createTable"<<endl;

	assert( attrName.size()==attrType.size() );

	string createTableSQL = "create table " + tableName + "(\n";
	for ( int i = 0; i < attrName.size()-1; ++i )
	{
		createTableSQL += attrName[i] + " " + attrType[i] + ",\n";
	}
	createTableSQL += attrName[attrName.size()-1] + " " + attrType[attrType.size()-1] + "\n);";

	try
	{
		//添加检查表是否存在,存在则将其删除
		pDB->ExecuteSQL( createTableSQL );
	}
	catch (XODBCException* e)
	{
		XODBCError error;
		e->GetError(error);
		cout<<"Error: errorMessage--"<<error.GetErrorText()<<endl;
		cout<<"Error: errorID--"<<error.GetState()<<endl;
		string errorMessage = "class AggDBWriter--ExecuteSQL "+createTableSQL+" failed";
		PreErrorNo = DB_OPER_FAILED;
		throw PreCmptException(errorMessage);
	}	
}

void AggDBWriter::insertHdrData( vector<string>& hdrData )
{
	cout<<"INFO: class AggDBWriter--insertHdrData"<<endl;
	assert( hdrData.size()==(dimsNum+msrsNum) );

	string insertHdrSQL = "";
	insertHdrSQL = string("insert into ") + hdrtbName + " values ( ";
	for ( int i = 0; i < hdrData.size()-1; ++i )
	{
		insertHdrSQL += string("'") + hdrData[i] + "',";
	}
	insertHdrSQL += string("'") + hdrData[hdrData.size()-1] + "');";

	try
	{
		pDB->ExecuteSQL( insertHdrSQL );
	}
	catch (XODBCException* e)
	{	
		XODBCError error;
		e->GetError(error);
		cout<<"Error: errorMessage--"<<error.GetErrorText()<<endl;
		cout<<"Error: errorID--"<<error.GetState()<<endl;
		string errorMessage = "class AggDBWriter--ExecuteSQL "+insertHdrSQL+" failed";
		PreErrorNo = DB_OPER_FAILED;
		throw PreCmptException(errorMessage);
	}	
	
}

void AggDBWriter::insertMapData( string& mapStr, int dim )
{
	cout<<"INFO: class AggDBWriter--insertMapData"<<endl;

	assert( dim >= 0 && dim < dimsNum );
	assert( mapStr != "" );

	vector<string> mapData = splitString( mapStr, "\n" );
	for ( int i = 0; i < mapData.size(); ++i )
	{
		string insertMapSQL = string("insert into ") + maptbNames[dim] + " values ('"+ mapData[i] + "'," + itos(i+1) + ");";
		
		try
		{
			pDB->ExecuteSQL(insertMapSQL);
		}
		catch (XODBCException* e)
		{				
			XODBCError error;
			e->GetError(error);
			cout<<"Error: errorMessage--"<<error.GetErrorText()<<endl;
			cout<<"Error: errorID--"<<error.GetState()<<endl;
			string errorMessage = "class AggDBWriter--ExecuteSQL "+insertMapSQL+" failed";
			PreErrorNo = DB_OPER_FAILED;
			throw PreCmptException(errorMessage);
		}
	}
}

void AggDBWriter::insertUclData( int* dimData, double* msrData, int layer )
{
	assert( layer >= 0 && layer <= dimsNum );
	assert( dimData && msrData );

	int i = 0;
	char buff[20];

	string insertUclSQL = string("insert into ") + ucltbNames[layer] + " values ( ";

	for ( i = 0; i < dimsNum; ++i )
	{
		itoa(dimData[i],buff,10);
		insertUclSQL += string("'") + buff + "',";
	}
	for ( i = 0; i < msrsNum-1; ++i )
	{
		insertUclSQL += string("'") + ftos(msrData[i]) + "',";
	}
	insertUclSQL += string("'") + ftos(msrData[msrsNum-1]) + "');";
	
	try
	{
		pDB->ExecuteSQL(insertUclSQL);
	}
	catch (XODBCException* e)
	{		
		XODBCError error;
		e->GetError(error);
		cout<<"Error: errorMessage--"<<error.GetErrorText()<<endl;
		cout<<"Error: errorID--"<<error.GetState()<<endl;
		string errorMessage = "class AggDBWriter--ExecuteSQL "+insertUclSQL+" failed";		
		PreErrorNo = DB_OPER_FAILED;
		throw PreCmptException(errorMessage);
	}
}

void AggDBWriter::insertNumPerLayer( vector<int>& aggNumPerLayer )
{
	cout<<"INFO: class AggDBWriter--insertNumPerLayer"<<endl;

	assert( aggNumPerLayer.size() == dimsNum + 1 );

	string insertNumPerLayerSQL = string("insert into ") + numPerLayertbName + " values ( ";
	for ( int i = 0; i < aggNumPerLayer.size()-1; ++i )
	{
		insertNumPerLayerSQL += itos(aggNumPerLayer[i]) + ",";
	}
	insertNumPerLayerSQL += itos(aggNumPerLayer[aggNumPerLayer.size()-1]) + ");";
	
	try
	{
		pDB->ExecuteSQL(insertNumPerLayerSQL);
	}
	catch (XODBCException* e)
	{
		XODBCError error;
		e->GetError(error);
		cout<<"Error: errorMessage--"<<error.GetErrorText()<<endl;
		cout<<"Error: errorID--"<<error.GetState()<<endl;
		string errorMessage = "class AggDBWriter--ExecuteSQL "+insertNumPerLayerSQL+" failed";		
		PreErrorNo = DB_OPER_FAILED;
		throw PreCmptException(errorMessage);
	}
}

}