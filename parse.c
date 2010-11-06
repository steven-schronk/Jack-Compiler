#include <ctype.h>
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

	while(has_more_tokens(pC))
	{
		pC = advance(pC, pT);
		tk = token_type(pT);

		if(tk == KEYWORD) {
			ttyp = keyword(pT);
			if(settings.tokens) { printf("\t<keyword>%s</keyword>\n", pT); }
		} else if (tk == IDENTIFIER){
			if(settings.tokens) { printf("\t<identifier>%s</identifier>\n", pT); }
		} else if (tk == SYMBOL){
			if(settings.tokens) { printf("\t<symbol>%s</symbol>\n", pT); }
			if(pT[0] == '{')
			{
				parse_subroutine(pS, pC, pT);
			}
		} else {
			compiler_error(1, "Incorrect Token Type", pS, pC, pT);
		}
	}
	if(settings.tokens) { printf("</class>\n"); }
}

void parse_class_var_dec()
{

}

void parse_subroutine()
{
	if(settings.tokens) { printf("\t<subroutineDec>\n"); }
	if(has_more_tokens(pC) == TRUE)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
		if(tk == KEYWORD) {
			if(strcmp(pT, "constructor") == 0 || strcmp(pT, "function") == 0 || strcmp(pT, "method") == 0)
			{
				if(settings.tokens) { printf("\t\t<keyword>%s</keyword>\n", pT); }
			} else {
				compiler_error(8, "Incorrect Token Found: Must be 'constructor', 'function', or 'method'", pS, pC, pT);
			}
		}
	}

	/* look for return type of function */
	if(has_more_tokens(pC) == TRUE)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
		if(tk == KEYWORD || tk == IDENTIFIER)
		{
			if(strcmp(pT, "void") == 0)
			{
				if(settings.tokens) { printf("\t\t<keyword>%s</keyword>\n", pT); }
			} else {
				if(settings.tokens) { printf("\t\t<type>%s</type>\n", pT); }
			}
		} else {
			compiler_error(9, "Could Not Complete Parse Tree of Subroutine. Incomplete Program", pS, pC, pT);
		}
	} else {
		compiler_error(1, "Incorrect Token Type", pS, pC, pT);
	}

	/* look for subroutine name */
	if(has_more_tokens(pC) == TRUE)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
		if(tk == IDENTIFIER)
		{
			if(settings.tokens) { printf("\t\t<identifier>%s</identifier>\n", pT); }
		} else {
			compiler_error(9, "Could Not Complete Parse Tree of Subroutine. Incomplete Program", pS, pC, pT);
		}
	} else {
		compiler_error(10, "Incorrect Token Type. Looking for Keyword or Identifier.", pS, pC, pT);
	}

	/* look for symbol '(' that specifies beginning of parameter list */
	if(has_more_tokens(pC) == TRUE)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
		if(*pT == '(')
		{
			if(settings.tokens) { printf("\t\t<symbol>%s</symbol>\n", pT); }
			parse_params();
		} else {
			compiler_error(12, "Parameter List for Function Missing", pS, pC, pT);
		}
	} else {
		compiler_error(11, "Name of Function Must be an Identifier", pS, pC, pT);
	}

	/* look for end of parameter list */
	if(*pT != ')')
	{
		compiler_error(13, "Could Not Complete Parameter List for Function", pS, pC, pT);
	}

	/* look for opening brace for block */
	if(has_more_tokens(pC) == TRUE)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
		if(*pT == '{')
		{
			parse_var_dec();
		}
	} else {
		compiler_error(9, "Could Not Complete Parse Tree of Subroutine. Incomplete Program", pS, pC, pT);
	}

	/* look for 'let' keyword */
	if(strcmp(pT, "let") == 0)
	{
		parse_let();
	}

	if(settings.tokens) { printf("\t</subroutineDec>\n"); }
}

void parse_params()
{
	if(*pT == '(') { if(settings.tokens) { printf("\t\t<parameterList>\n"); } }

	/* look for datatype in parameter list */
	if(has_more_tokens(pC) == TRUE)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
		if(tk == KEYWORD) {
			if(strcmp(pT, "int") == 0 || strcmp(pT, "char") == 0 || strcmp(pT, "boolean") == 0)
			{
				if(settings.tokens) { printf("\t\t<keyword>%s</keyword>\n", pT); }
			} else {
				compiler_error(14, "Incorrect Token Type in Parameter List. Looking for Datatype name.", pS, pC, pT);
			}
		} else if(tk == SYMBOL && *pT == ')') { if(settings.tokens) { printf("\t\t</parameterList>\n"); } return; }
	} else {
		compiler_error(13, "Could Not Complete Parameter List for Function", pS, pC, pT);
	}

	/* look for identifier for this parameter */
	if(has_more_tokens(pC) == TRUE)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
		if(tk == IDENTIFIER) {
			if(settings.tokens) { printf("\t\t<identifier>%s</identifier>\n", pT); }

		} else {
			compiler_error(15, "Incorrect Token Type in Parameter List. Looking for Variable Identifier.", pS, pC, pT);
		}
	} else {
		compiler_error(13, "Could Not Complete Parameter List for Function", pS, pC, pT);
	}

	/* are there more parameters? */
	if(has_more_tokens(pC) == TRUE)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
		if(*pT == ',') {
			parse_params();
		} else if (*pT == ')') { /* exit parse_params */
			if(settings.tokens) { printf("\t\t</parameterList>\n"); }
			return;
		} else {
			compiler_error(16, "Incorrect Token Type in Parameter List. Looking for Comma or Parenthesis.", pS, pC, pT);
		}
	} else {
		compiler_error(13, "Could Not Complete Parameter List for Function", pS, pC, pT);
	}
}

void parse_var_dec()
{
	int i = 0;
	/* look for token named 'var' */
	if(has_more_tokens(pC) == TRUE)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
		if(strcmp(pT, "var") == 0)
		{
			if(settings.tokens) { printf("\t<varDec>%s</varDec>\n", pT); }
			/* look for variable data type */
			if(has_more_tokens(pC) == TRUE)
			{
				pC = advance(pC, pT);
				tk = token_type(pT);
				if(strcmp(pT, "int") == 0 || strcmp(pT, "char") == 0 || strcmp(pT, "boolean") == 0 || strcmp(pT, "Array") == 0)
				{
					if(settings.tokens) { printf("\t<identifier>%s</identifier>\n", pT); }
					/* look for identifier(s) for variable(s) */
					do {
						i = 0;
						if(has_more_tokens(pC) == TRUE)
						{
							pC = advance(pC, pT);
							tk = token_type(pT);
							if(tk == IDENTIFIER)
							{
								if(settings.tokens) { printf("\t<identifier>%s</identifier>\n", pT); }
								if(has_more_tokens(pC) == TRUE)
								{
									pC = advance(pC, pT);
									tk = token_type(pT);
									if((tk == SYMBOL) && (*pT == ';' || *pT == ',')) {
										if(*pT == ',') { i++; }
										if(settings.tokens) { printf("\t<symbol>%s</symbol>\n", pT); }
										if(i == 0)
										{
											parse_var_dec();
										}
									} else {
										compiler_error(18, "Improperly Terminated Variable Declaration", pS, pC, pT);
									}
								} else {
									compiler_error(17, "Could Not Complete Variable List of Subroutine. Incomplete Program", pS, pC, pT);
								}
							}
						} else {
							compiler_error(17, "Could Not Complete Variable List of Subroutine. Incomplete Program", pS, pC, pT);
						}
					} while (i > 0);
				} else {
					compiler_error(17, "Incorrect Data Type in Variable Declaration", pS, pC, pT);
				}
			}
		} else { return; }
	} else {
		compiler_error(17, "Could Not Complete Variable List of Subroutine. Incomplete Program", pS, pC, pT);
	}
}

void parse_statements()
{

}

void parse_do()
{

}

void parse_let()
{
	if(settings.tokens) { printf("\t\t<letStatement>\n"); }
	if(has_more_tokens(pC) == TRUE)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(20, "Could Not Complete Let Statement. Incomplete Program", pS, pC, pT);
	}

	if(*pT == '[') {
		parse_expression();
		if(has_more_tokens(pC) == TRUE)
		{
			pC = advance(pC, pT);
			tk = token_type(pT);
			if(*pT == ']') {
				if(settings.tokens) { printf("<symbol>%s</symbol>\n", pT); }
			} else {
				compiler_error(20, "Expression Not Terminated Correctly", pS, pC, pT);
			}
		} else {
			compiler_error(20, "Could Not Complete Let Statement. Incomplete Program", pS, pC, pT);
		}
	}

	/* look for an '=' symbol */
	if(has_more_tokens(pC) == TRUE)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(20, "Could Not Complete Let Statement. Incomplete Program", pS, pC, pT);
	}

	if(*pT == '=') {
		if(settings.tokens) { printf("<symbol>%s</symbol>\n", pT); }
	} else {
		compiler_error(20, "Could Not Complete Let Statement. Incomplete Program", pS, pC, pT);
	}

	parse_expression();

	if(settings.tokens) { printf("\t\t</letStatement>\n"); }
	exit_error(0, "Parsing Let");
}

void parse_while()
{

}

void parse_return()
{

}

void parse_if()
{

}

void parse_expression()
{
	if(has_more_tokens(pC) == TRUE)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(20, "Could Not Complete Expression List. Incomplete Program", pS, pC, pT);
	}
	do {
			if (*pT == '(')
			{
				if(settings.tokens) { printf("<symbol>%s</symbol>\n", pT); }
				printf("Parsing Expression List!\n");
				parse_expression();
			} else 	if(tk == IDENTIFIER) /* TODO: Also test for KeyworkConstant here */
			{
				if(settings.tokens) { printf("<identifier>%s</identifier>\n", pT); }
	 	 	 	 parse_term();
			} else if (strchr(BINARY_OP, *pT) != NULL) {
				if(settings.tokens) { printf("<symbol>%s</symbol>\n", pT); }
			}
			if(has_more_tokens(pC) == TRUE)
			{
				pC = advance(pC, pT);
				tk = token_type(pT);
			} else {
				compiler_error(20, "Could Not Complete Expression List. Incomplete Program", pS, pC, pT);
			}
	} while((strchr(BINARY_OP, *pT) != NULL) || tk == IDENTIFIER);
	return;
}

void parse_term()
{
	if(has_more_tokens(pC) == TRUE)
	{
		pC = advance(pC, pT);
		tk = token_type(pT);
	} else {
		compiler_error(25, "Could Not Complete Term. Incomplete Program", pS, pC, pT);
	}

	switch(*pT)
	{
		case '[':
			if(settings.tokens) { printf("<symbol>%s</symbol>\n", pT); }
			parse_expression();
			if(has_more_tokens(pC) == TRUE)
			{
				pC = advance(pC, pT);
				tk = token_type(pT);
				if(*pT == ']')
				{
					if(settings.tokens) { printf("<symbol>%s</symbol>\n", pT); }
				} else {
					compiler_error(26, "Improperly Terminated Array Expression. Symbol ']' Required at this Location.", pS, pC, pT);
				}
			} else {
				compiler_error(25, "Could Not Complete Term. Incomplete Program", pS, pC, pT);
			}
			break;
		case '(':
			if(settings.tokens) { printf("<symbol>%s</symbol>\n", pT); }
			parse_expr_lst();
			/*
			if(has_more_tokens(pC) == TRUE)
			{
				pC = advance(pC, pT);
				tk = token_type(pT);
				if(*pT == ')')
				{
					if(settings.tokens) { printf("<symbol>%s</symbol>\n", pT); }
				} else {
					compiler_error(27, "Improperly Terminated Subroutine Expression. Symbol ')' Required at this Location", pS, pC, pT);
				}
			} else {
				compiler_error(25, "Could Not Complete Term. Incomplete Program", pS, pC, pT);
			}
			*/
			break;
		case '.':
			if(settings.tokens) { printf("<symbol>%s</symbol>\n", pT); }
			break;
		default:
			return;
	}

	if(strchr(UNARY_OP, *pT) != NULL)
	{
		if(settings.tokens) { printf("<symbol>%s</symbol>\n", pT); }
		if(has_more_tokens(pC) == TRUE)
		{
			pC = advance(pC, pT);
			tk = token_type(pT);
			parse_term();
		} else {
			compiler_error(25, "Could Not Complete Term. Incomplete Program", pS, pC, pT);
		}
	}
}

void parse_expr_lst()
{
	while(*pT != ')')
	{
		if(*pT == ',')
		{
			if(settings.tokens) { printf("<symbol>%s</symbol>\n", pT); }
			if(has_more_tokens(pC) == TRUE)
			{
					pC = advance(pC, pT);
					tk = token_type(pT);
			} else {
				compiler_error(20, "Could Not Complete Expression List. Incomplete Program", pS, pC, pT);
			}
		} else {
			parse_expression();
		}
	}
}
