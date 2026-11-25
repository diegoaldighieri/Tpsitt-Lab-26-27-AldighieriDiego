// * Esercizio 7 - Il buffer di printf viene copiato dalla fork
// * Traccia: prevedi l'output, poi eseguilo. Perché "Prima della fork" compare DUE volte?
// * Togli il commento a fflush e riprova. Infine prova anche: ./es07 > out.txt && cat out.txt
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    // * niente \n: il testo resta nel buffer di stdout, che è memoria del processo
    printf("Prima della fork ");
    // fflush(stdout);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    // * il figlio ha una COPIA del buffer ancora pieno: entrambi lo stampano quando lo svuotano
    if (pid == 0) {
        printf("[Figlio]\n");
        exit(0);
    }

    wait(NULL);
    printf("[Padre]\n");

    return 0;
}
