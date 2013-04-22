typedef union {
   char *str;     // a character string
   int  integer;  //a integer number
   double decimal;  // a decimal number
   class SymDesc *symbol;  // entry from symbol table
   class TreeNode *tnode;  // node in the syntax tree
} YYSTYPE;
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


extern YYSTYPE yylval;
