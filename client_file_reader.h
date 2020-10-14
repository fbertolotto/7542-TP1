#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdio.h>
#include <string.h>

typedef struct file_reader {
    FILE* file;
} file_reader_t;

int file_reader_init(file_reader_t* self);
int file_reader_read(file_reader_t* self, char* buffer, int buf_len);
int file_reader_destroy(file_reader_t* self);

#endif // FILE_READER_H
