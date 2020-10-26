#include "common_vigenere_method.h"

#include <string.h>

#define DIC_LENGTH 256

int vigenere_init(vigenere_method_t* self, char* key) {
  self->key = key;
  self->iteration = 0;
  return 0;
}

static void vigenere_msg_numb(char c, int* buffer) { *buffer = (int)c; }

static void vigenere_key_numb(char* key, int pos, int len, int* buffer) {
  if (pos <= len) {
    *buffer = (int)key[pos];
  } else {
    *buffer = (int)key[(pos % strlen(key))];
  }
}

static void vigenere(vigenere_method_t* self, char* msg, size_t msg_len,
                     char* buffer, char* op) {
  char* key = self->key;
  int char_numb_msg;
  int char_numb_key;
  for (int i = 0; i < msg_len; i++) {
    vigenere_msg_numb(msg[i], &char_numb_msg);
    vigenere_key_numb(key, self->iteration, strlen(key) - 1, &char_numb_key);
    self->iteration++;
    if (!strcmp(op, "sum")) {
      buffer[i] = (char)((char_numb_msg + char_numb_key) % DIC_LENGTH);
    } else {
      buffer[i] = (char)((char_numb_msg - char_numb_key) % DIC_LENGTH);
    }
  }
}

void vigenere_encrypt(vigenere_method_t* self, char* msg, size_t msg_len,
                      char* buffer) {
  vigenere(self, msg, msg_len, buffer, "sum");
}

void vigenere_decrypt(vigenere_method_t* self, char* msg, size_t msg_len,
                      char* buffer) {
  vigenere(self, msg, msg_len, buffer, "sub");
}

int vigenere_destroy(vigenere_method_t* self) { return 0; }
