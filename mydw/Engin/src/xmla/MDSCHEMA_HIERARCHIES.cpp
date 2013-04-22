// MDSCHEMA_HIERARCHIES.cpp: implementation of the MDSCHEMA_HIERARCHIES class.
//
//////////////////////////////////////////////////////////////////////

#include "MDSCHEMA_HIERARCHIES.h"

#define CATALOG_NAME "CATALOG_NAME"
#define CUBE_NAME "CUBE_NAME"
#define DIMENSION_UNIQUE_NAME "DIMENSION_UNIQUE_NAME"
#define HIERARCHY_UNIQUE_NAME "HIERARCHY_UNIQUE_NAME"
#define HIERARCHY_CAPTION "HIERARCHY_CAPTION"
#define DIMENSION_TYPE "DIMENSION_TYPE"
#define HIERARCHY_CARDINALITY "HIERARCHY_CARDINALITY"
#define DEFAULT_MEMBER "DEFAULT_MEMBER"
#define ALL_MEMBER "ALL_MEMBER"
#define STRUCTURE "STRUCTURE"
#define IS_VIRTUAL "IS_VIRTUAL"
#define IS_READWRITE "IS_READWRITE"
#define DIMENSION_UNIQUE_SETTINGS "DIMENSION_UNIQUE_SETTINGS"
#define DIMENSION_IS_VISIBLE "DIMENSION_IS_VISIBLE"
#define HIERARCHY_ORDINAL "HIERARCHY_ORDINAL"
#define DIMENSION_IS_SHARED "DIMENSION_IS_SHARED"

//extern XSchemas xSchemas;
extern bool readfile(char * filename,std::string &send);

MDSCHEMA_HIERARCHIES::MDSCHEMA_HIERARCHIES(Properties properties):Rowset(properties)
{

}

MDSCHEMA_HIERARCHIES::~MDSCHEMA_HIERARCHIES()
{

}

void MDSCHEMA_HIERARCHIES::serialize(SoapSerializer * SoapSer){
	
	serializeAny(SoapSer,"schemas/hierarchy_schema.txt");
}

bool MDSCHEMA_HIERARCHIES::processValue(Restrictions restrictions,Properties properties){
	
	processProperties(properties);

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
		Row measureRow=getRowM(measures[j]);
		if(isConsistent(measureRow,restrictions))
			rows.push_back(measureRow);
	}

	
	vector<Hierarchy*> hierarchies=this->getRestrictHierarchy(restrictions);

	for(int i=0;i<hierarchies.size();i++){
		Row row=getRow(hierarchies[i]);
		if(isConsistent(row,restrictions))
			rows.push_back(row);
	}

	return true;
}


void MDSCHEMA_HIERARCHIES::processProperties(Properties properties){
	
}

vector<Hierarchy*> MDSCHEMA_HIERARCHIES::getRestrictHierarchy(Restrictions &restrictions){
	vector<Hierarchy*> hierarchies;
	string catalogn="";
	string cuben="";
	string dimensionn="";
	Restrictions::iterator catalognIt=restrictions.find(CATALOG_NAME);
	//有CATALOG_NAME约束
	if(catalognIt!= restrictions.end()){
		catalogn=catalognIt->second;
		//earse
		restrictions.erase(catalognIt);
	}
	Restrictions::iterator cubenIt=restrictions.find(CUBE_NAME);
	//有CUBE_NAME约束
	if(cubenIt!=restrictions.end()){
		cuben=cubenIt->second;
		restrictions.erase(cubenIt);
	}
	Restrictions::iterator dimensionnIt=restrictions.find(DIMENSION_UNIQUE_NAME);
	//有DIMENSION_NAME约束
	if(dimensionnIt!=restrictions.end()){
		dimensionn=dimensionnIt->second;
		restrictions.erase(dimensionnIt);
	}
 
	hierarchies=XSchemas::instance().getHierarchies(catalogn,cuben,dimensionn);
	
	return hierarchies;
 	
}
 
//根据measure封装一个Row
Row MDSCHEMA_HIERARCHIES::getRowM(MeasureList measureList){
	Row measureRow;

	measureRow.push(CATALOG_NAME,measureList[0]->getcube()->getSchema()->getName());
	measureRow.push(CUBE_NAME,measureList[0]->getcube()->getName());
	measureRow.push(DIMENSION_UNIQUE_NAME,"[Measures]");
	measureRow.push(HIERARCHY_UNIQUE_NAME,"[Measures]");
	measureRow.push(HIERARCHY_CAPTION,"Measures");
	//measure=2
	measureRow.push(DIMENSION_TYPE,"2");
	
	AxisChar m_buf[16];
	AxisSprintf(m_buf,8,"%d",measureList[0]->getcube()->getMeasureMemberCount());
	string cardinality=m_buf;
	measureRow.push(HIERARCHY_CARDINALITY,cardinality);

	measureRow.push(DEFAULT_MEMBER,"[Measures].["+measureList[0]->getcube()->getDefaultMeasure()->getName()+"]");

	measureRow.push(STRUCTURE,"0");
	measureRow.push(IS_VIRTUAL,"false");
	measureRow.push(IS_READWRITE,"false");
	measureRow.push(DIMENSION_UNIQUE_SETTINGS,"0");
	measureRow.push(DIMENSION_IS_VISIBLE,"true");
	
	AxisSprintf(m_buf,8,"%d",measureList[0]->getcube()->getDimensions().size());
	string ordinal=m_buf;
	measureRow.push(HIERARCHY_ORDINAL,ordinal);

	measureRow.push(DIMENSION_IS_SHARED,"false");
	
	return measureRow;
}

Row MDSCHEMA_HIERARCHIES::getRow(Hierarchy* hierarchy){
	Row row;

	row.push(CATALOG_NAME,hierarchy->getDimension()->getCube()->getSchema()->getName());
	row.push(CUBE_NAME,hierarchy->getDimension()->getCube()->getName());
	row.push(DIMENSION_UNIQUE_NAME,"["+hierarchy->getDimension()->getName()+"]");
	row.push(HIERARCHY_UNIQUE_NAME,"["+hierarchy->getName()+"]");
	row.push(HIERARCHY_CAPTION,hierarchy->getName());
	
	//表示该维度的类型 time=1 common=3 measure=2
	AxisChar m_buf[16];
	AxisSprintf(m_buf,8,"%d",hierarchy->getDimension()->getDimensionType());
	string dtype=m_buf;
	row.push(DIMENSION_TYPE,dtype);
	
	//表示该hierarchy的所有level的member的个数之和
	AxisSprintf(m_buf,8,"%d",hierarchy->getMemberCount());
	string cardinality=m_buf;
	row.push(HIERARCHY_CARDINALITY,cardinality);

	row.push(DEFAULT_MEMBER,"["+hierarchy->getDimension()->getName()+"].["+hierarchy->getDefaultMember().get()->getKey()+"]");
	
	if(dtype!="1")
	row.push(ALL_MEMBER,"["+hierarchy->getDimension()->getName()+"].["+hierarchy->getAllMemberName()+"]");

	row.push(STRUCTURE,"0");
	row.push(IS_VIRTUAL,"false");
	row.push(IS_READWRITE,"false");
	row.push(DIMENSION_UNIQUE_SETTINGS,"0");
	row.push(DIMENSION_IS_VISIBLE,"true");
	
	//表示该dimension顺序
	AxisSprintf(m_buf,8,"%d",hierarchy->getDimension()->getOrdinal());
	string ordinal=m_buf;
	row.push(HIERARCHY_ORDINAL,ordinal);
	
	string isShared;
	if(hierarchy->getDimension()->isSharedDimension())
		isShared="true";
	else 
		isShared="false";
	row.push(DIMENSION_IS_SHARED,isShared);

	return row;
}
