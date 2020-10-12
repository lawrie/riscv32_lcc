#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
  struct tm tmval;
  struct tm *tm_new;
  long secs;

  if (argc != 8) {
    printf("Usage %s wday yyyy mon dd hh mm ss\n", argv[0]);
    abort();
  }

  tmval.tm_wday = atoi(argv[1]);
  tmval.tm_year = atoi(argv[2]) - 1900;
  tmval.tm_mon = atoi(argv[3]) - 1;
  tmval.tm_mday = atoi(argv[4]);
  tmval.tm_hour = atoi(argv[5]);
  tmval.tm_min = atoi(argv[6]);
  tmval.tm_sec = atoi(argv[7]);

  printf("%s\n", asctime(&tmval)); 
  
  secs = mktime(&tmval);
  printf("time_t is %ld\n", secs);
 
  tm_new = localtime(&secs);
  printf("%s\n", asctime(tm_new)); 
  
  return 0;
}

