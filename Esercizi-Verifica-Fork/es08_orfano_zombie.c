// * Esercizio 8 - Processo orfano e processo zombie
// * Traccia: scegli 1 o 2.
// *   1) ORFANO: il padre termina subito, il figlio stampa getppid() prima e dopo. Cosa cambia?
// *   2) ZOMBIE: il figlio termina subito, il padre dorme 15 s senza fare wait.
// *      Da un altro terminale lancia "ps -l": il figlio compare come <defunct> (stato Z).
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void orfano(void)
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        printf("[Figlio] PID: %d, genitore: %d\n", (int)getpid(), (int)getppid());
        sleep(2);
        // * il padre è morto: il figlio viene "adottato" da init (PID 1) o da un subreaper
        printf("[Figlio] Dopo 2 s il mio genitore è: %d\n", (int)getppid());
        exit(0);
    }

    printf("[Padre] Termino subito senza aspettare il figlio %d\n", (int)pid);
    exit(0);
}

void zombie(void)
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        printf("[Figlio] PID: %d, termino subito\n", (int)getpid());
        exit(0);
    }

    // * finché il padre non fa wait, il figlio resta nella tabella dei processi come zombie
    printf("[Padre] Dormo 15 s senza wait: il figlio %d ora è uno zombie\n", (int)pid);
    sleep(15);

    wait(NULL);
    printf("[Padre] Ho fatto wait: lo zombie è stato rimosso\n");
}

int main(void)
{
    int scelta;

    printf("1) Orfano\n2) Zombie\nScelta: ");
    if (scanf("%d", &scelta) != 1) {
        printf("Input non valido\n");
        return 1;
    }
    fflush(stdout);

    if (scelta == 1) {
        orfano();
    } else if (scelta == 2) {
        zombie();
    } else {
        printf("Scelta non valida\n");
    }

    return 0;
}
