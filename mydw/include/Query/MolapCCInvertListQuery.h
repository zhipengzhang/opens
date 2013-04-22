/**
 * @file CCInvertListQuery
 * ѹ���󽻲�ѯ�㷨�ඨ���ļ�
 * ���ļ�����ѹ���󽻲�ѯ�㷨��
 *
 * 
 */
#ifndef _CCINVERTLISTQUERY_H_INCLUDE__
#define _CCINVERTLISTQUERY_H_INCLUDE__

#include "Common.h"
#include "AggReader.h"
#include "MolapQueryComputationBase.h"
#include "QueryResult.h"
#include "AggFileReader.h"

#include "QueryCmptException.h"

#include "./MdxParser/ParsedMDX.h"

#include "./dwconfig/DWConfig.h"
#include "./dwconfig/DWConfiguration.h"
#include "./dwconfig/DWElement.h"

using namespace std;
class ParsedMDX;

namespace QueryComputationMethods
{
/**
 * @brief ѹ���Ķ��󽻲�ѯ�㷨��
 *
 * ����ѹ���Ķ��󽻲�ѯ�㷨����OLAP��ѯ�����ز�ѯ�Ľ����
 * 
 */
class MolapCCInvertListQuery : public MolapQueryComputationBase
{
public:
	/**
     * @brief ѹ���Ķ��󽻲�ѯ�㷨��Ĺ��캯��
     *
     * ����MDX������Ķ����Լ����Ӷ���
     *
     * @param parsedMDX MDX������Ķ���
     * @param conn ��ά���ݿ����Ӷ���
     */
	MolapCCInvertListQuery( ParsedMDX* parsedMDX );
	MolapCCInvertListQuery( ParsedMDX* parsedMDX, string partitionNum );

	/**
     * @brief ѹ���Ķ��󽻲�ѯ�㷨�����������
     *
     * �ͷ����ʼ���������Դ
     *
     */
	virtual ~MolapCCInvertListQuery();
	/**
     * @brief ѹ���Ķ��󽻲�ѯ�㷨��ĵ㼯��ѯ����
     *
     * ִ������OLAP��ѯ���󣬲��������յĲ�ѯ�����QueryResult����
     *
	 * @return �������в�ѯ�Ľ����QueryResult����
     */
	CellSet query();

	vector<Cell> Cellquery();

protected:
	void setCacheUpper(vector< string > upper);		//����ĳ����ѯ������Ͻ�
	vector<string> getCacheUpper() const;			//���ĳ����ѯ������Ͻ�
		/**
     * @brief ���󽻲�ѯ�㷨��Ļ�ȡ��ѯ���ά��ֵ����
     *
     * ���ڻ�ȡ�û�����Ĳ�ѯ������ڵĲ�ѯ��¼��ά��ֵ����
     *
	 * @param layer ����Ĳ�ѯ��¼�����Ͻ�Ĳ���
	 * @param layer ����Ĳ�ѯ��¼�����Ͻ�layer���е�����
     */
	inline void getDimValues(int layer, int row);
    /**
     * @brief ���󽻲�ѯ�㷨��Ļ�ȡ��ѯ�������ֵ����
     *
     * ���ڻ�ȡ�û�����Ĳ�ѯ������ڵĲ�ѯ��¼�Ķ���ֵ����
     *
	 * @param layer ����Ĳ�ѯ��¼�����Ͻ�Ĳ���
	 * @param row ����Ĳ�ѯ��¼�����Ͻ�layer���е�����
     */
	inline void getMsrValues(int layer, int row);
			/**
     * @brief ѹ���Ķ��󽻲�ѯ�㷨��ĵ��ѯ����
     *
     * �����Ѿ������õ�ѹ���ķ�ת����Ԫ��ID�б�ִ�е���OLAP��ѯ���󣬲���ȡ��ѯ���
     *
     */
	inline void pointQuery( int *qry );				//Ҳ��Ϊ�����ѯ�������

private:
		/**
     * @brief ѹ���Ķ��󽻲�ѯ�㷨��Ļ��ά��ֵԪ��ID�б���
     *
     * ���յ��ѯĳһά����ĳ��ά��ֵ����ȡѹ���ķ�ת������ȡ��ά��ֵ��Ԫ��ID�б�
     *
     * @param dims ���ѯ��ĳһ��ά��
     * @param val  ���ѯ��ά���ϵ�ά��ֵ
	 * @return ����Ԫ��ID�б��λ�ü���
     */
	vector<int> getDimsPos(int dims,int val);
		/**
     * @brief ѹ���Ķ��󽻲�ѯ�㷨�������˳������㷨���ز��ҵ�ǰά���в�С��nVal��λ��ֵ����
     *
     * ���յ�ǰ�Ƚ�λ��ֵ�����ڵ�ά��λ�ü��ϺͿ�ʼ���ҵ�λ�ã�
	 * ���ز��ҵ�ǰά���в�С��nVal��λ��ֵ������������һ��λ�÷��أ�2
     *
     * @param nVal ��ǰ�Ƚ�λ��ֵ
     * @param dimsVal  ��ֵ����ά��λ��ֵ����
	 * @param vecPos ��λ��ֵ�����п�ʼ���ҵ�λ��
	 * @return ���ز��ҵ�ǰά���в�С��nVal��λ��ֵ���Ҳ������أ�2
     */
    int findNextMaxVal(int nVal, vector<int> &dimsVal, int &vecPos);
		/**
     * @brief ѹ���Ķ��󽻲�ѯ�㷨��Ļ�õ��ѯ���Ͻ缯�е�λ�ú���
     *
     * ���յ��ѯ����ά���ϲ�ѯά��ֵ��Ԫ��ID�б�ļ��ϣ������ҵ��ĸõ��ѯ��ԭʼ�Ͻ缯�е�λ��ֵ
     *
     * @param dimsPos ���ѯ����ά���ϲ�ѯά��ֵ��Ԫ��ID�б�ļ���
	 * @return �����ҵ��ĸõ��ѯ��ԭʼ�Ͻ缯�е�λ��ֵ
     */
	int findQryPointPos(vector< vector<int> > &dimsPos);
	vector<int> aggsNumPerLayer;                             ///<�Ͻ缯ÿһ�������
	int zeroLayer;                                           ///<�Ͻ缯�յĲ�Ĳ���
	int* perLayerNumBefore;                                  ///<ÿһ��ǰ�������
	map< int, vector<int> >* buffer;
	
ofstream outfile;
ofstream out_file;
ofstream out_time;
};

};
#endif