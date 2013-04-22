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
// 	 elseif(size == 1)//ֻ��ƥ��CurrenMember����ʱ�Ż���ֵ��������ʱ������
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
		 //�ж��Ƿ���ʹ���˷�Ĭ��ά�ȣ���[dimension.hierarchy],����ǣ�               
		 //�������hierarchy����ȥȡ��hierarchy������ȥȡĬ��hierarchy 
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

					 //�жϴ�Hierarchy�Ƿ���hasAll���ԣ�
					 if (pHie->hasAll())
					 {
						 string hasAllstr = pHie->getAllMemberName();
						 if (hasAllstr == _vecmem.at(1))
						 {
                             
							 Level* plevel = temp.at(size-2);//val��level
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
							 Level* plevel = temp.at(size-1);//val��level 
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
									 _ancestorLevels.push_back(temp.at(1)->getName());//ע�⣬������All Memebr��level
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
					 else//hasAllΪfalse
					 {
                         Level* plevel = temp.at(size-2);//val��level,��Ϊû��hasall��level
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

			 //�жϴ�Hierarchy�Ƿ���hasAll���ԣ�
			 if (pHie->hasAll())
			 {
				 string hasAllstr = pHie->getAllMemberName();
	
				 if (hasAllstr == _vecmem.at(1))
				 {

					 Level* plevel = temp.at(size-2);//val��level
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
				 else//��hasAll���ԣ�������All memebers����ʽֱ��д����һ������ĳ�Ա����������������û��ֹ�����ʱ
				 {
					 isAll = false;
					 
					 Level* plevel = temp.at(size-1);//val��level����1�ɣ���ΪҪ����all member��level��

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
							 _ancestorLevels.push_back(temp.at(1)->getName());//ע�⣬������All Memebr��level
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
			 else//hasAll Ϊfalse�����
			 {
				 Level* plevel = temp.at(size-2);//val��level,��Ϊû��hasall��level
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

//��ʼ��vector
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

//���ڴ洢�ڲ�ѯ�ᣨselect����ά�ȵ�����
vector<string> dimName;

//���ڱ�ʶ��ѯ���Ƿ���ֹ�����
bool explicitMea = false;

//���ڱ�ʶ��ѯ������Ƿ����ά��
//����ʶWHERE_STMTʱ��vecTuple�е�slicer���﷨�����ֵ�
//��Ҫ�����ڴ�����"select from **"���⼸�ֱ�Ե��ѯ����Ƭ
bool slicerInfo = false;

//���ں������,MEM_EXPR��QueryMember�����ɽڵ�
//TUPLE����QueryTuple�����ɽڵ�
//AXIS_LIST����ParsedMDX�����ɽڵ�
//return ParsedMDX*
void TreeNode::traverse(vector<string>& _vecMemInfo,
								   vector<QueryMember*>& _vecMem,
								   vector<QueryTuple*>& _vecTuple,
								   vector< vector<QueryTuple*> >& _vecSet,
								   XSchema* _sch)
{
	string cubeName = this->getCubeName();//ȷ���ܵõ�Cube������ȥ��������ParsedMDXʱ����������Ӱ��Ч��
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
				_vecMemInfo.pop_back();//����0��1��2....��Ϊά������stringȥ��
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
                //�ѳ���measures�ĳ��ֵ�����ά������ӽ���---��measureҪͬ�ȶԴ�
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
			 *����������1
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
			 *����������1����
			 *�����Ǵ�����������member��Ϣ
			 ******************************************************/
			else
			{  	
			    _vecMem.push_back (this->creatQueryMember(_sch, _vecMemInfo));	

			}

			//��մ洢QueryMember��Ϣ��������Ϊ��һ��QueryMember����Ϣ�洢��׼��
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
		if(!_vecTuple.empty())//һ��Ҫ�жϣ���ΪSET_STMT���ظ��������ԣ��п�����ӿյ�_vecTuple
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

		//1���ο�yacc.y��where_clause_opt�Ĺ���
		//where_clause_opt�г��ֵ������tuple_specification
		//����ֻ�ܳ���һ��tuple_specification
		//2���ο�ParesedMDX.h�й���slicer��ע��.
		if(_vecTuple.size() == 1)//��Ƭ��ֻ�����һ��Tuple
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
					 //Level* pLevel = pMem->getLevel(); ////Ԫ���ݵ�Ĭ��Member����ȡ����Level
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
                         //�Ȳ��ǲ�ѯ���еģ�Ҳ����WHERE�Ӿ��г��ֵ�ά
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

						//���ǲ�ѯ���еģ����ǳ�����WHERE�Ӿ��е�ά
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
				if (!explicitMea)//�����ѯ��û���ֶ�������Ӧ�ðѶ���Ҳ��ӵ���Ƭ�ᣬ�ҷ���ǰ��ȥ
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
			//Ҷ�ӽڵ���Ϣ������ɣ�_vecTuple�����洢pSlicer
            _vecTuple.clear();//���ԭ���� 

			_vecTuple.push_back(pSlicer1.release());

		}

		break;


	default:
		break;
	}	
}


ParsedMDX* TreeNode::getParsedMDX(XSchema* _sch)
{
    //��ò�ѯ���ڵ�schema������
	//string schemaName = _sch->getName();
	//ParsedMDX* pMDX = new ParsedMDX(cubeName, schemaName, pSlicer, _vecSet);

	//��ʱ�Լ��ȶ�FoodMart����
	//   ParsedMDX* pMDX = new ParsedMDX("Sales", "FoodMart", pSlicer, _vecSet);

	this->traverse(vecMemInfo,vecMem,vecTuple,vecSet,_sch);

	/*****************************************
     �ж�vecTuple�Ƿ�Ϊ�գ���ΪΪ�յĻ�˵��û��
	 WHERE�Ӿ䣬��ʱ��Ҫ����Ƭ����ӳ�vecSet��
	 ���ֵ����е�ά
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

		if (!explicitMea)//�����ѯ��û���ֶ�������Ӧ�ðѶ���Ҳ��ӵ���Ƭ�ᣬ��Ҫ������ǰ��
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