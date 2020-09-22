#include <stdio.h>

extern int sleep(int sec);
extern int usleep(int usec);

int main() {
  printf("Sleep for 2 seconds\n");
  sleep(2);
  printf("Sleep for 1M microseconds\n");
  usleep(1000000);

  return 0;
}

