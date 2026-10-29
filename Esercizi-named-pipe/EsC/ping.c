#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      // * per open()
#include <sys/stat.h>   // * per mkfifo()
#include <unistd.h>     // * per read(), write(), close(), unlink()
#include <string.h>     // * per strlen()
#include <errno.h>      // * per errno e EEXIST

#define FIFO_PING "/tmp/fifo_ping"
#define FIFO_PONG "/tmp/fifo_pong"
#define BUF_SIZE  256

int main() {
    // * 1. Crea entrambe le FIFO
    if (mkfifo(FIFO_PING, 0666) == -1 && errno != EEXIST) {
        perror("Errore mkfifo ping");
        exit(EXIT_FAILURE);
    }
    if (mkfifo(FIFO_PONG, 0666) == -1 && errno != EEXIST) {
        perror("Errore mkfifo pong");
        exit(EXIT_FAILURE);
    }

    printf("[Ping] Attendo pong...\n");
    fflush(stdout);

    // * 2. Apre prima fifo_ping in scrittura e invia PING
    int fd_ping = open(FIFO_PING, O_WRONLY);
    if (fd_ping == -1) {
        perror("Errore open fifo_ping");
        exit(EXIT_FAILURE);
    }
    const char *msg = "PING";
    write(fd_ping, msg, strlen(msg) + 1);
    close(fd_ping);

    // * 3. Poi apre fifo_pong in lettura e aspetta la risposta
    int fd_pong = open(FIFO_PONG, O_RDONLY);
    if (fd_pong == -1) {
        perror("Errore open fifo_pong");
        exit(EXIT_FAILURE);
    }
    char buffer[BUF_SIZE];
    ssize_t n = read(fd_pong, buffer, sizeof(buffer));
    if (n > 0)
        printf("[Ping] Ricevuto: %s\n", buffer);
    else if (n == -1)
        perror("Errore read");
    close(fd_pong);

    // * 4. Rimuove entrambe le FIFO
    if (unlink(FIFO_PING) == -1)
        perror("Errore unlink ping");
    if (unlink(FIFO_PONG) == -1)
        perror("Errore unlink pong");

    return 0;
}
