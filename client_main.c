#include "client.h"

int main(int argc, char* argv[]) {
  client_t client;

  if (argc != ARG_N) return 0;
  strtok(argv[3], "=");
  char* method = strtok(NULL, "=");
  strtok(argv[4], "=");
  char* key = strtok(NULL, "=");

  if (client_init(&client, argv[1], argv[2], method, key)) return 0;
  if (!client_connect(&client)) client_start(&client);
  client_finish(&client);
  return 0;
}
