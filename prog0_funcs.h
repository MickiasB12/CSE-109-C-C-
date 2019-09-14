#ifndef PROG0_FUNCS
#define PROG0_FUNCS

char parseArgs(int, char *[]);
void collectInput(char **, int *);
size_t calcValue(char, char **, int, long *);
void printResult(char, long, size_t);
void bail(int, const char *);                 /* return code and message to print */
void help();

#endif
