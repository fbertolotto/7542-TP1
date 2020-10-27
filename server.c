#include "server.h"

int server_init(server_t* self, char* port, char* method, char* key) {
  self->port = port;
  self->method = method;
  self->key = key;
  return 0;
}

static int create_listen_socket(server_t* self, addrinfo_t** info) {
  int sock_i = socket_init(&self->sv, info, NULL, self->port);
  int sock_s = socket_start(&self->sv);
  int sock_b = socket_bind(&self->sv);
  int sock_l = socket_listen(&self->sv, MAX_QUEUE);
  return (sock_i || sock_b || sock_l || sock_s);
}

int server_start(server_t* self) {
  addrinfo_t* server_info;
  int c_l_s = create_listen_socket(self, &server_info);
  return c_l_s;
}

int server_accept(server_t* self) {
  return socket_accept(&self->sv, &self->connection);
}

static void decrypt_msg(crypto_t* crypto, char* msg, int n, char* buffer) {
  crypto_decrypt(crypto, msg, n, buffer);
}

static void show_msg(char* msg, int size) { fwrite(msg, 1, size, stdout); }

static int create_crypto(crypto_t* crypto, char* key, char* method) {
  int init = crypto_init(crypto, key, method);
  if (init) {
    crypto_destroy(crypto);
    return 1;
  }
  return 0;
}

void server_process(server_t* self) {
  crypto_t crypto;
  char buffer[CHUNK], saver[CHUNK];
  int error = create_crypto(&crypto, self->key, self->method);
  if (error) return;
  int b_r = 1;
  while (b_r) {
    b_r = socket_recv(&self->connection, buffer, CHUNK);
    if (b_r == 0 || b_r == -1) return;
    decrypt_msg(&crypto, buffer, b_r, saver);
    show_msg(saver, b_r);
  }
}

void server_finish(server_t* self) {
  socket_destroy(&self->sv);
  socket_destroy(&self->connection);
}
