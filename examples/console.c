#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define FIONBIO          0x5421

#define TCGETS           0x5401
#define TCSETS           0x5402

#define ECHO             0000010
#define ICANON           0000002
#define ISIG             0000001
#define IXON             0002000

typedef unsigned char    cc_t;
typedef unsigned int     speed_t;
typedef unsigned int     tcflag_t;

#define NCCS             32

struct termios {
    tcflag_t c_iflag;                /* input mode flags */
    tcflag_t c_oflag;                /* output mode flags */
    tcflag_t c_cflag;                /* control mode flags */
    tcflag_t c_lflag;                /* local mode flags */
    cc_t c_line;                     /* line discipline */
    cc_t c_cc[NCCS];                 /* control characters */
    speed_t c_ispeed;                /* input speed */
    speed_t c_ospeed;                /* output speed */
#define _HAVE_STRUCT_TERMIOS_C_ISPEED 1
#define _HAVE_STRUCT_TERMIOS_C_OSPEED 1
  };

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
  
