// * Esercizio 10 - Simulazione di verifica
// * Traccia: il padre legge una frase da tastiera, poi crea DUE figli.
// *   - il primo figlio conta le vocali e restituisce il numero con exit
// *   - il secondo figlio conta le consonanti e lo invia al padre tramite pipe
// * Il padre aspetta entrambi, recupera i due risultati e stampa il riepilogo.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 256

int e_vocale(char c)
{
    c = (char)tolower((unsigned char)c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main(void)
{
    char frase[MAX];
    int fd[2];

    printf("Inserisci una frase: ");
    fflush(stdout);
    if (fgets(frase, MAX, stdin) == NULL) {
        printf("Errore di lettura\n");
        return 1;
    }
    frase[strcspn(frase, "\n")] = '\0';

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    // * primo figlio: vocali tramite exit (va bene perché sono al massimo 255 caratteri)
    pid_t pid_vocali = fork();
    if (pid_vocali < 0) {
        perror("fork");
        return 1;
    }
    if (pid_vocali == 0) {
        close(fd[0]);
        close(fd[1]);   // * questo figlio non usa la pipe
        int vocali = 0;
        for (int i = 0; frase[i] != '\0'; i++) {
            if (e_vocale(frase[i])) {
                vocali++;
            }
        }
        exit(vocali);
    }

    // * secondo figlio: consonanti tramite pipe
    pid_t pid_consonanti = fork();
    if (pid_consonanti < 0) {
        perror("fork");
        return 1;
    }
    if (pid_consonanti == 0) {
        close(fd[0]);
        int consonanti = 0;
        for (int i = 0; frase[i] != '\0'; i++) {
            if (isalpha((unsigned char)frase[i]) && !e_vocale(frase[i])) {
                consonanti++;
            }
        }
        write(fd[1], &consonanti, sizeof(consonanti));
        close(fd[1]);
        exit(0);
    }

    close(fd[1]);

    int consonanti;
    if (read(fd[0], &consonanti, sizeof(consonanti)) != sizeof(consonanti)) {
        perror("read");
        return 1;
    }
    close(fd[0]);

    int status;
    waitpid(pid_vocali, &status, 0);
    int vocali = WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    waitpid(pid_consonanti, NULL, 0);

    printf("[Padre] Frase: \"%s\"\n", frase);
    printf("[Padre] Vocali (figlio %d, via exit): %d\n", (int)pid_vocali, vocali);
    printf("[Padre] Consonanti (figlio %d, via pipe): %d\n", (int)pid_consonanti, consonanti);

    return 0;
}
