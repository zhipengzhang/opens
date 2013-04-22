#pragma warning(disable: 4786 4715)

#include "MdxParser/Common.h"
#include "MdxParser/SymTab.h"
#include "MdxParser/QueryMember.h"
#include "MdxParser/SyntTree.h"
#include "MdxParser/ParsedMDX.h"
#include "MdxParser/SetFunFactory.h"
#include "MdxParser/MemberFunFactory.h"

using namespace dwschemac;

TreeNode::TreeNode (NodeType _type)
{
    type = _type; 
	child[0] = NULL; 
	child[1] = NULL; 
	child[2] = NULL;
	child[3] = NULL;
}

TreeNode::TreeNode (NodeType _type, TreeNode *child1)
{
	type = _type; 
	child[0] = child1; 
	child[1] = NULL; 
	child[2] = NULL;
	child[3] = NULL;
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
}


char *name[40]={
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
   "number",
   "value_expression",
   "term1",
   "term2",
   "term3",
   "term4",
   "fun_specification",
   "member_expression"
};

// Numbers of children per node type
int children[] = 
{
   4, 3, 3, 2, 1, 2, 2, 2, 0, 0, 2, 
   2, 3, 2, 2, 2, 2, 2, 0, 0, 2, 
   1, 2, 1, 2, 2, 1, 1, 0, 0, 0, 
   0, 2, 2, 3, 1, 2, 2, 1
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
	  case NUM_EXPR:
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
	return mdxcubeName;
}


QueryMember* TreeNode::creatQueryMember(XSchema* _sch, vector<string>& _vecmem)
{
	 int size = _vecmem.size();
	 if (size == 0)
	 {
		 cout<<"error...empty member information when creat QueryMember!"<<endl;
		 exit(-1);
	 }
// 	 elseif(size == 1)//只有匹配CurrenMember函数时才会出现的情况，暂时不处理
// 	 {
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
			     Measure* pMea = pCube->getMeasure(_vecmem.at(1));

                 assert(pMea);
				 std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(1),_ancestorVals,_ancestorLevels,isAll));
					 
				 return pQmem.release();
			 } 
			 else
			 {
				 cout<<"error...invalid measure"<<endl;
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
				 exit(-1);
			 } 
			 else
			 {
				 Hierarchy* pHie =  pDim->getHierarchy(_hieName);
				 if (!pHie)
				 {
					 cout<<"error...can not get hierarchy pointer when creat QueryMember!"<<endl;
					 exit(-1);
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
								 std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(1),_ancestorVals,_ancestorLevels,isAll));
					
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
								 
                                 std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(1),_ancestorVals,_ancestorLevels,isAll));
								 return pQmem.release();
							 }
							 
						 } 
						 else
						 {
							 Level* plevel = temp.at(size-1);//val的level 
							 _level = plevel->getName();

							 if (size == 2)
							 {
								 std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(1),_ancestorVals,_ancestorLevels,isAll));
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
								 
                                 std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(1),_ancestorVals,_ancestorLevels,isAll));
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
							 std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(1),_ancestorVals,_ancestorLevels,isAll));
							 return pQmem.release();
						 } 
						 else
						 {
							 vector<Level*> levelVec;
							 vector<Level*>::iterator iter;
							 levelVec.assign(levelVec.begin(), levelVec.begin()+size-2);

                             for (iter = levelVec.begin(); iter != levelVec.end(); iter++)
                             {
								 string templevel = (*iter)->getName();
								 _ancestorLevels.push_back(templevel);
                             }

							 _ancestorVals.assign(_vecmem.begin()+1, _vecmem.begin()+size-1);/////////
							 
                             std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(size-1),_ancestorVals,_ancestorLevels,isAll));
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
			 
			 assert(pDim);		 			 
			 
			 Hierarchy* pHie = pDim->getDefaultHierarchy();
			 
			 assert(pHie);
			 
			 _hieName = pHie->getName();

			 vector<Level*> temp = pHie->getLeveles();

			 //判断此Hierarchy是否有hasAll属性，
			 if (pHie->hasAll())
			 {
				 string hasAllstr = pHie->getAllMemberName();
	
				 if (hasAllstr == _vecmem.at(1))
				 {

					 Level* plevel = temp.at(size-2);//val的level
					 assert(plevel);
					 _level = plevel->getName();

					 if (size == 2)
					 {
						 isAll = true;
						 std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(1),_ancestorVals,_ancestorLevels,isAll));
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
						 
                         std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(size-1),_ancestorVals,_ancestorLevels,isAll));
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
						 std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(1),_ancestorVals,_ancestorLevels,isAll));
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
								 						 
                         std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(size-1),_ancestorVals,_ancestorLevels,isAll));
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
					 std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(1),_ancestorVals,_ancestorLevels,isAll));
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

                     std::auto_ptr<QueryMember> pQmem(new QueryMember(_dimName,_hieName,_level,_vecmem.at(size-1),_ancestorVals,_ancestorLevels,isAll));
					 return pQmem.release();
				 }
			 }
		 }
	 }
}


std::vector<string> vecFun;
bool _nonempty = false;

vector<string> vecMemInfo;
vector<QueryMember*> vecMem;
vector<QueryTuple*> vecTuple;
vector< vector<QueryTuple*> > vecSet;

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

//用于存储在查询轴（select）的维度的名字
vector<string> dimName;

//用于标识查询中是否出现过度量
bool explicitMea = false;

//用于标识查询语句中是否出现维度
//即标识WHERE_STMT时的vecTuple中的slicer是语法树出现的
//主要是用于处理如"select from **"等这几种边缘查询的切片
bool slicerInfo = false;

//用于后序遍历,MEM_EXPR即QueryMember的生成节点
//TUPLE即是QueryTuple的生成节点
//AXIS_LIST即是ParsedMDX的生成节点
//return ParsedMDX*
void TreeNode::traverse(vector<string>& _vecMemInfo,
								   vector<QueryMember*>& _vecMem,
								   vector<QueryTuple*>& _vecTuple,
								   vector< vector<QueryTuple*> >& _vecSet,
								   XSchema* _sch)
{
	string cubeName = this->getCubeName();//确保能得到Cube名，如去掉，生成ParsedMDX时出错；但极其影响效率
	for(int i = 0; i <children[type]; i++)
	{
		if (child[i] != NULL)
		{
			child[i]->traverse(_vecMemInfo, _vecMem, _vecTuple, _vecSet, _sch);
		}
	}
		
	switch(type){
	case IDENT_EXPR: case NUM_EXPR: case QIDENT_EXPR: 
		{
		    string a = symbol->cont;      
			if (a != cubeName)
			{
				if ((a == "Crossjoin")||(a == "crossjoin")||(a == "CrossJoin")||(a == "Union")||(a == "union")||
					(a == "Hierarchize")||(a == "hierarchize"))
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
	case MEM_EXPR:
		if(!_vecMemInfo.empty())
		{
            int size = _vecMemInfo.size();
            
			if ((_vecMemInfo.at(0) == "Measures")||(_vecMemInfo.at(0) == "measures"))
			{
				explicitMea = true;
			}
            else
			{
                //把除了measures的出现的所有维度名添加进来---错，measure要同等对待
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
                         dimName.push_back(_vecMemInfo.at(0));
					}
                }
				
				
			}
			/******************************************************
			 *函数处理部分1
			 ******************************************************/
			
			if ((_vecMemInfo.at(size-1) == "Members")||(_vecMemInfo.at(size-1) == "members"))
			{				
                _vecMemInfo.pop_back();
				
                std::auto_ptr<SetFunFactory>p(new SetFunFactory());
				
                vector<QueryTuple*> set = p->funInstance(_sch, cubeName, Members, _vecMemInfo);

		        _vecSet.push_back(set);
			}
			else if((_vecMemInfo.at(size-1) == "AllMembers")||(_vecMemInfo.at(size-1) == "allMembers"))
			{
			    _vecMemInfo.pop_back();
                std::auto_ptr<SetFunFactory>p(new SetFunFactory());
                vector<QueryTuple*> set = p->funInstance(_sch, cubeName, AllMembers, _vecMemInfo);
		        _vecSet.push_back(set);
			}
			else if((_vecMemInfo.at(size-1) == "Children")||(_vecMemInfo.at(size-1) == "children"))
			{
				_vecMemInfo.pop_back();
				
                std::auto_ptr<SetFunFactory>p(new SetFunFactory());
				
                vector<QueryTuple*> set = p->funInstance(_sch, cubeName, Children, _vecMemInfo);

		        _vecSet.push_back(set);				
			}
			else if ((_vecMemInfo.at(size-1) == "PrevMember")||(_vecMemInfo.at(size-1) == "prevMember"))
			{
				_vecMemInfo.pop_back(); 

				std::auto_ptr<MemberFunFactory>p(new MemberFunFactory());

				QueryMember* pMember = p->funInstance(_sch, cubeName, PrevMember, _vecMemInfo);

				_vecMem.push_back(pMember);
			}
			else if ((_vecMemInfo.at(size-1) == "FirstChild")||(_vecMemInfo.at(size-1) == "firstChild"))
			{
				_vecMemInfo.pop_back();

				std::auto_ptr<MemberFunFactory>p(new MemberFunFactory());

				QueryMember* pMember = p->funInstance(_sch, cubeName, FirstChild, _vecMemInfo);

				_vecMem.push_back(pMember);
			}
			else if ((_vecMemInfo.at(size-1) == "LastChild")||(_vecMemInfo.at(size-1) == "lastChild"))
			{
				_vecMemInfo.pop_back();

				std::auto_ptr<MemberFunFactory>p(new MemberFunFactory());

				QueryMember* pMember = p->funInstance(_sch, cubeName, LastChild, _vecMemInfo);

				_vecMem.push_back(pMember);
			}
            /******************************************************
			 *函数处理部分1结束
			 *下面是处理不带函数的member信息
			 ******************************************************/
			else
			{  	
			    _vecMem.push_back (this->creatQueryMember(_sch, _vecMemInfo));	

			}

			//清空存储QueryMember信息的容器，为下一个QueryMember的信息存储作准备
			_vecMemInfo.erase(_vecMemInfo.begin(), _vecMemInfo.end());
		}
		break;
	case TUPLE_STMT:
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
				set = p->funInstance(Crossjoin, set1, set2);
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
				set = p->funInstance(Union, set1, set2);
				_vecSet.push_back(set);
			}
			else if ((vecFunSize != 0)&&((vecFun.at(vecFunSize-1) == "Hierarchize")||(vecFun.at(vecFunSize-1) == "hierarchize")))
			{
				assert(setSize >= 1);
				set2 = _vecSet.at(setSize-1);
				_vecSet.pop_back();
				vecFun.pop_back();
				set = p->funInstance(Hierarchize, set2);
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

			if (dimName.empty())//the case of select from *** where ***"
			{
				for (theIter = dimVec.begin(); theIter != dimVec.end(); theIter++)
				{
					 string name = (*theIter)->getName();
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
					 //Level* pLevel = pMem->getLevel(); ////元数据的默认Member可能取不到Level
					 vector<Level*> levelVec = pHie->getLeveles();

					 Level* pLevel = levelVec.at(0);
					 string levelName = pLevel->getName();
					 vector<string> ancestorVals, ancestorLevels;
					 std::auto_ptr<QueryMember>p(new QueryMember(name, hieName,levelName,memName,ancestorVals,ancestorLevels,isAll));
				     vec.push_back(p.release());
				}
			}
			else//the case of "select *** from *** where ***"
			{
				for (theIter = dimVec.begin(); theIter != dimVec.end(); theIter++)
				{
					string name = (*theIter)->getName();

					iter1 = find(dimName.begin(),dimName.end(),name);
					iter2 = find(Qname.begin(),Qname.end(),name);
					if (iter1 == dimName.end())
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
						 std::auto_ptr<QueryMember>p(new QueryMember(name, hieName,levelName,memName,ancestorVals,ancestorLevels,isAll));
						 tempVec.push_back(p.release());
					} 
					else if(iter2 != Qname.end())
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
					vector<string> vec;
					vec.push_back("Measures");
					
					vec.push_back(val);
					QueryMember* p = this->creatQueryMember(_sch,vec);
					//temp.push_back(p);
					tempVec.insert(tempVec.begin(),p);
				}
				vec = tempVec;
			}

            std::auto_ptr<QueryTuple>pSlicer1(new QueryTuple(vec));
			//叶子节点信息遍历完成，_vecTuple用来存储pSlicer
            _vecTuple.clear();//清空原来的 

			_vecTuple.push_back(pSlicer1.release());

		}

		break;


	default:
		break;
	}	
}


ParsedMDX* TreeNode::getParsedMDX(XSchema* _sch)
{
    //获得查询所在的schema的名字
	//string schemaName = _sch->getName();
	//ParsedMDX* pMDX = new ParsedMDX(cubeName, schemaName, pSlicer, _vecSet);

	//暂时自己先对FoodMart测试
	//   ParsedMDX* pMDX = new ParsedMDX("Sales", "FoodMart", pSlicer, _vecSet);

	this->traverse(vecMemInfo,vecMem,vecTuple,vecSet,_sch);

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
			QueryMember* p = this->creatQueryMember(_sch,vec);
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
				auto_ptr<QueryMember>pQmem(new QueryMember(dimensionName,hieName,levelName,val,ancestorVals,ancestorLevels,isall));
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
					auto_ptr<QueryMember>pQmem(new QueryMember(dimensionName,hieName,levelName,val,ancestorVals,ancestorLevels,isall));
					theVec.push_back(pQmem.release());
				}
			}
		}
		
		auto_ptr<QueryTuple>pTuple(new QueryTuple(theVec));
		vecTuple.push_back(pTuple.release());
    }
                                   
	string schemaName = _sch->getName();
	
	string cubeName = this->getCubeName();

	std::auto_ptr<ParsedMDX>pMDX(new ParsedMDX(cubeName, schemaName, vecTuple, vecSet, _nonempty));

	return pMDX.release();
}