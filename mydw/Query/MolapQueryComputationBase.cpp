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
	vector< QueryMember* > temp;       //用于存储axes中某个Tuples的所有member成员
	vector<string> fatherVal;
	vector<string> fatherLevel;
	if (axesNum == 0)//处理最后一个轴，首先对其所有元素进行笛卡尔积，也是递归返回的条件
	{
		//下面对最后一个轴做笛卡尔积
		for (int i = 0; i < axes[axesNum].size(); i ++)
		{
			//处理它里面的每个tuple
			temp = axes[axesNum][i]->getMembers();
			for (int z = 0; z < temp.size(); z ++)
			{
				string hierarchyName = temp[z]->getDimensionName()+"."+temp[z]->getHierarchyName();
				if( hierarchyName.compare( "Measures.Measures" ) != 0 )
				{
					//判断是不是有父亲
					fatherVal = temp[z]->getAncestorVals();//父亲值
					if (fatherVal.size() != 0)
					{
						fatherLevel = temp[z]->getAncestorLevels(); //父亲层次
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
					//处理它自己的值
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
			row ++;           //处理完一个Tuples才增加一行
		}
		return;
	}


	//如果还没到递归结束，处理当前轴对应位置的那个Tuple
	for (int j = 0; j < axes[axesNum].size(); j ++)
	{
		int time = 1;		//用于计算该值在该维出现的行数
		for (int t = axesNum-1; t >= 0; t --)
		{
			time *= axes[t].size();
		}
		cout<<axesNum<<" time:"<<time;
		int line = 0;       //记录循环开始的行的位置
		//处理它里面的每个tuple
		temp = axes[axesNum][j]->getMembers();
		for (int z = 0; z < temp.size(); z ++)
		{
			string hierarchyName = temp[z]->getDimensionName()+"."+temp[z]->getHierarchyName();
			if( hierarchyName.compare( "Measures.Measures" ) != 0 )
			{
				//判断是不是有父亲
				fatherVal = temp[z]->getAncestorVals();//父亲值
				if (fatherVal.size() != 0)
				{
					fatherLevel = temp[z]->getAncestorLevels();//父亲层次
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
								//填二维表的时候，要把根据最后一个轴笛卡尔积结果的那些行全部填充相同的值
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
				//处理它自己的值
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
		//在这里进行递归
		getCartesianProduct(axes,axesNum - 1);
	}
}

int** MolapQueryComputationBase::getQueryPoints(ParsedMDX *parsedMdx)
{
	vector< vector<QueryTuple*> > axes = parsedMdx->getAxes();
	slicerTuplesNum = (parsedMdx->getSlicer()).size();
	//加入切片轴
	if (slicerTuplesNum != 0)
	{
		axes.push_back(parsedMdx->getSlicer());
	}
	
	hdrData = aggReader->getHdrData();
	this->dimsNum = aggReader->getDimsNum();
	this->msrsNum = aggReader->getMsrsNum();
	mapTable = aggReader->getMapTable();

	mdxHdrMap(axes);                   //这里只是处理Measures的头

	int i = 0,j= 0;                    
	for (i = 0; i < axes.size(); i ++)
	{
		tuplesNum *= axes[i].size();
	}

	//接下来申请用于存放查询点集的数组，它的大小是dimsNum×∏（每个轴的元组数）
	qryPoints = new int* [tuplesNum];
	qryPointsDimsVals = new string* [tuplesNum];
	for ( i = 0; i < tuplesNum; i++ )
	{
		qryPoints[i] = new int[dimsNum];
		qryPointsDimsVals[i] = new string[dimsNum];
	}
	//下面把它的值都初始化为0
	for(i = 0 ; i < tuplesNum; i ++)
	{
		for (j = 0; j < dimsNum; j ++)
		{
			qryPoints[i][j] = 0;
			qryPointsDimsVals[i][j] = "*";
		}
	}
	//下面调用递归函数进行笛卡尔积
	/*
		执行笛卡尔积的时候是从最后一个轴开始连接的，比如：
		a   c     
		b   d 
		执行的结果依次是：ca cb da db
	*/
	getCartesianProduct(axes,axes.size()-1);

	return qryPoints;

}

// 函数：doQuery
// 描述：抽象函数，作为查询的一个入口
// 输入：无
// 输出：无
CellSet MolapQueryComputationBase::query()
{
	return CellSet();
}

};