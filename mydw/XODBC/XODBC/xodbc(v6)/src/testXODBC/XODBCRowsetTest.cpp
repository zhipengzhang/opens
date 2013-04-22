#include "XODBCRowset.h"
#include <iostream>

void test()
{
	int nLength = 10;
	int nSize = 50;
	char * * ppChar = new char*[nLength];
	for(int  i = 0; i < nLength; i++)
	{
		ppChar[i] = new char[nSize];
		strcpy(ppChar[i],"yyee");
	}
	
	for(i = 0; i < nLength ; i++)
	{
		cout<<ppChar[i]<<endl;
	}
	
	char * * ppThar = ppChar;
	for(i = 0; i < nLength ; i++)
	{
		cout<<ppThar[i]<<endl;
		//delete ppThar[i];
	}
	
	for(i = 0; i < nLength ; i++)
	{
		cout<<ppChar[i]<<endl;
		delete ppChar[i];
	}
}


void main()
{
	
	XODBCRowset xrow;
	//if(xrow.Connect("sql","sa","123456"))
	if(xrow.Connect("sqlserverSample","sa",""))
	{
		cout<<"Concected!!"<<endl;
		for( int i = 0; i <= 50 ; i++)
		{
			int nRowset = 0;
			cout<<"Please input the RowsetCount"<<endl;
			cin>>nRowset;
			if (xrow.SetRowset(nRowset))
			{
				//xrow.OpenQuery("select WZSJ from WZ");
				if(xrow.OpenQuery("select CategoryName from Categories"))
				{
					xrow.CloseQuery();
				}
			}
		}
	}
	else
	{
		return ;
	}

	
}