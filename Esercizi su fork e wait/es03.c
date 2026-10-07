// * Esercizio 3 - Catena di processi (Nonno -> Padre -> Nipote)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    printf("[Nonno] PID: %d\n", (int)getpid());

    pid_t pid_padre = fork();

    if (pid_padre < 0) {
        perror("fork");
        return 1;
    }

    if (pid_padre == 0) {
        printf("[Padre] PID: %d, genitore: %d\n", (int)getpid(), (int)getppid());

        // * il Padre, a sua volta, genera il Nipote
        pid_t pid_nipote = fork();

        if (pid_nipote < 0) {
            perror("fork");
            exit(1);
        }

        if (pid_nipote == 0) {
            printf("[Nipote] PID: %d, genitore: %d\n", (int)getpid(), (int)getppid());
            printf("[Nipote] Termino.\n");
            exit(0);
        }

        wait(NULL);
        printf("[Padre] Il Nipote ha terminato, termino anch'io.\n");
        exit(0);
    }

    wait(NULL);
    printf("[Nonno] Il Padre ha terminato, termino anch'io.\n");

    return 0;
}
