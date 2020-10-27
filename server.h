#ifndef SERVER_H
#define SERVER_H
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_crypto.h"
#include "common_socket.h"

#define CHUNK 64
#define MAX_QUEUE 1
#define ARG_N 4

typedef struct server {
  socket_t sv;
  socket_t connection;
  char* port;
  char* method;
  char* key;
} server_t;

int server_init(server_t* self, char* port, char* method, char* key);
int server_start(server_t* self);
int server_accept(server_t* self);
void server_process(server_t* self);
void server_finish(server_t* self);

#endif  // SERVER_H
