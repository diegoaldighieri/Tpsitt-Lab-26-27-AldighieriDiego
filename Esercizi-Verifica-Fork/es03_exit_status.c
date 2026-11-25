// * Esercizio 3 - N figli che restituiscono un risultato con exit
// * Traccia: il padre crea N_FIGLI figli. Il figlio i-esimo calcola (i+1)! e lo restituisce
// * come codice di uscita. Il padre, con waitpid, raccoglie i risultati NELL'ORDINE di creazione.
// * Poi prova con N_FIGLI 6: perché 6! risulta 208 invece di 720?
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define N_FIGLI 5

int fattoriale(int n)
{
    int risultato = 1;
    for (int i = 2; i <= n; i++) {
        risultato *= i;
    }
    return risultato;
}

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
            int n = i + 1;
            int risultato = fattoriale(n);
            printf("[Figlio %d] calcolo %d! = %d\n", (int)getpid(), n, risultato);
            // * il codice di uscita vale solo 8 bit (0-255): 720 diventa 720 % 256 = 208
            exit(risultato);
        }

        figli[i] = pid;
    }

    for (int i = 0; i < N_FIGLI; i++) {
        int status;
        // * waitpid aspetta proprio QUEL figlio, così so a quale n corrisponde il risultato
        waitpid(figli[i], &status, 0);

        if (WIFEXITED(status)) {
            printf("[Padre] %d! = %d (dal figlio %d)\n", i + 1, WEXITSTATUS(status), (int)figli[i]);
        } else {
            printf("[Padre] Il figlio %d è terminato in modo anomalo\n", (int)figli[i]);
        }
    }

    return 0;
}
