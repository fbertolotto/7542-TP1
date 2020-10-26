#ifndef VIGENERE_METHOD_H
#define VIGENERE_METHOD_H

#include <stdio.h>

typedef struct vigenere_method {
  char* key;
  size_t iteration;
} vigenere_method_t;

/* Inicialiazdor del metodo Vigenere. Devuelve 0 en exito. Recibe la clave
 necesaria para funcionar. */
int vigenere_init(vigenere_method_t* self, char* key);

/* Metodo de encriptado Vigenere. Encripta el mensaje de largo especificado
y lo carga en el buffer. */
void vigenere_encrypt(vigenere_method_t* self, char* msg, size_t msg_len,
                      char* buffer);

/* Metodo de desencriptado Vigenere. Desencripta el mensaje de largo especificado 
y lo carga en el buffer. */
void vigenere_decrypt(vigenere_method_t* self, char* msg, size_t msg_len,
                      char* buffer);

/* Destructor del metodo RC4. Devuelve 0 en exito. */    
int vigenere_destroy(vigenere_method_t* self);

#endif  // VIGENERE_METHOD_H
