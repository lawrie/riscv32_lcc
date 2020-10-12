#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {
  int r = rename("temp", "temp1");

  printf("Result is %d\n", r);
  printf("errno is %d\n",  errno);

  return 0;
}


