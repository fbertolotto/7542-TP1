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

/* Inicializa un cliente. Recibe el host, el puerto, el metodo y la clave
a utilizar en la encriptacion y envió de datos. Devuelve 0 en éxito */
int client_init(client_t* self, char* host, char* port, char* method,
                char* key);

/* Conecta al cliente al host:puerto especificado en el inicializador.
Devuelve 0 en éxito. */
int client_connect(client_t* self);

/* Empieza a encriptar y enviar datos. Repite el proceso hasta encontrar un
EOF en stdin. */
void client_start(client_t* self);

/* Se elimina el cliente. Destruye las estructuras internas utilizadas. */
void client_finish(client_t* self);

#endif  // CLIENT_H
