#include "testXODBC.h"

int main()
{
	try
	{
		//testXODBCRecordset();
		//testSetpos();
		testDBSource();
		//testXODBCDatabase();
		//testXODBCDataSource();
		//testSQLType();
	}
	catch(XODBCException e)
	{
		XODBCError error;
		e.GetError(error);
		cout<<error.GetErrorText().c_str()<<endl;
		cout<<error.GetState()<<endl;
		return 0;
	}
	return 0;
}

void testSQLType()
{
	string strDataType = "";
		
	string strSQLType = XODBCDataSource::GetSQLType(DB_SQLSERVER,SQL_LONGVARCHAR);
	cout<<strSQLType.c_str()<<endl;
	strSQLType = XODBCDataSource::GetSQLType(DB_SQLSERVER,SQL_LONGVARCHAR);
	cout<<strSQLType.c_str()<<endl;
	strSQLType = XODBCDataSource::GetSQLType(DB_SQLSERVER,SQL_LONGVARCHAR);
	cout<<strSQLType.c_str()<<endl;
	strSQLType = XODBCDataSource::GetSQLType(DB_SQLSERVER,SQL_LONGVARCHAR);
	cout<<strSQLType.c_str()<<endl;
	strSQLType = XODBCDataSource::GetSQLType(DB_SQLSERVER,SQL_LONGVARCHAR);
	cout<<strSQLType.c_str()<<endl;
	strSQLType = XODBCDataSource::GetSQLType(DB_SQLSERVER,SQL_LONGVARCHAR);
	cout<<strSQLType.c_str()<<endl;

	
}

void testDBSource()
{
	/*if( !XODBCDataSource::TestDataSource(BOTH_DSN,"sql","sa",""))
	{
		cout<<"数据源不存在！！"<<endl;
	}*/

	XODBCRecordset *pRs = NULL;
	l:
	/*if( !XODBCDataSource::TestDataSource(BOTH_DSN,"sqlserverSample","sa",""))
	{
			cout<<"数据源不存在！！"<<endl;
	}
	else
	{
			cout<<"数据源存在！！"<<endl;
	}
	system("pause");*/
	XODBCDatabase db;
	try
	{
			if(db.Open("sql","sa","sa"))
			{
				pRs = new XODBCRecordset(&db);
			}
	}
	catch(XODBCException e)
	{
			XODBCError error;
			e.GetError(error);
			cout<<error.GetErrorText().c_str()<<endl;
			cout<<error.GetState()<<endl;
			
	}
	system("pause");
	delete pRs;
	goto l;

}

void testSetpos()
{
	//XODBCError XError;
	XODBCRecordset * pXRS;
	string strSQL;
	int i = 0;
	XDBVariant varValue;
	XFieldInfo xfInfo;


	pXRS = new XODBCRecordset("NorthWind","sa","",XODBCDatabase::openCanUpdate);

	strSQL = "select * from strTest";
	if( pXRS->Open( XODBCRecordset::dynamic,strSQL) )
	{
		long nCount = 0;

		do
		{
			for( i = 0;i < pXRS->GetFieldCount(); i++)
			{
				pXRS->GetFieldInfo(i,xfInfo);
				cout<<xfInfo.m_strName<<"    ";
			}
			cout<<endl;

			/* 获取值*/
			for( i = 0; i < pXRS->GetFieldCount();i++ )
			{
				string strValue;
				pXRS->GetFieldValue(i,varValue);
				
				{
					printVariant(varValue);
					cout<<"    ";
				}

				/* 设置值 */
				switch(varValue.m_nType)
				{
			        case XDBVT_BOOL:
					varValue.m_boolVal = 1;
					break;

				    case XDBVT_UCHAR:
					varValue.m_chVal = 'c';
					break;

				case XDBVT_SHORT:
					varValue.m_shVal = 0;
					break;

				case XDBVT_LONG:
					varValue.m_lVal = 0;
					break;

				case XDBVT_SINGLE:
					varValue.m_fltVal = 0.0;
					break;

				case XDBVT_DOUBLE:
					varValue.m_dblVal = 0.0;
					break;
				case XDBVT_LONGLONG:
				    varValue.m_llVal = 0;
					break;
				case XDBVT_DATE:
					varValue.m_dateVal.year  = 2007;
					varValue.m_dateVal.month = 1;
					varValue.m_dateVal.day   =  29;
					break;
				case XDBVT_TIME:
					varValue.m_timeVal.hour   = 20;
					varValue.m_timeVal.minute = 20;
					varValue.m_timeVal.second = 20;
					break;
				case XDBVT_TIMESTAMP:
					varValue.m_tsVal.year   = 2007;
					varValue.m_tsVal.month  = 1;
					varValue.m_tsVal.day    = 29;
					varValue.m_tsVal.hour   = 20;
					varValue.m_tsVal.minute = 20;
					varValue.m_tsVal.second = 20;
					break;

				case XDBVT_STRING:
					varValue.m_stringVal = "";
					break;

				case XDBVT_WSTRING:
				    varValue.m_wstringVal = L"";
					break;

				case XDBVT_BINARY:
					memcpy(varValue.m_binaryVal.GetBuffer(),"",0);
					break;
				default:
					break;
				}
				pXRS->SetFieldValue(i,varValue);
			}

			/* 添加当前值 */
			pXRS->AddNew();
			system("Pause");
           
		   /* 更新当前行值 */
		   //pXRS->Update();

		   /* 删除当前行值 */
			//pXRS->Delete();

		   pXRS->MoveNext();
		   nCount++;
		   if( nCount == 10 )
		   {
				//break;
		   }
		}while( !pXRS->IsEOF() );
	}

	if(pXRS->IsOpen())
	{
		pXRS->Close();
	}
}

void testXODBCRecordset()
{
	XODBCError XError;
	XODBCDatabase XDB;
	string strSQL;


	cout<<"**************************************** Test XODBCRecordset *********************************"<<endl;
	//XDB.Open("NorthWind","","",XODBCDatabase::openReadOnly);
	
	
	try
	{
		XDB.OpenEx("DSN=NorthWind;",XODBCDatabase::openReadOnly);
		if(XDB.IsOpen())
		{
			string strDBName = XDB.GetDatabaseName();
			cout<<"DB Name is "<<strDBName.c_str()<<endl;
		}
	}
    catch(XODBCException e)
	{
		XODBCError error;
		e.GetError(error);
		cout<<error.GetErrorText().c_str()<<endl;
		cout<<error.GetState()<<endl;
		return;
	}
	XODBCRecordset XRS(&XDB);
	//XODBCRecordset XRS("North","","",XODBCDatabase::openReadOnly);
	try
	{
		cout<<"***************************** Table List ********************************"<<endl;
		vector<string> tableList;
		tableList = XRS.GetTableList();
		for(int i = 0;i < (int)tableList.size(); i++)
		{
			cout<<tableList.at(i).c_str()<<endl;
		}
	}
	catch(XODBCException e)
	{
		XODBCError error;
		e.GetError(error);
		cout<<error.GetErrorText().c_str()<<endl;
		cout<<error.GetState()<<endl;
	}
	cout<<endl;
	system("Pause");

	try
	{
		cout<<"**************************** Open *************************************"<<endl;
		strSQL = "Select * from Products;Select * from Orders";
		//strSQL = "Select * from strTest";
		cout<<"*************************** Set Max Record Count ***********************"<<endl;
		XRS.SetMaxRecordCount(10);
		if(XRS.Open(XODBCRecordset::forwardOnly,strSQL) )
		{
			XFieldInfo xfInfo;
			XDBVariant varValue;
			int i;
			cout<<"***************** GetFieldCount And GetFieldInfo **********************"<<endl;
			for( i = 0;i < XRS.GetFieldCount(); i++)
			{
				XRS.GetFieldInfo(i,xfInfo);
				cout<<xfInfo.m_strName<<"    ";
			}
			cout<<endl;
			cout<<"******************* GetFieldValue as XDBVariant ************************"<<endl;
			do
			{
				for( i = 0; i < XRS.GetFieldCount();i++ )
				{
					string strValue;
					XRS.GetFieldValue(i,varValue);
					printVariant(varValue);
					cout<<"    ";
					varValue.Clear();
				}
				cout<<endl;
				//XRS.Move(2,FETCH_RELATIVE);
				XRS.MoveNext();
			}while( !XRS.IsEOF() );

			cout<<endl;
			system("Pause");
			cout<<"**************************** FlushResultSet *************************************"<<endl;
			while( XRS.FlushResultSet())
			{
				for( i = 0;i < XRS.GetFieldCount(); i++)
				{
					XRS.GetFieldInfo(i,xfInfo);
					cout<<xfInfo.m_strName<<"    ";
				}
				cout<<endl;
				cout<<"******************* GetFieldValue as String ************************"<<endl;
				do
				{
					for( i = 0; i < XRS.GetFieldCount();i++ )
					{
						string strValue;
						XRS.GetFieldValue((int)i,strValue);
						cout<<strValue.c_str();
						cout<<"    ";
					}
					cout<<endl;
					XRS.MoveNext();
				}while(  !XRS.IsEOF() );
			}
		}
	}
	catch(XODBCException e)
	{
		XODBCError error;
		e.GetError(error);
		cout<<error.GetErrorText().c_str()<<endl;
		cout<<error.GetState()<<endl;
	}

	if( XRS.IsOpen())
	{
		XRS.Close();
	}
	cout<<endl;
	system("Pause");


	cout<<"********************************** Open **************************************"<<endl;
	try
	{
		XRS.SetMaxRecordCount(10);
		strSQL = "Select * from Orders";// where OrderID >= 10993 and  OrderID<= 11000";
		//strSQL = "Select * from strTest";
		if( XRS.Open(XODBCRecordset::snapshot,strSQL) )
		{
			XFieldInfo xfInfo;
			XDBVariant varValue;
			int i;
			for( i = 0;i < XRS.GetFieldCount(); i++)
			{
				XRS.GetFieldInfo(i,xfInfo);
				cout<<xfInfo.m_strName<<"    ";
			}
			cout<<endl;
			
			XRS.MoveFirst();
			cout<<"******************* GetFieldValue as Unicode String ************************"<<endl;
			do
			{
				for( i = 0; i < XRS.GetFieldCount();i++ )
				{
					string strValue;
					XRS.GetFieldValue((int)i,strValue);
					//printVariant(varValue);
					cout<<strValue.c_str();
					cout<<"    ";
				}
				cout<<endl;
				XRS.MoveNext();
			}while( !XRS.IsEOF());

			cout<<endl;
			system("Pause");
			
			cout<<"********************************** Requery **************************************"<<endl;
			if(XRS.Requery())
			{
				XFieldInfo xfInfo;
				XDBVariant varValue;
				int i;
				for( i = 0;i < XRS.GetFieldCount(); i++)
				{
					XRS.GetFieldInfo(i,xfInfo);
					cout<<xfInfo.m_strName<<"    ";
				}
				cout<<endl;
				string strValue;
				wstring wstrValue;
				XRS.MoveFirst();
				do
				{
					for( i = 0; i < XRS.GetFieldCount();i++ )
					{
						XRS.GetFieldValue((int)i,wstrValue);
						//printVariant(wstrValue);
						printWChar(wstrValue.c_str());
						cout<<"    ";
					}
					cout<<endl;
					XRS.MoveNext();
				}while( !XRS.IsEOF());
			}
		}
	}
	catch(XODBCException e)
	{
		XODBCError error;
		e.GetError(error);
		cout<<error.GetErrorText().c_str()<<endl;
		cout<<error.GetState()<<endl;
	}

	if( XRS.IsOpen())
	{
		XRS.Close();
	}
	cout<<endl;
	system("Pause");


	/*try
	{*/
	//	cout<<"********************************** Index List **************************************"<<endl;
	//	
	//	vector<string> strIndexList;
	//	vector<short>  nIndexTypeList;
	//	vector<short>  nIsUniqueList;  
	//	strIndexList = XRS.GetIndexList("db",nIsUniqueList,nIndexTypeList);

	//	/*
	//	vector<string> GetIndexList(string strTableName, vector<string> &strColumnNameList,vector<short> &nIsUniqueList, vector<short> &nIndexTypeList);
	//    返回指定表有索引的字段名名列表及索引类型
	//*/
	//	for(int i = 0;i < (int)strIndexList.size(); i++)
	//	{
	//		cout<<strIndexList.at(i).c_str()<<"   ";
	//		if( nIsUniqueList.at(i) == SQL_TRUE)
	//		{
	//			cout<<"Unique Index"<<"   ";
	//		}
	//		else
	//		{
	//			cout<<"Not Unique Index"<<"   ";
	//		}
	//		switch( (int)nIndexTypeList.at(i))
	//		{
	//		case SQL_INDEX_CLUSTERED:
	//			cout<<"Clustered Index"<<endl;
	//			break;
	//		case SQL_INDEX_HASHED: 
	//			cout<<"Hashed Index"<<endl;
	//			break;
	//		default:
	//			cout<<"Unknown Index"<<endl;
	//			break;
	//		}
	//	}
	//}
	//catch(XODBCException e)
	//{
	//	XODBCError error;
	//	e.GetError(error);
	//	cout<<error.GetErrorText().c_str()<<endl;
	//	cout<<error.GetState()<<endl;
	//}
	//cout<<endl;
	//system("pause");
	try
	{
		cout<<"********************************** Primary Key List **************************************"<<endl;
		vector<string> strPKList;
		strPKList = XRS.GetPrimaryKeyList("Products");
		for(int i = 0;i < (int)strPKList.size(); i++)
		{
			cout<<strPKList.at(i).c_str()<<endl;
		}
	}
	catch(XODBCException e)
	{
		XODBCError error;
		e.GetError(error);
		cout<<error.GetErrorText().c_str()<<endl;
		cout<<error.GetState()<<endl;
	}
	cout<<endl;
	system("pause");

	try
	{
		cout<<"********************************** Foreign Key List **************************************"<<endl;
		vector<string> strFKList;
		vector<string> strPKTableNameList;
		strFKList = XRS.GetForeignKeyList((string)"Products",strPKTableNameList);
		for(int i = 0;i < (int)strFKList.size(); i++)
		{
			cout<<strFKList.at(i).c_str()<<"    ";
			cout<<strPKTableNameList.at(i).c_str()<<endl;
		}
	}
	catch(XODBCException e)
	{
		XODBCError error;
		e.GetError(error);
		cout<<error.GetErrorText().c_str()<<endl;
		cout<<error.GetState()<<endl;
	}
	cout<<endl;
	system("pause");
	

	if( XRS.IsOpen())
	{
		XRS.Close();
	}

	if(XDB.IsOpen())
	{
		XDB.Close();
	}
}


void testXODBCDatabase()
{
	XODBCDatabase XDB;
	XODBCRecordset * XRS1;
	XODBCRecordset * XRS2;
    cout<<"****************************** Test XODBCDatabase ********************************"<<endl;
	try
	{
		cout<<"*********************************** OpenEx ***************************************"<<endl;
		XDB.OpenEx("DSN=sql;UID=sa",XODBCDatabase::openReadOnly | XODBCDatabase::openCanUpdate);
	}
	catch(XODBCException e)
	{
		XODBCError error;
		e.GetError(error);
		cout<<error.GetErrorText().c_str()<<endl;
		cout<<error.GetState()<<endl;
		return ;
	}
	if(XDB.IsOpen())
	{
		cout<<"\n*********************************** GetDatabaseName ***************************************"<<endl;
		string strDBName = XDB.GetDatabaseName();
		
		cout<<"DB Name is "<<strDBName.c_str()<<endl;
		string strCon = XDB.GetConnectString();
		cout<<"*********************************** GetConnect ***************************************"<<endl;
		cout<<"Connection String is "<<strCon.c_str()<<endl;
		cout<<"*********************************** CanUpdate ***************************************"<<endl;
		if(XDB.CanUpdate())
		{
			cout<<"数据源可以更新！"<<endl;
		}
		cout<<"*********************************** Close ***************************************"<<endl;

		XDB.Close();
		system("pause");
	}
	
	cout<<"*********************************** Open ***************************************"<<endl;
	try{
		XDB.Open("NorthWind","sa","6564943",XODBCDatabase::openReadOnly | XODBCDatabase::openCanUpdate);
	}
	catch(XODBCException e)
	{
		XODBCError error;
		e.GetError(error);
		cout<<error.GetErrorText().c_str()<<endl;
		cout<<error.GetState()<<endl;
		return ;
	}

	if(XDB.IsOpen())
	{
		cout<<"连接数据源成功!!"<<endl;
		system("pause");
		cout<<"******************************* Transaction ***********************************"<<endl;
		if(XDB.CanTransact())
		{
			try
			{
				cout<<"Begin － Commit:"<<endl;
				XDB.BeginTrans();
				XDB.ExecuteSQL("delete from nullTable where intCol > 16");
				//XDB.ExecuteSQL("Select * from nullTable; Select * from orders");
				XDB.CommitTrans();
				//XDB.ExecuteSQL("Select * from Orders");
			}
			catch(XODBCException e)
			{
				XODBCError error;
				e.GetError(error);
				cout<<error.GetErrorText().c_str()<<endl;
				cout<<error.GetState()<<endl;
			}
			
			try
			{
				cout<<"Begin － RollBack::"<<endl;
				XDB.BeginTrans();
				XDB.ExecuteSQL("insert into nullTable values(21, \'yes\')");
				XDB.Rollback();
			}
			catch(XODBCException e)
			{
				XODBCError error;
				e.GetError(error);
				cout<<error.GetErrorText().c_str()<<endl;
				cout<<error.GetState()<<endl;
			}
		}
		system("pause");
		try
		{
			cout<<"************************* ExecuteSQL And GetEffectCount *************************"<<endl;
			XDB.ExecuteSQL("Update nullTable set chCol = \'yes\' where intCol > 15");
			cout<<"影响的行数为："<<XDB.GetEffectCount()<<endl;
		}
		catch(XODBCException e)
		{
			XODBCError error;
			e.GetError(error);
			cout<<error.GetErrorText().c_str()<<endl;
			cout<<error.GetState()<<endl;
		}
	}
    
	system("pause");
	XRS1 = new XODBCRecordset(&XDB);
	XRS1->Open(XODBCRecordset::snapshot,"select * from orders");
	
	XRS2 = new XODBCRecordset(&XDB);
	XRS2->Open(XODBCRecordset::dynamic,"select * from products");

	XODBCRecordset  XRS3(&XDB);
	XODBCRecordset  XRS4(&XDB);
	XODBCRecordset  XRS5(&XDB);

	if(XDB.IsOpen())
	{
		cout<<"********************************* Close *********************************"<<endl;
		XDB.Close();
	}
	cout<<"******************* Destroy And Remove the Recordsets List *********************"<<endl;


}


void printWChar(const wchar_t * wstr)
{
	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE),wstr,(DWORD)wcslen(wstr), 0,NULL); 
}

void printVariant(XDBVariant varValue)
{
		if( varValue.m_bNull)
		{
			cout<<"<NULL>"<<endl;;
		}
			switch(varValue.m_nType)
			{
			   case XDBVT_BOOL:
					cout<<varValue.m_boolVal;
					break;

				case XDBVT_UCHAR:
					cout<<(int) varValue.m_chVal;
					break;

				case XDBVT_SHORT:
					cout<<varValue.m_shVal;
					break;

				case XDBVT_LONG:
					cout<<varValue.m_lVal;
					break;

				case XDBVT_SINGLE:
					cout<<varValue.m_fltVal;
					break;

				case XDBVT_DOUBLE:
					cout<<varValue.m_dblVal;
					break;
				case XDBVT_LONGLONG:
					printf("%I64d",varValue.m_llVal);
					break;
				case XDBVT_DATE:
					printf("%d-%d-%d",varValue.m_dateVal.year,varValue.m_dateVal.month,varValue.m_dateVal.day);
					break;
				case XDBVT_TIME:
					printf("%d:%d:%d",varValue.m_timeVal.hour,varValue.m_timeVal.minute,varValue.m_timeVal.second);
					break;
				case XDBVT_TIMESTAMP:
					printf("%d-%d-%d ",varValue.m_tsVal.year,varValue.m_tsVal.month,varValue.m_tsVal.day);
					printf("%d:%d:%d",varValue.m_tsVal.hour,varValue.m_tsVal.minute,varValue.m_tsVal.second);
					break;

				case XDBVT_STRING:
					cout<<varValue.m_stringVal.c_str();
					break;

				case XDBVT_WSTRING:
					//wprintf(L"%s",varValue.m_pwstringVal->c_str());
					{
						WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE),varValue.m_wstringVal.c_str(),(DWORD)wcslen(varValue.m_wstringVal.c_str()), 0,NULL); 						break;
					}

				case XDBVT_BINARY:
					{
					void * p = malloc(varValue.m_binaryVal.GetLength() + 1);
					memcpy(p,varValue.m_binaryVal.GetBuffer(),varValue.m_binaryVal.GetLength());
					long * i ;
					i = (long *)p;
					{
						cout<<p;
						//cout<< *i <<endl;
					}
					free(p);
					break;
					}

				default:
					break;
			}

}

void testXODBCDataSource()
{

//  SQLCHAR szDSN[256], szDesc[256];
	bool check=false;
	int i;
	vector<string> strDSNList; 
	

	strDSNList=XODBCDataSource::GetAllDataSourceList();
	cout<<"------------------------"<<endl;
	cout<<"所有数据源： GetAllDataSourceList() "<<endl;
	for(i=0;i<(int)strDSNList.size();i++)
	{
	cout<<strDSNList[i]<<endl;
	}
	cout<<"------------------------"<<endl;
	cout<<'\n'<<endl;



	strDSNList=XODBCDataSource::GetODBCDriverList();
	cout<<"------------------------"<<endl;
	cout<<"所有驱动程序： GetODBCDriverList()"<<endl;
	for(i=0;i<(int)strDSNList.size();i++)
	{
	cout<<strDSNList[i]<<endl;
	}
	cout<<"------------------------"<<endl;
	cout<<'\n'<<endl;



	strDSNList=XODBCDataSource::GetDataSourceList("SQL Server");
//	strDSNList=XODBCDataSource::GetDataSourceList("Microsoft Access Driver (*.mdb)");  
//********************************************************************************//
//  驱动程序拼写严格，如果写成"Microsoft Access Driver(*.mdb)"(中间缺少一个空格), //
// 也将无法获取驱动程序"Microsoft Access Driver (*.mdb)"对应的数据源              //
//********************************************************************************//
	cout<<"------------------------"<<endl;
	cout<<"某一驱动程序对应的数据源：GetDataSourceList(SQL Server) "<<endl;
//	cout<<"某一驱动程序对应的数据源：GetDataSourceList(Microsoft Access Driver (*.mdb):"<<endl;
	for(i=0;i<(int)strDSNList.size();i++)
	{
	cout<<strDSNList[i]<<endl;
	}
	cout<<"------------------------"<<endl;
	cout<<'\n'<<endl;



	cout<<"______________________"<<endl;
	cout<<"添加数据源1： ";
	//n_DSNType 为ODBC_ADD_DSN 或 ODBC_ADD_SYS_DSN
//	char * szAttributes="DSN=userdsn1\0DESCRIPTION=SQLConfigDSN Sample\0SERVER=(local)\0DATABASE=NorthWind\0\0";	
//	check = XODBCDataSource::AddDataSource(ODBC_ADD_DSN,"SQL Server",szAttributes);
//	char * szAttributes="DSN=Acessmy\0DESCRIPTION=Access Sample\0\0";	
//  check = XODBCDataSource::AddDataSource(ODBC_ADD_DSN,"Microsoft Access Driver (*.mdb)",szAttributes); //添加成功，但连接失败
	char * szAttributes="DSN=usermysql\0DESCRIPTION=MySQL Sample\0SERVER=localhost\0DATABASE=test\0\0";	
    check = XODBCDataSource::AddDataSource(ODBC_ADD_DSN,"MySQL ODBC 3.51 Driver",szAttributes);
    
	 if(check==true)
	 {
		cout<<"success"<<endl;
	 }
	 else
	 {
	 	cout<<"fail"<<endl;
	 }
	cout<<"____________________"<<endl;
	cout<<'\n'<<endl;


//*******************************************************************************************************//
//	添加数据源是否成功　与用户，数据库，密码等正确与否无关，如果已存在相同的驱动程序名，则添加失败。     //
//                                                                                                       //
//	对于驱动程序参数，要严格遵造驱动程序名称，建议先用GetODBCDriverList获取驱动程序名称后，检验正确的驱动//
//  程序名称再添加相应的数据源。正确的驱动程序MySQL ODBC 3.51 Driver                                     //                                               
//	对于用户名，密码随便写什么也不影响添加成功，但在TestSource中该数据源的用户名密码必须与相应的驱动程序 //
//*******************************************************************************************************//
	cout<<"______________________"<<endl;
	cout<<"添加数据源2  (SQL Server)： ";
	//n_DSNType 为 ODBC_USER_DSN ， ODBC_SYSTEM_DSN 或 ODBC_BOTH_DSN
	 check =XODBCDataSource::AddDataSource(ODBC_USER_DSN,"SQL Server","user","Northwind","(local)");
	 if(check==true)
	 {
		cout<<"success"<<endl;
	 }
	else
	{
		cout<<"fail"<<endl;
	}
	cout<<"____________________"<<endl;
	cout<<"添加数据源2  ( MySQL )： ";
	//要先在MySQL里面创建一个test数据库，默认的用户是root,密码为空
	check =XODBCDataSource::AddDataSource(ODBC_USER_DSN,"MySQL ODBC 3.51 Driver","mysqladd","test","localhost","root");
//	check =XODBCDataSource::AddDataSource(ODBC_USER_DSN,"MySQL Driver","mysqluser2","test","localhost","root"); 

	 if(check==true)
	 {
		cout<<"success"<<endl;
	 }
	else
	{
		cout<<"fail"<<endl;
	}
	cout<<"____________________"<<endl;
	cout<<"添加数据源2 (Microsoft Access)： ";
	//n_DSNType 为 ODBC_USER_DSN ， ODBC_SYSTEM_DSN 或 ODBC_BOTH_DSN
	check =XODBCDataSource::AddDataSource(ODBC_USER_DSN,"Microsoft Access Driver (*.mdb)","changeaccess2","E:\\access.mdb","","sa","6564943","micro access");
	 if(check==true)
	 {
		cout<<"success"<<endl;
	 }
	else
	{
		cout<<"fail"<<endl;
	}
	cout<<"____________________"<<endl;
	cout<<"添加数据源2 (Microsoft Excel)： ";
	//n_DSNType 为 ODBC_USER_DSN ， ODBC_SYSTEM_DSN 或 ODBC_BOTH_DSN
	check =XODBCDataSource::AddDataSource(ODBC_USER_DSN,"Microsoft Excel Driver (*.xls)","changeexcel","E:\\excel.mdb","","sa","1111","micro access");
	 if(check==true)
	 {
		cout<<"success"<<endl;
	 }
	else
	{
		cout<<"fail"<<endl;
	}
	cout<<"____________________"<<endl;
	cout<<"添加数据源2 (Microsoft dBase)： ";
	//n_DSNType 为 ODBC_USER_DSN ， ODBC_SYSTEM_DSN 或 ODBC_BOTH_DSN
	check =XODBCDataSource::AddDataSource(ODBC_USER_DSN,"Microsoft dBase Driver (*.dbf)","changedBase","E:\\dBase.dbf","","sa","1111","micro access");
	 if(check==true)
	 {
		cout<<"success"<<endl;
	 }
	else
	{
		cout<<"fail"<<endl;
	}
	cout<<"____________________"<<endl;
	cout<<'\n'<<endl;




	cout<<"______________________"<<endl;
	cout<<"删除数据源： ";
	//n_DSNType 为 ODBC_USER_DSN ， ODBC_SYSTEM_DSN 或 ODBC_BOTH_DSN
	check= XODBCDataSource::RemoveDataSource(ODBC_USER_DSN,"usermxx");   //success
	//check= XODBCDataSource::RemoveDataSource(ODBC_USER_DSN,"noname");  //如果noname 不在ODBC.INI文件中，返回仍然是true (参见SQLRemoveDSNFromIni）
	//check= XODBCDataSource::RemoveDataSource(ODBC_USER_DSN,"changeaccess2");    //success
	if(check==true)
	{
		cout<<"success"<<endl;
	}
	else
	{
		cout<<"fail"<<endl;
	}
	cout<<"____________________"<<endl;
	cout<<'\n'<<endl;



	cout<<"______________________"<<endl;
	cout<<"更新数据源： ";
	//n_DSNType 为 ODBC_USER_DSN ， ODBC_SYSTEM_DSN 或 ODBC_BOTH_DSN
	//check = XODBCDataSource::UpdateDataSource(ODBC_USER_DSN,"changeexcel","Microsoft Excel Driver (*.xls)","excelnew","","E:\\excel.mdb","sa","6564943", "");
	//check = XODBCDataSource::UpdateDataSource(ODBC_USER_DSN,"changeexcel","SQL Server","sqluser","(local)","NorthWind","sa","6564943", "");
	check = XODBCDataSource::UpdateDataSource(ODBC_USER_DSN,"userdsn1","SQL Server","updatauser","(local)","Northwind","sa","6564943", "");
	if(check==true)
	{
		cout<<"success"<<endl;
	}
	else
	{
		cout<<"fail"<<endl;
	}
	cout<<"____________________"<<endl;
	cout<<'\n'<<endl;



	cout<<"______________________"<<endl;
	cout<<"获取数据源信息(GetDataSourceInfo)： ";
//**********************************************************************************************//
//	如果没有定义变量mystring,                                                                   //
//	而是直接调用check = XODBCDataSource::GetDataSourceInfo(ODBC_USER_DSN,"updatauser","","","","","","");     //
//	编译将出错： 不能将参数 3 从“const char [5]”转换为string                                  //
//**********************************************************************************************//
	string mystring="" ;
	//n_DSNType 为 ODBC_USER_DSN ， ODBC_SYSTEM_DSN 或 ODBC_BOTH_DSN
	check = XODBCDataSource::GetDataSourceInfo(ODBC_USER_DSN,"updatauser",mystring,mystring,mystring,mystring,mystring,mystring);
	if(check==true)
	{
		cout<<"success"<<endl;
	}
	else  
	{
		cout<<"fail"<<endl;
	}
	cout<<"________________________"<<endl;



	string st= XODBCDataSource:: GetDriverName(ODBC_USER_DSN,"updatauser");
	cout<<" GetDriverName :"<<st<<endl;

	st= XODBCDataSource::GetServerName(ODBC_USER_DSN,"updatauser");
	cout<<" GetServerName :"<<st<<endl;

	st= XODBCDataSource::GetDBName(ODBC_USER_DSN,"updatauser");
	cout<<" GetDBName :"<<st<<endl;

	st= XODBCDataSource::GetUserName(ODBC_USER_DSN,"updatauser");
	cout<<" GetUserName :"<<st<<endl;

	st= XODBCDataSource::GetPassword(ODBC_USER_DSN,"updatauser");
	cout<<" GetPassword:"<<st<<endl;

	st= XODBCDataSource::GetDesc(ODBC_USER_DSN,"updatauser");
	cout<<" GetDescription:"<<st<<endl;



//********************************************************************************************************//
//　TestDataSource连接数据源成功与否　与AddDataSource（"updatauser","none" ,"1111"）参数的用户名，密码无关//
//	只要连接该数据源的用户密码与对应的驱动程序登录的用户密码相一致，并且AddDataSource参数中的数据库存在   //
//   即连接数据源成功，否则失败 （数据库名称不区别大小写）                                                //
//	（如SQL Server登录用户中设置一个sa用户，密码为6564943，另一用户是mxx,密码1111(没有设置用户none)       //
//	那么测试updatauser数据源连接时("updatauser","sa" ,"6564943")或者("updatauser","mxx" ,"1111")          //
//	都连接成功,  ("updatauser","none" ,"1111")连接失败                                       　           //
//  对于MySQL,要先在MySQL中创建一个test数据库方可连接成功（系统默认的用户是root,密码为空 )                //              //
//********************************************************************************************************//

 // bool flag =XODBCDataSource::TestDataSource(ODBC_USER_DSN,"updatauser","sa" ,"11");    // print "fail"
    bool flag =XODBCDataSource::TestDataSource(ODBC_USER_DSN,"updatauser","sa" ,"6564943"); // print "success"
 // bool flag =XODBCDataSource::TestDataSource(ODBC_USER_DSN,"user","sa" ,"6564943"); // print "success"
//	bool flag =XODBCDataSource::TestDataSource(ODBC_USER_DSN,"changeaccess2","sa" ,"6564943");  //print "fail"
//	bool flag =XODBCDataSource::TestDataSource(ODBC_USER_DSN,"mysqladd","root" ,"");      //print "success"
//	bool flag =XODBCDataSource::TestDataSource(ODBC_USER_DSN,"usermysql","root" ,"");      //print "success"
	cout<<"________________________"<<endl;
	cout<<" 测试数据源  :";	
	if(flag==true)
	{
		cout<<"success"<<endl;
	}
	else
	{
		cout<<"fail"<<endl;
	}
	cout<<"________________________"<<endl;
}