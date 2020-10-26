#include "common_crypto.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_method.h"

int load_method(crypto_t* self, char* method, char* key) {
  if (!strcmp(method, "cesar")) return ceaser_init(&self->ceaser, key);
  if (!strcmp(method, "vigenere")) return vigenere_init(&self->vigenere, key);
  if (!strcmp(method, "rc4")) return rc4_init(&self->rc4, key);
  return 1;
}

int crypto_init(crypto_t* self, char* key, char* method) {
  self->name = method;
  return load_method(self, method, key);
}

void crypto_encrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer) {
  char* method = self->name;
  if (!strcmp(method, "cesar")) {
    ceaser_encrypt(&self->ceaser, msg, msg_len, buffer);
  } else if (!strcmp(method, "vigenere")) {
    vigenere_encrypt(&self->vigenere, msg, msg_len, buffer);
  } else if (!strcmp(method, "rc4")) {
    rc4_encrypt(&self->rc4, msg, msg_len, buffer);
  }
}

void crypto_decrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer) {
  char* method = self->name;
  if (!strcmp(method, "cesar"))
    ceaser_decrypt(&self->ceaser, msg, msg_len, buffer);
  else if (!strcmp(method, "vigenere"))
    vigenere_decrypt(&self->vigenere, msg, msg_len, buffer);
  else if (!strcmp(method, "rc4"))
    rc4_decrypt(&self->rc4, msg, msg_len, buffer);
}

int crypto_destroy(crypto_t* self) {
  int c = ceaser_destroy(&self->ceaser);
  int v = vigenere_destroy(&self->vigenere);
  int r = rc4_destroy(&self->rc4);
  return (!r && !v && !c);
}
