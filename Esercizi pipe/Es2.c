#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 100

// * Struct richiesta dalla consegna: array e non puntatore
struct Messaggio {
    char testo[MAX];
    int vocali;
};

int main() {
    int pipe1[2];   // * padre al figlio
    int pipe2[2];   // * figlio al padre

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(-1);
    }

    pid_t ritorno_fork = fork();
    if (ritorno_fork == -1) {
        perror("fork");
        exit(-2);
    }

    // * Processo figlio: maiuscolo e conteggio vocali
    if (ritorno_fork == 0) {
        close(pipe1[1]);
        close(pipe2[0]);

        char testo[MAX];
        read(pipe1[0], testo, sizeof(testo));
        close(pipe1[0]);

        struct Messaggio m;
        m.vocali = 0;
        int i = 0;
        while (testo[i] != '\0') {
            m.testo[i] = toupper(testo[i]);
            if (m.testo[i] == 'A' || m.testo[i] == 'E' || m.testo[i] == 'I' || m.testo[i] == 'O' || m.testo[i] == 'U') {
                m.vocali++;
            }
            i++;
        }
        m.testo[i] = '\0';

        write(pipe2[1],&m, sizeof(m));
        close(pipe2[1]);
        exit(0);
    }

    // * Processo padre
    close(pipe1[0]);
    close(pipe2[1]);

    char testo[MAX];
    printf("Inserisci una stringa: ");
    fgets(testo, sizeof(testo), stdin);

    // * Tolgo l'invio finale che fgets lascia nella stringa
    int lunghezza = strlen(testo);
    if (lunghezza > 0 && testo[lunghezza - 1] == '\n') {
        testo[lunghezza - 1] = '\0';
    }

    write(pipe1[1], testo, strlen(testo) + 1);   // * +1 per inviare anche il '\0'
    close(pipe1[1]);

    struct Messaggio risposta;
    read(pipe2[0], &risposta, sizeof(risposta));
    close(pipe2[0]);

    wait(NULL);

    printf("Stringa maiuscola:%s\n", risposta.testo);
    printf("Numero di vocali:%d\n", risposta.vocali);
    return 0;
}