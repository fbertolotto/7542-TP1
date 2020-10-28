#include "client.h"

int client_init(client_t* self, char* host, char* port, char* method,
                char* key) {
  self->host = host;
  self->port = port;
  self->method = method;
  self->key = key;
  return 0;
}

int client_connect(client_t* self) {
  addrinfo_t* results;
  int sock_c = socket_connect(&self->client, &results, self->host, self->port);
  return sock_c;
}

static int send_to_sv(socket_t* client, char* msg, size_t msg_len) {
  int b_s = socket_send(client, msg, msg_len);
  memset(msg, 0, CHUNK);
  return b_s;
}

static int init_structs(client_t* self) {
  int file_r = file_reader_init(&self->fr);
  int crypto_r = crypto_init(&self->crypto, self->key, self->method);
  return (file_r || crypto_r);
}

void client_start(client_t* self) {
  int error = init_structs(self);
  if (error) return;
  char msg_buf[CHUNK], crypto_buf[CHUNK];
  size_t bytes_read;
  while ((bytes_read = file_reader_read(&self->fr, msg_buf, CHUNK))) {
    crypto_encrypt(&self->crypto, msg_buf, bytes_read, crypto_buf);
    error = send_to_sv(&self->client, crypto_buf, bytes_read);
    if (error) return;
  }
}

void client_finish(client_t* self) {
  socket_destroy(&self->client);
  crypto_destroy(&self->crypto);
  file_reader_destroy(&self->fr);
}
