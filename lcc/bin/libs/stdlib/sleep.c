#include <stdlib.h>

int sleep(int sec)
{
  int tim[3], rem[3];
  
  tim[0] = sec;
  tim[1] = 0;
  tim[2] = 0;
  if (nanosleep(&tim, &rem)<0)
    return rem[0];
  else
    return 0;
}

int usleep(int usec)
{
  int tim[3];
  
  tim[0] = usec / 1000000;
  tim[1] = 0;
  tim[2] = (usec % 1000000) * 1000;
  return nanosleep(&tim, NULL);
}

