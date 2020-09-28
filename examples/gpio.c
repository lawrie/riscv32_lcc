#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

void error(char *msg, int r) {
  if (r < 0) {
    printf("errno from %s is %d\n", msg, errno);
    abort();
  }
}

void send(char *fname, char *val) {
  int f = open(fname, O_WRONLY);
  error(fname, f);
  
  write(f, val, strlen(val));
  close(f);
}

int main(int argc, char *argv[]) {
  int i, f, n = 0;
  char gpio[4];
  char dev[] = "/sys/class/gpio/";
  char dir[34], val[30], exp[23], unexp[25];

  if (argc > 1) n = atoi(argv[1]);

  sprintf(gpio,"%d",480+n);
  sprintf(dir,"%sgpio%s/direction", dev, gpio);
  sprintf(val,"%sgpio%s/value", dev, gpio);
  sprintf(exp,"%sexport", dev);
  sprintf(unexp,"%sunexport", dev);

  send(exp, gpio);
  send(dir,"out");
   
  f = open(val, O_WRONLY);
  error("value", f);

  for(i=0;i<10;i++) {
    write(f, ((i % 2) == 0) ? "1" : "0", 1);
    sleep(1);
  }

  close(f);
  send(unexp, gpio);

  return 0;
}
  
