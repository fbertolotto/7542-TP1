#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H

#define _POSIX_C_SOURCE 200112L
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define CHUNK 65
#define ARG_LEN 51

typedef struct addrinfo addrinfo_t;

/* Carga en el struct addrinfo_t los valores necesarios para generar una
conexion TCP con protocol IPV */
void set_net_flags(addrinfo_t* hints);

/* Carga en info, los valores provistos por el sistema operativo para 
realizar la conexion */
void get_system_info(addrinfo_t* hints, addrinfo_t** info, char* host,
                     char* port);

/* Parsea los parametros del estilo <param>=<value> y carga en el buffer
indicado solo el valor */
void clean_param(char* arg, char* buffer, size_t buf_len);

/* Limpia el buffer cargándolo con 0s */
void clean_buffer(char* buffer, int buf_len);

#endif // COMMON_FUNC_H
