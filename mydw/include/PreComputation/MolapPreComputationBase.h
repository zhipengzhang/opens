
/**
 * @file MolapPreComputationBase.h
 *
 * MOLAP�ܹ���������Ԥ�����ļ�
 *
 * @author DBNCLab
 * Copyright(c) 2007 by School Of Computer Science & Engineering, South China University of Technology, Guangzhou, Guangdong, P.R.C. 
 *
 */
#ifndef _MOLAPPRECOMPUTATIONBASE_H_INCLUDE__
#define _MOLAPPRECOMPUTATIONBASE_H_INCLUDE__

#include "PreComputationBase.h"
#include "PreCmptException.h"
#include "AggWriter.h"
#include "AggDBWriter.h"
#include "AggFileWriter.h"

#include "Common.h"
#include "FileHandle.h"

#include "DWSchemac/Dimension.h"
#include "DWSchemac/Hierarchy.h"
#include "DWSchemac/XSchemas.h"
#include "DWSchemac/Level.h"
#include "DWSchemac/XCube.h"
#include "DWSchemac/XSchema.h"
#include "DWSchemac/Measure.h"
#include "xodbc/XODBCDatabase.h"

#include "./dwconfig/DWConfig.h"
#include "./dwconfig/DWConfiguration.h"
#include "./dwconfig/DWElement.h"

using namespace xodbc;
using namespace dwschemac;

namespace PreCmpt{

typedef set<string> column;
typedef map<string,int> Mapper;                                            ///< ά��ֵӳ��Ϊ���ֵ�ӳ���

typedef enum _INTYPE{ TXT,DB }INTYPE;                                                     ///<������������TXT:�ı����� DB:���ݿ�����

const int ALL = 0;
const int AGGFUNNUM = 9;                                                   ///< ����ۼ���������

class MolapPreComputationBase;
typedef double (MolapPreComputationBase::* aggFun)( double **msrData, int bPos, int ePos, int msrNum );

class MolapPreComputationBase : public PreComputationBase
{
protected:
	int** dimData;
	double** msrData;
	int* card;
	int dimsNum;
	int msrsNum;
	int tuplesNum;

	string* mapData;
	vector<string> hdrData;
	AggWriter* aggWriter;
	
	static XODBCDatabase InXDB;
	static XODBCRecordset* pRS;
	
	INTYPE inputType;
	string InDir;

	vector<int> aggFunOrder;
	aggFun aggFunLib[AGGFUNNUM];

	void setAttribute();
	void loadDataTxt();
	void loadDataTable();
	void loadDataTxt( int start, int end );
	void loadDataTable( int start, int end );
	string buildSQL();                                                      ///< ����XCube������SQL
	inline void addAggFunOrder( const string& aggFunType );                           ///< ��Ӿۼ�������־

	/**
	* @brief ���漸������Ϊϵͳ��֧�ֵĸ��־ۼ�����
	*/
	double sumFun(double **msrData, int bPos, int ePos, int msrNum);        ///< ���
	double countFun(double **msrData, int bPos, int ePos, int msrNum);      ///< ��Ԫ�ظ���
	double avgFun(double **msrData, int bPos, int ePos, int msrNum);        ///< ��ƽ��ֵ
	double maxFun(double **msrData, int bPos, int ePos, int msrNum);        ///< �����ֵ
	double minFun(double **msrData, int bPos, int ePos, int msrNum);        ///< ����Сֵ
	double firstFun(double **msrData, int bPos, int ePos, int msrNum);      ///< ���һ��Ԫ��
	double lastFun(double **msrData, int bPos, int ePos, int msrNum);       ///< �����һ��Ԫ��
	double distinctFun(double **msrData, int bPos, int ePos, int msrNum);   ///< ��ͬԪ�صĸ���
	double mediumFun(double **msrData, int bPos, int ePos, int msrNum);     ///< ���м�ֵ

public:
	MolapPreComputationBase( XCube* cube );
	virtual ~MolapPreComputationBase();

	virtual void excutePreCompute()=0;   ///<ִ��Ԥ����
	int getTuplesNum();
	virtual void loadData();
	virtual void loadNextData( int start, int end, string partitionNum );
};

}
#endif
