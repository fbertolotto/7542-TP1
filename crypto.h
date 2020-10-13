#ifndef CRYPTO_H
#define CRYPTO_H
#include <stddef.h>
#define MAX_LENGHT 50

typedef struct crypto {
    void* key;
    char method[MAX_LENGHT];
    void(*encrypter) (struct crypto* self, char* msg,
                    size_t msg_len, char* buffer);
    void(*decrypter) (struct crypto* self, char* msg,
                    size_t msg_len, char* buffer);
} crypto_t;

int crypto_init(crypto_t* self, void* key, char* method);
void crypto_encrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer);
void crypto_decrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer);
int crypto_destroy(crypto_t* self);

#endif