#include <stdlib.h>      /* for free */
#include "prog0_funcs.h"

 /* compile with: makefile *
/* check memory leak with: valgrind --leak-check=yes prog0 sop */

int main(int argc, char *argv[]) {
  char *name = NULL;  /* to hold first and last name */
  int number;         /* to hold favorite integer */
  char op;            /* to hold 0 ("sop") or 1 ("pos") */
  size_t unrep;       /* to hold 0 (representable) or 1 (overflow/underflow, i.e., unrepresentable) */
  long result;        /* to hold calculated value */

  op = parseArgs(argc, argv);                      /* parse arguments and return 0 or 1 for operation */
  collectInput(&name, &number);                    /* collect student's name and favorite integer */
  unrep = calcValue(op, &name, number, &result);   /* calculate sop or pos result based on all input */
  printResult(op, result, unrep);                  /* print calculated result and if it is unrepresentable */

  if (name) free(name);
  return 0;  /* return a value to function which called main */
}
