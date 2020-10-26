#define _POSIX_C_SOURCE 200112L
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "client_file_reader.h"
#include "common_crypto.h"
#include "common_socket.h"

#define ARG_N 5
#define CHUNK 64
#define ARG_LEN 51

static void clean_param(char* arg, char* buffer, size_t buf_len) {
  memset(buffer, 0, buf_len);
  strtok(arg, "=");
  char* tmp = strtok(NULL, "=");
  memcpy(buffer, tmp, buf_len);
}


static int start_connection(socket_t* client, char* host, char* port) {
  addrinfo_t* results;
  int sock_c = socket_connect(client, &results, host, port);
  return sock_c;
}

static int send_to_sv(socket_t* client, char* msg, size_t msg_len) {
  int b_s = socket_send(client, msg, msg_len);
  memset(msg, 0, CHUNK);
  return b_s;
}

static void start_program(socket_t* client, crypto_t* crypto,
                          file_reader_t* fr) {
  char msg_buf[CHUNK], crypto_buf[CHUNK];
  memset(msg_buf, 0, CHUNK);
  memset(crypto_buf, 0, CHUNK);
  size_t bytes_read;
  while ((bytes_read = file_reader_read(fr, msg_buf, CHUNK))) {
    crypto_encrypt(crypto, msg_buf, bytes_read, crypto_buf);
    memset(msg_buf, 0, CHUNK);
    int error = send_to_sv(client, crypto_buf, bytes_read);
    if (error) return;
  }
}

static int get_parameters(int argc, char** argv, char params[ARG_N][ARG_LEN]) {
  if (argc != ARG_N) return 1;
  memcpy(params[0], argv[1], ARG_LEN);
  memcpy(params[1], argv[2], ARG_LEN);
  clean_param(argv[3], params[2], ARG_LEN);
  clean_param(argv[4], params[3], ARG_LEN);
  return 0;
}

static int init_structs(file_reader_t* fr, crypto_t* crypto, char* method,
                        char* key) {
  int file_r = file_reader_init(fr);
  int crypto_r = crypto_init(crypto, key, method);
  return (file_r || crypto_r);
}

int main(int argc, char* argv[]) {
  socket_t client;
  crypto_t crypto;
  file_reader_t fr;
  char params[ARG_N][ARG_LEN];  // host,port,method,key
  if (get_parameters(argc, argv, params)) return 0;
  if (!start_connection(&client, params[0], params[1])) {
    if (!init_structs(&fr, &crypto, params[2], params[3])) {
      start_program(&client, &crypto, &fr);
    }
  }
  socket_destroy(&client);
  crypto_destroy(&crypto);
  file_reader_destroy(&fr);
  return 0;
}
