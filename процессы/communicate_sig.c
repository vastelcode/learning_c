// Коммуникация между процессами с использованием сигналов
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define _POSIX_C_SOURCE 200809L   // для современных POSIX-функций

int x = 0;

void handle_sigusr1(int signal)
{
	if(x == 0) printf("\n May be valid answer will be 15 ? Don`t know... \n");
}

int main(int argc, char *argv[])
{
	int pid = fork();

	if(pid < 0) {
		printf("Ошибка вызова fork()\n");
		return 1;
	}

	if(pid == 0) {
		sleep(5);
		kill(getppid(),SIGUSR1);
	}
	else {

		// регистируем обработчик сигнала
		struct sigaction sa;
		sa.sa_handler = &handle_sigusr1;
		sa.sa_flags = SA_RESTART;
		sigaction(SIGUSR1,&sa,NULL);

		printf("What is the result 3 x 5 ? ");
		scanf("%d",&x);

		kill(pid,SIGKILL);

		if(x == 15) {
			printf("It is true !\n");
		}
		else {
			printf("It is false !\n");
		}

		wait(NULL);
	}

	return 0;
}