#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "error.h"
#include "jack.h"
#include "token.h"

struct settings settings;

void usage(void)
{
	printf("\n<options> <file>\n");
	printf("<file>	Filename to compile.\n");
	printf("	Filename must end with .jack.\n");
}

void settings_init(void)
{
	settings.verbose = 0;
}

int main(int argc, char *argv[])
{
	int i, size, file_loc = 1;
	char FilenameBuff[80];
	char ch;
	char *pC;
	char *pSource = NULL;
	FILE *fpSource, *fpDest;

	if(argc < 2) { exit_error(1, "No Input Files."); usage(); }
	/* TODO: future versions will accept more than one file */
	if(argc > 3) { exit_error(2, "Too Many Files Listed."); usage(); }

	/* test for switches passed - test for location of file in argv */
	if(argv[1][0] == '-')
	{
		file_loc = 2;
		while(-1 != (i = getopt(argc, argv,
			"-v" /* verbose output to stdout */
			"-t" /* print final hash table to stdout */
			"-c" /* print code output to stdout - without comments */
			"-C" /* print code output to stdout - with comments */
			"-x" /* print commands to stdout */
			"--help" /*print out usage statement */
		))) {

			switch (i)
			{
				case 'v':
					settings.verbose = 1;
					break;
				case '-':
					usage();
					break;
			}
		}
	}

	if((fpSource = fopen(argv[file_loc], "r")) == NULL) {
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

	/* get one line at a time and load into buffer */
	/* getline(fpSource); */

	fseek(fpSource, 0, SEEK_END); /* seek to end of file */
	size = ftell(fpSource); /* get current file pointer */
	fseek(fpSource, 0, SEEK_SET); /* seek back to beginning of file */
	/* proceed with allocating memory and reading the file */
	pSource = malloc((sizeof(char) * size)+1);

	if(pSource == NULL) { exit_error(7, "Cannot Allocate Memory For Source"); }

	i = 0;
	while(i < size)
	{
		pSource[i] = getc(fpSource);
		i++;
	}
	pSource[i] = '\0';


	/* remove all whitespace from source */

	printf("%s", pSource);

	return 0;
}
