/*
 *  File: assemblygen.c
 *	Purpose: To create proper assembly code from quads
 *			 
 *	CS 48
 *	Jonathan Connell & David Kopec
 */

#include "assemblygen.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "quads.h"
#include "ast.h"
#include "Symtab.h"


/* GLOBAL VARIABLES */
Quad **quads;				/* Array of Quads */
SymbolTable *symtab;		/* Symbol Table	  */


void AssemblyGen(Quad** q, FILE* file, SymbolTable* s) {
/**************************************************************************
 * Name: AssemblyGen
 * Purpose: iterates through each quad, generates the corresponding
 *			assembly code, and outputs the assembly code to a file.
 * Parameters: q, the array of quads
 *			   file, the file to which the assembly code will be wrriten to
 *			   s, the symbol table for our program
 **************************************************************************/
	
	quads = q;
	symtab = s;
	
	/* Here, we keep an array called quadStartLocations that keeps track 
	 * of each quad number and its corresponding assembly code line
	 * number. This makes it easier to quickly to do detect what line we
	 * may need to jump to. 
	 */
	int i = 0;			// Quad number
	int AssemNum = 0;	// Assembly code line number
	int quadStartLocations[10000];
	
	int curScope = 0;
	/* For each quad, we represent it with the form
	 * (op, a1, a2, a3)
	 */
	OpKind op = quads[i]->op;
	Address a1 = quads[i]->addr1;
	Address a2 = quads[i]->addr2;
	Address a3 = quads[i]->addr3;
	
	/* Symbol Table nodes for a1, a2, and a3 respectively */
	SymNode *s1;
	SymNode *s2;
	SymNode *s3;
	
	/* Loop through each quad, generating assembly code as necessary */
	while (quads[i] != NULL) {
		a1 = quads[i]->addr1;
		a2 = quads[i]->addr2;
		a3 = quads[i]->addr3;
		
		quadStartLocations[i] = AssemNum; /* Keeping track of which assembly code line
										   * numbers correspond to which quad numbers.
										   */
		
		
		/* TYPE DETECTION
		 *
		 * All variables are stored in quads as a string beginning with a '$',
		 * so we have see if each value is of type String. If it is then we know
		 * that it is a variable.
		 * Otherwise, it is either an Int constant or Double constant.
		 *
		 * This is checked for all 3 quad variables below.
		 */
		
		char type_to_store = 'i';		/* Type of variable to be stored to (default: int) */
		char type_of_storage = 'i';		/* Type of variable to be stored (default: int) */
		
		/* TYPE DETECTION OF THE FIRST QUAD VARIABLE */
		if (a1.kind == String){
			s1 = LookupInSymbolTable(symtab, a1.contents.name);
			printf(" %s", a1.contents.name);
			if (s1->attrs->type == DouT)
				type_of_storage = 'd';
		}
		else if (a1.kind == IntConst) {
			printf(" %d", a1.contents.val);
		}
		else if (a1.kind == DouConst) {
			printf(" %f", a1.contents.dval);
			type_of_storage = 'd';
		}
		else printf(" - ");
		
		/* TYPE DETECTION OF THE SECOND QUAD VARIABLE */
		if (a2.kind == String){
			s2 = LookupInSymbolTable(symtab, a2.contents.name);
			printf(" %s", a2.contents.name);
		}
		else if (a2.kind == IntConst) {
			printf(" %d", a2.contents.val);
		}
		else if (a2.kind == DouConst) {
			printf(" %f", a2.contents.dval);
		}
		else printf(" - ");
		
		/* TYPE DETECTION OF THE THIRD QUAD VARIABLE */
		if (a3.kind == String){
			s3 = LookupInSymbolTable(symtab, a3.contents.name);
			printf(" %s\n", a3.contents.name);
		}
		else if (a3.kind == IntConst) {
			printf(" %d\n", a3.contents.val);
		}
		else if (a3.kind == DouConst) {
			printf(" %f\n", a3.contents.dval);
		}
		else printf(" - \n");
		
		AssemKind AK;
		char* AssemCommand = " ";
		
		
		
		/****************************************************/
		/****************** TM48 COMMANDS *******************/
		/****************************************************/
		
		if (quads[i]->op == add) {				/* Addition (+) */
			AK = math;		 AssemCommand = "ADD";
		}
		else if (quads[i]->op == sub) {			/* Subtraction (-) */
			AK = math;		 AssemCommand = "SUB";
		}
		else if (quads[i]->op == mul) {			/* Multiplication (*) */
			AK = math;		 AssemCommand = "MUL";
		}
		else if (quads[i]->op == divi) {		/* Division (/) */
			AK = math;		 AssemCommand = "DIV";
		}
		else if (quads[i]->op == gt) {			/* Greater Than (>) */
			AK = inequality; AssemCommand = "GT";
		}
		else if (quads[i]->op == gteq) {		/* Greater Than or Equal (>=) */
			AK = inequality; AssemCommand = "GE";
		}
		else if (quads[i]->op == lt) {			/* Less Than (<) */
			AK = inequality; AssemCommand = "LT";
		}
		else if (quads[i]->op == lteq) {		/* Less Than or Equal (<=) */
			AK = inequality; AssemCommand = "LE";
		}
		else if (quads[i]->op == eq) {			/* Equals (=) */
			AK = inequality; AssemCommand = "EQ";
		}
		else if (quads[i]->op == neq) {			/* Not Equal To (!=) */
			AK = inequality; AssemCommand = "NE";
		}
		else if (quads[i]->op == asn) {			/* Store value */
			AK = assignment; AssemCommand = "ST";
		}
		else if (quads[i]->op == rd) {			/* Read from STD IN */
			AK = read;		 AssemCommand = "IN";
		}
		else if (quads[i]->op == wri) {			/* Write to STD OUT */
			AK = write;		 AssemCommand = "OUT";
		}
		else if (quads[i]->op == if_f) {		/* If False, Jump */
			AK = iffalse;	 AssemCommand = " ";
		}
		else if (quads[i]->op == gotoq) {		/* Go to Quad */
			AK = jumptoquad; AssemCommand = "LDA";
		}
		else if (quads[i]->op == loadpar) {		/* Load a Function's Parameter */
			AK = loadparam;  AssemCommand = "LD";
		}
		else if (quads[i]->op == con) {			/* Continue Statement */
			AK = cont;		 AssemCommand = "CONT";
		}
		else if (quads[i]->op == exs) {			/* Exit Scope */
			AK = exitScope;  AssemCommand = " ";
		}
		else if (quads[i]->op == ens) {			/* Enter Scope */
			AK = enterScope; AssemCommand = " ";
		}
		else if (quads[i]->op == ret) {			/* Return */
			AK = retu; AssemCommand = "LDA";
		}
		else {
			AK = other; AssemCommand = "ERROR";
		}
	
		/****************************************************/
		/***************** CODE GENERATION ******************/
		/****************************************************/
		
		/** Initialize registers **/
		if (i == 0) {
			fprintf(file, "%d: LD 6, 0(0)\n", AssemNum++);
			fprintf(file, "%d: LDF 6, 0(0)\n", AssemNum++);
			fprintf(file, "%d: ST 0, 0(0)\n", AssemNum++);
			fprintf(file, "%d: STF 0, 0(0)\n", AssemNum++);
		}
		switch (AK) {
				
			/*** MATH OPERATORS ***/
			case (math): 
				if (a2.kind == String) {	
					printf("%d\n", s2->attrs->type);
					if (s2->attrs->type == IntT) {		
						fprintf(file, "%d: LD 0, %d(5)\n", AssemNum++, -s2->attrs->memoffset);
						if (a3.kind == String) {
							if (s3->attrs->type == IntT) {
								/* Operation between Int var and Int var */
								fprintf(file, "%d: LD 1, %d(5)\n", AssemNum++, -s3->attrs->memoffset); 
								fprintf(file, "%d: %s 0, 1, 0\n", AssemNum++, AssemCommand);
							}
							else if (s3->attrs->type == DouT) {
								/* Operation between Int var and Double var */
								type_to_store = 'd';
								fprintf(file, "%d: CVTIF 0, 0, 0\n", AssemNum++);
								if (s3->attrs->memoffset % 8 == 0)
									fprintf(file, "%d: LDF 1, %d(5)\n", AssemNum++, -s3->attrs->memoffset); 
								else 
									fprintf(file, "%d: LDF 1, %d(5)\n", AssemNum++, -s3->attrs->memoffset + 4);
								fprintf(file, "%d: %sF 0, 1, 0\n", AssemNum++, AssemCommand);
							}
							else {
								fprintf(file, "ERROR - Math\n");
							}
						}
						else if (a3.kind == IntConst) {
							/* Operation between Int var and Int constant */
							fprintf(file, "%d: LDC 1, %d(0)\n", AssemNum++, a3.contents.val);
							fprintf(file, "%d: %s 0, 1, 0\n", AssemNum++, AssemCommand);
						}
						else if (a3.kind == DouConst) {
							/* Operation between Int var and Double constant */
							type_to_store = 'd';
							fprintf(file, "%d: CVTIF 0, 0, 0\n", AssemNum++);
							fprintf(file, "%d: LDFC 1, %f(0)\n", AssemNum++, a3.contents.dval); 
							fprintf(file, "%d: %sF 0, 1, 0\n", AssemNum++, AssemCommand);
						}
						else {
							fprintf(file, "ERROR - Math\n");
						}
					}
					else if (s2->attrs->type == DouT) {
						type_to_store = 'd';
						if (s2->attrs->memoffset % 8 == 0) 
							fprintf(file, "%d: LDF 0, %d(5)\n", AssemNum++, -s2->attrs->memoffset);
						else 
							fprintf(file, "%d: LDF 0, %d(5)\n", AssemNum++, -s2->attrs->memoffset + 4);
						//fprintf(file, "%d: LDF 0, %d(5)\n", AssemNum++, -s2->attrs->memoffset);
						if (a3.kind == String) {
							if (s3->attrs->type == IntT) {
								/* Operation between Double var and Int var */
								fprintf(file, "%d: LD 1, %d(5)\n", AssemNum++, -s3->attrs->memoffset);
								fprintf(file, "%d: CVTIF 1, 1, 1\n", AssemNum++);
								fprintf(file, "%d: %sF 0, 1, 0\n", AssemNum++, AssemCommand);
							}
							else if (s3->attrs->type == DouT) {
								/* Operation between Double var and Double var */
								if (s3->attrs->memoffset % 8 == 0)
									fprintf(file, "%d: LDF 1, %d(5)\n", AssemNum++, -s3->attrs->memoffset);
								else
									fprintf(file, "%d: LDF 1, %d(5)\n", AssemNum++, -s3->attrs->memoffset);
								fprintf(file, "%d: %sF 0, 1, 0\n", AssemNum++, AssemCommand);
							}
							else {
								fprintf(file, "ERROR - Math\n");
							}
						}
						else if (a3.kind == IntConst) {
							/* Operation between Double var and Int constant */
							fprintf(file, "%d: LDC 1, %d(0)\n", AssemNum++, a3.contents.val);
							fprintf(file, "%d: CVTIF 1, 1, 1\n", AssemNum++);
							fprintf(file, "%d: %sF 0, 1, 0\n", AssemNum++, AssemCommand);
						}
						else if (a3.kind == DouConst) {
							/* Operation between Double var and Double constant */
							fprintf(file, "%d: LDFC 1, %f(0)\n", AssemNum++, a3.contents.dval);
							fprintf(file, "%d: %sF 0, 1, 0\n", AssemNum++, AssemCommand);
						}
						else {
							fprintf(file, "ERROR - Math\n");
						}
					}
					else {
						fprintf(file, "ERROR - Math\n");
					}
				}
				else if (a2.kind == IntConst) {
					fprintf(file, "%d: LDC 0, %d(0)\n", AssemNum++, a2.contents.val);
					if (a3.kind == String) {
						if (s3->attrs->type == IntT) {
							/* Operation between Int constant and Int var */
							fprintf(file, "%d: LD 1, %d(5)\n", AssemNum++, -s3->attrs->memoffset);
							fprintf(file, "%d: %s 0, 1, 0\n", AssemNum++, AssemCommand);
						}
						else if (s3->attrs->type == DouT) {
							/* Operation between Int constant and Double var */
							type_to_store = 'd';
							fprintf(file, "%d: CVTIF 0, 0, 0\n", AssemNum++);
							fprintf(file, "%d: LDF 1, %d(5)\n", AssemNum++, -s3->attrs->memoffset);
							fprintf(file, "%d: %sF 0, 1, 0\n", AssemNum++, AssemCommand);
						}
						else {
							fprintf(file, "ERROR - Math\n");
						}
					}
					else if (a3.kind == IntConst) {
						/* Operation between Int constant and Int constant */
						fprintf(file, "%d: LDC 1, %d(0)\n", AssemNum++, a3.contents.val);
						fprintf(file, "%d: %s 0, 1, 0\n", AssemNum++, AssemCommand);
					}
					else if (a3.kind == DouConst) {
						/* Operation between Int constant and Double constant */
						type_to_store = 'd';
						fprintf(file, "%d: CVTIF 0, 0, 0\n", AssemNum++);
						fprintf(file, "%d: LDFC 1, %f(0)\n", AssemNum++, a3.contents.dval);
						fprintf(file, "%d: %sF 0, 1, 0\n", AssemNum++, AssemCommand);
					}
					else {
						fprintf(file, "ERROR - Math\n");
					}
				}
				else if (a2.kind == DouConst) {
					type_to_store = 'd';
					fprintf(file, "%d: LDFC 0, %f(0)\n", AssemNum++, a2.contents.dval);
					if (a3.kind == String) {
						if (s3->attrs->type == IntT) {
							/* Operation between Double constant and Int var */
							fprintf(file, "%d: LD 1, %d(5)\n", AssemNum++, -s3->attrs->memoffset);
							fprintf(file, "%d: CVTIF 1, 1, 1\n", AssemNum++);
							fprintf(file, "%d: %sF 0, 1, 0\n", AssemNum++, AssemCommand);
						}
						else if (s3->attrs->type == DouT) {
							/* Operation between Double constant and Double var */
							fprintf(file, "%d: LDF 1, %d(5)\n", AssemNum++, -s3->attrs->memoffset);
							fprintf(file, "%d: %sF 0, 1, 0\n", AssemNum++, AssemCommand);
						}
						else {
							fprintf(file, "ERROR - Math\n");
						}
					}
					else if (a3.kind == IntConst) {
						/* Operation between Double constant and Int constant */
						fprintf(file, "%d: LDC 1, %d(0)\n", AssemNum++, a3.contents.val);
						fprintf(file, "%d: CVTIF 1, 1, 1\n", AssemNum++);
						fprintf(file, "%d: %sF 0, 1, 0\n", AssemNum++, AssemCommand);
					}
					else if (a3.kind == DouConst) {
						/* Operation between Double constant and Double constant */
						fprintf(file, "%d: LDFC 1, %f(0)\n", AssemNum++, a3.contents.dval);
						fprintf(file, "%d: %sF 0, 1, 0\n", AssemNum++, AssemCommand);
					}
					else {
						fprintf(file, "ERROR - Math\n");
					}
				}
				else {
					fprintf(file, "ERROR - Math\n");
				}
				
				
				/** Storing values based on data types **/
				
				/* Store double in double */
				if (type_to_store == 'd' && type_of_storage == 'd') {		
					//fprintf(file, "%d: STF 0, %d(5)\n", AssemNum++, -s1->attrs->memoffset);
					if (s2->attrs->memoffset % 8 == 0) 
						fprintf(file, "%d: STF 0, %d(5)\n", AssemNum++, -s2->attrs->memoffset);
					else  
						fprintf(file, "%d: STF 0, %d(5)\n", AssemNum++, -s2->attrs->memoffset + 4);
				}
				/* Store double in int */
				else if (type_to_store == 'd' && type_of_storage == 'i') {	
					fprintf(file, "%d: CVTFI 0, 0, 0\n", AssemNum++);
					fprintf(file, "%d: ST 0, %d(5)\n", AssemNum++, -s1->attrs->memoffset);
				}
				/* Store int in double */
				else if (type_to_store == 'i' && type_of_storage == 'd') {	
					fprintf(file, "%d: CVTIF 0, 0, 0\n", AssemNum++);
					if (s1->attrs->memoffset % 8 == 0)
						fprintf(file, "%d: STF 0, %d(5)\n", AssemNum++, -s1->attrs->memoffset);
					else 
						fprintf(file, "%d: STF 0, %d(5)\n", AssemNum++, -s1->attrs->memoffset + 4);
					//fprintf(file, "%d: STF 0, %d(5)\n", AssemNum++, -s1->attrs->memoffset);
				}
				/* Store int in int */
				else if (type_to_store == 'i' && type_of_storage == 'i') {	
					fprintf(file, "%d: ST 0, %d(5)\n", AssemNum++, -s1->attrs->memoffset);
				}
				else {
					fprintf(file, "ERROR - Math\n");
				} 
				break;
				

			/*** INEQUALITIES ***/
			case inequality:
				if (a2.kind == String) {
					if (s2->attrs->type == IntT) {
						fprintf(file, "%d: LD 0, %d(5)\n", AssemNum++, -s2->attrs->memoffset);
						if (a3.kind == String) {
							if (s3->attrs->type == IntT) {
								/* Ineqality between Int var and Int var */
								fprintf(file, "%d: LD 1, %d(5)\n", AssemNum++, -s3->attrs->memoffset);
								fprintf(file, "%d: SUB 0, 1, 0\n", AssemNum++);
								fprintf(file, "%d: J%s 0, 2(7)\n", AssemNum++, AssemCommand);
								fprintf(file, "%d: LDC 0, 0(0)\n", AssemNum++);
								fprintf(file, "%d: LDA 7, 1(7)\n", AssemNum++);
								fprintf(file, "%d: LDC 0, 1(0)\n", AssemNum++);
							}
							else if (s3->attrs->type == DouT) {
								/* Ineqality between Int var and Double var */
								fprintf(file, "%d: CVTIF 0, 0, 0\n", AssemNum++);
								//fprintf(file, "%d: LDF 1, %d(5)\n", AssemNum++, -s3->attrs->memoffset);
								if (s3->attrs->memoffset % 8 == 0)
									fprintf(file, "%d: LDF 1, %d(5)\n", AssemNum++, -s3->attrs->memoffset);
								else
									fprintf(file, "%d: LDF 1, %d(5)\n", AssemNum++, -s3->attrs->memoffset + 4);
								fprintf(file, "%d: SUBF 0, 1, 0\n", AssemNum++);
								fprintf(file, "%d: JF%s 0, 2(7)\n", AssemNum++, AssemCommand);
								fprintf(file, "%d: LDC 0, 0(0)\n", AssemNum++);
								fprintf(file, "%d: LDA 7, 1(7)\n", AssemNum++);
								fprintf(file, "%d: LDC 0, 1(0)\n", AssemNum++);
							}
							else {
								fprintf(file, "ERROR - Inequality\n");
							}
						}
						else if (a3.kind == IntConst) {
							/* Ineqality between Int var and Int constant */
							fprintf(file, "%d: LDC 1, %d(0)\n", AssemNum++, a3.contents.val);
							fprintf(file, "%d: SUB 0, 1, 0\n", AssemNum++);
							fprintf(file, "%d: J%s 0, 2(7)\n", AssemNum++, AssemCommand);
							fprintf(file, "%d: LDC 0, 0(0)\n", AssemNum++);
							fprintf(file, "%d: LDA 7, 1(7)\n", AssemNum++);
							fprintf(file, "%d: LDC 0, 1(0)\n", AssemNum++);
						}
						else if (a3.kind == DouConst) {
							/* Ineqality between Int var and Double constant */
							fprintf(file, "%d: CVTIF 0, 0, 0\n", AssemNum++);
							fprintf(file, "%d: LDFC 1, %f(0)\n", AssemNum++, a3.contents.dval);
							fprintf(file, "%d: SUBF 0, 1, 0\n", AssemNum++);
							fprintf(file, "%d: JF%s 0, 2(7)\n", AssemNum++, AssemCommand);
							fprintf(file, "%d: LDC 0, 0(0)\n", AssemNum++);
							fprintf(file, "%d: LDA 7, 1(7)\n", AssemNum++);
							fprintf(file, "%d: LDC 0, 1(0)\n", AssemNum++);
						}
						else {
							fprintf(file, "ERROR - Inequality\n");
						}
					}
					else if (s2->attrs->type == DouT) {
						if (s2->attrs->memoffset % 8 == 0)
							fprintf(file, "%d: LDF 0, %d(5)\n", AssemNum++, -s2->attrs->memoffset);
						else
							fprintf(file, "%d: LDF 0, %d(5)\n", AssemNum++, -s2->attrs->memoffset + 4);
						//fprintf(file, "%d: LDF 0, %d(5)\n", AssemNum++, -s2->attrs->memoffset);
						if (a3.kind == String) {
							if (s3->attrs->type == IntT) {
								/* Ineqality between Double var and Int var */
								fprintf(file, "%d: LD 1, %d(5)\n", AssemNum++, -s3->attrs->memoffset);
								fprintf(file, "%d: CVTIF 1, 1, 1\n", AssemNum++);
							}
							else if (s3->attrs->type == DouT) {
								/* Ineqality between Double var and Double var */
								//fprintf(file, "%d: LDF 1, %d(5)\n", AssemNum++, -s3->attrs->memoffset);
								if (s3->attrs->memoffset % 8 == 0)
									fprintf(file, "%d: LDF 0, %d(5)\n", AssemNum++, -s3->attrs->memoffset);
								else 
									fprintf(file, "%d: LDF 0, %d(5)\n", AssemNum++, -s3->attrs->memoffset + 4);
							}
							else {
								fprintf(file, "ERROR - Inequality\n");
							}
						}
						else if (a3.kind == IntConst) {
							/* Ineqality between Double var and Int constant */
							fprintf(file, "%d: LDC 1, %d(0)\n", AssemNum++, a3.contents.val);
							fprintf(file, "%d: CVTIF 1, 1, 1\n", AssemNum++);
						}
						else if (a3.kind == DouConst) {
							/* Ineqality between Double var and Double constant */
							fprintf(file, "%d: LDFC 1, %f(0)\n", AssemNum++, a3.contents.dval);
						}
						else {
							fprintf(file, "ERROR - Inequality\n");
						}
						fprintf(file, "%d: SUBF 0, 1, 0\n", AssemNum++);
						fprintf(file, "%d: JF%s 0, 2(7)\n", AssemNum++, AssemCommand);
						fprintf(file, "%d: LDC 0, 0(0)\n", AssemNum++);
						fprintf(file, "%d: LDA 7, 1(7)\n", AssemNum++);
						fprintf(file, "%d: LDC 0, 1(0)\n", AssemNum++);
					}
					else {
						fprintf(file, "ERROR - Inequality\n");
					}
				}
				else if (a2.kind == IntConst) {
					fprintf(file, "%d: LDC 0, %d(0)\n", AssemNum++, a2.contents.val);
					if (a3.kind == String) {
						if (s3->attrs->type == IntT) {
							/* Ineqality between Int constant and Int var */
							fprintf(file, "%d: LD 1, %d(5)\n", AssemNum++, -s3->attrs->memoffset);
							fprintf(file, "%d: SUB 0, 1, 0\n", AssemNum++);
							fprintf(file, "%d: J%s 0, 2(7)\n", AssemNum++, AssemCommand);
							fprintf(file, "%d: LDC 0, 0(0)\n", AssemNum++);
							fprintf(file, "%d: LDA 7, 1(7)\n", AssemNum++);
							fprintf(file, "%d: LDC 0, 1(0)\n", AssemNum++);
						}
						else if (s3->attrs->type == DouT) {
							/* Ineqality between Int constant and Double var */
							fprintf(file, "%d: CVTIF 0, 0, 0\n", AssemNum++);
							fprintf(file, "%d: LDF 1, %d(5)\n", AssemNum++, -s3->attrs->memoffset);
							fprintf(file, "%d: SUBF 0, 1, 0\n", AssemNum++);
							fprintf(file, "%d: JF%s 0, 2(7)\n", AssemNum++, AssemCommand);
							fprintf(file, "%d: LDC 0, 0(0)\n", AssemNum++);
							fprintf(file, "%d: LDA 7, 1(7)\n", AssemNum++);
							fprintf(file, "%d: LDC 0, 1(0)\n", AssemNum++);
						}
						else {
							fprintf(file, "ERROR - Inequality\n");
						}
					}
					else if (a3.kind == IntConst) {
						/* Ineqality between Int constant and Int constant */
						fprintf(file, "%d: LDC 1, %d(0)\n", AssemNum++, a3.contents.val);
						fprintf(file, "%d: SUB 0, 1, 0\n", AssemNum++);
						fprintf(file, "%d: J%s 0, 2(7)\n", AssemNum++, AssemCommand);
						fprintf(file, "%d: LDC 0, 0(0)\n", AssemNum++);
						fprintf(file, "%d: LDA 7, 1(7)\n", AssemNum++);
						fprintf(file, "%d: LDC 0, 1(0)\n", AssemNum++);
					}
					else if (a3.kind == DouConst) {
						/* Ineqality between Int constant and Double constant */
						fprintf(file, "%d: CVTIF 0, 0, 0\n", AssemNum++);
						fprintf(file, "%d: LDFC 1, %f(0)\n", AssemNum++, a3.contents.dval);
						fprintf(file, "%d: SUBF 0, 1, 0\n", AssemNum++);
						fprintf(file, "%d: JF%s 0, 2(7)\n", AssemNum++, AssemCommand);
						fprintf(file, "%d: LDC 0, 0(0)\n", AssemNum++);
						fprintf(file, "%d: LDA 7, 1(7)\n", AssemNum++);
						fprintf(file, "%d: LDC 0, 1(0)\n", AssemNum++);
					}
					else {
						fprintf(file, "ERROR - Inequality\n");
					}
				}
				else if (a2.kind == DouConst) {
					fprintf(file, "%d: LDFC 0, %f(0)\n", AssemNum++, a2.contents.dval);
					if (a3.kind == String) {
						if (s3->attrs->type == IntT) {
							/* Ineqality between Double constant and Int var */
							fprintf(file, "%d: LD 1, %d(5)\n", AssemNum++, -s3->attrs->memoffset);
							fprintf(file, "%d: CVTIF 1, 0, 1\n", AssemNum++);
						}
						else if (s3->attrs->type == DouT) {
							/* Ineqality between Double constant and Double var */
							fprintf(file, "%d: LDF 1, %d(5)\n", AssemNum++, -s3->attrs->memoffset);
						}
						else {
							fprintf(file, "ERROR - Inequality\n");
						}
					}
					else if (a3.kind == IntConst) {
						/* Ineqality between Double constant and Int constant */
						fprintf(file, "%d: LDC 1, %d(0)\n", AssemNum++, a3.contents.val);
						fprintf(file, "%d: CVTIF 1, 0, 1\n", AssemNum++);
					}
					else if (a3.kind == DouConst) {
						/* Ineqality between Double constant and Double constant */
						fprintf(file, "%d: LDFC 1, %f(0)\n", AssemNum++, a3.contents.dval);
					}
					else {
						fprintf(file, "ERROR - Inequality\n");
					}
					fprintf(file, "%d: SUBF 0, 1, 0\n", AssemNum++);
					fprintf(file, "%d: JF%s 0, 2(7)\n", AssemNum++, AssemCommand);
					fprintf(file, "%d: LDC 0, 0(0)\n", AssemNum++);
					fprintf(file, "%d: LDA 7, 1(7)\n", AssemNum++);
					fprintf(file, "%d: LDC 0, 1(0)\n", AssemNum++);
				}
				else {
					fprintf(file, "ERROR\n");
				}
				break;
				
			/*** ASSIGNMENT ***/
			case assignment:
				if (type_of_storage == 'd') {
					if (a2.kind == String) {
						if (s2->attrs->type == IntT) {
							/* Store an Int variable in a Double variable */
							fprintf(file, "%d: LD 0, %d(5)\n", AssemNum++, -s2->attrs->memoffset);
							fprintf(file, "%d: CVTIF 0, 0, 0\n", AssemNum++);
							if (s1->attrs->memoffset % 8 == 0) 
								fprintf(file, "%d: STF 0, %d(5)\n", AssemNum++, -s1->attrs->memoffset);
							else  
								fprintf(file, "%d: STF 0, %d(5)\n", AssemNum++, -s1->attrs->memoffset + 4);

						}
						else if (s2->attrs->type == DouT) {
							/* Store a Double variable in a Double variable */
							if (s2->attrs->memoffset % 8 == 0)
								fprintf(file, "%d: LDF 0, %d(5)\n", AssemNum++, -s2->attrs->memoffset);
							else 
								fprintf(file, "%d: LDF 0, %d(5)\n", AssemNum++, -s2->attrs->memoffset + 4);
							if (s1->attrs->memoffset % 8 == 0)
								fprintf(file, "%d: STF 0, %d(5)\n", AssemNum++, -s1->attrs->memoffset);
							else 
								fprintf(file, "%d: STF 0, %d(5)\n", AssemNum++, -s1->attrs->memoffset + 4);
							//fprintf(file, "%d: STF 0, %d(5)\n", AssemNum++, -s1->attrs->memoffset);
						}
						else {
							fprintf(file, "ERROR - Assignment 1\n");
						}
					}
					else if (a2.kind == DouConst) {
						/* Store a Double constant in a Double variable */
						fprintf(file, "%d: LDFC 0, %f(0)\n", AssemNum++, a2.contents.dval);
						if (s1->attrs->memoffset % 8 == 0) 
							fprintf(file, "%d: STF 0, %d(5)\n", AssemNum++, -s1->attrs->memoffset);
						else
							fprintf(file, "%d: STF 0, %d(5)\n", AssemNum++, -(s1->attrs->memoffset - 4));
						//fprintf(file, "%d: STF 0, %d(5)\n", AssemNum++, -s1->attrs->memoffset);
					}
					else if (a2.kind == IntConst) {
						/* Store an Int constant in a Double variable */
						fprintf(file, "%d: LDC 0, %d(0)\n", AssemNum++, a2.contents.val);
						fprintf(file, "%d: CVTIF 0 0, 0\n", AssemNum++);
						if (s1->attrs->memoffset % 8 == 0)
							fprintf(file, "%d: STF 0, %d(5)\n", AssemNum++, -s1->attrs->memoffset);
						else 
							fprintf(file, "%d: STF 0, %d(5)\n", AssemNum++, -(s1->attrs->memoffset - 4));
						//fprintf(file, "%d: STF 0, %d(5)\n", AssemNum++, -s1->attrs->memoffset);
					}
					else {
						fprintf(file, "ERROR - Assignment 2\n");
					}
				}
				else { /* If storage type is an integer */
					if (a2.kind == String) {
						if (s2->attrs->type == IntT) {
							/* Store an Int variable in an Int variable */
							fprintf(file, "%d: LD 0, %d(5)\n", AssemNum++, -s2->attrs->memoffset);
							fprintf(file, "%d: ST 0, %d(5)\n", AssemNum++, -s1->attrs->memoffset);
						}
						else if (s2->attrs->type == DouT) {
							/* Store a Double variable in an Int variable */
							if (s2->attrs->memoffset % 8 == 0)
								fprintf(file, "%d: LDF 0, %d(5)\n", AssemNum++, -s2->attrs->memoffset);
							else 
								fprintf(file, "%d: LDF 0, %d(5)\n", AssemNum++, -s2->attrs->memoffset + 4);
							//fprintf(file, "%d: f, %d(5)\n", AssemNum++, -s2->attrs->memoffset);
							fprintf(file, "%d: CVTFI 0, 0, 0\n", AssemNum++);
							fprintf(file, "%d: ST 0, %d(5)\n", AssemNum++, -s1->attrs->memoffset);
						}
						else {
							/*f*/printf(/*file,*/ "ERROR - Assignment 3\n");
						}
					}
					else if (a2.kind == DouConst) {
						/* Store a Double constant in an Int variable */
						fprintf(file, "%d: LDFC 0, %f(0)\n", AssemNum++, a2.contents.dval);
						fprintf(file, "%d: CVTFI 0 0, 0\n", AssemNum++);
						fprintf(file, "%d: ST 0, %d(5)\n", AssemNum++, -s1->attrs->memoffset);
					}
					else if (a2.kind == IntConst) {
						/* Store an Int constant in an Int variable */
						fprintf(file, "%d: LDC 0, %d(0)\n", AssemNum++, a2.contents.val);
						fprintf(file, "%d: ST 0, %d(5)\n", AssemNum++, -s1->attrs->memoffset);
					}
					else {
						fprintf(file, "ERROR - Assignment 4\n");
					}
				}
				break;
			
			/*** READ FROM STANDARD INPUT ***/
			case read:
				if (s1->attrs->type == IntT) {
					fprintf(file, "%d: IN 0, 0, 0\n", AssemNum++);
				}
				else if (s1->attrs->type == DouT) {
					fprintf(file, "%d: INF 0, 0, 0\n", AssemNum++);
				}
				else {
					fprintf(file, "ERROR - Read\n");
				}
				break;
			
			/*** WRITE TO STANDARD OUTPUT ***/
			case write:
				if (a1.kind == String) {
					if (s1->attrs->type == IntT) {
						fprintf(file, "%d: LD 0, %d(5)\n", AssemNum++, -s1->attrs->memoffset);
						fprintf(file, "%d: OUT 0, 0, 0\n", AssemNum++);
					}
					else if (s1->attrs->type == DouT) {
						fprintf(file, "%d: LDF 0, %d(5)\n", AssemNum++, -s1->attrs->memoffset);
						fprintf(file, "%d: OUTF 0, 0, 0\n", AssemNum++);
					}
					else {
						/*f*/printf(/*file,*/ "ERROR - Write\n");
					}
				}
				else if (a1.kind == IntConst) {
					fprintf(file, "%d: LDC 0, %d(0)\n", AssemNum++, a1.contents.val);
					fprintf(file, "%d: OUT 0, 0, 0\n", AssemNum++);
				}
				else if (a1.kind == DouConst) {
					fprintf(file, "%d: LDFC 0, %f(0)\n", AssemNum++, a1.contents.dval);
					fprintf(file, "%d: OUTF 0, 0, 0\n", AssemNum++);
				}
				else {
					fprintf(file, "ERROR - Write\n");
				}
				break;
			
				
			/* 
			 * "If False" and "Goto" quads are not analyzed in normal order.
			 * This is explained below when they are actually implemented.
			 */
			
			/*** JUMP IF FALSE ***/
			case iffalse:
				AssemNum++;
				AssemNum++;
				AssemNum++;
				break;
				
			/*** JUMP TO A QUAD ***/
			case jumptoquad:
				AssemNum++;
				break;
				
			/*** CONTINUE ***/
			case cont:
				fprintf(file, "%d: LDA 7, %d(7)\n", AssemNum++, curScope);
				break;
						
								
			case enterScope:
				//printf(" Level %d \n", GetNodeLevel(s1));
				printf("ENTERING SCOPE\n");
				curScope = i;
				EnterScope(symtab);
				//continue;
				break;
			case exitScope:
				LeaveScope(symtab);
				//printf(" Level %d \n", GetNodeLevel(s1));
				//continue;
				break;
				
			case retu:
				printf("RETURNING AASFEGAEGEGAE\n");
				fprintf(file, "%d: LDA 7, %d(7)\n", AssemNum++, curScope);
				break;
				
			default:
				//printf("Quad not recognized.\n");
				break;
				
		}
		i++;
	}
	
	/*
	 * Due to the fact that there are times that we may want to jump to an
	 * unknown location that we have not processed yet, we wait to analyze 
	 * "goto" and "if false" quads until after all other asseembly lines
	 * have been analyzed. 
	 *
	 * By doing this we can just print a few lines out of order to avoid any
	 * rewriting of the output file.
	 * /
	
	/*** Printing assembly lines for goto statements. ***/
	i = 0;
	while (quads[i] != NULL) {
		a1 = quads[i]->addr1;
		a2 = quads[i]->addr2;
		a3 = quads[i]->addr3;
		
		if (quads[i]->op == gotoq) {
			fprintf(file, "%d: LDA 7, %d(7)\n", quadStartLocations[i], (quadStartLocations[a1.contents.val]) - quadStartLocations[i]);
		}
		i++;
	}
	
	/*** Printing assembly lines for "if false" statements ***/
	i = 0;
	while (quads[i] != NULL) {
		a1 = quads[i]->addr1;
		a2 = quads[i]->addr2;
		a3 = quads[i]->addr3;
		
		if (quads[i]->op == if_f) {
			if (a1.kind == String) {
				s1 = LookupInSymbolTable(symtab, a1.contents.name);
				if (s1->attrs->type == IntT) {
					fprintf(file, "%d: LD 0, %d(5)\n", quadStartLocations[i], -s1->attrs->memoffset);
					fprintf(file, "%d: JEQ 7, 1(7)\n", quadStartLocations[i]+1);
					fprintf(file, "%d: LDA 7, %d(7)\n", quadStartLocations[i]+2, (quadStartLocations[a2.contents.val]) - quadStartLocations[i]);
				}
				else if (s1->attrs->type == DouT) {
					fprintf(file, "%d: LDF 0, %d(5)\n", quadStartLocations[i], -s1->attrs->memoffset);
					fprintf(file, "%d: JFEQ 7, 1(7)\n", quadStartLocations[i]+1);
					fprintf(file, "%d: LDA 7, %d(7)\n", quadStartLocations[i]+2, (quadStartLocations[a2.contents.val]) - quadStartLocations[i]);
				}
				else {
					printf("ERROR - IfFalse\n");
				}
			}
			i++;
		}
		printf("%d\n", i++);
	}	
	
	/* Code for debugging purposes.
	 * This prints quad lines and their corresponding assembly lines.
	 */
	
	int j = 0;
	for (j = 0; j < 100; j++) {
		printf("%d %d\n", j, quadStartLocations[j]);
	}
	
	
	fprintf(file, "%d: HALT 0, 0, 0\n", AssemNum++);
}

