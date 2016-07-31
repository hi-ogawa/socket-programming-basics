# Socket Programming Basics

Motivation: familiarize myself with _socket_ concept before starting to read [Understanding Linux Network Internals](http://shop.oreilly.com/product/9780596002558.do).


## Demo

```
-- show client/server interaction in one command --
$ docker-compose up client server
Starting socketprogramming_client_1
Starting socketprogramming_server_1
Attaching to socketprogramming_client_1, socketprogramming_server_1
client_1  | Request sent: "Hello World"
server_1  | Request received: "Hello World"
server_1  | Response sent: "Message length is 11"
client_1  | Response received: "Message length is 11�"
socketprogramming_client_1 exited with code 0
socketprogramming_server_1 exited with code 0

-- clean up --
$ docker-compose down
$ rm client server
```


## Notes

- System calls from `<sys/socket.h>`:

```
-- server --
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

-- client --
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

-- both --
int socket(int domain, int type, int protocol);
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
ssize_t send(int sockfd, const void *buf, size_t len, int flags);
```

- Must-read man pages:
  - above system calls
  - `man 7 ip`

- Environment:
  - I'm using an [official gcc docker image](https://hub.docker.com/r/library/gcc/).
  - I extended the image for development purpose (e.g. man, nslookup, netcat).

- Subtle things:
  - `bind` is not needed for client socket.
  - `docker-compose up client server` might show output in a weird order like:

```
server_1  | Request received: "Hello World"
server_1  | Response sent: "Message length is 11"
client_1  | Request sent: "Hello World"
client_1  | Response received: "Message length is 11�"
```

## Reference

- http://www.linuxhowtos.org/C_C++/socket.htm
- http://www.csd.uoc.gr/~hy556/material/tutorials/cs556-3rd-tutorial.pdf
- http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html
- http://www.thegeekstuff.com/2011/12/c-socket-programming
