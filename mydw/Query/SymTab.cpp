#include <stdio.h>
#include <iostream.h>
#include <string.h>
#include "MdxParser/SymTab.h"


SymDesc::SymDesc (char *_name, SymType _type, char *_cont, int _line)    
{
   name = _name; // name of the symbol
   type = _type; // type of the symbol
   cont = _cont; // contents of the symbol
   line = _line; // line it was first encountered
   next = NULL;  // next symbol in list
}

SymDesc::~SymDesc () 
{
   if (this == NULL)   
	   return;
   if (name != NULL)   
	   delete [] name;
   if (cont != NULL)   
	   delete [] cont;
   if (next != NULL)
	   delete next;
}

void SymDesc::show ()   
{
   if (type == IDENT_STR)
      printf ("| %-20s | %4d | (= %s)\n", name, line, cont);
   else if (type == IDENT_NUM)
      printf ("| %-20s | %4d | (= %s)\n", name, line, cont);
   else if (type == QID_STR)
      printf ("| %-20s | %4d | (= [%s])\n", name, line, cont);
   else if (type == LOGIC_OPER_STR)
      printf ("| %-20s | %4d | (= [%s])\n", name, line, cont);
   else 
	  printf ("| %-20s | %4d | (= \"%s\")\n", name, line, cont);
}

/*==================================================================*/
SymTab::SymTab()   {
   start = NULL;
}

SymTab::~SymTab()   {
   delete start;
}

bool SymTab::add (SymDesc *symb)  {
   if (find (symb->name) != NULL)
      return false;
   if (start == NULL)
      start = symb;
   else  
   {
      SymDesc *search = start;
      while (search->next != NULL)
         search = search->next;
      search->next = symb;
   }
   return true;
}

SymDesc* SymTab::find (char *name)   {
   SymDesc *search = start;
   while (search != NULL && strcmp (search->name, name) != 0)
      search = search->next;
   return search;
}


void SymTab::show ()  {
   SymDesc *search = start;
   puts ("+----------------------+------+");
   puts ("| Name                 | Line |");
   puts ("+----------------------+------+");
   while (search != NULL)  {
      search->show ();
      search = search->next;
   }
   puts ("+----------------------+------+");
}
