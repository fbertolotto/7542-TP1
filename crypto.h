#ifndef CRYPTO_H
#define CRYPTO_H

#define MAX_LENGHT 50

typedef struct crypto {
    void* key;
    char original[MAX_LENGHT];
    char encrypted[MAX_LENGHT];
    char method[MAX_LENGHT];
    void(*encrypter) (struct crypto* self);
    void(*decrypter) (struct crypto* self);
} crypto_t;

int crypto_init(crypto_t* self, void* key, char* method);
void crypto_encrypt(crypto_t* self, char* msg);
void crypto_decrypt(crypto_t* self, char* cipher);
int crypto_destroy(crypto_t* self);
void crypto_print_original(crypto_t* self);
void crypto_print_encrypted(crypto_t* self);

#endif