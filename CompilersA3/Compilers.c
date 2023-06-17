/************************************************************
* File name : Buffer.c
* Compiler : MS Visual Studio 2019, Debug Win32
* Author : Paulo Sousa, Mostapha Abdelaziz
* Professor: Paulo Sousa
* Purpose: This file is the main program of Compilers Project
* Function list: main().
*************************************************************/


#include <stdio.h>
#include <stdlib.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

/************************************************************
* Function name: main
* Purpose: Main function
* Author: Paulo Sousa, Mostapha Abdelaziz
* History/Versions: Ver 1.0
* Called functions: mainBuffer(), mainScanner(), mainParser()
* Parameters: Command line arguments - argc, argv
* Return value: Status
* Algorithm: -
**************************************************************/

faiyum_int main(int argc, char** argv) {
	faiyum_int i;
	if (DEBUG) {
		for (i = 0; i < argc; ++i)
			printf("argv[%d] = %s\n", i, argv[i]);
	}
	if (argc < 2) {
		printf("%s%s%c%s%c%s%c%s", argv[0], ": OPTIONS [",
			PGM_BUFFER, "] - Buffer, [",
			PGM_SCANNER, "] - Scanner, [",
			PGM_PARSER, "] - Parser\n");
	}
	faiyum_chr option = argv[1][0];
	switch (option) {
	case PGM_BUFFER:
		mainBuffer(argc, argv);
		break;
	case PGM_SCANNER:
		mainScanner(argc, argv);
		break;
		
	case PGM_PARSER:
		mainParser(argc, argv);
		break;
		
	default:
		printf("%s%s%c%s%c%s%c%s", argv[0], ": OPTIONS [",
			PGM_BUFFER, "] - Buffer, [",
			PGM_SCANNER, "] - Scanner, [",
			PGM_PARSER, "] - Parser\n");
		break;
	}
	return EXIT_SUCCESS;
}
