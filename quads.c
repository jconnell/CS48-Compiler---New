/* quads.c
* Basic quad fucntions and code generation
* Written by DK and JC for CS 48.
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "quads.h"
#include "ast.h"
#include "Symtab.h"
#include "assemblygen.h"
#include "tokens.h"

#define DOASSEMBLY 1

extern int yylex(void); extern char *yytext;
extern int yyleng;
extern FILE *yyin;			//input file for Flex/Bison
extern FILE *astout;		//ast write out file

/* GLOBAL VARIABLES */

FILE *source;
FILE *listing;


int currentQuad = -1;		/* index into quads */
int tempCount = 0;			/* for unique temp names */

int goffset = 0;			/* global offset for dmem addresses */
int foffset = -4;			/* function offset for dmem addresses */
//must remember in function declaration to change foffset back to -4

Quad **quads;				/* array of Quads */
SymbolTable *symtab;		/* symbol table */

char namesOfOps[][10] = {"rd", "gotoq", "if_f", "asn", "lab", "mul", "divi", "add", "sub", "eq", "wri", "halt", "neq",
	"lt", "gt", "gteq", "lteq", "sym", "ret", "ens", "exs", "loadpar", "jne", "con", "brk"}; 

/* Get the larger of the two - int or double */
int MaxType(Address a, Address b) 
{
/**************************************************************************
 * Name: MaxType
 * Purpose: takes in two addresses, determine's their corresponding data
 *			types and returns the larger of the types (4 or 8 bits)
 * Parameters: a, an address to be examined
 *			   b, an address to be examined
 **************************************************************************/
	
	//printf("Called MaxType\n");
	SymNode *an;
	SymNode *bn;
	if (a.kind == String) 
	{
		//printf("a.kind is string\n");
		an = LookupInSymbolTable(symtab, a.contents.name);
		//printf("looked up a\n");
		typeenum te = GetTypeAttr(an);
		if (te == DouT)
			return 8;
	}
	
	if (b.kind == String) 
	{
		//printf("b.kind is string\n");
		bn = LookupInSymbolTable(symtab, b.contents.name);
		typeenum te = GetTypeAttr(bn);
		if (te == DouT)
			return 8;
	}
	
	/* Set the result to the right type */
	if (a.kind == DouConst || b.kind == DouConst) 
	{
		return 8;
	}
	
	
	//printf("Finished MaxType\n");
	
	return 4;
}

/* Actually creates the quads by recursing;
 * We will return the quad that was the last result or -1 if we have no result
 */
int CG(ast_node n)
{
/**************************************************************************
 * Name: CG
 * Purpose: generates intermediate code (quads) for a single AST node and
 *			returns the last result or -1 if there is no result
 * Parameters: n, the AST node to be examined.
 **************************************************************************/
	
	/* Temporaries we're going to use throughout the CG function, just for
	 *convenience
	 */
	Address ar1, ar2, ar3, ar4, ar5, tqa, ta, topatch, e, nq;
	int lrp, rrp;
	int tq, t, testq, gq;
	int typer;
	SymNode *sn;
	value v;
	
	ast_node next;
	
	ast_node x;
	
	if (n == NULL)
	{
		//printf("Error CG called on NULL node\n");
		
		return -1;
	}
	
	/************************************************************/
	/*** This is our giant switch statement where we check to ***/
	/*** see what type of AST node we are dealing with.		  ***/
	/************************************************************/
	switch (n->node_type) {
		
		/************************/
		/** CONTINUE STATEMENT **/
		/************************/
		case CONTINUE_ST:
			printf("Entering Continue. \n");
			e.kind = Empty;

			GenQuad(con, e, e, e);
			
			break;
		
		/*********************/
		/** BREAK STATEMENT **/
		/*********************/
		case BREAK_ST:
			printf("Entering break. \n");
			e.kind = Empty;
			
			GenQuad(brk, e, e, e);
			
			break;
		
		/**************/
		/** CONSTANT **/
		/**************/
		case CONSTANT:
			printf("Entering constant. \n");
			/* First we get the id */
			lrp = CG(n->left_child);
			/* id */
			ar1 = quads[lrp]->addr1;
			
			sn = LookupInSymbolTable(symtab, ar1.contents.name);
			
			SetFlagsAttr(sn, 1);
			
			break;
		
		/***************************/
		/** SIZE_OF FUNCTIONALITY **/
		/***************************/
		case OP_SIZEOF:
			printf("Entering sizeof. \n");
			/* First we get the id */
			lrp = CG(n->left_child);
			/* id */
			ar1 = quads[lrp]->addr1;
			sn = LookupInSymbolTable(symtab, ar1.contents.name);
			
			t = GetTypeAttr(sn);
			
			switch (t) {
				case IntT:
					tq = 4;
					break;
				case DouT:
					tq = 8;
					break;
				case IArT:
					gq = GetSizeAttr(sn);
					tq = 4*gq;
					break;
				case DArT:
					gq = GetSizeAttr(sn);
					tq = 8*gq;
					break;
				default:
					tq = 8;
					break;
			}
			
			/* Address ar1, ar2, ar3; */
			ar1.kind = String;
			ar1.contents.name = NewTemp(4);
			
			/* We are assigning this literal value to ar1 */
			ar2.kind = IntConst;
			ar2.contents.val = tq;
			
			/* We don't need ar3 */
			ar3.kind = Empty;
			
			return GenQuad(asn, ar1, ar2, ar3);
			
			
			break;
		
		/**********************/
		/** PULL ARRAY VALUE **/
		/**********************/
		case ARRAY_PULL:
			printf("Entering array pull. \n");
			e.kind = Empty;
			
			/* First we get the id, the name */
			lrp = CG(n->left_child);
			
			/* Then we get the left child, right sibling, which is the index of the array */
			rrp = CG(n->left_child->right_sibling);
			
			/* id */
			ar1 = quads[lrp]->addr1;
			
			/* index */
			ar2 = quads[rrp]->addr1;
			
			ar3.kind = String;
			
			
			sn = LookupInSymbolTable(symtab, ar1.contents.name);
			
			/* if int array */
			if (GetTypeAttr(sn) == IArT) typer = 4;
			/* if double array */
			else typer = 8;

			
			t = GetOffsetAttr(sn);
			
			/* We have a constant */
			if (ar2.kind != String) {
				tq = ar2.contents.val;
			}
			/* Temporary must be changed */
			else {
				tq = 4;
			}
			
			if (typer == 4) {
				ar3.contents.name = NewTemp(4);
			}
			else {
				ar3.contents.name = NewTemp(8);
			}

			
			sn = LookupInSymbolTable(symtab, ar3.contents.name);
			
			if (typer == 4) {
				SetTypeAttr(sn, IntT);
				SetOffsetAttr(sn, t-(tq*typer));
			}
			else {
				SetTypeAttr(sn, DouT);
				SetOffsetAttr(sn, t-(tq*typer));
			}
			
			return GenQuad(sym, ar3, e, e);
			
			
			break;
		
			
		/***************************/
		/** INT ARRAY DECLARATION **/
		/***************************/
		case INT_ARRAY_DEC:
			printf("Entering int array dec. \n");
			/* First we get the id, the name */
			lrp = CG(n->left_child);
			
			/* Then we get the left child, right sibling, which is the size of the array */
			rrp = CG(n->left_child->left_child->left_child);
			
			/* id */
			ar1 = quads[lrp]->addr1;
			
			/* size */
			ar2 = quads[rrp]->addr1;
			
			if (ar2.kind == IntConst) 
			{
				t = ar2.contents.val;
			}
			/* otherwise we have a string */
			else 
			{
				sn = LookupInSymbolTable(symtab, ar2.contents.name);
				v = GetValueAttr(sn);
				t = v.ival;
			}

			
			e.kind = Empty;
			
			/* Going to insert into symbol table */
			sn = InsertIntoSymbolTable(symtab, ar1.contents.name);
			SetTypeAttr(sn, IArT);
			SetSizeAttr(sn, t);
			
			if (sn->level == 1) 
			{
				SetOffsetAttr(sn, goffset);
				goffset -= 4*t;
			}
			else {
				SetOffsetAttr(sn, foffset);
				foffset -= 4*t;
			}
			//PLACEHOLDER - Need to set the TYPE ATTRIBUTE in the symbol table to int
			
			break;
		
			
		/******************************/
		/** DOUBLE ARRAY DECLARATION **/
		/******************************/
		case DOU_ARRAY_DEC:
			printf("Entering double array dec. \n");
			/* First we get the id, the name */
			lrp = CG(n->left_child);
			
			/* Then we get the left child, right sibling, which is the size of the array */
			rrp = CG(n->left_child->left_child->left_child);
			
			printf("got size, rrp is %d\n", rrp);
			
			/* id */
			ar1 = quads[lrp]->addr1;
			
			/* size */
			ar2 = quads[rrp]->addr1;
			
			
			printf("got ars\n");
			
			if (ar2.kind == IntConst) 
			{
				t = ar2.contents.val;
			}
			/* Otherwise we have a string */
			else 
			{
				printf("about to lookup\n");
				sn = LookupInSymbolTable(symtab, ar2.contents.name);
				printf("got lookup\n");
				v = GetValueAttr(sn);
				t = v.ival;
			}
			
			printf("got kind\n");
			
			e.kind = Empty;
			
			/* Going to insert into symbol table */
			sn = InsertIntoSymbolTable(symtab, ar1.contents.name);
			SetTypeAttr(sn, DArT);
			SetSizeAttr(sn, t);
			
			if (sn->level == 1) {
				SetOffsetAttr(sn, goffset);
				goffset -= 8*t;
			}
			else {
				SetOffsetAttr(sn, foffset);
				foffset -= 8*t;
			}
			//PLACEHOLDER - Need to set the TYPE ATTRIBUTE in the symbol table to int
			
			break;
			
			
		/**********************/
		/** SWITCH STATEMENT **/
		/**********************/
		case SWITCH_ST:
			printf("Entering switch_st. \n");
			/* This is the id or int we compare against */
			lrp = CG(n->left_child);
			ar1 = quads[lrp]->addr1;
			
			e.kind = Empty;
			
			/* Traverse the cases */
			next = n->left_child->right_sibling;
			while (next->node_type == SWITCH_CASE) 
			{
				/* Get the case */
				rrp = CG(next->left_child);
				ar2 = quads[rrp]->addr1;
				
				/* If the values are not equal, skip this case */
				gq = GenQuad(jne, e, ar2, ar1);
				
				/* Process the sequence */
				CG(next->left_child->right_sibling);
				
				nq.kind = IntConst;
				nq.contents.val = NextQuad();
				PatchQuad(gq, 1, nq);
				
				next=next->right_sibling;
			}
							
			/* Last node should be the default */
			
			CG(next);
			
			break;
			
			
		/**********************/
		/** SWITCH STATEMENT **/
		/**********************/	
		case SWITCH_CASE:
			printf("Entering switch case. \n");
			break;
		
			
		/*************************/
		/** FUNCTION DEFINITION **/
		/*************************/
		/* We have a function with parameters
		 * Based on Louden p 442 */
		case FUNC_DEF:
			printf("Entering func def. \n");
			e.kind = Empty;
			
			/* We must reset f-offset for memory management purposes */
			foffset = -4;
			
			/* This will generate a sym quad which is the start of the function.
			 * It's also a dummy quad for integer defintions.
			 * We're using it like ENT in this case in Louden. */
			lrp = CG(n->left_child);
			
			/* We expect an ID, so add it to the symbol table */
			sn = InsertIntoSymbolTable(symtab, quads[lrp]->addr1.contents.name);
			
			/* This is the quad where we'll need to jump if this function is called */
			v.ival = lrp;
			SetValueAttr(sn, v);
			
			/* We're going to ignore the parameters as per louden p 441 */
			next = n->left_child->right_sibling;
			while (next->node_type == FUNC_PARAM) 
			{
				next=next->right_sibling;
			}
			/* Now we're done so we should be at the SEQ of actual instructions */
			CG(next);
			
			/* Finish it off with a ret */
			GenQuad(ret, e, e, e);
			
			break;
		
			
		/*******************/
		/** FUNCTION CALL **/
		/*******************/
		/* Has id and parameters - we jump to the quad of the id 
		 * Based on Louden p 442 */
		case FUNC_CALL:
			printf("Entering func call. \n");
			e.kind = Empty;
			
			/* Load all the params */
			next = n->left_child;
			while (next->node_type == FUNC_PARAM) 
			{
				/* We're telling the assembler we want it to load parameters for a function call */
				if (next->left_child != NULL) {
					lrp = CG(next);
					GenQuad(loadpar, quads[lrp]->addr1, e, e);
				}
				next=next->right_sibling;
				 
			}
			
			/* The id has in the symbol table a value associated with it
			 * which represents the quad we want to jump to. */
			lrp = CG(next);
			
			/* Get the name of the ID and look up its place */
			sn = LookupInSymbolTable(symtab, quads[lrp]->addr1.contents.name);
			v = GetValueAttr(sn);
			
			t = v.ival;
			
			ar1.kind = IntConst;
			ar1.contents.val = t; 
			
			/* Jump to the location of the id */
			GenQuad(gotoq, ar1, e, e);
			
			break;
			
		
		/************************/
		/** FUNCTION PARAMETER **/
		/************************/
		case FUNC_PARAM:
			printf("Entering func_param. \n");
			if (n->left_child != NULL) return CG(n->left_child);
			break;
		
		/**********************/
		/** RETURN STATEMENT **/
		/**********************/
		case RETURN_S:
			printf("Entering return_s. \n");
			gq = GenQuad(ret, e, e, e);
			
			/* If we have a return after the statement */
			if(n->left_child != NULL)
			{
				lrp = CG(n->left_child);
				PatchQuad(gq, 1, quads[lrp]->addr1);
			}
			
			break;
			
			
		/******************/
		/** EQUALS ( = ) **/
		/******************/
		case OP_EQUALS:
			printf("Entering op_equals. \n");
			ar1.kind = String;
			ar1.contents.name = NewTemp(4);
			
			/* Left result needs to be put in */
			if (n->left_child == NULL) {
				printf("Error child is null\n");
			}
			lrp = CG(n->left_child);
			ar2 = quads[lrp]->addr1;
			
			/* Right child's result needs to be the other operand */
			if (n->left_child->right_sibling == NULL) {
				printf("Error left_child->right sibling is null\n");
			}
			rrp = CG(n->left_child->right_sibling);
			ar3 = quads[rrp]->addr1;
			
			return GenQuad(eq, ar1, ar2, ar3);
			break;
			
			
		/**************/
		/**   ROOT   **/
		/**************/	
		/* ROOT is nothing in itself, so we just start recursing down the tree */
		case ROOT:
			printf("Entering root. \n");
			//printf("In ROOT case\n");
			CG(n->left_child);
			break;
			
			
		/*************************/
		/** NOT EQUAL TO ( != ) **/
		/*************************/
		case OP_NOT_EQUALS:
			printf("Entering not equals. \n");
			ar1.kind = String;
			ar1.contents.name = NewTemp(4);
			
			/* Left result needs to be put in */
			lrp = CG(n->left_child);
			ar2 = quads[lrp]->addr1;
			
			/* Right child's result needs to be the other operand */
			rrp = CG(n->left_child->right_sibling);
			ar3 = quads[rrp]->addr1;
			
			return GenQuad(neq, ar1, ar2, ar3);
			break;
			
			
		/************************/
		/** GREATER THAN ( > ) **/
		/************************/			
		case OP_GREATER_THAN:
			printf("Entering greater than. \n");
			ar1.kind = String;
			ar1.contents.name = NewTemp(4);
			
			/* Left result needs to be put in */
			lrp = CG(n->left_child);
			ar2 = quads[lrp]->addr1;
			
			/* Right child's result needs to be the other operand */
			rrp = CG(n->left_child->right_sibling);
			ar3 = quads[rrp]->addr1;
			
			return GenQuad(gt, ar1, ar2, ar3);
			break;
			
			
		/*********************/
		/** LESS THAN ( < ) **/
		/*********************/
		case OP_LESS_THAN:
			printf("Entering less than. \n");
			ar1.kind = String;
			ar1.contents.name = NewTemp(4);
			
			/* Left result needs to be put in */
			lrp = CG(n->left_child);
			ar2 = quads[lrp]->addr1;
			
			/* Right child's result needs to be the other operand */
			rrp = CG(n->left_child->right_sibling);
			ar3 = quads[rrp]->addr1;
			
			return GenQuad(lt, ar1, ar2, ar3);
			break;
			
		
		/********************************/
		/** GREATER THAN / EQUAL( >= ) **/
		/********************************/
		case OP_GREATER_EQUALS:
			printf("Entering greater than equal. \n");
			ar1.kind = String;
			ar1.contents.name = NewTemp(4);
			
			/* Left result needs to be put in */
			lrp = CG(n->left_child);
			ar2 = quads[lrp]->addr1;
			
			/* Right child's result needs to be the other operand */
			rrp = CG(n->left_child->right_sibling);
			ar3 = quads[rrp]->addr1;
			
			return GenQuad(gteq, ar1, ar2, ar3);
			break;
			
		
		/*******************************/
		/** LESS THAN / EQUALS ( <= ) **/
		/*******************************/
		case OP_LESS_EQUALS:
			printf("Entering less than equals. \n");
			ar1.kind = String;
			ar1.contents.name = NewTemp(4);
			
			/* Left result needs to be put in */
			lrp = CG(n->left_child);
			ar2 = quads[lrp]->addr1;
			
			/* Right child's result needs to be the other operand */
			rrp = CG(n->left_child->right_sibling);
			ar3 = quads[rrp]->addr1;
			
			return GenQuad(lteq, ar1, ar2, ar3);
			break;
			
			
		/*********************/
		/**    OR ( || )    **/
		/*********************/
		case OP_OR:
			printf("Entering or. \n");
			ar1.kind = String;
			ar1.contents.name = NewTemp(4);
			
			ar2.kind = IntConst;
			ar2.contents.val = 1;
			
			ar3.kind = IntConst;
			ar3.contents.val = 0;
			
			ar4.kind = String;
			ar4.contents.name = NewTemp(4);
			
			e.kind = Empty;
			
			lrp = CG(n->left_child);
			ta = quads[lrp]->addr1;
			
			gq = GenQuad(if_f, ta, e, e);
			
			GenQuad(asn, ar4, ar2, e);
			typer = GenQuad(gotoq, e, e, e);
			
			t = CG(n->left_child->right_sibling);
			ar5.kind = IntConst;
			ar5.contents.val = t;
			
			ta = quads[t]->addr1;
			
			testq = GenQuad(if_f, ta, e, e);
			
			GenQuad(asn, ar4, ar2, e);
			
			tq = GenQuad(gotoq, e, e, e);
			
			nq.kind = IntConst;
			nq.contents.val = NextQuad();
			
			PatchQuad(testq, 2, nq);
			
			
			GenQuad(asn, ar4, ar3, e);
			PatchQuad(typer, 1, nq);
			PatchQuad(gq, 2, ar5);
			nq.kind = IntConst;
			nq.contents.val = NextQuad();
			PatchQuad(tq, 1, nq);
			
			rrp = GenQuad(asn, ar1, ar4, e);
			
			
			return rrp;
			
			break;
			
		
		/**********************/
		/**    AND ( && )    **/
		/**********************/
		case OP_AND:
			printf("Entering and. \n");
			ar1.kind = String;
			ar1.contents.name = NewTemp(4);
			
			ar2.kind = IntConst;
			ar2.contents.val = 1;
			
			ar3.kind = IntConst;
			ar3.contents.val = 0;
			
			ar4.kind = String;
			ar4.contents.name = NewTemp(4);
			
			e.kind = Empty;
			
			lrp = CG(n->left_child);
			ta = quads[lrp]->addr1;
			
			gq = GenQuad(if_f, ta, e, e);
			
			t = CG(n->left_child->right_sibling);
			
			ta = quads[t]->addr1;
			
			testq = GenQuad(if_f, ta, e, e);
			
			GenQuad(asn, ar4, ar2, e);
			
			tq = GenQuad(gotoq, e, e, e);
			
			nq.kind = IntConst;
			nq.contents.val = NextQuad();
			PatchQuad(gq, 2, nq);
			PatchQuad(testq, 2, nq);
			
			GenQuad(asn, ar4, ar3, e);
			nq.kind = IntConst;
			nq.contents.val = NextQuad();
			PatchQuad(tq, 1, nq);
			rrp = GenQuad(asn, ar1, ar4, e);
			
			return rrp;
			break;		 
			
			
		/*********************/
		/**    NOT ( ! )    **/
		/*********************/
		case OP_NOT:
			printf("Entering not. \n");
			ar1.kind = String;
			ar1.contents.name = NewTemp(4);
			
			ar2.kind = IntConst;
			ar2.contents.val = 1;
			
			ar3.kind = IntConst;
			ar3.contents.val = 0;
			
			ar4.kind = String;
			ar4.contents.name = NewTemp(4);
			
			e.kind = Empty;
			
			t = CG(n->left_child);
			
			ta = quads[t]->addr1;
			
			/* If false go to the end and give it a 0 */
			gq = GenQuad(if_f, ta, e, e);
			GenQuad(asn, ar4, ar2, e);
			
			tq = GenQuad(gotoq, e, e, e);
			
			nq.kind = IntConst;
			nq.contents.val = NextQuad();
			PatchQuad(gq, 2, nq);
			GenQuad(asn, ar4, ar3, e);
			
			nq.kind = IntConst;
			nq.contents.val = NextQuad();
			
			PatchQuad(tq, 1, nq);
			rrp = GenQuad(asn, ar1, ar4, e);
			
			return rrp;
			break;		 
			
			
		
		/***************/
		/** SEQUENCE  **/
		/***************/
		/* If it's a SEQ, we want to just recursively produce code for all the children */
		case SEQ:
			printf("Entering seq. \n");
			/* Adapted from THC if code */
			e.kind = Empty;
			//EnterScope(symtab);
			/* We must tell the assembly generator we've entered a new scope */
			GenQuad(ens, e, e, e);
			x = n->left_child;
			while (x != NULL) {
				CG(x);
				x = x->right_sibling;
			}
			GenQuad(exs, e, e, e);
			/* We must tell the assembly generator we've exited a scope */
			//LeaveScope(symtab);
			break;
			
			
		/********************/
		/** ADDITION ( + ) **/
		/********************/
		case OP_PLUS:
			printf("Entering plus. \n");
			ar1.kind = String;
			
			/* Left result needs to be put in */
			lrp = CG(n->left_child);
			ar2 = quads[lrp]->addr1;
			
			/* Right child's result needs to be the other operand */
			rrp = CG(n->left_child->right_sibling);
			ar3 = quads[rrp]->addr1;
			
			ar1.contents.name = NewTemp(MaxType(ar2, ar3));
			
			return GenQuad(add, ar1, ar2, ar3);
			break;
		
		
		/***********************/
		/** SUBTRACTION ( - ) **/
		/***********************/
		case OP_MINUS:
			printf("Entering subtraction. \n");
			ar1.kind = String;
			
			/* Left result needs to be put in */
			lrp = CG(n->left_child);
			ar2 = quads[lrp]->addr1;
			
			/* Right child's result needs to be the other operand */
			rrp = CG(n->left_child->right_sibling);
			ar3 = quads[rrp]->addr1;
			
			ar1.contents.name = NewTemp(MaxType(ar2, ar3));
			
			return GenQuad(sub, ar1, ar2, ar3);
			break;
		
			
		/**************************/
		/** MULTIPLICATION ( * ) **/
		/**************************/
		case OP_TIMES:
			printf("Entering multiplication. \n");
			ar1.kind = String;
			
			/* Left result needs to be put in */
			lrp = CG(n->left_child);
			ar2 = quads[lrp]->addr1;
			
			/* Right child's result needs to be the other operand */
			rrp = CG(n->left_child->right_sibling);
			ar3 = quads[rrp]->addr1;
			
			ar1.contents.name = NewTemp(MaxType(ar2, ar3));
			
			return GenQuad(mul, ar1, ar2, ar3);
			break;
		
			
		/********************/
		/** DIVISION ( / ) **/
		/********************/
		case OP_DIVIDE:
			printf("Entering divide. \n");
			ar1.kind = String;
			
			/* Left result needs to be put in */
			lrp = CG(n->left_child);
			ar2 = quads[lrp]->addr1;
			
			/* Right child's result needs to be the other operand */
			rrp = CG(n->left_child->right_sibling);
			ar3 = quads[rrp]->addr1;
			
			ar1.contents.name = NewTemp(MaxType(ar2, ar3));
			
			return GenQuad(divi, ar1, ar2, ar3);
			break;
			
			
		/*********************/
		/** NEGATION ( -a ) **/
		/*********************/
		/** THIS IS NOT SUBTRACTION **/
		case OP_NEGATIVE:
			printf("Entering negation. \n");
			ar1.kind = String;
			
			/* This should only have one child */
			lrp = CG(n->left_child);
			ar2 = quads[lrp]->addr1;
			
			/* We need to subtract from 0 */
			ar3.kind = IntConst;
			ar3.contents.val = 0;
			
			ar1.contents.name = NewTemp(MaxType(ar2, ar3));
			
			return GenQuad(sub, ar1, ar3, ar2);
			break;
			
			
		/*****************/
		/** INT LITERAL **/
		/*****************/
		case INT_LITERAL:
			printf("Entering int lit. \n");
			ar1.kind = String;
			ar1.contents.name = NewTemp(4);
			
			/* We are assigning this literal value to ar1 */
			ar2.kind = IntConst;
			ar2.contents.val = n->value.int_value;
			
			/* We don't need ar3 */
			ar3.kind = Empty;
			
			return GenQuad(asn, ar1, ar2, ar3);
			break;
			
		
		/********************/
		/** DOUBLE LITERAL **/
		/********************/
		case DOUBLE_LITERAL:
			printf("Entering double lit. \n");
			ar1.kind = String;
			ar1.contents.name = NewTemp(8);
			
			/* We are assigning this literal value to ar1 */
			ar2.kind = DouConst;
			ar2.contents.dval = n->value.double_value;
			
			/* We don't need ar3 */
			ar3.kind = Empty;
			
			return GenQuad(asn, ar1, ar2, ar3);
			break;
		
		/********************/
		/** STRING LITERAL **/
		/********************/	
		case STRING_LITERAL:
			printf("Entering string lit. \n");
			ar1.kind = String;
			ar1.contents.name = NewTemp(240);
			
			/* We are assigning this literal value to ar1 */
			ar2.kind = String;
			ar2.contents.name = n->value.string;
			
			/* We don't need ar3 */
			ar3.kind = Empty;
			
			return GenQuad(asn, ar1, ar2, ar3);
			break;
			
			
		/*********************/
		/** INT DECLARATION **/
		/*********************/
		case INT_DEC:
			printf("Entering int dec. \n");
			lrp = CG(n->left_child);
			ar1 = quads[lrp]->addr1;
			
			ar2.kind = Empty;
			
			ar3.kind = Empty;
			
			/* Going to insert into symbol table */
			sn = InsertIntoSymbolTable(symtab, ar1.contents.name);
			SetTypeAttr(sn, IntT);
			
			if (sn->level == 1) {
				SetOffsetAttr(sn, goffset);
				goffset -= 4;
			}
			else {
				SetOffsetAttr(sn, foffset);
				foffset -= 4;
			}
			//PLACEHOLDER - Need to set the TYPE ATTRIBUTE in the symbol table to int
			
			/*if there is a child of the id, assign that child to it
			 since that means it was declared with an =*/
			if (n->left_child->left_child != NULL) {
				rrp = CG(n->left_child->left_child);
				tqa = quads[rrp]->addr1;
				
				e.kind = Empty;

				GenQuad(asn, ar1, tqa, e);
			}
			
			break;
			
			
		/************************/
		/** DOUBLE DECLARATION **/
		/************************/
		case DOU_DEC:
			printf("Entering double dec. \n");
			lrp = CG(n->left_child);
			ar1 = quads[lrp]->addr1;
			
			ar2.kind = Empty;
			
			ar3.kind = Empty;
		
			/* Going to insert into symbol table */
			sn = InsertIntoSymbolTable(symtab, ar1.contents.name);
			SetTypeAttr(sn, DouT);
			
			if (sn->level == 1) {
				SetOffsetAttr(sn, goffset);
				goffset -= 8;
			}
			else {
				SetOffsetAttr(sn, foffset);
				foffset -= 8;
			}
			//PLACEHOLDER - Need to set the TYPE ATTRIBUTE in the symbol table to double
			
			/*if there is a child of the id, assign that child to it
			 since that means it was declared with an =*/
			if (n->left_child->left_child != NULL) {
				rrp = CG(n->left_child->left_child);
				tqa = quads[rrp]->addr1;
				
				e.kind = Empty;
				
				GenQuad(asn, ar1, tqa, e);
			}
			
			break;
		
			
		/**************/
		/** FOR LOOP **/
		/**************/
		case FOR_LOOP:
			printf("Entering for loop. \n");
			/* The first statement is always executed */
			CG(n->left_child);
			
			/* The inequality is statement two */
			t = CG(n->left_child->right_sibling);
			ta = quads[t]->addr1;
			testq = GenQuad(if_f, ta, topatch, e);
			
			/* We do the sequence before the final statement */
			CG(n->left_child->right_sibling->right_sibling->right_sibling);
			
			/* Now we do the third statement in the for-loop header */
			CG(n->left_child->right_sibling->right_sibling);
			
			/* Then we loop around */
			e.kind = Empty;
			
			nq.kind = IntConst;
			nq.contents.val = t;
			GenQuad(gotoq, nq, e, e);
			
			/* Finally we must patch the inequality	*/	
			nq.kind = IntConst;
			nq.contents.val = NextQuad();
			PatchQuad(testq, 2, nq);
			
			break;
			
		
		/**********************/
		/** PRE-INCR ( ++x ) **/
		/**********************/
		case OP_PRE_INCR:
			printf("Entering pre inc. \n");
			/* Left result needs to be put in */
			lrp = CG(n->left_child);
			ar2 = quads[lrp]->addr1;
			
			/* Right child's result needs to be the other operand */
			ar3.kind = IntConst;
			ar3.contents.val = 1;
			
			return GenQuad(add, ar2, ar2, ar3);
			break;
		
			
		/***********************/
		/** POST-INCR ( x++ ) **/
		/***********************/
		case OP_POST_INCR:
			printf("Entering post inc. \n");
			/* Left result needs to be put in */
			lrp = CG(n->left_child);
			ar2 = quads[lrp]->addr1;
			
			/* Right child's result needs to be the other operand */
			ar3.kind = IntConst;
			ar3.contents.val = 1;
			
			return GenQuad(add, ar2, ar2, ar3);
			break;
		
			
		/**********************/
		/** PRE-DECR ( --x ) **/
		/**********************/
		case OP_PRE_DECR:
			printf("Entering pre dec. \n");
			/* Left result needs to be put in */
			lrp = CG(n->left_child);
			ar2 = quads[lrp]->addr1;
			
			/* Right child's result needs to be the other operand */
			ar3.kind = IntConst;
			ar3.contents.val = 1;
			
			return GenQuad(sub, ar2, ar2, ar3);
			break;
			
			
		/***********************/
		/** POST-DECR ( x-- ) **/
		/***********************/
		case OP_POST_DECR:
			printf("Entering post dec. \n");
			/* Left result needs to be put in */
			lrp = CG(n->left_child);
			ar2 = quads[lrp]->addr1;
			
			/* Right child's result needs to be the other operand */
			ar3.kind = IntConst;
			ar3.contents.val = 1;
			
			return GenQuad(sub, ar2, ar2, ar3);
			break;
			
		
		/******************/
		/** IF/ELSE STMT **/
		/******************/
		case IF_ELSE:
			printf("Entering if else. \n");
			t = CG(n->left_child);
			
			ta = quads[t]->addr1;
			
			topatch.kind = Empty;
			
			e.kind = Empty;
			
			testq = GenQuad(if_f, ta, topatch, e);
			
			CG(n->left_child->right_sibling);
			gq = GenQuad(gotoq, e, e, e);
			
			nq.kind = IntConst;
			nq.contents.val = NextQuad();
			PatchQuad(testq, 2, nq);
			
			CG(n->left_child->right_sibling->right_sibling);
			
			nq.kind = IntConst;
			nq.contents.val = NextQuad();
			PatchQuad(gq, 1, nq);
			
			break;
		
			
		/***************/
		/**  IF STMT  **/
		/***************/
		case IF_S:
			printf("Entering if_s. \n");
			t = CG(n->left_child);
			ta = quads[t]->addr1;
			
			topatch.kind = Empty;
			e.kind = Empty;
			
			/* This is where we would switch the order for the do-while */
			testq = GenQuad(if_f, ta, topatch, e);
			
			CG(n->left_child->right_sibling);
			
			nq.kind = IntConst;
			nq.contents.val = NextQuad();
			
			PatchQuad(testq, 2, nq);
			
			break;
			
		
		/****************/
		/** WHILE LOOP **/
		/****************/
		/* Adapted from THC's code in class */
		/* MUST TYPE CHECK THAT t RETURNS AN INT FOR COMPARISON */
		case WHILE_LOOP:
			printf("Entering while loop. \n");
			tq = NextQuad();
			t = CG(n->left_child);
			
			tqa.kind = IntConst;
			tqa.contents.val = tq;
			
			ta = quads[t]->addr1;
			
			topatch.kind = Empty;
			
			e.kind = Empty;
			
			/* This is where we would switch the order for the do-while */
			testq = GenQuad(if_f, ta, topatch, e);
			
			CG(n->left_child->right_sibling);
			
			GenQuad(gotoq, tqa, e, e);
			
			nq.kind = IntConst;
			nq.contents.val = NextQuad();
			PatchQuad(testq, 2, nq);
			break;
			
		/*******************/
		/** DO WHILE LOOP **/
		/*******************/	
		/* We're still assuming the comparison is the left child
		 * not the left child->right sibling */
		case DO_WHILE_LOOP:
			printf("Entering do while. \n");
			tq = NextQuad();
			t = CG(n->left_child);
			
			/* Just do the other stuff first and then we potentially loop or leave */
			CG(n->left_child->right_sibling);
			
			tqa.kind = IntConst;
			tqa.contents.val = tq;
			
			ta = quads[t]->addr1;
			
			topatch.kind = Empty;
			
			e.kind = Empty;
			
			/* This is where we would switch the order for the dowhile */
			testq = GenQuad(if_f, ta, topatch, e);
			
			GenQuad(gotoq, tqa, e, e);
			
			nq.kind = IntConst;
			nq.contents.val = NextQuad();
			PatchQuad(testq, 2, nq);
			break;
		
			
		/****************/
		/**    READ    **/
		/****************/
		/* The assembler has a built in read facility, so this is very simple */
		/* NEED TO DEAL WITH DOUBLES HERE TOO BASED ON TYPE CHECK of CHILD's ATTRIBUTE */
		case READ_S:
			printf("Entering read. \n");
			lrp = CG(n->left_child);
			
			ar1 = quads[lrp]->addr1;
			
			ar2.kind = Empty;
			
			ar3.kind = Empty;
			
			gq = GenQuad(rd, ar1, ar2, ar3);
			
			/* PUT VALUE IN SYMBOL TABLE UNDER READ's CHILD */
			
			return gq;
			
			break;
		
			
		/*****************/
		/**    WRITE    **/
		/*****************/
		/* The assembler has a built in write facility, so this is very simple */
		/* NEED TO HANDLE DOUBLES HERE TOO BASED ON TYPE CHECK of CHILD's TYPE ATTRIBUTE */
		case WRITE_S:
			printf("Entering write. \n");
			//printf("WRITE Case in CG\n");
			lrp = CG(n->left_child);
			ar1 = quads[lrp]->addr1;
			
			ar2.kind = Empty;
			
			ar3.kind = Empty;
			
			GenQuad(wri, ar1, ar2, ar3);
			/* We put in a dummy just so that higher ups can use it, also put in symbol table */
			
			break;
			
			
		/**************/
		/**    ID    **/
		/**************/
		case IDENTIFIER:
			printf("Entering ID. \n");
			ar1.contents.name = strdup(n->value.string);
			
			ar1.kind = String;
			
			ar2.kind = Empty;
			
			ar3.kind = Empty;
			
			return GenQuad(sym, ar1, ar2, ar3);
			/* We put in a dummy just so that higher ups can use it, also put in symbol table */
			
			break;
			
			
		/****************/
		/** ASSIGNMENT **/
		/****************/
		case OP_ASSIGN:
			printf("Entering assign. \n");
			/* Left result needs to be put in */
			lrp = CG(n->left_child);
			ar1 = quads[lrp]->addr1;
			
			/* Right child's result needs to be the other operand */
			rrp = CG(n->left_child->right_sibling);
			ar2 = quads[rrp]->addr1;
			
			ar3.kind = Empty;
			
			return GenQuad(asn, ar1, ar2, ar3);
			break;
			
			//MISSING CONST, RETURN, SWITCH, BREAK, CONTINUE
			//RETURN NEEDS TO GO TOGETHER WITH FUNCTIONS I THINK...  MAYBE WE NEED TO TYPE CHECK WITH ANOTHER
			//SWITCH WITHIN THE CASE OF A FUNCTION CALL
		
		default:
			break;
	}
	
	/* Default, we return -1 which means no result from the previous call... */
	return -1;
}


int GenQuad(OpKind o, Address a, Address b, Address c)
{
/**************************************************************************
 * Name: GenQuad
 * Purpose: generates a quad using the information in the parameters,  
 *			appends the quad to the overall array of quads, and returns
 *			the current index of the quad array
 * Parameters: o, the type of operation
 *			   a, the first address to be put into the quad
 *			   b, the second address to be put into the quad
 *			   c, the third address to be put into the quad
 * The quad will be of the form (o, a, b, c).
 **************************************************************************/
	
	/* Make the quad */
	Quad *q = malloc(sizeof(Quad));
	q->op = o;
	q->addr1 = a;
	q->addr2 = b;
	q->addr3 = c;
	
	/* currentQuad points to the current index into the array of the 
	 * last added quad */
	currentQuad++;
	
	/* Add it to the array */
	quads[currentQuad] = q;
	
	
	/* DEBUG */
	char* a1 = malloc(sizeof(char) * 100);
	char* a2 = malloc(sizeof(char) * 100);
	char* a3 = malloc(sizeof(char) * 100);
	switch (q->addr1.kind) 
	{
		case Empty:
			a1 = " - ";
			break;
		case IntConst:
			sprintf(a1,"%d",q->addr1.contents.val);
			break;
		case DouConst:
			sprintf(a1,"%f",q->addr1.contents.dval);
			break;
		case String:
			a1 = q->addr1.contents.name;
			break;
		default:
			break;
	}
	
	switch (q->addr2.kind) 
	{
		case Empty:
			a2 = " - ";
			break;
		case IntConst:
			sprintf(a2,"%d",q->addr2.contents.val);
			break;
		case DouConst:
			sprintf(a2,"%f",q->addr2.contents.dval);
			break;
		case String:
			a2 = q->addr2.contents.name;
			break;
		default:
			break;
	}
	
	switch (q->addr3.kind) 
	{
		case Empty:
			a3 = " - ";
			break;
		case IntConst:
			sprintf(a3,"%d",q->addr3.contents.val);
			break;
		case DouConst:
			sprintf(a3,"%f",q->addr3.contents.dval);
			break;
		case String:
			a3 = q->addr3.contents.name;
			break;
		default:
			break;
	}
	
	//printf("Finished switches, printing quad details\n");
	//printf("%s",a1);
	//printf("%s",a2);
	//printf("%s",a3);
	//printf("(%s,%s,%s,%s)\n",namesOfOps[q->op],a1,a2,a3);
	
	/* END DEBUG */
	
	return currentQuad;
}


void PatchQuad(int q, int l, Address n)
{
/**************************************************************************
 * Name: PatchQuad
 * Purpose: changes a value in a quad that has already been generated to an
 *			updated value that wasn't known previously
 * Parameters: q, the index of the quad being looked at
 *			   l, the location within the quad that is being changed. (1,2,3)
 *			   n, the new address that is being added to the quad
 **************************************************************************/
	Quad *theQuad = quads[q];
	switch (l) {
		case 1:
			theQuad->addr1 = n;
			break;
		case 2:
			theQuad->addr2 = n;
			break;
		case 3:
			theQuad->addr3 = n;
			break;
		default:
			break;
	}
}


int NextQuad()
{
/**************************************************************************
 * Name: NextQuad
 * Purpose: returns the next quad after the last added one
 * Parameters: none
 **************************************************************************/
	
	return currentQuad+1;
}


char *NewTemp(int siz)
{
/**************************************************************************
 * Name: NewTemp
 * Purpose: creates a new temporary variable and adds it to the symbol table
 * Parameters: siz, the size of the temp to be created
 **************************************************************************/
	
	char *tempName;
	tempName = malloc(sizeof(char) * 7);
	sprintf(tempName, "$t%d", tempCount);  
	
	/* Inserting into symbol table */
	SymNode *thesn = InsertIntoSymbolTable(symtab, tempName);
	
	if (thesn->level == 1) {
		SetOffsetAttr(thesn, goffset-siz);
		goffset -= siz;
	}
	else {
		SetOffsetAttr(thesn, foffset-siz);
		foffset -= siz;
	}
	
	if (siz == 8) {
		SetTypeAttr(thesn, DouT);
	}
	else if (siz == 240)
	{
		SetTypeAttr(thesn, StrT);
	}
	else {
		SetTypeAttr(thesn, IntT);
	}
	
	
	tempCount++;			/* So next one has unique name */
	
	return tempName;
}

/* Main function - call with the name of the AST input file */
int main(int argc, char **argv) 
{
	/* Generate the array of quads (okay we have a limit of 10,000 - 
	 * we really don't think people in C48 will get beyond this using 
	 * our compiler - consider it a "compiler limit" */
	quads = calloc(10000, sizeof(Quad *));
	
	int n;
	
	/* We need an input file */
	if (argc < 2) {
		printf("Not enough input arguments.\n");
		return 1;
	}
	
	/* We're just reading it */
    source = fopen(argv[1], "r");
	/* Set yyin */
	yyin = source;
	
	listing = fopen("lexxer.out","w");
	
	
	ast_node root;
	
	printf("Building AST\n");
	
	//root = build_ast(argv[1]); /* Build an abstract syntax tree */
	root = doParse();
	
	printf("Printing AST\n");
	
	//file to write out the AST to
	astout = fopen("ast.out", "w");
	
	print_ast(root, 0);		      /* Print it out */
	
	fclose(astout);
	
	printf("finished parsing\n");
	
	if (root == NULL) {
		printf("root is NULL\n");
	}
	
	fclose(listing);
    fclose(source);
	
	printf("Creating Symbol Table\n");
	
	/* OUR CODE AGAIN */
	/* Create symbol table */
	symtab = CreateSymbolTable();
	/* Now we call CG of the root node */
	
	InsertIntoSymbolTable(symtab, "dog");
	
	printf("Calling CG on root node\n");
	
	CG(root);
	
	/* Print all of our quads for debug purposes */
	int i = 0;
	//char a1[5];
	//char a2[5];
	//char a3[5];
	
	printf("Entering Debug Printing While Loop - we have %d quads and they are:\n", currentQuad);
	
	FILE *qfile;
	qfile = fopen("quadsout.txt","w");
	
	while(quads[i] != NULL)
	{
		char* a1 = malloc(sizeof(char) * 15);
		char* a2 = malloc(sizeof(char) * 15);
		char* a3 = malloc(sizeof(char) * 15);
		printf("Printing quad %d", i);
		
		switch (quads[i]->addr1.kind) 
		{
			case Empty:
				a1 = " - ";
				break;
			case IntConst:
				sprintf(a1,"%d",quads[i]->addr1.contents.val);
				break;
			case DouConst:
				sprintf(a1,"%f",quads[i]->addr1.contents.dval);
				break;
			case String:
				//printf("%s", quads[i]->addr1.contents.name);
				a1 = quads[i]->addr1.contents.name;
				//printf("%s", a1);
				break;
			default:
				break;
		}
		
		switch (quads[i]->addr2.kind) 
		{
			case Empty:
				a2 = " - ";
				break;
			case IntConst:
				sprintf(a2,"%d",quads[i]->addr2.contents.val);
				break;
			case DouConst:
				sprintf(a2,"%f",quads[i]->addr2.contents.dval);
				break;
			case String:
				//printf("%s", quads[i]->addr2.contents.name);
				a2 = quads[i]->addr2.contents.name;
				break;
			default:
				break;
		}
		
		switch (quads[i]->addr3.kind) 
		{
			case Empty:
				a3 = " - ";
				break;
			case IntConst:
				sprintf(a3,"%d",quads[i]->addr3.contents.val);
				break;
			case DouConst:
				sprintf(a3,"%f",quads[i]->addr3.contents.dval);
				break;
			case String:
				//printf("%s", quads[i]->addr3.contents.name);
				a3 = quads[i]->addr3.contents.name;
				break;
			default:
				break;
		}
		
		//printf("Finished switches, printing quad details\n");
		//printf("%s",a1);
		//printf("%s",a2);
		//printf("%s",a3);
		printf("(%s,%s,%s,%s)\n",namesOfOps[quads[i]->op],a1,a2,a3);
		fprintf(qfile, "(%s,%s,%s,%s)\n",namesOfOps[quads[i]->op],a1,a2,a3);
		i++;
	}
	fclose(qfile);
	
	/*
	EnterScope(symtab);
	EnterScope(symtab);
	char *c = malloc(sizeof(char) *5);
	c = "a";
	printf("before segfault?\n");
	SymNode *sn = LookupInSymbolTable(symtab, c);
	printf("%d the offset of a is\n", GetOffsetAttr(sn));
	*/
	
	if(DOASSEMBLY)
	{
		/* File for final assembly output */
		FILE *file;
		file = fopen("tm48code.txt","w");
		
		/* Send over to the assembly generator, the quads array and symbol table */
		AssemblyGen(quads, file, symtab);
		
		
		fclose(file);
	}
	
	return 0;
}