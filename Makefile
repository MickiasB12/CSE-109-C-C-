CC=gcc #compiler name

CFLAGS= -DDEBUG -g -c -Wall -Wextra -Wwrite-strings #assigning the variable for the compiling

LFLAGS=-g -Wall -Wextra#assigning variable for linking files

output: prog1.o prog1_funcs.o #output is used for linking files
	${CC} ${LFLAGS} -o prog1 prog1.o prog1_funcs.o  #produces an executable file named 							#prog0
prog1.o: prog1.c #for creating a .o file for prog0.c
	${CC} ${LFLAGS} -c prog1.c
prog1_funcs.o: prog1_funcs.c prog1_funcs.h #creates a .o file for prog1_funcs.c
	${CC} ${LFLAGS} -c prog1_funcs.c

clean:  #for cleaning purposes
	rm -f *.o
	rm -f output

