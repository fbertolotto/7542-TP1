#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "crypto.h"
#include "methods.h"

#define MAX_LENGHT 50

static void crypto_create_method(crypto_t* self);

int crypto_init(crypto_t* self, void* key,const char* msg,const char* cipher,char* method) {

    self->original = calloc(sizeof(char),MAX_LENGHT);
    self->encrypted = calloc(sizeof(char),MAX_LENGHT);
    self->method = calloc(sizeof(char),MAX_LENGHT);
    self->key = key;

    strcpy(self->method,method);
    self->key = self->key;
    crypto_create_method(self);

    if (msg) {
        strcpy(self->original,msg);
        self->encrypter(self);
    }

    if (cipher) {
        strcpy(self->encrypted,cipher);
        self->decrypter(self);
    }

    return 0;
}

void crypto_print_original(crypto_t* self) {printf("%s\n",self->original);}
void crypto_print_encrypted(crypto_t* self) {printf("%s\n",self->encrypted);}

int crypto_destroy(crypto_t* self) {
    free(self->original);
    free(self->encrypted);
    free(self->method);
    return 0;
}

static void crypto_create_method(crypto_t* self) {

    if (!strcmp(self->method,"ceaser")) {
        self->encrypter = ceaser_encrypt;
        self->decrypter = ceaser_decrypt;
    }
    if (!strcmp(self->method,"vigenere")) {
        self->encrypter = vigenere_encrypt;
        self->decrypter = vigenere_decrypt;
    }
    
    if (!strcmp(self->method,"rc4")) {
        self->encrypter = rc4_encrypt;
        self->decrypter = rc4_decrypt;
    }
}