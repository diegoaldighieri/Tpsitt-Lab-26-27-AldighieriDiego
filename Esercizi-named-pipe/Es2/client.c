#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      // * per open() e O_WRONLY
#include <unistd.h>     // * per write() e close()
#include <string.h>     // * per strcmp() e strcspn()
#include <errno.h>      // * per errno e EPIPE
#include <signal.h>     // * per signal() e SIGPIPE

#define FIFO_PATH "/tmp/fifo_echo"
#define BUF_SIZE  256

int main() {
    // * Ignora SIGPIPE: la write() restituirà -1 invece di far crashare
    signal(SIGPIPE, SIG_IGN);

    printf("[Client] Attendo il server...\n");
    fflush(stdout);

    // * 1. Apre in sola scrittura (la FIFO la crea il server)
    int fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) {
        perror("Errore open client");
        exit(EXIT_FAILURE);
    }

    // * 2. Invia righe finché non si scrive QUIT
    char buffer[BUF_SIZE];
    while (1) {
        printf("Messaggio: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
            break;
        buffer[strcspn(buffer, "\n")] = '\0';

        // * invia sempre BUF_SIZE byte così ogni read riceve un messaggio intero
        if (write(fd, buffer, sizeof(buffer)) == -1) {
            if (errno == EPIPE)
                fprintf(stderr, "Nessun reader: canale chiuso.\n");
            else
                perror("Errore write");
            break;
        }
        if (strcmp(buffer, "QUIT") == 0)
            break;
    }

    // * 3. Chiude il file descriptor
    close(fd);
    return 0;
}
