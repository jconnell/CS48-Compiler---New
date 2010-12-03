%{
//By David Kopec and Jon Connell for CS 48
//#include "util.h"
//#include "scan.h"
#include "tokens.h"

#define IF			258
#define ELSE		259
#define READ		260
#define	WRITE		261
#define BANG		262
#define EQUALS		263
#define NOTEQUALS	264
#define GREATER		265
#define GREATEREQ	266
#define LESS		267
#define LESSEQ		268
#define DO			269
#define WHILE		270
#define FOR			271
#define	LPAREN		272
#define	RPAREN		273
#define	LBRACKET	274
#define	RBRACKET	275
#define AND			276
#define OR			277
#define SEMI		278
#define	INT			279
#define DOUBLE		280
#define CHAR		281
#define SWITCH		282
#define CASE		283
#define CONST		284
#define	CONTINUE    285
#define	DEFAULT		286
#define RETURN		287
#define SIZEOF		288
#define STATIC		289
#define VOID		290
#define BREAK		291
#define INCR		292
#define DECR		293
#define COMMENT		294
#define	INUM			295
#define	ID			296
#define DIVIDE		297
#define	ASSIGN		298
#define	MULTIPLY	299
#define	ADD			300
#define SUBTRACT	301
#define FNUM		302
#define STRING		303

//#define YY_NO_UNISTD_H

/*we redefine the name of yylex so it doesn't conflict
with the definition in the bison file (cs48.y)*/
/*
#define YY_DECL int lexscan(void)*/
	
	char tokenString[MAXTOKENLEN +1];
	int lineno = 1;
%}

string		\".*\"
digit 		[0-9]
fnumber		-?(({digit}*\.{digit}+)|({digit}+\.{digit}*))
inumber 	-?{digit}+
letter 		[a-zA-Z]
identifier 	{letter}({letter}|{digit}|"_")*
whitespace	[ \t]+
eol		[\n]
endoffile	"^Z"

%%

"if"		{return IF;}
"else"		{return ELSE;}
"read"		{return READ;}
"write"		{printf("Found write\n"); return WRITE;}
"do"		{return DO;}
"while"		{return WHILE;}
"for"		{return FOR;}
"int"		{	printf("Found int\n");
			return INT;}
"double"	{return DOUBLE;}
"switch"	{printf("Found switch\n"); return SWITCH;}
"case"		{printf("Found case\n"); return CASE;}
"const"		{return CONST;}
"continue"	{return CONTINUE;}
"default"	{printf("Found default\n"); return DEFAULT;}
"return"	{return RETURN;}
"sizeof"	{return SIZEOF;}
"void"		{return VOID;}
"break"		{printf("Found break\n"); return BREAK;}
"static"	{return STATIC;}

"/*"		{ char c;
			  int done = 0;
			  do {
				  while ((c=input()) != '*')
					  continue;
				  while ((c=input()) == '*')
					  continue;
				  if (c == '/') done = 1;
				 } while (!done);
			}

"//"		{ char c;
			  int done = 0;
			  do {
				  while ((c=input()) != '\n')
					  continue;
				  if (c == '\n')
				{ 
					done = 1;
					lineno++;
				}
			} while (!done);
			}

{eol}		{lineno++;}

"=="		{return EQUALS;}
"!="		{return NOTEQUALS;}
">="		{return GREATEREQ;}
"<="		{return LESSEQ;}
"&&"		{return AND;}
"||"		{return OR;}
"++"		{return INCR;}
"--"		{return DECR;}

"="			{return ASSIGN;}
"+"			{return ADD;}
"-"			{return SUBTRACT;}
"*"			{return MULTIPLY;}
"/"			{return DIVIDE;}
">"			{return GREATER;}
"<"			{return LESS;}
"("			{return '(';}
")"			{return ')';}
"{"			{return '{';}
"}"			{return '}';}
"["			{return '[';}
"]"			{return ']';}
";"			{
			printf("Found ;\n");
			return ';';}
":"			{return ':';}
","			{return ',';}
"!"			{return BANG;}

{string}		{return STRING;}
{fnumber}		{return FNUM;}
{inumber}		{return INUM;}
{identifier}		{printf("Found id\n");
			return ID;}
{whitespace}	{;}
<<EOF>>		return 0;


%%
