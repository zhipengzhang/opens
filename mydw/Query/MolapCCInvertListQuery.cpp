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
		dimsPos[i].push_back(-2);       //���ĳһά��ֵ�Ľ���   	
	}

	int rtemp = 0;              //��¼��ǰ���ֵ����һ��
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

    int temp =ntemp;             //���ڼ�¼���ҵ�ֵ
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
					break;//�ı������
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
		//���ض���ֵ���
		if(mdxMsrHdr.size() > 0 && !isNull)
		{
			getMsrValues(retLayer,retLine);
		}
		//�����Ͻ缯���
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
	msrValues.resize(msrsNum);         //��ʼ�����ڶ�ȡ������������С
	string cubeDir = static_cast<AggFileReader*>(aggReader)->getCubeDir();
	string msrsFile = cubeDir + "/aggMsrData" + itos(layer) +".dat";
	FILE * msrsDataFile = NULL;
	if ( (msrsDataFile = fopen(msrsFile.c_str(),"rb") ) == NULL)
	{   
		string errorMessage = "open "+msrsFile+" failed";
		throw QueryCmptException(errorMessage);
	}  

	fseek ( msrsDataFile,msrsNum*(row - 1)*sizeof(double),0 );

	//�������ж���ֵ
	fread ( &msrValues[0],sizeof(double),msrsNum,msrsDataFile );

	//�ѵõ��Ķ�������͸ò�ѯ�㼯���뵽map��
	pair<queryCellMapType::iterator,bool> insertPt;
	insertPt = queryCellMap.insert(queryCellMapType::value_type(qrycell,msrValues));
	//������벻�ɹ�������Ϊǰ���ѯ�Ѿ�ȷ���˲������ظ���������������ܳɹ�����
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
	//ִ�еѿ���������
	getQueryPoints( this->parsedMdx );

	//����ά�ȸ��������������Ͳ�ѯ��ڲ�κ�ÿ��ǰ��ļ�¼������,������ѯ�����ά����ۼ����е�ά�ȶ�Ӧ����
	aggsNumPerLayer = aggReader->getNumPerLayer();
	
	int i = 0,ii = 0;
	//����ÿ��ǰ���ж�����
    perLayerNumBefore = new int[dimsNum + 1];
	perLayerNumBefore[0] = 0;
	for ( i = 1; i < dimsNum+1; ++i )
	{ 
		if( aggsNumPerLayer[i-1]==0 )this->zeroLayer++;
		perLayerNumBefore[i] = perLayerNumBefore[i-1] + aggsNumPerLayer[i-1];  
	}

	cout<<"INFO: class MolapCCInvertListQuery--execute point query"<<endl;
	//ִ�е��ѯ
	CellSet ToXMLAResult(parsedMdx);

	buffer = new map< int, vector<int> >[dimsNum];
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

	delete [] buffer;
	//���ز�ѯ���
	return ToXMLAResult;
}

vector<Cell> MolapCCInvertListQuery::Cellquery()
{
	cout<<"INFO: class MolapCCInvertListQuery--Cellquery"<<endl;

	cout<<"INFO: class MolapCCInvertListQuery--getQueryPoints"<<endl;
	//ִ�еѿ���������
//	getQueryPoints( this->parsedMdx );

	//����ά�ȸ��������������Ͳ�ѯ��ڲ�κ�ÿ��ǰ��ļ�¼������,������ѯ�����ά����ۼ����е�ά�ȶ�Ӧ����
	aggsNumPerLayer = aggReader->getNumPerLayer();
	
	int i = 0,ii = 0;
	//����ÿ��ǰ���ж�����
    perLayerNumBefore = new int[dimsNum + 1];
	perLayerNumBefore[0] = 0;
	for ( i = 1; i < dimsNum+1; ++i )
	{
		if(aggsNumPerLayer[i-1]==0)this->zeroLayer++;
		perLayerNumBefore[i] = perLayerNumBefore[i-1] + aggsNumPerLayer[i-1];
	}

	cout<<"INFO: class MolapCCInvertList--execute point query"<<endl;
	//ִ�е��ѯ
	vector<Cell> cells;
	buffer = new map< int, vector<int> >[dimsNum];
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
			if ( qryPoints[i][ii]!=0 )
			{
				enterLayer ++;
			}
			if ( -1 == qryPoints[i][ii] )
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

	for(i = 0; i < tuplesNum; i++)
		delete [] qryPoints[i];
	delete [] qryPoints;

	delete [] buffer;
	//���ز�ѯ���
	return cells;
}

};