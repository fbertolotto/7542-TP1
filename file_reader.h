#ifndef FILE_READER
#define FILE_READER

#include <stdio.h>
#include <string.h>

typedef struct file_reader {
    FILE* file;
} file_reader_t;

int file_reader_init(file_reader_t* self, const char* file_name);
int file_reader_read(file_reader_t* self, char* buffer, size_t buffer_len);
int file_reader_destroy(file_reader_t* self);

#endif
