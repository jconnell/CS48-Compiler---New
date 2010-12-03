cs48compiler: lex.yy.o cs48.tab.o ast.o Symtab.o assemblygen.o quads.o tokens.h ast.h
	gcc -o cs48compiler lex.yy.o ast.o Symtab.o assemblygen.o quads.o cs48.tab.o -lfl

cs48.tab.o: cs48.tab.c ast.h tokens.h
	gcc -c cs48.tab.c

lex.yy.o: lex.yy.c ast.h tokens.h
	gcc -c lex.yy.c

Symtab.o: Symtab.c Symtab.h
	gcc -c Symtab.c

assemblygen.o: assemblygen.h quads.h Symtab.h ast.h
	gcc -c assemblygen.c

quads.o: quads.h
	gcc -c quads.c

ast.o: ast.c ast.h
	gcc -c ast.c

cs48.tab.c: cs48.y
	bison cs48.y

lex.yy.c: lexer.l
	flex lexer.l

.PHONY: clean
clean:
	rm -f lex.yy.c cs48.tab.c ast.o cs48.tab.o lex.yy.o Symtab.o assemblygen.o quads.o cs48parser

