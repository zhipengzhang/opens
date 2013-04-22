#ifndef __PARSEDMDX_H__
#define __PARSEDMDX_H__

#pragma warning (disable: 4514 4786)

#include <string>
#include "QueryTuple.h"
#include "calculatedMember.h"

using namespace std;
/**
 *  ��ParsedMDX. 
 *  ParsedMDX ��QueryTuple��һ����������¼�˴���ѯ������Ԫ����Ϣ
 *  ParsedMDX ��Ԥ����ģ������Ҫ�ģ���MDX����������������ѯ����
 *  @see QueryTuple
 *  @see QueryMember
 */
class ParsedMDX
{
    public:
		/**
          *  Ĭ�Ϲ��캯��
          */
        ParsedMDX();

	    /**
          *  �������캯��. 
          */
		ParsedMDX(const ParsedMDX& );

        /**
          *  �������Ĺ��캯��
		  *  @param _cubeName �����������
		  *  @param _schemaName MDX��ѯ���������
		  *  @param _slicer  һ����Ƭ����QueryTuple����
		  *  @param _pCaclMember  �洢�����Ա������
		  *  @param _axes ��ѯ�����Ϣ����һ�����������������ڴ洢��ѯ�ĳ�Ա��Ԫ�����Ϣ
          */
        ParsedMDX(string _cubeName,
			      string _schemaName,
				  vector<QueryTuple*>& _slicer,
				  vector<calculatedMember*>& _pCaclMember,
                  const vector< vector<QueryTuple*> >& _axes,
				  bool _nonempty);

        /**
          *  ��������
          */
        ~ParsedMDX();
		
		/**
         * ���ڵõ�MDX��ѯ������������ڵ�schema������
		 * @return string
         */
        const string getSchemaName()const;

        /**
         * ���ڵõ�MDX��ѯ�������������
		 * @return string
         */
        const string getCubeName()const;

		/**
         * ���ڵõ����ϵ����г�Ա��Ԫ��
		 * @return vector< vector<QueryTuple> >
         */
        vector< vector<QueryTuple*> > getAxes();


		/**
         * ���ڵõ����м����Ա
		 * @return vector< calculatedMember* >
         */
		vector<calculatedMember*> getCalcMember();


        /**
         * ���ڵõ���Ƭ����Ϣ
		 * @return QueryTuple
         */
        const vector<QueryTuple*> getSlicer()const;

        /**
         * ��������������
		 * @param _sechemaName ������
		 * @return void
         */
		void setSchemaName(string _schemaName);

		/**
         * ����������Ƭ��
		 * @param _slicer ��Ƭ��QueryTuple����
		 * @return void
         */
		//void setSlicer(const QueryTuple& _slicer);
			//throw (MDXParsedException);

		/**
         * �������������ᣨ��ȥ��Ƭ�ᣩ
		 * @param _axes ��ѯ�ᣬ����Ϊvector< vector<QueryTuple> >
		 * @return void
         */
		void setAxes(const vector< vector<QueryTuple*> >& _axes);

       /**
         * ����չʾParsedMDX������
		 * @return void
         */
		void showParsedMDX();

    private:
	    /**
          *  �����������
          */
        string cubeName;

		/**
          *  ��������
          */
	    string schemaName;

		/**
          *  ��Ƭ,���ڴ洢��Ƭ��
		  *  ���ж���һ���ض���MDX��ѯ��䣬slicerҪ�洢������WHERE
		  *  �Ӿ��е���Ƭ�ͳ�������MDX��ѯ�ᣨSELECT���е�Cube�е����е�
		  *  ά�ȵ����еĶ���Member������Ҫ��˳��洢����û�г����ڲ�ѯ��
		  *  ��ά�����������Ƭ��,����������Ҫ�����ڲ�ѯģ���XMLA���裻
		  *  �磺һ����������3��ά������ΪProduct,Time��Store��Timeά������
		  *  WHERE�У�����where [Time].[All times].[1997]����Product��Stroe
		  *  �Ķ����Ա�ֱ�Ϊ[All products]��[All stroes]����Ҫ���δ洢
		  *  [Product].[All products],[Time].[All times].[1997]��
		  *  [Stroe].[All stroes]��������QueryTuple��
          */
        vector<QueryTuple*> slicer; 

		/**
          *  ��ѯ��
          */
		vector< vector<QueryTuple*> > axes;


		/**
          *  �����Ա
          */
		vector<calculatedMember*> pCaclMember;

		/**
		 *  �Ƿ���ʾ�յ�ֵ                                                       
		 */
		bool nonEmpty;
};

//}
#endif
