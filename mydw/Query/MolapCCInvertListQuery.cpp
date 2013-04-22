#include "./Query/MolapCCInvertListQuery.h"

namespace QueryComputationMethods
{

MolapCCInvertListQuery::MolapCCInvertListQuery(ParsedMDX *parsedMDX_t)
:MolapQueryComputationBase(parsedMDX_t),zeroLayer(0),aggsNumPerLayer(0),perLayerNumBefore(0)
{	
	string cubeDir = "";
	string schemaName = parsedMdx->getSchemaName();
	string cubeName = parsedMdx->getCubeName();

	DWConfiguration &dwConfig = DWConfiguration::instance();
	dwConfig.addConfig("System","../../DWServer/conf/system-config.xml");
	DWConfig *config = NULL;	
	if ( !(config = dwConfig.getConfig("System")) )
	{
		string errorMessage = "open system-config.xml failed";
		throw QueryCmptException(errorMessage);
	}
	
	if ( (cubeDir = config->getValue("ConfigurationSettings.DataDir")) == "" )
	{
		string errorMessage = "get ConfigurationSettings.DataDir value failed";
		throw QueryCmptException(errorMessage);
	}
	
	cubeDir += "/" + schemaName + "_" + cubeName;
	aggReader = new AggFileReader(cubeDir);
}

MolapCCInvertListQuery::MolapCCInvertListQuery(ParsedMDX *parsedMDX_t,string partitionNum )
:MolapQueryComputationBase(parsedMDX_t),zeroLayer(0),aggsNumPerLayer(0),perLayerNumBefore(0)
{	
	string cubeDir = "";
	string schemaName = parsedMdx->getSchemaName();
	string cubeName = parsedMdx->getCubeName();

	DWConfiguration &dwConfig = DWConfiguration::instance();
	dwConfig.addConfig("System","../../DWServer/conf/system-config.xml");
	DWConfig *config = NULL;	
	if ( !(config = dwConfig.getConfig("System")) )
	{
		string errorMessage = "open system-config.xml failed";
		throw QueryCmptException(errorMessage);
	}
	
	if ( (cubeDir = config->getValue("ConfigurationSettings.DataDir")) == "" )
	{
		string errorMessage = "get ConfigurationSettings.DataDir value failed";
		throw QueryCmptException(errorMessage);
	}
	
	cubeDir += "/" + schemaName + "_" + cubeName + "/" + partitionNum;

	aggReader = new AggFileReader(cubeDir);
}

MolapCCInvertListQuery::~MolapCCInvertListQuery()
{
	if ( perLayerNumBefore )
	{
		delete [] perLayerNumBefore;
	}
}

void MolapCCInvertListQuery::setCacheUpper( vector< string > upper )
{
	dimValues = upper;
}

vector<string> MolapCCInvertListQuery::getCacheUpper() const
{
	return dimValues;
}

vector<int> MolapCCInvertListQuery::getDimsPos(int dims, int val)
{
	long pos = 0;
	long nextPos = 0;

	string cubeDir = static_cast<AggFileReader*>(aggReader)->getCubeDir();
	string keyName = cubeDir + "/key" + itos(dims) + ".dat";
	string keyPosName = cubeDir + "/keyPos" + itos(dims) + ".dat";

	FILE* keyFile = NULL;
	if ( !(keyFile= fopen(keyName.c_str(),"rb") ))
	{   
		string errorMessage = "open "+keyName+" failed";
		throw QueryCmptException(errorMessage);
	}   

	FILE* keyPosFile = NULL;
	if ( !(keyPosFile = fopen(keyPosName.c_str(),"rb") ) )
	{   
		string errorMessage = "open "+keyPosName+" failed";
		throw QueryCmptException(errorMessage);
	}  

	if ( val == 1 )
	{
		pos = 0;
		fread(&nextPos,sizeof(long),1,keyPosFile);
	}
	else
	{
		fseek(keyPosFile,4 * (val-2),0);
		fread(&pos,sizeof(long),1,keyPosFile);        //record the beginning pos
		fread(&nextPos,sizeof(long),1,keyPosFile);    //record the ending pos
	}

	int num = (nextPos - pos)/4;
	vector<int> tmpl(num);
	fseek(keyFile, pos, 0);
	fread(&tmpl[0],sizeof(int) * num,1,keyFile); 

    fclose(keyFile);
	fclose(keyPosFile);
	return tmpl;
}

int MolapCCInvertListQuery::findQryPointPos( vector< vector<int> > &dimsPos )
{
	int i = 0;
	int dimsNum = dimsPos.size();
	int *dimsLine = new int[dimsNum];

	for( i = 0; i < dimsNum; i++ )
	{
		dimsLine[i] = 0;
		dimsPos[i].push_back(-2);       //标记某一维的值的结束   	
	}

	int rtemp = 0;              //记录当前最大值的那一列
	int ntemp = -1;

	for( i = 0; i < dimsPos[0].size(); ++i )
	{
		if ( dimsPos[0][i]==-2 )
		{
			return -1;
		}
		else if ( dimsPos[0][i]==-1 )
		{
			if(dimsPos[0][++i] >= perLayerNumBefore[enterLayer])
			{
				ntemp = dimsPos[0][i];
				break;
			}
			else if((dimsPos[0][i] + dimsPos[0][++i]) >= perLayerNumBefore[enterLayer])
			{
				ntemp = perLayerNumBefore[enterLayer];
				break;
			}
			continue;
		}
		else if(dimsPos[0][i] >= perLayerNumBefore[enterLayer])
		{
			ntemp = dimsPos[0][i];
			break;
		}
	}

	if(ntemp == -1) return -1;
	if(dimsNum == 1) return ntemp;

    int temp =ntemp;             //用于记录查找的值
	bool unchange =true;

	while(true)
	{
		for(int j = 0; j < dimsNum; j ++, unchange = true)
		{
			if(j == rtemp)
			{
			}
			else
			{
				temp = findNextMaxVal(ntemp, dimsPos[j], dimsLine[j]);
				if(temp == -2)
				{
					return -1;
				}

				if(temp != ntemp)
				{
					ntemp = temp;
					rtemp = j;
					unchange = false;
					break;//改变后跳出
				}				
			}
		}
		if(unchange)
		{
			return ntemp;
		}
	}
}

int MolapCCInvertListQuery::findNextMaxVal(int nVal, vector<int> &dimsVal, int &vecPos)
{
	int currentVal = 0;
	int nextVal = 0;
	while( dimsVal[vecPos] != -2)
	{
		if(dimsVal[vecPos] == -1)
		{
			currentVal = dimsVal[++vecPos];
			nextVal = dimsVal[++vecPos];
			if(currentVal <= nVal && nVal <= nextVal)//find it
			{
				vecPos -= 2;
				return nVal;
			}
			else if(currentVal > nVal)
			{
				vecPos -= 2;
				return currentVal;
			}
			else
			{
				vecPos ++;
				continue;
			}
		}
		if(dimsVal[vecPos] >= nVal)//find it
		{
			return dimsVal[vecPos];
		}
		else
		{
			vecPos ++;
		}
	}

	return -2;	
}

void MolapCCInvertListQuery::pointQuery( int* qry )
{
	isNull = false;
	vector< vector<int> > obj; 
	int i = 0;
	int retLayer = 0;
	int retLine = 1;
	for ( i = 0; i < dimsNum; ++i )
	{
		if( qry[i] != 0 )
		{
			map< int, vector<int> >::iterator lb = buffer[i].find(qry[i]);
			if ( lb != buffer[i].end() )
			{
				obj.push_back((*lb).second);
			}
			else
			{
				vector<int> posInfo = getDimsPos(i, qry[i]);
				obj.push_back( posInfo );
				buffer[i].insert( pair<int,vector<int> >( qry[i],posInfo ) );
			}
		}
	}

	int resultLine = -1;
	int currentVal = 0;
	int nextVal = 0;
	if ( obj.size() == 0 )
	{
		retLayer = zeroLayer;
	}
	else
	{
		resultLine = findQryPointPos(obj);
		if( resultLine == -1 )
		{
			isNull = true;
		}
		else
		{
			for ( i = dimsNum; i >= 0; --i )
			{
				retLine = resultLine+1-perLayerNumBefore[i];
				if ( retLine < 0 )
					continue;
				else if ( retLine > 0 )
				{
					retLayer = i;
					break;
				}
				else 
				{
					retLayer = i - 1;
					retLine = perLayerNumBefore[i] - perLayerNumBefore[i - 1];
					break;
				}			
			}
		}
	}	

	obj.clear();

	if(retLayer >= zeroLayer)
	{	
		//返回度量值结果
		if(mdxMsrHdr.size() > 0 && !isNull)
		{
			getMsrValues(retLayer,retLine);
		}
		//返回上界集结果
#ifdef KEEPCLOSEDCELLSET
		if(!isNull)
			getDimValues(retLayer,retLine);
#endif
		
	}

}

inline void MolapCCInvertListQuery::getDimValues(int layer, int row)
{
	string cubeDir = static_cast<AggFileReader*>(aggReader)->getCubeDir();
	string dimsFile = cubeDir + "/aggDimData" + itos(layer) +".dat";
	FILE * dimsDataFile = NULL;
	if ( (dimsDataFile = fopen(dimsFile.c_str(),"rb") ) == NULL)
	{   
		string errorMessage = "open "+dimsFile+" failed";
		throw QueryCmptException(errorMessage);
	}  
	fseek(dimsDataFile,dimsNum * (row - 1) * sizeof(int),0);
	int *temp = new int[dimsNum];
	fread(temp,sizeof(int),dimsNum,dimsDataFile);
	
	for ( int i = 0; i < dimsNum; ++i )
	{	
		if ( temp[i] == 0 )
			dimValues.push_back("*");
		else
		{
			dimValues.push_back( (aggReader->getMapsVals())[i][ temp[i] - 1 ] );
		}
	}
	fclose(dimsDataFile);
	delete []temp;	
}

inline void MolapCCInvertListQuery::getMsrValues(int layer, int row)
{
	msrValues.resize(msrsNum);         //初始化用于读取度量的向量大小
	string cubeDir = static_cast<AggFileReader*>(aggReader)->getCubeDir();
	string msrsFile = cubeDir + "/aggMsrData" + itos(layer) +".dat";
	FILE * msrsDataFile = NULL;
	if ( (msrsDataFile = fopen(msrsFile.c_str(),"rb") ) == NULL)
	{   
		string errorMessage = "open "+msrsFile+" failed";
		throw QueryCmptException(errorMessage);
	}  

	fseek ( msrsDataFile,msrsNum*(row - 1)*sizeof(double),0 );

	//读出所有度量值
	fread ( &msrValues[0],sizeof(double),msrsNum,msrsDataFile );

	//把得到的度量结果和该查询点集加入到map中
	pair<queryCellMapType::iterator,bool> insertPt;
	insertPt = queryCellMap.insert(queryCellMapType::value_type(qrycell,msrValues));
	//如果插入不成功报错，因为前面查询已经确定了不会有重复，所以这里必须能成功插入
	if (!insertPt.second)
	{
		string errorMessage = "Reading msrvalues,a error has found";
		throw QueryCmptException(errorMessage);
	}
	
	fclose(msrsDataFile);		
}

CellSet MolapCCInvertListQuery::query()
{
	cout<<"INFO: class MolapCCInvertListQuery--Execute query"<<endl;

	cout<<"INFO: class MolapCCInvertListQuery--getQueryPoints"<<endl;
	//执行笛卡尔积计算
	getQueryPoints( this->parsedMdx );

	//计算维度个数、度量个数和查询入口层次和每层前面的记录总条数,并将查询对象的维度与聚集表中的维度对应起来
	aggsNumPerLayer = aggReader->getNumPerLayer();
	
	int i = 0,ii = 0;
	//计算每层前面有多少行
    perLayerNumBefore = new int[dimsNum + 1];
	perLayerNumBefore[0] = 0;
	for ( i = 1; i < dimsNum+1; ++i )
	{ 
		if( aggsNumPerLayer[i-1]==0 )this->zeroLayer++;
		perLayerNumBefore[i] = perLayerNumBefore[i-1] + aggsNumPerLayer[i-1];  
	}

	cout<<"INFO: class MolapCCInvertListQuery--execute point query"<<endl;
	//执行点查询
	CellSet ToXMLAResult(parsedMdx);

	buffer = new map< int, vector<int> >[dimsNum];
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

	delete [] buffer;
	//返回查询结果
	return ToXMLAResult;
}

vector<Cell> MolapCCInvertListQuery::Cellquery()
{
	cout<<"INFO: class MolapCCInvertListQuery--Cellquery"<<endl;

	cout<<"INFO: class MolapCCInvertListQuery--getQueryPoints"<<endl;
	//执行笛卡尔积计算
//	getQueryPoints( this->parsedMdx );

	//计算维度个数、度量个数和查询入口层次和每层前面的记录总条数,并将查询对象的维度与聚集表中的维度对应起来
	aggsNumPerLayer = aggReader->getNumPerLayer();
	
	int i = 0,ii = 0;
	//计算每层前面有多少行
    perLayerNumBefore = new int[dimsNum + 1];
	perLayerNumBefore[0] = 0;
	for ( i = 1; i < dimsNum+1; ++i )
	{
		if(aggsNumPerLayer[i-1]==0)this->zeroLayer++;
		perLayerNumBefore[i] = perLayerNumBefore[i-1] + aggsNumPerLayer[i-1];
	}

	cout<<"INFO: class MolapCCInvertList--execute point query"<<endl;
	//执行点查询
	vector<Cell> cells;
	buffer = new map< int, vector<int> >[dimsNum];
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
			if ( qryPoints[i][ii]!=0 )
			{
				enterLayer ++;
			}
			if ( -1 == qryPoints[i][ii] )
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

	for(i = 0; i < tuplesNum; i++)
		delete [] qryPoints[i];
	delete [] qryPoints;

	delete [] buffer;
	//返回查询结果
	return cells;
}

};