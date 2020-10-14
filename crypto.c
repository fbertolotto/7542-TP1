#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "crypto.h"
#include "methods.h"

static void crypto_create_method(crypto_t* self);

int crypto_init(crypto_t* self, void* key, char* method) {
    strncpy(self->method, method, MAX_LENGHT);
    self->key = key;
    crypto_create_method(self);
    return 0;
}

void crypto_encrypt(crypto_t* self, char* msg,
                    size_t msg_len, char* buffer, size_t buf_len) {
    memset(buffer,0,buf_len);
    self->encrypter(self, msg, msg_len, buffer);
}

void crypto_decrypt(crypto_t* self, char* msg,
                    size_t msg_len, char* buffer, size_t buf_len) {
    memset(buffer,0,buf_len);
    self->decrypter(self, msg, msg_len, buffer);
}

int crypto_destroy(crypto_t* self) {return 0;}

static void crypto_create_method(crypto_t* self) {
    if (!strcmp(self->method, "ceaser")) {
        self->encrypter = ceaser_encrypt;
        self->decrypter = ceaser_decrypt;
    }
    if (!strcmp(self->method, "vigenere")) {
        self->encrypter = vigenere_encrypt;
        self->decrypter = vigenere_decrypt;
    }
    if (!strcmp(self->method, "rc4")) {
        self->encrypter = rc4_encrypt;
        self->decrypter = rc4_decrypt;
    }
}
