#include "./Query/RolapCCQuery.h"
#include <windows.h>


namespace QueryComputationMethods{

RolapCCQuery::RolapCCQuery( ParsedMDX* parsedMDX_t ) 
:MolapQueryComputationBase(parsedMDX_t)
{	
	string schemaName = parsedMDX_t->getSchemaName();
	string cubeName = parsedMDX_t->getCubeName();
	XSchema* xs = XSchemas::instance().getSchema(schemaName);
	DataSource* datasource = xs->getDataSource();
	string URL = datasource->getURL();
	string username = datasource->getUserName();
	string password = datasource->getPassWord();
	
	try
	{
		XODBCDatabase* InPDB = new XODBCDatabase();
		InPDB->Open(URL,username,password,XODBCDatabase::openReadOnly);
		
		aggReader = new AggDBReader(InPDB,schemaName,cubeName);
	}
	catch ( XODBCException* e )
	{
		XODBCError error;
		e->GetError(error);
		cout<<"Error: errorMessage--"<<error.GetErrorText()<<endl;
		cout<<"Error: errorID--"<<error.GetState()<<endl;
		string errorMessage = "class RolapCCQuery--Connect DA:"+URL+" with user:"+username+" password:"+password+" failed";
		throw QueryCmptException(errorMessage);
	}		
}

RolapCCQuery::RolapCCQuery( ParsedMDX* parsedMDX_t, string partitionNum ) 
:MolapQueryComputationBase(parsedMDX_t)
{
	string schemaName = parsedMDX_t->getSchemaName();
	string cubeName = parsedMDX_t->getCubeName();
	XSchema* xs = XSchemas::instance().getSchema(schemaName);
	DataSource* datasource = xs->getDataSource();
	string URL = datasource->getURL();
	string username = datasource->getUserName();
	string password = datasource->getPassWord();
	
	try
	{
		XODBCDatabase* InPDB = new XODBCDatabase();
		InPDB->Open(URL,username,password,XODBCDatabase::openReadOnly);

		aggReader = new AggDBReader(InPDB,schemaName,cubeName,partitionNum);
	}
	catch ( XODBCException* e )
	{
		XODBCError error;
		e->GetError(error);
		cout<<"Error: errorMessage--"<<error.GetErrorText()<<endl;
		cout<<"Error: errorID--"<<error.GetState()<<endl;
		string errorMessage = "class RolapCCQuery--Connect DA:"+URL+" with user:"+username+" password:"+password+" failed";
		throw QueryCmptException(errorMessage);
	}		
}

RolapCCQuery::~RolapCCQuery()
{
}

void RolapCCQuery::setCacheUpper(vector< string > upper)
{
	dimValues = upper;
}

vector<string> RolapCCQuery::getCacheUpper() const
{
	return dimValues;
}

void RolapCCQuery::pointQuery( int* qry )
{
	int i = 0;
	bool ret;
	isNull = false;
	vector<int> tmpDimValues;
	ret = static_cast<AggDBReader*>(aggReader)->lookupPoint( qry, tmpDimValues, msrValues );
	
	if ( !ret )
		isNull = true;
	else
	{
		for ( i = 0; i < dimsNum; ++i )
		{
			if( tmpDimValues[i] == 0 )
				dimValues.push_back("*");
			else
			{
				dimValues.push_back( (aggReader->getMapsVals())[i][ tmpDimValues[i] - 1 ] );
			}
		}
	}
	
}

CellSet RolapCCQuery::query()
{
	int i = 0;
	int ii = 0;
	
	//ִ�еѿ���������
	getQueryPoints( this->parsedMdx );

	//ִ�е��ѯ
	CellSet ToXMLAResult(parsedMdx);
	for ( i = 0; i < tuplesNum; ++i )
	{
		Cell cell;
		bool isValid = true;
		enterLayer = 0;

		cell.formatString = msrFormatStr[mdxMsrHdr[i%mdxMsrHdr.size()]-dimsNum];
		//��ʼ����ѯcell��ά��ֵ���ظ��û�
		for ( ii = 0; ii < dimsNum; ++ii )
		{
			cell.cellDimsVals.push_back(qryPointsDimsVals[i][ii]);
		}

		for ( ii = 0; ii < dimsNum; ++ii )
		{
			if( qryPoints[i][ii]!=0 )
			{
				++enterLayer;
			}
			if( -1 == qryPoints[i][ii] )
			{
				isValid = false;
				cell.isNull = true;
				ToXMLAResult.Cells.push_back(cell); //����ò�ѯֵ�Ƿ�������һ���յ�cell��Ϊ���صĽ��
				break;
			}
			qrycell.push_back(qryPoints[i][ii]);//�ѵ�ǰ�Ĳ�ѯcell�ŵ�������
		}
		

		if(	isValid )
		{	
			//�����������ѯ��Ӧ�Ķ�������һ��
			int posInMdxMsrHdr = ((i % (msrsLineCount * mdxMsrHdr.size()))/msrsLineCount)%(mdxMsrHdr.size());
			//����鿴��¼�ǲ����Ѿ���ѯ����������ھͶ�����Ҫ�Ķ���ֵ
			queryCellMapType::iterator findPt;
			findPt = queryCellMap.find(qrycell);
			if ( findPt == queryCellMap.end() )           //�ڲ�ѯcell���滹û�г���
			{
				pointQuery( qryPoints[i] );	
		
				//�Ѳ�ѯ�Ľ���ŵ��������
				if (isNull)
				{
					cell.isNull = true;
				}
				else
				{
					cell.value = msrValues[ mdxMsrHdr[posInMdxMsrHdr] - dimsNum ];

					msrValues.clear();						//Ϊ�´ζ����������׼��
				}
			}
			else //�Ѿ����ڸò�ѯ�ĵ���									
			{
				cell.value = (*findPt).second[ mdxMsrHdr[posInMdxMsrHdr] - dimsNum ];
			}

			//���������Ƭ�����Ҫ����Ӧ�Ĵ���Ȼ������Ϊ���ս�����ظ�XMLA
			if (slicerTuplesNum == 0) //ֱ�Ӱѻ�õĶ������뵽������Ϳ�����
			{
				ToXMLAResult.Cells.push_back(cell);
			}
			else
			{
				//����׼���Ѹò�ѯ��ֵ���뵽������У����Ǳ��뿼����Ƭ����tuples����Ŀ��������Ƭ����n��tuples
				//������е�һ������Ӧ������n�����ѯ�����Ķ���ֵ�ĺ���ɵ�
				if (i % slicerTuplesNum == 0)//��cell.value���뵽������У�����һ�������֮��Ҫ����
				{
					ToXMLAResult.Cells.push_back(cell);
				}
				else//������Ƭ�������tuples��������                         
				{
					((ToXMLAResult.Cells)[ToXMLAResult.Cells.size()-1]).value += cell.value;
				}
			}
		}
		qrycell.clear();        //���׼���洢�¸����ѯ
	}

	for(i = 0; i < tuplesNum; i++)
		delete [] qryPoints[i];
	delete [] qryPoints;

	//���ز�ѯ���
	return ToXMLAResult;
}


vector<Cell> RolapCCQuery::Cellquery()
{
	int i = 0;
	int ii = 0;
	//ִ�еѿ���������
	//getQueryPoints( this->parsedMdx );

	//ִ�е��ѯ
	vector<Cell> cells;
	for ( i = 0; i < tuplesNum; i++ )
	{
		Cell cell;
		bool isValid = true;
		enterLayer = 0;

		cell.formatString = msrFormatStr[mdxMsrHdr[i%mdxMsrHdr.size()]-dimsNum];
		//��ʼ����ѯcell��ά��ֵ���ظ��û�
		for (ii = 0; ii < dimsNum; ii ++)
		{
			cell.cellDimsVals.push_back(qryPointsDimsVals[i][ii]);
		}
		for (ii = 0; ii < dimsNum; ii++ )
		{
			if(qryPoints[i][ii]!=0)
			{
				enterLayer ++;
			}
			if( -1 == qryPoints[i][ii] )
			{
				isValid = false;
				cell.isNull = true;
				cells.push_back(cell); //����ò�ѯֵ�Ƿ�������һ���յ�cell��Ϊ���صĽ��
				break;
			} 
			qrycell.push_back(qryPoints[i][ii]);//�ѵ�ǰ�Ĳ�ѯcell�ŵ�������
		}
		
		if(	isValid )
		{	
			//�����������ѯ��Ӧ�Ķ�������һ��
			int posInMdxMsrHdr = ((i % (msrsLineCount * mdxMsrHdr.size()))/msrsLineCount)%(mdxMsrHdr.size());
			//����鿴��¼�ǲ����Ѿ���ѯ����������ھͶ�����Ҫ�Ķ���ֵ
			queryCellMapType::iterator findPt;
			findPt = queryCellMap.find(qrycell);
			if ( findPt == queryCellMap.end() )           //�ڲ�ѯcell���滹û�г���
			{
				pointQuery( qryPoints[i] );	
				//�Ѳ�ѯ�Ľ���ŵ��������
				if (isNull)
				{
					cell.isNull = true;
				}
				else
				{
					cell.value = msrValues[ mdxMsrHdr[posInMdxMsrHdr] - dimsNum ];
					
					msrValues.clear();						//Ϊ�´ζ����������׼��
				}
			}
			else //�Ѿ����ڸò�ѯ�ĵ���									
			{
				cell.value = (*findPt).second[ mdxMsrHdr[posInMdxMsrHdr] - dimsNum ];
			}

			//���������Ƭ�����Ҫ����Ӧ�Ĵ���Ȼ������Ϊ���ս�����ظ�XMLA
			if (slicerTuplesNum == 0) //ֱ�Ӱѻ�õĶ������뵽������Ϳ�����
			{
				cells.push_back(cell);
			}
			else
			{
				//����׼���Ѹò�ѯ��ֵ���뵽������У����Ǳ��뿼����Ƭ����tuples����Ŀ��������Ƭ����n��tuples
				//������е�һ������Ӧ������n�����ѯ�����Ķ���ֵ�ĺ���ɵ�
				if (i % slicerTuplesNum == 0)//��cell.value���뵽������У�����һ�������֮��Ҫ����
				{
					cells.push_back(cell);
				}
				else//������Ƭ�������tuples��������                         
				{
					((cells)[cells.size()-1]).value += cell.value;
				}
			}
		}
		qrycell.clear();        //���׼���洢�¸����ѯ
	}

	for ( i = 0; i < tuplesNum; ++i )
		delete [] qryPoints[i];
	delete [] qryPoints;

	//���ز�ѯ���
	return cells;
}

};