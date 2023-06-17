/************************************************************
* File name : Buffer.h
* Compiler : MS Visual Studio 2019, Debug Win32
* Author : Paulo Sousa, Mostapha Abdelaziz
* Professor: Paulo Sousa
* Purpose : Main header for Buffer.c
* Function list : create, addChar, clear, destroy, isFull, getWritePos, getSize, getMode, getMarkPos,
* setMark, print, load, isEmpty, getChar, recover, retract, restore, getReadPos, getIncrement, getContent, getFlags
************************************************************/

/*************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2021
*************************************************************/


#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#define BUFFER_H_

/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer) */
enum BUFFERMODES {
	MODE_FIXED = 'f',
	MODE_ADDIT = 'a',
	MODE_MULTI = 'm'
};

/* TO_DO: Adjust all constants to your Language */

#define BUFFER_ERROR (-1)						/* General error message */
#define BUFFER_EOF '\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (FAIYUM) .................................. */

#define BUFFER_DEFAULT_SIZE			200			/* default initial buffer capacity */
#define BUFFER_DEFAULT_INCREMENT	100			/* default increment factor */

/* You should add your own constant definitions here */
#define FAIYUM_MAX_SIZE				SHRT_MAX-1	/*maximum capacity*/ 

/* Add your bit-masks constant definitions here - Defined for FAIYUM */
/* BITS                                7654.3210 */
#define FAIYUM_DEFAULT_FLAG 0xF0 	/* 1111.0000 = 240 */
/* TO_DO: BIT 0: EMP: Empty */
#define FAIYUM_SET_FLAG_EMP 0x01		/* 0000.0001 = 001 */
#define FAIYUM_RST_FLAG_EMP 0xFE		/* 1111.1110 = 254 */
#define FAIYUM_CHK_FLAG_EMP 0x01		/* 0000.0001 = 001 */
/* TO_DO: BIT 1: FUL = Full */
#define FAIYUM_SET_FLAG_FUL 0x02		/* 0000.0010 = 002 */
#define FAIYUM_RST_FLAG_FUL 0xFD		/* 1111.1101 = 253 */
#define FAIYUM_CHK_FLAG_FUL 0x02		/* 0000.0010 = 002 */
/* TO_DO: BIT 2: EOB = EndOfBuffer */
#define FAIYUM_SET_FLAG_EOB 0x04		/* 0000.0100 = 004 */
#define FAIYUM_RST_FLAG_EOB 0xFB		/* 1111.1011 = 251 */
#define FAIYUM_CHK_FLAG_EOB 0x03		/* 0000.0100 = 004 */
/* TO_DO: BIT 3: REL = Relocation */
#define FAIYUM_SET_FLAG_REL 0x08		/* 0000.1000 = 008 */
#define FAIYUM_RST_FLAG_REL 0xF7		/* 1111.0111 = 247 */
#define FAIYUM_CHK_FLAG_REL 0x08		/* 0000.1000 = 008 */

/*
SET bit use OR operator
buffer->flags = buffer->flags | FAIYUM_SET_FLAG
RESET bit use AND operator
buffer->flags = buffer->flags & FAIYUM_RST_FLAG
CHECK or evaluate, in if
buffer->flags = buffer->flags & FAIYUM_CHK_FLAG
*/

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (FAIYUM) .................................. */

/* TO_DO: Adjust datatypes */

/* Offset declaration */
typedef struct position {
	faiyum_int writePos;				/* the offset (in chars) to the add-character location */
	faiyum_int readPos;				/* the offset (in chars) to the get-character location */
	faiyum_int markPos;				/* the offset (in chars) to the mark location */
} Position;

/* Buffer structure */
typedef struct buffer {
	faiyum_chr*	content;		/* pointer to the beginning of character array (character buffer) */
	faiyum_int	size;		    /* current dynamic memory size (in bytes) allocated to character buffer */
	faiyum_int	increment;		/* character array increment factor */
	faiyum_int	mode;			/* operational mode indicator */
	faiyum_flg	flags;			/* contains character array reallocation flag and end-of-buffer flag */
	Position	position;		/* Offset / position field */
} Buffer, * BufferPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
BufferPointer create(faiyum_int, faiyum_int, faiyum_int);
BufferPointer addChar(BufferPointer const, faiyum_chr);
faiyum_bol retract(BufferPointer const);
faiyum_bol restore(BufferPointer const);
faiyum_bol recover(BufferPointer const);
faiyum_bol clear(BufferPointer const);
faiyum_bol destroy(BufferPointer const);
faiyum_bol setMark(BufferPointer const, faiyum_int);
faiyum_bol isEmpty(BufferPointer const);
faiyum_bol isFull(BufferPointer const);
faiyum_bol isRealocated(BufferPointer const);
faiyum_int print(BufferPointer const);
faiyum_int load(BufferPointer const, FILE* const);
/* Getters */
faiyum_int getSize(BufferPointer const);
faiyum_int getWritePos(BufferPointer const);
faiyum_int getMarkPos(BufferPointer const);
faiyum_int getReadPos(BufferPointer const);
faiyum_int getIncrement(BufferPointer const);
faiyum_int getMode(BufferPointer const);
faiyum_chr getChar(BufferPointer const);
faiyum_chr* getContent(BufferPointer const, faiyum_int);
faiyum_flg getFlags(BufferPointer const);

#endif
