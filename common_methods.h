#ifndef METHODS_H
#define METHODS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "common_crypto.h"

/* Metodo de encriptado Cesar. Encripta el mensaje de largo especificado y lo
carga en el buffer. */
void ceaser_encrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer);

/* Metodo de desencriptado Cesar. Desencripta el mensaje de largo especificado
y lo carga en el buffer. */
void ceaser_decrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer);

/* Metodo de encriptado Vigenere. Encripta el mensaje de largo especificado
y lo carga en el buffer. */
void vigenere_encrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer);

/* Metodo de desencriptado Vigenere. Desencripta el mensaje de largo especificado 
y lo carga en el buffer. */
void vigenere_decrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer);

/* Metodo de encriptado RC4. Encripta el mensaje de largo especificado y lo
carga en el buffer. */
void rc4_encrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer);

/* Metodo de desencriptado RC4. Desencripta el mensaje de largo especificado y lo
carga en el buffer. */
void rc4_decrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer);

/* Inicializa el diccionario necesario para el metodo. */
void rc4_init(char* S, char* key);

#endif // METHODS_H
