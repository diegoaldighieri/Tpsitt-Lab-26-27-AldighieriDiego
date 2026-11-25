// * Esercizio 2 - Memoria separata tra padre e figlio
// * Traccia: il figlio modifica una variabile globale, una locale e una allocata con malloc.
// * Il padre, dopo la wait, stampa le stesse variabili. Cosa vede? Gli indirizzi sono uguali?
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int globale = 10;

int main(void)
{
    int locale = 20;
    int *dinamica = malloc(sizeof(int));
    if (dinamica == NULL) {
        perror("malloc");
        return 1;
    }
    *dinamica = 30;

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        free(dinamica);
        return 1;
    }

    if (pid == 0) {
        globale += 1;
        locale += 1;
        *dinamica += 1;
        printf("[Figlio] globale=%d locale=%d dinamica=%d (indirizzo dinamica: %p)\n",
               globale, locale, *dinamica, (void *)dinamica);
        free(dinamica);
        exit(0);
    }

    wait(NULL);

    // * stesso indirizzo (virtuale) ma valori diversi: dopo la fork ognuno ha la SUA copia della memoria
    printf("[Padre]  globale=%d locale=%d dinamica=%d (indirizzo dinamica: %p)\n",
           globale, locale, *dinamica, (void *)dinamica);

    free(dinamica);
    return 0;
}
