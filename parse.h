#ifndef PARSE_H_
#define PARSE_H_

/*
* Compiles a complete class.
*
* pS is pointer to beginning of source code.
* pC is pointer to beginning of token where error occurred.
* pT is pointer to token.
*/
void parse_class(char *pS, char *pC, char pT[]);

/*
* Compiles a static declaration or a field declaration.
*/
void parse_class_var_dec(char *pC, char pT[]);

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
void parse_expression();

/*
* Compiles a term.
* Must determine if if current token is an identifier and must
* distinguish between a variable, array entry or a subroutine call.
* The three tokens "[", "(" and "." determine the option.
* Any other token is not part of this term and should not be advanced over.
*/
void parse_term();

/*
* Compiles a (possibly empty) comma-separated list of expressions.
*/
void parse_expr_lst();


#endif
