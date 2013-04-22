#ifndef __SYMTAB_H__
#define __SYMTAB_H__


//!  枚举SymType. 
/*!
  标识符的符号类型.
*/
enum SymType   { 
   IDENT_STR,         /*!< 枚举值一，字符串型的标识符,如Time. */  
   QID_STR,           /*!< 枚举值二，字符串型的引用标识符，如&[Q1]. */ 
   IDENT_NUM,         /*!< 枚举值三，数字型(整数)的标识符，如1998. */ 
   LOGIC_OPER_STR,    /*!< 枚举值四，逻辑运算符，如">" */
   MATH_OPER_STR,
   DECIMAL_NUM   
};

//! 类SymDesc. 
/*!
  一个SymDesc对象是用来记录MDX编译器中对应的一个标识符
  的属性信息的，它是构成MDX编译器的符号表的元素，每个
  SymDesc对象对应与符号表的一项。SymDesc包含5个数据成
  员:标识符的名称、标识符的内容、标识符所在的行、标识
  符的类型和指向下一个SymDesc对象的指针
*/
class SymDesc {
public:
	//!  构造函数. 
    /*!
      \param _name 标识符的名称
	  \param _type 标识符的类型
	  \param _cont 标识符的内容
	  \param _line 标识符所在的行
      \sa  ~SymDesc ()
    */
   SymDesc (char *_name, SymType _type, char *_cont, int _line);
   //! 析构函数
   /*!
      析构SymDesc
    */
   ~SymDesc ();
   //! 打印函数
   /*!
      打印出SymDesc对象的数据成员，即每个符号的属性信息
    */
   void show ();

   char    *name;                 /*!< 符号名. */
   char    *cont;                 /*!< 符号内容. */ 
   SymType  type;                 /*!< 符号类型. */
   int      line;                 /*!< 符号在MDX语句中出现的行号. */ 
   SymDesc *next;                 /*!< 指向下一个SymDesc对象的指针 */ 
   bool     isUminus;
};

//! 类SymTab. 
/*!
  lex词法分析器读到标识符并生成一个对应的SymDesc 对象，
  而符号表则是用来保存这些SymDesc对象的一个链表，符号
  表中的每一项都是一个SymDesc对象。
*/
class SymTab  {
public:
   //!  构造函数. 
   /*!
     构造一个符号表，用于存储SymDesc对象
     \sa  ~SymTab()
   */
   SymTab();
   //! 析构函数
   /*!
      析构SymTab
	  \sa SymTab()
    */
   ~SymTab();
   //!  添加符号表的函数. 
    /*!
      \param symb 一个SymDesc型的指针
	  \return 布尔值
      \sa  find ()
    */
   bool add (SymDesc *symb);
    //!  查找符号表的函数. 
    /*!
	  给出一个符号的名字，对符号表进行查询，并返回
	  其对应的SymDesc对象
      \param name 一个char型的指针
	  \return SymDesc对象的指针
      \sa  find ()
    */
   SymDesc *find (char *name);
   
   //! 打印函数
   /*!
      打印出符号表的信息
   */
   void show ();

private:
   SymDesc *start; /*!< 指向下一个SymDesc的指针. */
};

//}
#endif
