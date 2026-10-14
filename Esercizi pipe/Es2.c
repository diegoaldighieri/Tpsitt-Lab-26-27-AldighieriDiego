#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

struct Messaggio {
    char *testo;
    int vocali;
};

int main() {
    int pipe1[2];
    int pipe2[2];
    char testo[100] = "";

    pipe(pipe1);
    pipe(pipe2);

    pid_t ritorno_fork = fork();

    if (ritorno_fork == 0) {
        read(pipe1[0], testo, sizeof(testo));

        struct Messaggio m;
        m.vocali = 0;
        for (int i = 0; testo[i] != '\0'; i++) {
            testo[i] = toupper(testo[i]);
            if (testo[i] == 'a' || testo[i] == 'e' || testo[i] == 'i' ||
                testo[i] == 'o' || testo[i] == 'u') {
                m.vocali++;
            }
        }

        m.testo = testo;
        write(pipe2[1], &m, sizeof(m));
        exit(0);
    }

    printf("Inserisci una stringa: ");
    scanf("%s", testo);

    write(pipe1[1], testo, strlen(testo));

    struct Messaggio risposta;
    read(pipe2[0], &risposta, sizeof(risposta));

    printf("Stringa maiuscola:%s\n", risposta.testo);
    printf("Numero di vocali:%d\n", risposta.vocali);
    return 0;
}