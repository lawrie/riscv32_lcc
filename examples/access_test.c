#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {
  int r = access("temp", X_OK);

  printf("Result is %d\n", r);
  printf("errno is %d\n",  errno);

  return 0;
}


