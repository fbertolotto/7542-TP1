#include "server.h"

int main(int argc, char* argv[]) {
  server_t server;
  memset(&server, 0, sizeof(server_t));

  if (argc != ARG_N) return 0;
  strtok(argv[2], "=");
  char* method = strtok(NULL, "=");
  strtok(argv[3], "=");
  char* key = strtok(NULL, "=");

  if (server_init(&server, argv[1], method, key)) return 0;
  if (!server_start(&server)) {
    if (!server_accept(&server)) {
      server_process(&server);
    }
  }
  server_finish(&server);
  return 0;
}
