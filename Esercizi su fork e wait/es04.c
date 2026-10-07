// * Esercizio 4 - Decisione del Padre in base al valore di ritorno
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define PRIMO 1
#define PARI 2
#define DISPARI 3
#define INPUT_NON_VALIDO 4

int e_primo(int n)
{
    if (n < 2) {
        return 0;
    }
    // * d <= n / d equivale a d * d <= n, ma senza rischio di overflow
    for (int d = 2; d <= n / d; d++) {
        if (n % d == 0) {
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        int numero;

        printf("[Figlio] Inserisci un numero intero: ");
        if (scanf("%d", &numero) != 1) {
            exit(INPUT_NON_VALIDO);
        }

        // * il controllo sul primo va fatto prima: 2 è pari ma deve restituire PRIMO
        if (e_primo(numero)) {
            exit(PRIMO);
        } else if (numero % 2 == 0) {
            exit(PARI);
        } else {
            exit(DISPARI);
        }
    }

    int status;
    wait(&status);

    if (!WIFEXITED(status)) {
        printf("[Padre] Il figlio è terminato in modo anomalo.\n");
        return 1;
    }

    switch (WEXITSTATUS(status)) {
        case PRIMO:
            printf("[Padre] Il numero è primo: è divisibile solo per 1 e per se stesso.\n");
            break;
        case PARI:
            printf("[Padre] Il numero è pari e non primo: è divisibile per 2.\n");
            break;
        case DISPARI:
            printf("[Padre] Il numero è dispari e non primo: ha almeno un divisore dispari.\n");
            break;
        default:
            printf("[Padre] Il figlio non ha ricevuto un numero intero valido.\n");
            break;
    }

    return 0;
}
