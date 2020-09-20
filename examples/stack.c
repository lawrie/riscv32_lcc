#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

char buf[30];
char s[16];

void reverse(char str[], int length)  { 
    int start = 0; 
    int end = length -1; 
    char t;

    while (start < end)  { 
        t = *(str+start);
	*(str+start) = *(str+end);
        *(str+end) = t;
        start++; 
        end--; 
    } 
} 

char* itoa(unsigned int num, char* str, int base)  { 
    int i = 0; 

    if (num == 0) {
      str[i++] = '0';
    }
      
    while (num != 0)  { 
        int rem = num % base; 
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0'; 
        num = num/base; 
    } 

    str[i] = '\0';
    
    reverse(str, i); 
  
    return str; 
} 

int main(int argc, char *argv[]) { 
  int i;

  sprintf(buf,"Stack %s\n","Printer");
  write(1,buf,strlen(buf));
  
  itoa(argc,s,10);
  strcpy(buf,"argc is ");
  strcat(buf,s);
  strcat(buf,"\n");
  write(1,buf,strlen(buf));

  strcpy(buf,"Address of argv is ");
  itoa((unsigned int) argv, s, 16);
  strcat(buf,s);
  strcat(buf,"\n");
  write(1,buf,strlen(buf));

  for(i=0;i<argc;i++) {
    strcpy(buf,"Address of argv[");
    itoa(i,s,10);
    strcat(buf,s);
    strcat(buf, "] is ");
    itoa((unsigned int) argv[i], s, 16);
    strcat(buf,s);
    strcat(buf,"\n");
    write(1,buf,strlen(buf));
  }

  strcpy(buf,"Address of first local is ");
  itoa((unsigned int) &i, s, 16);
  strcat(buf,s);
  strcat(buf,"\n");
  write(1,buf,strlen(buf));

  return 0;
}
