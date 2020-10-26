#ifndef METHOD_H
#define METHOD_H

#include "common_ceaser_method.h"
#include "common_rc4_method.h"
#include "common_vigenere_method.h"

typedef struct method {
  char* name;
  rc4_method_t rc4;
  vigenere_method_t vigenere;
  ceaser_method_t ceaser;
} method_t;

int method_init(method_t* self, char* name, char* key);
void method_encrypt(method_t* self, char* msg, size_t msg_len, char* buffer);
void method_decrypt(method_t* self, char* msg, size_t msg_len, char* buffer);
void method_destroy(method_t* self);

#endif  // METHOD_H
