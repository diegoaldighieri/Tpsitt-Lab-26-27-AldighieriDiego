// * Esercizio 5 - Attesa non bloccante con WNOHANG
// * Traccia: il figlio conta fino a 5 (un numero al secondo). Il padre NON si blocca:
// * ogni secondo controlla con waitpid(..., WNOHANG) se il figlio ha finito e intanto
// * stampa "sto facendo altro". Quando il figlio termina, il padre stampa il suo codice di uscita.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        for (int i = 1; i <= 5; i++) {
            printf("[Figlio] %d\n", i);
            sleep(1);
        }
        exit(42);
    }

    int status;
    pid_t r;

    // * waitpid con WNOHANG restituisce 0 se il figlio è ancora vivo, il suo PID se ha terminato
    while ((r = waitpid(pid, &status, WNOHANG)) == 0) {
        printf("[Padre] Il figlio lavora ancora, intanto faccio altro...\n");
        sleep(1);
    }

    if (r < 0) {
        perror("waitpid");
        return 1;
    }

    if (WIFEXITED(status)) {
        printf("[Padre] Il figlio ha terminato con codice %d\n", WEXITSTATUS(status));
    }

    return 0;
}
