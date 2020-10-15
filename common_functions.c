#include "common_functions.h"

void set_net_flags(addrinfo_t* hints) {
  memset(hints, 0, sizeof(addrinfo_t));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
  hints->ai_flags = 0;
}

void get_system_info(addrinfo_t* hints, addrinfo_t** info, char* host,
                     char* port) {
  getaddrinfo(host, port, hints, info);
}

void clean_param(char* arg, char* buffer, size_t buf_len) {
  memset(buffer, 0, buf_len);
  strtok(arg, "=");
  char* tmp = strtok(NULL, "=");
  memcpy(buffer, tmp, buf_len);
}

void clean_buffer(char* buffer, int buf_len) {
  memset(buffer,0,buf_len);
}
