// HTTPParser.cpp: implementation of the HTTPParser class.
//
//////////////////////////////////////////////////////////////////////

#include "HTTPParser.h"
#include "XmlRpcUtil.h"

#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

#define Double_LINE "\r\n\r\n"
#define One_LINE "\r\n"
#define COLON ":"
#define SPACE " "


HTTPParser::HTTPParser()
{

}

HTTPParser::~HTTPParser()
{

}

//返回是否需要socket继续接收
bool HTTPParser::parse(const std::string httpstr)
{
	//分隔header和body的标致
	int dlmpos;
	if((dlmpos=httpstr.find(Double_LINE))==string::npos){
		XmlRpc::XmlRpcUtil::error("HTTPParser::parse:Can not find the flag between header and body!");
		return false;
	}
	//body部分
	hc.body=httpstr.substr(dlmpos+4);
	
	//header部分
	std::string header=httpstr.substr(0,dlmpos);
	
	//以下解析header

	//首先解析Initial Request Line
	std::string hline;
	
	//Initial Request Line的分界
	int iniFlag=0;  
	if((iniFlag=header.find(One_LINE,0))==string::npos){
		XmlRpc::XmlRpcUtil::error("HTTPParser::parse:Can not find the Initial Request Line!\n");
		return false;
	}
	if(!handleInitialLine(header.substr(0,iniFlag)))
		return false;

	//解析header lines
	int epos=iniFlag+2;
	int bpos=iniFlag+2;
	while((epos=header.find(One_LINE,epos))!=string::npos){
		hline=header.substr(bpos,epos-bpos);
		epos=bpos=epos+2;
		if(!handleHeaderLine(hline))
			return false;
	}
	hline=header.substr(bpos);
	if(!handleHeaderLine(hline))
		return false;

/*LLH test
	std::cout<<"methodname:"<<hc.methodname<<"\npath:"<<hc.path<<"\nversion:"<<hc.version<<"\n";
	HTTPHeader::iterator my_Itr;
	for (my_Itr=hc.header.begin(); my_Itr!=hc.header.end(); ++my_Itr)
	{
		string first=my_Itr->first;
		string second=hc.header.find(first)->second;
		std::cout<<first<<":"<<second<<endl;
	}
	std::cout<<"body:\n"<<hc.body<<endl;
	*/
	
	return true;
}

/*
bool f(string ch,string ah)   
  {   
  if(   ch=="a"   ||   ch=="A"   )   
  return  true;   
  else   
  return   false;   
  }   */



/*
The header lines are in the usual text header format, which is: one line per header, 
of the form "Header-Name: value", ending with CRLF. It's the same format used for 
email and news postings, defined in RFC 822, section 3. Details about RFC 822 header lines: 
1.As noted above, they should end in CRLF, but you should handle LF correctly. 
2.The header name is not case-sensitive (though the value may be). 
3.Any number of spaces or tabs may be between the ":" and the value. 
4.Header lines beginning with space or tab are actually part of the previous header 
  line, folded into multiple lines for easy reading. 
*/
//将header的一行插入到HTTPContext类的header中
bool HTTPParser::handleHeaderLine(std::string line)
{
	int pos=0;
	if((pos=line.find(COLON))==string::npos){
		XmlRpc::XmlRpcUtil::error("HTTPParser::handleHeaderLine:Can not find the \":\" in the header line!");
		return false;
	}
	std::string headername=line.substr(0,pos);
	std::string value=line.substr(pos+2);

	//The header name is not case-sensitive (though the value may be).so now transform it to lower case.
	transform (headername.begin(), headername.end(), headername.begin(), (int(*)(int))tolower);
	
	hc.header.insert(make_pair(headername,value));

	return true;
}

/*
The initial line is different for the request than for the response. 
A request line has three parts, separated by spaces: a method name, 
the local path of the requested resource, and the version of HTTP being used. 
A typical request line is: 
GET /path/to/file/index.html HTTP/1.0
*/
//处理HTTP请求的Initial Request Line
bool HTTPParser::handleInitialLine(std::string line){
	//解析方法名
	int pos1=0;
	if((pos1=line.find(SPACE))==string::npos){
		XmlRpc::XmlRpcUtil::error("HTTPParser::parse:Can not find the space in the initial line!");
		return false;
	}
	hc.methodname=line.substr(0,pos1);

	//解析path和HTTP version
	int pos2=0;
	if((pos2=line.find(SPACE,pos1+1))==string::npos){
		XmlRpc::XmlRpcUtil::error("HTTPParser::parse:Can not find the space in the initial line!");
		return false;
	}
	hc.path=line.substr(pos1+1,pos2-pos1-1);
	hc.version=line.substr(pos2+1);
	
	return true;
}

HTTPContext HTTPParser::getHc(){
	return this->hc;
}
