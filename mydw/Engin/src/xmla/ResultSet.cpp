#include "ResultSet.h"

 static int queryno=0;
ResultSet::ResultSet(std::string MDXString,Properties props,std::string cubeDir)
{	

	auto_ptr<QueryComputation>  temp(new QueryComputation(MDXString,cubeDir));
 	
	queryCom = temp;

	char stri[10];
	itoa(++queryno,stri,10);
	std::string filep=".\\log\\"+string(stri)+".txt";
	std::ofstream logFile(filep.c_str());
	std::streambuf *outbuf = std::cout.rdbuf(logFile.rdbuf());
 
	//执行查询
	Settime();
	cellset = queryCom->queryComputation();
	cout<<Gettime();
	cout<<"the query time:"<<Gettime()<<endl<<endl;
  
	//输出查询结果信息
	cout<<"mdx:"<<MDXString<<"\n";
//	cout<<"axesSize:"<<cellset.parsedMdx->getAxes().size()<<endl;
//	cout<<"the Result cells:\n";
//	for (int i = 0; i < cellset.Cells.size();i ++)
//	{
//		cout<<"Cell "<<i<<":  "<<cellset.Cells[i].value<<endl;
//		for(int j = 0; j <cellset.Cells[i].cellDimsVals.size(); j ++)
//			cout<<cellset.Cells[i].cellDimsVals[j]<<" ";
//		cout<<endl;
//	}
	std::cout.rdbuf(outbuf);
	 
	parsedMDX = queryCom->getParsedMDX();
	
	//default properties
	AxisFormat="TupleFormat";
	BeginRange="-1";
	Catalog="";
	Content="SchemaData";
	DataSourceInfo="";
	EndRange="-1";
	Format="Multidimensional";
	Password="";
	UserName="";
	
	Properties::iterator pIt;

		pIt=props.find("AxisFormat");
		if(pIt!=props.end())
			AxisFormat=pIt->second;

		pIt=props.find("BeginRange");
		if(pIt!=props.end())
			BeginRange=pIt->second;

		pIt=props.find("Catalog");
		if(pIt!=props.end())
			Catalog=pIt->second;

		pIt=props.find("Content");
		if(pIt!=props.end())
			Content=pIt->second;

		pIt=props.find("DataSourceInfo");
		if(pIt!=props.end())
			DataSourceInfo=pIt->second;

		pIt=props.find("EndRange");
		if(pIt!=props.end())
			EndRange=pIt->second;

		pIt=props.find("Format");
		if(pIt!=props.end())
			Format=pIt->second;

		pIt=props.find("LocaleIdentifier");
		if(pIt!=props.end())
			LocaleIdentifier=pIt->second;

		pIt=props.find("Password");
		if(pIt!=props.end())
			Password=pIt->second;

		pIt=props.find("Timeout");
		if(pIt!=props.end())
			Timeout=pIt->second;

		pIt=props.find("UserName");
		if(pIt!=props.end())
			UserName=pIt->second;
		
}

ResultSet::~ResultSet()
{

}
  
void ResultSet::serializeSchema(SoapSerializer * SoapSer){
	//schema
	std::string schemaStr;
	readfile("schemas/execute_schema.txt",schemaStr);

	SoapSer->serialize(schemaStr.c_str(),NULL);
	
}
     
 
void ResultSet::serialize(SoapSerializer * SoapSer){

	char stri[10];
	itoa(queryno,stri,10);
	std::string filep=".\\log\\"+string(stri)+".txt";
	std::ofstream logFile(filep.c_str(),ios::app);
	std::streambuf *outbuf = std::cout.rdbuf(logFile.rdbuf());
 
	//执行查询
	Settime();

	serializeSchema(SoapSer);
	cout<<"serializeSchema time:"<<Gettime()<<"\n";

	serializeOlapInfo(SoapSer);
	cout<<"serializeOlapInfo time:"<<Gettime()<<"\n";

	serializeAxesTF(SoapSer);
	cout<<"serializeAxesTF time:"<<Gettime()<<"\n";

	serializeCellData(SoapSer);
	cout<<"serializeCellData time:"<<Gettime()<<"\n";

	std::cout.rdbuf(outbuf);
}

//<OlapInfo> output
void ResultSet::serializeOlapInfo(SoapSerializer * SoapSer){

	//<OlapInfo> output
    SoapSer->serialize("<OlapInfo>\r\n",NULL);
	//<AxesInfo> output
	SoapSer->serialize("<AxesInfo>\r\n",NULL);

	const vector< vector<QueryTuple*> > axes= parsedMDX->getAxes();
	AxisChar m_Buf[32];
	QueryTuple *qtuple;
	string hierarchyName;
	
	//<axes>
	for(int an=0;an<axes.size();an++){
		AxisSprintf(m_Buf, 8, "Axis%d", an);
		
		SoapSer->serialize("<AxisInfo name=\"",m_Buf,"\">\r\n",NULL);
		if(axes[an].size()<1)
			//err log
			break;
		qtuple=axes[an][0];
		if(!qtuple)
			//err log
			break;
		const vector<QueryMember*> qmembers=qtuple->getMembers();
		
		for(int qmemNo=0;qmemNo<qmembers.size();qmemNo++){
			if(!qmembers[qmemNo])
				continue;
			hierarchyName=qmembers[qmemNo]->getHierarchyName();
			SoapSer->serialize("<HierarchyInfo name=\"",hierarchyName.c_str(),"\">\r\n",NULL);
			SoapSer->serialize("<UName name=\"[",hierarchyName.c_str(),"].[MEMBER_UNIQUE_NAME]\"/>\r\n",NULL);
			SoapSer->serialize("<Caption name=\"[",hierarchyName.c_str(),"].[MEMBER_CAPTION]\"/>\r\n",NULL);
			SoapSer->serialize("<LName name=\"[",hierarchyName.c_str(),"].[LEVEL_UNIQUE_NAME]\"/>\r\n",NULL);
			SoapSer->serialize("<LNum name=\"[",hierarchyName.c_str(),"].[LEVEL_NUMBER]\"/>\r\n",NULL);
			SoapSer->serialize("<DisplayInfo name=\"[",hierarchyName.c_str(),"].[DISPLAY_INFO]\"/>\r\n",NULL);
			SoapSer->serialize("</HierarchyInfo>\r\n",NULL);
		}
		SoapSer->serialize("</AxisInfo>\r\n",NULL);
		
	}
	//</axes>   end
	//SlicerAxis begin
	SoapSer->serialize("<AxisInfo name=\"SlicerAxis\">\r\n",NULL);
  
	const vector<QueryTuple*> slicerAxis=parsedMDX->getSlicer();

	if(slicerAxis.size()>0){
	
		QueryTuple * slicerTuple=slicerAxis[0];
	
		const vector<QueryMember*> qmembers=slicerTuple->getMembers();
		for(int qmemNo=0;qmemNo<qmembers.size();qmemNo++){
			hierarchyName=qmembers[qmemNo]->getHierarchyName();
			SoapSer->serialize("<HierarchyInfo name=\"",hierarchyName.c_str(),"\">\r\n",NULL);
			SoapSer->serialize("<UName name=\"[",hierarchyName.c_str(),"].[MEMBER_UNIQUE_NAME]\"/>\r\n",NULL);
			SoapSer->serialize("<Caption name=\"[",hierarchyName.c_str(),"].[MEMBER_CAPTION]\"/>\r\n",NULL);
			SoapSer->serialize("<LName name=\"[",hierarchyName.c_str(),"].[LEVEL_UNIQUE_NAME]\"/>\r\n",NULL);
			SoapSer->serialize("<LNum name=\"[",hierarchyName.c_str(),"].[LEVEL_NUMBER]\"/>\r\n",NULL);
			SoapSer->serialize("<DisplayInfo name=\"[",hierarchyName.c_str(),"].[DISPLAY_INFO]\"/>\r\n",NULL);
			SoapSer->serialize("</HierarchyInfo>\r\n",NULL);
		}
	}
	 
	//SlicerAxis end
	SoapSer->serialize("</AxisInfo>\r\n",NULL);
	//AxisInfo end
	SoapSer->serialize("</AxesInfo>\r\n",NULL);
	
	//CellInfo
	SoapSer->serialize("<CellInfo>\r\n",NULL);
	SoapSer->serialize("<Value name=\"VALUE\"/>\r\n",NULL);
	SoapSer->serialize("<FmtValue name=\"FORMATTED_VALUE\"/>\r\n",NULL);
	SoapSer->serialize("<CellOrdinal name=\"CELL_ORDINAL\"/>\r\n",NULL);
	SoapSer->serialize("</CellInfo>\r\n",NULL);

	SoapSer->serialize("</OlapInfo>\r\n",NULL);
}


//只实现默认的TupleFormat格式，ClusterFormat格式和CustomFormat格式暂不实现
void ResultSet::serializeAxesTF(SoapSerializer * SoapSer){
	
	SoapSer->serialize("<Axes>\r\n",NULL);
	QueryTuple * queryTuple;
	vector<QueryMember*> members;
	QueryMember * member;
	AxisChar m_Buf[32];
	const vector< vector<QueryTuple*> > axes= parsedMDX->getAxes();

	for(int an=0;an<axes.size();an++){
		char axesbuf[10];
		AxisSprintf(axesbuf, 8, "%d", an);
		cout<<"Axes"+string(axesbuf)+":"<<Gettime()<<"\n";
		
		AxisSprintf(m_Buf, 8, "Axis%d", an);
		//Axis
		SoapSer->serialize("<Axis name=\"",m_Buf,"\">\r\n",NULL);
		//<Tuples>
		SoapSer->serialize("<Tuples>\r\n",NULL);
		
		//Tuples output
		for(int tuplei=0;tuplei<axes[an].size();tuplei++){
			
			char t_Buf[10];
			AxisSprintf(t_Buf, 8, "%d", tuplei);
			cout<<"tuplei"+string(t_Buf)+":"<<Gettime()<<"\n";

			queryTuple=axes[an][tuplei];

			if(!queryTuple)
				//err log here
				continue;
 
			members=queryTuple->getMembers();
 
			SoapSer->serialize("<Tuple>\r\n",NULL);

			for(int memi=0;memi<members.size();memi++){
				member=members[memi];
				if(!member)
					//err log here
					continue;
				string heirarchyname=member->getHierarchyName();
				//menber
				SoapSer->serialize("<Member Hierarchy=\"",heirarchyname.c_str(),"\">\r\n",NULL);
			  	
				SoapSer->serialize("<UName>",getUName(member).c_str(),"</UName>\r\n",NULL);
				SoapSer->serialize("<Caption>",member->getVal().c_str(),"</Caption>\r\n",NULL);
				SoapSer->serialize("<LName>",getLName(member).c_str(),"</LName>\r\n",NULL);		
				
		 	
				SoapSer->serialize("<LNum>",getLNum(member).c_str(),"</LNum>\r\n",NULL);
				SoapSer->serialize("<DisplayInfo>",getDisplayInfo(member).c_str(),"</DisplayInfo>\r\n",NULL);

				SoapSer->serialize("</Member>\r\n",NULL);
			}
			SoapSer->serialize("</Tuple>\r\n",NULL);
		}

		//</Tuples> end
		SoapSer->serialize("</Tuples>\r\n",NULL);
		//Axis end
		SoapSer->serialize("</Axis>\r\n",NULL);

		cout<<"End Axes"+string(axesbuf)+":"<<Gettime()<<"\n";
	}

	cout<<"After Axis:"<<Gettime()<<"\n";
	//SlicerAxis  ///////////////////////
	const vector<QueryTuple*> slicerAxis=parsedMDX->getSlicer();
	SoapSer->serialize("<Axis name=\"SlicerAxis\">\r\n",NULL);
	if(slicerAxis.size()>0){

		//<Tuples>
		SoapSer->serialize("<Tuples>\r\n",NULL);

		//<Tuple>
		SoapSer->serialize("<Tuple>\r\n",NULL);

		if(slicerAxis[0]){
			members=slicerAxis[0]->getMembers();
			for(int memi=0;memi<members.size();memi++){

				//cout<<"memi:"<<Gettime()<<"\n";
				
				member=members[memi];
				if(!member)
					//err log here
					continue;
				string heirarchyname=member->getHierarchyName();
				//menber
				SoapSer->serialize("<Member Hierarchy=\"",heirarchyname.c_str(),"\">\r\n",NULL);
				
				SoapSer->serialize("<UName>",getUName(member).c_str(),"</UName>\r\n",NULL);
				SoapSer->serialize("<Caption>",member->getVal().c_str(),"</Caption>\r\n",NULL);
				SoapSer->serialize("<LName>",getLName(member).c_str(),"</LName>\r\n",NULL);
				SoapSer->serialize("<LNum>",getLNum(member).c_str(),"</LNum>\r\n",NULL);
				SoapSer->serialize("<DisplayInfo>",getDisplayInfo(member).c_str(),"</DisplayInfo>\r\n",NULL);

				SoapSer->serialize("</Member>\r\n",NULL);
			}

		}
		//<Tuple> end
		SoapSer->serialize("</Tuple>\r\n",NULL);
		//</Tuples> end
		SoapSer->serialize("</Tuples>\r\n",NULL);

	//	cout<<"Axes"+string(m_Buf)+":"<<Gettime()<<"\n";
	}

	cout<<"After slicerAxis:"<<Gettime()<<"\n";
	//SlicerAxis end
	SoapSer->serialize("</Axis>\r\n",NULL);

	SoapSer->serialize("</Axes>\r\n",NULL);
}

//<CellData> out
void ResultSet::serializeCellData(SoapSerializer * SoapSer){
	
	SoapSer->serialize("<CellData>\r\n",NULL);
	AxisChar m_Buf[64];
	
	for(int i=0;i<cellset.Cells.size();i++){
		if(!cellset.Cells[i].isNull){
		
		AxisSprintf(m_Buf,32, "%d",i);
		string sno=m_Buf;
		//Cell
		SoapSer->serialize("<Cell CellOrdinal=\"",sno.c_str(),"\">\r\n",NULL);
		
		SoapSer->serialize("<Value xsi:type=\"xsd:double\">",getValue(cellset.Cells[i]).c_str(),"</Value>\r\n",NULL);
		SoapSer->serialize("<FmtValue>",getValue(cellset.Cells[i]).c_str(),"</FmtValue>\r\n",NULL);
		//Cell end
		SoapSer->serialize("</Cell>\r\n",NULL);
		}
	}
	
	SoapSer->serialize("</CellData>\r\n",NULL);
}
 

//获取Uname,如[Time].[1997].[Q2].[4]
string ResultSet::getUName(const QueryMember *member){
	if(!member)
		return "";
	string UName;
	//Hierarchy
	UName="["+member->getHierarchyName()+"]";
	
	//父level
	const vector<string> ancestorVals=member->getAncestorVals();
	for(int i=0;i<ancestorVals.size();i++)
		UName=UName+".["+ancestorVals[i]+"]";
	
	//level value
	UName=UName+".["+member->getVal()+"]";
	return UName;
}
 
//获取Level Name,如[Time].[Month]
string ResultSet::getLName(const QueryMember *member){
	 
		if(!member)
			return "";
		string LName;
   	
		//Hierarchy
		LName="["+member->getHierarchyName()+"]";
		
		//Level Name
		LName=LName+".["+member->getLevelName()+"]";
	
		return LName;
	
}

//获得该member的层数
string ResultSet::getLNum(const QueryMember *member){
	int lnum=0;
	if(member){
		lnum=member->getAncestorLevels().size();
	}
	AxisChar m_Buf[32];
	AxisSprintf(m_Buf,8, "%d", lnum);
	
	string res=m_Buf;
	return res;
}
         
//获得DisplayInfo
string ResultSet::getDisplayInfo(const QueryMember *member){
	int di=0;

	if(!parsedMDX)
		return "0";


	XSchema *p_xSchema= XSchemas::instance().getSchema(parsedMDX->getSchemaName());
	if(!p_xSchema)
		return "0";
	
	XCube *p_xCube=p_xSchema->getCube(parsedMDX->getCubeName());
	if(!p_xCube)
		return "0";
	
	//该维度是Measures
	if(member->getDimensionName()=="Measures"){
		//Measure * measure=p_xCube->getMeasure("Measures");
		
	//	if(!measure)
			return "0";
		//measure->get
	}

	else{
		Dimension* dim=p_xCube->getDimension(member->getDimensionName());
		if(!dim)
			return "0";

		Hierarchy *hie= dim->getHierarchy(member->getHierarchyName());
		if(!hie)
			return "0";

		Level *lev=hie->getLevel(member->getLevelName());
		if(!lev)
			return "0";
		
		Level * levchild=lev->getChildLevel();
		if(!levchild)
			return "0";
		di=levchild->getMemberCount();
	}
	
		
	AxisChar m_Buf[32];
	AxisSprintf(m_Buf,8, "%d",di);
	string res=m_Buf;
	return res;
}


 
//返回cell的value
string ResultSet::getValue(const Cell cell){
		
		if(cell.isNull)
			return "0";
		AxisChar m_buf[64];
		AxisSprintf(m_buf,32,"%f",cell.value);
		string rs=m_buf;
		return rs;

}


//SELECT {[Measures].[Store Cost], [Measures].[Store Sales]} ON columns, 
//Hierarchize(Union
//			
//(Union
//  (
//    CrossJoin({[Gender].[All Gender]}, {[Store].[All Stores]}), 
//    CrossJoin({[Gender].[All Gender]}, [Store].[All Stores].Children)
//   ), 
//    CrossJoin({[Gender].[All Gender]}, [Store].[All Stores].[Canada].Children)
//)
//) ON rows FROM Sales WHERE ([Time].[1997])
