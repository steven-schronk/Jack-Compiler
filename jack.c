#include <stdio.h>
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
	char c;
	FILE *fp;

	if(argc < 2) { exit_error(1, "No Input Files."); usage(); }
	/* TODO: future versions will accept more than one file */
	if(argc > 3) { exit_error(2, "Too Many Files Listed."); usage(); }

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

	if(( fp = fopen(argv[1], "r")) == NULL) {
		exit_error(3, "Cannot Open Input (Source) File");
	}

	return 0;
}
