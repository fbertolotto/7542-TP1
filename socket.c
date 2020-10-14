#include "socket.h"
#include <stdio.h>

static int socket_starter(socket_t* self, struct addrinfo* datas) {
    struct addrinfo* data;
    int file_d;
    for (data = datas; data != NULL; data = data->ai_next) {
        file_d = socket(data->ai_family, data->ai_socktype, data->ai_protocol);
        if (file_d != -1) {break;}
    }
    return file_d;
}

int socket_init(socket_t* self, struct addrinfo* info) {
    self->info = info;
    int file_d = socket_starter(self, info);

    if (file_d != -1) {
        self->file_d = file_d;
    } else {
        return -1;
    }
    int val = 1;
    setsockopt(self->file_d, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    return 0;
}

int socket_bind(socket_t* self) {
    bind(self->file_d, self->info->ai_addr, self->info->ai_addrlen);
    return 0;
}

int socket_listen(socket_t* self, int queue) {
    listen(self->file_d, queue);
    return 0;
}
int socket_accept(socket_t* self, socket_t* new) {
    struct sockaddr adrr;
    socklen_t adrrlen = (socklen_t) sizeof(adrr);
    new->file_d = accept(self->file_d, &adrr, &adrrlen);
    return new->file_d;
}

int socket_connect(socket_t* self, struct addrinfo* servers) {
    struct addrinfo* sv;
    int connected = -1;
    for (sv = servers; sv != NULL; sv = sv->ai_next) {
        if (socket_init(self, sv) == 0) {
            connected = connect(self->file_d, sv->ai_addr, sv->ai_addrlen);
            if (connected != -1) { break;}
        }
    }
    return connected;
}

int socket_send(socket_t* self, char* msg, int len) {
    return send(self->file_d, msg, len, MSG_NOSIGNAL);
}

int socket_recv(socket_t* self, char* buffer, size_t buffer_len) {
    int bytes = recv(self->file_d, buffer, buffer_len, 0);
    return bytes;
}

int socket_destroy(socket_t* self) {
    close(self->file_d);
    return 0;
}



