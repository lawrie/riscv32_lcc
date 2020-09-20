#include <stdio.h>
#include <unistd.h>
#include <string.h>

main() {
  char name[20];
  char buf[32];

  printf("What's your name?");
  scanf("%s",name);
  sprintf(buf,"Hello, %s\n", name);
  write(1,buf,strlen(buf));

  return 0;
}



