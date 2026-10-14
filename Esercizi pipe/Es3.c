#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int pipe1[2];
    int pipe2[2];
    pipe(pipe1);
    pipe(pipe2);

    pid_t pidB = fork();
    if (pidB == 0) {
        int n;
        while (read(pipe1[0], &n, sizeof(n)) > 0) {
            if (n >= 50) {
                int quadrato = n*n;
                write(pipe2[1], &quadrato, sizeof(quadrato));
            }
        }
        exit(0);
    }

    pid_t pidC = fork();
    if (pidC == 0) {
        int q;
        int somma = 0;
        int conta = 0;
        while (read(pipe2[0], &q, sizeof(q)) > 0) {
            printf("C ha ricevuto: %d\n", q);
            somma += q;
            conta++;
        }
        printf("Media:%d\n", somma / conta);
        exit(0);
    }
    for (int i = 0; i < 20; i++) {
        int n = rand() % 100;
        write(pipe1[1], &n, sizeof(n));
    }
    wait(NULL);
    return 0;
}