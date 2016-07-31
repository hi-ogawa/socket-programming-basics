#include <sys/socket.h>
#include <netinet/in.h> // struct sockaddr_in, INADDR_ANY
#include <string.h>     // memset
#include <stdlib.h>     // atoi
#include <stdio.h>      // printf, sprintf, fflush

int main() {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(struct sockaddr_in));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(atoi(getenv("PORT"))); // convertion to network byte order
  addr.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0
  bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));

  listen(sockfd, 1);

  struct sockaddr_in cli_addr;
  socklen_t cli_addrlen;
  int conn_sockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_addrlen);

  int len = 256;
  char req[len];
  memset(&req, 0, len);
  recv(conn_sockfd, req, len, 0);
  printf("Request received: \"%s\"\n", req);
  fflush(stdout);

  char resp[len];
  sprintf(resp, "Message length is %d", (int)strlen(req));
  send(conn_sockfd, resp, strlen(resp), 0);
  printf("Response sent: \"%s\"\n", resp);
  fflush(stdout);

  return 0;
}
