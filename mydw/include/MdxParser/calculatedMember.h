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
 	* 用于表示计算成员的名字
 	*/
	vector<string> memberName;
	

	/**
 	* 用于表示计算成员的后缀表达式
 	*/
	vector<calcMemFormat *> Format;
	

	/**
     * 带参数的构造函数.
	 * @param _memberName 成员的名字
	 * @param _Format     成员的后缀表达式
     */
	calculatedMember(vector<string>& _memberName,vector<calcMemFormat *>& _Format);
	

	/**
     * 用于得到成员后缀表达式
     * @return vector<calcMemFormat *>
     */
	vector<calcMemFormat *> getCalcMemFormat();
	

	/**
     * 用于得到成员的名字
     * @return <vector> string
     */
	vector<string> getCalcMemberName();

	
	void showCalcMember();
	
	virtual ~calculatedMember();

};

#endif // !defined(AFX_CALCULATEDMEMBER_H__81A634C0_04F7_472A_95C5_303EA2737140__INCLUDED_)
