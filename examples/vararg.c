
#include <stdarg.h>
#include <unistd.h>

void putc(char c) {
  char s[2];
  s[0] = c;
  s[1] = 0;
  write(1, s, 1);
}

void puti(int i)
{
    int b=0;
    int c=0;

    for (b = 28; b >= 0; b = b - 4)
    {
        c = (i >> b) & 0xF;
        if (c < 10)
        {
            putc( 48 + c );
        }
        else
        {
            putc( 65 - 10 + c );
        }
    }

     putc(10); // Newline!
}

void printargs(int arg1, ...)
{
  va_list ap;
  int i;

  va_start(ap, arg1);
  for (i = arg1; i >= 0; i = va_arg(ap, int))
    puti(i);
  va_end(ap);
  putc('\n');
}


int main()
{
  printargs(5, 2, 14, 84, 97, 15, -1, 48, -1);
  printargs(84, 51, -1);
  return 0;
}

