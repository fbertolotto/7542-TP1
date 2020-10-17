#ifndef CRYPTO_H
#define CRYPTO_H
#include <stddef.h>

#define RC4_DIC 256
#define KEY_MAX_SIZE 51

typedef struct crypto {
  char key[KEY_MAX_SIZE];
  int pos_i;
  int pos_j;
  char S[RC4_DIC];
  void (*encrypter)(struct crypto* self, char* msg, size_t msg_len,
                    char* buffer);
  void (*decrypter)(struct crypto* self, char* msg, size_t msg_len,
                    char* buffer);
} crypto_t;

/* Inicializa un crypto (criptografo) según el metodo y la clave especificada.
Devuelve 0. */
int crypto_init(crypto_t* self, char* key, char* method);

/* Encripta el mensaje de largo especificado y lo carga en el buffer.
Es necesario que el buffer sea mayor que el mensaje. */
void crypto_encrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer);

/* Desencripta el mensaje de largo especificado y lo carga en el buffer.
Es necesario que el buffer sea mayor que el mensaje. */
void crypto_decrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer);

/* Destruye el crypto. Devuelve 0. */
int crypto_destroy(crypto_t* self);

#endif // CRYPTO_H
