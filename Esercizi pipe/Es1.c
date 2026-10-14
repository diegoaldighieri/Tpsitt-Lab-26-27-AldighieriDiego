#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
	int numeri[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int fd[2];

	if (pipe(fd) == -1) {
		perror("pipe");
		return EXIT_FAILURE;
	}

	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
		close(fd[0]);
		close(fd[1]);
		return EXIT_FAILURE;
	}

	if (pid == 0) {
		close(fd[0]);

		int somma_pari = 0;
		for (int i = 0; i < 10; i++) {
			if (numeri[i] % 2 == 0) {
				somma_pari += numeri[i];
			}
		}

		if (write(fd[1], &somma_pari, sizeof(somma_pari)) != sizeof(somma_pari)) {
			perror("write");
			close(fd[1]);
			_exit(EXIT_FAILURE);
		}

		close(fd[1]);
		_exit(EXIT_SUCCESS);
	}

	close(fd[1]);

	int somma_dispari = 0;
	for (int i = 0; i < 10; i++) {
		if (numeri[i] % 2 != 0) {
			somma_dispari += numeri[i];
		}
	}

	int somma_pari;
	ssize_t letti = read(fd[0], &somma_pari, sizeof(somma_pari));
	close(fd[0]);
	if (letti != sizeof(somma_pari)) {
		perror("read");
		wait(NULL);
		return EXIT_FAILURE;
	}

	wait(NULL);

	printf("Somma dei numeri pari: %d\n", somma_pari);
	printf("Somma dei numeri dispari: %d\n", somma_dispari);
	printf("Somma totale: %d\n", somma_pari + somma_dispari);

	return EXIT_SUCCESS;
}
