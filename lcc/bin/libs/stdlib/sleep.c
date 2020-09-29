#include <stdlib.h>

int sleep(int sec)
{
  int tim[2], rem[2];
  
  tim[0] = sec;
  tim[1] = 0;
  if (nanosleep(&tim, &rem)<0)
    return rem[0];
  else
    return 0;
}

int usleep(int usec)
{
  int tim[2];
  
  tim[0] = usec / 1000000;
  tim[1] = (usec % 1000000) * 1000;
  return nanosleep(&tim, NULL);
}

