#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif
#ifndef __QUERYTUPLE_H__
#define __QUERYTUPLE_H__
#include <vector>
#include "QueryMember.h"

using namespace std;
//namespace mdx{
/**
 *  ��QueryTuple. 
 *  QueryTuple���ڼ�¼MDX��ѯ�Ķ�ά���ݿ飬��Ԫ�����Ϣ��
 *  ����QueryMember��һ��������������������Ƭ.
 *  @see QueryMember
 *  @see ParsedMDX
 */
class QueryTuple
{   
    public:
            /**
			  *  Ĭ�Ϲ��캯��. 
              */
            QueryTuple(); 
			/**
			  *  �������캯��. 
              */
			QueryTuple(const QueryTuple& qt);
			/**
			  *  �������Ĺ��캯��. 
			  *  @param _members ������vector<QueryMember>
              */
            QueryTuple(vector<QueryMember*>& _members);
            /**
			  *  ��������Ԫ���е����г�Ա. 
			  *  @return vector<QueryMember>
              */
            const vector<QueryMember*> getMembers()const;
            /**
			 *  ���ز�������
             */
		    QueryTuple& operator=(const QueryTuple& other);
			
			/**
			  *  �ж�QueryTuple�����Ƿ�Ϊ�գ����Ƿ񲻴���QueryMember����
			  *  @return bool
              */
			bool empty()const;
            /**
			  *  ����QueryTuple����
			  *  @return void
              */
            void setTuple(vector<QueryMember*>& _members);

			/**
			  *  չʾQueryTuple
			  *  @return void
              */
			void showTuple();

	 private:
		    /**
			  *  һ��QueryMember�����������Դ洢QueryMember����
              */
            vector<QueryMember*> members;
	            
};

//}
#endif
