#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
  time_t tim = time(NULL);
  char *ts = ctime(&tim);
  struct tm *lt = localtime(&tim);
  struct tm *gmt = gmtime(&tim);
  time_t mt = mktime(lt);
  char buf[32];

  printf("Date is %s\n", ts); 

  printf("mtime is %ld\n", mt);

  asctime_r(gmt, buf);
  printf("asctime_r is %s\n", buf);

  ctime_r(&tim, buf);

  printf("ctime_r is %s\n", buf);

  return 0;
}

