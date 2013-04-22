
/*  A Bison parser, made from yacc.y
    by GNU Bison version 1.28  */

#define YYBISON 1  /* Identify Bison output.  */

#define	OR	257
#define	AND	258
#define	NOT	259
#define	XOR	260
#define	UMINUS	261
#define	IDENTIFIER	262
#define	QUOTED_ID	263
#define	LOGICOPER	264
#define	INT_NUM	265
#define	DEC_NUM	266
#define	ADD	267
#define	AMPERSAND	268
#define	AS	269
#define	AXIS	270
#define	CHAPTERS	271
#define	COLUMNS	272
#define	DIMENSION	273
#define	DIV	274
#define	DOT	275
#define	EMPTY	276
#define	EXCEPT	277
#define	FORMAT	278
#define	FROM	279
#define	IS	280
#define	MEMBER	281
#define	MINUS	282
#define	NON	283
#define	NULLX	284
#define	ON	285
#define	PAGES	286
#define	PERCENTSIGN	287
#define	PROPERTIES	288
#define	ROWS	289
#define	SECTIONS	290
#define	SELECT	291
#define	SET	292
#define	SHARP	293
#define	SINGLEQUOTE	294
#define	STAR	295
#define	STRING	296
#define	WHERE	297
#define	WITH	298

#line 1 "yacc.y"

#pragma warning (disable: 4514 4786)
#include <windows.h>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdarg.h>  //'va_start' is used 
#include <string>
#include <vector>
#include "QueryMember.h"
#include "QueryTuple.h"
#include "ParsedMDX.h"
#include "SymTab.h"
#include "SyntTree.h" 
#include <iostream>

using namespace dwschemac;
//using namespace mdx;

#define DEBUG
// Some yacc (bison) defines
#define YYDEBUG 1 //将这个变量设置为1时则表示启动YACC的调试功能,需要YYERROR_VERBOSE
#define YYERROR_VERBOSE // 给出更加详细的编译信息 

// Error-reporting function must be defined by the caller
void Error (char *format, ...);

SymTab st;     // create the symbol table
SyntTree tree = NULL; // the syntax tree

// vector<string> vecMemInfo;
// vector<QueryMember*> vecMem;
// vector<QueryTuple*> vecTuple;
//vector< vector<QueryTuple*> > vecSet;

#ifdef _LEX_YY_CPP
   int lineno = 1; // line number count; this will be used for error messages later
#else
   // Import some variables
   extern char *yytext;       // add by eason
   extern int lineno;
#endif

extern int yylex();
extern void yyerror(char *msg);
extern FILE *yyin, *yyout;

char* MakeLogicoperName();
char* MakeMathoperName();
char* MakeIdName ();
char* MakeQidName();
char* MakeNumName ();
char* MakeFormName ();

#line 61 "yacc.y"
typedef union {
   char *str;     // a character string
   int  integer;  //a integer number
   double decimal;  // a decimal number
   class SymDesc *symbol;  // entry from symbol table
   class TreeNode *tnode;  // node in the syntax tree
} YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		155
#define	YYFLAG		-32768
#define	YYNTBASE	54

#define YYTRANSLATE(x) ((unsigned)(x) <= 298 ? yytranslate[x] : 108)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    50,
    51,     9,     8,    49,     7,     2,    10,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    52,     2,    53,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     3,     4,     5,     6,
    11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
    21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
    31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
    41,    42,    43,    44,    45,    46,    47,    48
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     9,    10,    13,    16,    18,    20,    22,    26,
    28,    33,    37,    39,    43,    48,    52,    56,    60,    64,
    68,    72,    75,    77,    79,    81,    85,    87,    89,    91,
    95,    97,   100,   102,   106,   110,   112,   114,   116,   118,
   120,   124,   126,   127,   131,   133,   137,   143,   145,   147,
   149,   151,   153,   155,   157,   159,   164,   168,   170,   172,
   174,   178,   180,   185,   192,   194,   196,   200,   202,   204,
   208,   210,   212,   216,   218,   220,   222,   226,   229,   233,
   236,   238,   240,   242,   244,   247,   249,   251,   253,   255,
   256,   259,   261,   263,   265,   267,   269
};

static const short yyrhs[] = {    55,
     0,    56,    41,    76,    29,    97,   101,     0,     0,    48,
    57,     0,    58,    57,     0,    58,     0,    59,     0,    63,
     0,    60,    49,    61,     0,    60,     0,    31,    74,    19,
    64,     0,    62,    49,    61,     0,    62,     0,    98,    71,
    66,     0,    42,    73,    19,    64,     0,    44,    65,    44,
     0,    65,     8,    65,     0,    65,     7,    65,     0,    65,
     9,    65,     0,    65,    10,    65,     0,    50,    65,    51,
     0,     7,    65,     0,    91,     0,    99,     0,   100,     0,
    68,    67,    66,     0,    68,     0,     3,     0,     6,     0,
    69,     4,    68,     0,    69,     0,     5,    69,     0,    70,
     0,    70,    71,    72,     0,    70,    30,    34,     0,    72,
     0,   103,     0,    87,     0,    74,     0,    75,     0,    75,
    25,    95,     0,    95,     0,     0,    77,    49,    76,     0,
    77,     0,    81,    35,    78,     0,    33,    26,    81,    35,
    78,     0,    79,     0,    80,     0,    22,     0,    39,     0,
    36,     0,    21,     0,    40,     0,    99,     0,    20,    50,
    99,    51,     0,    81,    49,    82,     0,    82,     0,    83,
     0,    84,     0,    52,    86,    53,     0,    90,     0,    98,
    50,    81,    51,     0,    98,    50,    81,    49,    85,    51,
     0,    99,     0,    95,     0,    87,    49,    86,     0,    87,
     0,    88,     0,    50,    89,    51,     0,    90,     0,    84,
     0,    90,    49,    89,     0,    90,     0,    92,     0,    92,
     0,    92,    25,    94,     0,    92,    93,     0,    95,    25,
    95,     0,    25,    99,     0,    95,     0,    96,     0,    98,
     0,   104,     0,    18,   104,     0,    95,     0,   105,     0,
   106,     0,   107,     0,     0,    47,   102,     0,    66,     0,
    14,     0,    13,     0,    12,     0,    15,     0,    16,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   116,   119,   143,   145,   149,   154,   156,   158,   163,   168,
   173,   180,   185,   188,   198,   205,   210,   211,   212,   213,
   214,   215,   216,   217,   218,   222,   227,   230,   232,   235,
   237,   239,   241,   243,   245,   246,   249,   252,   259,   263,
   269,   274,   281,   283,   287,   301,   306,   312,   314,   317,
   319,   320,   321,   322,   325,   327,   332,   337,   339,   343,
   345,   346,   349,   354,   368,   370,   373,   378,   382,   386,
   388,   389,   392,   397,   401,   407,   413,   418,   422,   425,
   428,   430,   433,   436,   441,   446,   450,   454,   458,   463,
   465,   476,   481,   494,   506,   518,   533
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","OR","AND",
"NOT","XOR","'-'","'+'","'*'","'/'","UMINUS","IDENTIFIER","QUOTED_ID","LOGICOPER",
"INT_NUM","DEC_NUM","ADD","AMPERSAND","AS","AXIS","CHAPTERS","COLUMNS","DIMENSION",
"DIV","DOT","EMPTY","EXCEPT","FORMAT","FROM","IS","MEMBER","MINUS","NON","NULLX",
"ON","PAGES","PERCENTSIGN","PROPERTIES","ROWS","SECTIONS","SELECT","SET","SHARP",
"SINGLEQUOTE","STAR","STRING","WHERE","WITH","','","'('","')'","'{'","'}'","mdx_statement",
"statement_list","with_formula_specification_opt","formula_specification","single_formula_specification",
"member_specification_list","member_specification","member_property_def_list",
"member_property_definition","nameset_specification_list","formula_string","expression",
"value_expression","or_xor","term4","term3","term2","logic_oper_node","term1",
"name_set","calcmember_name","compound_id","axis_specification_list","axis_specification",
"axis_name_number","axis_name","axis_number","set_specification_list","set_specification",
"set_node","fun_specification","fun_param_list","tuple_specification_list","tuple_specification",
"tuple_node","member_expression_list","member_expression","calcmember_expression",
"member_expression_node","num_identifier","identifier_list_opt","identifier_opt",
"amp_quoted_identifier","cube_specification","identifier_node","int_number_node",
"dec_number_node","where_clause_opt","slicer_specification","logic_oper","quoted_identifier",
"identifier","int_number","dec_number", NULL
};
#endif

static const short yyr1[] = {     0,
    54,    55,    56,    56,    57,    57,    58,    58,    59,    59,
    60,    61,    61,    62,    63,    64,    65,    65,    65,    65,
    65,    65,    65,    65,    65,    66,    66,    67,    67,    68,
    68,    69,    69,    70,    70,    70,    71,    72,    73,    74,
    75,    75,    76,    76,    76,    77,    77,    78,    78,    79,
    79,    79,    79,    79,    80,    80,    81,    81,    82,    83,
    83,    83,    84,    84,    85,    85,    86,    86,    87,    88,
    88,    88,    89,    89,    90,    91,    92,    92,    92,    93,
    94,    94,    95,    95,    96,    97,    98,    99,   100,   101,
   101,   102,   103,   104,   105,   106,   107
};

static const short yyr2[] = {     0,
     1,     6,     0,     2,     2,     1,     1,     1,     3,     1,
     4,     3,     1,     3,     4,     3,     3,     3,     3,     3,
     3,     2,     1,     1,     1,     3,     1,     1,     1,     3,
     1,     2,     1,     3,     3,     1,     1,     1,     1,     1,
     3,     1,     0,     3,     1,     3,     5,     1,     1,     1,
     1,     1,     1,     1,     1,     4,     3,     1,     1,     1,
     3,     1,     4,     6,     1,     1,     3,     1,     1,     3,
     1,     1,     3,     1,     1,     1,     3,     2,     3,     2,
     1,     1,     1,     1,     2,     1,     1,     1,     1,     0,
     2,     1,     1,     1,     1,     1,     1
};

static const short yydefact[] = {     3,
     0,     1,     0,     0,     0,     4,     6,     7,    10,     8,
    43,    95,    94,     0,    40,    42,    83,    84,    87,     0,
    39,     5,     0,     0,     0,     0,    45,     0,    58,    59,
    60,    62,    75,     0,    83,     0,     0,     0,     9,    13,
     0,     0,     0,    72,     0,    68,    69,    71,     0,    43,
     0,     0,     0,    78,     0,     0,     0,    11,    41,    15,
     0,    93,     0,    37,     0,     0,    74,    61,     0,    86,
    90,    44,    96,     0,    53,    50,    52,    51,    54,    46,
    48,    49,    55,    88,    57,     0,    77,    81,    82,    80,
    79,     0,     0,    97,     0,     0,    23,    76,    24,    25,
    89,    12,     0,    14,    27,    31,    33,    36,    38,     0,
    70,     0,    67,     0,     2,     0,    85,     0,    63,    22,
     0,     0,     0,     0,     0,    16,    32,    28,    29,     0,
     0,     0,     0,    47,    73,    92,    91,     0,     0,    66,
    65,    21,    18,    17,    19,    20,    26,    30,    35,    34,
    56,    64,     0,     0,     0
};

static const short yydefgoto[] = {   153,
     2,     3,     6,     7,     8,     9,    39,    40,    10,    58,
    96,   104,   130,   105,   106,   107,    63,   108,    20,    14,
    15,    26,    27,    80,    81,    82,    28,    29,    30,    44,
   139,    45,   109,    47,    66,    48,    97,    33,    54,    87,
    34,    89,    71,    17,    99,   100,   115,   137,    64,    18,
    19,    84,   101
};

static const short yypact[] = {   -38,
    56,-32768,   -26,    77,    77,-32768,    56,-32768,   -15,-32768,
    48,-32768,-32768,    19,    47,-32768,-32768,-32768,-32768,    72,
-32768,-32768,    85,    80,    67,    81,    60,    -5,-32768,-32768,
-32768,-32768,    86,    88,    64,    74,    77,    74,-32768,    66,
   107,    24,    77,-32768,    73,    75,-32768,-32768,    77,    48,
   112,    24,   123,-32768,    77,    24,    62,-32768,-32768,-32768,
    85,-32768,     4,-32768,    13,    89,    90,-32768,    67,-32768,
    96,-32768,-32768,    87,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,   129,-32768,-32768,-32768,-32768,
-32768,   -44,    62,-32768,    62,    12,-32768,    86,-32768,-32768,
-32768,-32768,     4,-32768,    82,   140,    -1,-32768,-32768,   112,
-32768,    77,-32768,     4,-32768,   130,-32768,    71,-32768,-32768,
    16,    62,    62,    62,    62,-32768,-32768,-32768,-32768,     4,
     4,   113,    67,-32768,-32768,-32768,-32768,    98,    99,    88,
-32768,-32768,    95,    95,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,   146,   153,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,   147,-32768,-32768,-32768,    94,-32768,-32768,   118,
     6,   -87,-32768,    27,    54,-32768,    52,    28,-32768,   155,
-32768,   114,-32768,    53,-32768,-32768,    26,   -48,-32768,     7,
-32768,    93,   -14,-32768,    55,   -10,-32768,   -29,-32768,-32768,
    -2,-32768,-32768,   -11,   -45,-32768,-32768,-32768,-32768,    79,
-32768,-32768,-32768
};


#define	YYLAST		167


static const short yytable[] = {    35,
    32,    16,    16,    85,   118,    83,   119,    90,   103,     1,
    46,    41,    62,    35,    11,    12,    13,    31,   122,   123,
   124,   125,   122,   123,   124,   125,   136,    98,   132,    51,
    35,    32,    67,    23,    59,    12,    13,    36,    35,    32,
    35,    32,   147,    52,    35,    32,    70,   110,    31,    41,
    88,    35,    91,    43,    46,   126,    31,    35,    31,    12,
    13,    52,    31,    98,    83,    98,   142,    65,    93,    85,
   138,    37,   141,    12,    13,    25,    73,    94,    12,    13,
    24,    92,    12,    13,   128,    73,     4,   129,    12,    13,
    38,    35,    98,    98,    98,    98,    12,     5,   120,    25,
   121,    67,    35,   124,   125,    42,    35,    32,    50,    49,
    53,    95,    55,    56,    61,   140,    43,    57,    35,    35,
    62,    35,    25,    69,    31,    68,    73,   143,   144,   145,
   146,    74,    75,    76,    12,    13,   116,    73,   112,   111,
    86,    13,   114,   131,    73,   154,   149,    77,   151,   152,
    78,    79,   155,    22,   102,    60,   127,   148,   133,    21,
   150,   113,   134,    72,   117,     0,   135
};

static const short yycheck[] = {    11,
    11,     4,     5,    52,    49,    51,    51,    53,     5,    48,
    25,    23,    14,    25,    41,    12,    13,    11,     7,     8,
     9,    10,     7,     8,     9,    10,   114,    57,    30,    35,
    42,    42,    43,    49,    37,    12,    13,    19,    50,    50,
    52,    52,   130,    49,    56,    56,    49,    35,    42,    61,
    53,    63,    55,    50,    69,    44,    50,    69,    52,    12,
    13,    49,    56,    93,   110,    95,    51,    42,     7,   118,
   116,    25,   118,    12,    13,    52,    15,    16,    12,    13,
    33,    56,    12,    13,     3,    15,    31,     6,    12,    13,
    19,   103,   122,   123,   124,   125,    12,    42,    93,    52,
    95,   112,   114,     9,    10,    26,   118,   118,    49,    29,
    25,    50,    25,    50,    49,   118,    50,    44,   130,   131,
    14,   133,    52,    49,   118,    53,    15,   122,   123,   124,
   125,    20,    21,    22,    12,    13,    50,    15,    49,    51,
    18,    13,    47,     4,    15,     0,    34,    36,    51,    51,
    39,    40,     0,     7,    61,    38,   103,   131,   107,     5,
   133,    69,   110,    50,    86,    -1,   112
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/local/share/bison.simple"
/* This file comes from bison-1.28.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
#ifdef alloca
#define YYSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define YYSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
/* We think this test detects Watcom and Microsoft C.  */
/* This used to test MSDOS, but that is a bad idea
   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
	 instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
/* I don't know what this was needed for, but it pollutes the namespace.
   So I turned it off.   rms, 2 May 1997.  */
/* #include <malloc.h>  */
 #pragma alloca
#define YYSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
		 and on HPUX 10.  Eventually we can turn this on.  */
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifdef YYSTACK_USE_ALLOCA
#define YYSTACK_ALLOC alloca
#else
#define YYSTACK_ALLOC malloc
#endif

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     unsigned int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, unsigned int count)
{
  register char *t = to;
  register char *f = from;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 217 "/usr/local/share/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef YYPARSE_PARAM
int yyparse (void *);
#else
int yyparse (void);
#endif
#endif

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;
  int yyfree_stacks = 0;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  if (yyfree_stacks)
	    {
	      free (yyss);
	      free (yyvs);
#ifdef YYLSP_NEEDED
	      free (yyls);
#endif
	    }
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
#endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
		   size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
		   size * (unsigned int) sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
		   size * (unsigned int) sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 117 "yacc.y"
{tree = yyvsp[0].tnode;;
    break;}
case 2:
#line 124 "yacc.y"
{   
              if ((yyvsp[-5].tnode != NULL)&&(yyvsp[0].tnode != NULL)&&(yyvsp[-3].tnode != NULL))
                  yyval.tnode = new TreeNode(WITHSELTFROMWHERE_LIST, yyvsp[-5].tnode, yyvsp[-3].tnode, yyvsp[-1].tnode, yyvsp[0].tnode);
              else if ((yyvsp[-5].tnode != NULL)&&(yyvsp[0].tnode == NULL)&&(yyvsp[-3].tnode != NULL))
                  yyval.tnode = new TreeNode(WITHSELFROM_LIST, yyvsp[-5].tnode, yyvsp[-3].tnode, yyvsp[-1].tnode);
              else if ((yyvsp[-5].tnode == NULL)&&(yyvsp[0].tnode != NULL)&&(yyvsp[-3].tnode != NULL))
                  yyval.tnode = new TreeNode(SELFROMWHERE_LIST, yyvsp[-3].tnode, yyvsp[-1].tnode, yyvsp[0].tnode);
			  else if ((yyvsp[-5].tnode == NULL)&&(yyvsp[0].tnode == NULL)&&(yyvsp[-3].tnode == NULL))
			      yyval.tnode = new TreeNode(FROM_STMT, yyvsp[-1].tnode);
			  else if ((yyvsp[-5].tnode == NULL)&&(yyvsp[0].tnode != NULL)&&(yyvsp[-3].tnode == NULL))
			      yyval.tnode = new TreeNode(FORM_WHERE,yyvsp[-1].tnode,yyvsp[0].tnode);
              else
                  yyval.tnode = new TreeNode(SELFROM_LIST, yyvsp[-3].tnode, yyvsp[-1].tnode);
         ;
    break;}
case 3:
#line 144 "yacc.y"
{yyval.tnode = NULL;;
    break;}
case 4:
#line 145 "yacc.y"
{yyval.tnode = yyvsp[0].tnode;;
    break;}
case 5:
#line 151 "yacc.y"
{
            yyval.tnode = new TreeNode (FORMULA_STMT, yyvsp[-1].tnode, yyvsp[0].tnode);               
         ;
    break;}
case 6:
#line 154 "yacc.y"
{ yyval.tnode = yyvsp[0].tnode; ;
    break;}
case 7:
#line 157 "yacc.y"
{ yyval.tnode = yyvsp[0].tnode; ;
    break;}
case 8:
#line 158 "yacc.y"
{ yyval.tnode = yyvsp[0].tnode; ;
    break;}
case 9:
#line 165 "yacc.y"
{
               yyval.tnode = new TreeNode(MEM_LIST, yyvsp[-2].tnode, yyvsp[0].tnode);                 
           ;
    break;}
case 10:
#line 168 "yacc.y"
{ yyval.tnode = yyvsp[0].tnode; ;
    break;}
case 11:
#line 175 "yacc.y"
{
            yyval.tnode = new TreeNode(CALCMEM_STMT, yyvsp[-2].tnode, yyvsp[0].tnode);
        ;
    break;}
case 12:
#line 182 "yacc.y"
{
            yyval.tnode = new TreeNode(MEMDEF_LIST, yyvsp[-2].tnode, yyvsp[0].tnode);                           
        ;
    break;}
case 13:
#line 185 "yacc.y"
{ yyval.tnode = yyvsp[0].tnode; ;
    break;}
case 14:
#line 190 "yacc.y"
{
            yyval.tnode = new TreeNode(MEMPDEF_STMT,  yyvsp[-2].tnode, yyvsp[-1].tnode, yyvsp[0].tnode);      
        ;
    break;}
case 15:
#line 200 "yacc.y"
{
            yyval.tnode = new TreeNode(NAMESET_LIST, yyvsp[-2].tnode, yyvsp[0].tnode);    
          ;
    break;}
case 16:
#line 206 "yacc.y"
{ yyval.tnode = yyvsp[-1].tnode; ;
    break;}
case 17:
#line 210 "yacc.y"
{yyval.tnode = new TreeNode(ADD_NODE, yyvsp[-2].tnode, yyvsp[0].tnode);;
    break;}
case 18:
#line 211 "yacc.y"
{yyval.tnode = new TreeNode(MINUS_NODE, yyvsp[-2].tnode, yyvsp[0].tnode);;
    break;}
case 19:
#line 212 "yacc.y"
{yyval.tnode = new TreeNode(MUL_NODE, yyvsp[-2].tnode, yyvsp[0].tnode);;
    break;}
case 20:
#line 213 "yacc.y"
{yyval.tnode = new TreeNode(DIV_NODE, yyvsp[-2].tnode, yyvsp[0].tnode);;
    break;}
case 21:
#line 214 "yacc.y"
{yyval.tnode = yyvsp[-1].tnode;;
    break;}
case 22:
#line 215 "yacc.y"
{ yyvsp[0].tnode->isUminus = true; yyval.tnode = yyvsp[0].tnode; ;
    break;}
case 23:
#line 216 "yacc.y"
{yyval.tnode = yyvsp[0].tnode;;
    break;}
case 24:
#line 217 "yacc.y"
{yyval.tnode = yyvsp[0].tnode;;
    break;}
case 25:
#line 218 "yacc.y"
{yyval.tnode = yyvsp[0].tnode;;
    break;}
case 26:
#line 224 "yacc.y"
{
             yyval.tnode = new TreeNode(VALUE_EXPR, yyvsp[-2].tnode, yyvsp[0].tnode);              
         ;
    break;}
case 27:
#line 227 "yacc.y"
{yyval.tnode = yyvsp[0].tnode;;
    break;}
case 28:
#line 231 "yacc.y"
{yyval.tnode = NULL;;
    break;}
case 29:
#line 232 "yacc.y"
{yyval.tnode = NULL;;
    break;}
case 30:
#line 236 "yacc.y"
{yyval.tnode = new TreeNode(TERM4, yyvsp[-2].tnode, yyvsp[0].tnode);;
    break;}
case 31:
#line 237 "yacc.y"
{yyval.tnode = yyvsp[0].tnode;;
    break;}
case 32:
#line 240 "yacc.y"
{yyval.tnode = new TreeNode(TERM3, yyvsp[0].tnode);;
    break;}
case 33:
#line 241 "yacc.y"
{yyval.tnode = yyvsp[0].tnode;;
    break;}
case 34:
#line 244 "yacc.y"
{yyval.tnode = new TreeNode(TERM2, yyvsp[-2].tnode, yyvsp[-1].tnode, yyvsp[0].tnode);;
    break;}
case 35:
#line 245 "yacc.y"
{yyval.tnode = yyvsp[-2].tnode;;
    break;}
case 36:
#line 246 "yacc.y"
{yyval.tnode = yyvsp[0].tnode;;
    break;}
case 37:
#line 250 "yacc.y"
{yyval.tnode = new TreeNode(LOGIC_OPER); yyval.tnode->symbol = yyvsp[0].symbol;;
    break;}
case 38:
#line 253 "yacc.y"
{yyval.tnode = yyvsp[0].tnode;;
    break;}
case 39:
#line 260 "yacc.y"
{yyval.tnode = yyvsp[0].tnode;;
    break;}
case 40:
#line 265 "yacc.y"
{
                     yyval.tnode = new TreeNode(CALCMEM_NAME, yyvsp[0].tnode);       
                ;
    break;}
case 41:
#line 271 "yacc.y"
{
          yyval.tnode = new TreeNode(COMID_STMT, yyvsp[-2].tnode, yyvsp[0].tnode);       
       ;
    break;}
case 42:
#line 274 "yacc.y"
{yyval.tnode = yyvsp[0].tnode;;
    break;}
case 43:
#line 282 "yacc.y"
{yyval.tnode = NULL;;
    break;}
case 44:
#line 284 "yacc.y"
{
               yyval.tnode = new TreeNode(AXIS_LIST, yyvsp[-2].tnode, yyvsp[0].tnode);              
          ;
    break;}
case 45:
#line 287 "yacc.y"
{yyval.tnode = yyvsp[0].tnode;;
    break;}
case 46:
#line 303 "yacc.y"
{
  				yyval.tnode = new TreeNode(AXIS_STMT, yyvsp[-2].tnode, yyvsp[0].tnode);
  			;
    break;}
case 47:
#line 307 "yacc.y"
{
 			   yyval.tnode = new  TreeNode(NONEMPTY_AXIS_STMT, yyvsp[-2].tnode, yyvsp[0].tnode);
 			;
    break;}
case 48:
#line 313 "yacc.y"
{yyval.tnode = new TreeNode(AXISNAME_STMT, yyvsp[0].tnode);;
    break;}
case 49:
#line 314 "yacc.y"
{yyval.tnode = new TreeNode(AXISNUM_STMT, yyvsp[0].tnode);;
    break;}
case 50:
#line 318 "yacc.y"
{yyval.tnode = NULL;;
    break;}
case 51:
#line 319 "yacc.y"
{yyval.tnode = NULL;;
    break;}
case 52:
#line 320 "yacc.y"
{yyval.tnode = NULL;;
    break;}
case 53:
#line 321 "yacc.y"
{yyval.tnode = NULL;;
    break;}
case 54:
#line 322 "yacc.y"
{yyval.tnode = NULL;;
    break;}
case 55:
#line 326 "yacc.y"
{ yyval.tnode = yyvsp[0].tnode; ;
    break;}
case 56:
#line 327 "yacc.y"
{yyval.tnode = yyvsp[-1].tnode;;
    break;}
case 57:
#line 334 "yacc.y"
{
	        yyval.tnode = new TreeNode(SET_STMT_LIST, yyvsp[-2].tnode, yyvsp[0].tnode);
	   ;
    break;}
case 58:
#line 337 "yacc.y"
{yyval.tnode = yyvsp[0].tnode;;
    break;}
case 59:
#line 340 "yacc.y"
{yyval.tnode = new TreeNode(SET_STMT, yyvsp[0].tnode);;
    break;}
case 60:
#line 344 "yacc.y"
{yyval.tnode = yyvsp[0].tnode;;
    break;}
case 61:
#line 345 "yacc.y"
{yyval.tnode = yyvsp[-1].tnode;;
    break;}
case 62:
#line 346 "yacc.y"
{yyval.tnode = yyvsp[0].tnode;
    break;}
case 63:
#line 351 "yacc.y"
{
	       yyval.tnode = new TreeNode(FUN_STMT, yyvsp[-3].tnode, yyvsp[-1].tnode,NULL);       //不带参数的集合函数
	   ;
    break;}
case 64:
#line 355 "yacc.y"
{
               yyval.tnode = new TreeNode(FUN_STMT, yyvsp[-5].tnode, yyvsp[-3].tnode, yyvsp[-1].tnode);  //带参数的集合函数
           ;
    break;}
case 65:
#line 369 "yacc.y"
{yyval.tnode = yyvsp[0].tnode;;
    break;}
case 66:
#line 370 "yacc.y"
{yyval.tnode = yyvsp[0].tnode;;
    break;}
case 67:
#line 375 "yacc.y"
{
		   yyval.tnode = new TreeNode(TUPLE_LIST, yyvsp[-2].tnode, yyvsp[0].tnode);
	   ;
    break;}
case 68:
#line 378 "yacc.y"
{ yyval.tnode = yyvsp[0].tnode; ;
    break;}
case 69:
#line 383 "yacc.y"
{ yyval.tnode = new TreeNode(TUPLE_STMT, yyvsp[0].tnode); ;
    break;}
case 70:
#line 387 "yacc.y"
{ yyval.tnode = yyvsp[-1].tnode; ;
    break;}
case 71:
#line 388 "yacc.y"
{ yyval.tnode = yyvsp[0].tnode; ;
    break;}
case 72:
#line 389 "yacc.y"
{ yyval.tnode = yyvsp[0].tnode; ;
    break;}
case 73:
#line 394 "yacc.y"
{
		    yyval.tnode = new TreeNode(MEMEXPR_LIST, yyvsp[-2].tnode, yyvsp[0].tnode);
		;
    break;}
case 74:
#line 397 "yacc.y"
{ yyval.tnode = yyvsp[0].tnode; ;
    break;}
case 75:
#line 403 "yacc.y"
{
		     yyval.tnode = new TreeNode(QRYMEM_EXPR, yyvsp[0].tnode);  //读到QRYMEM_EXPR生成QueryMember对象，而不是MEM_NODE
		 ;
    break;}
case 76:
#line 409 "yacc.y"
{
		     yyval.tnode = new TreeNode(CALCMEM_EXPR, yyvsp[0].tnode);  
		 ;
    break;}
case 77:
#line 415 "yacc.y"
{
		     yyval.tnode = new TreeNode(MEM_NODE, yyvsp[-2].tnode, yyvsp[0].tnode);
		 ;
    break;}
case 78:
#line 419 "yacc.y"
{
		     yyval.tnode = new TreeNode(MEM_NODE, yyvsp[-1].tnode, yyvsp[0].tnode);
		 ;
    break;}
case 79:
#line 422 "yacc.y"
{yyval.tnode = new TreeNode(MEM_NODE, yyvsp[-2].tnode, yyvsp[0].tnode);;
    break;}
case 80:
#line 426 "yacc.y"
{yyval.tnode = yyvsp[0].tnode;;
    break;}
case 81:
#line 429 "yacc.y"
{yyval.tnode = yyvsp[0].tnode;;
    break;}
case 82:
#line 430 "yacc.y"
{yyval.tnode = yyvsp[0].tnode;;
    break;}
case 83:
#line 435 "yacc.y"
{yyval.tnode = yyvsp[0].tnode;;
    break;}
case 84:
#line 436 "yacc.y"
{yyval.tnode = new TreeNode (QIDENT_EXPR); yyval.tnode->symbol = yyvsp[0].symbol;;
    break;}
case 85:
#line 442 "yacc.y"
{yyval.tnode = new TreeNode(AMPID_EXPR);yyval.tnode->symbol = yyvsp[0].symbol;;
    break;}
case 86:
#line 447 "yacc.y"
{yyval.tnode = new TreeNode(CUBE_STMT,yyvsp[0].tnode);;
    break;}
case 87:
#line 451 "yacc.y"
{yyval.tnode = new TreeNode (IDENT_EXPR); yyval.tnode->symbol = yyvsp[0].symbol;;
    break;}
case 88:
#line 455 "yacc.y"
{yyval.tnode = new TreeNode (INT_NUM_EXPR); yyval.tnode->symbol = yyvsp[0].symbol;;
    break;}
case 89:
#line 459 "yacc.y"
{yyval.tnode = new TreeNode (DEC_NUM_EXPR); yyval.tnode->symbol = yyvsp[0].symbol;;
    break;}
case 90:
#line 464 "yacc.y"
{yyval.tnode = NULL;;
    break;}
case 91:
#line 466 "yacc.y"
{
             //printf("keyword:WHERE\n");
             yyval.tnode = new TreeNode(WHERE_STMT, yyvsp[0].tnode);
         ;
    break;}
case 92:
#line 477 "yacc.y"
{yyval.tnode = yyvsp[0].tnode;;
    break;}
case 93:
#line 483 "yacc.y"
{
	    yyval.symbol = st.find (yylval.str);
        if (yyval.symbol == NULL)   
        { // doesn't exist yet; create it
            yyval.symbol = new SymDesc (MakeLogicoperName(), LOGIC_OPER_STR, yylval.str, lineno);
            st.add (yyval.symbol);
        }  
	;
    break;}
case 94:
#line 496 "yacc.y"
{
	        yyval.symbol = st.find (yylval.str);
            if (yyval.symbol == NULL)   
            { // doesn't exist yet; create it
                yyval.symbol = new SymDesc (MakeQidName(), QID_STR, yylval.str, lineno);
                st.add (yyval.symbol);
            }  
		 ;
    break;}
case 95:
#line 508 "yacc.y"
{
           yyval.symbol = st.find (yylval.str);
           if (yyval.symbol == NULL)   
              { // doesn't exist yet; create it
                 yyval.symbol = new SymDesc (MakeIdName(), IDENT_STR, yylval.str, lineno);
                 st.add (yyval.symbol);
              }       
         ;
    break;}
case 96:
#line 520 "yacc.y"
{  
		   //符号表暂时只支持字符型的，没法加入和显示int型的
		   //所以把int型的改为字符型的加入和显示
		   char* c = new char[32];
		   _itoa(yylval.integer, c, 10);
           yyval.symbol = st.find (c);
           if (yyval.symbol == NULL)   
           { // doesn't exist yet; create it
              yyval.symbol = new SymDesc (MakeNumName(), IDENT_NUM, c, lineno);
              st.add (yyval.symbol);			  
           }       
        ;
    break;}
case 97:
#line 535 "yacc.y"
{  
		   //符号表暂时只支持字符型的，没法加入和显示double型的
		   //所以把double型的改为字符型的加入和显示
		   char* c = new char[32];
		   sprintf(c,"%lf",yylval.decimal); // double 到 char 
           yyval.symbol = st.find (c);
           if (yyval.symbol == NULL)   
           { // doesn't exist yet; create it
              yyval.symbol = new SymDesc (MakeNumName(), DECIMAL_NUM, c, lineno);
              st.add (yyval.symbol);			  
           }       
        ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 543 "/usr/local/share/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;

 yyacceptlab:
  /* YYACCEPT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;

 yyabortlab:
  /* YYABORT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
}
#line 547 "yacc.y"



// Generate a unique name for a logic operator
char* MakeLogicoperName(){
   char *name = new char [32];
   char num[32];
   static l = 0;
   _itoa(++l,num,10);
   strcpy (name, "logicOper");
   strcat (name, num);
   return name;
}
// Generate a unique name for a mathematical operator
char* MakeMathoperName(){
   char *name = new char [32];
   char num[32];
   static l = 0;
   _itoa(++l,num,10);
   strcpy (name, "mathematicalOper");
   strcat (name, num);
   return name;
}

// Generate a unique name for a string identifier
char* MakeIdName(){
   char *name = new char [32];
   char num[32];
   static l = 0;
   //sprintf (num, "%d", ++l);
   _itoa(++l,num,10);
   strcpy (name, "unquotedId");
   strcat (name, num);
   //printf("MakeIdName:%d->%s\n",l,name);
   return name;
}

// Generate a unique name for a number identifier
char* MakeNumName(){
   char *name = new char [32];
   char num[32];
   static m = 0;
   //sprintf (num, "%d", ++m);

   _itoa(++m,num,10);
   strcpy (name, "numberId"); 
   strcat (name, num);
   //printf("MakeNumName:%d->%s\n",m,name);
   return name;
}

// Generate a unique name for formula_string
char* MakeFormName(){
   char *name = new char [32];
   char num[32];   
   static n = 0;
   //sprintf (num, "%d", ++n);
   _itoa(++n,num,10);
   strcpy (name, "fromulaStr"); 
   strcat (name, num);
   //printf("MakeFormName:%d->%s\n",n,name);
   return name;
}

char* MakeQidName(){
   char *name = new char [32];
   char num[32];
   static s = 0;
   //sprintf (num, "%d", ++s);
    _itoa(++s,num,10);
   strcpy (name, "quotedId"); 
   strcat (name, num);
   //printf("MakeQidName:%d->%s\n",s,name);
   return name;
}


int errors = 0;

// Function used to report errors
void Error (char *format, ...)   {
  
   errors++;
   printf("syntax error at Line %d: %s at %s\n", lineno, format, yytext);  // add by eason

}

// Show an error count
int ErrorSummary ()  {
   fprintf (stderr, "%d syntax error(s) were found.\n", errors);
   return errors;            // add by eason
}

// Function called by the parser when an error occurs while parsing
// (parse error or stack overflow)
void yyerror(char *msg) {
   Error (msg);
}
