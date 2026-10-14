#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(){

    int fd[2] = pipe();
    if (pipe(fd) == -1) {
        fprintf(stderr, "Error pipe");
        exit(-1);
    }
    pid_t ritorno = fork();
    if(ritorno == -1){
        fprintf(stderr, "Error fork");
        exit(-2);
    }

    if(!ritorno){

        close(fd[0]);

        char msg[] = "Ciao boateng";
        write(fd[1], msg, sizeof(msg));


        close(fd[1]);
        exit(0);
    }

    close(fd[1]);

    int buffer;
    int bytes_letti = read(fd[0], &buffer, sizeof(buffer)); // * Il read ritorna un intero
    printf("%d", buffer);

    close(fd[0]);
}