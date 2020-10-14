#include "common_network.h"
#include "socket.h"
#include "crypto.h"
#include "file_reader.h"

static int start_connection(socket_t* client) {
    struct addrinfo cl_hints, *results;
    set_net_flags(&cl_hints);
    get_system_info(&cl_hints, &results, "localhost");
    socket_connect(client, results);
    freeaddrinfo(results);
    return 0;
}

static int send_to_sv(socket_t* client, char* msg, size_t msg_len) {
    int i = 0;
    while (i != msg_len) {
        int bytes = socket_send(client, msg, msg_len);
        if (bytes == -1) return 1;
        i += bytes;
    }
    return 0;
}

static int start_program(socket_t* client, crypto_t* crypto,
                        file_reader_t* fr) {
    int error = 1;
    char msg_buf[CHUNK], crypto_buf[CHUNK];
    while (file_reader_read(fr, msg_buf, CHUNK)) {
        crypto_encrypt(crypto, msg_buf, strlen(msg_buf), crypto_buf, CHUNK);
        error = send_to_sv(client, crypto_buf, strlen(crypto_buf));
    }
    return error;
}

int main() {
    socket_t client;
    crypto_t crypto;
    file_reader_t fr;
    size_t key = 5;
    start_connection(&client);
    int file_r = file_reader_init(&fr, NULL);
    int crypto_r = crypto_init(&crypto, (void*) key, "ceaser");

    if (file_r || crypto_r) {
        socket_destroy(&client);
        file_reader_destroy(&fr);
    }
    return start_program(&client, &crypto, &fr);
}
