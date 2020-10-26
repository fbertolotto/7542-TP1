#ifndef RC4_METHOD_H
#define RC4_METHOD_H

#include <stdio.h>

#define DIC_LENGTH 256

typedef struct rc4_method {
  char* key;
  size_t i;
  size_t j;
  char S[DIC_LENGTH];
} rc4_method_t;

int rc4_init(rc4_method_t* self, char* key);
void rc4_encrypt(rc4_method_t* self, char* msg, size_t msg_len, char* buffer);
void rc4_decrypt(rc4_method_t* self, char* msg, size_t msg_len, char* buffer);
int rc4_destroy(rc4_method_t* self);

#endif  // RC4_METHOD_H
