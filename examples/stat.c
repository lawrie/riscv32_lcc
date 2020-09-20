#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

struct statx {
  char data[512];
};

static struct statx finfo;

extern int statx(int dirfd, const char *pathname, 
                 int flags, unsigned int mask, struct statx *statxbuf);

int main(int argc, char *argv[]) {
  int r;
  int err;
  char buf[32];

  if (argc != 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    _exit(1);
  }

  r = statx(-100, argv[1], 0, 0x7ff, &finfo);

  if (r != 0) {
    err = errno;
    sprintf(buf, "Result: %d\n",r);
    write(1,buf,strlen(buf));
    sprintf(buf, "errno: %d\n",err);
    write(1, buf, strlen(buf));
   } else {
    sprintf(buf, "File size of %s is %d\n", argv[1], *((int *) &finfo.data[40]));
    write(1, buf, strlen(buf));
   }

  _exit(0);
  return 0;
}

