/*************************************************************
* File name: Parser.h
* Compiler: MS Visual Studio 2019
* Author: Paulo Sousa (based on prof. Svillen Ranev work), Mostapha Abdelaziz
* Purpose: This file is the main header for Parser (.h)
*************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef BUFFER_H_
#include "Buffer.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */

/* TO_DO: Adjust all datatypes to your language */
static Token lookahead;
faiyum_int syntaxErrorNumber = 0;
extern Buffer* stringLiteralTable;
extern faiyum_int line;
extern Token tokenizer();
extern faiyum_chr* keywordTable[];

/* TO_DO: Adjust your language name here */
#define STR_LANGNAME "Faiyum"

/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */

/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
	Var,
	Int,
	Float,
	String,
	function,
	returns,
	output,
	input,
	is,
	CONST,
	IF,
	ELSE,
	FOR,
	IN,
	LOOP,
	WHILE
};

/* Function definitions */
faiyum_nul startParser();
faiyum_nul matchToken(faiyum_int, faiyum_int);
faiyum_nul syncErrorHandler(faiyum_int);
faiyum_nul printError();

/* TO_DO: Place ALL non-terminal function declarations */
faiyum_nul additiveArithmeticExpression();
faiyum_nul additiveArithmeticExpressionPrime();
faiyum_nul unaryArithmeticExpression();
faiyum_nul arithmeticExpression();
faiyum_nul assignmentExpression();
faiyum_nul assignmentStatement();
//faiyum_nul codeSession();
//faiyum_nul dataSession();
faiyum_nul fltVariableIdentifier();
faiyum_nul fltVarList();
faiyum_nul fltVarListPrime();
faiyum_nul inputStatement();
faiyum_nul multiplicativeArithmeticExpression();
faiyum_nul multiplicativeArithmeticExpressionPrime();
faiyum_nul fltVarListDeclaration();
faiyum_nul optVarListDeclarations();
faiyum_nul optionalStatements();
faiyum_nul outputStatement();
faiyum_nul outputVariableList();
faiyum_nul primaryArithmeticExpression();
faiyum_nul program();
faiyum_nul statement();
faiyum_nul statements();
faiyum_nul statementsPrime();
faiyum_nul variableIdentifier();
faiyum_nul variableList();
faiyum_nul variableListPrime();
faiyum_nul varListDeclarations();
faiyum_nul varListDeclaration();
faiyum_nul varListDeclarationsPrime();
faiyum_nul iterationStatement();
faiyum_nul selectionStatement();
faiyum_nul conditionalExpression();
faiyum_nul logicalOrExpression();
faiyum_nul logicalOrExpressionPrime();
faiyum_nul logicalAndExpression();
faiyum_nul logicalAndExpressionPrime();
faiyum_nul logicalNotExpression();
faiyum_nul relationalExpression();
faiyum_nul relationalAExpression();
faiyum_nul relationalAExpressionPrime();
faiyum_nul relationalSExpression();
faiyum_nul relationalSExpressionPrime();
faiyum_nul declarationStatement();

#endif
