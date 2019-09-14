CC = gcc #compiler name

CFLAGS= -g -c -Wall -Wextra -Wwrite-strings #assigning the variable for the compiling

LFLAGS=-g -Wall -Wextra #assigning variable for linking files

all: prog0 prog link #finally wrapping up all the compilation and linking

prog0: 
	${CC} ${CFLAGS} prog0_funcs.c #for prog0_funcs.c file
prog:
	${CC} ${CFLAGS} prog0.c #for prog0.c file
link: 
	${CC} ${LFLAGS} -o prog0 prog0_funcs.o prog0.o #links all the file

