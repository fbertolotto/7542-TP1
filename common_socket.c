#include "common_socket.h"

#include <string.h>

static void set_net_flags(addrinfo_t* hints) {
  memset(hints, 0, sizeof(addrinfo_t));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
  hints->ai_flags = 0;
}

int socket_start(socket_t* self) {
  addrinfo_t* data;
  int file_d = -1;
  for (data = self->info; data != NULL; data = data->ai_next) {
    file_d = socket(data->ai_family, data->ai_socktype, data->ai_protocol);
    if (file_d != -1) {
      self->file_d = file_d;
      break;
    }
  }
  if (file_d == -1) return 1;
  int val = 1;
  setsockopt(self->file_d, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
  return 0;
}

int socket_init(socket_t* self, addrinfo_t** info, char* host, char* port) {
  addrinfo_t hints;
  set_net_flags(&hints);
  getaddrinfo(host, port, &hints, &self->info);
  return 0;
}

int socket_bind(socket_t* self) {
  int res = bind(self->file_d, self->info->ai_addr, self->info->ai_addrlen);
  freeaddrinfo(self->info);
  if (res == -1) return 1;
  return 0;
}

int socket_listen(socket_t* self, int queue) {
  int res = listen(self->file_d, queue);
  if (res == -1) return 1;
  return 0;
}
int socket_accept(socket_t* self, socket_t* new) {
  struct sockaddr adrr;
  socklen_t adrrlen = (socklen_t)sizeof(adrr);
  int res = accept(self->file_d, &adrr, &adrrlen);
  if (res == -1) return 1;
  new->file_d = res;
  return 0;
}

int socket_connect(socket_t* self, addrinfo_t** results, char* host,
                   char* port) {
  socket_init(self, results, host, port);
  addrinfo_t* sv;
  int connected = -1;
  for (sv = self->info; sv != NULL; sv = sv->ai_next) {
    if (socket_start(self) == 0) {
      connected = connect(self->file_d, sv->ai_addr, sv->ai_addrlen);
      if (connected != -1) break;
    }
  }
  freeaddrinfo(self->info);
  if (connected == -1) return 1;
  return 0;
}

int socket_send(socket_t* self, char* msg, int len) {
  int t_b_s = 0;
  while (t_b_s < len) {
    int b_s = send(self->file_d, msg, len, MSG_NOSIGNAL);
    if (b_s == -1) return 1;
    t_b_s += b_s;
  }
  return 0;
}

int socket_recv(socket_t* self, char* buffer, size_t buffer_len) {
  return recv(self->file_d, buffer, buffer_len, 0);
}

int socket_destroy(socket_t* self) {
  if (self) {
    close(self->file_d);
  }
  return 0;
}
