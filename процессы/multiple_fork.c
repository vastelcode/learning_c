// Многократный вызов fork() в Си
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	/*
	Многократный вызов fork() создаёт некое дерево процессов.
	С каждым вызовом fork() у каждого существующего процесса создаётся потомок.
	Потомок наследует от предка значения переменных.

	*/

	int id1 = fork();
	int id2 = fork();

	if(id1 == 0) { // дочерний процесс главного процесса
		if(id2 == 0) {
			printf("We are process y pid: %d\n",getpid()); // у этого процесса нет потомков, так как оба id равны 0
		}
		else {
			printf("We are process x pid: %d\n",getpid()); // первый созданный потомок main
		}
	}
	else {
		if (id2 == 0) {
			printf("We are process z pid: %d\n",getpid()); // второй созданный потомок main
		}
		else {
			printf("We are parent process\n");
		}
	}

	int pid_waited;

	while((pid_waited = wait(NULL)) != -1 || errno != ECHILD) { // -1 , если ждать уже нечего
		printf("Waited %d\n",pid_waited);
	}

	return 0;
}