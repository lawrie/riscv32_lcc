#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>

#define AF_UNIX		1
#define AF_INET		2

#define SOCK_STREAM	1

typedef int socklen_t;

struct sockaddr {
   unsigned short   sa_family;
   char             sa_data[14];
};

struct in_addr {
   unsigned long s_addr;
};

struct	sockaddr_un
{
 short	sun_family;	/* AF_UNIX */
 char	sun_path[108];	/* path name (gag) */
};

struct sockaddr_in {
   short int            sin_family;
   unsigned short int   sin_port;
   struct in_addr       sin_addr;
   unsigned char        sin_zero[8];
};

struct hostent {
   char *h_name; 
   char **h_aliases; 
   int h_addrtype;  
   int h_length;    
   char **h_addr_list;
#define h_addr  h_addr_list[0]
};

struct servent {
   char  *s_name; 
   char  **s_aliases; 
   int   s_port;  
   char  *s_proto;
};

extern int socket(int domain, int type, int protocol);
extern int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
extern int listen(int sockfd, int backlog);
extern int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen, 
                  int flags);
extern int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

void error(char *msg) {
  int err = errno;
  printf("Error %s: %d\n", msg, err);
  abort();
}

short htons(int n) {
  return ((n & 0xff) << 8) | (n >> 8);
}

int main(int argc, char *argv[]) {
  int sockfd, servlen, n;
  struct sockaddr_un serv_addr;
  char buf[82];

  if (argc < 2) {
    fprintf(stderr,"usage %s sockname\n", argv[0]);
    abort();
  }

  printf("AF_UNIX socket client test\n");

  bzero((char *)&serv_addr,sizeof(serv_addr));
  serv_addr.sun_family = AF_UNIX;
  strcpy(serv_addr.sun_path, argv[1]);
  servlen = strlen(serv_addr.sun_path) + 
                 sizeof(serv_addr.sun_family);

  if ((sockfd = socket(AF_UNIX, SOCK_STREAM,0)) < 0)
    error("Creating socket");

  printf("servlen is %d\n", servlen);

  printf("Address of serv_addr: %x\n", &serv_addr);
  printf("Address of serv_addr.sun_path: %x\n", &serv_addr.sun_path);

  if (connect(sockfd, (struct sockaddr *) &serv_addr, servlen) < 0)
    error("connecting");

  printf("Connected\n");

  printf("Please enter your message\n");
  bzero(buf,82);
  read(0,buf,80);
  printf("Sending %s\n", buf);

  //write(sockfd, buf, strlen(buf));

  printf("Reading reply\n");

  n = 0;
  //n=read(sockfd,buf,80);

  printf("Read %d bytes from socket\n", n);
  printf("The return message was ");
  write(1,buf,n);
  printf("\n");

  close(sockfd);

  return 0;  
}

