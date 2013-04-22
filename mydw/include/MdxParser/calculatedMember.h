// calculatedMember.h: interface for the calculatedMember class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCULATEDMEMBER_H__81A634C0_04F7_472A_95C5_303EA2737140__INCLUDED_)
#define AFX_CALCULATEDMEMBER_H__81A634C0_04F7_472A_95C5_303EA2737140__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "calcMemFormat.h"

class calculatedMember  
{
public:

	/**
 	* ���ڱ�ʾ�����Ա������
 	*/
	vector<string> memberName;
	

	/**
 	* ���ڱ�ʾ�����Ա�ĺ�׺���ʽ
 	*/
	vector<calcMemFormat *> Format;
	

	/**
     * �������Ĺ��캯��.
	 * @param _memberName ��Ա������
	 * @param _Format     ��Ա�ĺ�׺���ʽ
     */
	calculatedMember(vector<string>& _memberName,vector<calcMemFormat *>& _Format);
	

	/**
     * ���ڵõ���Ա��׺���ʽ
     * @return vector<calcMemFormat *>
     */
	vector<calcMemFormat *> getCalcMemFormat();
	

	/**
     * ���ڵõ���Ա������
     * @return <vector> string
     */
	vector<string> getCalcMemberName();

	
	void showCalcMember();
	
	virtual ~calculatedMember();

};

#endif // !defined(AFX_CALCULATEDMEMBER_H__81A634C0_04F7_472A_95C5_303EA2737140__INCLUDED_)
