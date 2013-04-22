#ifndef __SYMTAB_H__
#define __SYMTAB_H__


//!  ö��SymType. 
/*!
  ��ʶ���ķ�������.
*/
enum SymType   { 
   IDENT_STR,         /*!< ö��ֵһ���ַ����͵ı�ʶ��,��Time. */  
   QID_STR,           /*!< ö��ֵ�����ַ����͵����ñ�ʶ������&[Q1]. */ 
   IDENT_NUM,         /*!< ö��ֵ����������(����)�ı�ʶ������1998. */ 
   LOGIC_OPER_STR,    /*!< ö��ֵ�ģ��߼����������">" */
   MATH_OPER_STR,
   DECIMAL_NUM   
};

//! ��SymDesc. 
/*!
  һ��SymDesc������������¼MDX�������ж�Ӧ��һ����ʶ��
  ��������Ϣ�ģ����ǹ���MDX�������ķ��ű��Ԫ�أ�ÿ��
  SymDesc�����Ӧ����ű��һ�SymDesc����5�����ݳ�
  Ա:��ʶ�������ơ���ʶ�������ݡ���ʶ�����ڵ��С���ʶ
  �������ͺ�ָ����һ��SymDesc�����ָ��
*/
class SymDesc {
public:
	//!  ���캯��. 
    /*!
      \param _name ��ʶ��������
	  \param _type ��ʶ��������
	  \param _cont ��ʶ��������
	  \param _line ��ʶ�����ڵ���
      \sa  ~SymDesc ()
    */
   SymDesc (char *_name, SymType _type, char *_cont, int _line);
   //! ��������
   /*!
      ����SymDesc
    */
   ~SymDesc ();
   //! ��ӡ����
   /*!
      ��ӡ��SymDesc��������ݳ�Ա����ÿ�����ŵ�������Ϣ
    */
   void show ();

   char    *name;                 /*!< ������. */
   char    *cont;                 /*!< ��������. */ 
   SymType  type;                 /*!< ��������. */
   int      line;                 /*!< ������MDX����г��ֵ��к�. */ 
   SymDesc *next;                 /*!< ָ����һ��SymDesc�����ָ�� */ 
   bool     isUminus;
};

//! ��SymTab. 
/*!
  lex�ʷ�������������ʶ��������һ����Ӧ��SymDesc ����
  �����ű���������������ЩSymDesc�����һ����������
  ���е�ÿһ���һ��SymDesc����
*/
class SymTab  {
public:
   //!  ���캯��. 
   /*!
     ����һ�����ű����ڴ洢SymDesc����
     \sa  ~SymTab()
   */
   SymTab();
   //! ��������
   /*!
      ����SymTab
	  \sa SymTab()
    */
   ~SymTab();
   //!  ��ӷ��ű�ĺ���. 
    /*!
      \param symb һ��SymDesc�͵�ָ��
	  \return ����ֵ
      \sa  find ()
    */
   bool add (SymDesc *symb);
    //!  ���ҷ��ű�ĺ���. 
    /*!
	  ����һ�����ŵ����֣��Է��ű���в�ѯ��������
	  ���Ӧ��SymDesc����
      \param name һ��char�͵�ָ��
	  \return SymDesc�����ָ��
      \sa  find ()
    */
   SymDesc *find (char *name);
   
   //! ��ӡ����
   /*!
      ��ӡ�����ű����Ϣ
   */
   void show ();

private:
   SymDesc *start; /*!< ָ����һ��SymDesc��ָ��. */
};

//}
#endif
