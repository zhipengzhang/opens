// calcMemFormat.h: interface for the calcMemFormat class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCMEMFORMAT_H__70EF6E94_87C9_495B_AF20_ADD8C23DDB50__INCLUDED_)
#define AFX_CALCMEMFORMAT_H__70EF6E94_87C9_495B_AF20_ADD8C23DDB50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdxParser/QueryMember.h"

//�ڵ�����
enum ContentType {
	MATH_OPERATER,    // ��ѧ������
	INT_NUMBER,       // ����
	DEC_NUMBER,       // С��
	QUERYMEMBER,      // ��Ա
	QUERYMEMBER_UMINUS  // ���и��ŵĳ�Ա�������ڼ����Ա�ı��ʽ�У���" -[Measures].[Unit Sales]/2.0 "
};


union content {
	char *mathOper;         //��ѧ������
	int int_number;         //����
	double dec_number;      //С��
	QueryMember * member;   //QueryMember
};


class calcMemFormat  
{
	
public:	

	/**
     * �������Ĺ��캯��.
	 * @param _type         �ڵ������
	 * @param _mathOper     �ڵ�Ĳ�����
    */
	calcMemFormat(ContentType _type,char* _mathOper);
    

	/**
     * �������Ĺ��캯��.
	 * @param _type         �ڵ������
	 * @param _int_number    ����ֵ
    */
	calcMemFormat(ContentType _type,int _int_number);
	

	/**
     * �������Ĺ��캯��.
	 * @param _type         �ڵ������
	 * @param _dec_number   С��ֵ
    */
	calcMemFormat(ContentType _type,double _dec_number);


	/**
     * �������Ĺ��캯��.
	 * @param _type         �ڵ������
	 * @param _member       ��Ա
    */
	calcMemFormat(ContentType _type,QueryMember* _member);
	

	/**
    * ���ڵõ��ڵ������
    * @return ContentType
    */
	ContentType getType();

    
	/**
    * ���ڵõ��ڵ����ѧ��������
    * @return char*
    */
	char* getMathOper();


	/**
    * ���ڵõ��ڵ������ֵ
    * @return int
    */
	int getIntNum();

    
	/**
    * ���ڵõ��ڵ��С��ֵ
    * @return double
    */
	double getDecNum();


	/**
    * ���ڵõ��ڵ�ĳ�Ա����
    * @return QueryMember*
    */
	QueryMember* getQryMember();

	/**
    * ������ʾ�ڵ������
    */
	void showFormat();
	
	virtual ~calcMemFormat();

public:
	/**
 	* �ڵ������
 	*/
	ContentType type;

	/**
 	* ���ڱ�ʾ�ڵ������
 	*/
	union content FormatContent;
	


};

#endif // !defined(AFX_CALCMEMFORMAT_H__70EF6E94_87C9_495B_AF20_ADD8C23DDB50__INCLUDED_)
