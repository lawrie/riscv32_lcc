#include <float.h>
#include <stdio.h>
#include <string.h>

float x = 3.1415;
float y = 2.4563;
float z;
char buf[32];

int main(void) {
  z = x  + y;
  sprintf(buf, "Result: %f\n",z);
  write(1,buf,strlen(buf));
  return 0;
}

