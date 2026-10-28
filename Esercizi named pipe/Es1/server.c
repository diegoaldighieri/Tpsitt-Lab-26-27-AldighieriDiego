#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      // * per open() e O_RDONLY
#include <sys/stat.h>   // * per mkfifo()
#include <unistd.h>     // * per read(), close(), unlink()
#include <errno.h>      // * per errno e EEXIST

#define FIFO_PATH "/tmp/fifo_echo"
#define BUF_SIZE  256

int main() {
    // * 1. Crea la FIFO nel filesystem
    if (mkfifo(FIFO_PATH, 0666) == -1) {
        if (errno != EEXIST) {
            perror("Errore mkfifo");
            exit(EXIT_FAILURE);
        }
    }

    printf("[SERVER] Attendo un client...\n");
    fflush(stdout);

    // * 2. Apre in sola lettura, si blocca finché non c'è un client
    int fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) {
        perror("Errore open server");
        exit(EXIT_FAILURE);
    }

    // * 3. Legge il messaggio e lo stampa
    char buffer[BUF_SIZE];
    ssize_t n = read(fd, buffer, sizeof(buffer));

    if (n > 0)
        printf("[SERVER] %s\n", buffer);
    else if (n == 0)
        printf("[SERVER] Il client ha chiuso senza inviare dati.\n");
    else
        perror("Errore read");

    // * 4. Chiude e rimuove la FIFO
    close(fd);
    if (unlink(FIFO_PATH) == -1)
        perror("Errore unlink");

    return 0;
}
