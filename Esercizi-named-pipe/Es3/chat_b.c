#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      // * per open()
#include <unistd.h>     // * per read(), write(), close()
#include <string.h>     // * per strcmp() e strcspn()

#define FIFO_A_TO_B "/tmp/fifo_a_to_b"
#define FIFO_B_TO_A "/tmp/fifo_b_to_a"
#define BUF_SIZE    256

int main() {
    printf("[B] Attendo A...\n");
    fflush(stdout);

    // * 1. B apre prima in lettura, poi in scrittura (speculare ad A)
    int fd_read = open(FIFO_A_TO_B, O_RDONLY);
    if (fd_read == -1) {
        perror("Errore open a_to_b");
        exit(EXIT_FAILURE);
    }
    int fd_write = open(FIFO_B_TO_A, O_WRONLY);
    if (fd_write == -1) {
        perror("Errore open b_to_a");
        exit(EXIT_FAILURE);
    }

    // * 2. Aspetta il messaggio di A, poi risponde, finché qualcuno non scrive EXIT
    char buffer[BUF_SIZE];
    while (1) {
        if (read(fd_read, buffer, sizeof(buffer)) <= 0)
            break;
        printf("A: %s\n", buffer);
        if (strcmp(buffer, "EXIT") == 0)
            break;

        printf("B: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
            break;
        buffer[strcspn(buffer, "\n")] = '\0';
        write(fd_write, buffer, sizeof(buffer));
        if (strcmp(buffer, "EXIT") == 0)
            break;
    }

    // * 3. Chiude i file descriptor (le FIFO le rimuove A)
    close(fd_read);
    close(fd_write);
    return 0;
}
