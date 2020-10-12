#include "file_reader.h"

#define DATA_LEN 1

int file_reader_init(file_reader_t* self, const char* file_name) {
    self->file = file_name != NULL ? fopen(file_name, "rb"):stdin;
    return 0;
}

/* 
Returns 1 if the file is not over yet and the buffer is filled.
Returns 0 if the file is over.
*/
int file_reader_read(file_reader_t* self, char* buffer, size_t buffer_len) {
    char temp[1];
    int i = 0;

    while (i < buffer_len) {
        fread(temp, 1, DATA_LEN, self->file);
        if (feof(self->file)) {
            for (; i < buffer_len; i++) buffer[i] = '\0';
            return 0;
        }
        memcpy(&buffer[i], &temp[0], DATA_LEN);
        i++;
    }
    return 1;
}

int file_reader_destroy(file_reader_t* self) {
    if (self->file != stdin) {
        fclose(self->file);
    }
    return 0;
}
