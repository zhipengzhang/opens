/**
 * @file QueryComputation
 * ��ѯ�㷨�����ඨ���ļ�
 * ���ļ������ѯ�㷨������
 *
 */
#ifndef __QueryComputation_H_INCLUDE__
#define __QueryComputation_H_INCLUDE__

#include "MolapCCInvertListQuery.h"
#include "RolapCCQuery.h"
#include "MolapQueryComputationBase.h"
#include "MTCCQuery.h"

#include "QueryCmptException.h"

#include "./dwconfig/DWConfig.h"
#include "./dwconfig/DWConfiguration.h"
#include "./dwconfig/DWElement.h"

class ParsedMDX;

namespace QueryComputationMethods{
class QueryComputation
{
private:
	ParsedMDX* parsed;					///< MDX������Ķ���
	string mdxstring;					///< mdx���
	string schemaName;
	string cubeName;

	void initialParsedMDX();
public:
	/**
	* @brief ��ѯ�㷨�ӿ���Ĺ��캯��
	*
	* ����MDX������Ķ����Լ����Ӷ���
	*
	* @param parsedMDX MDX������Ķ���
	* @param cubedir ��ά���ݿ�洢��Ϣ
	*/

	//�ӹ��캯�������ʼ����ParsedMDX�������
	explicit QueryComputation(string mdxstring_t,string schemaName_t);

	/**
	* @brief ��ѯ�㷨�ӿ������������
	*
	*�ͷ���Դ
	*/
	~QueryComputation();
	
	/**
	* @brief ��ѯ�㷨�ӿ���Ĳ�ѯ����
	*
	*���ز�ѯ�Ľ����
	*/
	CellSet queryComputation( );
	
	ParsedMDX* getParsedMDX();  
};

};
#endif