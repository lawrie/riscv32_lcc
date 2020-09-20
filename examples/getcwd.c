#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {
  char buf[32];
  int r;
  int err;

  r = getcwd(buf,32);
  err = errno;

  printf("Result: %d\n",r);
  printf("errno: %d\n",err);

  printf("%s\n",buf);

  return 0;
}

  
