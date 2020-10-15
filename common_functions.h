#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H

#define _POSIX_C_SOURCE 200112L
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define CHUNK 65
#define ARG_LEN 10

typedef struct addrinfo addrinfo_t;

void set_net_flags(addrinfo_t* hints);
void get_system_info(addrinfo_t* hints, addrinfo_t** info, char* host,
                     char* port);
void clean_param(char* arg, char* buffer, size_t buf_len);
void clean_buffer(char* buffer, int buf_len);

#endif // COMMON_FUNC_H
