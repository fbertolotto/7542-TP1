#ifndef SOCKET_H
#define SOCKET_H

#define _POSIX_C_SOURCE 200112L
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_PORT_LENGTH = 10

typedef struct socket {
  int file_d;
  struct addrinfo* info;
} socket_t;

/* Inicializa un socket. Devuelve 1 en caso de error y
0 en caso de éxito */
int socket_init(socket_t* self, struct addrinfo* info);

/* Bindea un socket al puerto asignado por el sistema.
Devuelve 1 en caso de error y 0 en éxito */
int socket_bind(socket_t* self);

/* Pone al socket en modo "listen" y asigna el maximo
de clientes posibles en espera. Devuelve 1 en caso de 
error y 0 en éxito */
int socket_listen(socket_t* self, int queue);

/* Acepta la conexión recibida por el primer socket
y la carga en el nuevo. Devuelve 1 en caso de error
y 0 en éxito */
int socket_accept(socket_t* self, socket_t* new);

/* Itera las opciones de servidores posibles e intenta
conectarse. En caso de conseguirlo devuelve 0 y el socket
queda cargado con la conexión. En error devuelve 1 */
int socket_connect(socket_t* self, struct addrinfo* servers);

/* Enviá el mensaje a traves del socket. Devuelve la
cantidad de bytes que logro enviar y -1 en caso de
ocurrir algún error */
int socket_send(socket_t* self, char* msg, int len);

/* Recibe el mensaje a traves del socket y lo guarda en el buffer.
Devuelve la cantidad de bytes que recibió,-1 en caso de
ocurrir algún error y 0 si el que enviá cerro la conexión. */
int socket_recv(socket_t* self, char* buffer, size_t buffer_len);

/* Destruye el socket. Devuelve 0 */
int socket_destroy(socket_t* self);

#endif  // SOCKET_H
