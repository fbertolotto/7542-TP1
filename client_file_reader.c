#include "client_file_reader.h"

#define DATA_LEN 1
#define BUFFER_SIZE 64

int file_reader_init(file_reader_t* self) {
  self->file = stdin;
  return 0;
}

/*
Returns != 0 if the file is not over yet.
Returns 0 if the file is over.
*/
int file_reader_read(file_reader_t* self, char* buffer, int buf_len) {
  memset(buffer, 0, buf_len);
  if (feof(self->file)) return 0;
  return fread(buffer, DATA_LEN, BUFFER_SIZE, self->file);
}

int file_reader_destroy(file_reader_t* self) {
  return 0;
}
