#include "common_crypto.h"
#include "common_functions.h"
#include "common_socket.h"
#include "client_file_reader.h"

#define ARG_N 5

static int start_connection(socket_t* client, char* host, char* port) {
  addrinfo_t cl_hints, *results;
  set_net_flags(&cl_hints);
  get_system_info(&cl_hints, &results, "127.0.0.1", port);
  int sock_c = socket_connect(client, results);
  freeaddrinfo(results);
  return sock_c;
}

static int send_to_sv(socket_t* client, char* msg, size_t msg_len) {
  int i = 0;
  while (i != msg_len) {
    int bytes = socket_send(client, msg, msg_len);
    if (bytes == -1) return 1;
    i += bytes;
  }
  return 0;
}

static int start_program(socket_t* client, crypto_t* crypto,
                         file_reader_t* fr) {
  int error = 1;
  char msg_buf[CHUNK], crypto_buf[CHUNK];
  memset(msg_buf, 0, CHUNK);
  memset(crypto_buf, 0, CHUNK);
  while (file_reader_read(fr, msg_buf, CHUNK)) {
    crypto_encrypt(crypto, msg_buf, strlen(msg_buf), crypto_buf, CHUNK);
    error = send_to_sv(client, crypto_buf, strlen(crypto_buf));
    memset(msg_buf, 0, CHUNK);
    memset(crypto_buf, 0, CHUNK);
  }
  return error;
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
  int crypto_r = crypto_init(crypto, (void*)key, method);
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
