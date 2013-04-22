/*===========================================
class TreeNode is used to creat a syntax tree.
Roger,2007/4/3
============================================*/
#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

#ifndef __SYNTTREE_H__
#define __SYNTTREE_H__

//#include "SymTab.h"
#include "QueryTuple.h"
#include "DWSchemac/XSchemas.h"
#include "DWSchemac/XSchema.h"
#include "DWSchemac/XCube.h"
#include "DWSchemac/Dimension.h"
#include "DWSchemac/Hierarchy.h"
#include "DWSchemac/Level.h"
#include "DWSchemac/Measure.h"
#include "DWSchemac/Member.h"



#include "calculatedMember.h"

using namespace dwschemac;
using namespace std;

class SymDesc;
class ParsedMDX;
class QueryMember;



/** 
 * 枚举.
 * 用于给每一个MDX编译器的语法树上的节点给出一个对应的名字
 * 访问语法树的节点时，可以通过访问这个节点对应的名字来访问到.
 * @see TreeNoede
 */
enum NodeType  {          
   WITHSELTFROMWHERE_LIST, /**< 有4个孩子节点,对应含有with,select,from,where的"statement_list"规则. */  
   WITHSELFROM_LIST,       /**< 有3个孩子节点,对应含有with,select,from的"statement_list"规则. */ 
   SELFROMWHERE_LIST,      /**< 有3个孩子节点,对应含有select,from,where的"statement_list"规则. */
   SELFROM_LIST,           /**< 有2个孩子节点,对应含有select,from的"statement_list"规则. */
   FROM_STMT,              /**< 有1个孩子节点,对应select后面为空的"statement_list"规则. */
   FORM_WHERE,             /**< 有2个孩子节点,对应select为空，而where不为空的"statement_list"规则. */
   FORMULA_STMT,	       /**< 有2个孩子节点,对应"formula_specification"规则. */
   MEM_LIST,		 /**< 有2个孩子节点,对应"member_specification_list"规则. */
   LOGIC_OPER,       /**< 有0个孩子节点,对应"logic_oper"规则. */
   MATH_OPER,        /**< 有0个孩子节点,对应"mathematical_oper"规则. */
   CALCMEM_STMT,         /**< 有2个孩子节点,对应"member_specification"规则. */
   MEMDEF_LIST,      /**< 有2个孩子节点,对应"member_property_def_list"规则. */
   MEMPDEF_STMT,	 /**< 有3个孩子节点,对应"member_property_definition"规则. */
   NAMESET_LIST,	 /**< 有2个孩子节点,对应"nameset_specification_list"规则. */
   COMID_STMT,       /**< 有2个孩子节点,对应"compound_id"规则. */
   AXIS_LIST,        /**< 有2个孩子节点,对应"axis_specification_list"规则. */
   AXIS_STMT,		 /**< 有2个孩子节点,对应"axis_specification"规则. */
   NONEMPTY_AXIS_STMT,    /**< 有2个孩子节点,对应有关键字"NON EMPTY"的"axis_specification"规则. */
   AXISNAME_STMT,    /**< 有1个孩子节点,对应"axis_name"规则. */ 
   AXISNUM_STMT,     /**< 有1个孩子节点,对应"axis_number"规则. */
   SET_STMT_LIST,    /**< 有2个孩子节点,对应"set_specification_list"规则. */
   SET_STMT,         /**< 有1个孩子节点,对应"set_specification"规则. */
   TUPLE_LIST,       /**< 有2个孩子节点,对应"tuple_specification_list"规则. */
   TUPLE_STMT,       /**< 有1个孩子节点,对应"tuple_node"规则. */
   MEMEXPR_LIST,     /**< 有2个孩子节点,对应"member_expression_list"规则. */
   MEM_NODE,         /**< 有2个孩子节点,对应"member_expression_node"规则. */ 
   WHERE_STMT,		 /**< 有1个孩子节点,对应"where_clause_opt"规则. */
   CUBE_STMT,		 /**< 有1个孩子节点,对应"cube_specification"规则. */
   
   IDENT_EXPR,		/**< 有0个孩子节点,对应"identifier"规则. */
   QIDENT_EXPR,     /**< 有0个孩子节点,对应"quoted_identifier"规则. */
   AMPID_EXPR,      /**< 有0个孩子节点,对应"amp_quoted_identifier"规则. */
   INT_NUM_EXPR,	    /**< 有0个孩子节点,对应"int_number"规则. */
   DEC_NUM_EXPR,	    /**< 有0个孩子节点,对应"dec_number"规则. */
   VALUE_EXPR,		/**< 有2个孩子节点,对应"value_expression"规则. */
   TERM1,			/**< 有2个孩子节点,对应"term1"规则. */
   TERM2,			/**< 有3个孩子节点,对应"term2"规则. */
   TERM3,			/**< 有1个孩子节点,对应"term3"规则. */
   TERM4,			/**< 有2个孩子节点,对应"term4"规则. */
   FUN_STMT,        /**< 有3个孩子节点,对应"fun_specification"规则. */
 //  FUN_PARAM_STMT,  /**< 有3个孩子节点,对应"fun_specification"规则. */
   QRYMEM_EXPR,         /**< 有1个孩子节点,对应"member_expression"规则. */
   CALCMEM_EXPR,         /**< 有1个孩子节点,对应"calcmember_expression"规则. */
   CALCMEM_NAME,      /**< 有1个孩子节点,对应"calcmember_name"规则. */

   ADD_NODE,        /**< 有2个孩子节点,对应加法规则. */
   MINUS_NODE,      /**< 有2个孩子节点,对应减法规则. */
   MUL_NODE,        /**< 有2个孩子节点,对应乘法规则. */
   DIV_NODE,         /**< 有2个孩子节点,对应除法规则. */

   MEM_FUNSET
};

const int MAXCHILD = 4; /**< 常量MDXCHILD，是MDX语法树上最大孩子节点数的值. */


/**
 *  类TreeNode. 
 *  TreeNode是用来表示MDX生成的语法树上的一个节点的，根据编写的YACC的规则
 *  判断语法树上可能出现的最大的孩子节点数,如最大会有N个孩子节点出现，则
 *  需要N+1个构造函数.
 *  @see MAXCHILD
 *  @see SymDesc
 *  @see SymTab
 */
class TreeNode
{
public:
	/**
     * 构造函数1.
     * 用于构造没有孩子节点的TreeNode.
	 * @param _type 节点的名字，NodeType型的.
     * @see NodeType
     */
	TreeNode(NodeType _type);

	/**
     * 构造函数2.
     * 用于构造有一个孩子节点的TreeNode.
	 * @param _type 节点的名字，NodeType型的.
     * @param child1 指向第一个孩子节点的指针
     * @see NodeType
     */
	TreeNode (NodeType _type, TreeNode *child1);

	/**
     * 构造函数3.
     * 用于构造有两个孩子节点的TreeNode.
	 * @param _type 节点的名字，NodeType型的.
     * @param child1 指向第一个孩子节点的指针
     * @param child2 指向第二个孩子节点的指针
     * @see NodeType
     */
	TreeNode (NodeType _type, TreeNode *child1, TreeNode *child2);

	/**
     * 构造函数4.
     * 用于构造有三个孩子节点的TreeNode.
	 * @param _type 节点的名字，NodeType型的.
     * @param child1 指向第一个孩子节点的指针
     * @param child2 指向第二个孩子节点的指针
	 * @param child3 指向第三个孩子节点的指针
     * @see NodeType
     */
	TreeNode (NodeType _type, TreeNode *child1, TreeNode *child2, TreeNode *child3);

	/**
     * 构造函数5.
     * 用于构造有四个孩子节点的TreeNode.
	 * @param _type 节点的名字，NodeType型的.
     * @param child1 指向第一个孩子节点的指针
     * @param child2 指向第二个孩子节点的指针
	 * @param child3 指向第三个孩子节点的指针
	 * @param child4 指向第四个孩子节点的指针
     * @see NodeType
     */
	TreeNode (NodeType _type, TreeNode *child1, TreeNode *child2, TreeNode *child3,TreeNode *child4);
	
	/**
     * 析造函数.
	 * @see TreeNode()
     */
	~TreeNode();

public:
     /**
     * 从语法树上读取MDX语句的Cube名字信息
	 * @return string
     */
	string getCubeName();

	/**
	* 用从语法树上收集的成员信息生成一个BasicMember对象，
	* 这是生成QueryMember对象的一个过渡性的对象
	* @param _vecstr 用于收集成员信息的容器
	* @return BasicMember
	* @see QueryMember
	*/
	//BasicMember* creatBasicMember(vector<string>& _vecstr);
	
    /**
	* 用从语法树上收集的成员信息生成一个BasicMember对象，
	* 这是生成QueryMember对象的一个过渡性的对象,用于调用元数据
	* @param _vecmem 用于收集成员信息的容器
	* @param _sch MDX查询所在的schema的指针
	* @return QueryMember
	* @see BasicMember creatBasicMember()
	*/
    QueryMember* creatQueryMember(XSchema* _sch, vector<string>& _vecmem,bool _isCalculated);
    
	void init(void);
	/**
	* 对语法树进行后续遍历，生成所需的ParseMDX对象，其主要分以下几步：\n
	* 第一：用一个string型容器存储从语法树中获取MDX查询语句查询的一个成员的详细信息;\n
	* 第二：调用元数据的信息，利用容器里的信息生成一个QueryMember对象，并添加进
	*       QueryMember型容器，然后清空string型容器；\n
	* 第三：重复前两步，直到访问到一个名为TUPLE的节点后,生成一个QueryTuple对象添加进
	*       QueryTuple型容器，并清空QueryMember型容器；\n
	* 第四：重复前三步，直到遍历完整棵语法树,生成一个ParsedMDX对象，并清空
	*       QueryMember型容器；\n
	* 注：在这四步中，同时处理函数
	* @param _vecMemInfo 用于存储string型字符串的容器，用来记录从语法树上获得的MDX成员信息
	* @param _vecMem 用于存储QueryMember对象的容器，存储完一个元组（Tuple）的QueryMember对象后被清空
	* @param _vecTuple 用于存储QueryTuple对象的容器，用于生成ParsedMDX对象，遍历完语法树后被清空
	* @param _sch MDX查询语句查询的schema,用于获取成员的具体信息
	//	 * @return ParsedMDX
	* @see TreeNode 	  
	* @see XSchema 
	* @see BasicMember
	* @see QueryMember
	* @see QueryTuple
	* @see ParsedMDX
	* @see Level
	* @see Hierarchy
	* @see Member
	*/
	
	bool traverse(vector<string>& _vecMemInfo,
		vector<QueryMember*>& _vecMem,
		vector<QueryTuple*>& _vecTuple,
		vector<calculatedMember*>& _vec_calcMember,
		vector< vector<QueryTuple*> >& _vecSet,
		XSchema* _sch);
	
    ParsedMDX* getParsedMDX(XSchema* _sch);
	
	
	 /**
     * 向终端打印出语法树
     */
	void show ()  {show(0);}


	void SetIsUminus();

public:
    /**
     * 节点的类型
	 * @see NodeType
     */
	NodeType type; 
	
	/**
     * 用于在语法树上附上符号的属性信息
     */
    SymDesc  *symbol; 
	
	/**
     * 指向孩子节点的指针
     */
    TreeNode *child[MAXCHILD];  


    bool isUminus;


private:
    /**
     * 按语法树节点深度打印出语法树
     */
   void show (int level);

};

/** 定义类型 SyntTree */
typedef TreeNode *SyntTree;

//}
#endif
