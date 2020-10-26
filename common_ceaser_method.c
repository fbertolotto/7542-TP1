#include "common_ceaser_method.h"

#include <stdlib.h>
#include <string.h>

#define DIC_LENGTH 256

int ceaser_init(ceaser_method_t* self, char* key) {
  self->key = (size_t)atoi(key);
  return 0;
}

static void ceaser(ceaser_method_t* self, char* msg, size_t msg_len,
                   char* buffer, char* op) {
  int i = 0;
  for (; i < msg_len; i++) {
    int char_numb = (int)msg[i];
    if (!strcmp(op, "sum")) {
      buffer[i] = (char)((char_numb + self->key) % DIC_LENGTH);
    } else {
      buffer[i] = (char)((char_numb - self->key) % DIC_LENGTH);
    }
  }
}

void ceaser_encrypt(ceaser_method_t* self, char* msg, size_t msg_len,
                    char* buffer) {
  ceaser(self, msg, msg_len, buffer, "sum");
}

void ceaser_decrypt(ceaser_method_t* self, char* msg, size_t msg_len,
                    char* buffer) {
  ceaser(self, msg, msg_len, buffer, "sub");
}

int ceaser_destroy(ceaser_method_t* self) { return 0; }
