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
	int sp_count = 0; /* space count */
	int tb_count = 0; /* tab count */
	int line_num = 1;
	int token_len = 0;

	printf("\n");
	fflush(stdout);

	/* backup pointer to token to beginning of previous token. */
	token_len = strlen(pT);
	do {
		pC--;
	} while (strncmp(pT, pC, token_len) != 0);

	/* set pTemp to beginning of current line */
	/* count tabs and spaces as you go */
	while(pTemp > pS && *pTemp != '\n')
	{
		if(*pTemp == '\t') { tb_count++; }
		else { sp_count++; }
		pTemp--;
	}
	sp_count = pC - pTemp;

	/* count line number to beginning of file print for user later */
	while(pS <= pC)
	{
		if(*pC == '\n') { line_num++; }
		pC--;
	}

	pTemp++;
	/* print last line to stderr */
	while((*pTemp != '\n') && (*pTemp != '\0'))
	{
		putc(*pTemp, stderr);
		pTemp++;
	}
	fprintf(stderr, "\n");

	/* print arrow pointing to token compiler cannot comprehend */
	while(sp_count > 1) { fprintf(stderr, " ");  sp_count--; }
	while(tb_count > 0)	{ fprintf(stderr, "\t"); tb_count--; }
	fprintf(stderr, "^\n");

	fprintf(stderr, "ERROR %d: %s On Line %d\n\n", comp_num, err_msg, line_num);
	exit(EXIT_SUCCESS);
}

void line_notification(const int line_num)
{
	fprintf(stderr, "ERROR FOUND ON LINE: %d\n", line_num);
}
