#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>

struct loff {
  long offset0;
  long offset1;
};

typedef struct loff loff_t;

extern int _llseek(unsigned int fd, unsigned long offset_high,
                   unsigned long offset_low, loff_t *result,
                   unsigned int whence);
main() {
  int fd;
  char buf[32];
  int r, err;
  loff_t result;

  fd = open("test.txt",O_RDONLY);

  errno = 0;
  r = _llseek(fd, 0, 8, &result, SEEK_SET);
  err = errno;

  printf("Result: %d\n",r);
  printf("errno: %d\n",err);

  printf("Offset 0: %d\n", result.offset0);
  printf("Offset 1: %d\n", result.offset1);

  read(fd,buf,2);
  printf("Second row:\n");

  write(1,buf,2);

  return 0;
}
 
