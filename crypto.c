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

void crypto_encrypt(crypto_t* self, char* msg) {
    strncpy(self->original, msg, MAX_LENGHT);
    self->encrypter(self);
}

void crypto_decrypt(crypto_t* self, char* cipher) {
    memcpy(self->encrypted, cipher, MAX_LENGHT);
    self->decrypter(self);
}

void crypto_print_original(crypto_t* self) {printf("%s\n", self->original);}

void crypto_print_encrypted(crypto_t* self) {printf("%s\n",self->encrypted);}

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
