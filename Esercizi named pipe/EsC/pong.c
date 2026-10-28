#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      // * per open()
#include <unistd.h>     // * per read(), write(), close()
#include <string.h>     // * per strlen()

#define FIFO_PING "/tmp/fifo_ping"
#define FIFO_PONG "/tmp/fifo_pong"
#define BUF_SIZE  256

int main() {
    printf("[Pong] Attendo ping...\n");
    fflush(stdout);

    // * 1. Apre prima fifo_ping in lettura (le FIFO le crea ping)
    int fd_ping = open(FIFO_PING, O_RDONLY);
    if (fd_ping == -1) {
        perror("Errore open fifo_ping");
        exit(EXIT_FAILURE);
    }
    char buffer[BUF_SIZE];
    ssize_t n = read(fd_ping, buffer, sizeof(buffer));
    if (n > 0)
        printf("[Pong] Ricevuto: %s\n", buffer);
    else if (n == -1)
        perror("Errore read");
    close(fd_ping);

    // * 2. Poi apre fifo_pong in scrittura e risponde PONG
    int fd_pong = open(FIFO_PONG, O_WRONLY);
    if (fd_pong == -1) {
        perror("Errore open fifo_pong");
        exit(EXIT_FAILURE);
    }
    const char *msg = "PONG";
    write(fd_pong, msg, strlen(msg) + 1);
    close(fd_pong);

    return 0;
}
