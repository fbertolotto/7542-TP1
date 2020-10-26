#ifndef RC4_METHOD_H
#define RC4_METHOD_H

#include <stdio.h>

#define DIC_LENGTH 256

typedef struct rc4_method {
  char* key;
  size_t i;
  size_t j;
  char S[DIC_LENGTH];
} rc4_method_t;

/* Inicialiazdor del metodo RC4. Devuelve 0 en exito. Recibe la clave
 necesaria para funcionar. */
int rc4_init(rc4_method_t* self, char* key);

/* Metodo de encriptado RC4. Encripta el mensaje de largo especificado y lo
carga en el buffer. */
void rc4_encrypt(rc4_method_t* self, char* msg, size_t msg_len, char* buffer);

/* Metodo de desencriptado RC4. Desencripta el mensaje de largo especificado y lo
carga en el buffer. */
void rc4_decrypt(rc4_method_t* self, char* msg, size_t msg_len, char* buffer);

/* Destructor del metodo RC4. Devuelve 0 en exito. */    
int rc4_destroy(rc4_method_t* self);

#endif  // RC4_METHOD_H
