#include "common_methods.h"

#define DIC_LENGTH 256

void ceaser_encrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer) {
    int i = 0;
    size_t key = (size_t) atoi((char*) self->key);
    for (; i < msg_len; i++) {
        int char_numb = (int) msg[i];
        buffer[i] = (char) ((char_numb + key) % DIC_LENGTH);
    }
}

void ceaser_decrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer) {
    int i = 0;
    size_t key = (size_t) atoi((char*) self->key);
    for (; i < msg_len; i++) {
        int char_numb = (int) msg[i];
        buffer[i] = (char) ((char_numb - key) % DIC_LENGTH);
    }
}

void vigenere_encrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer) {
    char* key = (char*) self->key;
    int char_numb_key;
    int i = 0;
    for (; i < msg_len; i++) {
        int char_numb_msg = (int) msg[i];
        if (i <= strlen(key) - 1) {
            char_numb_key = (int) key[i];
        } else {
            char_numb_key = (int) key[(i % strlen(key))];
        }
        buffer[i] = (char) ((char_numb_msg + char_numb_key) % DIC_LENGTH);
    }
}

void vigenere_decrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer) {
    char* key = (char*) self->key;
    int char_numb_key;
    for (int i=0; i < msg_len; i++) {
        int char_numb_msg = (int) msg[i];
        if (i <= strlen(key) - 1) {
            char_numb_key = (int) key[i];
        } else {
            char_numb_key = (int) key[(i % strlen(key))];
        }
        buffer[i] = (char) ((char_numb_msg - char_numb_key) % DIC_LENGTH);
    }
}

void swap(char *s, unsigned int i, unsigned int j) {
    char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

void rc4_init(char* S, char *key, size_t key_length) {
    int i, j;
    for (i = 0; i < 256; i++)
        S[i] = (char) i;
    for (i = j = 0; i < 256; i++) {
        j = (j + key[i % key_length] + S[i]) & 255;
        swap(S, i, j);
    }
}

void rc4_encrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer) {
    char S[256];
    int i = 0, j = 0, y = 0;
    char* key = (char*) self->key;
    rc4_init(S, key, strlen(key));
    for (; y < msg_len; y++) {
        i = (i + 1) & 255;
        j = (j + S[i]) & 255;
        swap(S, i, j);
        char value = S[(S[i] + S[j]) & 255];
        buffer[y] = msg[y] ^ value;
    }
}

void rc4_decrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer) {
    rc4_encrypt(self, msg, msg_len, buffer);
}
