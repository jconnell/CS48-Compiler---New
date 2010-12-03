/*
 * tokens.h
 * 
 * CS 48 - Project Part 4
 * Jonathan Connell & David Kopec
 *
 */
#include "ast.h"

#ifndef TOK_H_
#define TOK_H_

#define MAXTOKENLEN 100

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

typedef int TokenType;

extern int TraceScan;	/* TRUE causes token info to be printed to the 
						 listing file as each token is recognized by scanner.*/

extern int lineno;		/* Source file's current line number */

extern char tokenString[MAXTOKENLEN+1];

extern FILE* source; /* source code text file */
extern FILE* listing; /* listing output text file */

int getToken(void);
char * copyString(char * s);
ast_node createNode(int type);
ast_node doParse(void);

#endif