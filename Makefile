CC = gcc
CFLAGS = -g -c -Wall -Wextra -Wwrite-strings
LFLAGS = -g -Wall -Wextra

output: prog3.o prog3_funcs.o
	${CC} ${LFLAGS} -o prog3 prog3.o prog3_funcs.o -lcurl

prog3.o: prog3.c prog3_funcs.h ftp_file.h
	${CC} ${CFLAGS} prog3.c

prog3_funcs.o: prog3_funcs.c prog3_funcs.h ftp_file.h
	${CC} ${CFLAGS} prog3_funcs.c
clean: 
	rm -f *.o
	rm -f output
