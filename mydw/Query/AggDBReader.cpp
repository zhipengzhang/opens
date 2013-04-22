#include "./Query/AggDBReader.h"


namespace QueryComputationMethods
{

AggDBReader::AggDBReader( XODBCDatabase* pDB, string schemaName_t, string cubeName_t )
:pDB(pDB),schemaName(schemaName_t),cubeName(cubeName_t),partitionNum("")
{
	cout<<"INFO: class AggDBReader--Constructor"<<endl;
	
	DWConfiguration &dwConfig = DWConfiguration::instance();
	dwConfig.addConfig("System","../../DWServer/conf/system-config.xml");
	DWConfig *config = NULL;	
	if ( !(config = dwConfig.getConfig("System")) )
	{
		string errorMessage = "open system-config.xml failed";
		throw QueryCmptException(errorMessage);
	}
	
	string qryTimeStr = "";
	if ( (qryTimeStr = config->getValue("ConfigurationSettings.QryQueryTime")) == "" )
	{
		string errorMessage = "get ConfigurationSettings.QryQueryTime value failed";
		throw QueryCmptException(errorMessage);
	}

	pDB->SetQueryTimeout(atoi(qryTimeStr.c_str()));

	loadHdrData(); 
	loadMapData();
	loadNumPerLayer();	
}


AggDBReader::AggDBReader( XODBCDatabase* pDB, string schemaName_t, string cubeName_t, string partitionNum_t )
:pDB(pDB),schemaName(schemaName_t),cubeName(cubeName_t),partitionNum(partitionNum_t)
{
	cout<<"INFO: class AggDBReader--Constructor Partition"<<endl;
	
	DWConfiguration &dwConfig = DWConfiguration::instance();
	dwConfig.addConfig("System","../../DWServer/conf/system-config.xml");
	DWConfig *config = NULL;	
	if ( !(config = dwConfig.getConfig("System")) )
	{
		string errorMessage = "open system-config.xml failed";
		throw QueryCmptException(errorMessage);
	}
	
	string qryTimeStr = "";
	if ( (qryTimeStr = config->getValue("ConfigurationSettings.QryQueryTime")) == "" )
	{
		string errorMessage = "get ConfigurationSettings.QryQueryTime value failed";
		throw QueryCmptException(errorMessage);
	}

	pDB->SetQueryTimeout(atoi(qryTimeStr.c_str()));

	loadHdrData();
	loadMapData();
	loadNumPerLayer();
}


AggDBReader::~AggDBReader()
{
	if ( mapTables )
	{
		delete[] mapTables;
	}	
	if ( pDB )
	{
		pDB->Close();
		delete pDB;
	}
}

bool AggDBReader::loadNumPerLayer()
{
	string loadNumPerLayerSQL = "";
	if ( "" == partitionNum )
		loadNumPerLayerSQL = "select * from agg"+schemaName+"_"+cubeName+"_numperlayer;";
	else
		loadNumPerLayerSQL = "select * from agg"+schemaName+"_"+cubeName+"_"+partitionNum+"_numperlayer;";
	
	try
	{
		XODBCRecordset XRS(pDB);
		XRS.Open( XODBCRecordset::forwardOnly, toLower(loadNumPerLayerSQL) );
		for ( int i = 0; i < XRS.GetFieldCount(); ++i )
		{
			string fieldValue;
			XRS.GetFieldValue(i, fieldValue);
			aggNumPerLayer.push_back(atoi(fieldValue.c_str()));
		}
		XRS.Close();	
	}
	catch (XODBCException* e)
	{
		XODBCError error;
		e->GetError(error);
		cout<<"Error: errorMessage--"<<error.GetErrorText()<<endl;
		cout<<"Error: errorID--"<<error.GetState()<<endl;
		string errorMessage = "class AggDBReader--ExecuteSQL "+loadNumPerLayerSQL+" failed";
		throw QueryCmptException(errorMessage);
	}

	return true;

}

bool AggDBReader::loadHdrData()
{
	int i = 0;
	string loadHdrSQL = "";
	if ( partitionNum == "" )
		loadHdrSQL = "select * from agg"+schemaName+"_"+cubeName+"_hdr;";
	else
		loadHdrSQL = "select * from agg"+schemaName+"_"+cubeName+"_"+partitionNum+"_hdr;";
	
	try
	{
		XODBCRecordset XRS( pDB );
		XRS.Open( XODBCRecordset::forwardOnly, toLower(loadHdrSQL) );
	
		for ( i = 0; i < XRS.GetFieldCount(); ++i )
		{
			string fieldValue;
			XRS.GetFieldValue(i, fieldValue);
			hdrTable.insert( pair<string, int>(fieldValue, i) );
			if ( fieldValue.find("Measures.") != string::npos )
				msrsNum++;
			else
				dimsNum++;

		}
		XRS.Close();
	}
	catch (XODBCException* e)
	{
		XODBCError error;
		e->GetError(error);
		cout<<"Error: errorMessage--"<<error.GetErrorText()<<endl;
		cout<<"Error: errorID--"<<error.GetState()<<endl;
		string errorMessage = "class AggDBReader--ExecuteSQL "+loadHdrSQL+" failed";
		throw QueryCmptException(errorMessage);
	}
	
	return true;
}

bool AggDBReader::loadMapData()
{
	vector<string> temp;
	string selectSQL = "";
	if ( partitionNum == "" )
		selectSQL = "select * from agg"+schemaName+"_"+cubeName+"_map";
	else
		selectSQL = "select * from agg"+schemaName+"_"+cubeName+"_"+partitionNum+"_map";
	
	string loadMapSQL = "";

	string dimValue = "";
	string dimPos = "";

	mapTables = new map<string,int>[dimsNum];
	try
	{
		XODBCRecordset XRS( pDB );
		for ( int i = 0; i < dimsNum; ++i )
		{
			loadMapSQL = selectSQL + itos(i+1) + " order by dimPos;";
			XRS.Open( XODBCRecordset::forwardOnly, toLower(loadMapSQL) );
			if ( !XRS.IsOpen() )
			{
				cout<<"Error:load map data failed !"<<endl;
				exit(-1);
			}
		
			mapsVals.push_back(temp);

			while ( !XRS.IsEOF() )
			{
				XRS.GetFieldValue(0, dimValue);
				XRS.GetFieldValue(1, dimPos);
				mapTables[i].insert( pair<string, int>( dimValue, atoi(dimPos.c_str()) ) );
				mapsVals[i].push_back(dimValue);
				XRS.MoveNext();
			}
			XRS.Close();
		}
	}
	catch (XODBCException* e)
	{
		XODBCError error;
		e->GetError(error);
		cout<<"Error: errorMessage--"<<error.GetErrorText()<<endl;
		cout<<"Error: errorID--"<<error.GetState()<<endl;
		string errorMessage = "class AggDBReader--ExecuteSQL "+loadMapSQL+" failed";
		throw QueryCmptException(errorMessage);	
	}		
	return true;
}

bool AggDBReader::lookupPoint( int* queryPoint, vector<int>& dimsVal, vector<double>& msrsVal )
{
	int i = 0;
	int enterLayer = 0;
	vector< pair<int,int> > conditionItems;
	for ( i = 0; i < dimsNum; ++i )
	{
		if ( queryPoint[i] != 0 )
		{
			++enterLayer;
			conditionItems.push_back( pair<int,int>( i+1, queryPoint[i] ) );
		}
	}

	string selectSQL = "";
	if ( partitionNum == "" )
		selectSQL = "select top 1 * from agg"+schemaName+"_"+cubeName+"_ucl";
	else
		selectSQL = "select top 1 * from agg"+schemaName+"_"+cubeName+"_"+partitionNum+"_ucl";

	string whereSQL = " where ";
	for ( i = 0; i < enterLayer-1; i++ )
	{
		whereSQL += string("dim") + itos(conditionItems[i].first) + "= '" +itos(conditionItems[i].second) + "' and ";
	}
	whereSQL += string("dim") + itos(conditionItems[enterLayer-1].first) + "= '" +itos(conditionItems[enterLayer-1].second) + "';";

	string lookupUclSQL = "";

	try
	{
		XODBCRecordset XRS(pDB);
		XRS.SetMaxRecordCount(1);
		while( enterLayer <= dimsNum )
		{
			lookupUclSQL = selectSQL + itos(enterLayer) + whereSQL;
		
			XRS.Open( XODBCRecordset::forwardOnly, toLower(lookupUclSQL) );
			if ( !XRS.IsOpen() )
			{
				cout<<"Error:look up ucl execute failed !"<<endl;
			}

			if ( XRS.IsEOF() )
			{
				lookupUclSQL = "";
				++enterLayer;
			}
			else
			{
				string fieldValue = "";
				for ( i = 0; i < XRS.GetFieldCount(); ++i )
				{
					XRS.GetFieldValue(i, fieldValue);
					if ( i < dimsNum )
					{
						dimsVal.push_back( atoi( fieldValue.c_str() ) );
					}
					else
					{
						msrsVal.push_back( atof( fieldValue.c_str() ) );
					}
				}

				XRS.Close();
				return true;
			}

			XRS.Close();
		}
	}
	catch (XODBCException* e)
	{
		XODBCError error;
		e->GetError(error);
		cout<<"Error: errorMessage--"<<error.GetErrorText()<<endl;
		cout<<"Error: errorID--"<<error.GetState()<<endl;
		string errorMessage = "class AggDBReader--ExecuteSQL "+lookupUclSQL+" failed";
		throw QueryCmptException(errorMessage);
	}
	
	return false;
}

};