#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

void error(char *msg) {
  int err = errno;
  printf("Error %s: %d\n", msg, err);
  abort();
}

int main(int argc, char *argv[]) {
  int sockfd, servlen, n;
  struct sockaddr_un serv_addr;
  char buf[82];
  char buf2[82];

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

  printf("Address of serv_addr: %p\n", &serv_addr);
  printf("Address of serv_addr.sun_path: %p\n", &serv_addr.sun_path);

  if (connect(sockfd, (struct sockaddr *) &serv_addr, servlen) < 0)
    error("connecting");

  printf("Connected\n");

  do {
    printf("Please enter your message\n");
    memset(buf,0, 82);
    read(0,buf,80);
    printf("Sending %s\n", buf);

    write(sockfd, buf, strlen(buf));

    printf("Reading reply\n");

    memset(buf2, 0, 82);
    n=read(sockfd,buf2,80);

    printf("Read %d bytes from socket\n", n);
    if (n > 0) {
      printf("The return message was: %s\n", buf2);
    }
  } while (1);

  printf("Closing\n");

  close(sockfd);

  return 0;  
}

