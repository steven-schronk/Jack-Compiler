#ifndef TEST_H_
#define TEST_H_

extern char *keywords[];

/* These are the unit tests for the compiler. */

/* Prints standardized message about the type of test */
void test_msg_start(char *msg);

/* Prints results of test message - exits if failed */
void test_msg_end(int pass);

int test_c_comments();

int test_nested_c_comments();

int test_cpp_comments();

int test_nested_cpp_comments();

int test_literal_strings();

int test_symbol_recog();

int test_keyword_recog();

int test_token_type();

int test_end_of_code();

int test_no_code();

int test_parse_expression();

int test_parse_expression_keyword();

int test_parse_expression_nested_array();

int test_parse_expression_nested_sub();

int test_parse_expression_class_sub();

int test_parse_expression_list();

int test_all();

#endif
