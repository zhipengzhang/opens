#include "MdxParser/yacc1.h" 
#include "./Query/QueryComputation.h"


namespace QueryComputationMethods{
	
QueryComputation::QueryComputation(string mdxstring_t,string schemaName_t)
{
	parsed = NULL;
	schemaName = schemaName_t;
	mdxstring = mdxstring_t;
}

QueryComputation::~QueryComputation()
{
	if (parsed)
		delete parsed;
}

void QueryComputation::initialParsedMDX()
{
	string tmpDir = "./temp";
	string filename = tmpDir + "/mdx.txt";
	
	mkdir(tmpDir.c_str());
	ofstream fwmdx( filename.c_str(), ios::out );
	if(!fwmdx)
	{
		cout<<"Error:can't open file to write mdxstring."<<endl;
		exit(-1);
	}

	fwmdx<<mdxstring<<endl;
	fwmdx.close();

	yyin = fopen(filename.c_str(), "rt");

	yyparse (); 

	ErrorSummary ();


	XSchema* schema = XSchemas::instance().getSchema( schemaName ); 

	tree->init();
	parsed = tree->getParsedMDX(schema);
	cubeName = tree->getCubeName();
	parsed->showParsedMDX();
}

CellSet QueryComputation::queryComputation( )

{	
	try
	{
		initialParsedMDX();
		DWConfiguration& dwConfig = DWConfiguration::instance();
		dwConfig.addConfig("local","../../DWServer/conf/local-config.xml");	
		DWConfig *config = NULL;	
		if ( !(config = dwConfig.getConfig("local")) )
		{
			string errorMessage = "open local-config.xml failed";
			throw QueryCmptException(errorMessage);
		}

		string algConfigPath = "Config."+schemaName+"."+cubeName+".Alg";
		string algorithmType = "";
		if ( (algorithmType = config->getValue(algConfigPath)) == "" )
		{
			string errorMessage = "get "+algConfigPath+" value failed";
			throw QueryCmptException(errorMessage);
		}	

		cout<<"INFO: ALG:"<<algorithmType<<endl;

		if( "MolapMTPDPreComputation" == algorithmType )
		{
			cout<<"INFO: MolapMTCCQuery"<<endl;
			MTCCQuery mmtcc(parsed,MOLAP);
			return mmtcc.query();
		}
		else if ( "RolapMTPDPreComputation" == algorithmType )
		{
			MTCCQuery rmtcc(parsed,ROLAP);
			return rmtcc.query();
		}
		else
		{
			MolapQueryComputationBase *queryCmpt;

			if ( "RolapCCPreComputation" == algorithmType )
				queryCmpt = new RolapCCQuery(parsed);
			else
				queryCmpt = new MolapCCInvertListQuery(parsed);

			return queryCmpt->query();
		}

	}
	catch ( QueryCmptException e )
	{
		cout<<"ERROR: "<<e.GetError()<<endl;
		return CellSet();
	}
		
}

ParsedMDX* QueryComputation::getParsedMDX()
{
	return this->parsed;
}

};