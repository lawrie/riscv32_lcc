#include <string.h>
#include <stdlib.h>

void *calloc(size_t n, size_t s) {
  void *r = malloc(n * s);
  memset(r, 0, n*s);
  return r;
}

