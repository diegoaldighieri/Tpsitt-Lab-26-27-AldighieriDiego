// * Esercizio 4 - Ordine di creazione vs ordine di terminazione
// * Traccia: il padre crea 3 figli che dormono rispettivamente 3, 1 e 2 secondi.
// * Usando wait (non waitpid), il padre stampa in che ordine terminano e a quale figlio
// * corrisponde ogni PID restituito.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define N_FIGLI 3

int main(void)
{
    int durate[N_FIGLI] = {3, 1, 2};
    pid_t figli[N_FIGLI];

    for (int i = 0; i < N_FIGLI; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            return 1;
        }

        if (pid == 0) {
            printf("[Figlio #%d] PID: %d, dormo %d s\n", i + 1, (int)getpid(), durate[i]);
            sleep(durate[i]);
            exit(i + 1);
        }

        figli[i] = pid;
    }

    for (int k = 0; k < N_FIGLI; k++) {
        int status;
        pid_t terminato = wait(&status);

        // * cerco il PID nell'array per sapere quale figlio è (si poteva usare anche WEXITSTATUS)
        for (int i = 0; i < N_FIGLI; i++) {
            if (figli[i] == terminato) {
                printf("[Padre] %d° a terminare: figlio #%d (PID %d, durata %d s, exit %d)\n",
                       k + 1, i + 1, (int)terminato, durate[i], WEXITSTATUS(status));
            }
        }
    }

    return 0;
}
