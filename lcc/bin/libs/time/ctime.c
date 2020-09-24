/*
 * Copyright (c) 1987 Regents of the University of California.
 * This file may be freely redistributed provided that this
 */
#include <stdio.h>
#include <time.h>

#define	SECS_PER_MIN	60
#define	MINS_PER_HOUR	60
#define	HOURS_PER_DAY	24
#define	SECS_PER_HOUR	(SECS_PER_MIN * MINS_PER_HOUR)
#define	SECS_PER_DAY	((long) SECS_PER_HOUR * HOURS_PER_DAY)
#define	EPOCH_WDAY	4 /* thursday */

static int mon_lengths[2][12] = {
  31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
  31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static int year_lengths[2] = {
  365, 366
}
;
static int isleap(int y) {
  if (y % 4 != 0) return 0;
  if (y % 100 != 0) return 1;
  if (y % 400 == 0) return 1;
  return 0;
}

static struct tm *offtime(const time_t *clock, time_t offset) {
  register struct tm *tmp;
  register long	     days;
  register long      rem;
  register int       y;
  register int       yleap;
  register int       *ip;
	
  static struct tm   tm;

  tmp = &tm;
  days = *clock / SECS_PER_DAY;
  rem = *clock % SECS_PER_DAY;
  rem += offset;

  while (rem < 0) {
    rem += SECS_PER_DAY;
    --days;
  }  

  while (rem >= SECS_PER_DAY) {
    rem -= SECS_PER_DAY;
    ++days;
  }

  tmp->tm_hour = (int) (rem / SECS_PER_HOUR);
  rem = rem % SECS_PER_HOUR;
  tmp->tm_min = (int) (rem / SECS_PER_MIN);
  tmp->tm_sec = (int) (rem % SECS_PER_MIN);
  tmp->tm_wday = (int) ((EPOCH_WDAY + days) % 7);
  if (tmp->tm_wday < 0) tmp->tm_wday += 7;
	
  y = 1970;
  if (days >= 0)
    for ( ; ; ) {
      yleap = isleap(y);
      if (days < (long) year_lengths[yleap]) break;
      ++y;
      days = days - (long) year_lengths[yleap];
    }
  else 
    do {
      --y;
      yleap = isleap(y);
      days = days + (long) year_lengths[yleap];
    } while (days < 0);

  tmp->tm_year = y - 1900;
  tmp->tm_yday = (int) days;
  ip = mon_lengths[yleap];

  for (tmp->tm_mon = 0; days >= (long) ip[tmp->tm_mon]; ++(tmp->tm_mon))
    days = days - (long) ip[tmp->tm_mon];

  tmp->tm_mday = (int) (days + 1);
  tmp->tm_isdst = 0;

  return tmp;
}

struct tm *gmtime(const time_t *timep) {
  return offtime(timep, 0);
}

struct tm *gmtime_r(const time_t *timep, struct tm *result) {
  result = offtime(timep, 0);
  return result;
}

struct tm *localtime(const time_t *timep) {
  return offtime(timep, 0);
}

struct tm *localtime_r(const time_t *timep, struct tm *result) {
  result = offtime(timep, 0);
  return result;
}
static void putnumb(register char *cp, int n) {
  *cp++ = (n / 10) % 10 + '0';
  *cp++ = n % 10 + '0';
}

char * ctime(const time_t *timep) {
  return(asctime(localtime(timep)));
}

char *asctime_r(const struct tm *tm, char *buf) {
  buf = asctime(tm);
  return buf;
}

char *asctime(const struct tm *tm) {
  static char wday_name[7][3] = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
  };
  static char mon_name[12][3] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
  };
  static char  result[25];

  strcpy(result, "Day Mon 00 00:00:00 1900\n");
  memcpy(result, wday_name[tm->tm_wday], 3);
  memcpy(result+4, mon_name[tm->tm_mon], 3);
  putnumb(result+8, tm->tm_mday);
  putnumb(result+11, tm->tm_hour);
  putnumb(result+14, tm->tm_min);
  putnumb(result+17, tm->tm_sec);
  putnumb(result+20, 19 + tm->tm_year / 100);
  putnumb(result+22, tm->tm_year);
  result[24] = 0;
	
  return result;
}

