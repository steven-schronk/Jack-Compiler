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

int test_all()
{
	int result = 0;

	result += test_c_comments();
	result += test_nested_c_comments();
	result += test_cpp_comments();
	result += test_nested_cpp_comments();

	return result;
}
