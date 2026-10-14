#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 100

struct Messaggio {
    char testo[MAX];
    int vocali;
};

int main(void) {
    int pipe1[2];
    int pipe2[2];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(-1);
    }

    pid_t ritorno_fork = fork();
    if (ritorno_fork == -1) {
        perror("fork");
        exit(-2);
    }

    if (ritorno_fork == 0) {
        close(pipe1[1]);
        close(pipe2[0]);

        char testo[MAX];
        read(pipe1[0], testo, sizeof(testo));
        close(pipe1[0]);

        struct Messaggio m;
        m.vocali = 0;
        for (int i = 0; testo[i] != '\0'; i++) {
            testo[i] = toupper(testo[i]);
            if (testo[i] == 'A' || testo[i] == 'E' || testo[i] == 'I' || testo[i] == 'O' || testo[i] == 'U') {
                m.vocali++;
            }
        }
        strcpy(m.testo, testo);

        write(pipe2[1],&m, sizeof(m));
        close(pipe2[1]);
        exit(0);
    }

    close(pipe1[0]);
    close(pipe2[1]);

    char testo[MAX];
    printf("Inserisci una stringa: ");
    fgets(testo, sizeof(testo), stdin);

    write(pipe1[1], testo, strlen(testo) + 1);
    close(pipe1[1]);

    struct Messaggio risposta;
    read(pipe2[0], &risposta, sizeof(risposta));
    close(pipe2[0]);

    wait(NULL);

    printf("Stringa maiuscola: %s", risposta.testo);
    printf("Numero di vocali: %d\n", risposta.vocali);
    return 0;
}