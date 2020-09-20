#include <unistd.h>
#include <string.h>
int main(void) {
  char buf[32];
  printf("Hi!\n");
  sprintf(buf, "Hey %d\n", 123);
  printf("%s ***\n", buf);
  return 0;
}
