
#ifndef __QUERYRESULT_H_INCLUDE__
#define __QUERYRESULT_H_INCLUDE__

#include "Common.h"

class ParsedMDX;

namespace QueryComputationMethods{

class Cell 
{
public:
	Cell():value(0.0),formatString(""),isNull(false){}
	~Cell(){}

	inline string addComma( char* buf )
	{
		char tbuf[128];
		
		char* pos = strchr( buf, '.' );

		int length = pos - buf;
		if ( length <= 3 )
		{
			return string(buf);
		}
 
		length = length + length/3;

		int mod = (pos-buf)%3;
		int i = 0;
		int index = 0; 
		int count = 0;
		if ( mod != 0 )
		{
			while ( i < mod && i < length ) tbuf[i++] = buf[index++];
			tbuf[i++] = ',';
		}
		else
			length --;

		for ( ; i < length; ++i )
		{
			if ( count++ == 3 )
				tbuf[i] = ',';
			else
				tbuf[i] = buf[index++];
		}
		
		while ( *pos != '\0' )
			tbuf[i++] = *pos++;
		
		tbuf[i] = '\0';

		return string(tbuf);
	}

	string getFormatString()
	{
		
		if ( formatString == "" || formatString == "Standard" )
		{
			char buf[128];
			sprintf( buf, "%6.2f", value );
			return addComma(buf);
			
		}
		else if ( formatString == "Currency" )
		{
			return "￥"+ftos(value);
		}
		else 
		{
			int leftPart = 0;
			int rightPart = 0;
			char buf[128];

			const char* tmp = formatString.c_str();
			for ( int i = 0; i < formatString.size(); ++i )
			{
				if ( *(tmp+i) == '#' )
					leftPart++;
				else if( *(tmp+i) == '0' )
					rightPart++;
			}

			string formatStr;
			if ( rightPart == 0 )
			{
				formatStr = "%" + itos(leftPart) + "f";
				sprintf(buf,formatStr.c_str(),value);
				return string(buf);
			}
			else
			{
				formatStr = "%" +itos(leftPart) +"."+itos(rightPart)+"f";
				sprintf(buf,formatStr.c_str(),value);
				return addComma(buf);
			}
	
		}
	}
public:	
	double  value;						 ///数据单元的值
	string formatString;				 ///数据单元的格式定义
	vector<string> cellDimsVals;		 ///查询cell各维度的值
	bool isNull;						 ///查询值是否为空
};

class CellSet
{
public:
	CellSet(){}
	CellSet(ParsedMDX *parsedMDX):parsedMdx(parsedMDX){}
	~CellSet(){}

public:
	vector<Cell> Cells;					 ///数据单元集合
	ParsedMDX* parsedMdx;				 ///被解析的MDX对象
};

};
#endif