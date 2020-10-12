#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {
  int r = rmdir("temp");

  printf("Result is %d\n", r);
  printf("errno is %d\n",  errno);

  return 0;
}


