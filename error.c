#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "error.h"

void exit_error(const int err_num, const char *err_msg)
{
	fprintf(stderr, "ERROR %d: %s\n", err_num, err_msg);
	/*
	if(pInfile != NULL) { fclose(pInfile); }
	if(pOutfile != NULL) { fclose(pOutfile); }
	*/
	exit(EXIT_FAILURE);
}

void warning_error(const int err_num, const char *err_msg)
{
	fprintf(stderr, "WARNING: %d: %s\n", err_num, err_msg);
}

void compiler_error(const int comp_num, const char *err_msg, char *pS, char *pC, char pT[])
{
	char *pTemp = pC;
	char *pCount = pC;
	int sp_count = 0; /* space count */
	int line_num = 1;
	int token_len = 0;

	printf("\n");
	fflush(stdout);

	/* backup pointer to token to beginning of previous token. */
	token_len = strlen(pT);
	do {
		pC--;
	} while (strncmp(pT, pC, token_len) != 0);

	pTemp = pC;
	/* set pTemp to beginning of current line */
	while(pTemp > pS && *pTemp != '\n')
	{
		sp_count++;
		pTemp--;
	}

	/* count line number to beginning of file print for user later */
	while(pS <= pC)
	{
		if(*pC == '\n') { line_num++; }
		pC--;
	}
	pTemp++; /* move past newline */
	pCount = pTemp;

	/* print last line to stderr */
	while((*pTemp != '\n') && (*pTemp != '\0'))
	{
		putc(*pTemp, stderr);
		pTemp++;
	}
	fprintf(stderr, "\n");

	sp_count--; /* off by one because of arrow printed at end of line*/

	/* print arrow pointing to token compiler cannot comprehend */
	while(sp_count >= 0)
	{
		if(sp_count == 0)
		{
			fprintf(stderr, "^\n");
		} else {
			if(*pCount == '\t')
			{
				fprintf(stderr, "\t");
			} else  {
				fprintf(stderr, " ");
			}
		}
		sp_count--;
		pCount++;
	}

	fprintf(stderr, "ERROR %d: %s On Line %d.\n\n", comp_num, err_msg, line_num);

	exit(EXIT_FAILURE);
}

void line_notification(const int line_num)
{
	fprintf(stderr, "ERROR FOUND ON LINE: %d.\n", line_num);
}
