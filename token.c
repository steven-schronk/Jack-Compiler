#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "token.h"

#define SYMBOLS "{}()[].,;+-*/&|<>=~"
#define SPACES "\t\n\r "

int has_more_tokens(char *pC)
{
	if(*(pC+1) != EOF)
	{
		return TRUE;
	} else {
		return FALSE;
		}
}

char *advance(char *pC)
{
	char ch = NULL;
	/* skip past C++ style comments */
	if(*pC == '/' && *(pC+1) == '/')
	{
		while(*pC != '\n' && *pC != EOF)
			{ pC++; }
	}
	if(*pC == '\n') { pC++; }

	/* skip past C style comments */
	if(*pC == '/' && *(pC+1) == '*')
	{
		while(*(pC+1) != '/')
		{
			pC++;
		}
		pC += 2; /* move past end of comment */
	}

	/* advance past spaces and newline chars */
	ch = *pC;
	while((strchr(SPACES, ch)) != NULL)
	{
		pC++;
		ch = *pC;
	}

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
