#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

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
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sun_family = AF_UNIX;
  strcpy(serv_addr.sun_path, argv[1]);
  servlen=strlen(serv_addr.sun_path) + 
                 sizeof(serv_addr.sun_family);

  printf("servlen is %d\n", servlen);

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

  newsockfd = accept( sockfd, (struct sockaddr *)&cli_addr, &clilen);

  if (newsockfd < 0) 
    error("accepting");

  printf("Socket id is %d\n", newsockfd);

  printf("A connection has been established\n");

  printf("Client address path: %s, length: %d, type %d\n", 
          cli_addr.sun_path, clilen, cli_addr.sun_family);

  do {
    /* Read the message and write to stdout */ 
    n=read(newsockfd,buf,80);

    if (n > 0) {
      printf("Bytes read %d\n", n);
      write(1,buf,n);

      printf("Writing reply\n");

      /* Write reply */
      write(newsockfd,"Message received\n",17);
    }
  } while(1);

  /* Tidy up */
  close(newsockfd);
  close(sockfd);

  return 0;
}
