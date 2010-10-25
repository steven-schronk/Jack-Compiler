#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "token.h"

char *keywords[] =
{
		 "boolean","char", "class", "constructor", "do", "else",
		 "false", "field", "function", "if", "int", "let", "method",
		 "null", "return", "static", "this", "true", "var", "void", "while"
};

int has_more_tokens(char *pC)
{
	if(*(pC+1) == '\0')
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
	int in_quote = 0; /* inside quotes? */
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
	cont = 0; in_quote = 0;
	if(*pC == '"')
	{
		in_quote++; /* inside quote */
		pC++;		/* skip quote itself */
	}
	while(TRUE)
	{
		if(in_quote){
			if(*pC == '"') {  pC++; break; } /* found corresponding quote, stop */
		} else {
			if(((strchr(SPACES, ch)) != NULL) || ((strchr(SYMBOLS, ch)) != NULL))
			{
				break;
			}
		}
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
	token t = IDENTIFIER;
	int i = 0, j = 0;;

	/* check token for symbols */
	if(strchr(SYMBOLS, pT[0]) != NULL) { t = SYMBOL; }

	/* check token for integer constants */
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

	/* check token for keywords */
	i = 0; j = 0;
	do {
		j = strcmp(keywords[i], pT);
		i++;
	} while ((j != 0) && (i < KEYWORD_COUNT));

	if(j == 0) { t = KEYWORD; }
	return t;
}


 ttype keyword(char pT[])
{
	 int i = 0;
	 do {
		 i++;
	 } while (strcmp(pT, keywords[i]) < 0 && i < KEYWORD_COUNT);
	return i;
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


int int_val(char pT[])
{
	return atoi(pT);
}


char *string_val()
{
	return NULL;
}
