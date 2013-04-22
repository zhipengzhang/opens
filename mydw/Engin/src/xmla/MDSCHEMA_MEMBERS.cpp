// MDSCHEMA_MEMBERS.cpp: implementation of the MDSCHEMA_MEMBERS class.
//
//////////////////////////////////////////////////////////////////////

#include "MDSCHEMA_MEMBERS.h"

#define CATALOG_NAME "CATALOG_NAME"
#define CUBE_NAME "CUBE_NAME"
#define DIMENSION_UNIQUE_NAME "DIMENSION_UNIQUE_NAME"
#define HIERARCHY_UNIQUE_NAME "HIERARCHY_UNIQUE_NAME"
#define LEVEL_UNIQUE_NAME "LEVEL_UNIQUE_NAME"
#define LEVEL_NUMBER "LEVEL_NUMBER"
#define MEMBER_ORDINAL "MEMBER_ORDINAL"
#define MEMBER_NAME "MEMBER_NAME"
#define MEMBER_UNIQUE_NAME "MEMBER_UNIQUE_NAME"
#define MEMBER_TYPE "MEMBER_TYPE"
#define MEMBER_CAPTION "MEMBER_CAPTION"
#define CHILDREN_CARDINALITY "CHILDREN_CARDINALITY"
#define PARENT_LEVEL "PARENT_LEVEL"
#define PARENT_UNIQUE_NAME "PARENT_UNIQUE_NAME"
#define PARENT_COUNT "PARENT_COUNT"
#define MEMBER_KEY "MEMBER_KEY"
#define IS_PLACEHOLDERMEMBER "IS_PLACEHOLDERMEMBER"
#define IS_DATAMEMBER "IS_DATAMEMBER"
#define EXPRESSION "EXPRESSION"

//extern XSchemas xSchemas;

MDSCHEMA_MEMBERS::MDSCHEMA_MEMBERS(Properties properties):Rowset(properties)
{

}

MDSCHEMA_MEMBERS::~MDSCHEMA_MEMBERS()
{

}

void MDSCHEMA_MEMBERS::serialize(SoapSerializer * SoapSer){

	serializeAny(SoapSer,"schemas/members_schema.txt");
}


bool MDSCHEMA_MEMBERS::processValue(Restrictions restrictions,Properties properties){
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
	
	for(int i=0;i<measures.size();i++){
		MeasureList mlist=measures[i];
		cout<<mlist.size();
		for(int j=0;j<mlist.size();j++){	
			Row measureRow=getRowM(mlist[j],j);
			if(isConsistent(measureRow,restrictions))
			rows.push_back(measureRow);
		}
	}

	vector<Member*> members=this->getRestrictMembers(restrictions);
	
	Restrictions::iterator MemberUN_It=restrictions.find(MEMBER_UNIQUE_NAME);
	Restrictions::iterator TREE_OP_It=restrictions.find("TREE_OP");
	//有MEMBER_UNIQUE_NAME约束并且有TREE_OP约束
	if(MemberUN_It!=restrictions.end()&&TREE_OP_It!=restrictions.end()){
		if(TREE_OP_It->second=="1"){
 			
			for(int a=0;a<members.size();a++){
				Row row=getRow(members[a]);
				if(isConsistent(row,restrictions)){
					vector<Member *> m_children=members[a]->getChildrenMember();
					for(int j=0;j<m_children.size();j++){
						Row row=getRow(m_children[j]);
						rows.push_back(row);
					}
					break;
				}
			}
			
			return true;
		}
		if(TREE_OP_It->second=="0"){
			for(int a=0;a<members.size();a++){
				Row row=getRow(members[a]);
				if(isConsistent(row,restrictions))
					rows.push_back(row);
			}
			return true;
		}
		else
			return true;
		return true;
	}
	
	else{	
		for(int a=0;a<members.size();a++){
			Row row=getRow(members[a]);
			if(isConsistent(row,restrictions))
				rows.push_back(row);
		}
		return true;
	}
}


void MDSCHEMA_MEMBERS::processProperties(Properties properties){
	
}

//expression measure member
/*Row MDSCHEMA_MEMBERS::getRowC(calcMember * calc,int ordinal){
	Row calcRow;
	calcRow.push(CATALOG_NAME,calc->getCube()->getSchema()->getName());
	calcRow.push(CUBE_NAME,calc->getCube()->getName());
	calcRow.push(DIMENSION_UNIQUE_NAME,"[Measures]");
	calcRow.push(HIERARCHY_UNIQUE_NAME,"[Measures]");
	calcRow.push(LEVEL_UNIQUE_NAME,"[Measures].[MeasuresLevel]");
	calcRow.push(LEVEL_NUMBER,"0");

	char m_buf[30];
	AxisSprintf(m_buf,8,"%d",ordinal);
	string ordstr=m_buf;
	calcRow.push(MEMBER_ORDINAL,ordstr);

	calcRow.push(MEMBER_NAME,calc->getName());
	calcRow.push(MEMBER_UNIQUE_NAME,"[Measures].["+calc->getName()+"]");
	
	//common member=1;all member=2;
	//common measure member=3;expression measure member=4
	calcRow.push(MEMBER_TYPE,"4");
	calcRow.push(MEMBER_CAPTION,calc->getName());
	calcRow.push(CHILDREN_CARDINALITY,"0");
	calcRow.push(PARENT_LEVEL,"0");
	calcRow.push(PARENT_COUNT,"0");
	calcRow.push(EXPRESSION,calc->getFormula());
	calcRow.push(IS_PLACEHOLDERMEMBER,"false");
	calcRow.push(IS_DATAMEMBER,"false");

	return calcRow;
}*/

//measure member
Row MDSCHEMA_MEMBERS::getRowM(Measure *measure,int ordinal)
{
	Row measureRow;
	measureRow.push(CATALOG_NAME,measure->getcube()->getSchema()->getName());
	measureRow.push(CUBE_NAME,measure->getcube()->getName());
	measureRow.push(DIMENSION_UNIQUE_NAME,"[Measures]");
	measureRow.push(HIERARCHY_UNIQUE_NAME,"[Measures]");
	measureRow.push(LEVEL_UNIQUE_NAME,"[Measures].[MeasuresLevel]");
	measureRow.push(LEVEL_NUMBER,"0");

	char m_buf[30];
	AxisSprintf(m_buf,8,"%d",ordinal);
	string ordstr=m_buf;
	measureRow.push(MEMBER_ORDINAL,ordstr);

	measureRow.push(MEMBER_NAME,measure->getName());
	measureRow.push(MEMBER_UNIQUE_NAME,"[Measures].["+measure->getName()+"]");
	
	//common member=1;all member=2;
	//common measure member=3;expression measure member=4
	measureRow.push(MEMBER_TYPE,"3");
	measureRow.push(MEMBER_CAPTION,measure->getName());
	measureRow.push(CHILDREN_CARDINALITY,"0");
	measureRow.push(PARENT_LEVEL,"0");
	measureRow.push(PARENT_COUNT,"0");
	measureRow.push(IS_PLACEHOLDERMEMBER,"false");
	measureRow.push(IS_DATAMEMBER,"false");

	return measureRow;
}

Row MDSCHEMA_MEMBERS::getRow(Member* member){
	Row row;

	row.push(CATALOG_NAME,member->getLevel()->getHierarchy()->getDimension()->getCube()->getSchema()->getName());
	row.push(CUBE_NAME,member->getLevel()->getHierarchy()->getDimension()->getCube()->getName());
	row.push(DIMENSION_UNIQUE_NAME,"["+member->getLevel()->getHierarchy()->getDimension()->getName()+"]");
	row.push(HIERARCHY_UNIQUE_NAME,"["+member->getLevel()->getHierarchy()->getName()+"]");
	row.push(LEVEL_UNIQUE_NAME,"["+member->getLevel()->getHierarchy()->getDimension()->getName()+"].["+member->getLevel()->getName()+"]");
	
	//the depth of level
	char m_buf[20];
	int levno=member->getLevel()->getDepth()-1;
	AxisSprintf(m_buf,8,"%d",levno);
	string levelno=m_buf;
	row.push(LEVEL_NUMBER,levelno);

	int ordinal=member->getOrdinal();
	AxisSprintf(m_buf,8,"%d",ordinal);
	row.push(MEMBER_ORDINAL,m_buf);
	
	row.push(MEMBER_NAME,member->getKey());

	row.push(MEMBER_UNIQUE_NAME,getMemberUName(member));

	//common member=1;all member=2;
	//common measure member=3;expression measure member=4
	//if the all members
	if(levno==0)
		row.push(MEMBER_TYPE,"2");
	else
		row.push(MEMBER_TYPE,"1");

	row.push(MEMBER_CAPTION,member->getKey());

	if(!member->getLevel()->getChildLevel())
		row.push(CHILDREN_CARDINALITY,"0");
	else{
		AxisSprintf(m_buf,8,"%d",member->getLevel()->getChildLevel()->getMemberCount());
		string cardinality=m_buf;
		row.push(CHILDREN_CARDINALITY,cardinality);
	}
	
	//if the all members,set 0
	if(levno==0)
		row.push(PARENT_LEVEL,"0");
	else{
		AxisSprintf(m_buf,8,"%d",levno-1);
		string plevno=m_buf;
		row.push(PARENT_LEVEL,plevno);
	}
	
	//not the all members
	if(levno!=0)
	row.push(PARENT_UNIQUE_NAME,getParentUName(member));

	//default
	row.push(PARENT_COUNT,"1");

	row.push(MEMBER_KEY,member->getKey());
	//default
	row.push(IS_PLACEHOLDERMEMBER,"false");
	row.push(IS_DATAMEMBER,"false");

	return row;
} 

string MDSCHEMA_MEMBERS::getMemberUName(Member *member)
{
	string uname=getParentUName(member)+".["+member->getKey()+"]";

	return uname;
}

string MDSCHEMA_MEMBERS::getParentUName(Member *member)
{
	string uname;
	Member *acor=member;
	while((acor=acor->getParent())!=NULL){
		uname=".["+acor->getKey()+"]"+uname;
	}
	uname="["+member->getLevel()->getHierarchy()->getDimension()->getName()+"]"+uname;
	return uname;
}

vector<Member*> MDSCHEMA_MEMBERS::getRestrictMembers(Restrictions &restrictions){
	vector<Member*> members;
	string catalogn="";
	string cuben="";
	string dimensionn="";
	string hien="";
	string leveln="";
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

	Restrictions::iterator levelnIt=restrictions.find(LEVEL_UNIQUE_NAME);
	//有LEVEL_UNIQUE_NAME约束
	if(levelnIt!=restrictions.end()){
		leveln=levelnIt->second;
		restrictions.erase(levelnIt);
	}
	 
	handleString(hien);
	handleString(leveln);
	members=XSchemas::instance().getMembers(catalogn,cuben,dimensionn,hien,leveln);
	
	return members;
}



