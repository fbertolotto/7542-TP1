#include "methods.h"

#define DIC_LENGTH 256

static void buffer_filler(char* buffer, int pos) {
    pos++;
    for (; pos < MAX_LENGHT; pos++) {
        buffer[pos] = '\0';
    }
}

/////////////////////////////////////////////////////////////////////////
void ceaser_encrypt(crypto_t* self) {
    int i = 0;
    size_t key = (size_t) self->key;
    for (; i < strlen(self->original); i++) {
        int char_numb = (int) self->original[i];
        self->encrypted[i+1] = (char) ((char_numb + key) % DIC_LENGTH);
    }
    self->encrypted[0] = (char) i;
    buffer_filler(self->encrypted, i++);
}

void ceaser_decrypt(crypto_t* self) {
    char buff[50];
    int i = 0;
    size_t key = (size_t) self->key;
    for (; i < strlen(self->encrypted); i++) {
        int char_numb = (int) self->encrypted[i];
        buff[i] = (char) ((char_numb - key) % DIC_LENGTH);
    }
    for (; i < 50; i++) {
        buff[i] = '\0';
    }
    memcpy(self->original, buff, 50);
}

/////////////////////////////////////////////////////////////////////////
void vigenere_encrypt(crypto_t* self) {
    char* key = (char*) self->key;
    int char_numb_key;
    int i = 0;

    for (; i < strlen(self->original); i++) {
        int char_numb_msg = (int) self->original[i];

        if (i <= strlen(key) - 1) {
            char_numb_key = (int) key[i];
        } else {
            char_numb_key = (int) key[(i % strlen(key))];
        }
        self->encrypted[i+1] = (char) ((char_numb_msg + char_numb_key) % DIC_LENGTH);
    }
    self->encrypted[0] = (char) i;
    buffer_filler(self->encrypted, i++);
}

void vigenere_decrypt(crypto_t* self) {
    char* key = (char*) self->key;
    int char_numb_key;

    for (int i=0; i < strlen(self->encrypted); i++) {
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


void rc4_init(char* S, char *key, size_t key_length) {
    int i, j;
    for (i = 0; i < 256; i++)
        S[i] = (char) i;
    for (i = j = 0; i < 256; i++) {
        j = (j + key[i % key_length] + S[i]) & 255;
        swap(S, i, j);
    }
}

void rc4_encrypt(crypto_t* self) {
    char S[256];
    int i = 0, j = 0, y = 0;
    char* key = (char*) self->key;

    rc4_init(S, key, strlen(key));

    for (; y < strlen(self->original); y++) {
        i = (i + 1) & 255;
        j = (j + S[i]) & 255;
        swap(S, i, j);
        char value = S[(S[i] + S[j]) & 255];
        // printf("%02X", (self->original[y] ^ value) & 0xff );
        self->encrypted[y+1] = self->original[y] ^ value;
    }
    self->encrypted[0] = (char) y;
    buffer_filler(self->encrypted, y++);
}

void rc4_decrypt(crypto_t* self) {
    char S[256];
    int i = 0, j = 0;
    char* key = (char*) self->key;

    rc4_init(S, key, strlen(key));

    for (int y = 0; y < strlen(self->encrypted); y++) {
        i = (i + 1) & 255;
        j = (j + S[i]) & 255;
        swap(S, i, j);
        char value = S[(S[i] + S[j]) & 255];
        // printf("%02X", (self->original[y] ^ value) & 0xf );
        self->original[y] = self->encrypted[y] ^ value;
    }
}
