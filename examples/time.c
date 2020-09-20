#include <stdio.h>
#include <time.h>

#define CLOCK_REALTIME 0

typedef int clockid_t;

struct timespec {
  time_t tv_sec;
  long tv_nsec;
};

int main(int argc, char **argv)
{ 
  int result;
  struct timespec tp;
  clockid_t clk_id;

  clk_id = CLOCK_REALTIME;

  result = clock_gettime(clk_id, &tp);
  printf("result: %i\n", result);
  printf("tp.tv_sec: %lld\n", tp.tv_sec);
  printf("tp.tv_nsec: %ld\n", tp.tv_nsec);

  return 0;
}
