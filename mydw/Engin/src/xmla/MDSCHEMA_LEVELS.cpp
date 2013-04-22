// MDSCHEMA_LEVELS.cpp: implementation of the MDSCHEMA_LEVELS class.
//
//////////////////////////////////////////////////////////////////////

#include "MDSCHEMA_LEVELS.h"

#define CATALOG_NAME "CATALOG_NAME"
#define CUBE_NAME "CUBE_NAME"
#define DIMENSION_UNIQUE_NAME "DIMENSION_UNIQUE_NAME"
#define HIERARCHY_UNIQUE_NAME "HIERARCHY_UNIQUE_NAME"
#define LEVEL_NAME "LEVEL_NAME"
#define LEVEL_UNIQUE_NAME "LEVEL_UNIQUE_NAME"
#define LEVEL_CAPTION "LEVEL_CAPTION"
#define LEVEL_NUMBER "LEVEL_NUMBER"
#define LEVEL_CARDINALITY "LEVEL_CARDINALITY"
#define LEVEL_TYPE "LEVEL_TYPE"
#define CUSTOM_ROLLUP_SETTINGS "CUSTOM_ROLLUP_SETTINGS"
#define LEVEL_UNIQUE_SETTINGS "LEVEL_UNIQUE_SETTINGS"
#define LEVEL_IS_VISIBLE "LEVEL_IS_VISIBLE"
#define LEVEL_ORDERING_PROPERTY "LEVEL_ORDERING_PROPERTY"
#define LEVEL_DBTYPE "LEVEL_DBTYPE"
#define LEVEL_NAME_SQL_COLUMN_NAME "LEVEL_NAME_SQL_COLUMN_NAME"
#define LEVEL_KEY_SQL_COLUMN_NAME "LEVEL_KEY_SQL_COLUMN_NAME"
#define LEVEL_UNIQUE_NAME_SQL_COLUMN_NAME "LEVEL_UNIQUE_NAME_SQL_COLUMN_NAME"

//extern XSchemas xSchemas;


MDSCHEMA_LEVELS::MDSCHEMA_LEVELS(Properties properties):Rowset(properties)
{

}

MDSCHEMA_LEVELS::~MDSCHEMA_LEVELS()
{

}

void MDSCHEMA_LEVELS::serialize(SoapSerializer * SoapSer){

	serializeAny(SoapSer,"schemas/level_schema.txt");

}


bool MDSCHEMA_LEVELS::processValue(Restrictions restrictions,Properties properties){
	processProperties(properties);

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

	vector<Level*> levels=this->getRestrictLevel(restrictions);
	
	for(int i=0;i<levels.size();i++){
		Row row=getRow(levels[i]);
		if(isConsistent(row,restrictions))
			rows.push_back(row);
	}
	return true;
}
	
void MDSCHEMA_LEVELS::processProperties(Properties properties){

	
}
	

vector<Level*> MDSCHEMA_LEVELS::getRestrictLevel(Restrictions &restrictions){
	vector<Level*> levels;
	string catalogn="";
	string cuben="";
	string dimensionn="";
	string hien="";
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
	Restrictions::iterator hienIt=restrictions.find(HIERARCHY_UNIQUE_NAME);
	//有HIERARCHY_UNIQUE_NAME约束
	if(hienIt!=restrictions.end()){
		hien=hienIt->second;
		restrictions.erase(hienIt);
	}

	levels=XSchemas::instance().getLevels(catalogn,cuben,dimensionn,hien);
	
	return levels;
}

//Measure
Row MDSCHEMA_LEVELS::getRowM(MeasureList measureList){
	Row measureRow;
	
	measureRow.push(CATALOG_NAME,measureList[0]->getcube()->getSchema()->getName());
	measureRow.push(CUBE_NAME,measureList[0]->getcube()->getName());
	measureRow.push(DIMENSION_UNIQUE_NAME,"[Measures]");
	measureRow.push(HIERARCHY_UNIQUE_NAME,"[Measures]");
	measureRow.push(LEVEL_NAME,"MeasuresLevel");
	measureRow.push(LEVEL_UNIQUE_NAME,"[Measures].[MeasuresLevel]");
	measureRow.push(LEVEL_CAPTION,"MeasuresLevel");
	measureRow.push(LEVEL_NUMBER,"0");

	AxisChar m_buf[16];
	AxisSprintf(m_buf,8,"%d",measureList[0]->getcube()->getMeasureMemberCount());
	string cardinality=m_buf;
	measureRow.push(LEVEL_CARDINALITY,cardinality);

	measureRow.push(LEVEL_TYPE,"0");
	measureRow.push(CUSTOM_ROLLUP_SETTINGS,"0");
	measureRow.push(LEVEL_UNIQUE_SETTINGS,"0");
	measureRow.push(LEVEL_IS_VISIBLE,"true");
	measureRow.push(LEVEL_DBTYPE,"1");
	measureRow.push(LEVEL_NAME_SQL_COLUMN_NAME,"Measures:MeasuresLevel!NAME");
	measureRow.push(LEVEL_KEY_SQL_COLUMN_NAME,"Measures:MeasuresLevel!KEY");
	measureRow.push(LEVEL_UNIQUE_NAME_SQL_COLUMN_NAME,"Measures:MeasuresLevel!UNIQUE_NAME");

	return measureRow;
}
	
Row MDSCHEMA_LEVELS::getRow(Level* level){
	Row row;

	row.push(CATALOG_NAME,level->getHierarchy()->getDimension()->getCube()->getSchema()->getName());
	row.push(CUBE_NAME,level->getHierarchy()->getDimension()->getCube()->getName());
	row.push(DIMENSION_UNIQUE_NAME,"["+level->getHierarchy()->getDimension()->getName()+"]");
	row.push(HIERARCHY_UNIQUE_NAME,"["+level->getHierarchy()->getName()+"]");
	row.push(LEVEL_NAME,level->getName());
	row.push(LEVEL_UNIQUE_NAME,"["+level->getHierarchy()->getDimension()->getName()+"].["+level->getName()+"]");
	row.push(LEVEL_CAPTION,level->getName());
	 
	//表示该level在hierarchy中的层次顺序
	AxisChar m_buf[16];
	AxisSprintf(m_buf,8,"%d",level->getDepth()-1);
	string lnum=m_buf;
	row.push(LEVEL_NUMBER,lnum);

	AxisSprintf(m_buf,8,"%d",level->getMemberCount());
	string card=m_buf;
	row.push(LEVEL_CARDINALITY,card);
 
	//如果level名字为(All)，标志为1，否则为0
	if(level->isAllLevel())  
	 row.push(LEVEL_TYPE,"1");
	else
		row.push(LEVEL_TYPE,"0");

	row.push(CUSTOM_ROLLUP_SETTINGS,"0");
	row.push(LEVEL_UNIQUE_SETTINGS,"3");
	row.push(LEVEL_IS_VISIBLE,"true");
	row.push(LEVEL_ORDERING_PROPERTY,"Name");
	row.push(LEVEL_DBTYPE,"1");

	row.push(LEVEL_NAME_SQL_COLUMN_NAME,level->getHierarchy()->getName()+":"+level->getName()+"!NAME");
	row.push(LEVEL_KEY_SQL_COLUMN_NAME,level->getHierarchy()->getName()+":"+level->getName()+"!KEY");
	row.push(LEVEL_UNIQUE_NAME_SQL_COLUMN_NAME,level->getHierarchy()->getName()+":"+level->getName()+"!UNIQUE_NAME");

	return row;
	
}
