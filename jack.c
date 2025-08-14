#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "error.h"
#include "jack.h"
#include "parse.h"
#include "test.h"
#include "token.h"

char *pC = NULL; /* pointer to code */
char pT[1000];  /* pointer to token */
char *pS = NULL;
token tk;
ttype ttyp;
int space_count = 0; /* number of spaces before printing token */
extern struct settings_t settings;

void usage(void)
{
	printf("Usage: jack [options] file\n");
	printf("Options:\n");
	printf("  <file>        Compile file without tokens\n");
	printf("	              Filename must end with .jack\n");
	printf("  -h            Display this information\n");
	printf("  -t <file>     Compile file and display tokens\n");
	printf("  -u            Run all unit tests\n");
}

void settings_init(void)
{
	settings.tokens = 0;
	settings.test = 0;
}

int main(int argc, char *argv[])
{
	int i, size, file_loc = 1;
	char FilenameBuff[80];

	FILE *fpSource, *fpDest;

	/* test for switches passed - test for location of file in argv */
	file_loc = 2;
	while ((i = getopt(argc, argv, "uht:")) != -1)
	{
		switch (i)
		{
			case 't':
				settings.tokens = 1;
				break;
			case 'u':
				settings.test = 1;
				break;
			case 'h':
				usage();
				exit(EXIT_SUCCESS);
				break;
			default:
				usage();
				exit(EXIT_SUCCESS);
		}
	}

	if(settings.test)
	{
		printf("\nRUNNING ALL UNIT TESTS ON COMPILER.\n\n");
		if(test_all() == 0)
		{
			printf("\nUNIT TEST COMPLETE - ALL TESTS RETURNED PASSED.\n\n");
		} else {
			exit_error(0, "UNIT TEST FAILED.\n\n");
		}
		exit(EXIT_SUCCESS);
	}

	if(argc < 2) { exit_error(1, "No Input Files."); usage(); }
	/* TODO: future versions will accept more than one file */
	if(argc > 3) { exit_error(2, "Too Many Files Listed."); usage(); }

	if((fpSource = fopen(argv[file_loc], "r")) == NULL)
	{
		exit_error(3, "Cannot Open Input (Source) File");
	}

	strcpy(FilenameBuff, argv[file_loc]);

	/* verify filename extension */
	if(strstr(argv[file_loc], "jack") == NULL)
	{
		exit_error(5, "Filename Extension Not Correct."); usage();
	}

	/* modify output filename and then open output file */
	pC = strrchr(FilenameBuff, '.');
	if( pC == NULL){ exit_error(5, "Input File Has No Extension"); usage(); }

	pC++;
	strcpy(pC, "xml"); /* buffer should contain output filename */

	if((fpDest = fopen(FilenameBuff, "w+")) == NULL)
	{
		exit_error(6, "Cannot Open Output (Object) File");
	}

	fseek(fpSource, 0, SEEK_END); /* seek to end of file */
	size = ftell(fpSource); /* get current file pointer */
	fseek(fpSource, 0, SEEK_SET); /* seek back to beginning of file */
	/* proceed with allocating memory and reading the file */
	pS = malloc((sizeof(char) * size)+1);

	if(pS == NULL) { exit_error(7, "Cannot Allocate Memory For Source"); }

	i = 0;
	while(i < size)
	{
		pS[i] = getc(fpSource);
		i++;
	}
	pS[i] = '\0';

	pC = pS; /* move to beginning of source code */
	parse_class(pS, pC, pT);
	return 0;
}
