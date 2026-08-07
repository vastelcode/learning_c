// Остановка или продолжение процессов с помощью сигналов
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	int pid = fork();

	if(pid == -1) {
		printf("Ошибка вызова fork\n");
		return 1;
	}

	if(pid == 0) {
		while(1) {
			printf("Некоторый текст\n");
			sleep(2);
		}
	}
	else {
		kill(pid,SIGSTOP); // останавливаем дочерний процесс

		int t;

		do {
			
			printf("Time in seconds for execution: ");
			scanf("%d",&t);

			if(t > 0) {
				kill(pid,SIGCONT); // восстанавливаем исполнение процесса
				sleep(t);
				kill(pid,SIGSTOP);
			}
		} while(t > 0);

		kill(pid, SIGKILL);
		wait(NULL);
	}

	return 0;
}