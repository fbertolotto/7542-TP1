#ifndef CRYPTO_H
#define CRYPTO_H
#include <stddef.h>

#define RC4_DIC 256

typedef struct crypto {
  void* key;
  int pos_i;
  int pos_j;
  char S[RC4_DIC];
  void (*encrypter)(struct crypto* self, char* msg, size_t msg_len,
                    char* buffer);
  void (*decrypter)(struct crypto* self, char* msg, size_t msg_len,
                    char* buffer);
} crypto_t;

int crypto_init(crypto_t* self, void* key, char* method);
void crypto_encrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer,
                    size_t buf_len);
void crypto_decrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer,
                    size_t buf_len);
int crypto_destroy(crypto_t* self);

#endif // CRYPTO_H
