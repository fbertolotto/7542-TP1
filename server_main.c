#include "common_crypto.h"
#include "common_functions.h"
#include "common_socket.h"

#define MAX_QUEUE 1
#define ARG_N 4

static int create_listen_socket(socket_t* server, addrinfo_t* info) {
  int sock_i = socket_init(server, info);
  int sock_b = socket_bind(server);
  int sock_l = socket_listen(server, MAX_QUEUE);
  return (sock_i || sock_b || sock_l);
}

static int server_start(socket_t* server, char* port) {
  addrinfo_t sv_hints, *server_info;
  set_net_flags(&sv_hints);
  get_system_info(&sv_hints, &server_info, NULL, port);
  int c_l_s = create_listen_socket(server, server_info);
  freeaddrinfo(server_info);
  return c_l_s;
}

static int server_accept(socket_t* sv, socket_t* conect) {
  return socket_accept(sv, conect);
}

static void decrypt_msg(crypto_t* crypto, char* msg, int n, char* buffer) {
  crypto_decrypt(crypto, msg, n, buffer, CHUNK - 1);
  clean_buffer(msg, CHUNK);
}

static void show_msg(char* msg) {
  fprintf(stdout, "%s", msg);
  clean_buffer(msg, CHUNK);
}

static int create_crypto(crypto_t* crypto, char* key, char* method) {
    int init = crypto_init(crypto, key, method);
    if (init) {
      crypto_destroy(crypto);
      return 1;
    }
    return 0;
  }

static void server_process(socket_t* socket, char* method, char* key) {
  crypto_t crypto;
  char buffer[CHUNK], saver[CHUNK];
  clean_buffer(buffer, CHUNK);
  clean_buffer(saver, CHUNK);
  int error = create_crypto(&crypto, key, method);
  if (error) return;
  int b_r = 1;
  while (b_r) {
    b_r = socket_recv(socket, buffer, CHUNK - 1);
    if (b_r == 0 || b_r == -1) return;
    decrypt_msg(&crypto, buffer, b_r, saver);
    show_msg(saver);
  }
}

static void server_finish(socket_t* server, socket_t* conection) {
  socket_destroy(server);
  socket_destroy(conection);
}

static int get_parameters(int argc, char** argv, char params[ARG_N][ARG_LEN]) {
  if (argc != ARG_N) return 1;
  memcpy(params[0], argv[1], ARG_LEN);
  clean_param(argv[2], params[1], ARG_LEN);
  clean_param(argv[3], params[2], ARG_LEN);
  return 0;
}

int main(int argc, char* argv[]) {
  socket_t server, conect;
  char params[ARG_N][ARG_LEN];  // port,method,key
  if (get_parameters(argc, argv, params)) return 0;

  if (!server_start(&server, params[0])) {
    if (!server_accept(&server, &conect)) {
      server_process(&conect, params[1], params[2]);
    }
  }
  server_finish(&server, &conect);
  return 0;
}
