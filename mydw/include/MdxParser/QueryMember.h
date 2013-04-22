//*****************************************************
//Header file of QueryMember.h for the MDX
//Copyright(c) 2007/6/1 by Roger,MDX complier
//*****************************************************
#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

#include <string>
#include <vector>


#ifndef __QUERYMEMBER_H__
#define __QUERYMEMBER_H__
using namespace std;

class calcMemFormat;

/**
 *  ��QueryMember . 
 *  QueryMember ��������ʾMDX��ѯ����ѯ�ĳ�Ա����Ա��MDX��ѯ�е���С���ȣ�
 *  �����ɳ�Ա��ֵ����Ա���ڵ�level���֡���Ա���ڵ�hierarchy���֡���Ա����
 *  �и���Ա���ڵ�level���ֺͳ�Ա���и���Ա��ֵ,��Ա�ĺ�׺���ʽ(����Ǽ���
 *  ��Ա)����.
 *  @see QueryTuple
 *  @see ParsedMDX
 *  @see calcMemFormat
 */
class QueryMember 
{
    public:
	   /**
        * Ĭ�Ϲ��캯��.
        */
		QueryMember();

        /**
         * �������캯��.
         */
		QueryMember(const QueryMember& other);

        /**
         * �������Ĺ��캯��.
		 * @param _hierarchyName ��Ա���ڵ�hierarchy����
		 * @param _levelName     ��Ա���ڵ�level����
         * @param _val           ��Ա��ֵ
		 * @param _ancestorVals  ��Ա�ĸ���Ա��ֵ������Ϊһ��string�͵�vector����
         * @param _ancestorLevels  ��Ա�ĸ���Ա���ڵ�level������Ϊһ��string�͵�vector����
         */
        QueryMember(string& _dimensionName,
					string& _hierarchyName,
					string& _levelName,
					string& _val,
					vector<string>& _ancestorVals,
					vector<string>& _ancestorLevels,
					bool _isAll,
					bool _isCalculated); 


        /**
         * ���ڵõ���Ա��ֵ
		 * @return string
         */
        const string getVal()const;

		/**
         * ���ڵõ���Ա����level������
		 * @return string
         */
        const string getLevelName()const;

		/**
         * ���ڵõ���Ա����hierarchy������
		 * @return string
         */
        const string getHierarchyName()const;

		/**
         * ���ڵõ���Ա����dimension������
		 * @return string
         */
        const string getDimensionName()const;

        /**
         * ���ڵõ���Ա�����и���Ա��ֵ
		 * @return vector<string>
         */
		const vector<string> getAncestorVals()const;

		/**
         * ���ڵõ���Ա���и���Ա���ڵ�level����
		 * @return vector<string>
         */
		const vector<string> getAncestorLevels()const;

		/**
         *  ����QueryMember�Ƿ�Ϊ����member����Ϣ
		 *  @return bool
		 */
         bool hasAll();

		 /**
         *  ����QueryMember�Ƿ�Ϊ�����Ա����Ϣ
		 *  @return bool
		 */
		 bool getIsCalculated();

		 /**
         *  ���ؼ����Ա�ĺ�׺���ʽ��Ϣ
		 *  @return vector<calcMemFormat* >
		 */
		 vector<calcMemFormat* > getCalcFormat();

        /**
         * ���ز�������
         */
		QueryMember& operator=(const QueryMember& other);
		
        /**
         * ���ó�Ա��ֵ
		 * @return void
         */
		void setVal(string _val);
			
        
		/**
         * ���ó�Ա���ڵ�level����
		 * @return void
         */
		void setLevelName(string _levelName);
			
        
		/**
         * ���ó�Ա���ڵ�hierarchy����
		 * @return void
         */
		void setHierarchyName(string _hierarchyName);
			
        /**
         * ���ó�Ա���ڵ�dimension����
		 * @return void
         */
		void setDimensionName(string _dimensionName);
			
        /**
         * ���ó�Ա���и���Ա��ֵ
		 * @return void
         */
		void setAncestorVals(const vector<string>& _ancestorVals);

		/**
         * ���ó�Ա���и���Ա���ڵ�level��ֵ
		 * @return void
         */
		void setAncestorLevels(const vector<string>& _ancestorLevels);

		void setIsAll(bool _isAll);

		/**
         * ���ó�Ա�Ƿ�Ϊ�����Ա
		 * @return void
         */
		void setIsCalculated(bool _isCalculated);

		/**
         * ���ü����Ա�ĺ�׺���ʽ
		 * @return void
         */
		void setCalcFormat(vector<calcMemFormat *> &_format);
        /**
         * ��ӡ��Ա����Ϣ
		 * @return void
         */
		void showMember();

		void _showMember();

		vector<string> getMemberName();

	private:
		/**
         * ���ڱ�ʾ��Ա���ڵ�dimension����
         */
		string dimensionName;
		/**
         * ���ڱ�ʾ��Ա���ڵ�hierarchy����
         */
        string hierarchyName;
		/**
         * ���ڱ�ʾ��Ա���ڵ�level����
         */
        string levelName;
		/**
         * ���ڱ�ʾ��Ա��ֵ
         */
        string val;	  
        /**
         * ���ڱ�ʾ��Ա���еĸ���Ա��ֵ
         */
	    vector<string> ancestorVals;
		/**
         * ���ڱ�ʾ��Ա����Ա���ڵ�level����
         */
		vector<string> ancestorLevels;

		/**
 		 * bool�ͣ������жϳ�Ա�Ƿ���ALL
 		 * ��Hierarchy��hasall�����Ƿ�Ϊ��
 		 */
		 bool isAll;

		 /**
 		 * bool�ͣ������жϳ�Ա�Ƿ�Ϊ�����Ա
 		 */
		 bool isCalculated;

		 /**
 		 * ���ڱ�ʾ�����Ա�ĺ�׺���ʽ
 		 */
		 vector<calcMemFormat* > calcFormat;
};

#endif
