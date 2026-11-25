// * Esercizio 6 - Somma parallela di un array con N figli e una pipe
// * Traccia: l'array di DIM numeri viene diviso in N_FIGLI parti uguali. Ogni figlio somma
// * la sua parte e scrive sulla pipe una struct {indice figlio, somma parziale}.
// * Il padre legge le N somme parziali, le stampa e calcola la somma totale.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define DIM 12
#define N_FIGLI 3

typedef struct {
    int indice;
    int somma;
} Parziale;

int main(void)
{
    int numeri[DIM] = {4, -7, 12, 5, -3, 8, 21, -10, 6, 9, 1, 2};
    int fd[2];   // * fd[0] lettura, fd[1] scrittura

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    int porzione = DIM / N_FIGLI;

    for (int i = 0; i < N_FIGLI; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            return 1;
        }

        if (pid == 0) {
            close(fd[0]);

            Parziale p;
            p.indice = i;
            p.somma = 0;
            for (int j = i * porzione; j < (i + 1) * porzione; j++) {
                p.somma += numeri[j];
            }

            // * scritture piccole (<= PIPE_BUF) sono atomiche: i messaggi dei figli non si mescolano
            write(fd[1], &p, sizeof(p));
            close(fd[1]);
            exit(0);
        }
    }

    // * il padre chiude la scrittura, altrimenti read non vedrebbe mai la fine della pipe
    close(fd[1]);

    int totale = 0;
    Parziale p;
    while (read(fd[0], &p, sizeof(p)) == sizeof(p)) {
        printf("[Padre] Figlio %d: somma da numeri[%d] a numeri[%d] = %d\n",
               p.indice, p.indice * porzione, (p.indice + 1) * porzione - 1, p.somma);
        totale += p.somma;
    }
    close(fd[0]);

    while (wait(NULL) > 0) {
    }

    printf("[Padre] Somma totale: %d\n", totale);
    return 0;
}
