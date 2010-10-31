#ifndef ERROR_H_
#define ERROR_H_

/*
* Prints error to stdout along with error number and string description of problem.
* Exits program without recourse.
*/
void exit_error(const int err_num, const char *err_msg);

/*
* Display Warnings about assembler status as needed.
*
* These are messages to the user that contain both an error number
* as well as simple description of what went wrong.
* 
* Error number corresponds to number listed in documentation.
*
*/
void warning_error(const int err_num, const char *err_msg);

/*
* Compiler error informs user of poorly formated code.
* Prints line of code error occurs on and gives message about what went wrong.
*
* comp_num is unique number for compiler error.
* err_msg is unique text message for user.
* pS is pointer to beginning of source code.
* pC is pointer to beginning of token where error occurred.
*
*/
void compiler_error(const int comp_num, const char *err_msg, char *pS, char *pC);

/*
* Prints line number that error/warning occurred for user.
*/
void line_notification(const int line_num);

#endif
