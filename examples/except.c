#include <stdio.h>
#include <string.h>

main() {
  int *x = 0;
  char buf[32];

  sprintf(buf, "Addr of local data: %p\n", &x);
  write(1,buf,strlen(buf));

  return *x;
}

