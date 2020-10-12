#include <stdio.h>
#include <time.h>

int main() {
  time_t tim = time(NULL);

  printf("time is %ld\n", tim);
  
  return 0;
}

