/*
By David Kopec and Jonathan Connell for CS 48
This defines the bison input for our compiler.
The parser contained herein complies with all of the
grammar rules of C48.
Small parts of this file are based on tiny.y from the appendix to 
the Louden book.
*/
%{
#define YYPARSER /* distinguishes Yacc output from other code files */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tokens.h"	/* from the lexer */
#include "ast.h"	/* for the node definitions and functions */

/*for verbose errors*/
#define YYERROR_VERBOSE 1

#define YYSTYPE ast_node
static ast_node savedTree; /* stores syntax tree for later return */
extern char *yytext;		/*the token's text from the lexxer*/
%}

/* make sure these values match up with the lexxer ones in lexer.l */
%token IF			258
%token ELSE		259
%token READ		260
%token	WRITE		261
%token BANG		262
%token EQUALS		263
%token NOTEQUALS	264
%token GREATER		265
%token GREATEREQ	266
%token LESS		267
%token LESSEQ		268
%token DO			269
%token WHILE		270
%token FOR			271
%token	LPAREN		272
%token	RPAREN		273
%token	LBRACKET	274
%token	RBRACKET	275
%token AND			276
%token OR			277
%token SEMI		278
%token	INT			279
%token DOUBLE		280
%token CHAR		281
%token SWITCH		282
%token CASE		283
%token CONST		284
%token	CONTINUE    285
%token	DEFAULT		286
%token RETURN		287
%token SIZEOF		288
%token STATIC		289
%token VOID		290
%token BREAK		291
%token INCR		292
%token DECR		293
%token COMMENT		294
%token	INUM			295
%token	ID			296
%token DIVIDE		297
%token	ASSIGN		298
%token	MULTIPLY	299
%token	ADD			300
%token SUBTRACT	301
%token FNUM		302
%token STRING		303

/*set precedences of operations*/

%right ASSIGN
%left OR
%left AND
%left EQUALS NOTEQUALS
%left LESS GREATER LESSEQ GREATEREQ
%left ADD SUBTRACT
%left MULTIPLY DIVIDE
%right BANG DECR INCR 

%% /* Grammar for C 48 based on website grammar with some modifications and additions*/

/*at the start of the program we have a root node and the first sequence, this is just
how we start every program*/
program		: declaration_list
		{
		$$ = createNode(ROOT);
		/*root must have a sequence as a child
		and that sequence will have all the declarations*/
		$$->left_child = createNode(SEQ);
		$$->left_child->left_child = $1; 
		savedTree = $$; 
		}
		;

/*left recursion is common in this grammar and we always do it the same way;
by going through the right_siblings until we find one that is null*/
declaration_list : declaration_list declaration
		{ YYSTYPE t = $1;
                   if (t != NULL)
                   { while (t->right_sibling != NULL)
                        t = t->right_sibling;
                     t->right_sibling = $2;
                     $$ = $1; 
		   }
                     else $$ = $2;
                 }
		| declaration
		{ $$ = $1; }
		;

/*whenever something is just a direct transfer from one rule to the next
you will see this construct of $$ = $1*/
declaration	: var_declaration
		{ $$ = $1; }
		| func_declaration
		{ $$ = $1; }
		;

/*if it has an ARRAY_SIZE as a child, then we know that's
an array and we do an array declare,
otherwise it's just a regular declare*/
var_declaration : INT var_decl_list ';'
		{
		/*check for any ARRAY_SIZE nodes and declare those differently*/
		YYSTYPE t = $2;
		/*this is just a dummy that will get overwritten*/
		$$ = createNode(INT_DEC);
		YYSTYPE v = $$;
		while(t != NULL)
		{
			/*if the ARRAY_SIZE thing is where expected, then we do an array dec*/
			if(t->left_child != NULL && t->left_child->node_type == ARRAY_SIZE)
			{
				v->right_sibling = createNode(INT_ARRAY_DEC); 
				v->right_sibling->left_child = t;
				t=t->right_sibling;
				v->right_sibling->left_child->right_sibling = NULL;
			}
			else
			{
				v->right_sibling = createNode(INT_DEC); 
				v->right_sibling->left_child = t;
				t=t->right_sibling;
				v->right_sibling->left_child->right_sibling = NULL;
			}
			v=v->right_sibling;
		}
		/*cleanup overwrite dummy original v and start where the good stuff starts*/
		v = $$;
		$$ = $$->right_sibling;
		free(v);
		}
		| DOUBLE var_decl_list ';'
		{
		/*check for any ARRAY_SIZE nodes and declare those differently*/
		YYSTYPE t = $2;
		/*this is just a dummy that will get overwritten*/
		$$ = createNode(DOU_DEC);
		YYSTYPE v = $$;
		while(t != NULL)
		{
			/*if the ARRAY_SIZE thing is where expected, then we do an array dec*/
			if(t->left_child != NULL && t->left_child->node_type == ARRAY_SIZE)
			{
				v->right_sibling = createNode(DOU_ARRAY_DEC); 
				v->right_sibling->left_child = t;
				t=t->right_sibling;
				v->right_sibling->left_child->right_sibling = NULL;
			}
			else
			{
				v->right_sibling = createNode(DOU_DEC); 
				v->right_sibling->left_child = t;
				t=t->right_sibling;
				v->right_sibling->left_child->right_sibling = NULL;
			}
			v=v->right_sibling;
		}
		/*cleanup overwrite dummy original v*/
		v = $$;
		$$ = $$->right_sibling;
		free(v);
		}
		;

/*again, this is like the last left recursion*/
var_decl_list	: var_decl_list ',' var_decl
		{ YYSTYPE t = $1;
                   if (t != NULL)
                   { while (t->right_sibling != NULL)
                        t = t->right_sibling;
                     t->right_sibling = $3;
                     $$ = $1; 
		   }
                     else $$ = $3;
                 }
		| var_decl
		{$$ = $1;}
		;

/*an edifier is just a convenient way of making an IDENTIFIER when we see
an ID token*/
idifier		: ID
		{
		$$ = createNode(IDENTIFIER);
                   $$->value.string = 
                         copyString(yytext);
		}
		;

/*the size of the declared array*/
arraylen	: INUM
		{
			$$ = createNode(INT_LITERAL);
			$$->value.int_value = atoi(yytext);
		}
		;

/*if an ID after a declaration has a left child that is an expression then it should be
turned into an assign quad in quads.c after the variable is declared*/
var_decl	: idifier 
		{ 
		$$ = $1;
                 }
		/*we must check for dangling assignments in quads when we're doing
		variable declarations - if the id has a child then
		we should be assigning it that value as a quad*/
		| idifier ASSIGN expression
		{
		$$ = $1;
		$$->left_child = $3;
		}
		| idifier '[' arraylen ']'
		/*we're going to have to check for an ARRAY_SIZE node to see if it's an array dec*/
		{
			$$ = $1;
			$$->left_child = createNode(ARRAY_SIZE);
			$$->left_child->left_child = $3;
		}
		;

/*we're not worrying about return types, our bad, but
formal params are just dummies since we worry about the params only in the 
caller as in Louden.  We do however need to store the compound_statement, since this
is what will actually get executed later!*/
func_declaration : INT idifier '(' formal_params ')' compound_statement
		{
		$$ = createNode(FUNC_DEF);
		$$->left_child = $2;
		$$->left_child->right_sibling = $4;
		$$->left_child->right_sibling->right_sibling = $6;
		}
		|  DOUBLE idifier '(' formal_params ')' compound_statement
		{
		$$ = createNode(FUNC_DEF);
		$$->left_child = $2;
		$$->left_child->right_sibling = $4;
		$$->left_child->right_sibling->right_sibling = $6;
		}
		|  VOID idifier '(' formal_params ')' compound_statement
		{
		$$ = createNode(FUNC_DEF);
		$$->left_child = $2;
		$$->left_child->right_sibling = $4;
		$$->left_child->right_sibling->right_sibling = $6;
		}
		;

/*this is those empty params*/
formal_params	: formal_list {$$ = $1;}
		/*just put a blank param in*/
		| VOID {$$ = createNode(FUNC_PARAM);}
		| {$$ = createNode(FUNC_PARAM);}
		;

/* lists of empties */
formal_list	: formal_list ',' formal_param
		{ YYSTYPE t = $1;
                   if (t != NULL)
                   { while (t->right_sibling != NULL)
                        t = t->right_sibling;
                     t->right_sibling = $3;
                     $$ = $1; 
		   }
                     else $$ = $3;
                 }
		| formal_param
		{$$ = $1;}
		;

/*we skip over these currently in quads since we only
look at this at the point of call, so we'll just put blank
ones here */
formal_param	: INT idifier
		{$$ = createNode(FUNC_PARAM);}
		| DOUBLE idifier
		{$$ = createNode(FUNC_PARAM);}
		| INT idifier '[' ']'
		{$$ = createNode(FUNC_PARAM);}
		| DOUBLE idifier '[' ']'
		{$$ = createNode(FUNC_PARAM);}
		;

/*this should be a sequence with both nonterminals as children
since they are both lists*/
compound_statement : '{' local_declarations statement_list '}'
		{
		$$ = createNode(SEQ);
		$$->left_child = $2;
		YYSTYPE t = $2;
                   if (t != NULL)
                   { while (t->right_sibling != NULL)
                        t = t->right_sibling;
                     t->right_sibling = $3; 
		   }
		   else
			$$->left_child = $3;
		}
		;
/* same left recursion shizzle again */
local_declarations : local_declarations var_declaration
		{ YYSTYPE t = $1;
                   if (t != NULL)
                   { while (t->right_sibling != NULL)
                        t = t->right_sibling;
                     t->right_sibling = $2;
                     $$ = $1; 
		   }
                     else $$ = $2;
                 }
		|
		{
		$$ = NULL;
		}
		;
/* and yet again */
statement_list	: statement_list statement
		{ YYSTYPE t = $1;
                   if (t != NULL)
                   { while (t->right_sibling != NULL)
                        t = t->right_sibling;
                     t->right_sibling = $2;
                     $$ = $1; 
		   }
                     else $$ = $2;
                 }
		|
		{
		$$ = NULL;
		}
		;

/* just basic one to ones */
statement	: expression_statement
		{ $$ = $1; }
		| compound_statement
		{ $$ = $1; }
		| if_statement
		{ $$ = $1; }
		| while_statement
		{ $$ = $1; }
		| do_while_statement
		{ $$ = $1; }
		| for_statement
		{ $$ = $1; }
		| return_statement
		{ $$ = $1; }
		| read_statement
		{ $$ = $1; }
		| write_statement
		{ $$ = $1; }
		| switch_statement
		{ $$ = $1; }
		;

/*switch statement is an addition the original grammar, it features
a var that's compared and a list of cases*/
switch_statement : SWITCH '(' var ')' '{' cases '}'
		{
		$$ = createNode(SWITCH_ST);
		$$->left_child = $3;
		$$->left_child->right_sibling = $6;
		printf("created switch\n");
		}
		;

/*same left recursion as before */
cases		: cases acase
		{
		 YYSTYPE t = $1;
                   if (t != NULL)
                   { while (t->right_sibling != NULL)
                        t = t->right_sibling;
                     t->right_sibling = $2;
                     $$ = $1; 
		   }
                     else $$ = $2;
		}
		| acase
		{$$ = $1;}
		;

/* a comparison can be a literal or a variable */
casecompare	: var
		{$$ = $1;}
		| INUM
		{$$ = createNode(INT_LITERAL);
		$$->value.int_value = atoi(yytext);}
		| FNUM
		{$$ = createNode(DOUBLE_LITERAL);
		$$->value.double_value = atof(yytext);}
		;

/*all cases have a list of statement if the comparison is true to execute,
the last case is always default*/
acase		: CASE casecompare ':' statement_list
		{
			$$ = createNode(SWITCH_CASE);
			$$->left_child = $2;
			$$->left_child->right_sibling = $4;
		}
		/*we always process the default in quads, and it's always last, unless there was a break to stop us
		so we'll just make it a sequence*/
		| DEFAULT ':' statement_list
		{
			$$ = createNode(SEQ);
			$$->left_child = $3;
		}
		;

/*expressions sometimes need to end in semicolon, here it is*/
expression_statement : expression ';'
		{ $$ = $1; }
		| ';'
		{ $$ = NULL;}
		;

/*left child is the evaluation, left child->right sibling
is what to do if the evaluation is true,
if_else adds additionally another child to do if the statement
is false and only if it's false*/

if_statement	: IF '(' expression ')' statement
		{ $$ = createNode(IF_S);
		$$->left_child = $3;
		$$->left_child->right_sibling = $5;
		}
		| IF '(' expression ')' statement ELSE statement
		{ $$ = createNode(IF_ELSE);
		$$->left_child = $3;
		$$->left_child->right_sibling = $5;
		$$->left_child->right_sibling->right_sibling = $7;
		}
		;


/*left_child is the expression, right_sibling is what to execute while it's true*/
while_statement : WHILE '(' expression ')' statement
		{
			$$ = createNode(WHILE_LOOP);
			$$->left_child = $3;
			$$->left_child->right_sibling = $5;
		}
		;

/*quads still expects the expression as the left_child, so we keep it there
and this is the same as for a WHILE loop almost*/
do_while_statement : DO statement WHILE '(' expression ')' ';'
		{
			$$ = createNode(DO_WHILE_LOOP);
			$$->left_child = $5;
			$$->left_child->right_sibling = $2;
		}
		;

/* quads expects the fore_header_expressions in order followed by the statement */
for_statement	: FOR '(' for_header_expression ';' for_header_expression ';' for_header_expression ')' statement
		{
			$$ = createNode(FOR_LOOP);
			$$->left_child = $3;
			$$->left_child->right_sibling = $5;
			$$->left_child->right_sibling->right_sibling = $7;
			$$->left_child->right_sibling->right_sibling->right_sibling = $9;
		}
		;


/* we can't have null, so we just put a one in when nothing is entered */
for_header_expression : expression
		{$$ = $1;}
		|
		{
			$$ = createNode(INT_LITERAL);
			
		}
		;

/*if there is something to return, we put it as the 
child of the return node*/
return_statement : RETURN ';'
		{$$ = createNode(RETURN_S);}
		| RETURN expression ';'
		{$$ = createNode(RETURN_S);
		$$->left_child = $2;}
		;

/*read has whatever is being read into as a child*/
read_statement	: READ var ';'
		{
		$$ = createNode(READ_S);
		$$->left_child = $2;
		}
		;

/*we just create a node with the string as its value*/
strl		: STRING
		{
			$$ = createNode(STRING_LITERAL);
			$$->value.string = 
                         copyString(yytext);
		}
		;

/*write has what's being written as its child*/
write_statement : WRITE expression ';'
		{
		$$ = createNode(WRITE_S);
		$$->left_child = $2;
		}
		| WRITE strl ';'
		{
		$$ = createNode(WRITE_S);
		$$->left_child = $2;
		}
		;

/*an expression can be an assignment to a var*/
expression	: var ASSIGN expression
		{
		$$ = createNode(OP_ASSIGN);
		$$->left_child = $1;
		$$->left_child->right_sibling = $3;
		}
		/*r-value covers most expressions*/
		| r_value
		{ $$ = $1; }
		;

/*a var is an array pull or just an id*/
var		: idifier
		{$$ = $1;}
		/*ID is the first child, the index into it is the second*/
		| idifier '[' expression ']'
		{
		$$ = createNode(ARRAY_PULL);
		$$->left_child = $1;
		$$->left_child->right_sibling = $3;
		}
		;

/*these are all pretty self explanatory;
the children are the operands of each operation*/
r_value		: expression ADD expression
		{
		$$ = createNode(OP_PLUS);
		$$->left_child = $1;
		$$->left_child->right_sibling = $3;
		}
		| expression SUBTRACT expression
		{
		$$ = createNode(OP_MINUS);
		$$->left_child = $1;
		$$->left_child->right_sibling = $3;
		}
		| expression MULTIPLY expression
		{
		$$ = createNode(OP_TIMES);
		$$->left_child = $1;
		$$->left_child->right_sibling = $3;
		}
		| expression DIVIDE expression
		{
		$$ = createNode(OP_DIVIDE);
		$$->left_child = $1;
		$$->left_child->right_sibling = $3;
		}
		| expression LESS expression
		{
		$$ = createNode(OP_LESS_THAN);
		$$->left_child = $1;
		$$->left_child->right_sibling = $3;
		}
		| expression LESSEQ expression
		{
		$$ = createNode(OP_LESS_EQUALS);
		$$->left_child = $1;
		$$->left_child->right_sibling = $3;
		}
		| expression GREATER expression
		{
		$$ = createNode(OP_GREATER_THAN);
		$$->left_child = $1;
		$$->left_child->right_sibling = $3;
		}
		| expression GREATEREQ expression
		{
		$$ = createNode(OP_GREATER_EQUALS);
		$$->left_child = $1;
		$$->left_child->right_sibling = $3;
		}
		| expression EQUALS expression
		{
		$$ = createNode(OP_EQUALS);
		$$->left_child = $1;
		$$->left_child->right_sibling = $3;
		}
		| expression NOTEQUALS expression
		{
		$$ = createNode(OP_NOT_EQUALS);
		$$->left_child = $1;
		$$->left_child->right_sibling = $3;
		}
		| expression AND expression
		{
		$$ = createNode(OP_AND);
		$$->left_child = $1;
		$$->left_child->right_sibling = $3;
		}
		| expression OR expression
		{
		$$ = createNode(OP_OR);
		$$->left_child = $1;
		$$->left_child->right_sibling = $3;
		}
		| BANG expression
		{
		$$ = createNode(OP_NOT);
		$$->left_child = $2;
		}
		| SUBTRACT expression
		{
		$$ = createNode(OP_NEGATIVE);
		$$->left_child = $2;
		}
		| var
		{$$ = $1;}
		| INCR expression
		{
		$$ = createNode(OP_PRE_INCR);
		$$->left_child = $2;
		}
		| DECR expression
		{
		$$ = createNode(OP_PRE_DECR);
		$$->left_child = $2;
		}
		| expression INCR
		{
		$$ = createNode(OP_POST_INCR);
		$$->left_child = $1;
		}
		| expression DECR
		{
		$$ = createNode(OP_POST_DECR);
		$$->left_child = $1;
		}
		| '(' expression ')'
		{ $$ = $2; }
		| SIZEOF '(' var ')'
		{
			$$ = createNode(OP_SIZEOF);
			$$->left_child = $3;
		}
		| call
		{ $$ = $1; }
		| INUM
		{
		$$ = createNode(INT_LITERAL);
		$$->value.int_value = atoi(yytext);
		}
		| FNUM
		{
		$$ = createNode(DOUBLE_LITERAL);
		$$->value.double_value = atof(yytext);
		}
		| CONTINUE
		{$$ = createNode(CONTINUE_ST);}
		| BREAK
		{$$ = createNode(BREAK_ST);}
		;

/* every child is a function parameter and each of its children is the expression that 
represents the actual parameter; if the function is called with no parameters it 
just gets a blank FUNC_PARAM, because quads expects that (old design)*/
call		: idifier '(' args ')'
		{
			$$ = createNode(FUNC_CALL);
			/*as per quads, we put params first, then id*/
			$$->left_child = createNode(FUNC_PARAM);
			YYSTYPE t = $3;
			YYSTYPE v = $$->left_child;
                 	  if (t != NULL)
                 	  {
			$$->left_child->left_child = t; 
			while (t->right_sibling != NULL)
			{
				YYSTYPE r = t->right_sibling;
				t->right_sibling = NULL;
				v->right_sibling = createNode(FUNC_PARAM);
				v->right_sibling->left_child = r;
                   	     	t = r;
				v=v->right_sibling;
			}
                   	  v->right_sibling = $1; 
		  	 }
			else
				$$->left_child->right_sibling = $1;

		}
		;

/*left recursive argument list will follow, this is the prepper*/
args		: arg_list
		{ $$ = $1; }
		|
		{ $$ = NULL; }
		;

/*each of these args actually needs to be in the format of a function param
so we need to wrap them in there somehow, still thinking*/
arg_list	: arg_list ',' expression
		{ YYSTYPE t = $1;
                   if (t != NULL)
                   { while (t->right_sibling != NULL)
                        t = t->right_sibling;
                     t->right_sibling = $3;
                     $$ = $1; 
		   }
                     else $$ = $3;
                 }
		| expression
		{
		$$ = $1;
		}
		;

%%

/*print out the syntax error and what line it occurred on*/
int yyerror(char * message)
{ printf("Syntax error at line %d: %s\n",lineno,message);
  printf("Current token: %s\n", yytext);
  //printToken(yychar,yytext);
  //Error = TRUE;
  return 0;
}

/*yparse() is called which will continue and call yylex() until
it reaches the end of the file*/
ast_node doParse(void)
{ 
	printf("doparse in cs48.y called\n");
	printf("yyparse returned %d\n\n", yyparse());
	return savedTree;
}

/* Function copyString allocates and makes a new
 * copy of an existing string 
	from Louden
 */
char * copyString(char * s)
{ int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = malloc(n);
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else strcpy(t,s);
  return t;
}

/*create a node of type type with its children set to NULL*/
ast_node createNode(int type)
{
	ast_node new_node = malloc(sizeof(struct ast_node_struct));
	new_node->left_child = new_node->right_sibling = NULL;
	new_node->node_type = type;
}

