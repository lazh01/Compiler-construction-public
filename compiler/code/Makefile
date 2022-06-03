CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -pedantic -g


main:             y.tab.o lex.yy.o main.o tree.h tree.o pretty.h pretty.o types.h types.o typecheck.h typecheck.o symbol.h symbol.o memory.h memory.o weed.h weed.o TEMP.h TEMP.o codegen.h codegen.o frame.h frame.o
	          $(CC) lex.yy.o y.tab.o tree.o pretty.o memory.o typecheck.o types.o symbol.o weed.o main.o  TEMP.o codegen.o frame.o -o compiler -lfl

y.tab.c y.tab.h:  compiler.y
	          bison -v -y -d compiler.y

lex.yy.c:         compiler.l y.tab.h 
	          flex compiler.l