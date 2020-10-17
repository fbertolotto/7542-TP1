#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdio.h>
#include <string.h>

typedef struct file_reader {
    FILE* file;
} file_reader_t;

/* Inicializa un lector de archivo de entrada STDIN.
Devuelve 0*/
int file_reader_init(file_reader_t* self);

/* Carga en el buffer lo leído de entrada estándar.
La cantidad es especificada por el largo del buffer.
Ademas para evitar problemas, limpia el buffer antes
de la carga y se reserva la ultima posicion para un 0.
Devuelve la cantidad de bytes que logro
leer y 0 si el archivo termino. */
int file_reader_read(file_reader_t* self, char* buffer, int buf_len);

/* Destruye el lector de archivos. Devuelve 0 */
int file_reader_destroy(file_reader_t* self);

#endif // FILE_READER_H
