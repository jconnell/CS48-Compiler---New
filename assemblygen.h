/*
 *  assemblygen.h
 *  Assembly Generation from quads.
 *  Written by Jonathan Connell and David Kopec
 */

#include "ast.h"
#include "quads.h"
#include "Symtab.h"
#include <stdio.h>


#ifndef ASSEM_H_
#define ASSEM_H_

typedef enum {math, enterScope, exitScope, inequality, assignment, read, write, jumptoquad, iffalse, loadparam, func_ret, cont, retu, other} AssemKind;


void AssemblyGen(Quad** q, FILE* file, SymbolTable* s);
/**************************************************************************
 * Name: AssemblyGen
 * Purpose: iterates through each quad, generates the corresponding
 *			assembly code, and outputs the assembly code to a file.
 * Parameters: q, the array of quads
 *			   file, the file to which the assembly code will be wrriten to
 *			   s, the symbol table for our program
 **************************************************************************/

#endif