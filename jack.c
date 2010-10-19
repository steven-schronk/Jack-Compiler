#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "error.h"
#include "jack.h"

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
	int c, file_loc = 1;
	char FilenameBuff[80];
	char * pC;
	FILE *fpSource, *fpDest;

	if(argc < 2) { exit_error(1, "No Input Files."); usage(); }
	/* TODO: future versions will accept more than one file */
	if(argc > 3) { exit_error(2, "Too Many Files Listed."); usage(); }

	/* test for switches passed - test for location of file in argv */
	if(argv[1][0] == '-')
	{
		file_loc = 2;
		while(-1 != (c = getopt(argc, argv,
			"-v" /* verbose output to stdout */
			"-t" /* print final hash table to stdout */
			"-c" /* print code output to stdout - without comments */
			"-C" /* print code output to stdout - with comments */
			"-x" /* print commands to stdout */
			"--help" /*print out usage statement */
		))) {

			switch (c)
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

	return 0;
}
