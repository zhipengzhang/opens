#ifdef WIN32
#pragma warning (disable : 4786)
#pragma warning (disable : 4275)
#endif

#include "XmlRpcSocket.h"
#include "XmlRpcUtil.h"
#include "../soap/SoapParser.h"
#include "winsock2.h"
#include "HTTPParser.h"
#include "XmlRpc.h"

//#include "../xmla/DiscoverMethod.h"

#include "../xmla/RowsetBuilder.h"
#include "../xmla/ResultSet.h"
#include "../engine/SoapServer.h"

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include <DWSchemac/XSchemas.h>
#include <DWSchemac/XSchema.h>
#include <DWSchemac/Dimension.h>

using namespace std;

using namespace XmlRpc;

using namespace dwschemac;

//XSchemas XSchemas::instance();


int discoverU(Rowset* rsSet, SoapSerializer *serializer, bool bArray){
	serializer->serialize(">\r\n",NULL);
	rsSet->serialize(serializer);
	return AXIS_SUCCESS;
}

int executeU(ResultSet* rsSet, SoapSerializer *serializer, bool bArray){
	serializer->serialize(">\r\n",NULL);
	rsSet->serialize(serializer);
	return AXIS_SUCCESS;
}


void string_replace(string & strBig, const string & strsrc, const string &strdst) {
		string::size_type pos=0;
		string::size_type srclen=strsrc.size();
		string::size_type dstlen=strdst.size();
		while( (pos=strBig.find(strsrc, pos)) != string::npos){
			strBig.replace(pos, srclen, strdst);
			pos += dstlen;        
	}
}

void sendstr(int s, std::string str){
	char *sp1 = const_cast<char*>(str.c_str());
	send(s,sp1,str.length(),0);
}

bool readfile(char * filename,std::string &send){
	ifstream myf;
	myf.open(filename);
	
	if(!myf)
	{
		myf.clear();
		myf.open("~rawdata.csv");
		if(!myf)
		{
		   return false;
		}
	}
	
	char lineBuffer[1000];
	while(myf.getline(lineBuffer,sizeof(lineBuffer))){
		send=send+lineBuffer+"\r\n";
	}
	return true;
}


int test1(){

	SoapSerializer serializer;
	SoapTransport soaptransport;
	serializer.init();
	
	soaptransport.init(81,5);

	int sockCon=soaptransport.accept();

	string rs1;
	soaptransport.Read(sockCon,rs1);

	std::string sends1;
	readfile("ToSend1.txt",sends1);
	soaptransport.sendBytes(sends1.c_str());
	soaptransport.flushOutput(sockCon);
	
	string rs2;
	soaptransport.Read(sockCon,rs2);
	std::string sends2;
	readfile("ToSend2.txt",sends2);
	soaptransport.sendBytes(sends2.c_str());
	soaptransport.flushOutput(sockCon);
	
	string rs3;
	soaptransport.Read(sockCon,rs3);
	std::string sends3;
	readfile("ToSend3.txt",sends3);
	soaptransport.sendBytes(sends3.c_str());
	soaptransport.flushOutput(sockCon);

	string rs4;
	soaptransport.Read(sockCon,rs4);
	std::string sends4;
	readfile("ToSend4.txt",sends4);
	string_replace(sends4,"[0d]","\r");
	string_replace(sends4,"[0a]","\n");
	soaptransport.sendBytes(sends4.c_str());
	soaptransport.flushOutput(sockCon);

	string rs5;
	soaptransport.Read(sockCon,rs5);
	std::string sends5;
	readfile("ToSend5.txt",sends5);
	soaptransport.sendBytes(sends5.c_str());
	soaptransport.flushOutput(sockCon);

	string rs6;
	soaptransport.Read(sockCon,rs6);
	std::string sends6;
	readfile("ToSend6.txt",sends6);
	string_replace(sends6,"[ef]","\xef");
	string_replace(sends6,"[bf]","\xbf");
	string_replace(sends6,"[a5]","\xa5");
	soaptransport.sendBytes(sends6.c_str());
	soaptransport.flushOutput(sockCon);

	string rs7;
	soaptransport.Read(sockCon,rs7);

	soaptransport.sendBytes("");
	soaptransport.flushOutput(sockCon);


		string rs8;
		soaptransport.Read(sockCon,rs8);
	/*
		soaptransport.sendBytes("\r\n");
		soaptransport.flushOutput(sockCon);*/
	
	while(1){
	}
	return 0;
}




//void test(){
//
//	xSchemas.createSchema("FoodMart.xml");
//
//	SoapSerializer serializer;
//	SoapTransport soaptransport;
//	serializer.init();
//
//	soaptransport.init(81,5);
//
//	int sockCon=soaptransport.accept();
//	string rs1;
//	//111111111111111111111111111111111111111111111111111111111111111111111111111111
//	soaptransport.Read(sockCon,rs1);
//	
///*	std::string sends1;
//	readfile("ToSend1.txt",sends1);
//	soaptransport.sendBytes(sends1.c_str());
//	soaptransport.flushOutput(sockCon);*/
//	
//	//加入XML命名空间和前缀
//	serializer.addNamespaceToNamespaceList("urn:schemas-microsoft-com:xml-analysis","m");
//	serializer.addNamespaceToNamespaceList("http://www.w3.org/2001/XMLSchema-instance","xsi");
//	serializer.addNamespaceToNamespaceList("http://www.w3.org/2001/XMLSchema","xsd");
//	serializer.addNamespaceToNamespaceList("urn:schemas-microsoft-com:xml-analysis:mddataset","n");
//	serializer.addNamespaceToNamespaceList("EX","urn:schemas-microsoft-com:xml-analysis:exception");
//	//获取Resultset
//	Restrictions restrictions;
//	Properties properties;
//	
//	Rowset * rsSet=RowsetBuilder::getRowset(discover_DATASOURCES,restrictions,properties);
//
//	//SoapMethod
//	serializer.createSoapMethod("DiscoverResponse","urn:schemas-microsoft-com:xml-analysis",true);
//	serializer.addOutputCmplxParam(rsSet,(void *)discoverU,NULL,"root","urn:schemas-microsoft-com:xml-analysis:rowset");
//	
//	soaptransport.setTransportProperty("Server","Microsoft-IIS/5.1");
//	soaptransport.setTransportProperty("Date","Tue, 26 Dec 2006 12:13:11 GMT");
//	soaptransport.setTransportProperty("Content-Type","text/xml");
//	soaptransport.setTransportProperty("charset","\"utf-8\"");
//	soaptransport.setTransportProperty("Transfer-encoding","chunked");
//	
//	//将待发送字符添加到缓存
//	serializer.setOutputStream(&soaptransport);
//	//处理HTTP Header
//	soaptransport.processHttpHeader();
//	//发送
//	soaptransport.flushOutput(sockCon);
//
//	/* **********************************************************************  */
//	
////2222222222222222222222222222222222222222222222222222222222222222222222222222222222222
///*			string rs2;
//			soaptransport.Read(sockCon,rs2);
//			
//			std::string sends2;
//			readfile("ToSend2.txt",sends2);
//			soaptransport.sendBytes(sends2.c_str());
//			soaptransport.flushOutput(sockCon);*/
//			
//	string rs2;
//	soaptransport.Read(sockCon,rs2);
//		//获取Resultset
//
//		Restrictions restrictions2;
//		restrictions2.insert(pair<string,string>("CATALOG_NAME","FoodMart 2000"));
//		restrictions2.insert(pair<string,string>("CUBE_NAME","Sales"));
//		Properties properties2;
//		properties2.insert(pair<string,string>("Content","SchemaData"));
//		Rowset* dimrsSet=RowsetBuilder::getRowset(mdschema_DIMENSIONS,restrictions2,properties2);
//		
//		//SoapMethod
//		serializer.createSoapMethod("DiscoverResponse","urn:schemas-microsoft-com:xml-analysis",true);
//		serializer.addOutputCmplxParam(dimrsSet,(void *)discoverU,NULL,"root","urn:schemas-microsoft-com:xml-analysis:rowset");
//
//		soaptransport.setTransportProperty("Server","Microsoft-IIS/5.1");
//		soaptransport.setTransportProperty("Date","Tue, 26 Dec 2006 12:13:11 GMT");
//		soaptransport.setTransportProperty("Content-Type","text/xml");
//		soaptransport.setTransportProperty("charset","\"utf-8\"");
//		soaptransport.setTransportProperty("Transfer-encoding","chunked");
//
//		//将待发送字符添加到缓存
//		serializer.setOutputStream(&soaptransport);
//		//处理HTTP Header
//		soaptransport.processHttpHeader();
//		//发送
//		soaptransport.flushOutput(sockCon);
//		
////3333333333333333333333333333333333333333333333333333333333333333333333333333
//				
///*				string rs3;
//				soaptransport.Read(sockCon,rs3);
//				std::string sends3;
//				readfile("ToSend3.txt",sends3);
//				soaptransport.sendBytes(sends3.c_str());
//				soaptransport.flushOutput(sockCon);*/
//		
//		string rs3;
//		soaptransport.Read(sockCon,rs3);
//		//获取Resultset
//		Restrictions restrictions3;
//		restrictions3.insert(pair<string,string>("CATALOG_NAME","FoodMart 2000"));
//		restrictions3.insert(pair<string,string>("CUBE_NAME","Sales"));
//		Properties properties3;
//		properties3.insert(pair<string,string>("SchemaData","SchemaData"));
//		Rowset * dimrsSet3=RowsetBuilder::getRowset(mdschema_HIERARCHIES,restrictions3,properties3);
//		
//		//SoapMethod
//		serializer.createSoapMethod("DiscoverResponse","urn:schemas-microsoft-com:xml-analysis",true);
//		serializer.addOutputCmplxParam(dimrsSet3,(void *)discoverU,NULL,"root","urn:schemas-microsoft-com:xml-analysis:rowset");
//		
//		soaptransport.setTransportProperty("Server","Microsoft-IIS/5.1");
//		soaptransport.setTransportProperty("Date","Tue, 26 Dec 2006 12:13:11 GMT");
//		soaptransport.setTransportProperty("Content-Type","text/xml");
//		soaptransport.setTransportProperty("charset","\"utf-8\"");
//		soaptransport.setTransportProperty("Transfer-encoding","chunked");
//		
//		//将待发送字符添加到缓存
//		serializer.setOutputStream(&soaptransport);
//		//处理HTTP Header
//		soaptransport.processHttpHeader();
//		//发送
//		soaptransport.flushOutput(sockCon);
//		
////444444444444444444444444444444444444444444444444444444444444444444444444444
//	/*			string rs4;
//				soaptransport.Read(sockCon,rs4);
//				std::string sends4;
//				readfile("ToSend4.txt",sends4);
//				string_replace(sends4,"[0d]","\r");
//				string_replace(sends4,"[0a]","\n");
//				soaptransport.sendBytes(sends4.c_str());
//				soaptransport.flushOutput(sockCon);*/
//			
//
//		string rs4;
//		soaptransport.Read(sockCon,rs4);
//		//获取Resultset
//		Restrictions restrictions4;
//		restrictions4.insert(pair<string,string>("CATALOG_NAME","FoodMart 2000"));
//		restrictions4.insert(pair<string,string>("CUBE_NAME","Sales"));
//		Properties properties4;
//		properties4.insert(pair<string,string>("Content","SchemaData"));
//		Rowset* dimrsSet4=RowsetBuilder::getRowset(mdschema_LEVELS,restrictions4,properties4);
//		
//		//SoapMethod
//		serializer.createSoapMethod("DiscoverResponse","urn:schemas-microsoft-com:xml-analysis",true);
//		serializer.addOutputCmplxParam(dimrsSet4,(void *)discoverU,NULL,"root","urn:schemas-microsoft-com:xml-analysis:rowset");
//		
//			soaptransport.setTransportProperty("Server","Microsoft-IIS/5.1");
//	soaptransport.setTransportProperty("Date","Tue, 26 Dec 2006 12:13:11 GMT");
//	soaptransport.setTransportProperty("Content-Type","text/xml");
//	soaptransport.setTransportProperty("charset","\"utf-8\"");
//	soaptransport.setTransportProperty("Transfer-encoding","chunked");
//
//		//将待发送字符添加到缓存
//		serializer.setOutputStream(&soaptransport);
//		//处理HTTP Header
//		soaptransport.processHttpHeader();
//		//发送
//		soaptransport.flushOutput(sockCon);
//
//  
////5555555555555555555555555555555555555555555555555555555555555555555555
//
//				
///*				string rs5;
//				soaptransport.Read(sockCon,rs5);
//				std::string sends5;
//				readfile("ToSend5.txt",sends5);
//				soaptransport.sendBytes(sends5.c_str());
//				soaptransport.flushOutput(sockCon);*/
//				
//		string rs5;
//		soaptransport.Read(sockCon,rs5);
//		//获取Resultset
//		Restrictions restrictions5;
//		restrictions5.insert(pair<string,string>("CATALOG_NAME","FoodMart 2000"));
//		restrictions5.insert(pair<string,string>("CUBE_NAME","Sales"));
//		Properties properties5;
//		properties5.insert(pair<string,string>("Content","SchemaData"));
//		Rowset * dimrsSet5=RowsetBuilder::getRowset(mdschema_PROPERTIES,restrictions5,properties5);
//		
//		//SoapMethod
//		serializer.createSoapMethod("DiscoverResponse","urn:schemas-microsoft-com:xml-analysis",true);
//		serializer.addOutputCmplxParam(dimrsSet5,(void *)discoverU,NULL,"root","urn:schemas-microsoft-com:xml-analysis:rowset");
//		
//			soaptransport.setTransportProperty("Server","Microsoft-IIS/5.1");
//	soaptransport.setTransportProperty("Date","Tue, 26 Dec 2006 12:13:11 GMT");
//	soaptransport.setTransportProperty("Content-Type","text/xml");
//	soaptransport.setTransportProperty("charset","\"utf-8\"");
//	soaptransport.setTransportProperty("Transfer-encoding","chunked");
//	
//		//将待发送字符添加到缓存
//		serializer.setOutputStream(&soaptransport);
//		//处理HTTP Header
//		soaptransport.processHttpHeader();
//		//发送
//		soaptransport.flushOutput(sockCon);
//			
////6666666666666666666666666666666666666666666666666666666666666666666666
///*			string rs6;	
//			soaptransport.Read(sockCon,rs6);
//				std::string sends6;
//				readfile("ToSend6.txt",sends6);
//				string_replace(sends6,"[ef]","\xef");
//				string_replace(sends6,"[bf]","\xbf");
//				string_replace(sends6,"[a5]","\xa5");
//				soaptransport.sendBytes(sends6.c_str());
//				soaptransport.flushOutput(sockCon);*/
//				
//
//		
////string mdx="select {[Measures].[Unit Sales], [Measures].[Store Cost], [Measures].[Store Sales]} ON COLUMNS, Hierarchize(Union(Union(Union(Crossjoin({[Time].[Time].[1997].[Q2].[4]}, {[Education Level].[Education Level]}),Crossjoin({[Time].[Time].[1997].[Q2].[4]}, [Education Level].[Education Level].Children)), Union(Crossjoin({[Time].[Time].[1997].[Q2].[5]}, {[Education Level].[Education Level]}), Crossjoin({[Time].[Time].[1997].[Q2].[5]}, [Education Level].[Education Level].Children))), Union(Crossjoin({[Time].[Time].[1997].[Q2].[6]}, {[Education Level].[Education Level]}), Crossjoin({[Time].[Time].[1997].[Q2].[6]}, [Education Level].[Education Level].Children)))) ON ROWS from [Sales]";
////string mdx="select {[Measures].[Store Cost], [Measures].[Store Sales]} on columns,{([Promotion Media].[All Media], [Product].[All Products])} ON rows from Sales where ([Time].[1997])";
////string mdx="select from Sales where ([Time].[1997])";
//string mdx="select {[Measures].[Store Cost], [Measures].[Store Sales]} on columns,{([Promotion Media].[All Media], [Product].[All Products])} ON rows from Sales";	
//	Properties properties6;
//	properties6.insert(pair<string,string>("Catalog","FoodMart 2000"));
//	string rs6;
//	soaptransport.Read(sockCon,rs6);
//	ResultSet resultsSet(mdx,properties6,".\\Sales");
//	 
//	//SoapMethod
//	serializer.createSoapMethod("ExecuteResponse","urn:schemas-microsoft-com:xml-analysis",true);
//	serializer.addOutputCmplxParam(&resultsSet,(void *)executeU,NULL,"root","urn:schemas-microsoft-com:xml-analysis:mddataset");
//	
//	soaptransport.setTransportProperty("Server","Microsoft-IIS/5.1");
//	soaptransport.setTransportProperty("Date","Tue, 26 Dec 2006 12:13:11 GMT");
//	soaptransport.setTransportProperty("Content-Type","text/xml");
//	soaptransport.setTransportProperty("charset","\"utf-8\"");
//	soaptransport.setTransportProperty("Transfer-encoding","chunked");
//
//
//	//将待发送字符添加到缓存
//	serializer.setOutputStream(&soaptransport);
//	//处理HTTP Header
//	soaptransport.processHttpHeader();
//	//发送
//	soaptransport.flushOutput(sockCon);
//
//	while(1){
//	}
//	string rss1;
//	soaptransport.Read(sockCon,rss1);
//
//	string rss2;
//	soaptransport.Read(sockCon,rss2);
//
//
//	XmlRpcSocket::close(sockCon);
//	int sockCon2=soaptransport.accept();
//
//	string rs7;
//	soaptransport.Read(sockCon2,rs7);
//
//	string rs8;
//	soaptransport.Read(sockCon2,rs8);
//
//	xSchemas.Dispose();
//	
//	while(1){
//	}
//}

void testServer(){
	XSchemas::instance().createSchema("./Foodmart.xml");
	SoapServer *s=SoapServer::instance();

	s->process(81,5);


}



int main(){

//	testSoapServer();
//	testParseXML();
//	test1();
//	test();

	testServer();
//	testMeasure();

	return 1;
}









