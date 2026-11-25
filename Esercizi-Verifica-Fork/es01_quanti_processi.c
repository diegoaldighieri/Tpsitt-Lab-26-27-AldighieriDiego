// * Esercizio 1 - Quanti processi? (fork in sequenza)
// * Traccia: PRIMA di eseguirlo, prevedi quante righe "[a=.. b=..]" verranno stampate
// * e da quali processi. Poi eseguilo e confronta con la tua previsione.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    printf("[Inizio] PID: %d\n", (int)getpid());
    // * svuoto il buffer, altrimenti la riga sopra potrebbe essere copiata nei figli (vedi es07)
    fflush(stdout);

    pid_t a = fork();   // * 1 processo -> 2 processi
    pid_t b = fork();   // * 2 processi -> 4 processi (anche il figlio della prima fork esegue questa)

    // * a == 0 -> sono figlio della prima fork, b == 0 -> sono figlio della seconda fork
    printf("[a=%d b=%d] PID: %d, genitore: %d\n", (int)a, (int)b, (int)getpid(), (int)getppid());

    // * ogni processo aspetta TUTTI i figli che ha creato: wait restituisce -1 quando non ne ha più
    while (wait(NULL) > 0) {
    }

    return 0;
}
