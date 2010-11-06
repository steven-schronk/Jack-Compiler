#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "error.h"
#include "jack.h"
#include "parse.h"
#include "token.h"

char *pC = NULL; /* pointer to code */
char pT[1000];  /* pointer to token */
char *pS = NULL;
token tk;
ttype ttyp;

void usage(void)
{
	printf("\n<options> <file>\n");
	printf("<file>	Filename to compile.\n");
	printf("	Filename must end with .jack.\n");
}

void settings_init(void)
{
	settings.tokens = 0;
}

int main(int argc, char *argv[])
{
	int i, size, file_loc = 1;
	char FilenameBuff[80];

	FILE *fpSource, *fpDest;

	if(argc < 2) { exit_error(1, "No Input Files."); usage(); }
	/* TODO: future versions will accept more than one file */
	if(argc > 3) { exit_error(2, "Too Many Files Listed."); usage(); }

	/* test for switches passed - test for location of file in argv */
	if(argv[1][0] == '-')
	{
		file_loc = 2;
		while(-1 != (i = getopt(argc, argv,
			"-t" /* print tokenizer output */
			"--help" /*print out usage statement */
		))) {

			switch (i)
			{
				case 't':
					settings.tokens = 1;
					break;
				case '-':
					usage();
					break;
			}
		}
	}

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
