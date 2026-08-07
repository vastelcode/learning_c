// Ввдение в сигналы
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>


int main(int argc, char *argv[])
{
	/*
	Сигналы - ещё один способ взаимодействия между процессами.
	Но в отличие от FIFO или pipe, здесь вы отправляет другому процессу целочисленный код, сообщающий о происхождении
	какого-то события.
	*/

	int pid = fork();

	if(pid < 0) {
		printf("Fork Error\n");
		return 1;
	}

	if(pid == 0) {
		while(1) {
			printf("Some text\n");
			sleep(3);
		}
	}
	else {
		sleep(9);
		kill(pid, SIGKILL); // отправляем сигнал дочернему процессу
		wait(NULL);
	}

	return 0;
}