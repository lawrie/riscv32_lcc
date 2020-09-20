
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <errno.h>
  
int main()  { 
   int p;
   int err;

   p = fork();
   err = errno;

   printf("p  = %d\n", p);
   printf("errno  = %d\n", err);

   if (p < 0) {
     printf("Fork failed\n");
   } else if (p == 0) {
     printf("Child process\n");
   } else {
     printf("Parent process\n");
   }
    
   return 0; 
} 

