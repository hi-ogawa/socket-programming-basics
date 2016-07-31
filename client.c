#include <sys/socket.h>
#include <netinet/in.h> // struct sockaddr_in, INADDR_ANY, htons
#include <netdb.h>      // gethostbyname
#include <string.h>     // memset, memcpy, strlen
#include <stdlib.h>     // atoi, getenv
#include <stdio.h>      // printf, puts, fflush

int main() {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(struct sockaddr_in));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(atoi(getenv("PORT")));
  memcpy((char *)&addr.sin_addr.s_addr, (char *)gethostbyname(getenv("HOST"))->h_addr, 4);
  connect(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr));

  char *buf = "Hello World";
  send(sockfd, buf, strlen(buf), 0);
  printf("Request sent: \"%s\"\n", buf);
  fflush(stdout);

  int len = 256;
  char req[len];
  recv(sockfd, req, len, 0);
  printf("Response received: \"%s\"\n", req);
  fflush(stdout);

  return 0;
}
