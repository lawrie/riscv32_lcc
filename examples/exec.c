#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]) {
  int r;
  int err;

  if (argc < 2) {
    printf("Usage: %s <program> <args>\n", argv[0]);
    abort();
  }

  r = execve(argv[1], &argv[1], NULL);
  err = errno;

  printf("Result is %d\n", r);
  printf("errno is %d\n", err);

  return 0;
}
    
