#ifndef CRYPTO_H
#define CRYPTO_H
#include <stddef.h>

#include "common_ceaser_method.h"
#include "common_rc4_method.h"
#include "common_vigenere_method.h"

typedef struct crypto {
  char* name;
  rc4_method_t rc4;
  vigenere_method_t vigenere;
  ceaser_method_t ceaser;
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

#endif  // CRYPTO_H
