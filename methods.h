#ifndef METHODS_H
#define METHODS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "crypto.h"

void ceaser_encrypt(crypto_t* self);
void ceaser_decrypt(crypto_t* self);
void vigenere_encrypt(crypto_t* self);
void vigenere_decrypt(crypto_t* self);
void rc4_encrypt(crypto_t* self);
void rc4_decrypt(crypto_t* self);

#endif