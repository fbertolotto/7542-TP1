#ifndef CLIENT_H
#define CLIENT_H
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "client_file_reader.h"
#include "common_crypto.h"
#include "common_socket.h"

#define CHUNK 64
#define ARG_N 5

typedef struct client {
  socket_t client;
  crypto_t crypto;
  file_reader_t fr;
  char* host;
  char* port;
  char* method;
  char* key;
} client_t;

int client_init(client_t* self, char* host, char* port, char* method,
                char* key);
int client_connect(client_t* self);
void client_start(client_t* self);
void client_finish(client_t* self);

#endif  // CLIENT_H
