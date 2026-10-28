#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      // * per open() e O_WRONLY
#include <unistd.h>     // * per write() e close()
#include <string.h>     // * per strlen() e strcspn()

#define FIFO_PATH "/tmp/fifo_echo"
#define BUF_SIZE  256

int main() {
    // * 1. Legge una riga da tastiera (la FIFO la crea il server)
    char buffer[BUF_SIZE];
    printf("Messaggio: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        exit(EXIT_FAILURE);
    buffer[strcspn(buffer, "\n")] = '\0';   // * toglie l'invio

    // * 2. Apre in sola scrittura
    int fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) {
        perror("Errore open client");
        exit(EXIT_FAILURE);
    }

    // * 3. Invia il messaggio (terminatore incluso) e chiude
    write(fd, buffer, strlen(buffer) + 1);
    close(fd);

    return 0;
}
