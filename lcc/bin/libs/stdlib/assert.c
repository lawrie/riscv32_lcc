#include <stdio.h>
#include <stdlib.h>

void __assertfail(char *msg, char *cond, char *file, int line) {
  fprintf(stderr, msg, cond, file, line);
  abort();
}

