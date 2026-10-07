// * Esercizio 2 - Gestione di N figli in parallelo
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define N_FIGLI 3

int main(void)
{
    for (int i = 0; i < N_FIGLI; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            return 1;
        }

        if (pid == 0) {
            printf("[Figlio %d] PID: %d\n", i + 1, (int)getpid());
            sleep(2);
            // * senza exit il figlio continuerebbe il ciclo creando altri processi
            exit(0);
        }
    }

    // * una wait per ogni figlio: l'ordine di terminazione non è garantito
    for (int i = 0; i < N_FIGLI; i++) {
        pid_t terminato = wait(NULL);
        printf("[Padre] Il figlio %d ha terminato\n", (int)terminato);
    }

    printf("[Padre] Tutti i %d figli hanno terminato, chiudo.\n", N_FIGLI);
    return 0;
}
