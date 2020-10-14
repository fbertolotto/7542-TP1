#ifndef SOCKET
#define SOCKET

#define _POSIX_C_SOURCE 200112L
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define MAX_PORT_LENGTH = 10

typedef struct socket {
    int file_d;
    struct addrinfo* info;
} socket_t;

int socket_init(socket_t* self, struct addrinfo* info);

int socket_bind(socket_t* self);

int socket_listen(socket_t* self, int queue);

int socket_accept(socket_t* self, socket_t* new);

int socket_connect(socket_t* self, struct addrinfo* servers);

int socket_send(socket_t* self, char* msg, int len);

int socket_recv(socket_t* self,char* buffer, size_t buffer_len);

int socket_destroy(socket_t* self);

#endif