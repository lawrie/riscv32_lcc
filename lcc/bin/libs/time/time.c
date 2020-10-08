#include <time.h>

time_t time(time_t *tloc) {
  int result;                  
  struct timespec tp;
                     
  result = clock_gettime(CLOCK_REALTIME, &tp);

  if (tloc) *tloc = tp.tv_sec;

  return tp.tv_sec;
}

