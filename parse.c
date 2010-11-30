#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "error.h"
#include "jack.h"
#include "parse.h"
#include "token.h"

void parse_class()
{
	if(settings.tokens)
	{
		token_print("class", OPEN);
		space_count++;
	}

	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(40, "Incomplete Class Declaration", pS, pC, pT);
	}

	if(strcmp(pT, "class") == 0 ) {
	if(settings.tokens) { token_print("keyword", BOTH); }
	} else {
		compiler_error(43, "Incorrect Token Found: Must be 'class'", pS, pC, pT);
	}

	/* look for class name */
	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
			compiler_error(40, "Incomplete Class Declaration", pS, pC, pT);
	}

	if (tk == IDENTIFIER){
		if(settings.tokens) { token_print("identifier", BOTH); }
	} else {
		compiler_error(44, "Could Not Find Class Name or Subroutine Name at This Location", pS, pC, pT);
	}

	/* look for '{' symbol */
	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
			compiler_error(40, "Incomplete Class Declaration", pS, pC, pT);
	}

	if (tk == SYMBOL)
	{
		if(settings.tokens) { token_print("symbol", BOTH); }
	} else {
		compiler_error(44, "Could Not Find Class Name or Subroutine Name at This Location", pS, pC, pT);
	}

	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(40, "Incomplete Class Declaration", pS, pC, pT);
	}

	while(strcmp(pT, "static") == 0 || strcmp(pT, "field") == 0)
	{
		parse_class_var_dec();
		if(has_more_tokens(pC) == true)
		{
			pC = advance(pC, pT);
			tk = token_type(pT);
		} else {
			compiler_error(40, "Incomplete Class Declaration", pS, pC, pT);
		}
	}

	while(strcmp(pT, "constructor") == 0 || strcmp(pT, "function") == 0 || strcmp(pT, "method") == 0)
	{
		parse_subroutine();
		if(has_more_tokens(pC) == true)
		{
			pC = advance(pC, pT);
			tk = token_type(pT);
		} else {
			compiler_error(40, "Incomplete Class Declaration", pS, pC, pT);
		}
	}

	if(*pT == '}')
	{
		if(settings.tokens) { token_print("symbol", BOTH); }
	} else {
		compiler_error(40, "Incomplete Class Declaration", pS, pC, pT);
	}

	if(settings.tokens)
	{
		space_count--;
		token_print("class", CLOSE);
	}
}

void parse_class_var_dec()
{
	if(settings.tokens)
	{
		token_print("classVarDec", OPEN);
		space_count++;
	}

	/* look for 'static' or 'field' */
	if(settings.tokens) { token_print("keyword", BOTH); }
	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(40, "Incomplete Class Declaration", pS, pC, pT);
	}

	/* look for type */
	if(tk == IDENTIFIER) {
		if(settings.tokens) { token_print("identifier", BOTH); }
	} else if (tk == KEYWORD) {
		if(strcmp(pT, "int") == 0 || strcmp(pT, "char") == 0 || strcmp(pT, "boolean") == 0) {
			if(settings.tokens) { token_print("keyword", BOTH); }
		} else {
			compiler_error(41, "Token Must be Data Type.", pS, pC, pT);
		}
	} else {
		compiler_error(41, "Token Must be Data Type", pS, pC, pT);
	}

	/* look or variable name */
	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(40, "Incomplete Class Declaration", pS, pC, pT);
	}
	if(tk == IDENTIFIER) {
		if(settings.tokens) { token_print("identifier", BOTH); }
	} else {
		compiler_error(42, "Token Must be Variable Name", pS, pC, pT);
	}

	/* look for ',' */
	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(40, "Incomplete Class Declaration", pS, pC, pT);
	}

	if(*pT == ',') {
		do {
			if(settings.tokens) { token_print("symbol", BOTH); }
			if(has_more_tokens(pC) == true)
			{
				pC = advance(pC, pT);
				tk = token_type(pT);
			} else {
				compiler_error(40, "Incomplete Class Declaration", pS, pC, pT);
			}
			if(tk == IDENTIFIER) {
				if(settings.tokens) { token_print("identifier", BOTH); }
			} else {
				compiler_error(42, "Token Must be Variable Name", pS, pC, pT);
			}
			if(has_more_tokens(pC) == true)
			{
				pC = advance(pC, pT);
				tk = token_type(pT);
			} else {
				compiler_error(40, "Incomplete Class Declaration", pS, pC, pT);
			}
		} while (*pT == ',');
	}

	if(*pT == ';') {
		if(settings.tokens) { token_print("symbol", BOTH); }
	} else {
		compiler_error(33, "Could Not Find ';' Symbol At This Location", pS, pC, pT);
	}

	if(settings.tokens)
	{
		space_count--;
		token_print("classVarDec", CLOSE);
	}
}

void parse_subroutine()
{
	if(settings.tokens)
	{
		token_print("subroutineDec", OPEN);
		space_count++;
	}

	if(tk == KEYWORD) {
		if(strcmp(pT, "constructor") == 0 || strcmp(pT, "function") == 0 || strcmp(pT, "method") == 0)
		{
			if(settings.tokens) { token_print("keyword", BOTH); }
		} else {
			compiler_error(8, "Incorrect Token Found: Must be 'constructor', 'function', or 'method'", pS, pC, pT);
		}
	}

	/* look for return type of function */
	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
		if(tk == KEYWORD || tk == IDENTIFIER)
		{
			if(strcmp(pT, "void") == 0)
			{
				if(settings.tokens) { token_print("keyword", BOTH); }
			} else {
				if(settings.tokens) { token_print("identifier", BOTH); }
			}
		} else {
			compiler_error(9, "Could Not Complete Parse Tree of Subroutine. Incomplete Program", pS, pC, pT);
		}
	} else {
		compiler_error(29, "Incorrect Token Type", pS, pC, pT);
	}

	/* look for subroutine name */
	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
		if(tk == IDENTIFIER)
		{
			if(settings.tokens) { token_print("identifier", BOTH); }
		} else {
			compiler_error(9, "Could Not Complete Parse Tree of Subroutine. Incomplete Program", pS, pC, pT);
		}
	} else {
		compiler_error(10, "Incorrect Token Type. Looking for Keyword or Identifier.", pS, pC, pT);
	}

	/* look for symbol '(' that specifies beginning of parameter list */
	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
		if(*pT == '(')
		{
			if(settings.tokens) { token_print("symbol", BOTH); }
			parse_params();
		} else {
			compiler_error(12, "Parameter List for Function Missing", pS, pC, pT);
		}
	} else {
		compiler_error(11, "Name of Function Must be an Identifier", pS, pC, pT);
	}

	/* look for end of parameter list */
	if(*pT == ')')
	{
		if(settings.tokens)
		{
			token_print("symbol", BOTH);
			token_print("subroutineBody", OPEN);
			space_count++;
		}
	} else {
		compiler_error(13, "Could Not Complete Parameter List for Function", pS, pC, pT);
	}

	/* look for opening brace for block */
	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
		if(*pT == '{')
		{
			if(settings.tokens) { token_print("symbol", BOTH); }
			if(has_more_tokens(pC) == true)
			{
				pC = advance(pC, pT);
				tk = token_type(pT);
			} else {
				compiler_error(17, "Could Not Complete Variable List of Subroutine. Incomplete Program", pS, pC, pT);
			}
			parse_var_dec();
		}
	} else {
		compiler_error(9, "Could Not Complete Parse Tree of Subroutine. Incomplete Program", pS, pC, pT);
	}

	parse_statements();

	if(*pT == '}')
	{
		if(settings.tokens) { token_print("symbol", BOTH); }
	} else {
		compiler_error(17, "Could Not Complete Subroutine. Incomplete Program", pS, pC, pT);
	}

	if(settings.tokens)
	{
		space_count--;
		token_print("subroutineBody", CLOSE);
		space_count--;
		token_print("subroutineDec", CLOSE);
	}
}

void parse_params()
{
	if(*pT == '(') { if(settings.tokens) { token_print("parameterList", OPEN); space_count++; } }

	/* look for datatype in parameter list */
	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
		if(tk == KEYWORD) {
			if(strcmp(pT, "int") == 0 || strcmp(pT, "char") == 0 || strcmp(pT, "boolean") == 0)
			{
				if(settings.tokens) { token_print("keyword", BOTH); }
			} else {
				compiler_error(14, "Incorrect Token Type in Parameter List. Looking for Datatype name.", pS, pC, pT);
			}
		} else if(tk == SYMBOL && *pT == ')') {
			if(settings.tokens)
			{
				space_count--;
				token_print("parameterList", CLOSE);
			}
			return;
		}
	} else {
		compiler_error(13, "Could Not Complete Parameter List for Function", pS, pC, pT);
	}

	/* look for identifier for this parameter */
	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
		if(tk == IDENTIFIER) {
			if(settings.tokens) { token_print("identifier", BOTH); }
		} else {
			compiler_error(15, "Incorrect Token Type in Parameter List. Looking for Variable Identifier.", pS, pC, pT);
		}
	} else {
		compiler_error(13, "Could Not Complete Parameter List for Function", pS, pC, pT);
	}

	/* are there more parameters? */
	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
		if(*pT == ',') {
			if(settings.tokens) { token_print("symbol", BOTH); }
			parse_params();
		} else if (*pT == ')') { /* exit parse_params */
			if(settings.tokens)
			{
				space_count--;
				token_print("parameterList", CLOSE);
			}
			return;
		} else {
			compiler_error(16, "Incorrect Token Type in Parameter List. Looking for ',' or ')'", pS, pC, pT);
		}
	} else {
		compiler_error(13, "Could Not Complete Parameter List for Function", pS, pC, pT);
	}
}

void parse_var_dec()
{
	/* look for token named 'var' */
	if(strcmp(pT, "var") == 0)
	{
		if(settings.tokens)
		{
			token_print("varDec", OPEN);
			token_print("symbol", BOTH);
		}
	} else { return; }

	/* look for variable data type */
	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
		if(strcmp(pT, "int") == 0 || strcmp(pT, "char") == 0 || strcmp(pT, "boolean") == 0 || strcmp(pT, "Array") == 0)
		{
			if(settings.tokens) { token_print("identifier", BOTH); }

		} else if (tk == IDENTIFIER) { /* could also be a custom class name */
			if(settings.tokens) { token_print("identifier", BOTH); }
		} else {
			compiler_error(17, "Could Not Complete Variable List of Subroutine. Incomplete Program", pS, pC, pT);
		}
	}

	/* look for identifier(s) for variable(s) */
	do {
		if(has_more_tokens(pC) == true)
		{
			pC = advance(pC, pT);
			tk = token_type(pT);
		} else {
			compiler_error(17, "Could Not Complete Variable List of Subroutine. Incomplete Program", pS, pC, pT);
		}
		if(tk == IDENTIFIER)
		{
			if(settings.tokens) { token_print("identifier", BOTH); }
		}

		if(has_more_tokens(pC) == true)
		{
			pC = advance(pC, pT);
			tk = token_type(pT);
		} else {
			compiler_error(17, "Could Not Complete Variable List of Subroutine. Incomplete Program", pS, pC, pT);
		}
		if(tk == SYMBOL)
		{
			if(settings.tokens) { token_print("symbol", BOTH); }
		}
	} while (*pT == ',');

	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(17, "Could Not Complete Variable List of Subroutine. Incomplete Program", pS, pC, pT);
	}
	parse_var_dec();
}

void parse_statements()
{
	if(settings.tokens)
	{
		token_print("statements", OPEN);
		space_count++;
	}
	do {
		if(strcmp(pT, "let") == 0)
		{
			parse_let();
		} else if(strcmp(pT, "if") == 0)
		{
			parse_if();
		} else if(strcmp(pT, "while") == 0)
		{
			parse_while();
		} else if(strcmp(pT, "do") == 0)
		{
			parse_do();
		} else if(strcmp(pT, "return") == 0)
		{
			parse_return();
		}

		if(has_more_tokens(pC) == true)
		{
			pC = advance(pC, pT);
			tk = token_type(pT);
		}

	} while (strcmp(pT, "let") == 0 || strcmp(pT, "if") == 0 || strcmp(pT, "while") == 0 || \
			 strcmp(pT, "do") == 0  || strcmp(pT, "return") == 0 );
	if(settings.tokens)
	{
		space_count--;
		token_print("statements", CLOSE);
	}
}

void parse_do()
{
	if(settings.tokens)
	{
		token_print("doStatement", OPEN);
		space_count++;
		token_print("keyword", BOTH);
	}

	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(20, "Could Not Complete Do Statement. Incomplete Program", pS, pC, pT);
	}

	/* must be an identifier */
	if(tk == IDENTIFIER) {
		parse_subroutine_call();
	} else {
		compiler_error(30, "Subroutine Name Must Be Listed Here", pS, pC, pT);
	}

	if(*pT == ';')
	{
		if(settings.tokens) { token_print("symbol", BOTH); }
	} else {
		compiler_error(33, "Could Not Find ';' Symbol At This Location.", pS, pC, pT);
	}

	if(settings.tokens)
	{
		space_count--;
		token_print("doStatement", CLOSE);
	}
}

void parse_let()
{
	int found_array = 0;
	if(settings.tokens)
	{
		token_print("letStatement", OPEN);
		space_count++;
		token_print("keyword", BOTH);
	}

	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(20, "Could Not Complete Let Statement. Incomplete Program", pS, pC, pT);
	}

	/* look for an identifier - must be a variable name */
	if(tk == IDENTIFIER)
	{
		if(settings.tokens) { token_print("identifier", BOTH); }
	} else {
		compiler_error(31, "Could Not Find Identifier At This Location", pS, pC, pT);
	}

	/* optional '[' for an array offset value */
	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(20, "Could Not Complete Let Statement. Incomplete Program", pS, pC, pT);
	}

	if(*pT == '[')
	{
		found_array++;
		if(settings.tokens) { token_print("symbol", BOTH); }
		if(has_more_tokens(pC) == true)
		{
			pC = advance(pC, pT);
			tk = token_type(pT);
		} else {
			compiler_error(20, "Could Not Complete Let Statement. Incomplete Program", pS, pC, pT);
		}
		parse_expression();
	}

	/* should be closing ']' here if variable was array */
	if(found_array && *pT == ']')
	{
		if(settings.tokens) { token_print("symbol", BOTH); }
		if(has_more_tokens(pC) == true)
		{
			pC = advance(pC, pT);
			tk = token_type(pT);
		} else {
			compiler_error(20, "Could Not Find ']' Symbol At This Location", pS, pC, pT);
		}
	}

	if(*pT == '=')
	{
		if(settings.tokens) { token_print("symbol", BOTH); }
	} else {
		compiler_error(32, "Could Not Find '=' Symbol At This Location", pS, pC, pT);
	}

	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(20, "Could Not Complete Let Statement. Incomplete Program", pS, pC, pT);
	}

	parse_expression();

	if(*pT == ';')
	{
		if(settings.tokens) { token_print("symbol", BOTH); }
	} else {
		compiler_error(33, "Could Not Find ';' Symbol At This Location", pS, pC, pT);
	}

	if(settings.tokens)
	{
		space_count--;
		token_print("letStatement", CLOSE);
	}
}

void parse_while()
{
	if(settings.tokens)
	{
		token_print("whileStatement", OPEN);
		space_count++;
		token_print("keyword", BOTH);
	}

	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(47, "Could Not Complete While Statement. Incomplete Program", pS, pC, pT);
	}

	if(*pT == '(')
	{
		if(settings.tokens) { token_print("symbol", BOTH); }
	} else {
		compiler_error(39, "Could Not Find '(' Symbol At This Location", pS, pC, pT);
	}

	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(47, "Could Not Complete While Statement. Incomplete Program", pS, pC, pT);
	}

	parse_expression();

	if(*pT == ')')
	{
		if(settings.tokens) { token_print("symbol", BOTH); }
	} else {
		compiler_error(38, "Could Not Find ')' Symbol At This Location", pS, pC, pT);
	}

	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(47, "Could Not Complete While Statement. Incomplete Program", pS, pC, pT);
	}

	if(*pT == '{')
	{
		if(settings.tokens) { token_print("symbol", BOTH); }
	} else {
		compiler_error(45, "Could Not Find '{' Symbol At This Location", pS, pC, pT);
	}

	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(47, "Could Not Complete While Statement. Incomplete Program", pS, pC, pT);
	}

	parse_statements();

	if(*pT == '}')
	{
		if(settings.tokens) { token_print("symbol", BOTH); }
	} else {
		compiler_error(46, "Could Not Find '}' Symbol At This Location", pS, pC, pT);
	}

	if(settings.tokens)
	{
		space_count--;
		token_print("whileStatement", CLOSE);
	}
}

void parse_return()
{
	if(settings.tokens)
	{
		token_print("returnStatement", OPEN);
		space_count++;
		token_print("keyword", BOTH);
	}

	/* look for ';' */
	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(20, "Could Not Complete Let Statement. Incomplete Program", pS, pC, pT);
	}

	if (*pT != ';') { parse_expression(); }

	if(*pT == ';')
	{
		if(settings.tokens) { token_print("symbol", BOTH); }
	} else {
		compiler_error(33, "Could Not Find ';' Symbol At This Location", pS, pC, pT);
	}
	if(settings.tokens)
	{
		space_count--;
		token_print("returnStatement", CLOSE);
	}
}

void parse_if()
{
	char *pTemp = NULL;

	if(settings.tokens)
	{
		token_print("ifStatement", OPEN);
		space_count++;
		token_print("keyword", BOTH);
	}

	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(47, "Could Not Complete If Statement. Incomplete Program", pS, pC, pT);
	}

	if(*pT == '(')
	{
		if(settings.tokens) { token_print("symbol", BOTH); }
	} else {
		compiler_error(39, "Could Not Find '(' Symbol At This Location", pS, pC, pT);
	}

	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(47, "Could Not Complete If Statement. Incomplete Program", pS, pC, pT);
	}

	parse_expression();

	if(*pT == ')')
	{
		if(settings.tokens) { token_print("symbol", BOTH); }
	} else {
		compiler_error(38, "Could Not Find ')' Symbol At This Location", pS, pC, pT);
	}

	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(47, "Could Not Complete If Statement. Incomplete Program", pS, pC, pT);
	}

	if(*pT == '{')
	{
		if(settings.tokens) { token_print("symbol", BOTH); }
	} else {
		compiler_error(45, "Could Not Find '{' Symbol At This Location", pS, pC, pT);
	}

	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(47, "Could Not Complete If Statement. Incomplete Program", pS, pC, pT);
	}

	parse_statements();

	if(*pT == '}')
	{
		pTemp = pC; /* store pointer to where we are - in case no 'else' clause exists */
		if(settings.tokens) { token_print("symbol", BOTH); }
	} else {
		compiler_error(46, "Could Not Find '}' Symbol At This Location", pS, pC, pT);
	}

	/* Look forward and see if 'else' clause is there*/
	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(47, "Could Not Complete If Statement. Incomplete Program", pS, pC, pT);
	}

	if(strcmp(pT, "else") == 0)
	{
		if(settings.tokens) { token_print("keyword", BOTH); };

		if(has_more_tokens(pC) == true)
		{
			pC = advance(pC, pT);
			tk = token_type(pT);
		} else {
			compiler_error(47, "Could Not Complete If Statement. Incomplete Program", pS, pC, pT);
		}

		if(*pT == '{')
		{
			if(settings.tokens) { token_print("symbol", BOTH); }
		} else {
			compiler_error(45, "Could Not Find '{' Symbol At This Location", pS, pC, pT);
		}

		parse_statements();

		if(*pT == '}')
		{
			if(settings.tokens) { token_print("symbol", BOTH); }
		} else {
			compiler_error(46, "Could Not Find '}' Symbol At This Location", pS, pC, pT);
		}
	} else {
		pC = pTemp-1; /* rewind back to end of 'if' statement */
		if(has_more_tokens(pC) == true)
		{
			pC = advance(pC, pT);
			tk = token_type(pT);
		} else {
			compiler_error(47, "Could Not Complete If Statement. Incomplete Program", pS, pC, pT);
		}
	}

	if(settings.tokens)
	{
		space_count--;
		token_print("ifStatement", CLOSE);
	}
}

void parse_expression()
{
	if(settings.tokens)
	{
		token_print("expression", OPEN);
		space_count++;
	}
	parse_term();

	if(strchr(BINARY_OP, *pT) != NULL)
	{
		if(settings.tokens) { token_print("operator", BOTH); }
			if(has_more_tokens(pC) == true)
			{
				pC = advance(pC, pT);
				tk = token_type(pT);
			} else {
				compiler_error(34, "Could Not Parse Expression. Incomplete Program", pS, pC, pT);
			}
			parse_expression();
	}
	if(settings.tokens)
	{
		space_count--;
		token_print("expression", CLOSE);
	}
}

void parse_term()
{
	if(settings.tokens)
	{
		token_print("term", OPEN);
		space_count++;
	}

	if(tk == INT_CONST)
	{
		if(settings.tokens) { token_print("intConst", BOTH); }
		if(has_more_tokens(pC) == true)
		{
			pC = advance(pC, pT);
			tk = token_type(pT);
		} else {
			compiler_error(25, "Could Not Complete Term. Incomplete Program", pS, pC, pT);
		}
		return;
	}

	if(strchr(UNARY_OP, *pT) != NULL)
	{
		if(settings.tokens) { token_print("unaryOperator", BOTH); }
		if(has_more_tokens(pC) == true)
		{
			pC = advance(pC, pT);
			tk = token_type(pT);
		} else {
			compiler_error(25, "Could Not Complete Term. Incomplete Program", pS, pC, pT);
		}
		parse_term();
	}

	if(tk == KEYWORD)
	{
		if(settings.tokens) { token_print("keyword", BOTH); }

		if(has_more_tokens(pC) == true)
		{
			pC = advance(pC, pT);
			tk = token_type(pT);
		} else {
			compiler_error(25, "Could Not Complete Term. Incomplete Program", pS, pC, pT);
		}
	}

	if(tk == IDENTIFIER)
	{
		if(settings.tokens) { token_print("identifier", BOTH); }

		if(has_more_tokens(pC) == true)
		{
			pC = advance(pC, pT);
			tk = token_type(pT);
		} else {
			compiler_error(25, "Could Not Complete Term. Incomplete Program", pS, pC, pT);
		}
	}

	switch(*pT)
	{
		case '[':
			if(settings.tokens) { token_print("symbol", BOTH); }

			if(has_more_tokens(pC) == true)
			{
				pC = advance(pC, pT);
				tk = token_type(pT);
			} else {
				compiler_error(25, "Could Not Complete Term. Incomplete Program", pS, pC, pT);
			}
			parse_expression();
			if(*pT == ']')
			{
				if(settings.tokens) { token_print("symbol", BOTH); }
				/* parse_expression(); */
				} else {
					compiler_error(26, "Improperly Terminated Array Expression. Symbol ']' Required at this Location.", pS, pC, pT);
			}

			if(has_more_tokens(pC) == true)
			{
				pC = advance(pC, pT);
				tk = token_type(pT);
			} else {
				compiler_error(25, "Could Not Complete Term. Incomplete Program", pS, pC, pT);
			}
			break;
		case '(':
			if(settings.tokens) { token_print("symbol", BOTH); }

			if(has_more_tokens(pC) == true)
			{
				pC = advance(pC, pT);
				tk = token_type(pT);
			} else {
				compiler_error(25, "Could Not Complete Term. Incomplete Program", pS, pC, pT);
			}

			parse_expression();

			if (*pT == ')') {
				if(settings.tokens) { token_print("symbol", BOTH); }
			} else {
				compiler_error(38, "Could Not Find Symbol ')' At This Location", pS, pC, pT);
			}

			if(has_more_tokens(pC) == true)
			{
				pC = advance(pC, pT);
				tk = token_type(pT);
			} else {
				compiler_error(25, "Could Not Complete Term. Incomplete Program", pS, pC, pT);
			}
			break;
		case '.':
			if(settings.tokens) { token_print("symbol", BOTH); }

			if(has_more_tokens(pC) == true)
			{
				pC = advance(pC, pT);
				tk = token_type(pT);
			} else {
				compiler_error(25, "Could Not Complete Term. Incomplete Program", pS, pC, pT);
			}

			parse_subroutine_call();
			break;
	}

	if(settings.tokens)
	{
		space_count--;
		token_print("term", CLOSE);
	}
}

void parse_subroutine_call()
{
	if(tk == IDENTIFIER)
	{
		if(settings.tokens) { token_print("identifier", BOTH); }
	} else {
		compiler_error(35, "Could Not Find Class Name or Subroutine Name at This Location", pS, pC, pT);
	}

	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(36, "Could Not Complete Subroutine Call. Incomplete Program", pS, pC, pT);
	}

	if (*pT == '.') {
			if(settings.tokens) { token_print("symbol", BOTH); }
			if(has_more_tokens(pC) == true)
			{
				pC = advance(pC, pT);
				tk = token_type(pT);
			} else {
				compiler_error(36, "Could Not Complete Subroutine Call. Incomplete Program", pS, pC, pT);
			}
			if(tk == IDENTIFIER)
			{
				if(settings.tokens) { token_print("identifier", BOTH); }
			} else {
				compiler_error(37, "Could Not Find Method Name or Subroutine Name at This Location", pS, pC, pT);
			}
	}

	if(*pT != '(') /* this for calls with no class name at beginning */
	{
		if(has_more_tokens(pC) == true)
		{
			pC = advance(pC, pT);
			tk = token_type(pT);
		} else {
			compiler_error(36, "Could Not Complete Subroutine Call. Incomplete Program", pS, pC, pT);
		}
	}

	if(*pT == '(')
	{
		if(settings.tokens) { token_print("symbol", BOTH); }
	} else {
		compiler_error(39, "Could Not Find Symbol '(' At This Location", pS, pC, pT);
	}

	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(36, "Could Not Complete Subroutine Call. Incomplete Program", pS, pC, pT);
	}

	parse_expr_lst();

	if(*pT == ')')
	{
		if(settings.tokens) { token_print("symbol", BOTH); }
	} else {
		compiler_error(38, "Could Not Find Symbol ')' At This Location", pS, pC, pT);
	}

	if(has_more_tokens(pC) == true)
	{
			pC = advance(pC, pT);
			tk = token_type(pT);
	} else {
		compiler_error(24, "Could Not Complete Subroutine Call. Incomplete Program", pS, pC, pT);
	}
}

void parse_expr_lst()
{
	if(settings.tokens) { token_print("expressionList", OPEN); }
	while(*pT != ')')
	{
		if(*pT == ',')
		{
			if(settings.tokens) { token_print("symbol", BOTH); }
			if(has_more_tokens(pC) == true)
			{
					pC = advance(pC, pT);
					tk = token_type(pT);
			} else {
				compiler_error(24, "Could Not Complete Expression List. Incomplete Program", pS, pC, pT);
			}
		} else {
			parse_expression();
		}
	}
	if(settings.tokens) { token_print("expressionList", CLOSE); }
}
