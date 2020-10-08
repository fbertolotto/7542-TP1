#include "methods.h"

#define DIC_LENGTH 256

/////////////////////////////////////////////////////////////////////////
void ceaser_encrypt(crypto_t* self) {
    size_t key = (size_t) self->key;
    for (int i=0;i < strlen(self->original);i++) {
        int char_numb = (int) self->original[i];
        self->encrypted[i] = (char) ((char_numb + key) % DIC_LENGTH);
    }
}

void ceaser_decrypt(crypto_t* self) {
    size_t key = (size_t) self->key;
    for (int i=0;i < strlen(self->encrypted);i++) {
        int char_numb = (int) self->encrypted[i];
        self->original[i] = (char) ((char_numb - key) % DIC_LENGTH);
    }
}
/////////////////////////////////////////////////////////////////////////
void vigenere_encrypt(crypto_t* self) {

    char* key = (char*) self->key;
    int char_numb_key;

    for (int i=0;i < strlen(self->original);i++) {

        int char_numb_msg = (int) self->original[i];

        if (i <= strlen(key) - 1) {
            char_numb_key = (int) key[i];
        } else {
            char_numb_key = (int) key[(i % strlen(key))];
        }
        self->encrypted[i] = (char) ((char_numb_msg + char_numb_key) % DIC_LENGTH);
    }

}

void vigenere_decrypt(crypto_t* self) {
    char* key = (char*) self->key;
    int char_numb_key;

    for (int i=0;i < strlen(self->encrypted);i++) {

        int char_numb_msg = (int) self->encrypted[i];

        if (i <= strlen(key) - 1) {
            char_numb_key = (int) key[i];
        } else {
            char_numb_key = (int) key[(i % strlen(key))];
        }
        self->original[i] = (char) ((char_numb_msg - char_numb_key) % DIC_LENGTH);
    }

}

/////////////////////////////////////////////////////////////////////////
void swap(char *s, unsigned int i, unsigned int j) {
    char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}


void rc4_init(char* S,char *key,size_t key_length) {
    int i,j;
    for (i = 0; i < 256; i++)
        S[i] = (char) i;
 
    for (i = j = 0; i < 256; i++) {
        j = (j + key[i % key_length] + S[i]) & 255;
        swap(S, i, j);
    }
}

void rc4_encrypt(crypto_t* self) {

    char* S = malloc(sizeof(char)*256);
    int i = 0, j = 0;
    char* key = (char*) self->key;

    rc4_init(S,key,strlen(key));


    for (int y = 0; y < strlen(self->original);y++) {
        i = (i + 1) & 255;
        j = (j + S[i]) & 255;
        swap(S, i, j);
        char value = S[(S[i] + S[j]) & 255];
        //printf("%02X", (self->original[y] ^ value) & 0xff );
        self->encrypted[y] = self->original[y] ^ value;
    }
    free(S);

}

void rc4_decrypt(crypto_t* self) {

    char* S = malloc(sizeof(char)*256);
    int i = 0, j = 0;
    char* key = (char*) self->key;

    rc4_init(S,key,strlen(key));


    for (int y = 0; y < strlen(self->encrypted);y++) {
        i = (i + 1) & 255;
        j = (j + S[i]) & 255;
        swap(S, i, j);
        char value = S[(S[i] + S[j]) & 255];
        //printf("%02X", (self->original[y] ^ value) & 0xf );
        self->original[y] = self->encrypted[y] ^ value;
    }
    free(S);

}