#ifndef TEST_H_
#define TEST_H_

/* These are the unit tests for the compiler. */

/* Prints standardized message about the type of test */
void test_msg_start(char *msg);

/* Prints results of test message - exits if failed */
void test_msg_end(int pass);

int test_c_comments();

int test_nested_c_comments();

int test_cpp_comments();

int test_nested_cpp_comments();

int test_all();

#endif
