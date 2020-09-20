#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

main() {
  int fd;
  char buf[32];
  int r, err;

  fd = open("test.txt",O_RDONLY);

  errno = 0;
  r = lseek(fd, 8, SEEK_SET);
  err = errno;

  printf("Result: %d\n",r);
  printf("errno: %d\n",err);

  read(fd,buf,2);
  printf("Second row:\n");

  write(1,buf,2);

  return 0;
}
 
