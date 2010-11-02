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
	token tk;
	ttype ttyp;
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
	token tk;
	if(settings.tokens) { printf("<subroutineDec>\n"); }
	while(has_more_tokens(pC))
	{
		pC = advance(pC, pT);
		tk = token_type(pT);

		if(tk == KEYWORD) {
			/*if()*/
			if(strcmp(pT, "constructor") == 0 || strcmp(pT, "function") == 0 || strcmp(pT, "method") == 0)
			{

			} else {
				printf("\nCURRENT TOKEN: ->%s<-\n\n", pT);
				compiler_error(1, "Incorrect Token Type", pS, pC, pT);
			}
		} else {
			compiler_error(1, "Incorrect Token Type", pS, pC, pT);
		}
	}
	if(settings.tokens) { printf("</subroutineDec>\n"); }
}

void parse_params()
{

}

void parse_var_dec()
{

}

void parse_statements()
{

}

void parse_do()
{

}

void parse_let()
{

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

}


void parse_term()
{

}


void parse_expr_lst()
{

}

