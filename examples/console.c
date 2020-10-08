#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h>

struct termios raw, orig;
int mode;

void tidyup() {
  mode = 0;
  ioctl(0, FIONBIO, &mode);
  ioctl(0, TCSETS, &orig);
}

int main() {
  char buf[1];
  int r;

  atexit(tidyup);

  ioctl(0, TCGETS, &orig);
  raw = orig;

  raw.c_iflag &= ~(IXON);
  raw.c_lflag &= ~(ECHO | ICANON | ISIG);
  ioctl(0, TCSETS, &raw);
   
  mode = 1;
  ioctl(0, FIONBIO, &mode);

  while (1) {
    r = read(0, buf, 1);
    if (r > 0)  {
      printf("key is %d\n", buf[0]);
      if (buf[0] == 'q') break;
    } else write(1,"!",1);
  }

  exit(0);
}
  
