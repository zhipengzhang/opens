#include "MdxParser/ParsedMDX.h"
#include "./Query/MolapQueryComputationBase.h"

namespace QueryComputationMethods
{

MolapQueryComputationBase::MolapQueryComputationBase( ParsedMDX *parsedMDX )
:parsedMdx(parsedMDX),
 qryPoints(0),
 dimsNum(0),
 msrsNum(0),
 enterLayer(0),
 tuplesNum(1),
 mapTable(NULL),
 row(0),
 msrsLineCount(1),
 slicerTuplesNum(0),
 isNull(false)
{
	getMsrFormatStr();
}


MolapQueryComputationBase::~MolapQueryComputationBase()
{
	delete aggReader;
	mapTable = NULL;
}


vector<string> MolapQueryComputationBase::getCacheUpper() const
{
	return dimValues;
}

void MolapQueryComputationBase::setCacheUpper(vector< string > upper)
{

}

void MolapQueryComputationBase::getMsrFormatStr()
{
	string schemaName = parsedMdx->getSchemaName();
	string cubeName = parsedMdx->getCubeName();

	XSchema* schema = XSchemas::instance().getSchema( schemaName );
	XCube* cube = schema->getCube(cubeName);
	vector<Measure*>& measures = cube->getMeasures();
	for ( int i = 0; i < measures.size(); ++i )
	{
		msrFormatStr.push_back(measures[i]->getFormat());
	}
}


void MolapQueryComputationBase::mdxHdrMap(vector< vector<QueryTuple*> >& axes)
{
	vector< QueryMember* > temp;

	string tMember;
	string tmptMember;
	int i = 0,j = 0,z = 0;
	for ( i = 0; i < axes.size(); ++i )
	{
		for ( j = 0; j < axes[i].size(); ++j )
		{
			temp = axes[i][j]->getMembers();		
			for ( z = 0; z < temp.size(); ++z )
			{
				tMember = temp[z]->getDimensionName()+"."+temp[z]->getHierarchyName();
				
				if (tMember.compare( "Measures.Measures" ) == 0)
				{
					tMember.append(".");
					tMember.append(temp[z]->getVal());
					mdxMsrHdr.push_back(hdrData[tMember]);
				}
			}
			temp.clear();
		}
	}

}

void MolapQueryComputationBase::getCartesianProduct(vector< vector<QueryTuple*> > &axes,int axesNum)
{
	cout<<"INFO: getCartesianProduct"<<endl;
	vector< QueryMember* > temp;       //���ڴ洢axes��ĳ��Tuples������member��Ա
	vector<string> fatherVal;
	vector<string> fatherLevel;
	if (axesNum == 0)//�������һ���ᣬ���ȶ�������Ԫ�ؽ��еѿ�������Ҳ�ǵݹ鷵�ص�����
	{
		//��������һ�������ѿ�����
		for (int i = 0; i < axes[axesNum].size(); i ++)
		{
			//�����������ÿ��tuple
			temp = axes[axesNum][i]->getMembers();
			for (int z = 0; z < temp.size(); z ++)
			{
				string hierarchyName = temp[z]->getDimensionName()+"."+temp[z]->getHierarchyName();
				if( hierarchyName.compare( "Measures.Measures" ) != 0 )
				{
					//�ж��ǲ����и���
					fatherVal = temp[z]->getAncestorVals();//����ֵ
					if (fatherVal.size() != 0)
					{
						fatherLevel = temp[z]->getAncestorLevels(); //���ײ��
						for (int f = 0; f < fatherVal.size(); f ++)
						{
							string tMember = hierarchyName;
							tMember.append(".");
							tMember.append(fatherLevel[f]);
							if (fatherVal[f].find("All") == string::npos)  //added by yy in 2007.11.02
							{
								int hdrPos = hdrData[tMember];
								cout<<"1 "<<tMember<<":"<<fatherVal[f]<<endl;
								qryPointsDimsVals[row][hdrPos] = fatherVal[f];
								MapTable::iterator it = (mapTable[hdrPos]).find(fatherVal[f]);
								if ( it != mapTable[hdrPos].end())
								{
									qryPoints[row][hdrPos] = it->second;
								}
								else
								{
									qryPoints[row][hdrPos] = -1;
								}
							}
						}
						fatherVal.clear();
						fatherLevel.clear();
					}
					//�������Լ���ֵ
					string selfMember = hierarchyName;
					if ((temp[z]->getLevelName()).compare("") != 0 )
					{
						selfMember.append(".");
						selfMember.append(temp[z]->getLevelName());
						if(!temp[z]->hasAll())  //if the member is not in top level
						{
							int selfHdrPos = hdrData[selfMember];
							qryPointsDimsVals[row][selfHdrPos] = temp[z]->getVal();
							cout<<"2 "<<selfMember<<":"<<temp[z]->getVal()<<endl;
							MapTable::iterator selfIt = (mapTable[selfHdrPos]).find(temp[z]->getVal());
							if ( selfIt != mapTable[selfHdrPos].end())
							{
								qryPoints[row][selfHdrPos] = selfIt->second;
							}
							else
							{
								qryPoints[row][selfHdrPos] = -1;
							}
						}
					}
					
				}
			}
			temp.clear();
			row ++;           //������һ��Tuples������һ��
		}
		return;
	}


	//�����û���ݹ����������ǰ���Ӧλ�õ��Ǹ�Tuple
	for (int j = 0; j < axes[axesNum].size(); j ++)
	{
		int time = 1;		//���ڼ����ֵ�ڸ�ά���ֵ�����
		for (int t = axesNum-1; t >= 0; t --)
		{
			time *= axes[t].size();
		}
		cout<<axesNum<<" time:"<<time;
		int line = 0;       //��¼ѭ����ʼ���е�λ��
		//�����������ÿ��tuple
		temp = axes[axesNum][j]->getMembers();
		for (int z = 0; z < temp.size(); z ++)
		{
			string hierarchyName = temp[z]->getDimensionName()+"."+temp[z]->getHierarchyName();
			if( hierarchyName.compare( "Measures.Measures" ) != 0 )
			{
				//�ж��ǲ����и���
				fatherVal = temp[z]->getAncestorVals();//����ֵ
				if (fatherVal.size() != 0)
				{
					fatherLevel = temp[z]->getAncestorLevels();//���ײ��
					for (int f = 0; f < fatherVal.size(); f ++)
					{
						string tMember = hierarchyName;
						tMember.append(".");
						tMember.append(fatherLevel[f]);
						if (fatherVal[f].find("All") == string::npos)  //added by yy in 2007.11.02
						{
							int hdrPos = hdrData[tMember];
							for (line = 0; line < time; line ++)
							{
								qryPointsDimsVals[row + line][hdrPos] = fatherVal[f];
							}
							cout<<"3"<<tMember<<":"<<fatherVal[f]<<endl;
							MapTable::iterator it = (mapTable[hdrPos]).find(fatherVal[f]);
							if ( it != mapTable[hdrPos].end())
							{
								//���ά���ʱ��Ҫ�Ѹ������һ����ѿ������������Щ��ȫ�������ͬ��ֵ
								for (line = 0; line < time; line ++ )
								{
									qryPoints[row + line ][hdrPos] = it->second;
								}					
							}
							else
							{
								for (line = 0; line < time; line ++ )
								{
									qryPoints[row + line ][hdrPos] = -1;
								}
							}
						}
					}
					fatherVal.clear();
					fatherLevel.clear();
				}
				//�������Լ���ֵ
				//
				string selfMember = hierarchyName;
				if ((temp[z]->getLevelName()).compare("") != 0 )
				{
					selfMember.append(".");
					selfMember.append(temp[z]->getLevelName());
					cout<<"4"<<temp[z]->getLevelName()<<":";
					if(!temp[z]->hasAll())  //if the member is not in top level
					{
						cout<<selfMember<<"yes"<<endl;
						int selfHdrPos = hdrData[selfMember];
						cout<<selfMember<<":"<<temp[z]->getVal();
						MapTable::iterator selfIt = (mapTable[selfHdrPos]).find(temp[z]->getVal());
						for (line = 0; line < time; line ++)
						{
							qryPointsDimsVals[row + line][selfHdrPos] = temp[z]->getVal();
						}
						if ( selfIt != mapTable[selfHdrPos].end())
						{
							for (line = 0; line < time; line ++)
							{
								qryPoints[row + line][selfHdrPos] = selfIt->second;
							}								
						}
						else
						{
							for (line = 0; line < time; line ++)
							{
								qryPoints[row + line][selfHdrPos] = -1;
							}		
						}
					}
				}
			}
			else
			{
				msrsLineCount = time;
			}
		}
		temp.clear();
		//��������еݹ�
		getCartesianProduct(axes,axesNum - 1);
	}
}

int** MolapQueryComputationBase::getQueryPoints(ParsedMDX *parsedMdx)
{
	vector< vector<QueryTuple*> > axes = parsedMdx->getAxes();
	slicerTuplesNum = (parsedMdx->getSlicer()).size();
	//������Ƭ��
	if (slicerTuplesNum != 0)
	{
		axes.push_back(parsedMdx->getSlicer());
	}
	
	hdrData = aggReader->getHdrData();
	this->dimsNum = aggReader->getDimsNum();
	this->msrsNum = aggReader->getMsrsNum();
	mapTable = aggReader->getMapTable();

	mdxHdrMap(axes);                   //����ֻ�Ǵ���Measures��ͷ

	int i = 0,j= 0;                    
	for (i = 0; i < axes.size(); i ++)
	{
		tuplesNum *= axes[i].size();
	}

	//�������������ڴ�Ų�ѯ�㼯�����飬���Ĵ�С��dimsNum���ǣ�ÿ�����Ԫ������
	qryPoints = new int* [tuplesNum];
	qryPointsDimsVals = new string* [tuplesNum];
	for ( i = 0; i < tuplesNum; i++ )
	{
		qryPoints[i] = new int[dimsNum];
		qryPointsDimsVals[i] = new string[dimsNum];
	}
	//���������ֵ����ʼ��Ϊ0
	for(i = 0 ; i < tuplesNum; i ++)
	{
		for (j = 0; j < dimsNum; j ++)
		{
			qryPoints[i][j] = 0;
			qryPointsDimsVals[i][j] = "*";
		}
	}
	//������õݹ麯�����еѿ�����
	/*
		ִ�еѿ�������ʱ���Ǵ����һ���Ὺʼ���ӵģ����磺
		a   c     
		b   d 
		ִ�еĽ�������ǣ�ca cb da db
	*/
	getCartesianProduct(axes,axes.size()-1);

	return qryPoints;

}

// ������doQuery
// ����������������Ϊ��ѯ��һ�����
// ���룺��
// �������
CellSet MolapQueryComputationBase::query()
{
	return CellSet();
}

};