/*************************************************************
* File name: Parser.c
* Compiler: MS Visual Studio 2019
* Author: Svillen Ranev - Paulo Sousa, Mostapha Abdelaziz
* Professor: Paulo Sousa
* Purpose: This file contains all functionalities from Parser.
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/* TO_DO: For all functions adjust the datatypes used in your language */

/*************************************************************
 * Process Parser
 ************************************************************/
/* TO_DO: This is the function to start the parser - check your program definition */

faiyum_nul startParser() {
	lookahead = tokenizer();
	if (lookahead.code != SEOF_T) {
		program();
	}
	matchToken(SEOF_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}


/*************************************************************
 * Match Token
 ************************************************************/
/* TO_DO: This is the main code for match - check your definitions */

faiyum_nul matchToken(faiyum_int tokenCode, faiyum_int tokenAttribute) {
	faiyum_int matchFlag = 1;
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType != tokenAttribute)
			matchFlag = 0;
	default:
		if (lookahead.code != tokenCode)
			matchFlag = 0;
	}
	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag) {
		lookahead = tokenizer();
		if (lookahead.code == ERR_T) {
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	else
		syncErrorHandler(tokenCode);
}

/*************************************************************
 * Syncronize Error Handler
 ************************************************************/
/* TO_DO: This is the function to handler error - adjust basically datatypes */

faiyum_nul syncErrorHandler(faiyum_int syncTokenCode) {
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
}

/*************************************************************
 * Print Error
 ************************************************************/
/* TO_DO: This is the function to error printing - adjust basically datatypes */

faiyum_nul printError() {
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case ERR_T:
		printf("%s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
		/*
	case MNID_T:
		printf("%s\n", t.attribute.idLexeme);
		break;
		*/
	case STR_T:
		printf("%s\n", getContent(stringLiteralTable, t.attribute.contentString));
		break;
	case KW_T:
		printf("%s\n", keywordTable[t.attribute.codeType]);
		break;
		//case COM_T:
	case LPR_T:
	case RPR_T:
	case LBR_T:
	case RBR_T:
	case EOS_T:
		printf("NA\n");
		break;
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
	}
}

/*************************************************************
 * Program statement
 * BNF: <program> -> MAIN { <opt_statements> }
 * FIRST(<program>)= { MNID_T }.
 ************************************************************/
/* TO_DO: Adjust this function to respect your grammar */

faiyum_nul program() {
	switch (lookahead.code) {
	case KW_T:
		//printf("\n\nin function case\n\n");
		// function main
		//if (strncmp(lookahead.attribute.idLexeme, "function", 9) == 0) {
			//printf("\n\nbefore function match token\n\n");
			matchToken(KW_T, function);
			//matchToken(VID_T, NO_ATTR);
			//printf("\n\nbefore var identifier\n\n");

			variableIdentifier();
			//printf("\n\nbefore l bracket match token\n\n");
			matchToken(LBR_T, NO_ATTR);
			//declarationStatements();
			//dataAndCode();
			//printf("\n\nbefore opt var list dec\n\n");
			//optVarListDeclarations();
			//printf("\n\nbefore optional statements token\n\n");
			optionalStatements();
			/*
			dataSession();
			codeSession();
			*/
			//printf("before match r bracket token");
			matchToken(RBR_T, NO_ATTR);
			break;
		//}
			/*
		else {
			printf("\n\nin else function case\n\n");
			printError();
		}
		*/
	case SEOF_T:
		//printf("\n\nin empty case\n\n");
		break;
	default:
		//printf("\n\nin default case\n\n");
		printError();
		break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}


/*************************************************************
 * dataSession
 * BNF: <dataSession> -> DATA { <opt_varlist_declarations> }
 * FIRST(<program>)= {KW_T (DATA)}.
 ************************************************************/
 /* TO_DO: Adjust this function to respect your grammar */
/*
faiyum_nul dataSession() {
	matchToken(KW_T, DATA);
	matchToken(LBR_T, NO_ATTR);
	optVarListDeclarations();
	matchToken(RBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Data Session parsed");
}
*/

/*************************************************************
 * codeSession statement
 * BNF: <codeSession> -> CODE { <opt_statements> }
 * FIRST(<???>) = { ??? }.
 ************************************************************/
 /* TO_DO: Adjust this function to respect your grammar */
/*
faiyum_nul codeSession() {
	matchToken(KW_T, CODE);
	matchToken(LBR_T, NO_ATTR);
	optionalStatements();
	matchToken(RBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Code Session parsed");
}
*/

faiyum_nul dataAndCode() {
	// loop through until right brace
	while (lookahead.code != RBR_T) {
		optionalStatements();
	}
}


/*************************************************************
 * Optional Var List Declarations
 * BNF: <opt_varlist_declarations> -> <varlist_declarations> | e
 * FIRST(<opt_varlist_declarations>) = { e, KW_T (FLOAT) }.
 ************************************************************/
 /* TO_DO: Adjust this function to respect your grammar */

faiyum_nul optVarListDeclarations() {
	switch (lookahead.code) {
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional Variable List Declarations parsed");
}


/*************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<???>) = { ??? }.
 ************************************************************/
 /* TO_DO: Adjust this function to respect your grammar */

faiyum_nul optionalStatements() {
	switch (lookahead.code) {
	case KW_T:
		statements();
		break;
	case VID_T:
		statements();
		break;
	default:
		// epsilon
		break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/*************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<???>) = { ??? }.
 ************************************************************/
 /* TO_DO: Adjust this function to respect your grammar */

faiyum_nul statements() {
	//printf("------  IN STATEMENTS  ------\n");
	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*************************************************************
 * Statements Prime
 * BNF: <statementsPrime>  <statement><statementsPrime> | ϵ
 * FIRST(<???>) = { ??? }.
 ************************************************************/
 /* TO_DO: Adjust this function to respect your grammar */

faiyum_nul statementsPrime() {
	switch (lookahead.code) {
	case VID_T:
		statement();
		statementsPrime();
		break;
	case KW_T:
		//printf("------  IN STATEMENTS PRIME - KWT CASE STATEMENT  ------\n");
		statement();
		statementsPrime();
		break;
	case EOS_T:
		//printf("------  IN STATEMENTS PRIME - EOS CASE STATEMENT  ------\n");
		break;
	default:
		// epsilon
		break;
	}
	
	/*
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType == output) {
			statement();
			statementsPrime();
			break;
		}
	default:
		; //empty string
	}
	*/
}

/*************************************************************
 * Single statement
 * BNF: <statement> ->  <assignment statement> | <input statement> | <output statement>
 * FIRST(<???>) = { ??? }.
 ************************************************************/
 /* TO_DO: Adjust this function to respect your grammar */

faiyum_nul statement() {
	// <statement> → <assignment statement> | <selection statement> | <iteration statement>
	// | <input statement> | <output statement>
	//printf("------  IN STATEMENT - STATEMENT  ------\n");
	switch (lookahead.code) {
	case VID_T:
		//printf("------  IN STATEMENT - VID CASE  ------\n");
		assignmentStatement();
		/*
		switch (lookahead.attribute.codeType) {
		case output:
			outputStatement();
			break;
		default:
			printError();
		}
		break;
		*/
		break;
	case KW_T:
		//printf("------  IN STATEMENT - KWT CASE  ------\n");
		if (lookahead.attribute.codeType == Var ||
			lookahead.attribute.codeType == Int ||
			lookahead.attribute.codeType == Float ||
			lookahead.attribute.codeType == String) {
			declarationStatements();
		}
		
		else if (lookahead.attribute.codeType == output) {
			//printf("------  IN STATEMENT - OUTPUT STATEMENT CASE  ------\n");
			outputStatement();
		}
		else if (lookahead.attribute.codeType == LOOP) {
			iterationStatement();
		}
		else {
			selectionStatement();
		}
		break;
	default:
		//printf("------  IN STATEMENT - DEFAULT CASE  ------\n");
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

faiyum_nul declarationStatements() {
	//printf("------  IN DECLARATION STATEMENT  ------\n");
	switch (lookahead.attribute.codeType) {
	case Var:
		matchToken(KW_T, Var);
		matchToken(VID_T, NO_ATTR);
		break;
	case Int:
		matchToken(KW_T, Int);
		matchToken(VID_T, NO_ATTR);
		break;
	case Float:
		//printf("------  FLOAT CASE  ------\n");
		matchToken(KW_T, Float);
		variableIdentifier();
		//matchToken(VID_T, NO_ATTR);
		break;
	case String:
		matchToken(KW_T, String);
		matchToken(VID_T, NO_ATTR);
		break;
	default:
		//printf("------  DEFAULT CASE  ------\n");
		break;
	}

	printf("%s%s\n", STR_LANGNAME, ": Declaration Statement parsed");
}

faiyum_nul iterationStatement() {
	matchToken(KW_T, LOOP);
	matchToken(KW_T, WHILE);
	conditionalExpression();
	matchToken(LBR_T, NO_ATTR);
	optionalStatements();
	matchToken(LBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Iteration Statement parsed");
}

faiyum_nul selectionStatement() {
	matchToken(KW_T, IF);
	conditionalExpression();
	matchToken(LBR_T, NO_ATTR);
	optionalStatements();
	matchToken(LBR_T, NO_ATTR);
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType == ELSE) {
			if (lookahead.attribute.codeType == IF) {
				iterationStatement();
			}
			else {
				matchToken(LBR_T, NO_ATTR);
				optionalStatements();
				matchToken(LBR_T, NO_ATTR);
			}
		}
		break;
	default:
		// epsilon
		break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Selection Statement parsed");
}

faiyum_nul conditionalExpression() {
	logicalOrExpression();
	printf("%s%s\n", STR_LANGNAME, ": Conditional Expression parsed");
}

faiyum_nul logicalOrExpression() {
	logicalAndExpression();
	logicalOrExpressionPrime();
	printf("%s%s\n", STR_LANGNAME, ": Logical Or Expression parsed");
}

faiyum_nul logicalOrExpressionPrime() {
	switch (lookahead.attribute.logicalOperator) {
	case OP_OR:
		matchToken(LOG_OP_T, OP_OR);
		logicalAndExpression();
		logicalOrExpressionPrime();
		break;
	default:
		// epsilon
		break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Logical Or Expression Prime parsed");
}

faiyum_nul logicalAndExpression() {
	//printf("------  IN LOGICAL AND  ------\n");
	logicalNotExpression();
	logicalAndExpressionPrime();
	printf("%s%s\n", STR_LANGNAME, ": Logical And Expression parsed");
}

faiyum_nul logicalAndExpressionPrime() {
	//printf("------  IN LOGICAL AND PRIME  ------\n");
	switch (lookahead.attribute.logicalOperator) {
	case OP_AND:
		matchToken(LOG_OP_T, OP_AND);
		logicalNotExpression();
		logicalAndExpressionPrime();
		break;
	default:
		// epsilon
		break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Logical And Expression Prime parsed");
}

faiyum_nul logicalNotExpression() {
	//printf("------  IN LOGICAL NOT  ------\n");
	switch (lookahead.attribute.logicalOperator) {
	case OP_NOT:
		//printf("------  IN LOGICAL NOT CASE NOT ------\n");
		
		matchToken(LOG_OP_T, OP_NOT);
		relationalExpression();
		break;
	default:
		//printf("------  IN LOGICAL NOT CASE DEFAULT ------\n");
		relationalExpression();
		break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Logical Not Expression parsed");
}

faiyum_nul relationalExpression() {
	relationalAExpression();
	printf("%s%s\n", STR_LANGNAME, ": Relational Expression parsed");
}

faiyum_nul relationalAExpression() {
	relationalAExpressionPrime();
	switch (lookahead.code) {
	case OP_EQ:
		matchToken(REL_OP_T, OP_EQ);
		break;
	case OP_NE:
		matchToken(REL_OP_T, OP_NE);
		break;
	case OP_GT:
		matchToken(REL_OP_T, OP_GT);
		break;
	case OP_LT:
		matchToken(REL_OP_T, OP_LT);
		break;
	}
	relationalAExpressionPrime();
	printf("%s%s\n", STR_LANGNAME, ": Relational Arithmetic Expression parsed");
}

faiyum_nul relationalAExpressionPrime() {
	switch (lookahead.code) {
	case VID_T:
		matchToken(VID_T, NO_ATTR);
		break;
	case INL_T:
		matchToken(INL_T, NO_ATTR);
		break;
	case FPL_T:
		matchToken(FPL_T, NO_ATTR);
		break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Relational Arithmetic Prime Expression parsed");
}

faiyum_nul relationalSExpression() {
	relationalSExpressionPrime();
	switch (lookahead.code) {
	case OP_EQ:
		matchToken(REL_OP_T, OP_EQ);
		break;
	case OP_NE:
		matchToken(REL_OP_T, OP_NE);
		break;
	case OP_GT:
		matchToken(REL_OP_T, OP_GT);
		break;
	case OP_LT:
		matchToken(REL_OP_T, OP_LT);
		break;
	}
	relationalSExpressionPrime();
	printf("%s%s\n", STR_LANGNAME, ": Relational String Expression parsed");
}

faiyum_nul relationalSExpressionPrime() {
	matchToken(STR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Relational String Prime Expression parsed");
}

/*************************************************************
 * Output Statement
 * BNF: <output statement> -> WRITE (<output statementPrime>);
 * FIRST(<???>) = { ??? }.
 ************************************************************/
 /* TO_DO: Adjust this function to respect your grammar */

faiyum_nul outputStatement() {
	matchToken(KW_T, output);
	//matchToken(LPR_T, NO_ATTR);
	switch (lookahead.code) {
	case VID_T:
		matchToken(VID_T, NO_ATTR);
		break;
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	default:
		// empty print statement
		break;
	}
	//matchToken(RPR_T, NO_ATTR);
	//matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

/*************************************************************
 * Output Variable List
 * BNF: <opt_variable list> -> <variable list> | ϵ
 * FIRST(<???>) = { ??? }.
 ************************************************************/
 /* TO_DO: Adjust this function to respect your grammar */
/*
faiyum_nul outputVariableList() {
	outputVariable();
	outputVariableListPrime();
	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
}

faiyum_nul outputVariableListPrime() {
	matchToken(SCC_OP_T, NO_ATTR);

}

faiyum_nul outputVariable() {

}
*/


/* TO_DO: Continue the development (all non-terminal functions) */
faiyum_nul arithmeticExpression() {
	// <arithmetic expression> → <unary arithmetic expression> | <additive arithmetic expression>
	switch (lookahead.code) {
	case ART_OP_T:
		unaryArithmeticExpression();
		break;

		// additive 
	case VID_T:
	case FPL_T:
	case INL_T:
		additiveArithmeticExpression();
		break;
	case LPR_T:
		matchToken(LPR_T, NO_ATTR);
		additiveArithmeticExpression();
		matchToken(RPR_T, NO_ATTR);
		break;
	default:
		break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Arithmetic Expression Parsed");
}

faiyum_nul unaryArithmeticExpression() {
	// <unary arithmetic expression> → - <primary arithmetic expression> | +<primary arithmetic expression>
	switch (lookahead.code) {
	case ART_OP_T:
		switch (lookahead.attribute.codeType) {
		case OP_ADD:
			matchToken(ART_OP_T, OP_ADD);
			primaryArithmeticExpression();
			break;
		case OP_SUB:
			matchToken(ART_OP_T, OP_SUB);
			primaryArithmeticExpression();
			break;
		}
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Unary Arithmetic Expression Parsed");
}

faiyum_nul primaryArithmeticExpression() {
	// <primary arithmetic expression> → <integer_variable> | <float_variable | FPL_T | INL_T | (<arithmetic expression>)
	switch (lookahead.code) {
	case INL_T:
		matchToken(INL_T, NO_ATTR);
		break;
	case FPL_T:
		matchToken(FPL_T, NO_ATTR);
		break;
	case VID_T:
		matchToken(VID_T, NO_ATTR);
		break;
	default:
		arithmeticExpression();
		break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Primary Arithmetic Expression Parsed");
}

faiyum_nul additiveArithmeticExpression() {
	multiplicativeArithmeticExpression();
	additiveArithmeticExpressionPrime();
	printf("%s%s\n", STR_LANGNAME, ": Additive Arithmetic Expression Parsed");
}

faiyum_nul additiveArithmeticExpressionPrime() {
	switch (lookahead.code) {
	case ART_OP_T:
		switch (lookahead.attribute.arithmeticOperator) {
		case OP_ADD:
			matchToken(ART_OP_T, OP_ADD);
			multiplicativeArithmeticExpression();
			additiveArithmeticExpressionPrime();
			break;
		case OP_SUB:
			matchToken(ART_OP_T, OP_SUB);
			multiplicativeArithmeticExpression();
			additiveArithmeticExpressionPrime();
			break;
		}
	default:
		break; // epsilon
	}
	printf("%s%s\n", STR_LANGNAME, ": Additive Arithmetic Expression Prime Parsed");
}

faiyum_nul assignmentExpression() {
	/*
	<assignment expression> → <integer_variable> is <arithmetic expression>
	| <float_variable> is <arithmetic expression>
	| <string_variable> is <string expression>
	*/
	//printf("------  IN ASSIGNMENT EXPRESSION  ------\n");
	matchToken(VID_T, NO_ATTR);
	matchToken(KW_T, is);
	switch (lookahead.code)
	{
	case STR_T:
		//printf("------  IN ASSIGNMENT EXPRESSION QOT CASE  ------\n");
		matchToken(STR_T, NO_ATTR);
		break;
	case KW_T:
		//printf("------  IN ASSIGNMENT EXPRESSION KW CASE  ------\n");
		inputStatement();
		break;
	case VID_T:
		//printf("------  IN ASSIGNMENT EXPRESSION VID CASE  ------\n");
		matchToken(VID_T, NO_ATTR);
		break;
	default:
		//printf("------  IN ASSIGNMENT EXPRESSION DEFAULT CASE  ------\n");
		arithmeticExpression();
		break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Assignment Expression Parsed");
}

faiyum_nul assignmentStatement() {
	
	// <assignment statement> → <assignment expression>
	assignmentExpression();
	printf("%s%s\n", STR_LANGNAME, ": Assignment Statement Parsed");
}

faiyum_nul inputStatement() {
	matchToken(KW_T, input);
	printf("%s%s\n", STR_LANGNAME, ": Input Statement Parsed");
}

faiyum_nul multiplicativeArithmeticExpression() {
	primaryArithmeticExpression();
	multiplicativeArithmeticExpressionPrime();
	printf("%s%s\n", STR_LANGNAME, ": Multiplicative Arithmetic Expression Parsed");
}

faiyum_nul multiplicativeArithmeticExpressionPrime() {
	/*
	< multiplicative arithmetic expression _prime> -> * < primary arithmetic expression>< multiplicative arithmetic expression _prime> 
	| / < primary arithmetic expression>< multiplicative arithmetic expression _prime> 
	|ϵ
	*/
	switch (lookahead.code) {
	case ART_OP_T:
		switch (lookahead.attribute.arithmeticOperator) {
		case OP_MUL:
			matchToken(ART_OP_T, OP_MUL);
			primaryArithmeticExpression();
			multiplicativeArithmeticExpression();
			break;
		case OP_DIV:
			matchToken(ART_OP_T, OP_DIV);
			primaryArithmeticExpression();
			multiplicativeArithmeticExpression();
			break;
		}
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Multiplicative Arithmetic Expresion Prime Parsed");
}

/*
faiyum_nul fltVariableIdentifier() {
	matchToken(KW_T, Float);
	matchToken(VID_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Float Variable Identifier Parsed");
}

faiyum_nul fltVarList() {
	// <float_variable_list > -> <float_variable >< float_variable_list_prime>
	fltVariableIdentifier();
	fltVarListPrime();
	printf("%s%s\n", STR_LANGNAME, ": Float Variable List Parsed");
}

faiyum_nul fltVarListPrime() {
	// <float_variable_list_prime> -> <float_variable >< float_variable_list_prime> | ϵ
	switch (lookahead.code)
	{
	case KW_T:
		fltVariableIdentifier();
		fltVarListPrime();
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Float Variable List Prime Parsed");
}


faiyum_nul fltVarListDeclaration() {
	fltVariableIdentifier();
	fltVarListPrime();
	printf("%s%s\n", STR_LANGNAME, ": Float Variable List Declaration Parsed");
}
*/

faiyum_nul variableIdentifier() {
	matchToken(VID_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Variable Identifier Parsed");
}

faiyum_nul variableList() {
	variableIdentifier();
	variableListPrime();
	printf("%s%s\n", STR_LANGNAME, ": Variable List Parsed");
}

faiyum_nul variableListPrime() {
	// <variable list_prime> -> <variable identifier >< variable list_prime> | ϵ
	switch (lookahead.code)
	{
	case VID_T:
		variableIdentifier();
		variableListPrime();
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Variable List Prime Parsed");
}

faiyum_nul varListDeclarations() {
	varListDeclaration();
	varListDeclarationsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Variable List Declarations Parsed");
}

faiyum_nul varListDeclaration() {
	/*
	<varlist_declaration> → <integer_varlist_declaration>
	| <float_varlist_declaration>
	| <string_varlist_declaration>
	*/
	switch (lookahead.code)
	{
	case Var:
		matchToken(KW_T, Var);
		matchToken(VID_T, NO_ATTR);
		break;
	case Int:
		matchToken(KW_T, Int);
		matchToken(VID_T, NO_ATTR);
		break;
	case Float:
		matchToken(KW_T, Float);
		matchToken(VID_T, NO_ATTR);
		break;
	case String:
		matchToken(KW_T, String);
		matchToken(VID_T, NO_ATTR);
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Variable List Declaration Parsed");
}

faiyum_nul varListDeclarationsPrime() {
	// <varlist_declarationsPrime> → <varlist_declaration> <varlist_declarationsPrime> | ϵ
	switch (lookahead.code)
	{
	case KW_T:
		varListDeclaration();
		varListDeclarationsPrime();
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Variable List Declarations Prime Parsed");

}