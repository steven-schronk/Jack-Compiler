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

void compiler_error(const int comp_num, const char *err_msg, char *pS, char *pC)
{
	char *pT = pC;
	int sp_count = 0; /* space count */
	int tb_count = 0; /* tab count */
	int line_num = 1;

	while(pT > pS && *pT != '\n') /* looking for start of current line */
	{
		if(*pT == '\t') { tb_count++; }
		else { sp_count++; }
		pT--;
	}

	sp_count = pC - pT;
	while(pS <= pC)
	{
		if(*pC == '\n') { line_num++; }
		pC--;
	}

	pT++;
	while(*pT != '\n') { putchar(*pT); pT++; }

	/* print arrow pointing to token compiler cannot comprehend */
	while(sp_count > 0) { printf(" ");  sp_count--; }
	while(tb_count > 0)	{ printf("\t"); tb_count--;	}
	printf("^\n");

	printf("ERROR %d: %s On Line %d\n", comp_num, err_msg, line_num);
	exit(EXIT_FAILURE);
}

void line_notification(const int line_num)
{
	fprintf(stderr, "ERROR FOUND ON LINE: %d\n", line_num);
}
