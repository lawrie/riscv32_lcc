#include <unistd.h>

int main(int argc, char *argv[]) {
  write(1,argv[0],7);
  return 0;
}

