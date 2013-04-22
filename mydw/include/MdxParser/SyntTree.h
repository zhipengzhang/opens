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
 * ö��.
 * ���ڸ�ÿһ��MDX���������﷨���ϵĽڵ����һ����Ӧ������
 * �����﷨���Ľڵ�ʱ������ͨ����������ڵ��Ӧ�����������ʵ�.
 * @see TreeNoede
 */
enum NodeType  {          
   WITHSELTFROMWHERE_LIST, /**< ��4�����ӽڵ�,��Ӧ����with,select,from,where��"statement_list"����. */  
   WITHSELFROM_LIST,       /**< ��3�����ӽڵ�,��Ӧ����with,select,from��"statement_list"����. */ 
   SELFROMWHERE_LIST,      /**< ��3�����ӽڵ�,��Ӧ����select,from,where��"statement_list"����. */
   SELFROM_LIST,           /**< ��2�����ӽڵ�,��Ӧ����select,from��"statement_list"����. */
   FROM_STMT,              /**< ��1�����ӽڵ�,��Ӧselect����Ϊ�յ�"statement_list"����. */
   FORM_WHERE,             /**< ��2�����ӽڵ�,��ӦselectΪ�գ���where��Ϊ�յ�"statement_list"����. */
   FORMULA_STMT,	       /**< ��2�����ӽڵ�,��Ӧ"formula_specification"����. */
   MEM_LIST,		 /**< ��2�����ӽڵ�,��Ӧ"member_specification_list"����. */
   LOGIC_OPER,       /**< ��0�����ӽڵ�,��Ӧ"logic_oper"����. */
   MATH_OPER,        /**< ��0�����ӽڵ�,��Ӧ"mathematical_oper"����. */
   CALCMEM_STMT,         /**< ��2�����ӽڵ�,��Ӧ"member_specification"����. */
   MEMDEF_LIST,      /**< ��2�����ӽڵ�,��Ӧ"member_property_def_list"����. */
   MEMPDEF_STMT,	 /**< ��3�����ӽڵ�,��Ӧ"member_property_definition"����. */
   NAMESET_LIST,	 /**< ��2�����ӽڵ�,��Ӧ"nameset_specification_list"����. */
   COMID_STMT,       /**< ��2�����ӽڵ�,��Ӧ"compound_id"����. */
   AXIS_LIST,        /**< ��2�����ӽڵ�,��Ӧ"axis_specification_list"����. */
   AXIS_STMT,		 /**< ��2�����ӽڵ�,��Ӧ"axis_specification"����. */
   NONEMPTY_AXIS_STMT,    /**< ��2�����ӽڵ�,��Ӧ�йؼ���"NON EMPTY"��"axis_specification"����. */
   AXISNAME_STMT,    /**< ��1�����ӽڵ�,��Ӧ"axis_name"����. */ 
   AXISNUM_STMT,     /**< ��1�����ӽڵ�,��Ӧ"axis_number"����. */
   SET_STMT_LIST,    /**< ��2�����ӽڵ�,��Ӧ"set_specification_list"����. */
   SET_STMT,         /**< ��1�����ӽڵ�,��Ӧ"set_specification"����. */
   TUPLE_LIST,       /**< ��2�����ӽڵ�,��Ӧ"tuple_specification_list"����. */
   TUPLE_STMT,       /**< ��1�����ӽڵ�,��Ӧ"tuple_node"����. */
   MEMEXPR_LIST,     /**< ��2�����ӽڵ�,��Ӧ"member_expression_list"����. */
   MEM_NODE,         /**< ��2�����ӽڵ�,��Ӧ"member_expression_node"����. */ 
   WHERE_STMT,		 /**< ��1�����ӽڵ�,��Ӧ"where_clause_opt"����. */
   CUBE_STMT,		 /**< ��1�����ӽڵ�,��Ӧ"cube_specification"����. */
   
   IDENT_EXPR,		/**< ��0�����ӽڵ�,��Ӧ"identifier"����. */
   QIDENT_EXPR,     /**< ��0�����ӽڵ�,��Ӧ"quoted_identifier"����. */
   AMPID_EXPR,      /**< ��0�����ӽڵ�,��Ӧ"amp_quoted_identifier"����. */
   INT_NUM_EXPR,	    /**< ��0�����ӽڵ�,��Ӧ"int_number"����. */
   DEC_NUM_EXPR,	    /**< ��0�����ӽڵ�,��Ӧ"dec_number"����. */
   VALUE_EXPR,		/**< ��2�����ӽڵ�,��Ӧ"value_expression"����. */
   TERM1,			/**< ��2�����ӽڵ�,��Ӧ"term1"����. */
   TERM2,			/**< ��3�����ӽڵ�,��Ӧ"term2"����. */
   TERM3,			/**< ��1�����ӽڵ�,��Ӧ"term3"����. */
   TERM4,			/**< ��2�����ӽڵ�,��Ӧ"term4"����. */
   FUN_STMT,        /**< ��3�����ӽڵ�,��Ӧ"fun_specification"����. */
 //  FUN_PARAM_STMT,  /**< ��3�����ӽڵ�,��Ӧ"fun_specification"����. */
   QRYMEM_EXPR,         /**< ��1�����ӽڵ�,��Ӧ"member_expression"����. */
   CALCMEM_EXPR,         /**< ��1�����ӽڵ�,��Ӧ"calcmember_expression"����. */
   CALCMEM_NAME,      /**< ��1�����ӽڵ�,��Ӧ"calcmember_name"����. */

   ADD_NODE,        /**< ��2�����ӽڵ�,��Ӧ�ӷ�����. */
   MINUS_NODE,      /**< ��2�����ӽڵ�,��Ӧ��������. */
   MUL_NODE,        /**< ��2�����ӽڵ�,��Ӧ�˷�����. */
   DIV_NODE,         /**< ��2�����ӽڵ�,��Ӧ��������. */

   MEM_FUNSET
};

const int MAXCHILD = 4; /**< ����MDXCHILD����MDX�﷨��������ӽڵ�����ֵ. */


/**
 *  ��TreeNode. 
 *  TreeNode��������ʾMDX���ɵ��﷨���ϵ�һ���ڵ�ģ����ݱ�д��YACC�Ĺ���
 *  �ж��﷨���Ͽ��ܳ��ֵ����ĺ��ӽڵ���,��������N�����ӽڵ���֣���
 *  ��ҪN+1�����캯��.
 *  @see MAXCHILD
 *  @see SymDesc
 *  @see SymTab
 */
class TreeNode
{
public:
	/**
     * ���캯��1.
     * ���ڹ���û�к��ӽڵ��TreeNode.
	 * @param _type �ڵ�����֣�NodeType�͵�.
     * @see NodeType
     */
	TreeNode(NodeType _type);

	/**
     * ���캯��2.
     * ���ڹ�����һ�����ӽڵ��TreeNode.
	 * @param _type �ڵ�����֣�NodeType�͵�.
     * @param child1 ָ���һ�����ӽڵ��ָ��
     * @see NodeType
     */
	TreeNode (NodeType _type, TreeNode *child1);

	/**
     * ���캯��3.
     * ���ڹ������������ӽڵ��TreeNode.
	 * @param _type �ڵ�����֣�NodeType�͵�.
     * @param child1 ָ���һ�����ӽڵ��ָ��
     * @param child2 ָ��ڶ������ӽڵ��ָ��
     * @see NodeType
     */
	TreeNode (NodeType _type, TreeNode *child1, TreeNode *child2);

	/**
     * ���캯��4.
     * ���ڹ������������ӽڵ��TreeNode.
	 * @param _type �ڵ�����֣�NodeType�͵�.
     * @param child1 ָ���һ�����ӽڵ��ָ��
     * @param child2 ָ��ڶ������ӽڵ��ָ��
	 * @param child3 ָ����������ӽڵ��ָ��
     * @see NodeType
     */
	TreeNode (NodeType _type, TreeNode *child1, TreeNode *child2, TreeNode *child3);

	/**
     * ���캯��5.
     * ���ڹ������ĸ����ӽڵ��TreeNode.
	 * @param _type �ڵ�����֣�NodeType�͵�.
     * @param child1 ָ���һ�����ӽڵ��ָ��
     * @param child2 ָ��ڶ������ӽڵ��ָ��
	 * @param child3 ָ����������ӽڵ��ָ��
	 * @param child4 ָ����ĸ����ӽڵ��ָ��
     * @see NodeType
     */
	TreeNode (NodeType _type, TreeNode *child1, TreeNode *child2, TreeNode *child3,TreeNode *child4);
	
	/**
     * ���캯��.
	 * @see TreeNode()
     */
	~TreeNode();

public:
     /**
     * ���﷨���϶�ȡMDX����Cube������Ϣ
	 * @return string
     */
	string getCubeName();

	/**
	* �ô��﷨�����ռ��ĳ�Ա��Ϣ����һ��BasicMember����
	* ��������QueryMember�����һ�������ԵĶ���
	* @param _vecstr �����ռ���Ա��Ϣ������
	* @return BasicMember
	* @see QueryMember
	*/
	//BasicMember* creatBasicMember(vector<string>& _vecstr);
	
    /**
	* �ô��﷨�����ռ��ĳ�Ա��Ϣ����һ��BasicMember����
	* ��������QueryMember�����һ�������ԵĶ���,���ڵ���Ԫ����
	* @param _vecmem �����ռ���Ա��Ϣ������
	* @param _sch MDX��ѯ���ڵ�schema��ָ��
	* @return QueryMember
	* @see BasicMember creatBasicMember()
	*/
    QueryMember* creatQueryMember(XSchema* _sch, vector<string>& _vecmem,bool _isCalculated);
    
	void init(void);
	/**
	* ���﷨�����к������������������ParseMDX��������Ҫ�����¼�����\n
	* ��һ����һ��string�������洢���﷨���л�ȡMDX��ѯ����ѯ��һ����Ա����ϸ��Ϣ;\n
	* �ڶ�������Ԫ���ݵ���Ϣ���������������Ϣ����һ��QueryMember���󣬲���ӽ�
	*       QueryMember��������Ȼ�����string��������\n
	* �������ظ�ǰ������ֱ�����ʵ�һ����ΪTUPLE�Ľڵ��,����һ��QueryTuple������ӽ�
	*       QueryTuple�������������QueryMember��������\n
	* ���ģ��ظ�ǰ������ֱ�������������﷨��,����һ��ParsedMDX���󣬲����
	*       QueryMember��������\n
	* ע�������Ĳ��У�ͬʱ������
	* @param _vecMemInfo ���ڴ洢string���ַ�����������������¼���﷨���ϻ�õ�MDX��Ա��Ϣ
	* @param _vecMem ���ڴ洢QueryMember������������洢��һ��Ԫ�飨Tuple����QueryMember��������
	* @param _vecTuple ���ڴ洢QueryTuple�������������������ParsedMDX���󣬱������﷨�������
	* @param _sch MDX��ѯ����ѯ��schema,���ڻ�ȡ��Ա�ľ�����Ϣ
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
     * ���ն˴�ӡ���﷨��
     */
	void show ()  {show(0);}


	void SetIsUminus();

public:
    /**
     * �ڵ������
	 * @see NodeType
     */
	NodeType type; 
	
	/**
     * �������﷨���ϸ��Ϸ��ŵ�������Ϣ
     */
    SymDesc  *symbol; 
	
	/**
     * ָ���ӽڵ��ָ��
     */
    TreeNode *child[MAXCHILD];  


    bool isUminus;


private:
    /**
     * ���﷨���ڵ���ȴ�ӡ���﷨��
     */
   void show (int level);

};

/** �������� SyntTree */
typedef TreeNode *SyntTree;

//}
#endif
