#include <ctype.h>
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

char *advance(char *pC, char pT[])
{
	char ch;
	int cont; /* continue */
	do {
		cont = 0;
		/* skip past C++ style comments */
		if(*pC == '/' && *(pC+1) == '/')
		{
			pC = strchr(pC, '\n');
		}

		/* skip past C style comments */
		if(*pC == '/' && *(pC+1) == '*')
		{
			pC++;
			pC = strchr(pC, '/');
			pC++;
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

	/* test for symbol - copy to buffer */
	ch = *pC;
	if(strchr(SYMBOLS, ch) != NULL)
	{
		pT[0] = ch;
		pT[1] = '\0';
		pC++;
		return pC;
	}

	/* should be at beginning of token - copy to buffer */
	cont = 0;
	while(((strchr(SPACES, ch)) == NULL) && ((strchr(SYMBOLS, ch)) == NULL))
	{
		pT[cont] = *pC;
		pC++;
		ch = *pC;
		cont++;
	}
	pT[cont] = '\0';
	return pC;
}


token token_type(char pT[])
{
	token t;
	int i = 0, j = 0;;
	if(strchr(SYMBOLS, pT[0]) != NULL) { t = SYMBOL; }
	while(pT[i] != '\0')
	{
		if(isdigit(pT[i]) == 0)
		{
			j++;
			break;
		}
		i++;
	}
	if(j == 0) { t = INT_CONST; }
	return t;
}


 ttype keyword(void)
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
