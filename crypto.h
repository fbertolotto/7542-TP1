#ifndef CRYPTO_H
#define CRYPTO_H

typedef struct crypto {
    void* key;
    char* original;
    char* encrypted;
    char* method;
    void (*encrypter) (struct crypto* self);
    void (*decrypter) (struct crypto* self);
    

} crypto_t;

int crypto_init(crypto_t* self, void* key,const char* msg,const char* cipher,char* method);
int crypto_destroy(crypto_t* self);
void crypto_print_original(crypto_t* self);
void crypto_print_encrypted(crypto_t* self);

#endif