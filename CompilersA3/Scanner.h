/*************************************************************
* File name: Scanner.h
* Compiler: MS Visual Studio 2019
* Author: Paulo Sousa (from original work of Svillen Ranev) - altered by Mostapha A
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 8   /* variable identifier length */
#define ERR_LEN 20  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1   /* Value for run-time error */

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/* 0:	Error token */
	VID_T,		/* 1:	Variable identifier: Any variable name token */
	UNL_T,		/* 2:	Underline Token */
	DSH_T,		/* 3:	Dash token */
	QOT_T,		/* 4:	Quote token */
	INL_T,		/* 5:	Integer literal token */
	FPL_T,		/* 6:	Floating point literal token */
	STR_T,		/* 7:	String literal token */
	SCC_OP_T,	/* 8:	String concatenation operator token: (.) */
	ASS_OP_T,	/* 9:	Assignment operator token (is) */
	ART_OP_T,	/* 10:	Arithmetic operator token */
	REL_OP_T,	/* 11:	Relational operator token */
	LOG_OP_T,	/* 12:	Logical operator token */
	LPR_T,		/* 13:	Left parenthesis token */
	RPR_T,		/* 14:	Right parenthesis token */
	LBR_T,		/* 15:	Left brace token */
	RBR_T,		/* 16:	Right brace token */
	KW_T,		/* 17:	Keyword token */
	EOS_T,		/* 18:	End of statement (newline) */
	RTE_T,		/* 19:	Run-time error token */
	SEOF_T		/* 20:	Source end-of-file token */
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	faiyum_int codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	faiyum_int intValue;						/* integer literal attribute (value) */
	faiyum_int keywordIndex;					/* keyword index in the keyword table */
	faiyum_int contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	faiyum_flt floatValue;					/* floating-point literal attribute (value) */
	faiyum_chr idLexeme[VID_LEN + 1];		/* variable identifier token attribute */
	faiyum_chr errLexeme[ERR_LEN + 1];		/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	faiyum_flg flags;			/* Flags information */
	union {
		faiyum_int intValue;				/* Integer value */
		faiyum_flt floatValue;			/* Float value */
		faiyum_nul* stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	faiyum_int code;					    /* token code */
	TokenAttribute attribute;		/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner
 *  '=' , ' ' , '(' , ')' , '{' , '}' , == , <> , '>' , '<' , ';',
 *  white space, @comment@ , ',' , ';' , '-' , '+' , '*' , '/', ## ,
 *  .&., .|. , .!. , SEOF.
 */

 /* TO_DO: Error states and illegal state */
#define ES  9		/* Error state with no retract */
#define ER  10		/* Error state with retract */
#define IS -1		/* Illegal state */

 /* TO_DO: State transition table definition */
#define TABLE_COLUMNS 11

/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL4A '_'
#define CHRCOL6 '.'
#define CHRCOL4B '-'
#define CHRCOL2 '\"'
/*
#define CHRCOL4 '#'
#define CHRCOL5 '%'
#define CHRCOL6 '$'
#define CHRCOL7 '&'
*/
/* These constants will be used on VID function */
//#define IVIDPREFIX '#'
//#define FVIDPREFIX '%'
//#define SVIDPREFIX '$'
//#define MNIDPREFIX '&'

/* TO_DO: Transition table - type of states defined in separate table */
static faiyum_int transitionTable[][TABLE_COLUMNS] = {
	/*			[A-z],	[0-9],	",		EOFS,	_|-,	OTHER,	.,		*/
	/*			L(0),	D(1),	Q(2),	E(3),	U(4),	O(5),   (.)(6)	*/
	/* S00 */	{7,		3,		1,		ER,		ER,		ER,		ER},	/* NOAS */
	/* S01 */	{1,		1,		2,		ER,		1,		1,		1},		/* NOAS */
	/* S02 */	{IS,	IS,		IS,		IS,		IS,		IS,		IS},	/* ASNR (SL) */
	/* S03 */	{6,		3,		6,		ER,		6,		6,		4},		/* NOAS */
	/* S04 */	{5,		4,		5,		ER,		5,		5,		5},		/* NOAS */
	/* S05 */	{IS,	IS,		IS,		IS,		IS,		IS,		IS},	/* ASNR (FL) */
	/* S06 */	{IS,	IS,		IS,		IS,		IS,		IS,		IS},	/* ASNR (IL) */
	/* S07 */	{7,		7,		8,		ER,		7,		8,		8},		/* NOAS */
	/* S08 */	{IS,	IS,		IS,		IS,		IS,		IS,		IS},	/* ASWR (VID) */
	/* S09 */	{IS,	IS,		IS,		IS,		IS,		IS,		IS},	/* ASNR (ERR)   */
	/* S10 */	{IS,	IS,		IS,		IS,		IS,		IS,		IS}		/* ASWR (Err) */ };

/* Define accepting states types */
#define NOAS	0		/* not accepting state */
#define ASNR	1		/* accepting state with no retract */
#define ASWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static faiyum_int stateType[] = {
	NOAS, /* 00 */
	NOAS, /* 01 */
	ASNR, /* 02 (SL - String Literal) */
	NOAS, /* 03 */
	NOAS, /* 04 */
	ASNR, /* 05 (FL - Float Literal) */
	ASNR, /* 06 (IL - Integer Literal) */
	NOAS, /* 07 */
	ASWR, /* 08 (VID) - Variables and Keys */
	ASNR, /* 09 (ERR) */
	ASWR  /* 10 (ERR) */
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
faiyum_int startScanner(BufferPointer psc_buf);
static faiyum_int nextClass(faiyum_chr c);			/* character class function */
static faiyum_int nextState(faiyum_int, faiyum_chr);		/* state machine function */
//void multiLineComment();
//void singleLineComment();								/* for comments*/

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(faiyum_chr* lexeme);

/* Declare accepting states functions */
// Token funcMID(faiyum_chr lexeme[]);
Token funcVID(faiyum_chr lexeme[]);
Token funcIL(faiyum_chr lexeme[]);
Token funcFPL(faiyum_chr lexeme[]);
Token funcSL(faiyum_chr lexeme[]);
Token funcKEY(faiyum_chr lexeme[]);
Token funcErr(faiyum_chr lexeme[]);

/*
 * Accepting function (action) callback table (array) definition
 * If you do not want to use the typedef, the equvalent declaration is:
 */

 /* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[] = {
	NULL,		/* 00 */
	NULL,		/* 01 */
	funcSL,		/* 02 */
	NULL,		/* 03 */
	NULL,		/* 04 */
	funcFPL,	/* 05 */
	funcIL,		/* 06 */
	NULL,		/* 07 */
	funcKEY,	/* 08 */
	funcErr,	/* 09 */
	funcErr		/* 10 */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 16

/* TO_DO: Define the list of keywords */
static faiyum_chr* keywordTable[KWT_SIZE] = {
	"Var",
	"Int",
	"Float",
	"String",
	"function",
	"returns",
	"output",
	"input",
	"is",
	"CONST",
	"IF",
	"ELSE",
	"FOR",
	"IN",
	"LOOP",
	"WHILE"
};

#endif
