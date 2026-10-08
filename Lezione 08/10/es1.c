#include<unistd.h>

int main(){

    int fd[2] = pipe();
    if (pipe(fd) == -1) {
        fprintf(stderr, "Error pipe");
        exit(-1);
    }
    pid_t ritorno = fork();
    if(ritorno == -1){
        fprintf(stderr, "Error fork");
        exit(-1);
    }

}