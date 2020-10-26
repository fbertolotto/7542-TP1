#ifndef VIGENERE_METHOD_H
#define VIGENERE_METHOD_H

#include <stdio.h>

typedef struct vigenere_method {
  char* key;
  size_t iteration;
} vigenere_method_t;

int vigenere_init(vigenere_method_t* self, char* key);
void vigenere_encrypt(vigenere_method_t* self, char* msg, size_t msg_len,
                      char* buffer);
void vigenere_decrypt(vigenere_method_t* self, char* msg, size_t msg_len,
                      char* buffer);
int vigenere_destroy(vigenere_method_t* self);

#endif  // VIGENERE_METHOD_H
