// ResultsetBuilder.cpp: implementation of the ResultsetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "RowsetBuilder.h"


RowsetBuilder::RowsetBuilder()
{

}

RowsetBuilder::~RowsetBuilder()
{

}


	Rowset* RowsetBuilder::getRowset(DISCOVER_RequestType RequestType,Restrictions restrictions,Properties properties){
		Rowset* resultset=getRowset(RequestType,properties);
 		resultset->processValue(restrictions, properties);

		return resultset;
}

	Rowset* RowsetBuilder::getRowset(DISCOVER_RequestType RequestType,Properties properties){
	
	switch(RequestType) {
	case discover_DATASOURCES:
		return new DISCOVER_DATASOURCES(properties);
	case mdschema_DIMENSIONS:
	    return new MDSCHEMA_DIMENSIONS(properties);
	case mdschema_HIERARCHIES:
		return new MDSCHEMA_HIERARCHIES(properties);
	case mdschema_LEVELS:
		return new MDSCHEMA_LEVELS(properties);
	case mdschema_PROPERTIES:
		return new MDSCHEMA_PROPERTIES(properties);
	case mdschema_MEMBERS:
		return new MDSCHEMA_MEMBERS(properties);
		    
		break;
	default:
		return NULL;
	}

}
