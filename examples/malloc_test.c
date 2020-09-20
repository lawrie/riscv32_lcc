#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
  char *m1 = malloc(20);
  char *m2 = malloc(20);

  printf("Addr of m1: %p\n", m1);
  printf("Addr of m2: %p\n", m2);
  
  strcpy(m1,"Hello\n");
  write(1,m1, strlen(m1));

  return 0;
}

