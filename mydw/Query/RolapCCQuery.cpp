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
	
	//执行笛卡尔积计算
	getQueryPoints( this->parsedMdx );

	//执行点查询
	CellSet ToXMLAResult(parsedMdx);
	for ( i = 0; i < tuplesNum; ++i )
	{
		Cell cell;
		bool isValid = true;
		enterLayer = 0;

		cell.formatString = msrFormatStr[mdxMsrHdr[i%mdxMsrHdr.size()]-dimsNum];
		//初始化查询cell的维度值返回给用户
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
				ToXMLAResult.Cells.push_back(cell); //如果该查询值非法，插入一个空的cell作为返回的结果
				break;
			}
			qrycell.push_back(qryPoints[i][ii]);//把当前的查询cell放到向量中
		}
		

		if(	isValid )
		{	
			//计算出该条查询对应的度量是哪一个
			int posInMdxMsrHdr = ((i % (msrsLineCount * mdxMsrHdr.size()))/msrsLineCount)%(mdxMsrHdr.size());
			//下面查看记录是不是已经查询过，如果存在就读出需要的度量值
			queryCellMapType::iterator findPt;
			findPt = queryCellMap.find(qrycell);
			if ( findPt == queryCellMap.end() )           //在查询cell里面还没有出现
			{
				pointQuery( qryPoints[i] );	
		
				//把查询的结果放到结果集中
				if (isNull)
				{
					cell.isNull = true;
				}
				else
				{
					cell.value = msrValues[ mdxMsrHdr[posInMdxMsrHdr] - dimsNum ];

					msrValues.clear();						//为下次读入度量做好准备
				}
			}
			else //已经存在该查询的点了									
			{
				cell.value = (*findPt).second[ mdxMsrHdr[posInMdxMsrHdr] - dimsNum ];
			}

			//如果存在切片轴度量要做相应的处理然后再作为最终结果返回给XMLA
			if (slicerTuplesNum == 0) //直接把获得的度量放入到结果集就可以了
			{
				ToXMLAResult.Cells.push_back(cell);
			}
			else
			{
				//下面准备把该查询的值加入到结果集中，但是必须考虑切片轴中tuples的数目，加入切片轴有n个tuples
				//结果集中的一个度量应该是由n个点查询产生的度量值的和组成的
				if (i % slicerTuplesNum == 0)//把cell.value加入到结果集中，增加一个新项，但之后还要迭加
				{
					ToXMLAResult.Cells.push_back(cell);
				}
				else//进行切片轴的所有tuples度量迭加                         
				{
					((ToXMLAResult.Cells)[ToXMLAResult.Cells.size()-1]).value += cell.value;
				}
			}
		}
		qrycell.clear();        //清空准备存储下个点查询
	}

	for(i = 0; i < tuplesNum; i++)
		delete [] qryPoints[i];
	delete [] qryPoints;

	//返回查询结果
	return ToXMLAResult;
}


vector<Cell> RolapCCQuery::Cellquery()
{
	int i = 0;
	int ii = 0;
	//执行笛卡尔积计算
	//getQueryPoints( this->parsedMdx );

	//执行点查询
	vector<Cell> cells;
	for ( i = 0; i < tuplesNum; i++ )
	{
		Cell cell;
		bool isValid = true;
		enterLayer = 0;

		cell.formatString = msrFormatStr[mdxMsrHdr[i%mdxMsrHdr.size()]-dimsNum];
		//初始化查询cell的维度值返回给用户
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
				cells.push_back(cell); //如果该查询值非法，插入一个空的cell作为返回的结果
				break;
			} 
			qrycell.push_back(qryPoints[i][ii]);//把当前的查询cell放到向量中
		}
		
		if(	isValid )
		{	
			//计算出该条查询对应的度量是哪一个
			int posInMdxMsrHdr = ((i % (msrsLineCount * mdxMsrHdr.size()))/msrsLineCount)%(mdxMsrHdr.size());
			//下面查看记录是不是已经查询过，如果存在就读出需要的度量值
			queryCellMapType::iterator findPt;
			findPt = queryCellMap.find(qrycell);
			if ( findPt == queryCellMap.end() )           //在查询cell里面还没有出现
			{
				pointQuery( qryPoints[i] );	
				//把查询的结果放到结果集中
				if (isNull)
				{
					cell.isNull = true;
				}
				else
				{
					cell.value = msrValues[ mdxMsrHdr[posInMdxMsrHdr] - dimsNum ];
					
					msrValues.clear();						//为下次读入度量做好准备
				}
			}
			else //已经存在该查询的点了									
			{
				cell.value = (*findPt).second[ mdxMsrHdr[posInMdxMsrHdr] - dimsNum ];
			}

			//如果存在切片轴度量要做相应的处理然后再作为最终结果返回给XMLA
			if (slicerTuplesNum == 0) //直接把获得的度量放入到结果集就可以了
			{
				cells.push_back(cell);
			}
			else
			{
				//下面准备把该查询的值加入到结果集中，但是必须考虑切片轴中tuples的数目，加入切片轴有n个tuples
				//结果集中的一个度量应该是由n个点查询产生的度量值的和组成的
				if (i % slicerTuplesNum == 0)//把cell.value加入到结果集中，增加一个新项，但之后还要迭加
				{
					cells.push_back(cell);
				}
				else//进行切片轴的所有tuples度量迭加                         
				{
					((cells)[cells.size()-1]).value += cell.value;
				}
			}
		}
		qrycell.clear();        //清空准备存储下个点查询
	}

	for ( i = 0; i < tuplesNum; ++i )
		delete [] qryPoints[i];
	delete [] qryPoints;

	//返回查询结果
	return cells;
}

};