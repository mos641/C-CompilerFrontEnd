/************************************************************
* File name : Buffer.c
* Compiler : MS Visual Studio 2019, Debug Win32 
* Author : Paulo Sousa, Mostapha Abdelaziz
* Professor: Paulo Sousa
* Purpose : Main Code for the buffer
* Function list : create, addChar, clear, destroy, isFull, getWritePos, getSize, getMode, getMarkPos, 
* setMark, print, load, isEmpty, getChar, recover, retract, restore, getReadPos, getIncrement, getContent, getFlags
************************************************************/

/*************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2021
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa / Daniel Cormier
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#include "Buffer.h"
#endif

/************************************************************
* Function name: create
* Purpose: Creates the buffer according to capacity, increment
	factor and operational mode ('f', 'a', 'm')
* Author: Svillen Ranev / Paulo Sousa / Mostapha Abdelaziz
* History/Versions: Ver 2.2
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to Buffer)
* Algorithm: Allocation of memory according to inicial (default) values.
* TO_DO: 
*	- Adjust datatypes for your LANGUAGE.
*   - Use defensive programming
*	- Check boundary conditions
*	- Check flags.
**************************************************************/
BufferPointer create(faiyum_int size, faiyum_int increment, faiyum_int mode) {
	BufferPointer b;
	/* TO_DO: Defensive programming - done */
	if (increment < 0) {
		return NULL;
	}
	if (size<0 || size>FAIYUM_MAX_SIZE)
		return NULL;
	if (!size) {
		size = BUFFER_DEFAULT_SIZE;
		increment = BUFFER_DEFAULT_INCREMENT;
	}
	/* test the modes, must be f, a, m */
	if (mode != MODE_ADDIT && mode != MODE_FIXED && mode != MODE_MULTI) {
		return NULL;
	}
	if (!increment)
		mode = MODE_FIXED;
	b = (BufferPointer)calloc(1, sizeof(Buffer));
	/* check if b is null, return NULL */
	/* TO_DO: Defensive programming - done */
	if (b == NULL)
		return NULL;
	b->content = (faiyum_chr*)malloc(size);
	/* TO_DO: Defensive programming - done */
	if (!b->content) {
		free(b);
		return NULL;
	}
	b->mode = mode;
	b->size = size;
	b->increment = increment;
	/* TO_DO: Initialize flags - done*/
	b->flags = FAIYUM_DEFAULT_FLAG;
	/* TO_DO: The created flag must be signalized as EMP - done */
	b->flags = b->flags | FAIYUM_SET_FLAG_EMP;
	return b;
}


/************************************************************
* Function name: addChar
* Purpose: Adds a char to buffer
* Author: Svillen Ranev / Paulo Sousa / Mostapha Abdelaziz
* History/Versions: Ver 2.2
* Called functions: sizeof(), realloc()
* Parameters:
*   pBuffer = pointer to Buffer Entity
*   ch = char to be added
* Return value:
*	bPointer (pointer to Buffer)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
BufferPointer addChar(BufferPointer const pBuffer, faiyum_chr ch) {
	faiyum_chr* tempbuf;
	faiyum_int newSize;
	/* TO_DO: Defensive programming - done */
	if (pBuffer == NULL) {
		return NULL;
	}
	/* TO_DO: Reset Relocation - done */
	pBuffer->flags = pBuffer->flags & FAIYUM_RST_FLAG_REL;
    /* TO_DO: Check FUL - done */
	if (pBuffer->flags == (pBuffer->flags & FAIYUM_CHK_FLAG_FUL)) {
		return NULL;
	}

	if (pBuffer->size == pBuffer->position.writePos * (faiyum_int)sizeof(faiyum_chr)) {
		switch (pBuffer->mode) {
		case MODE_FIXED:
			/* TO_DO: Set FUL - done */
			pBuffer->flags = pBuffer->flags | FAIYUM_SET_FLAG_FUL;
			return NULL;
		case MODE_ADDIT:
			newSize = pBuffer->size + pBuffer->increment;
			/* TO_DO: Defensive programming */
			if (newSize < 0 || newSize <= pBuffer->size) {
				return NULL;
			}
			break;
		case MODE_MULTI:
			newSize = pBuffer->size * pBuffer->increment;
			/* TO_DO: Defensive programming */
			if (newSize > FAIYUM_MAX_SIZE) {
				return NULL;
			}
			if (newSize < 0 || newSize <= pBuffer->size) {
				return NULL;
			}
			break;
		default:
			return NULL;
		}
		tempbuf = (faiyum_chr*)realloc(pBuffer->content, newSize);
		if (tempbuf == NULL) {
			return NULL;
		}
		/* TO_DO: Defensive programming - done */
		if (tempbuf && tempbuf != pBuffer->content) {
			/* TO_DO: Set Relocation - done */
			pBuffer->flags = pBuffer->flags | FAIYUM_SET_FLAG_REL;
			pBuffer->content = tempbuf;
		}
		pBuffer->size = newSize;
	}
	/* TO_DO: Adjust flags: Reset EMP - done*/
	pBuffer->flags = pBuffer->flags & FAIYUM_RST_FLAG_EMP;
	/* TO_DO: Adjust flags: Set FUL if necessary - */
	if (pBuffer->flags != (pBuffer->flags | FAIYUM_CHK_FLAG_FUL)) {
		pBuffer->flags = pBuffer->flags | FAIYUM_SET_FLAG_FUL;
	}
	pBuffer->content[pBuffer->position.writePos++] = ch;
	return pBuffer;
}

/************************************************************
* Function name: clear
* Purpose: Clears the buffer
* Author: Svillen Ranev / Paulo Sousa / Mostapha Abdelaziz
* History/Versions: Ver 2.2
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
faiyum_bol clear(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming - done */
	if (!pBuffer) {
		return FAIYUM_FALSE;
	}

	pBuffer->position.writePos = pBuffer->position.markPos = pBuffer->position.readPos = 0;
	/* TO_DO: Adjust flags original - done */
	pBuffer->flags = FAIYUM_DEFAULT_FLAG;
	return FAIYUM_TRUE;
}

/************************************************************
* Function name: destroy
* Purpose: Releases the buffer address
* Author: Svillen Ranev / Paulo Sousa
* History/Versions: Ver 2.2
* Called functions: free()
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
faiyum_bol destroy(BufferPointer const pBuffer) {
	free(pBuffer->content);
	free(pBuffer);
	return FAIYUM_TRUE;
}

/************************************************************
* Function name: isFull
* Purpose: Checks if buffer is full
* Author: Svillen Ranev / Paulo Sousa / Mostapha Abdelaziz
* History/Versions: Ver 2.2
* Called functions: sizeof()
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
faiyum_bol isFull(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming - done*/
	if (!pBuffer) {
		return FAIYUM_FALSE;
	}

	/* TO_DO: Use bitwise check to test if buffer is FUL - done */

	if (pBuffer->size == pBuffer->position.writePos * (faiyum_int)sizeof(faiyum_chr))
		return FAIYUM_TRUE;
	return FAIYUM_FALSE;
}

/************************************************************
* Function name: getWritePos
* Purpose: Returns the position of char to be added
* Author: Svillen Ranev / Paulo Sousa / Mostapha Abdelaziz
* History/Versions: Ver 2.2
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	addcPosition value
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
faiyum_int getWritePos(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming - done */
	if (!pBuffer) {
		return -1;
	}
	return pBuffer->position.writePos;
}

/************************************************************
* Function name: getSize
* Purpose: Returns the current buffer capacity
* Author: Svillen Ranev / Paulo Sousa / Mostapha Abdelaziz
* History/Versions: Ver 2.2
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
faiyum_int getSize(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming - done */
	if (!pBuffer) {
		return -1;
	}

	if (pBuffer->size == FAIYUM_MAX_SIZE) {
		return -1;
	}

	return pBuffer->size;
}

/************************************************************
* Function name: getMode
* Purpose: Returns the operational mode
* Author: Svillen Ranev / Paulo Sousa / Mostapha Abdelaziz
* History/Versions: Ver 2.2
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
faiyum_int getMode(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming - done */
	if (!pBuffer) {
		return -1;
	}

	if (pBuffer->mode != MODE_ADDIT && pBuffer->mode != MODE_FIXED && pBuffer->mode != MODE_MULTI) {
		return -1;
	}
	return pBuffer->mode;
}


/************************************************************
* Function name: getMarkPos
* Purpose: Returns the position of mark in the buffer
* Author: Svillen Ranev / Paulo Sousa / Mostapha Abdelaziz
* History/Versions: Ver 2.2
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	mark offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
faiyum_int getMarkPos(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming - done */
	if (!pBuffer) {
		return -1;
	}

	if (pBuffer->position.markPos == 0) {
		return -1;
	}
	return pBuffer->position.markPos;
}


/************************************************************
* Function name: setMark
* Purpose: Adjust the position of mark in the buffer
* Author: Svillen Ranev / Paulo Sousa / Mostapha Abdelaziz
* History/Versions: Ver 2.2
* Parameters:
*   pBuffer = pointer to Buffer Entity
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
faiyum_bol setMark(BufferPointer const pBuffer, faiyum_int mark) {
	/* TO_DO: Defensive programming - done*/
	if (!pBuffer) {
		return FAIYUM_FALSE;
	}
	if (mark < 0 || mark > pBuffer->position.writePos) {
		return FAIYUM_FALSE;
	}

	pBuffer->position.markPos = mark;
	return FAIYUM_TRUE;
}

/************************************************************
* Function name: print
* Purpose: Prints the string in the buffer.
* Author: Svillen Ranev / Paulo Sousa / Mostapha Abdelaziz
* History/Versions: Ver 2.2
* Called functions: getChar()
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
faiyum_int print(BufferPointer const pBuffer) {
	faiyum_int cont = 0;
	faiyum_chr c;
	/* TO_DO: Defensive programming - done */
	if (!pBuffer) {
		return -1;
	}

	if (pBuffer->position.readPos > pBuffer->position.writePos) {
		return -1;
	}

	c = getChar(pBuffer);
	/* TO_DO: Check flag if buffer EOB has achieved - done  */
	if (pBuffer->flags == (pBuffer->flags | FAIYUM_CHK_FLAG_EOB)) {
		return cont;
	}
	while (!(pBuffer->position.readPos == pBuffer->position.writePos)) {
		cont++;
		printf("%c", c);
		c = getChar(pBuffer);
	}
	return cont;
}

/************************************************************
* Function name: load
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Author: Svillen Ranev / Paulo Sousa / Mostapha Abdelaziz
* History/Versions: Ver 2.2
* Called functions: fgetc(), feof(), ferror()
* Parameters:
*   pBuffer = pointer to Buffer Entity
*   fi = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
faiyum_int load(BufferPointer const pBuffer, FILE* const fi) {
	faiyum_int size = 0;
	faiyum_chr c;
	/* TO_DO: Defensive programming - done */
	if (!pBuffer) {
		return -1;
	}

	if (!fi) {
		return -1;
	}

	c = (faiyum_chr)fgetc(fi);
	while (!feof(fi)) {
		if (!addChar(pBuffer, c)) {
			ungetc(c, fi);
			return BUFFER_ERROR;
		}
		c = (char)fgetc(fi);
		size++;
	}
	if (ferror(fi))
		return BUFFER_ERROR;
	return size;
}

/************************************************************
* Function name: isEmpty
* Purpose: Checks if buffer is empty.
* Author: Svillen Ranev / Paulo Sousa / Mostapha Abdelaziz
* History/Versions: Ver 2.2
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
faiyum_bol isEmpty(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming -done */
	if (!pBuffer) {
		return FAIYUM_FALSE;
	}

	/* TO_DO: Use bitwise operation to test if buffer is EMP - done */
	if (pBuffer->flags == (pBuffer->flags | FAIYUM_CHK_FLAG_EMP)) {
		return FAIYUM_TRUE;
	}
	if (pBuffer->position.writePos==0)
		return FAIYUM_TRUE;
	return FAIYUM_FALSE;
}

/************************************************************
* Function name: getChar
* Purpose: Returns the char in the getC position.
* Author: Svillen Ranev / Paulo Sousa / Mostapha Abdelaziz
* History/Versions: Ver 2.2
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
faiyum_chr getChar(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming - done */
	if (!pBuffer) {
		return -1;
	}

	if (pBuffer->position.readPos > pBuffer->position.writePos) {
		return -1;
	}

	if (pBuffer->position.readPos == pBuffer->position.writePos) {
		/* TO_DO: Set EOB flag - done */
		pBuffer->flags = pBuffer->flags | FAIYUM_SET_FLAG_EOB;
		return BUFFER_EOF;
	}
	/* TO_DO: Reset EOB flag - done */
	pBuffer->flags = pBuffer->flags & FAIYUM_SET_FLAG_EOB;
	return pBuffer->content[pBuffer->position.readPos++];
}


/************************************************************
* Function name: recover
* Purpose: Rewinds the buffer.
* Author: Svillen Ranev / Paulo Sousa / Mostapha Abdelaziz
* History/Versions: Ver 2.2
* Called functions: getWritePos()
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
faiyum_bol recover(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming - done */
	if (!pBuffer) {
		return FAIYUM_FALSE;
	}

	if (getWritePos == 0) {
		return FAIYUM_FALSE;
	}

	pBuffer->position.readPos = 0;
	pBuffer->position.markPos = 0;
	return FAIYUM_TRUE;
}


/************************************************************
* Function name: retract
* Purpose: Retracts the buffer to put back the char in buffer.
* Author: Svillen Ranev / Paulo Sousa / Mostapha Abdelaziz
* History/Versions: Ver 2.2
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
faiyum_bol retract(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming - done */
	if (!pBuffer) {
		return FAIYUM_FALSE;
	}

	if (pBuffer->position.readPos <= 0) {
		return FAIYUM_FALSE;
	}
	pBuffer->position.readPos--;
	return FAIYUM_TRUE;
}


/************************************************************
* Function name: restore
* Purpose: Resets the buffer.
* Author: Svillen Ranev / Paulo Sousa / Mostapha Abdelaziz
* History/Versions: Ver 2.2
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
faiyum_bol restore(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming - done*/
	if (!pBuffer) {
		return FAIYUM_FALSE;
	}

	if (pBuffer->position.markPos > pBuffer->position.writePos) {
		return FAIYUM_FALSE;
	}

	pBuffer->position.readPos = pBuffer->position.markPos;
	return FAIYUM_TRUE;
}


/************************************************************
* Function name: getReadPos
* Purpose: Returns the value of getCPosition.
* Author: Svillen Ranev / Paulo Sousa / Mostapha Abdelaziz
* History/Versions: Ver 2.2
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	The readPos offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
faiyum_int getReadPos(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming - done */
	if (!pBuffer) {
		return -1;
	}

	if (pBuffer->position.readPos > pBuffer->position.writePos) {
		return -1;
	}
	return pBuffer->position.readPos;
}


/************************************************************
* Function name: getIncrement
* Purpose: Returns the buffer increment.
* Author: Svillen Ranev / Paulo Sousa / Mostapha Abdelaziz
* History/Versions: Ver 2.2
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
faiyum_int getIncrement(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming - done */
	if (!pBuffer) {
		return 0;
	}

	if (pBuffer->mode == MODE_FIXED) {
		return 0;
	}
	return pBuffer->increment;
}


/************************************************************
* Function name: getContent
* Purpose: Returns the pointer to String.
* Author: Svillen Ranev / Paulo Sousa / Mostapha Abdelaziz
* History/Versions: Ver 2.2
* Parameters:
*   pBuffer = pointer to Buffer Entity
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
faiyum_chr* getContent(BufferPointer const pBuffer, faiyum_int pos) {
	/* TO_DO: Defensive programming - done */
	if (!pBuffer) {
		return NULL;
	}

	if ((pos < 0) || (pos > pBuffer->position.writePos)) {
		return NULL;
	}

	return pBuffer->content + pos;
}


/************************************************************
* Function name: getFlags
* Purpose: Returns the entire flags of Buffer.
* Author: Svillen Ranev / Paulo Sousa / Mostapha Abdelaziz
* History/Versions: Ver 2.2
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Flags from Buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
faiyum_flg getFlags(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming - done*/
	if (!pBuffer) {
		return -1;
	}

	return pBuffer->flags;
}
