#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define KDGETMODE        0x4B3B
#define KDSETMODE        0x4B3A 

int main() {
  int r;
  int mode;

  r = ioctl(0, KDGETMODE, &mode);

  printf("Result: %d\n", r);
  printf("errno: %d\n", errno);

  return 0;
}
