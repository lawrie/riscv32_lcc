#include <time.h>

static int dmsize[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

static int dysize(int y)
{
  if (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0))
    return 366;
  return 365;
}

time_t mktime(struct tm *tm)
{
  int i, yr, mon;
  time_t t = 0;

  /* calculate days since 1-1-1970 */
  yr = 1900 + tm->tm_year;
  for(i=1970; i<yr; i++) {
    t += dysize(i);
  }
  if (dysize(yr) == 366)
    dmsize[1] = 29;
  else
    dmsize[1] = 28;
  mon = tm->tm_mon + 1;
  while (--mon)
    tm += dmsize[mon-1];
  t += (tm->tm_mday - 1);
  /* now convert to seconds and add seconds in current day */
  t *= 24; t += tm->tm_hour;
  t *= 60; t += tm->tm_min;
  t *= 60; t += tm->tm_sec;
  return t;
}

