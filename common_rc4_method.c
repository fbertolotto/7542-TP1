#include "common_rc4_method.h"

#include <string.h>

void swap(rc4_method_t* self, int x, int y) {
  char temp = self->S[x];
  self->S[x] = self->S[y];
  self->S[y] = temp;
}

static void load_dic(rc4_method_t* self) {
  char* S = self->S;
  int i = 0;
  int j = 0;
  size_t key_len = strlen(self->key);
  for (; i < DIC_LENGTH; i++) S[i] = (char)i;
  for (i = j = 0; i < DIC_LENGTH; i++) {
    j = (j + self->key[i % key_len] + S[i]) & (DIC_LENGTH - 1);
    swap(self, i, j);
  }
}

int rc4_init(rc4_method_t* self, char* key) {
  self->key = key;
  memset(self->S, 0, 256);
  self->i = 0;
  self->j = 0;
  load_dic(self);
  return 0;
}

void rc4_encrypt(rc4_method_t* self, char* msg, size_t msg_len, char* buffer) {
  char* S = self->S;
  int y = 0;
  for (; y < msg_len; y++) {
    self->i = (self->i + 1) & (DIC_LENGTH - 1);
    self->j = (self->j + S[self->i]) & (DIC_LENGTH - 1);
    swap(self, self->i, self->j);
    char value = S[(S[self->i] + S[self->j]) & (DIC_LENGTH - 1)];
    buffer[y] = msg[y] ^ value;
  }
}

void rc4_decrypt(rc4_method_t* self, char* msg, size_t msg_len, char* buffer) {
  rc4_encrypt(self, msg, msg_len, buffer);
}

int rc4_destroy(rc4_method_t* self) { return 0; }
