#ifndef METHODS_H
#define METHODS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "common_crypto.h"

void ceaser_encrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer);
void ceaser_decrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer);
void vigenere_encrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer);
void vigenere_decrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer);
void rc4_encrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer);
void rc4_decrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer);
void rc4_init(char* S, void* key);

#endif // METHODS_H
