 /*============================================================================
  File:    QueryComputation.h

  Summary: The identifier of QueryComputation members and operations for query

  Copyright(c) 2007 by DBNC Lab, South China University of Technology, Guangzhou, Guangdong, P.R.C. 

------------------------------------------------------------------------------
  Modification history:
  2007.01.30 Version 1.0 by Yuhong Xiao
============================================================================*/
/**
 * @file MolpQueryComputationBase
 * molap��ѯ�㷨�ඨ���ļ�
 * ���ļ�����MOLAP��ѯ�㷨����
 */

#ifndef __MOLAPQUERYCOMPUTATIONBASE_H_INCLUDE__
#define __MOLAPQUERYCOMPUTATIONBASE_H_INCLUDE__

#include "Common.h"
#include "QueryResult.h"
#include "AggReader.h"
#include "AggDBReader.h"
#include "AggFileReader.h"
#include "QueryComputationBase.h"
#include "xodbc/XODBCDatabase.h"

#include "DWSchemac/XSchemas.h"
#include "DWSchemac/XSchema.h"
#include "DWSchemac/Measure.h"
#include "DWSchemac/XCube.h"

#include "QueryCmptException.h"

using namespace dwschemac;
using namespace xodbc;

class ParsedMDX;
class QueryTuple;


namespace QueryComputationMethods{

//��map�����ж�ĳ����ѯ�Ƿ���ڣ������ڵĲ��벢�Ѷ�Ӧ�Ķ�����Ϊmap�ļ���ֵ�洢����
typedef map< vector<int>, vector<double> > queryCellMapType;

class MolapQueryComputationBase:public QueryComputationBase
{
private:
	MapTable hdrData;
	MapTable* mapTable;
	int row;

	void mdxHdrMap(vector< vector<QueryTuple*> > &axes);
	void getCartesianProduct(vector< vector<QueryTuple*> > &axes,int axesNum);

	void getMsrFormatStr();
	
protected:
	int** qryPoints;						 ///< ����ParsedMDX��Ķ���ת����ĵ㼯,��ѯ�㼯
	string** qryPointsDimsVals;              ///< ������ѯԭ����ά��ֵ
             
	vector<double> msrValues;				 ///< ��ȡ���ѯ������ж���������
	vector<string> dimValues;				 ///< ��ѯ���ص��Ͻ� 

	//parsedMDXͷ��Ϣ
	vector<int> mdxMsrHdr;
	vector<string> msrFormatStr;             ///< ������ж�����FormatString
	int dimsNum;						     ///< ��ѯ��ά������
	int msrsNum;						     ///< ��ѯ�Ķ�������
	int tuplesNum;                           ///< ��ParsedMdx��õĵ��ѯ��¼����	
	int enterLayer;					         ///< ��ѯ��ڲ�

	ParsedMDX *parsedMdx;                    ///< ����MDX������Ķ���

	AggReader *aggReader;
	
	int msrsLineCount;				         ///< ����ͳ�ƶ���ֵ����������
	bool isNull;                             ///< �ж�ĳ����ѯ��¼�Ƿ����
	queryCellMapType queryCellMap;           ///< ��¼��ѯ�Ĳ�ͬ��¼cells
	vector<int> qrycell;				     ///< ���ڼ���queryCellMap�еĲ�ѯ��¼������Ϊ��ѯ�ļ�
	int slicerTuplesNum;                     ///< ��¼��Ƭ��tuples��Ŀ�����ڽ�������ĺϲ�

	//���������������ںͻ���Ĵ���ӿ�
	//���õ��ѯ��Ӧ���Ͻ�
	virtual void setCacheUpper(vector< string > upper);
	//��õ��ѯ��Ӧ���Ͻ�
	virtual vector<string> getCacheUpper() const;


	virtual inline void pointQuery( int *qry ) = 0;

public:
	/**
	* @brief ��ѯ�㷨����Ĺ��캯��
	*
	* ����MDX������Ķ������Ӷ���ȳ�ʼ������
	*
	* @param parsedMDX MDX������Ķ���
	* @param conn ��ά���ݿ����Ӷ���
	*/
	explicit MolapQueryComputationBase( ParsedMDX* parsedMDX );

	/**
	 * @brief ��ѯ�㷨�������������
	 *
	 * �ͷż������õ�����Դ
	 */
	virtual ~MolapQueryComputationBase();


	/**
	 * @brief ִ�в�ѯ����
	 *
	 * ��ȡMDX������Ķ��󣬽��в�ѯ���㣬�����ز�ѯ��������κβ�ѯ�㷨��Ҫʵ������
	 */
	virtual CellSet query();

	int** getQueryPoints(ParsedMDX *parsedMdx);

};

};
#endif
