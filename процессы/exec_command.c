// Выполнение команд UNIX
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

#define PATH "/usr/bin/ls" // путь до исполняемого файла
#define NAME "ls" // имя команды

int main(int argc, char *argv[])
{
	int pid = fork(); // создаём дочерний процесс

	if(pid == -1) {
		perror("fork");
		return errno;
	}

	if(pid == 0) { // дочерний процесс

		if(execl(PATH,NAME,(char *) NULL) == -1) // выполняем команду
		{
			perror("execle");
			return errno;
		}
	}

	else { // родительский процесс

		int status_child;
		wait(&status_child); // ждём выполнения дочернего процесса

		if(status_child == 0) {
			printf("Success !\n");
		}
		else {
			printf("Fail\n");
		}
	}
	return 0;
}