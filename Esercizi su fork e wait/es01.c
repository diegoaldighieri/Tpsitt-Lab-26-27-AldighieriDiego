// * Esercizio 1 - Sincronizzazione sequenziale (Padre e Figlio)
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
        exit(0);
    }

    // * il padre resta bloccato qui finché il figlio non termina
    wait(NULL);

    for (int i = 6; i <= 10; i++) {
        printf("[Padre] %d\n", i);
    }

    return 0;
}
