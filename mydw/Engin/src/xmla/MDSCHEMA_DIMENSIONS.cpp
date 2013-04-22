// MDSCHEMA_DIMENSIONS.cpp: implementation of the MDSCHEMA_DIMENSIONS class.
//
//////////////////////////////////////////////////////////////////////

#include "MDSCHEMA_DIMENSIONS.h"

#define CATALOG_NAME "CATALOG_NAME"
#define CUBE_NAME "CUBE_NAME"
#define DIMENSION_NAME "DIMENSION_NAME"
#define DIMENSION_UNIQUE_NAME "DIMENSION_UNIQUE_NAME"
#define DIMENSION_CAPTION "DIMENSION_CAPTION"
#define DIMENSION_ORDINAL "DIMENSION_ORDINAL"
#define DIMENSION_TYPE "DIMENSION_TYPE"
#define DIMENSION_CARDINALITY "DIMENSION_CARDINALITY"
#define DEFAULT_HIERARCHY "DEFAULT_HIERARCHY"
#define IS_VIRTUAL "IS_VIRTUAL"
#define IS_READWRITE "IS_READWRITE"
#define DIMENSION_UNIQUE_SETTINGS "DIMENSION_UNIQUE_SETTINGS"
#define DIMENSION_IS_VISIBLE "DIMENSION_IS_VISIBLE"

//extern XSchemas xSchemas;

MDSCHEMA_DIMENSIONS::MDSCHEMA_DIMENSIONS(Properties properties):Rowset(properties)
{
	
}

MDSCHEMA_DIMENSIONS::~MDSCHEMA_DIMENSIONS()
{
	
}

/*

Content:一种枚举器，用于指定结果集中返回的数据的类型。 
None：允许校验命令的结构，但不执行命令。类似于使用 Prepare 来检查语法，等等。

Schema：包含与所请求的查询相关的 XML 架构（用于指明列信息等）。

Data：仅包含所请求的数据。

SchemaData：返回架构信息和数据。
*/

void MDSCHEMA_DIMENSIONS::serialize(SoapSerializer * SoapSer){
	
	serializeAny(SoapSer,"schemas/dimension_schema.txt");	
}


bool MDSCHEMA_DIMENSIONS::processValue(Restrictions restrictions,Properties properties){
	processProperties(properties);

/*
	std::ofstream logFile("outll.txt");
	std::streambuf *outbuf = std::cout.rdbuf(logFile.rdbuf());

	for(Restrictions::iterator u=restrictions.begin();u!=restrictions.end();u++){
		cout<<u->first<<"\n";
		cout<<u->second<<"\n";
	}
    
	for(Properties::iterator w=properties.begin();w!=properties.end();w++){
		cout<<w->first<<"\n";
		cout<<w->second<<"\n";
	}
	std::cout.rdbuf(outbuf);*/


	//Measure is also a kind of dimension
	vector<MeasureList> measures;
	string catalogn="";
	string cuben="";

	//properties有指定Catalog
	if(this->Catalog!="")
		catalogn=Catalog;
	else{
		Restrictions::iterator catalognIt=restrictions.find(CATALOG_NAME);
		//有CATALOG_NAME约束
		if(catalognIt!= restrictions.end()){
			catalogn=catalognIt->second;
		}
	}
	
	Restrictions::iterator cubenIt=restrictions.find(CUBE_NAME);
	//有CUBE_NAME约束
	if(cubenIt!=restrictions.end()){
		cuben=cubenIt->second;
	}
	
	measures=XSchemas::instance().getMeasures(catalogn,cuben);
	for(int j=0;j<measures.size();j++){
		Row measureRow1=getRowM(measures[j]);
		if(isConsistent(measureRow1,restrictions))
			rows.push_back(measureRow1);
	}
	
	vector<Dimension*> dimensions=this->getRestrictDimension(restrictions,properties);
	
	for(int i=0;i<dimensions.size();i++){
		Row row=getRow(dimensions[i]);
		if(isConsistent(row,restrictions))
			rows.push_back(row);
	}
	return true;
}
 
//根据measure封装一个Row
Row MDSCHEMA_DIMENSIONS::getRowM(MeasureList measureList){
	///***********************Measure维**************************************/

	Row measureRow;
	measureRow.push(CATALOG_NAME,measureList[0]->getcube()->getSchema()->getName());
	measureRow.push(CUBE_NAME,measureList[0]->getcube()->getName());
	measureRow.push(DIMENSION_NAME,"Measures");
	measureRow.push(DIMENSION_UNIQUE_NAME,"[Measures]");
	measureRow.push(DIMENSION_CAPTION,"Measures");

	//表示该dimension顺序
	AxisChar m_buf[16];
	AxisSprintf(m_buf,8,"%d",measureList[0]->getcube()->getDimensions().size());
	string ordinal=m_buf;
	measureRow.push(DIMENSION_ORDINAL,ordinal);

	measureRow.push(DIMENSION_TYPE,"2");

	AxisSprintf(m_buf,8,"%d",measureList[0]->getcube()->getMeasureMemberCount());
	string cardinality=m_buf;
	measureRow.push(DIMENSION_CARDINALITY,cardinality);

	measureRow.push(DEFAULT_HIERARCHY,"[Measures]");

	measureRow.push(IS_VIRTUAL,"false");
	measureRow.push(IS_READWRITE,"false");
	measureRow.push(DIMENSION_UNIQUE_SETTINGS,"0");
	measureRow.push(DIMENSION_IS_VISIBLE,"true");
	
	return measureRow;
}


//根据dimension封装一个Row
Row MDSCHEMA_DIMENSIONS::getRow(Dimension* dimension){
	Row row;
	row.push(CATALOG_NAME,dimension->getCube()->getSchema()->getName());
	row.push(CUBE_NAME,dimension->getCube()->getName());
	row.push(DIMENSION_NAME,dimension->getName());
	row.push(DIMENSION_UNIQUE_NAME,"["+dimension->getName()+"]");
	row.push(DIMENSION_CAPTION,dimension->getName());

	//表示该dimension顺序
	AxisChar m_buf[16];
	AxisSprintf(m_buf,8,"%d",dimension->getOrdinal());
	string ordinal=m_buf;
	row.push(DIMENSION_ORDINAL,ordinal);
	
	//表示该维度的类型 time=1 common=3 measure=2
	AxisSprintf(m_buf,8,"%d",dimension->getDimensionType());
	string dtype=m_buf;
	row.push(DIMENSION_TYPE,dtype);
	//dimension->getDimensionType();

	//表示该维度下的默认hierarchy的所有level的member的个数之和
	AxisSprintf(m_buf,8,"%d",dimension->getDefaultHierarchy()->getMemberCount());
	string cardinality=m_buf;
	row.push(DIMENSION_CARDINALITY,cardinality);
	
	row.push(DEFAULT_HIERARCHY,"["+dimension->getDefaultHierarchy()->getName()+"]");
	///////////////////////////////////////////////////////////////////////////////////
	row.push(IS_VIRTUAL,"false");
	row.push(IS_READWRITE,"false");
	row.push(DIMENSION_UNIQUE_SETTINGS,"0");
	row.push(DIMENSION_IS_VISIBLE,"true");
	
	return row;
}

vector<Dimension*> MDSCHEMA_DIMENSIONS::getRestrictDimension(Restrictions &restrictions,Properties properties){
	vector<Dimension*> dimensions;
	string catalogn="";
	string cuben="";

	//properties有指定Catalog
	if(this->Catalog!="")
		catalogn=catalogn;
	else{
		Restrictions::iterator catalognIt=restrictions.find(CATALOG_NAME);
		//有CATALOG_NAME约束
		if(catalognIt!= restrictions.end()){
			catalogn=catalognIt->second;
			//earse
			restrictions.erase(catalognIt);
		}
	}
	
	Restrictions::iterator cubenIt=restrictions.find(CUBE_NAME);
	//有CUBE_NAME约束
	if(cubenIt!=restrictions.end()){
		cuben=cubenIt->second;
		restrictions.erase(cubenIt);
	}
	dimensions=XSchemas::instance().getDimensions(catalogn,cuben);
	
	return dimensions;
}





void MDSCHEMA_DIMENSIONS::processProperties(Properties properties){
	
}

