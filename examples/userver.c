#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <errno.h>

#define AF_UNIX         1
#define AF_INET         2

#define SOCK_STREAM     1

typedef int socklen_t;

struct sockaddr {
   unsigned short   sa_family;
   char             sa_data[14];
};

struct  sockaddr_un   
{                       
 short  sun_family;     /* AF_UNIX */
 char   sun_path[108];  /* path name (gag) */
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

int main(int argc, char*argv[]) {
  int sockfd, newsockfd, n;
  socklen_t servlen, clilen;
  struct sockaddr_un cli_addr, serv_addr;
  char buf[80];

  if (argc < 2) {
    fprintf(stderr,"usage %s sockname\n", argv[0]);
    abort();
  }

  /* Create socket */
  if ((sockfd = socket(AF_UNIX,SOCK_STREAM,0)) < 0)
    error("creating socket");
 
  /* Setup serv_addr strucrure */
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sun_family = AF_UNIX;
  strcpy(serv_addr.sun_path, argv[1]);
  servlen=strlen(serv_addr.sun_path) + 
                 sizeof(serv_addr.sun_family);

  /* Bind to socket */
  if (bind(sockfd,(struct sockaddr *)&serv_addr,servlen)<0)
    error("binding socket"); 

  /* Listen for connections */
  if (listen(sockfd,5) < 0)
    error("listening");

  printf("Listening ...\n");

  /* Accept connection */
  clilen = sizeof(cli_addr);
  printf("clilen is %d\n", clilen);

  newsockfd = accept( sockfd,(struct sockaddr *)&cli_addr,&clilen, 0);

  if (newsockfd < 0) 
    error("accepting");

  printf("Socket id is %d\n", newsockfd);

  printf("A connection has been established\n");

  printf("Client address is %s, length: %d, type %d\n", 
          cli_addr.sun_path, clilen, cli_addr.sun_family);

  /* Read the message and write to stdouti */ 
  n=read(newsockfd,buf,80);

  printf("Bytes read %d\n", n);
  write(1,buf,n);

  printf("Writing reply\n");

  /* Write reply */
  write(newsockfd,"Message received\n",17);

  /* Tidy up */
  close(newsockfd);
  close(sockfd);

  return 0;
}
