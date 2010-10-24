#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "token.h"

#define SYMBOLS "{}()[].,;+-*/&|<>=~"
#define SPACES "\t\n\r "

int has_more_tokens(char *pC)
{
	if(*(pC+1) == EOF)
	{
		return FALSE;
	} else {
		return TRUE;
	}
}

char *advance(char *pC, char *pT)
{
	char ch;
	int cont; /* continue */
	free(pT);
	do {
		cont = 0;
		/* skip past C++ style comments */
		if(*pC == '/' && *(pC+1) == '/')
		{
			/* TODO: use string lib here */
			pC = strchr(pC, '\n');
		}

		/* skip past C style comments */
		if(*pC == '/' && *(pC+1) == '*')
		{
			pC++;
			pC = strchr(pC, '/');
			pC++;
			/* pC += 2; move past end of comment */
		}

		/* advance past spaces and newline chars */
		ch = *pC;
		while((strchr(SPACES, ch)) != NULL)
		{
			pC++;
			ch = *pC;
		}

		/* determine if more advancement is needed */
		if(*pC == '/' && *(pC+1) == '/') { cont++; }
		if(*pC == '/' && *(pC+1) == '*') { cont++; }

	} while (cont);
	return pC;
}


ttype token_type(void)
{
	return FALSE;
}


token keyword(void)
{
	return KEYWORD;
}


char symbol()
{
	return 'z';
}


char *identifier(char *str)
{
	str = NULL;
	return NULL;
}


int int_val()
{
	return 0;
}


char *string_val()
{
	return NULL;
}
