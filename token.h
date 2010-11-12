#ifndef TOKEN_H_
#define TOKEN_H_

#define KEYWORD_COUNT 21
#define SYMBOLS "{}()[].,;+-*/&|<>=~"
#define SPACES "\t\n\r "
#define BINARY_OP "*+-&/|<>="
#define UNARY_OP "-~"

typedef enum {
	BOOLEAN, CHAR, CLASS, CONSTRUCTOR, DO, ELSE,
	FALSE, FIELD, FUNCTION, IF, INT, LET, METHOD,
	 NUL, RETURN, STATIC, THIS, TRUE, VAR, VOID, WHILE
} ttype;

typedef enum { KEYWORD, SYMBOL, IDENTIFIER, INT_CONST, STRING_CONST } token;

/*
* Look at source stream and determine if more tokens are available.
* Returns > 0 if more are found and 0 if none found.
*/
int has_more_tokens(char *pC);

/*
 * Move source pointer to next token in source stream.
 * pC is pointer to code and pT is pointer to an
 * array of char that contains the token.
 * Should be called only if has_more_tokens is true.
 */
char *advance(char *pC, char pT[]);

/*
 * Returns type of current token.
 */
token token_type(char pT[]);

/*
 * Returns keyword of current token.
 * Called only when token_type is KEYWORD.
 */
ttype keyword(char pT[]);

/*
 * Returns character which is the current token.
 * Called only when token_type is a SYMBOL.
 */
char symbol();

/*
 * Returns identifier which is the current token.
 * Called only when token_type is IDENTIFIER.
 */
char *identifier(char *str);

/*
 * Returns integer value of the current token.
 * Called only when token_type is INT_CONST.
 */
int int_val(char pT[]);

/*
 * Returns a pointer to an array of char, without double quotes.
 * Called only when token_type is STRING_CONST.
 */
char *string_val();

#endif

