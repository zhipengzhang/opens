// MDSCHEMA_PROPERTIES.cpp: implementation of the MDSCHEMA_PROPERTIES class.
//
//////////////////////////////////////////////////////////////////////

#include "MDSCHEMA_PROPERTIES.h"

extern XSchemas xSchemas;
extern bool readfile(char * filename,std::string &send);


MDSCHEMA_PROPERTIES::MDSCHEMA_PROPERTIES(Properties properties):Rowset(properties)
{

}

MDSCHEMA_PROPERTIES::~MDSCHEMA_PROPERTIES()
{

}


void MDSCHEMA_PROPERTIES::serialize(SoapSerializer * SoapSer){
	serializeAny(SoapSer,"schemas/properties_schema.txt");

}

bool MDSCHEMA_PROPERTIES::processValue(Restrictions restrictions,Properties properties){
	processProperties(properties);

	//todo

	return true;
	
}

void MDSCHEMA_PROPERTIES::processProperties(Properties properties){
	//todo	

}
	

	
Row MDSCHEMA_PROPERTIES::getRow(Dimension* dimension){
	//todo
	Row row;

	return row;
}