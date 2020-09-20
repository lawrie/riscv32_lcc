#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>

main() {
  int fd, nfd;
  int err;

  fd = open("test.txt",O_RDONLY);
  nfd = dup(fd);
  err = errno;

  printf("Result: %d\n",nfd);
  printf("errno: %d\n",err);

  return 0;
}
 
