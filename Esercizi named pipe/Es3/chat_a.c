#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      // * per open()
#include <sys/stat.h>   // * per mkfifo()
#include <unistd.h>     // * per read(), write(), close(), unlink()
#include <string.h>     // * per strcmp() e strcspn()
#include <errno.h>      // * per errno e EEXIST

#define FIFO_A_TO_B "/tmp/fifo_a_to_b"
#define FIFO_B_TO_A "/tmp/fifo_b_to_a"
#define BUF_SIZE    256

int main() {
    // * 1. A crea entrambe le FIFO
    if (mkfifo(FIFO_A_TO_B, 0666) == -1 && errno != EEXIST) {
        perror("Errore mkfifo a_to_b");
        exit(EXIT_FAILURE);
    }
    if (mkfifo(FIFO_B_TO_A, 0666) == -1 && errno != EEXIST) {
        perror("Errore mkfifo b_to_a");
        exit(EXIT_FAILURE);
    }

    printf("[A] Attendo B...\n");
    fflush(stdout);

    // * 2. A apre prima in scrittura, poi in lettura (B fa il contrario)
    int fd_write = open(FIFO_A_TO_B, O_WRONLY);
    if (fd_write == -1) {
        perror("Errore open a_to_b");
        exit(EXIT_FAILURE);
    }
    int fd_read = open(FIFO_B_TO_A, O_RDONLY);
    if (fd_read == -1) {
        perror("Errore open b_to_a");
        exit(EXIT_FAILURE);
    }

    // * 3. Scrive, poi aspetta la risposta, finché qualcuno non scrive EXIT
    char buffer[BUF_SIZE];
    while (1) {
        printf("A: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
            break;
        buffer[strcspn(buffer, "\n")] = '\0';
        write(fd_write, buffer, sizeof(buffer));
        if (strcmp(buffer, "EXIT") == 0)
            break;

        if (read(fd_read, buffer, sizeof(buffer)) <= 0)
            break;
        printf("B: %s\n", buffer);
        if (strcmp(buffer, "EXIT") == 0)
            break;
    }

    // * 4. Chiude e rimuove le FIFO
    close(fd_write);
    close(fd_read);
    if (unlink(FIFO_A_TO_B) == -1)
        perror("Errore unlink a_to_b");
    if (unlink(FIFO_B_TO_A) == -1)
        perror("Errore unlink b_to_a");

    return 0;
}
