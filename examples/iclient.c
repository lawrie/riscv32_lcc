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

void error() {
  int err = errno;
  printf("Error: %d\n", err);
  abort();
}

short htons(int n) {
  return ((n & 0xff) << 8) | (n >> 8);
}

int main(int argc, char *argv[]) {
  int sockfd, portno, r;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  if (argc < 3) {
    fprintf(stderr,"usage %s hostname port\n", argv[0]);
    _exit(0);
  }

  printf("Socket client test\n");

  portno = atoi(argv[2]);
  printf("Host: %s, port: %d\n", argv[1], portno);

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("sockfd: %d\n", sockfd);
  if (sockfd <0) error();

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  //bcopy((char *)server->h_addr, 
  //   (char *)&serv_addr.sin_addr.s_addr,
  //   server->h_length);
  
  serv_addr.sin_port = htons(portno);
  r = connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
  printf("Connect result: %d\n", r);

  if (r <0) error();

  return 0;  
}

