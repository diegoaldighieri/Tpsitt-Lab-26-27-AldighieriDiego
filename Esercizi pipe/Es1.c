#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int numeri[10] = {4, -7, 12, 5, -3, 8, 21, -10, 6, 9};
    int fd[2];   // * fd[0] lettura, fd[1] scrittura

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(-1);
    }

    pid_t ritorno_fork = fork();
    if (ritorno_fork == -1) {
        perror("fork");
        exit(-2);
    }

    // * Processo figlio: somma dei pari
    if (ritorno_fork == 0) {
        close(fd[0]);

        int somma_pari = 0;
        for (int i = 0; i < 10; i++) {
            if (numeri[i] % 2 == 0) {
                somma_pari += numeri[i];
            }
        }

        write(fd[1], &somma_pari, sizeof(somma_pari));
        close(fd[1]);
        exit(0);
    }

    // * Processo padre: somma dei dispari
    close(fd[1]);

    int somma_dispari = 0;
    for (int i = 0; i < 10; i++) {
        if (numeri[i] % 2 != 0) {   // * != 0 perché -7 % 2 vale -1
            somma_dispari += numeri[i];
        }
    }

    int somma_pari;
    if (read(fd[0], &somma_pari, sizeof(somma_pari)) <= 0) {
        perror("read");
        exit(-3);
    }
    close(fd[0]);

    wait(NULL);

    printf("Somma pari (figlio):%d\n", somma_pari);
    printf("Somma dispari (padre):%d\n", somma_dispari);
    printf("Somma totale:%d\n", somma_pari + somma_dispari);
    return 0;
}