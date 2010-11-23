#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "error.h"
#include "jack.h"
#include "parse.h"
#include "test.h"
#include "token.h"

#define PASSED 0
#define FAILED 1

void test_msg_start(char *msg)
{
	int msg_length = strlen(msg);
	printf("%s", msg);

	/* 74 is 80 - length of "PASSED" */
	while(msg_length < 74)
	{
		putchar('.');
		msg_length++;
	}
}

void test_msg_end(int pass)
{
	if(pass == PASSED)
	{
		printf("PASSED\n");
	} else {
		printf("FAILED\n");
		exit_error(0, "UNIT TESTING FAILED");
	}
}

int test_c_comments()
{
	int result = 0;
	char *pStart = NULL;
	char source[] = "/* this is a test */ \tclass \0";

	test_msg_start("Testing C Comments");

	pC = pStart = source;
	pC = advance(pC, pT);

	/* token should be correct */
	if(strcmp(pT, "class") != 0) { result++; }

	/* pointer to code should be in correct position */
	if(pC - pStart != 27) { result++; }

	if(result == PASSED)
	{
		test_msg_end(PASSED);
	} else {
		test_msg_end(FAILED);
	}

	return result;
}

int test_nested_c_comments()
{
	int result = 0;
	char *pStart = NULL;
	char source[] = "/* this /*is a test */ \tclass \0";

	test_msg_start("Testing Nested C Comments");
	pC = pStart = source;
	pC = advance(pC, pT);

	/* token should be correct */
	if(strcmp(pT, "class") != 0) { result++; }

	/* pointer to code should be in correct position */
	if(pC - pStart != 29) { result++; }

	if(result == PASSED)
	{
		test_msg_end(PASSED);
	} else {
		test_msg_end(FAILED);
	}

	return result;
}

int test_cpp_comments()
{
	int result = 0;
	char *pStart = NULL;
	char source[] = "// this is a test\nclass \0";

	test_msg_start("Testing C++ Comments");
	pC = pStart = source;
	pC = advance(pC, pT);

	/* token should be correct */
	if(strcmp(pT, "class") != 0) { result++; }

	/* pointer to code should be in correct position */
	if(pC - pStart != 23) { result++; }

	if(result == PASSED)
	{
		test_msg_end(PASSED);
	} else {
		test_msg_end(FAILED);
	}

	return result;
}

int test_nested_cpp_comments()
{
	int result = 0;
	char *pStart = NULL;
	char source[] = "// this is a //test\nclass \0";

	test_msg_start("Testing Nested C++ Comments");
	pC = pStart = source;
	pC = advance(pC, pT);

	/* token should be correct */
	if(strcmp(pT, "class") != 0) { result++; }

	/* pointer to code should be in correct position */
	if(pC - pStart != 25) { result++; }

	if(result == PASSED)
	{
		test_msg_end(PASSED);
	} else {
		test_msg_end(FAILED);
	}

	return result;
}

int test_literal_strings()
{
	int result = 0;
	char *pStart = NULL;
	char source[] = "\"S\" \0";

	test_msg_start("Testing String Literals");
	pC = pStart = source;
	pC = advance(pC, pT);

	/* token should be correct */
	if(strcmp(pT, "S") != 0) { result++; }

	/* pointer to code should be in correct position */
	if(pC - pStart != 3) { result++; }

	if(result == PASSED)
	{
		test_msg_end(PASSED);
	} else {
		test_msg_end(FAILED);
	}

	return result;
}

int test_symbol_recog()
{
	int result = 0;
	char *pStart = NULL;
	char source[] = "(){\0";

	test_msg_start("Testing Symbol Recognition");
	pC = pStart = source;
	pC = advance(pC, pT);

	/* token should be correct */
	if(strcmp(pT, "(") != 0) { result++; }

	/* pointer to code should be in correct position */
	if(pC - pStart != 1) { result++; }

	if(result == PASSED)
	{
		test_msg_end(PASSED);
	} else {
		test_msg_end(FAILED);
	}

	return result;
}

int test_keyword_recog()
{
	int result = 0;
	return result;
}

int test_token_type()
{
	int result = 0;
	int i = 0;

	test_msg_start("Testing Token Type Recognition");

	while(keywords[i] != NULL)
	{
		strcpy(pT, keywords[i]);
		tk = -1; /* be certain this value is changed */
		tk = token_type(pT);
		if(tk != KEYWORD) { result++; }
		i++;
	}

	if(result == PASSED)
	{
		test_msg_end(PASSED);
	} else {
		test_msg_end(FAILED);
	}

	return result;
}

int test_end_of_code()
{
	int result = 0;
	char source[] = "\n\0";

	test_msg_start("Testing For EOF Source");

	pC = source;
	result = has_more_tokens(pC);

	if(result == PASSED)
	{
		test_msg_end(PASSED);
	} else {
		test_msg_end(FAILED);
	}

	return result;
}

int test_no_code()
{
	int result = 0;
	test_msg_start("Testing For NULL Source");

	pC = NULL;
	result = has_more_tokens(pC);

	if(result == PASSED)
	{
		test_msg_end(PASSED);
	} else {
		test_msg_end(FAILED);
	}

	return result;
}

int test_parse_expression()
{
	int result = 0;
	char source[] = "-(-(2 + (-12 / 12)*83));\n while";

	test_msg_start("Testing Expression Parsing");

	pC = source;
	pC = advance(pC, pT);
	tk = token_type(pT);

	parse_expression();

	/* pointer to code should be in correct position */
	if(pC - source != 24) { result++; }

	/* token should be correct */
	if(strcmp(pT, ";") != 0) { result++; }

	if(result == PASSED)
	{
		test_msg_end(PASSED);
	} else {
		test_msg_end(FAILED);
	}

	return result;
}

int test_all()
{
	int result = 0;

	/* modify settings regardless of command line options */
	settings.tokens = 0;

	result += test_c_comments();
	result += test_nested_c_comments();
	result += test_cpp_comments();
	result += test_nested_cpp_comments();
	result += test_literal_strings();
	result += test_symbol_recog();
	result += test_keyword_recog();
	result += test_token_type();
	result += test_end_of_code();
	result += test_no_code();
	result += test_parse_expression();

	return result;
}
