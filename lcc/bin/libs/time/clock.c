#include <time.h>

clock_t clock(void) {
  struct timespec ts;
  clock_t result = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);

  if (result < 0) return result;
  else return (ts.tv_sec * CLOCKS_PER_SEC
                + ts.tv_nsec / (1000000000 / CLOCKS_PER_SEC));
}

