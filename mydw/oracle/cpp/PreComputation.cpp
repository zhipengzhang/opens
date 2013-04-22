#include "./PreComputation/PreComputation.h"


namespace PreCmpt{

extern EXECUTESTATE PreErrorNo;

extern const char* StateMessage[];

PreComputation::PreComputation()
{
}

PreComputation::~PreComputation()
{
}

string PreComputation::preCompute( string schemaName, string cubeName )
{
	try
	{
		PreErrorNo = SUCCEEDED;
		XSchema *schema = XSchemas::instance().getSchema( schemaName );
		if(!schema)
		{
			PreErrorNo = SCHEMA_CANNOT_FIND;
			string errorMessage = "Schema "+schemaName+" doesn't exist!";
			throw PreCmptException(errorMessage);
		}
		XCube* cube = schema->getCube( cubeName );
		if(!cube)
		{
			PreErrorNo = CUBE_CANNOT_FIND;
			string errorMessage = "Cube "+cubeName+" doesn't exist in Schema "+schemaName+"!";
			throw PreCmptException(errorMessage);
		}

		DWConfiguration& dwConfig = DWConfiguration::instance();
		dwConfig.addConfig("local","../../DWServer/conf/local-config.xml");	
		DWConfig *config = NULL;	
		if ( !(config = dwConfig.getConfig("local")) )
		{
			PreErrorNo = LOCAL_OPEN_FAILED;
			string errorMessage = "open system-config.xml failed";
			throw PreCmptException(errorMessage);
		}

		string algConfigPath = "Config."+schemaName+"."+cubeName+".Alg";
		string algorithmType = "";
		if ( (algorithmType = config->getValue(algConfigPath)) == "" )
		{
			PreErrorNo = LOCAL_GET_FAILED;
			string errorMessage = "get "+algConfigPath+" value failed";
			throw PreCmptException(errorMessage);
		}

		cout<<"INFO: PreCmpt ALG: "<<algorithmType<<endl;

		if ( "MolapMTPDPreComputation" == algorithmType )
		{
			MTPDCCPreComputation MMtpdcc(cube,MOLAP);
			MMtpdcc.excutePreCompute();
		}
		else if( "RolapMTPDPreComputation" == algorithmType )
		{
			MTPDCCPreComputation MMtpdcc(cube,ROLAP);
			MMtpdcc.excutePreCompute();
		}
		else
		{
			PreComputationBase* preBase = NULL;

			if ( "MolapCCPreComputation" == algorithmType )
			{
				preBase = new MolapCCPreComputation(cube);
			}

			else if ( "MolapFullPreComputation" == algorithmType )
				preBase = new MolapFullPreComputation(cube);
			else if ( "MolapMTPreComputation" == algorithmType )
				preBase = new MolapMTCCPreComputation(cube);
			else if ( "RolapCCPreComputation" == algorithmType )
				preBase = new RolapCCPreComputation(cube);

			preBase->excutePreCompute();

			delete preBase;
		}	

	}
	catch ( PreCmptException e)
	{
		cout<<"Error: "<<e.GetError()<<endl;
	}

	return StateMessage[PreErrorNo];
}

};