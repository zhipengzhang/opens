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
		cout<<"����Դ�����ڣ���"<<endl;
	}*/

	XODBCRecordset *pRs = NULL;
	l:
	/*if( !XODBCDataSource::TestDataSource(BOTH_DSN,"sqlserverSample","sa",""))
	{
			cout<<"����Դ�����ڣ���"<<endl;
	}
	else
	{
			cout<<"����Դ���ڣ���"<<endl;
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

			/* ��ȡֵ*/
			for( i = 0; i < pXRS->GetFieldCount();i++ )
			{
				string strValue;
				pXRS->GetFieldValue(i,varValue);
				
				{
					printVariant(varValue);
					cout<<"    ";
				}

				/* ����ֵ */
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

			/* ��ӵ�ǰֵ */
			pXRS->AddNew();
			system("Pause");
           
		   /* ���µ�ǰ��ֵ */
		   //pXRS->Update();

		   /* ɾ����ǰ��ֵ */
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
	//    ����ָ�������������ֶ������б���������
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
			cout<<"����Դ���Ը��£�"<<endl;
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
		cout<<"��������Դ�ɹ�!!"<<endl;
		system("pause");
		cout<<"******************************* Transaction ***********************************"<<endl;
		if(XDB.CanTransact())
		{
			try
			{
				cout<<"Begin �� Commit:"<<endl;
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
				cout<<"Begin �� RollBack::"<<endl;
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
			cout<<"Ӱ�������Ϊ��"<<XDB.GetEffectCount()<<endl;
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
	cout<<"��������Դ�� GetAllDataSourceList() "<<endl;
	for(i=0;i<(int)strDSNList.size();i++)
	{
	cout<<strDSNList[i]<<endl;
	}
	cout<<"------------------------"<<endl;
	cout<<'\n'<<endl;



	strDSNList=XODBCDataSource::GetODBCDriverList();
	cout<<"------------------------"<<endl;
	cout<<"������������ GetODBCDriverList()"<<endl;
	for(i=0;i<(int)strDSNList.size();i++)
	{
	cout<<strDSNList[i]<<endl;
	}
	cout<<"------------------------"<<endl;
	cout<<'\n'<<endl;



	strDSNList=XODBCDataSource::GetDataSourceList("SQL Server");
//	strDSNList=XODBCDataSource::GetDataSourceList("Microsoft Access Driver (*.mdb)");  
//********************************************************************************//
//  ��������ƴд�ϸ����д��"Microsoft Access Driver(*.mdb)"(�м�ȱ��һ���ո�), //
// Ҳ���޷���ȡ��������"Microsoft Access Driver (*.mdb)"��Ӧ������Դ              //
//********************************************************************************//
	cout<<"------------------------"<<endl;
	cout<<"ĳһ���������Ӧ������Դ��GetDataSourceList(SQL Server) "<<endl;
//	cout<<"ĳһ���������Ӧ������Դ��GetDataSourceList(Microsoft Access Driver (*.mdb):"<<endl;
	for(i=0;i<(int)strDSNList.size();i++)
	{
	cout<<strDSNList[i]<<endl;
	}
	cout<<"------------------------"<<endl;
	cout<<'\n'<<endl;



	cout<<"______________________"<<endl;
	cout<<"�������Դ1�� ";
	//n_DSNType ΪODBC_ADD_DSN �� ODBC_ADD_SYS_DSN
//	char * szAttributes="DSN=userdsn1\0DESCRIPTION=SQLConfigDSN Sample\0SERVER=(local)\0DATABASE=NorthWind\0\0";	
//	check = XODBCDataSource::AddDataSource(ODBC_ADD_DSN,"SQL Server",szAttributes);
//	char * szAttributes="DSN=Acessmy\0DESCRIPTION=Access Sample\0\0";	
//  check = XODBCDataSource::AddDataSource(ODBC_ADD_DSN,"Microsoft Access Driver (*.mdb)",szAttributes); //��ӳɹ���������ʧ��
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
//	�������Դ�Ƿ�ɹ������û������ݿ⣬�������ȷ����޹أ�����Ѵ�����ͬ�������������������ʧ�ܡ�     //
//                                                                                                       //
//	�����������������Ҫ�ϸ����������������ƣ���������GetODBCDriverList��ȡ�����������ƺ󣬼�����ȷ������//
//  ���������������Ӧ������Դ����ȷ����������MySQL ODBC 3.51 Driver                                     //                                               
//	�����û������������дʲôҲ��Ӱ����ӳɹ�������TestSource�и�����Դ���û��������������Ӧ���������� //
//*******************************************************************************************************//
	cout<<"______________________"<<endl;
	cout<<"�������Դ2  (SQL Server)�� ";
	//n_DSNType Ϊ ODBC_USER_DSN �� ODBC_SYSTEM_DSN �� ODBC_BOTH_DSN
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
	cout<<"�������Դ2  ( MySQL )�� ";
	//Ҫ����MySQL���洴��һ��test���ݿ⣬Ĭ�ϵ��û���root,����Ϊ��
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
	cout<<"�������Դ2 (Microsoft Access)�� ";
	//n_DSNType Ϊ ODBC_USER_DSN �� ODBC_SYSTEM_DSN �� ODBC_BOTH_DSN
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
	cout<<"�������Դ2 (Microsoft Excel)�� ";
	//n_DSNType Ϊ ODBC_USER_DSN �� ODBC_SYSTEM_DSN �� ODBC_BOTH_DSN
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
	cout<<"�������Դ2 (Microsoft dBase)�� ";
	//n_DSNType Ϊ ODBC_USER_DSN �� ODBC_SYSTEM_DSN �� ODBC_BOTH_DSN
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
	cout<<"ɾ������Դ�� ";
	//n_DSNType Ϊ ODBC_USER_DSN �� ODBC_SYSTEM_DSN �� ODBC_BOTH_DSN
	check= XODBCDataSource::RemoveDataSource(ODBC_USER_DSN,"usermxx");   //success
	//check= XODBCDataSource::RemoveDataSource(ODBC_USER_DSN,"noname");  //���noname ����ODBC.INI�ļ��У�������Ȼ��true (�μ�SQLRemoveDSNFromIni��
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
	cout<<"��������Դ�� ";
	//n_DSNType Ϊ ODBC_USER_DSN �� ODBC_SYSTEM_DSN �� ODBC_BOTH_DSN
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
	cout<<"��ȡ����Դ��Ϣ(GetDataSourceInfo)�� ";
//**********************************************************************************************//
//	���û�ж������mystring,                                                                   //
//	����ֱ�ӵ���check = XODBCDataSource::GetDataSourceInfo(ODBC_USER_DSN,"updatauser","","","","","","");     //
//	���뽫���� ���ܽ����� 3 �ӡ�const char [5]��ת��Ϊstring                                  //
//**********************************************************************************************//
	string mystring="" ;
	//n_DSNType Ϊ ODBC_USER_DSN �� ODBC_SYSTEM_DSN �� ODBC_BOTH_DSN
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
//��TestDataSource��������Դ�ɹ������AddDataSource��"updatauser","none" ,"1111"���������û����������޹�//
//	ֻҪ���Ӹ�����Դ���û��������Ӧ�����������¼���û�������һ�£�����AddDataSource�����е����ݿ����   //
//   ����������Դ�ɹ�������ʧ�� �����ݿ����Ʋ������Сд��                                                //
//	����SQL Server��¼�û�������һ��sa�û�������Ϊ6564943����һ�û���mxx,����1111(û�������û�none)       //
//	��ô����updatauser����Դ����ʱ("updatauser","sa" ,"6564943")����("updatauser","mxx" ,"1111")          //
//	�����ӳɹ�,  ("updatauser","none" ,"1111")����ʧ��                                       ��           //
//  ����MySQL,Ҫ����MySQL�д���һ��test���ݿⷽ�����ӳɹ���ϵͳĬ�ϵ��û���root,����Ϊ�� )                //              //
//********************************************************************************************************//

 // bool flag =XODBCDataSource::TestDataSource(ODBC_USER_DSN,"updatauser","sa" ,"11");    // print "fail"
    bool flag =XODBCDataSource::TestDataSource(ODBC_USER_DSN,"updatauser","sa" ,"6564943"); // print "success"
 // bool flag =XODBCDataSource::TestDataSource(ODBC_USER_DSN,"user","sa" ,"6564943"); // print "success"
//	bool flag =XODBCDataSource::TestDataSource(ODBC_USER_DSN,"changeaccess2","sa" ,"6564943");  //print "fail"
//	bool flag =XODBCDataSource::TestDataSource(ODBC_USER_DSN,"mysqladd","root" ,"");      //print "success"
//	bool flag =XODBCDataSource::TestDataSource(ODBC_USER_DSN,"usermysql","root" ,"");      //print "success"
	cout<<"________________________"<<endl;
	cout<<" ��������Դ  :";	
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