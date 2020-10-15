#include "common_methods.h"

#define DIC_LENGTH 256

static void ceaser(crypto_t* self, char* msg, size_t msg_len, char* buffer,
                   char* op) {
  int i = 0;
  size_t key = (size_t)atoi((char*)self->key);
  for (; i < msg_len; i++) {
    int char_numb = (int)msg[i];
    if (!strcmp(op, "sum")) {
      buffer[i] = (char)((char_numb + key) % DIC_LENGTH);
    } else {
      buffer[i] = (char)((char_numb - key) % DIC_LENGTH);
    }
  }
}

void ceaser_encrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer) {
  ceaser(self, msg, msg_len, buffer, "sum");
}

void ceaser_decrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer) {
  ceaser(self, msg, msg_len, buffer, "sub");
}

static void vigenere_msg_numb(char c, int* buffer) {
  *buffer = (int)c;
}

static void vigenere_key_numb(char* key, int pos, int len, int* buffer) {
  if (pos <= len) {
    *buffer = (int)key[pos];
  } else {
    *buffer = (int)key[(pos % strlen(key))];
  }
}

static void vigenere(crypto_t* self, char* msg, size_t msg_len, char* buffer,
                     char* op) {
  char* key = (char*)self->key;
  int char_numb_msg;
  int char_numb_key;
  for (int i = 0; i < msg_len; i++) {
    vigenere_msg_numb(msg[i], &char_numb_msg);
    vigenere_key_numb(key, self->pos_i, strlen(key) - 1, &char_numb_key);
    self->pos_i++;
    if (!strcmp(op, "sum")) {
      buffer[i] = (char)((char_numb_msg + char_numb_key) % DIC_LENGTH);
    } else {
      buffer[i] = (char)((char_numb_msg - char_numb_key) % DIC_LENGTH);
    }
  }
}
void vigenere_encrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer) {
  vigenere(self, msg, msg_len, buffer, "sum");
}

void vigenere_decrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer) {
  vigenere(self, msg, msg_len, buffer, "sub");
}

void swap(char* s, unsigned int i, unsigned int j) {
  char temp = s[i];
  s[i] = s[j];
  s[j] = temp;
}

void rc4_init(char* S, void* key_p) {
  char* key = (char*) key_p;
  size_t key_len = strlen(key);
  int i, j;
  for (i = 0; i < 256; i++) S[i] = (char)i;
  for (i = j = 0; i < 256; i++) {
    j = (j + key[i % key_len] + S[i]) & 255;
    swap(S, i, j);
  }
}

void rc4_encrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer) {
  char* S = self->S;
  int* i = &self->pos_i;
  int* j = &self->pos_j;
  int y = 0;
  for (; y < msg_len; y++) {
    *i = (*i + 1) & 255;
    *j = (*j + S[*i]) & 255;
    swap(S, *i, *j);
    char value = S[(S[*i] + S[*j]) & 255];
    buffer[y] = msg[y] ^ value;
  }
}

void rc4_decrypt(crypto_t* self, char* msg, size_t msg_len, char* buffer) {
  rc4_encrypt(self, msg, msg_len, buffer);
}

