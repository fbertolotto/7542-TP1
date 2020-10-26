#ifndef CEASER_METHOD_H
#define CEASER_METHOD_H

#include <stdio.h>

typedef struct ceaser_method {
  size_t key;
} ceaser_method_t;

/* Inicialiazdor del metodo Cesar. Devuelve 0 en exito. Recibe la clave
 necesaria para funcionar. */
int ceaser_init(ceaser_method_t* self, char* key);

/* Metodo de encriptado Cesar. Encripta el mensaje de largo especificado y lo
carga en el buffer. */
void ceaser_encrypt(ceaser_method_t* self, char* msg, size_t msg_len,
                    char* buffer);

/* Metodo de desencriptado Cesar. Desencripta el mensaje de largo especificado
y lo carga en el buffer. */
void ceaser_decrypt(ceaser_method_t* self, char* msg, size_t msg_len,
                    char* buffer);

/* Destructor del metodo Cesar. Devuelve 0 en exito. */    
int ceaser_destroy(ceaser_method_t* self);

#endif  // CEASER_METHOD_H
