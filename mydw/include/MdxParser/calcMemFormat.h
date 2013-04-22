// calcMemFormat.h: interface for the calcMemFormat class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCMEMFORMAT_H__70EF6E94_87C9_495B_AF20_ADD8C23DDB50__INCLUDED_)
#define AFX_CALCMEMFORMAT_H__70EF6E94_87C9_495B_AF20_ADD8C23DDB50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdxParser/QueryMember.h"

//节点类型
enum ContentType {
	MATH_OPERATER,    // 数学操作符
	INT_NUMBER,       // 整数
	DEC_NUMBER,       // 小数
	QUERYMEMBER,      // 成员
	QUERYMEMBER_UMINUS  // 带有负号的成员，出现在计算成员的表达式中，如" -[Measures].[Unit Sales]/2.0 "
};


union content {
	char *mathOper;         //数学操作符
	int int_number;         //整数
	double dec_number;      //小数
	QueryMember * member;   //QueryMember
};


class calcMemFormat  
{
	
public:	

	/**
     * 带参数的构造函数.
	 * @param _type         节点的类型
	 * @param _mathOper     节点的操作符
    */
	calcMemFormat(ContentType _type,char* _mathOper);
    

	/**
     * 带参数的构造函数.
	 * @param _type         节点的类型
	 * @param _int_number    整数值
    */
	calcMemFormat(ContentType _type,int _int_number);
	

	/**
     * 带参数的构造函数.
	 * @param _type         节点的类型
	 * @param _dec_number   小数值
    */
	calcMemFormat(ContentType _type,double _dec_number);


	/**
     * 带参数的构造函数.
	 * @param _type         节点的类型
	 * @param _member       成员
    */
	calcMemFormat(ContentType _type,QueryMember* _member);
	

	/**
    * 用于得到节点的类型
    * @return ContentType
    */
	ContentType getType();

    
	/**
    * 用于得到节点的数学操作符号
    * @return char*
    */
	char* getMathOper();


	/**
    * 用于得到节点的整数值
    * @return int
    */
	int getIntNum();

    
	/**
    * 用于得到节点的小数值
    * @return double
    */
	double getDecNum();


	/**
    * 用于得到节点的成员对象
    * @return QueryMember*
    */
	QueryMember* getQryMember();

	/**
    * 用于显示节点的内容
    */
	void showFormat();
	
	virtual ~calcMemFormat();

public:
	/**
 	* 节点的类型
 	*/
	ContentType type;

	/**
 	* 用于表示节点的内容
 	*/
	union content FormatContent;
	


};

#endif // !defined(AFX_CALCMEMFORMAT_H__70EF6E94_87C9_495B_AF20_ADD8C23DDB50__INCLUDED_)
