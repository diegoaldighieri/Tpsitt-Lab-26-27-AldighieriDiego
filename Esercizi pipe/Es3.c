#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main() {
    int pipe1[2];
    int pipe2[2];
    pipe(pipe1);
    pipe(pipe2);

    pid_t pidB = fork();
    if (pidB == 0) {
        close(pipe1[1]);
        close(pipe2[0]);
        int n;

        while (read(pipe1[0],&n, sizeof(n)) > 0) {
            if (n >= 50) {
                int quadrato = n*n;
                write(pipe2[1], &quadrato, sizeof(quadrato));
            }
        }

        close(pipe1[0]);
        close(pipe2[1]);
        exit(0);
    }

    pid_t pidC = fork();
    if (pidC == 0) {
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[1]);
        int q;
        int somma = 0;
        int conta = 0;
        while (read(pipe2[0], &q, sizeof(q)) > 0) {
            printf("C ha ricevuto: %d\n", q);
            somma += q;
            conta++;
        }
        close(pipe2[0]);
        printf("Media: %.2f\n", (double) somma / conta);
        exit(0);
    }
    close(pipe1[0]);
    close(pipe2[0]);
    close(pipe2[1]);

    srand(time(NULL));
    for (int i = 0; i < 20; i++) {
        int n = rand() % 100 + 1;
        write(pipe1[1], &n, sizeof(n));
    }
    close(pipe1[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}