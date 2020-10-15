#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common_crypto.h"
#include "common_methods.h"

static void crypto_create_method(crypto_t* self, char* method);

int crypto_init(crypto_t* self, void* key, char* method) {
    self->key = key;
    self->pos_i = 0;
    self->pos_j = 0;
    crypto_create_method(self, method);
    return 0;
}

void crypto_encrypt(crypto_t* self, char* msg,
                    size_t msg_len, char* buffer, size_t buf_len) {
    self->encrypter(self, msg, msg_len, buffer);
}

void crypto_decrypt(crypto_t* self, char* msg,
                    size_t msg_len, char* buffer, size_t buf_len) {
    self->decrypter(self, msg, msg_len, buffer);
}

int crypto_destroy(crypto_t* self) {return 0;}

static void crypto_create_method(crypto_t* self, char* method) {
    if (!strcmp(method, "cesar")) {
        self->encrypter = ceaser_encrypt;
        self->decrypter = ceaser_decrypt;
    }
    if (!strcmp(method, "vigenere")) {
        self->encrypter = vigenere_encrypt;
        self->decrypter = vigenere_decrypt;
    }
    if (!strcmp(method, "rc4")) {
        self->encrypter = rc4_encrypt;
        self->decrypter = rc4_decrypt;
        rc4_init(self->S, self->key);
    }
}
