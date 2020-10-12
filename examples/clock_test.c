#include <stdio.h>
#include <time.h>

int main(int argc, char **argv)
{ 
  int result;
  struct timespec tp;
  clockid_t clk_id;

  clk_id = CLOCK_REALTIME;

  printf("Real time\n");

  result = clock_gettime(clk_id, &tp);
  printf("result: %i\n", result);
  printf("tp.tv_sec: %lld\n", tp.tv_sec);
  printf("tp.tv_nsec: %ld\n", tp.tv_nsec);

  clk_id = CLOCK_PROCESS_CPUTIME_ID;;

  printf("Process time\n");

  result = clock_gettime(clk_id, &tp);
  printf("result: %i\n", result);
  printf("tp.tv_sec: %lld\n", tp.tv_sec);
  printf("tp.tv_nsec: %ld\n", tp.tv_nsec);

  printf("clock is %ld\n", clock());

  return 0;
}
