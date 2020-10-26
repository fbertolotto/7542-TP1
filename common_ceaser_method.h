#ifndef CEASER_METHOD_H
#define CEASER_METHOD_H

#include <stdio.h>

typedef struct ceaser_method {
  size_t key;
} ceaser_method_t;

int ceaser_init(ceaser_method_t* self, char* key);
void ceaser_encrypt(ceaser_method_t* self, char* msg, size_t msg_len,
                    char* buffer);
void ceaser_decrypt(ceaser_method_t* self, char* msg, size_t msg_len,
                    char* buffer);
int ceaser_destroy(ceaser_method_t* self);

#endif  // CEASER_METHOD_H
