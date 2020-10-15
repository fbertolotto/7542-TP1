#include "common_socket.h"

#include <string.h>

static int socket_starter(socket_t* self, struct addrinfo* datas) {
  struct addrinfo* data;
  int file_d = -1;
  for (data = datas; data != NULL; data = data->ai_next) {
    file_d = socket(data->ai_family, data->ai_socktype, data->ai_protocol);
    if (file_d != -1) {
      self->file_d = file_d;
      break;
    }
  }
  if (file_d == -1) return 1;
  return 0;
}

int socket_init(socket_t* self, struct addrinfo* info) {
  self->info = info;
  int file_d = socket_starter(self, info);
  if (file_d == 1) {
    return file_d;
  }
  int val = 1;
  setsockopt(self->file_d, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
  return 0;
}

int socket_bind(socket_t* self) {
  int res = bind(self->file_d, self->info->ai_addr, self->info->ai_addrlen);
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

int socket_connect(socket_t* self, struct addrinfo* servers) {
  struct addrinfo* sv;
  int connected = -1;
  for (sv = servers; sv != NULL; sv = sv->ai_next) {
    if (socket_init(self, sv) == 0) {
      connected = connect(self->file_d, sv->ai_addr, sv->ai_addrlen);
      if (connected != -1) {
        break;
      }
    }
  }
  if (connected == -1) return 1;
  return 0;
}

int socket_send(socket_t* self, char* msg, int len) {
  return send(self->file_d, msg, len, MSG_NOSIGNAL);
}

int socket_recv(socket_t* self, char* buffer, size_t buffer_len) {
  memset(buffer, 0, buffer_len);
  return recv(self->file_d, buffer, buffer_len, 0);
}

int socket_destroy(socket_t* self) {
  if (self) {
    close(self->file_d);
  }
  return 0;
}
