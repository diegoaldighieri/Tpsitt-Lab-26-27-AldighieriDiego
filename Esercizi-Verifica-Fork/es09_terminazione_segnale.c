// * Esercizio 9 - Terminazione normale o tramite segnale
// * Traccia: il padre crea 3 figli. Il primo termina con exit(7), il secondo con abort(),
// * il terzo si auto-uccide con SIGKILL. Il padre, per ognuno, stampa se è terminato
// * normalmente (e con che codice) oppure per un segnale (e quale).
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define N_FIGLI 3

int main(void)
{
    pid_t figli[N_FIGLI];

    for (int i = 0; i < N_FIGLI; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            return 1;
        }

        if (pid == 0) {
            if (i == 0) {
                exit(7);
            } else if (i == 1) {
                abort();                    // * invia SIGABRT a se stesso
            } else {
                kill(getpid(), SIGKILL);    // * SIGKILL non si può ignorare né gestire
            }
            exit(0);                        // * non ci arriva mai
        }

        figli[i] = pid;
    }

    for (int i = 0; i < N_FIGLI; i++) {
        int status;
        waitpid(figli[i], &status, 0);

        if (WIFEXITED(status)) {
            printf("[Padre] Figlio %d: terminato normalmente, codice %d\n",
                   (int)figli[i], WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("[Padre] Figlio %d: ucciso dal segnale %d\n",
                   (int)figli[i], WTERMSIG(status));
        }
    }

    printf("[Padre] Per confronto: SIGABRT = %d, SIGKILL = %d\n", SIGABRT, SIGKILL);
    return 0;
}
