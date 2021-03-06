#ifndef PARSE_H_
#define PARSE_H_

#include "token.h"

extern char *pS;
extern char *pC;
extern char pT[];
extern token  tk;
extern ttype ttyp;
extern int space_count;

/*
* Compiles a complete class.
*/
void parse_class();

/*
* Compiles a static declaration or a field declaration.
*/
void parse_class_var_dec();

/*
* Compiles a complete method, function or constructor.
*/
void parse_subroutine();

/*
* Compiles a (possibly empty) parameter list.
* Skips over the parentheses.
*/
void parse_params();

/*
* Compiles a variable declaration.
*/
void parse_var_dec();

/*
* Compiles a sequence of statements.
* Skips over opening and closing braces.
*/
void parse_statements();

/*
* Compiles do statement.
*/
void parse_do();

/*
* Compiles let statement.
*/
void parse_let();

/*
* Compiles while statement.
*/
void parse_while();

/*
* Compiles return statement.
*/
void parse_return();

/*
* Compiles an if statement, possibly including an else statement.
*/
void parse_if();

/*
* Compiles and expression.
*/
void parse_expression(int count);

/*
* Compiles a term.
* Must determine if if current token is an identifier and must
* distinguish between a variable, array entry or a subroutine call.
* The three tokens "[", "(" and "." determine the option.
* Any other token is not part of this term and should not be advanced over.
*/
void parse_term();

/*
 *	Compiles a call to a defined subroutine.
 */
void parse_subroutine_call();

/*
* Compiles a (possibly empty) comma-separated list of expressions.
*/
void parse_expr_lst();

#endif
