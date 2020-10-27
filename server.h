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

/* Inicializa un servidor. Recibe el puerto, el metodo y la clave
a utilizar en la desencriptacion y recibo de datos. Devuelve 0 en éxito */
int server_init(server_t* self, char* port, char* method, char* key);

/* Prepara al servidor para escuchar una conexión. Devuelve 0 en éxito. */
int server_start(server_t* self);

/* El servidor espera activamente una conexion, una vez detectada intenta
realizarla, en caso de éxito devuelve 0. */
int server_accept(server_t* self);

/* El servidor comienza a recibir datos de la conexion establecida, y a
medida que los reciba, los desencripta y los escribe en stdout. Este
proceso termina cuando la conexion es terminada por parte del cliente. */
void server_process(server_t* self);

/* Se elimina el servidor. Destruye las estructuras internas utilizadas. */
void server_finish(server_t* self);

#endif  // SERVER_H
