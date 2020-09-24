#include <time.h>

#define CLOCK_REALTIME 0

typedef int clockid_t;

struct timespec {
  time_t tv_sec;
  long tv_nsec;
};

time_t time(time_t *tloc) {
  int result;                  
  struct timespec tp;
                     
  result = clock_gettime(CLOCK_REALTIME, &tp);

  if (tloc) *tloc = tp.tv_sec;

  return tp.tv_sec;
}

