// Resultset.h: interface for the Resultset class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESULTSET_H__1AE1D65D_5E03_4B2F_9D8E_6874EB947EF9__INCLUDED_)
#define AFX_RESULTSET_H__1AE1D65D_5E03_4B2F_9D8E_6874EB947EF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../soap/SoapSerializer.h"

extern bool readfile(char * filename,std::string &send);

typedef  map<std::string,std::string> Restrictions;
typedef  map<std::string,std::string> Properties;


//支持的xmla的discover的行集
typedef enum DISCOVER_RequestType_Tag
{
    discover_DATASOURCES=0,
    discover_PROPERTIES,
	discover_SCHEMA_ROWSETS,
	discover_ENUMERATORS,
	discover_KEYWORDS,
	discover_LITERALS,
	mdschema_ACTIONS,
	mdschema_CUBES,
	mdschema_DIMENSIONS,
	mdschema_HIERARCHIES,
	mdschema_LEVELS,
	mdschema_MEASURES,
	mdschema_PROPERTIES,
	mdschema_SETS,
	mdschema_MEMBERS,
	NULLorErr
} DISCOVER_RequestType;


class Row{
public:
	Row::Row(){
	}

	virtual Row::~Row(){
	}
	
	void Row::push(string key,string value){
		pair<string,string> p;
		p.first=key;
		p.second=value;
		row.push_back(p);
	}

	//该row是否符合key和value
	bool Row::contain(string key,string value){
		for(int i=0;i<row.size();i++){
			if(row[i].first==key&&row[i].second!=value)
				return false;
		}
		return true;
	}

	void Row::serialize(SoapSerializer *serializer){
		for(int i=0;i<row.size();i++){
			serializeAsElement((AxisChar*)row[i].first.c_str(),(AxisChar*)row[i].second.c_str(),serializer);
		}
	}


	vector<pair<string,string> > row;

private:
	void serializeAsElement(AxisChar* columnName,AxisChar* columnValue,SoapSerializer * SoapSer){
		SoapSer->serialize("<",columnName,">",columnValue,"</",columnName,">\r\n",NULL);
	}
};


class Rowset  
{
public:
	Rowset::Rowset(Properties properties){

		setProperties( properties);
		
	}
	virtual Rowset::~Rowset(){

	}
	
	virtual void serialize(SoapSerializer * SoapSer)=0;

/*
Content:一种枚举器，用于指定结果集中返回的数据的类型。 
None：允许校验命令的结构，但不执行命令。类似于使用 Prepare 来检查语法，等等。
Schema：包含与所请求的查询相关的 XML 架构（用于指明列信息等）。
Data：仅包含所请求的数据。
SchemaData：返回架构信息和数据。
*/
void serializeAny(SoapSerializer * SoapSer,char * filename){
	std::string schemaStr;
	if(Content=="SchemaData"||Content=="Schema"){
		readfile(filename,schemaStr);
		SoapSer->serialize(schemaStr.c_str(),NULL);
	}
	if(Content=="SchemaData"||Content=="Data"){	
		for(int i=0;i<rows.size();i++){
		SoapSer->serialize("<row>\r\n",NULL);
		rows[i].serialize(SoapSer);
		SoapSer->serialize("</row>\r\n",NULL);
		}
	}
	if(Content=="None"){
		//do nothing
	}
}
	virtual bool processValue(Restrictions restrictions,Properties properties)=0;

	void serializeAsElement(AxisChar* columnName,AxisChar* columnValue,SoapSerializer * SoapSer){
		SoapSer->serialize("<",columnName,">",columnValue,"</",columnName,">\r\n",NULL);
	}
	
	//检查row是否符合所有restrictions
	bool isConsistent(Row row,Restrictions restrictions){
		if(restrictions.size()==0) 
			return true; 
		for(Restrictions::iterator iter=restrictions.begin();iter!=restrictions.end();iter++){
			if(!row.contain(iter->first,iter->second))
				return false;
		}
		return true;
	}

	virtual void processProperties(Properties properties)=0;

	
	static string DR2Str(DISCOVER_RequestType dr){
	string rstr;
	switch(dr) {
	case discover_DATASOURCES:
		rstr="DISCOVER_DATASOURCES";
		break;
	case discover_PROPERTIES:
		rstr="DISCOVER_PROPERTIES";
		break;

	case discover_SCHEMA_ROWSETS:
		rstr="DISCOVER_SCHEMA_ROWSETS";
		break;

	case discover_ENUMERATORS:
		rstr="DISCOVER_ENUMERATORS";
		break;
	case discover_KEYWORDS:
		rstr="DISCOVER_KEYWORDS";
		break;
	case discover_LITERALS:
		rstr="DISCOVER_LITERALS";
		break;
	case mdschema_ACTIONS:
		rstr="MDSCHEMA_ACTIONS";
		break;
	case mdschema_CUBES:
		rstr="MDSCHEMA_CUBES";
		break;
	case mdschema_DIMENSIONS:
		rstr="MDSCHEMA_DIMENSIONS";
		break;
	case mdschema_HIERARCHIES:
		rstr="MDSCHEMA_HIERARCHIES";
		break;
	case mdschema_LEVELS:
		rstr="MDSCHEMA_LEVELS";
		break;
	case mdschema_MEASURES:
		rstr="MDSCHEMA_MEASURES";
		break;
	case mdschema_PROPERTIES:
		rstr="MDSCHEMA_PROPERTIES";
		break;
	case mdschema_SETS:
		rstr="MDSCHEMA_SETS";
		break;

	case mdschema_MEMBERS:
		rstr="MDSCHEMA_MEMBERS";
		break;

	default:
		rstr="";
	}

	return rstr;
}

	static DISCOVER_RequestType Str2DR(string rstr){
		
		if(rstr=="DISCOVER_DATASOURCES")
			return discover_DATASOURCES;

		if(rstr=="DISCOVER_PROPERTIES")
			return discover_PROPERTIES;

		if(rstr=="discover_SCHEMA_ROWSETS")
			return discover_SCHEMA_ROWSETS;

		if(rstr=="DISCOVER_ENUMERATORS")
			return discover_ENUMERATORS;

		if(rstr=="DISCOVER_KEYWORDS")
			return discover_KEYWORDS;

		if(rstr=="DISCOVER_LITERALS")
			return discover_LITERALS;

		if(rstr=="MDSCHEMA_ACTIONS")
			return mdschema_ACTIONS;

		if(rstr=="MDSCHEMA_CUBES")
			return mdschema_CUBES;

		if(rstr=="MDSCHEMA_DIMENSIONS")
			return mdschema_DIMENSIONS;

		if(rstr=="MDSCHEMA_HIERARCHIES")
			return mdschema_HIERARCHIES;

		if(rstr=="MDSCHEMA_LEVELS")
			return mdschema_LEVELS;

		if(rstr=="MDSCHEMA_MEASURES")
			return mdschema_MEASURES;
		
		if(rstr=="MDSCHEMA_PROPERTIES")
			return mdschema_PROPERTIES;
		
		if(rstr=="MDSCHEMA_SETS")
			return mdschema_SETS;

		if(rstr=="MDSCHEMA_MEMBERS")
			return mdschema_MEMBERS;

		return NULLorErr;
	}

	void setProperties(Properties properties){
		Catalog="";
		Content="SchemaData";
		DataSourceInfo="";
		Format="Tabular";
		MDXSupport="Core";
		Password="";
		ProviderName="";
		ProviderVersion="";
		UserName="";

		Properties::iterator pIt;

		pIt=properties.find("Catalog");
		if(pIt!=properties.end())
			Catalog=pIt->second;
		
		pIt=properties.find("Content");
		if(pIt!=properties.end())
			Content=pIt->second;
		
		pIt=properties.find("DataSourceInfo");
		if(pIt!=properties.end())
			DataSourceInfo=pIt->second;

		pIt=properties.find("Format");
		if(pIt!=properties.end())
			Format=pIt->second;

		pIt=properties.find("LocaleIdentifier");
		if(pIt!=properties.end())
			LocaleIdentifier=pIt->second;

		pIt=properties.find("MDXSupport");
		if(pIt!=properties.end())
			MDXSupport=pIt->second;

		pIt=properties.find("Password");
		if(pIt!=properties.end())
			Password=pIt->second;

		pIt=properties.find("ProviderName");
		if(pIt!=properties.end())
			ProviderName=pIt->second;

		pIt=properties.find("ProviderVersion");
		if(pIt!=properties.end())
			ProviderVersion=pIt->second;

		pIt=properties.find("StateSupport");
		if(pIt!=properties.end())
			StateSupport=pIt->second;

		pIt=properties.find("Timeout");
		if(pIt!=properties.end())
			Timeout=pIt->second;

		pIt=properties.find("UserName");
		if(pIt!=properties.end())
			UserName=pIt->second;
		
	}
	
	std::vector <Row> rows;
protected:
	
	//properties
	string Catalog;
	string Content;
	string DataSourceInfo;
	string Format;
	string LocaleIdentifier;
	string MDXSupport;
	string Password;
	string ProviderName;
	string ProviderVersion;
	string StateSupport;
	string Timeout;
	string UserName;

};



#endif // !defined(AFX_RESULTSET_H__1AE1D65D_5E03_4B2F_9D8E_6874EB947EF9__INCLUDED_)
