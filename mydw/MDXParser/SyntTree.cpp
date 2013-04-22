#pragma warning(disable: 4786 4715)

#include "MdxParser/Common.h"
#include "MdxParser/SymTab.h"
#include "MdxParser/QueryMember.h"
#include "MdxParser/SyntTree.h"
#include "MdxParser/ParsedMDX.h"
#include "MdxParser/SetFunFactory.h"
#include "MdxParser/MemberFunFactory.h"
#include "MdxParser/calcMemFormat.h"

#include "MdxParser/GlobalFun.h"


using namespace dwschemac;

TreeNode::TreeNode (NodeType _type)
{
    type = _type; 
	child[0] = NULL; 
	child[1] = NULL; 
	child[2] = NULL;
	child[3] = NULL;
	isUminus = false;
}

TreeNode::TreeNode (NodeType _type, TreeNode *child1)
{
	type = _type; 
	child[0] = child1; 
	child[1] = NULL; 
	child[2] = NULL;
	child[3] = NULL;
	isUminus = false;	
}

TreeNode::TreeNode (NodeType _type, 
		      TreeNode *child1, 
			  TreeNode *child2)
{
    type = _type; 
	child[0] = child1; 
	child[1] = child2; 
	child[2] = NULL;
	child[3] = NULL;  
	isUminus = false;	
}

TreeNode::TreeNode (NodeType _type, 
		      TreeNode *child1, 
			  TreeNode *child2, 
			  TreeNode *child3)
{
    type = _type; 
	child[0] = child1; 
	child[1] = child2; 
	child[2] = child3;
	child[3] = NULL;  
	isUminus = false;	
}

TreeNode::TreeNode (NodeType _type, 
		      TreeNode *child1, 
			  TreeNode *child2, 
			  TreeNode *child3,
			  TreeNode *child4)
{
    type = _type; 
	child[0] = child1; 
	child[1] = child2; 
	child[2] = child3;
	child[3] = child4;  
	isUminus = false;	
}

void TreeNode::SetIsUminus()
{
	isUminus = true;
}

char *name[]={
   "with...select...from...where statement",
   "with...select...from statement",
   "select...from...where statement",
   "select...from statement",
   "select...all...from statement",
   "select..nothing..from..where.. statement",
   "formula_specification",
   "member_specification_list",
   "logic_operator",
   "mathematical_operator",
   "member_specification",
   "member_property_def_list",
   "member_property_definition",
   "nameset_specification_list",
   "compound_id",
   "axis_specification_list",
   "axis_specification",
   "non empty...axis_specification",
   "axis_name",
   "axis_number",
   "set_specification_list",
   "set_specification",
   "tuple_specification_list",
   "tuple_node",
   "member_expression_list",
   "member_expression_node",
   "where_clause",
   "cube_specification",

   "identifier",
   "quoted_identifer",
   "amp_quoted_identifer",
   "int_number",
   "dec_number",
   "value_expression",
   "term1",
   "term2",
   "term3",
   "term4",
   "fun_specification",
//  "fun_param_specification",
   "member_expression",
   "calc_member_expression",
   "calc_member_name",
   "add_expression",
   "minus_expression",
   "mul_expression",
   "div_expression"
};

// Numbers of children per node type
int children[] = 
{
   4, 3, 3, 2, 1, 2, 2, 2, 0, 0, 2, 
   2, 3, 2, 2, 2, 2, 2, 0, 0, 2, 
   1, 2, 1, 2, 2, 1, 1, 0, 0, 0, 0,
   0, 2, 2, 3, 1, 2, 3, 1,1,1,
   2,2,2,2
};
//destructor
TreeNode::~TreeNode()
{
    if(symbol != NULL)
	delete symbol;
	if(child[MAXCHILD] != NULL)
	delete child[MAXCHILD];
}

// Recursively show the contents of the syntax tree
void TreeNode::show (int level)
{
  int i,nl;
  if (!this)  return;
   if((type != WITHSELTFROMWHERE_LIST)&&(type != WITHSELFROM_LIST)&&(type != SELFROMWHERE_LIST)&&(type != SELFROM_LIST))
   {
      for (i = 0; i < level; i++)   printf ("   ");
      printf ("%s", name[type]);
      switch (type)  {
      case IDENT_EXPR: 
         printf (" (%s)", symbol->cont); break;
	  case QIDENT_EXPR: case AMPID_EXPR:
		 printf (" (%s)", symbol->cont); break;
	  case INT_NUM_EXPR:case DEC_NUM_EXPR:
	 	 printf (" (%s)", symbol->cont); break;
      }
      nl = level + 1;
      printf ("\n");
   } else nl = level;
   for (i = 0; i < children[type]; i++) 
	   child[i]->show(nl);
}  

string mdxtempCubeName = " ";
string mdxcubeName = " ";

string TreeNode::getCubeName()
{
	/*
		for(int i = 0; i <children[type]; i++)
				if (child[i] != NULL)
				{
					child[i]->getCubeName();
				}
			switch(type){
			case IDENT_EXPR: case QIDENT_EXPR:
				mdxtempCubeName = symbol->cont;
			 break;
			case CUBE_STMT: 
				mdxcubeName = mdxtempCubeName;
			 break;
			default:
			 break;
			}
		return mdxcubeName;*/
	
	/*========================add by eason==============================*/
	
	for(int i = 0; i <children[type]; i++)  {   //  找出CUBE_STMT结点
		
		if (child[i] != NULL && child[i]->type == CUBE_STMT) {					
			mdxcubeName = child[i] -> child[0] -> symbol -> cont ; 	
			break;
		}
	}	
	return mdxcubeName;	
	
	/*==================================================================*/
}


QueryMember* TreeNode::creatQueryMember(XSchema* _sch, vector<string>& _vecmem,bool _isCalculated)
{

	 int size = _vecmem.size();
	 if (size == 0)
	 {
		 cout<<"error...empty member information when creat QueryMember!"<<endl;
	//	 exit(-1);
		 return 0;
	 }
// 	 else if(size == 1)//只有匹配CurrenMember函数时才会出现的情况，暂时不处理
// 	 {
//		 return 0;
// 	 }
 	 
	 else
	 {
		 string _dimName = "";
		 string _hieName = "";
		 string _level = "";
		 string _value = "";
		 vector<string> _ancestorVals, _ancestorLevels;

		 bool isAll = false;

		 XCube* pCube = _sch->getCube(this->getCubeName());
         
		 if (_vecmem.at(0)=="Measures"||_vecmem.at(0)=="measures")
		 {
			 if (size == 2)
			 {
				 _dimName = "Measures";
				 _hieName = "Measures";
				 _level = "MeasuresLevel";
//			     Measure* pMea = pCube->getMeasure(_vecmem.at(1));
//
//				 if(!pMea)
//				 {
//                     cout<<"error member information when creat QueryMember!"<<endl;
//					 return 0;
//				 }

              // assert(pMea);
				 std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(1),_ancestorVals,_ancestorLevels,isAll,_isCalculated));
					 
				 return pQmem.release();
			 } 
			 else
			 {
				 cout<<"error...invalid measure"<<endl;
				 return 0;
			 }
		 }
		 //判断是否是使用了非默认维度，即[dimension.hierarchy],如果是，               
		 //则用这个hierarchy名字去取得hierarchy，否则去取默认hierarchy 
		 else if (isDimHie(_vecmem.at(0)))
		 {
			 vector<string> dimHie = distinct(_vecmem.at(0));
			 if (dimHie.size() == 2)
			 {
				 _dimName = dimHie.at(0);
				 _hieName = dimHie.at(1);
			 }

			 Dimension* pDim = pCube->getDimension(_dimName);

			 if (!pDim)
			 {
				 cout<<"error...can not get dimension pointer when creat QueryMember!"<<endl;
				 return 0;
			 } 
			 else
			 {
				 Hierarchy* pHie =  pDim->getHierarchy(_hieName);
				 if (!pHie)
				 {
					 cout<<"error...can not get hierarchy pointer when creat QueryMember!"<<endl;
					 return 0;
				 } 
				 else
				 {
					 vector<Level*> temp = pHie->getLeveles();

					 //判断此Hierarchy是否有hasAll属性，
					 if (pHie->hasAll())
					 {
						 string hasAllstr = pHie->getAllMemberName();
						 if (hasAllstr == _vecmem.at(1))
						 {
                             
							 Level* plevel = temp.at(size-2);//val的level
							 _level = plevel->getName();

							 if (size == 2)
							 {
								 isAll = true;
								 std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(1),_ancestorVals,_ancestorLevels,isAll,_isCalculated));
					
								 return pQmem.release();
							 } 
							 else
							 {
								 vector<Level*> levelVec;
								 vector<Level*>::iterator iter;
								 if (size == 3)
 								 {
									 _ancestorLevels.push_back(temp.at(0)->getName());
									 _ancestorVals.push_back(_vecmem.at(1));
 								 } 
 								 else
 								 {
									 levelVec.assign(temp.begin(), temp.begin()+size-2);
									 for (iter = levelVec.begin(); iter != levelVec.end(); iter++)
									 {
										 string templevel = (*iter)->getName();
										 _ancestorLevels.push_back(templevel);
									 }
									 _ancestorVals.assign(_vecmem.begin()+1, _vecmem.begin()+size-1);  

 								 }
								 
                                 std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(1),_ancestorVals,_ancestorLevels,isAll,_isCalculated));
								 return pQmem.release();
							 }
							 
						 } 
						 else  //有hasAll属性，但跳过All memebers的形式直接写了下一个级别的成员，这种情况出现在用户手工输入时
						 {
							 Level* plevel = temp.at(size-1);//val的level 
							 _level = plevel->getName();

							 if (size == 2)
							 {
								 std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(1),_ancestorVals,_ancestorLevels,isAll,_isCalculated));
							     return pQmem.release();
							 } 
							 else
							 {
								 vector<Level*> levelVec;
								 vector<Level*>::iterator iter;
								 if (size == 3)
 								 {
									 _ancestorLevels.push_back(temp.at(1)->getName());//注意，跳过了All Memebr的level
									 _ancestorVals.push_back(_vecmem.at(1));
 								 } 
 								 else
 								 {
									 levelVec.assign(temp.begin()+1, temp.begin()+size-1);
									 for (iter = levelVec.begin(); iter != levelVec.end(); iter++)
									 {
										 string templevel = (*iter)->getName();
										 _ancestorLevels.push_back(templevel);
									 }
									 _ancestorVals.assign(_vecmem.begin()+1, _vecmem.begin()+size-1);
 								 }
								 
                                 std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(1),_ancestorVals,_ancestorLevels,isAll,_isCalculated));
								 return pQmem.release();
							 } 
						 }
					 }
					 else//hasAll为false
					 {
                         Level* plevel = temp.at(size-2);//val的level,因为没有hasall的level
						 _level = plevel->getName();

						 if (size == 2)
						 {
							 std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(1),_ancestorVals,_ancestorLevels,isAll,_isCalculated));
							 return pQmem.release();
						 } 
						 else
						 {
							 vector<Level*> levelVec;
							 vector<Level*>::iterator iter;
							 levelVec.assign(temp.begin(), temp.begin()+size-2);

                             for (iter = levelVec.begin(); iter != levelVec.end(); iter++)
                             {
								 string templevel = (*iter)->getName();
								 _ancestorLevels.push_back(templevel);
                             }

							 _ancestorVals.assign(_vecmem.begin()+1, _vecmem.begin()+size-1);/////////
							 
                             std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(size-1),_ancestorVals,_ancestorLevels,isAll,_isCalculated));
							 return pQmem.release();
						 } 
                         
					 }
				 }
			 }
		 }//end of the case that query with the hierarchy that is not default  
		 
		 else 
		 {		
			 _dimName = _vecmem.at(0);

			 Dimension* pDim = pCube->getDimension(_dimName);
			 
		//	 assert(pDim);
			 if(!pDim)
			 {
				 cout<<"error...can not get dimension pointer when creat QueryMember!"<<endl;				 
				 return 0;
			 }
			 
			 Hierarchy* pHie = pDim->getDefaultHierarchy();
			 
//			 assert(pHie);
			 if(!pHie)
			 {
				 cout<<"error...can not get hierarchy pointer when creat QueryMember!"<<endl;				 
				 return 0;
			 }
			 
			 _hieName = pHie->getName();

			 vector<Level*> temp = pHie->getLeveles();

			 //判断此Hierarchy是否有hasAll属性，
			 if (pHie->hasAll())
			 {
				 string hasAllstr = pHie->getAllMemberName();
	//cout<<"hasAllstr:"<<hasAllstr<<" "<<"_vecmem.at(1):"<<_vecmem.at(1)<<endl;
				 if (hasAllstr == _vecmem.at(1))
				 {

					 Level* plevel = temp.at(size-2);//val的level
					 assert(plevel);
					 _level = plevel->getName();

					 if (size == 2)
					 {
						 isAll = true;
						 std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(1),_ancestorVals,_ancestorLevels,isAll,_isCalculated));
						 return pQmem.release();
					 } 
					 else
					 {
						 vector<Level*> levelVec;
						 vector<Level*>::iterator iter;
						 if (size == 3)
 						 {
							 _ancestorLevels.push_back(temp.at(0)->getName());
							 _ancestorVals.push_back(_vecmem.at(1));
 						 } 
 						 else
 						 {
							 levelVec.assign(temp.begin(), temp.begin()+size-2);
							 for (iter = levelVec.begin(); iter != levelVec.end(); iter++)
							 {
								 string templevel = (*iter)->getName();
								 _ancestorLevels.push_back(templevel);
							 }
							 _ancestorVals.assign(_vecmem.begin()+1, _vecmem.begin()+size-1);

 						 }
						 
						 isAll = false;
						 
                         std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(size-1),_ancestorVals,_ancestorLevels,isAll,_isCalculated));
						 return pQmem.release();
					 }
					 
				 } 
				 else//有hasAll属性，但跳过All memebers的形式直接写了下一个级别的成员，这种情况出现在用户手工输入时
				 {
					 isAll = false;
					 
					 Level* plevel = temp.at(size-1);//val的level“－1吧，因为要跳过all member的level”

					 assert(plevel);
					 
					 _level = plevel->getName();

					 if (size == 2)
					 {
						 std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(1),_ancestorVals,_ancestorLevels,isAll,_isCalculated));
						 return pQmem.release();
					 } 
					 else
					 {
						 vector<Level*> levelVec;
						 vector<Level*>::iterator iter;
 						 if (size == 3)
 						 {
							 _ancestorLevels.push_back(temp.at(1)->getName());//注意，跳过了All Memebr的level
							 _ancestorVals.push_back(_vecmem.at(1));
 						 } 
 						 else
 						 {
							 levelVec.assign(temp.begin()+1, temp.begin()+size-1);
							 for (iter = levelVec.begin(); iter != levelVec.end(); iter++)
							 {
								 string templevel = (*iter)->getName();
								 _ancestorLevels.push_back(templevel);
							 }
							 _ancestorVals.assign(_vecmem.begin()+1, _vecmem.begin()+size-1);
 						 }
								 						 
                         std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(size-1),_ancestorVals,_ancestorLevels,isAll,_isCalculated));
						 return pQmem.release();
					 } 
				 }
			 }
			 else//hasAll 为false的情况
			 {
				 Level* plevel = temp.at(size-2);//val的level,因为没有hasall的level
				 _level = plevel->getName();

				 if (size == 2)
				 {
					 std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(1),_ancestorVals,_ancestorLevels,isAll,_isCalculated));
					 return pQmem.release();
				 } 
				 else
				 {
					 vector<Level*> levelVec;
					 vector<Level*>::iterator iter;
					 levelVec.assign(temp.begin(), temp.begin()+size-2);

                     for (iter = levelVec.begin(); iter != levelVec.end(); iter++)
                     {
						 string templevel = (*iter)->getName();
						 _ancestorLevels.push_back(templevel);
                     }

					 _ancestorVals.assign(_vecmem.begin()+1, _vecmem.begin()+size-1);

                     std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(size-1),_ancestorVals,_ancestorLevels,isAll,_isCalculated));
					 return pQmem.release();
				 }
			 }
			
		 }
	 }
}


std::vector<string> vecFun;
bool _nonempty = false;



vector<calcMemFormat*> vec_calcMemFormat; //存储单个计算成员的表达式信息
calcMemFormat* pCalcMemFormat;

calculatedMember* pCalcMember;                  //存储单个计算成员

vector<string> vec_calcMemName;           //存储单个计算成员的名字


//用于存储在查询轴（select）的维度的名字
vector<string> dimName;

//用于标识查询中是否出现过度量
bool explicitMea = false;

//用于标识查询语句中是否出现维度
//即标识WHERE_STMT时的vecTuple中的slicer是语法树出现的
//主要是用于处理如"select from **"等这几种边缘查询的切片
bool slicerInfo = false;

//用于标识是否获取计算成员的信息
bool Get_CalMemInfo = false;



//用于后序遍历
//MEM_EXPR即是QueryMember的生成节点
//CALCMEM_STMT即是calcMember的生成节点 
//TUPLE即是QueryTuple的生成节点
//AXIS_LIST即是ParsedMDX的生成节点
//return ParsedMDX*
bool TreeNode::traverse(vector<string>& _vecMemInfo,
								   vector<QueryMember*>& _vecMem,
								   vector<QueryTuple*>& _vecTuple,
								   vector<calculatedMember*>& _vec_calcMember,
								   vector< vector<QueryTuple*> >& _vecSet,
								   XSchema* _sch)
{
	string cubeName = this->getCubeName();//确保能得到Cube名，如去掉，生成ParsedMDX时出错
	for(int i = 0; i <children[type]; i++)
	{
		if (child[i] != NULL)
		{
			if(!child[i]->traverse(_vecMemInfo, _vecMem, _vecTuple, _vec_calcMember,_vecSet, _sch))
			{
				return false;
			}
		}
	}
		
	switch(type){
 
	case FORMULA_STMT:
		Get_CalMemInfo = false;
		break;
	
	case CALCMEM_STMT: //遇到该节点，生成计算成员

		pCalcMember = new calculatedMember(vec_calcMemName,vec_calcMemFormat);
		_vec_calcMember.push_back(pCalcMember);
//		printf(" end \n");
		vec_calcMemFormat.clear();
		Get_CalMemInfo = false;
		break;
		

	case INT_NUM_EXPR:
		//获取计算成员表达式中的整数
		if(Get_CalMemInfo)
		{
			int number = atoi(symbol->cont); 
			if(isUminus)       //如果为负数
			{
                number = -number;
			}
//			printf("%d ",number);
			pCalcMemFormat = new calcMemFormat(INT_NUMBER,number);
			vec_calcMemFormat.push_back(pCalcMemFormat);
		}

		
		break;

	case DEC_NUM_EXPR:
		//获取计算成员表达式中的小数
		if(Get_CalMemInfo)
		{
			double number = atof(symbol->cont); 
			if(isUminus)       //如果为负数
			{
                number = -number;
			}
//			printf("%f ",number);
			pCalcMemFormat = new calcMemFormat(DEC_NUMBER,number);
			vec_calcMemFormat.push_back(pCalcMemFormat);
		}

		
		break;

	case IDENT_EXPR: case QIDENT_EXPR: 
		{
		    string a = symbol->cont;    
			//cout<<a<<endl; 
			if (a != cubeName)
			{
				if ((a == "Crossjoin")||(a == "crossjoin")||(a == "CrossJoin")||(a == "Union")||(a == "union")||
					(a == "Hierarchize")||(a == "hierarchize")||(a == "Distinct")||(a == "distinct")||
					(a == "Intersect")||(a == "intersect") || (a == "Tail")||(a == "tail") ||
					(a == "Ancestor")||(a == "ancestor") || (a == "Order")||(a == "order") ||
					(a == "Descendants")||(a == "descendants") || (a == "Ascendants")||(a == "ascendants") ||
					(a == "Head")||(a == "head") )
				{
					vecFun.push_back(a);
				} 
				else
				{					
					_vecMemInfo.push_back(a);
				}
			}
		}
        break;
		
	case AXISNUM_STMT:
		{
			if(0 < _vecMemInfo.size())
			{
				_vecMemInfo.pop_back();//把以0，1，2....作为维度名的string去掉
			}
		}
		break;
    
	case CALCMEM_NAME:
		if(!_vecMemInfo.empty())
		{
//	        printf("\n计算成员名字大小为:%d\n",_vecMemInfo.size());
			vector<string> Vec;
			Vec.assign(_vecMemInfo.begin(),_vecMemInfo.end()-1);

			if(!isMember(_sch, cubeName, Vec))
			{
				cout<<"can't find parent member when create calcmember!"<<endl;
				return false;
			}

			vec_calcMemName = _vecMemInfo; //存储计算成员的名字
			Get_CalMemInfo = true;         // 设置获取计算成员的表达式信息
			
			//清空存储QueryMember信息的容器，为下一个QueryMember的信息存储作准备
			_vecMemInfo.erase(_vecMemInfo.begin(), _vecMemInfo.end());
		}
		break;

	case ADD_NODE:		
//		printf("+ ");
		pCalcMemFormat = new calcMemFormat(MATH_OPERATER,'+');
		vec_calcMemFormat.push_back(pCalcMemFormat);
//		delete pCalcMemFormat;
		break;

	case MINUS_NODE:
//		printf("- ");
		pCalcMemFormat = new calcMemFormat(MATH_OPERATER,'-');
		vec_calcMemFormat.push_back(pCalcMemFormat);
//		delete pCalcMemFormat;
		break;

	case MUL_NODE:
//		printf("* ");
		pCalcMemFormat = new calcMemFormat(MATH_OPERATER,'*');
		vec_calcMemFormat.push_back(pCalcMemFormat);
//		delete pCalcMemFormat;
		break;

	case DIV_NODE:
//		printf("/ ");
		pCalcMemFormat = new calcMemFormat(MATH_OPERATER,'/');
		vec_calcMemFormat.push_back(pCalcMemFormat);
//		delete pCalcMemFormat;
		break;
		
	case QRYMEM_EXPR:
		if(!_vecMemInfo.empty())
		{	
			FunParam *param = new FunParam();

            int size = _vecMemInfo.size();
            
			if ((_vecMemInfo.at(0) == "Measures")||(_vecMemInfo.at(0) == "measures"))
			{
				explicitMea = true;
			}
//            else
//			{
                //把除了measures的出现的所有维度名添加进来---错，measure要同等对待        // 即是什么意思? add by eason
				string temp = _vecMemInfo.at(0);
				if (isDimHie(temp))
				{
					vector<string> dimHie = distinct(temp);
					temp = dimHie.at(0);
				}


                if (dimName.empty())
                {
					dimName.push_back(temp);
                } 
                else
                {
					vector<string>::iterator iter = find(dimName.begin(),dimName.end(),temp);
				    if (iter == dimName.end())
					{
                //         dimName.push_back(_vecMemInfo.at(0));      // 应该是temp吧? add by eason
				 		dimName.push_back(temp); 
					}
                }
				
				
//			}
			/******************************************************
			 *函数处理部分1
			 ******************************************************/
			
			if ((_vecMemInfo.at(size-1) == "Members")||(_vecMemInfo.at(size-1) == "members"))
			{	
				this->type = MEM_FUNSET;   // 为了处理{ [Time].[1997].Children,[Time].[1998] }被错认为有2个set的情况
				
                _vecMemInfo.pop_back();
				
                std::auto_ptr<SetFunFactory>p(new SetFunFactory());
				
                vector<QueryTuple*> set = p->funInstance(_sch, cubeName, Members, _vecMemInfo, param);

		        _vecSet.push_back(set);
			}
			else if((_vecMemInfo.at(size-1) == "AllMembers")||(_vecMemInfo.at(size-1) == "allMembers"))
			{
				this->type = MEM_FUNSET;   // 为了处理{ [Time].[1997].Children,[Time].[1998] }被错认为有2个set的情况
				
			    _vecMemInfo.pop_back();
                std::auto_ptr<SetFunFactory>p(new SetFunFactory());
                vector<QueryTuple*> set = p->funInstance(_sch, cubeName, AllMembers, _vecMemInfo, param);
		        _vecSet.push_back(set);
			}
			else if((_vecMemInfo.at(size-1) == "Children")||(_vecMemInfo.at(size-1) == "children"))
			{
				this->type = MEM_FUNSET;   // 为了处理{ [Time].[1997].Children,[Time].[1998] }被错认为有2个set的情况

				vector<string> Vec;
				Vec.assign(_vecMemInfo.begin(),_vecMemInfo.end()-1);
				
				if(!isMember(_sch, cubeName, Vec))
				{
					return false;
				}
				
				_vecMemInfo.pop_back();
				
                std::auto_ptr<SetFunFactory>p(new SetFunFactory());
				
                vector<QueryTuple*> set = p->funInstance(_sch, cubeName, Children, _vecMemInfo, param);

		        _vecSet.push_back(set);				
			}
			else if((_vecMemInfo.at(size-1) == "Siblings")||(_vecMemInfo.at(size-1) == "siblings"))
			{
				this->type = MEM_FUNSET;   // 为了处理{ [Time].[1997].Children,[Time].[1998] }被错认为有2个set的情况

				vector<string> Vec;
				Vec.assign(_vecMemInfo.begin(),_vecMemInfo.end()-1);
				
				if(!isMember(_sch, cubeName, Vec))
				{
					return false;
				}
				
				_vecMemInfo.pop_back();
				
                std::auto_ptr<SetFunFactory>p(new SetFunFactory());
				
                vector<QueryTuple*> set = p->funInstance(_sch, cubeName, Siblings, _vecMemInfo, param);

		        _vecSet.push_back(set);				
			}

			else if ((_vecMemInfo.at(size-1) == "CurrentMember")||(_vecMemInfo.at(size-1) == "currentMember"))
			{
				vector<string> Vec;
				Vec.assign(_vecMemInfo.begin(),_vecMemInfo.end()-1);
				
				if(!isMember(_sch, cubeName, Vec))
				{
					return false;
				}
				
				_vecMemInfo.pop_back(); 
				
				std::auto_ptr<MemberFunFactory>p(new MemberFunFactory());
				
				QueryMember* pMember = p->funInstance(_sch, cubeName, CurrentMember, _vecMemInfo, param);
				
				_vecMem.push_back(pMember);
			}

			else if ((_vecMemInfo.at(size-1) == "PrevMember")||(_vecMemInfo.at(size-1) == "prevMember"))
			{
				vector<string> Vec;
				Vec.assign(_vecMemInfo.begin(),_vecMemInfo.end()-1);
				
				if(!isMember(_sch, cubeName, Vec))
				{
					return false;
				}
				
				_vecMemInfo.pop_back(); 

				std::auto_ptr<MemberFunFactory>p(new MemberFunFactory());

				QueryMember* pMember = p->funInstance(_sch, cubeName, PrevMember, _vecMemInfo, param);

				_vecMem.push_back(pMember);
			}
			else if ((_vecMemInfo.at(size-1) == "NextMember")||(_vecMemInfo.at(size-1) == "nextMember"))
			{
				vector<string> Vec;
				Vec.assign(_vecMemInfo.begin(),_vecMemInfo.end()-1);
				
				if(!isMember(_sch, cubeName, Vec))
				{
					return false;
				}

				_vecMemInfo.pop_back(); 
				
				std::auto_ptr<MemberFunFactory>p(new MemberFunFactory());
				
				QueryMember* pMember = p->funInstance(_sch, cubeName, NextMember, _vecMemInfo, param);
				
				_vecMem.push_back(pMember);
			}
			else if ((_vecMemInfo.at(size-1) == "FirstChild")||(_vecMemInfo.at(size-1) == "firstChild"))
			{
				vector<string> Vec;
				Vec.assign(_vecMemInfo.begin(),_vecMemInfo.end()-1);
				
				if(!isMember(_sch, cubeName, Vec))
				{
					return false;
				}
				
				_vecMemInfo.pop_back();

				std::auto_ptr<MemberFunFactory>p(new MemberFunFactory());

				QueryMember* pMember = p->funInstance(_sch, cubeName, FirstChild, _vecMemInfo, param);

				_vecMem.push_back(pMember);
			}
			else if ((_vecMemInfo.at(size-1) == "LastChild")||(_vecMemInfo.at(size-1) == "lastChild"))
			{
				vector<string> Vec;
				Vec.assign(_vecMemInfo.begin(),_vecMemInfo.end()-1);
				
				if(!isMember(_sch, cubeName, Vec))
				{
					return false;
				}

				_vecMemInfo.pop_back();

				std::auto_ptr<MemberFunFactory>p(new MemberFunFactory());

				QueryMember* pMember = p->funInstance(_sch, cubeName, LastChild, _vecMemInfo, param);

				_vecMem.push_back(pMember);
			}
			else if ((_vecMemInfo.at(size-1) == "FirstSibling")||(_vecMemInfo.at(size-1) == "firstSibling"))
			{
				vector<string> Vec;
				Vec.assign(_vecMemInfo.begin(),_vecMemInfo.end()-1);
				
				if(!isMember(_sch, cubeName, Vec))
				{
					return false;
				}

				_vecMemInfo.pop_back();
				
				std::auto_ptr<MemberFunFactory>p(new MemberFunFactory());
				
				QueryMember* pMember = p->funInstance(_sch, cubeName, FirstSibling, _vecMemInfo, param);
				
				_vecMem.push_back(pMember);
			}
			else if ((_vecMemInfo.at(size-1) == "LastSibling")||(_vecMemInfo.at(size-1) == "lastSibling"))
			{
				vector<string> Vec;
				Vec.assign(_vecMemInfo.begin(),_vecMemInfo.end()-1);
				
				if(!isMember(_sch, cubeName, Vec))
				{
					return false;
				}

				_vecMemInfo.pop_back();
				
				std::auto_ptr<MemberFunFactory>p(new MemberFunFactory());
				
				QueryMember* pMember = p->funInstance(_sch, cubeName, LastSibling, _vecMemInfo ,param);
				
				_vecMem.push_back(pMember);
			}

			else if ((_vecMemInfo.at(size-1) == "Parent")||(_vecMemInfo.at(size-1) == "parent"))
			{
				vector<string> Vec;
				Vec.assign(_vecMemInfo.begin(),_vecMemInfo.end()-1);
				
				if(!isMember(_sch, cubeName, Vec))
				{
					return false;
				}
				
				_vecMemInfo.pop_back();
				
				std::auto_ptr<MemberFunFactory>p(new MemberFunFactory());
				
				QueryMember* pMember = p->funInstance(_sch, cubeName, Parent, _vecMemInfo, param);
				
				_vecMem.push_back(pMember);
			}
            /******************************************************
			 *函数处理部分1结束
			 *下面是处理不带函数的member信息
			 ******************************************************/
			else
			{  	
				if(_vecMemInfo.size()>1)
				{	
					vector<calculatedMember*>::iterator iter;
					bool  isEqualOrNot = false;
					//判断该成员是否是计算成员
					for(iter = _vec_calcMember.begin(); iter != _vec_calcMember.end();iter++)
					{
						if(isEqual_String((*iter)->getCalcMemberName(),_vecMemInfo))
						{
							isEqualOrNot = true;
							break;
						}
					}
					
					if(!isEqualOrNot) //如果不是计算成员
					{
						if(!isMember(_sch, cubeName, _vecMemInfo))
						{
							return false;
						}
						_vecMem.push_back (this->creatQueryMember(_sch, _vecMemInfo,false));
					}
					else  //如果是计算成员
					{
						QueryMember * mem = this->creatQueryMember(_sch, _vecMemInfo,true);
//						mem->setCalcFormat(getCalcFormat(mem,_vec_calcMember));
                        mem->setCalcFormat(getCalcFormat2(_vecMemInfo,_vec_calcMember));
						_vecMem.push_back (mem);
					}
				}
				
			}

			//清空存储QueryMember信息的容器，为下一个QueryMember的信息存储作准备
			_vecMemInfo.erase(_vecMemInfo.begin(), _vecMemInfo.end());
		}
		break;

    case CALCMEM_EXPR:
		if(true)
		{			
			QueryMember* pMember = this->creatQueryMember(_sch, _vecMemInfo,false); //待改进，因为计算成员的表达式中可能含有另一个计算成员
			//  pMember->showMember();
			if(isUminus)       //如果为负数成员
			{
                pCalcMemFormat = new calcMemFormat(QUERYMEMBER_UMINUS,pMember);
			}
			else 
			{				
				pCalcMemFormat = new calcMemFormat(QUERYMEMBER,pMember);
			}
			vec_calcMemFormat.push_back(pCalcMemFormat);
			//	delete pCalcMemFormat;
			//清空存储calcMember信息的容器，为下一个Member的信息存储作准备
			_vecMemInfo.erase(_vecMemInfo.begin(), _vecMemInfo.end());
		}
		break;
		
	case TUPLE_STMT:
/******************************** add by eason **********************************
*		select                                                                  *
*		{ [Measures].[Units Shipped],[Measures].[Units Ordered] }  on 0,        *
*		{ [Time].[1997].Children,[Time].[1998] } on 1                           *
*		from Warehouse                                                          *
*																				*
*		程序会返回axes size为3的错误信息(应该为2的)，因为程序把[Time].[1997].   *
*        Children和Time.[1998]分别视为2个集合了。以下是解决办法。				*
********************************************************************************/
	
		if(this->child[0]->type == MEM_FUNSET)
		{
		//	cout<<"我在这里了!"<<endl;
			
			vector<QueryTuple *> vecTup = _vecSet.at(_vecSet.size()-1);
			_vecSet.pop_back();

			vector<QueryTuple *>::iterator tupIterator;
			for(tupIterator = vecTup.begin();tupIterator!=vecTup.end();tupIterator++)
			{
				_vecTuple.push_back(*tupIterator);	
			}
			
		}

		if(!_vecMem.empty())
 		{
			std::auto_ptr<QueryTuple>pTuple1(new QueryTuple(_vecMem));
			_vecTuple.push_back(pTuple1.release());

			_vecMem.erase(_vecMem.begin(), _vecMem.end());
		}		
		break;
	
	case SET_STMT:
		if(!_vecTuple.empty())//一定要判断，因为SET_STMT可重复的特殊性，有可能添加空的_vecTuple
		{	
		   std::vector<QueryTuple*> set;
		   set = _vecTuple;
		   _vecSet.push_back(set);
		   _vecTuple.erase(_vecTuple.begin(), _vecTuple.end());
           set.erase(set.begin(), set.end());
		}
		break;
		
	case FUN_STMT:
		if (!vecFun.empty())
		{
			FunParam *param = new FunParam();
			
			std::vector<QueryTuple*> set,set1,set2;
			std::auto_ptr<SetFunFactory>p(new SetFunFactory());
			int setSize = _vecSet.size();
			
			int vecFunSize = vecFun.size();
			if ((vecFunSize != 0)&&((vecFun.at(vecFunSize-1) == "Crossjoin")||(vecFun.at(vecFunSize-1) == "crossJoin")||(vecFun.at(vecFunSize-1) == "CrossJoin")))
			{
				assert(setSize >= 2);
                set2 = _vecSet.at(setSize-1);
 				_vecSet.pop_back();
 				set1 = _vecSet.at(setSize-2);		
 				_vecSet.pop_back();

				vecFun.pop_back();
				set = p->funInstance(Crossjoin, set1, set2,param);
				_vecSet.push_back(set);
			
			} 
			else if((vecFunSize != 0)&&((vecFun.at(vecFunSize-1) == "Union")||(vecFun.at(vecFunSize-1) == "union")))
			{
				assert(setSize >= 2);
                set2 = _vecSet.at(setSize-1);
				_vecSet.pop_back();
				set1 = _vecSet.at(setSize-2);			
				_vecSet.pop_back();
				
				vecFun.pop_back();
				
				char * strParam = "NULL";
				if(this->child[2])
				{
					strParam = this->child[2]->symbol->cont ;
				}
				
				param->setStrParam(strParam);
				set = p->funInstance(Union, set1, set2, param);
				_vecSet.push_back(set);
			}
			else if((vecFunSize != 0)&&((vecFun.at(vecFunSize-1) == "Intersect")||(vecFun.at(vecFunSize-1) == "intersect")))
			{
				assert(setSize >= 2);
                set2 = _vecSet.at(setSize-1);
				_vecSet.pop_back();
				set1 = _vecSet.at(setSize-2);			
				_vecSet.pop_back();
				
				vecFun.pop_back();

				char * strParam = "NULL";
				if(this->child[2])
				{
					strParam = this->child[2]->symbol->cont ;
				}
				
				param->setStrParam(strParam);
				set = p->funInstance(Intersect, set1, set2 , param);
				_vecSet.push_back(set);
			}
			else if ((vecFunSize != 0)&&((vecFun.at(vecFunSize-1) == "Hierarchize")||(vecFun.at(vecFunSize-1) == "hierarchize")))
			{
				assert(setSize >= 1);
				set2 = _vecSet.at(setSize-1);
				_vecSet.pop_back();
				vecFun.pop_back();
				set = p->funInstance(Hierarchize, set2, param);
                _vecSet.push_back(set);
			}
			else if ((vecFunSize != 0)&&((vecFun.at(vecFunSize-1) == "Distinct")||(vecFun.at(vecFunSize-1) == "distinct")))
			{
				assert(setSize >= 1);
				set2 = _vecSet.at(setSize-1);
				_vecSet.pop_back();
				vecFun.pop_back();

//				cout<<"**************************************************"<<endl;
//				vector<QueryTuple*>::iterator tupIterator2;
//				for(tupIterator2 = set2.begin();tupIterator2!=set2.end();tupIterator2++)
//				{
//					(*tupIterator2)->showTuple();
//				}
//				cout<<"***************************************************"<<endl;

				set = p->funInstance(Distinct, set2, param);

                _vecSet.push_back(set);
			}
			else if ((vecFunSize != 0)&&((vecFun.at(vecFunSize-1) == "Tail")||(vecFun.at(vecFunSize-1) == "tail")))
			{
			//	cout<<this->child[2]->symbol->cont<<endl;
				
				assert(setSize >= 1);
				set2 = _vecSet.at(setSize-1);
				_vecSet.pop_back();
				vecFun.pop_back();

				param->setIntParam(atoi(this->child[2]->symbol->cont));
				set = p->funInstance(Tail, set2, param);
                _vecSet.push_back(set);
			}

			else if ((vecFunSize != 0)&&((vecFun.at(vecFunSize-1) == "Head")||(vecFun.at(vecFunSize-1) == "head")))
			{
				//	cout<<this->child[2]->symbol->cont<<endl;
				
				assert(setSize >= 1);
				set2 = _vecSet.at(setSize-1);
				_vecSet.pop_back();
				vecFun.pop_back();
				
				param->setIntParam(atoi(this->child[2]->symbol->cont));
				set = p->funInstance(Head, set2, param);
                _vecSet.push_back(set);
			}

			else if ((vecFunSize != 0)&&((vecFun.at(vecFunSize-1) == "Ancestor")||(vecFun.at(vecFunSize-1) == "ancestor")))
			{
					cout<<this->child[2]->symbol->cont<<endl;
					
					//如果参数为数字
					if(this->child[2]->symbol->type == IDENT_NUM)
					{
						param->setHasIntParam(true);
						param->setIntParam(atoi(this->child[2]->symbol->cont));		
					}
					//如果参数为字符
					if(this->child[2]->symbol->type == IDENT_STR || this->child[2]->symbol->type == QID_STR)
					{
						param->setHasStrParam(true);
						param->setStrParam(this->child[2]->symbol->cont);
					}

					QueryMember * mem = _vecMem.at(_vecMem.size()-1);
					_vecMem.pop_back();
					vector<string> Vec = mem->getMemberName();
					
					std::auto_ptr<MemberFunFactory>p(new MemberFunFactory());
					
					QueryMember* pMember = p->funInstance(_sch, cubeName, Ancestor, Vec, param);
			//		pMember->showMember();

					vector<QueryMember *> vec_Mem;
					vec_Mem.push_back(pMember);

					std::auto_ptr<QueryTuple>pTuple1(new QueryTuple(vec_Mem));
					_vecTuple.push_back(pTuple1.release());
					vec_Mem.erase(vec_Mem.begin(),vec_Mem.end());
			
			}

			else if ((vecFunSize != 0)&&((vecFun.at(vecFunSize-1) == "Order")||(vecFun.at(vecFunSize-1) == "order")))
			{
				if(!_vecMem.empty())
				{
					std::auto_ptr<QueryTuple>pTuple1(new QueryTuple(_vecMem));
					_vecTuple.push_back(pTuple1.release());
					
					_vecMem.erase(_vecMem.begin(), _vecMem.end());
				}	
				
				if(!_vecTuple.empty())//一定要判断，因为SET_STMT可重复的特殊性，有可能添加空的_vecTuple
				{	
					std::vector<QueryTuple*> set;
					set = _vecTuple;
					_vecSet.push_back(set);
					_vecTuple.erase(_vecTuple.begin(), _vecTuple.end());
					set.erase(set.begin(), set.end());				
				}
				
			}
			
			else if ((vecFunSize != 0)&&((vecFun.at(vecFunSize-1) == "Descendants")||(vecFun.at(vecFunSize-1) == "descendants")))
			{
				if(this->child[2])
				{
					//如果参数为数字
					if(this->child[2]->symbol->type == IDENT_NUM)
					{
						param->setHasIntParam(true);
						param->setIntParam(atoi(this->child[2]->symbol->cont));		
					}
				
					//如果参数为字符
					if(this->child[2]->symbol->type == IDENT_STR || this->child[2]->symbol->type == QID_STR)
					{
						param->setHasStrParam(true);
						param->setStrParam(this->child[2]->symbol->cont);
					}
				}
				
				QueryMember * mem = _vecMem.at(_vecMem.size()-1);
				_vecMem.pop_back();
				vector<string> Vec = mem->getMemberName();

				std::auto_ptr<SetFunFactory>p(new SetFunFactory());
				
                vector<QueryTuple*> set = p->funInstance(_sch, cubeName, Descendants, Vec,param);
				
				_vecSet.push_back(set);
				
			}

			else if ((vecFunSize != 0)&&((vecFun.at(vecFunSize-1) == "Ascendants")||(vecFun.at(vecFunSize-1) == "ascendants")))
			{
				
				QueryMember * mem = _vecMem.at(_vecMem.size()-1);
				_vecMem.pop_back();
				vector<string> Vec = mem->getMemberName();
				
				std::auto_ptr<SetFunFactory>p(new SetFunFactory());
				
                vector<QueryTuple*> set = p->funInstance(_sch, cubeName, Ascendants, Vec,param);
				
				_vecSet.push_back(set);
				
			}
			
		}
		break;

	case NONEMPTY_AXIS_STMT:
		_nonempty = true;
		break;

	case AXIS_STMT:
		break;

	case WHERE_STMT:

		//1、参看yacc.y中where_clause_opt的规则
		//where_clause_opt中出现的情况是tuple_specification
		//并且只能出现一个tuple_specification
		//2、参看ParesedMDX.h中关于slicer的注释.
		if(_vecTuple.size() == 1)//切片中只会出现一个Tuple
		{  

			XCube *pCbue = _sch->getCube(this->getCubeName());
			bool isAll = false;
			vector<QueryMember*> vec = (_vecTuple.at(0))->getMembers();
			int size = vec.size();
			vector<Dimension*> dimVec = pCbue->getDimensions();
			vector<Dimension*>::iterator theIter;

			vector<string> Qname;
			vector<string>::iterator iter1,iter2;
            vector<QueryMember*>::iterator iter;
			for (iter = vec.begin(); iter != vec.end(); iter++)
			{
                 string temp = (*iter)->getDimensionName();
				 Qname.push_back(temp);
			}
            vector<QueryMember*> tempVec;
			/****************************************************************************
			where ([Education Level].[All Education Levels].[Partial High School],
			       [Marital Status].[All Marital Status].[S],
			        [Store Size in SQFT].[All Store Size in SQFTs].[30797], [Time].[1997])
            *****************************************************************************/

				for (theIter = dimVec.begin(); theIter != dimVec.end(); theIter++)
				{
					string name = (*theIter)->getName();

					iter1 = find(dimName.begin(),dimName.end(),name);
					iter2 = find(Qname.begin(),Qname.end(),name);
					if (iter1 == dimName.end())   // 照下面的注释,应该要加多个iter2 == Qname.end() 吧?   add by eason
					{
                         //既不是查询轴中的，也不是WHERE子句中出现的维
                         Hierarchy* pHie = (*theIter)->getDefaultHierarchy();
						 assert(pHie);
						 if(pHie->hasAll())
						 {
							 isAll = true;
						 }
						 string hieName = pHie->getName();
						 auto_ptr<Member> pMem = pHie->getDefaultMember();
						 pMem.release();
						 string memName = pMem->getKey();
						 vector<Level*> levelVec = pHie->getLeveles();

						 Level* pLevel = levelVec.at(0);
						 string levelName = pLevel->getName();
						 vector<string> ancestorVals, ancestorLevels;
						 std::auto_ptr<QueryMember>p(new QueryMember(name, hieName,levelName,memName,ancestorVals,ancestorLevels,isAll,false));
						 tempVec.push_back(p.release());
					} 
					else if(iter2 != Qname.end()) // 加多个iter1 == dimName.end() ? add by eason
					{

						//不是查询轴中的，但是出现在WHERE子句中的维
						for (iter = vec.begin(); iter != vec.end(); iter++)
						{
							if ((*iter2) == (*iter)->getDimensionName())
							{
								tempVec.push_back(*iter);
							}							
						}						
					}
				}
				vec.clear();
				if (!explicitMea)//假如查询中没出现度量，则应该把度量也添加到切片轴，且放最前面去
				{

					Measure* pMea = pCbue->getDefaultMeasure();
					string val = pMea->getName();
					vector<string> vec1;
					vec1.push_back("Measures");
					
					vec1.push_back(val);
					QueryMember* p = this->creatQueryMember(_sch,vec1,false);
					//temp.push_back(p);
					tempVec.insert(tempVec.begin(),p);
				}
				vec = tempVec;

            std::auto_ptr<QueryTuple>pSlicer1(new QueryTuple(vec));
			
			//叶子节点信息遍历完成，_vecTuple用来存储pSlicer
            _vecTuple.clear();//清空原来的 

			_vecTuple.push_back(pSlicer1.release());

		}

		break;


	default:
		break;
	}
	return true; //遍历成功
}


vector<string> vecMemInfo;
vector<QueryMember*> vecMem;
vector<QueryTuple*> vecTuple;
vector< vector<QueryTuple*> > vecSet;
vector<calculatedMember*> vec_calcMember;       //存储所有计算成员

//初始化vector
void TreeNode::init(void)
{
	if (!vecMemInfo.empty())
	{
		vecMemInfo.clear();
	}
	
	if (!vecMem.empty())
	{
		vecMem.clear();
	}
	
	if (!vecTuple.empty())
	{
		vecTuple.clear();
	}
	
	if (!vecSet.empty())
	{	
		vecSet.clear();
	}
}


ParsedMDX* TreeNode::getParsedMDX(XSchema* _sch)
{
    //获得查询所在的schema的名字
	//string schemaName = _sch->getName();
	//ParsedMDX* pMDX = new ParsedMDX(cubeName, schemaName, pSlicer, _vecSet);

	//暂时自己先对FoodMart测试
	//   ParsedMDX* pMDX = new ParsedMDX("Sales", "FoodMart", pSlicer, _vecSet);

	if(!this->traverse(vecMemInfo,vecMem,vecTuple,vec_calcMember,vecSet,_sch))
	{
		return 0;
	}
	
//	printf("\n计算成员的表达式栈大小为:%d\n",vec_calcMemFormat.size());

	/*****************************************
     判断vecTuple是否为空，因为为空的话说明没有
	 WHERE子句，这时需要在切片中添加除vecSet中
	 出现的所有的维
    ******************************************/
    if (vecTuple.empty())
    {
		vector<QueryMember*> theVec;
		string cubeName = this->getCubeName();
		XCube* pCube = _sch->getCube(cubeName);
		assert(pCube);
		vector<Dimension*> vec = pCube->getDimensions();
	
		vector<Dimension*>::iterator dIter;
		vector<string> ancestorVals;
		vector<string> ancestorLevels;

		if (!explicitMea)//假如查询中没出现度量，则应该把度量也添加到切片轴，且要放在最前面
		{
			Measure* pMea = pCube->getDefaultMeasure();
			string val = pMea->getName();
			vector<string> vec;
			vec.push_back("Measures");
			vec.push_back(val);
			QueryMember* p = this->creatQueryMember(_sch,vec,false);
			theVec.push_back(p);
		}

		if (dimName.empty())//thes case of "select from ***"
		{
			for (dIter = vec.begin(); dIter != vec.end(); dIter++)
			{
				string dimensionName = (*dIter)->getName();
				bool isall = false;
				Hierarchy* pHie = (*dIter)->getDefaultHierarchy();
				assert(pHie);
				if (pHie->hasAll())
				{
					isall = true;
				}

				auto_ptr<Member> pm = pHie->getDefaultMember();
				string val = pm->getKey();
				Level* plevel = pm->getLevel();
				string levelName = plevel->getName();
				string hieName = pHie->getName();
				auto_ptr<QueryMember>pQmem(new QueryMember(dimensionName,hieName,levelName,val,ancestorVals,ancestorLevels,isall,false));
				theVec.push_back(pQmem.release());
			}
		} 
		else//the case of "select ** from **"
		{
   			for (dIter = vec.begin(); dIter != vec.end(); dIter++)
			{
				string dimensionName = (*dIter)->getName();
	
				vector<string>::iterator iter = find(dimName.begin(),dimName.end(),dimensionName);
	
				if (iter == dimName.end())
				{
					bool isall = false;
					Hierarchy* pHie = (*dIter)->getDefaultHierarchy();
					assert(pHie);
					if (pHie->hasAll())
					{
						isall = true;
					}

					auto_ptr<Member> pm = pHie->getDefaultMember();
					string val = pm->getKey();
					Level* plevel = pm->getLevel();
					string levelName = plevel->getName();
					string hieName = pHie->getName();
					auto_ptr<QueryMember>pQmem(new QueryMember(dimensionName,hieName,levelName,val,ancestorVals,ancestorLevels,isall,false));
					theVec.push_back(pQmem.release());
				}
			}
		}
		
		auto_ptr<QueryTuple>pTuple(new QueryTuple(theVec));
		vecTuple.push_back(pTuple.release());
    }
                                   
	string schemaName = _sch->getName();
	
	string cubeName = this->getCubeName();
	
	std::auto_ptr<ParsedMDX>pMDX(new ParsedMDX(cubeName, schemaName, vecTuple, vec_calcMember,vecSet, _nonempty));
	
	return pMDX.release();
}