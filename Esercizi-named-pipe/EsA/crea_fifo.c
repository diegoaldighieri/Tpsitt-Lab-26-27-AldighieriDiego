#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>   // * per mkfifo()
#include <unistd.h>     // * per sleep() e unlink()
#include <errno.h>      // * per errno e EEXIST

#define FIFO_PATH "/tmp/fifo_test"

int main() {
    // * 1. Crea la FIFO, se esiste già va avanti
    if (mkfifo(FIFO_PATH, 0666) == -1) {
        if (errno != EEXIST) {
            perror("Errore mkfifo");
            exit(EXIT_FAILURE);
        }
        printf("La FIFO esiste già\n");
    }

    // * 2. Stampa il percorso e aspetta per controllare con ls -l
    printf("FIFO: %s\n", FIFO_PATH);
    fflush(stdout);
    sleep(10);

    // * 3. Rimuove la FIFO dal filesystem
    if (unlink(FIFO_PATH) == -1)
        perror("Errore unlink");

    return 0;
}
