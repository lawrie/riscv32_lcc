#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[]) {
  int f;
  char buf[32];
  int err;
  int i;

  f = open("test.txt", 01101, 0777); // O_WRONLY | O_CREAT | O_TRUNC, 0644
  err = errno;

  sprintf(buf, "Result: %d\n",f);
  write(1,buf,strlen(buf));

  sprintf(buf, "errno: %d\n",err);
  write(1,buf,strlen(buf));

  if (f) {
    for(i=0;i<argc;i++) {
      write(f,argv[i],strlen(argv[i]));
      write(f,"\n",1);
    }

    close(f);
  }

  return 0;
}

