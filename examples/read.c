#include <unistd.h>
#include <stdio.h>
#include <string.h>

extern int errno;

main() {
  char buf[32];
  char s[8];
  int r;
  int err;

  r = read(0,s,7);
  err = errno;
  s[8] = 0;
  sprintf(buf,"Result from read: %d\n",r);
  write(1,buf,strlen(buf));
  
  sprintf(buf, "errno: %d\n",err);
  write(1,buf,strlen(buf));

  printf("String read:");
  write(1,s,strlen(s));
 
  return 0;
}
  
