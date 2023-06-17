/************************************************************
* File name : Buffer.c
* Compiler : MS Visual Studio 2019, Debug Win32
* Author : Paulo Sousa, Mostapha Abdelaziz
* Professor: Paulo Sousa
* Purpose: This file defines the functions called by main function.
* Function list: mainBuffer(), mainScanner(), mainParser().
************************************************************/

#ifndef COMPILERS_H_
#define COMPILERS_H_

#define DEBUG 0

/* Logical constants - adapt for your language */
#define FAIYUM_TRUE	1
#define FAIYUM_FALSE 0

/*
------------------------------------------------------------
Programs:
1: Buffer - invokes MainBuffer code
2: Scanner - invokes MainScanner code
3: Parser - invokes MainParser code
------------------------------------------------------------
*/
enum PROGRAMS {
	PGM_BUFFER	= '1',
	PGM_SCANNER = '2',
	PGM_PARSER	= '3'
};

/*
------------------------------------------------------------
Main functions signatures
(Codes will be updated during next assignments)
------------------------------------------------------------
*/
int mainBuffer	(int argc, char** argv);
int mainScanner	(int argc, char** argv);
int mainParser	(int argc, char** argv);

/*
------------------------------------------------------------
Data types definitions
------------------------------------------------------------
*/

/* TO_DO: Define your typedefs */

typedef short			faiyum_int;
typedef long			faiyum_lng;
typedef char			faiyum_chr;
typedef unsigned char	faiyum_flg;
typedef char			faiyum_bol;
typedef float			faiyum_flt;
typedef double			faiyum_dbl;
typedef void			faiyum_nul;


#endif
