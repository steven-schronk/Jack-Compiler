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
	if(settings.tokens) { printf("<class>\n"); }

	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(40, "Incomplete Class Declaration", pS, pC, pT);
	}

	if(strcmp(pT, "class") == 0 ) {
	if(settings.tokens) { printf("\t<keyword>%s</keyword>\n", pT); }
	} else {
		compiler_error(40, "Incorrect Token Found: Must be 'class'", pS, pC, pT);
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
		if(settings.tokens) { printf("\t<identifier>%s</identifier>\n", pT); }
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

	if (tk == SYMBOL){
		if(settings.tokens) { printf("\t<symbol>%s</symbol>\n", pT); }
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

	parse_subroutine();

	if(settings.tokens) { printf("</class>\n"); }
}

void parse_class_var_dec()
{
	if(settings.tokens) { printf("<classVarDec>\n"); }

	/* look for 'static' or 'field' */
	if(settings.tokens) { printf("\t<identifier>%s</identifier>\n", pT); }
	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(40, "Incomplete Class Declaration", pS, pC, pT);
	}

	/* look for type */
	if(tk == IDENTIFIER) {
		if(settings.tokens) { printf("\t<identifier>%s</identifier>\n", pT); }
	} else if (tk == KEYWORD) {
		if(strcmp(pT, "int") == 0 || strcmp(pT, "char") == 0 || strcmp(pT, "boolean") == 0) {
			if(settings.tokens) { printf("\t<keyword>%s</keyword>\n", pT); }
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
		if(settings.tokens) { printf("\t<identifier>%s</identifier>\n", pT); }
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
			if(settings.tokens) { printf("\t<symbol>%s</symbol>\n", pT); }
			if(has_more_tokens(pC) == true)
			{
				pC = advance(pC, pT);
				tk = token_type(pT);
			} else {
				compiler_error(40, "Incomplete Class Declaration", pS, pC, pT);
			}
			if(tk == IDENTIFIER) {
				if(settings.tokens) { printf("\t<identifier>%s</identifier>\n", pT); }
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
		if(settings.tokens) { printf("\t<symbol>%s</symbol>\n", pT); }
	} else {
		compiler_error(33, "Could Not Find ';' Symbol At This Location", pS, pC, pT);
	}

	if(settings.tokens) { printf("</classVarDec>\n"); }
}

void parse_subroutine()
{
	if(settings.tokens) { printf("<subroutineDec>\n"); }

	if(tk == KEYWORD) {
		if(strcmp(pT, "constructor") == 0 || strcmp(pT, "function") == 0 || strcmp(pT, "method") == 0)
		{
			if(settings.tokens) { printf("\t<keyword>%s</keyword>\n", pT); }
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
				if(settings.tokens) { printf("\t<keyword>%s</keyword>\n", pT); }
			} else {
				if(settings.tokens) { printf("\t<type>%s</type>\n", pT); }
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
			if(settings.tokens) { printf("\t<identifier>%s</identifier>\n", pT); }
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
			if(settings.tokens) { printf("\t<symbol>%s</symbol>\n", pT); }
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
		if(settings.tokens) { printf("\t<symbol>%s</symbol>\n", pT); }
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
			if(settings.tokens) { printf("\t<symbol>%s</symbol>\n", pT); }
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

	while(strcmp(pT, "let") == 0 || strcmp(pT, "if") == 0 || strcmp(pT, "while") == 0 || strcmp(pT, "do") == 0 || strcmp(pT, "return") == 0)
	{
		parse_statements();
		if(has_more_tokens(pC) == true)
		{
			pC = advance(pC, pT);
			tk = token_type(pT);
		} else {
			compiler_error(9, "Could Not Complete Parse Tree of Subroutine. Incomplete Program", pS, pC, pT);
		}
	}

	if(settings.tokens) { printf("</subroutineDec>\n"); }
}

void parse_params()
{
	if(*pT == '(') { if(settings.tokens) { printf("<parameterList>\n"); } }

	/* look for datatype in parameter list */
	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
		if(tk == KEYWORD) {
			if(strcmp(pT, "int") == 0 || strcmp(pT, "char") == 0 || strcmp(pT, "boolean") == 0)
			{
				if(settings.tokens) { printf("\t<keyword>%s</keyword>\n", pT); }
			} else {
				compiler_error(14, "Incorrect Token Type in Parameter List. Looking for Datatype name.", pS, pC, pT);
			}
		} else if(tk == SYMBOL && *pT == ')') { if(settings.tokens) { printf("</parameterList>\n"); } return; }
	} else {
		compiler_error(13, "Could Not Complete Parameter List for Function", pS, pC, pT);
	}

	/* look for identifier for this parameter */
	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
		if(tk == IDENTIFIER) {
			if(settings.tokens) { printf("\t<identifier>%s</identifier>\n", pT); }

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
			parse_params();
		} else if (*pT == ')') { /* exit parse_params */
			if(settings.tokens) { printf("</parameterList>\n"); }
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
		if(settings.tokens) { printf("<varDec>\n\t<symbol>%s</symbol>\n", pT); }
	} else { return; }

	/* look for variable data type */
	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
		if(strcmp(pT, "int") == 0 || strcmp(pT, "char") == 0 || strcmp(pT, "boolean") == 0 || strcmp(pT, "Array") == 0)
		{
			if(settings.tokens) { printf("\t<identifier>%s</identifier>\n", pT); }

		} else if (tk == IDENTIFIER) { /* could also be a custom class name */
			if(settings.tokens) { printf("\t<identifier>%s</identifier>\n", pT); }
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
			if(settings.tokens) { printf("\t<identifier>%s</identifier>\n", pT); }
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
			if(settings.tokens) { printf("\t<symbol>%s</symbol>\n", pT); }
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
}

void parse_do()
{
	if(settings.tokens) { printf("<doStatement>\n\t<keyword>do</keyword>\n"); }
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

	if(settings.tokens) { printf("</doStatement>\n"); }
}

void parse_let()
{
	if(settings.tokens) { printf("<letStatement>\n\t<keyword>let</keyword>\n"); }
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
		if(settings.tokens) { printf("\t<identifier>%s</identifier>\n", pT); }
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
		if(settings.tokens) { printf("\t<symbol>%s</symbol>\n", pT); }
		parse_expression();
	}

	if(*pT == ']')
	{
		if(settings.tokens) { printf("\t<symbol>%s</symbol>\n", pT); }
	}

	/* look for '=' */
	if(*pT == '=')
	{
		if(settings.tokens) { printf("\t<symbol>%s</symbol>\n", pT); }
	} else {
		compiler_error(32, "Could Not Find '=' Symbol At This Location", pS, pC, pT);
	}

	/* parse_expression(); */

	/* look for identifier */
	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(20, "Could Not Complete Let Statement. Incomplete Program", pS, pC, pT);
	}

	if(tk == IDENTIFIER)
	{
		if(settings.tokens) { printf("\t<identifier>%s</identifier>\n", pT); }
	} else {
		compiler_error(20, "Could Not Find ';' Symbol At This Location", pS, pC, pT);
	}

	/* look for ';' */
	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(20, "Could Not Complete Let Statement. Incomplete Program", pS, pC, pT);
	}

	if(*pT == ';')
	{
		if(settings.tokens) { printf("\t<symbol>%s</symbol>\n", pT); }
	} else {
		compiler_error(33, "Could Not Find ';' Symbol At This Location", pS, pC, pT);
	}

	if(settings.tokens) { printf("</letStatement>\n"); }
}

void parse_while()
{

	exit_error(0, "Parsing While");
}

void parse_return()
{
	if(settings.tokens) { printf("<returnStatement>\n\t<identifier>%s</identifier>\n", pT); }

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
		if(settings.tokens) { printf("\t<symbol>%s</symbol>\n", pT); }
	} else {
		compiler_error(33, "Could Not Find ';' Symbol At This Location", pS, pC, pT);
	}
	if(settings.tokens) { printf("</returnStatement>\n"); }
}

void parse_if()
{
	exit_error(0, "Parsing If");
}

void parse_expression()
{
	do {
		if(settings.tokens) { printf("<expression>%s</expression>\n", pT); }
		if(has_more_tokens(pC) == true)
		{
			pC = advance(pC, pT);
			tk = token_type(pT);
		} else {
			compiler_error(34, "Could Not Parse Expression. Incomplete Program", pS, pC, pT);
		}
	} while (*pT != ']' && *pT != ';');
}

void parse_term()
{
	if(has_more_tokens(pC) == true)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(25, "Could Not Complete Term. Incomplete Program", pS, pC, pT);
	}

	switch(*pT)
	{
		case '[':
			if(settings.tokens) { printf("\t<symbol>%s</symbol>\n", pT); }
			parse_term();
			if(has_more_tokens(pC) == true)
			{
				pC = advance(pC, pT);
				tk = token_type(pT);
				if(*pT == ']')
				{
					if(settings.tokens) { printf("\t<symbol>%s</symbol>\n", pT); }
				} else {
					compiler_error(26, "Improperly Terminated Array Expression. Symbol ']' Required at this Location.", pS, pC, pT);
				}
			} else {
				compiler_error(25, "Could Not Complete Term. Incomplete Program", pS, pC, pT);
			}
			break;
		case '(':
			if(settings.tokens) { printf("\t<symbol>%s</symbol>\n", pT); }
			parse_expr_lst();
			break;
		case '.':
			if(settings.tokens) { printf("\t<symbol>%s</symbol>\n", pT); }
			break;
		default:
			return;
	}

	if(strchr(UNARY_OP, *pT) != NULL)
	{
		if(settings.tokens) { printf("\t<symbol>%s</symbol>\n", pT); }
		if(has_more_tokens(pC) == true)
		{
			pC = advance(pC, pT);
			tk = token_type(pT);
			parse_term();
		} else {
			compiler_error(25, "Could Not Complete Term. Incomplete Program", pS, pC, pT);
		}
	}
}

void parse_subroutine_call()
{
	if(settings.tokens) { printf("<subroutineCall>\n"); }
	if(tk == IDENTIFIER)
	{
		if(settings.tokens) { printf("\t<identifier>%s</identifier>\n", pT); }
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
			if(settings.tokens) { printf("\t<symbol>%s</symbol>\n", pT); }
			if(has_more_tokens(pC) == true)
			{
				pC = advance(pC, pT);
				tk = token_type(pT);
			} else {
				compiler_error(36, "Could Not Complete Subroutine Call. Incomplete Program", pS, pC, pT);
			}
			if(tk == IDENTIFIER)
			{
				if(settings.tokens) { printf("\t<identifier>%s</identifier>\n", pT); }
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
		if(settings.tokens) { printf("\t<symbol>%s</symbol>\n", pT); }
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
			if(settings.tokens) { printf("\t<symbol>%s</symbol>\n", pT); }
			if(has_more_tokens(pC) == true)
			{
				pC = advance(pC, pT);
				tk = token_type(pT);
			} else {
				compiler_error(38, "Could Not Find Symbol ')' At This Location", pS, pC, pT);
			}
		}
	} else {
		compiler_error(39, "Could Not Find Symbol '(' At This Location", pS, pC, pT);
	}

	if(*pT == ';')
	{
		if(settings.tokens) { printf("\t<symbol>%s</symbol>\n", pT); }
	}

	if(settings.tokens) { printf("<subroutineCall>\n"); }
}

void parse_expr_lst()
{
	while(*pT != ')')
	{
		if(*pT == ',')
		{
			if(settings.tokens) { printf("\t<symbol>%s</symbol>\n", pT); }
			if(has_more_tokens(pC) == true)
			{
					pC = advance(pC, pT);
					tk = token_type(pT);
			} else {
				compiler_error(24, "Could Not Complete Expression List. Incomplete Program", pS, pC, pT);
			}
		} else {
			parse_term();
		}
	}
}
