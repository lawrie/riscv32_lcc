#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>

main() {
  int pid, uid, gid;
  int err;

  pid = getpid();
  uid = getuid();
  gid = getgid();

  printf("pid: %d\n",pid);
  printf("uid: %d\n",uid);
  printf("gid: %d\n",gid);

  return 0;
}
 
