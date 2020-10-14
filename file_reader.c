#include "file_reader.h"

#define DATA_LEN 1

int file_reader_init(file_reader_t* self, const char* file_name) {
    if (!file_name) {
        self->file = stdin;
        return 0;
    }
    FILE* file_d = fopen(file_name, "rb");
    if (!file_d) return -1;
    else
    {self->file = file_d;}
    return 0;
}

/* 
Returns 1 if the file is not over yet.
Returns 0 if the file is over.
*/
int file_reader_read(file_reader_t* self, char* buffer, int buf_len) {
    memset(buffer, 0, buf_len);
    while (!feof(self->file)) {
        fread(buffer, 64, 1, self->file);
        return 1;
    }
    return 0;
}

int file_reader_destroy(file_reader_t* self) {
    if (self->file != stdin) {
        fclose(self->file);
    }
    return 0;
}
