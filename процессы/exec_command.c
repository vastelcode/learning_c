// Выполнение команд UNIX
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

#define PATH_PROGRAMM "/usr/bin/ping" // путь до исполняемого файла
#define NAME "ping" // имя команды
#define PATH_OUTPUT "data/ping_output.txt" // путь до файла вывода

int main(int argc, char *argv[])
{
	int pid = fork(); // создаём дочерний процесс

	if(pid == -1) {
		perror("fork");
		return errno;
	}

	if(pid == 0) { // дочерний процесс

		int fd = open(PATH_OUTPUT,O_WRONLY | O_CREAT, 0777); // открываем файл на запись вывода (создаём его)

		if(fd == -1) {
			perror("open");
			return errno;
		}

		dup2(fd,STDOUT_FILENO); // перенаправляем поток STDOUT в файл вывода
		close(fd); // закрываем файл после дубликации

		/*
		При запуске процесса автоматически открываются 3 файла:
		STDIN - fd = 0
		STDOUT - fd = 1
		STDERR - fd = 2, где fd - файловый дескриптор

		С помощью функции int dup(int fd) мы можем дублировать файл, но уже с другим файловым дескприптором
		С помощью функции int dup2(int fd1, int fd2) мы можем заменять путь , соответствующий fd2 , путём, соответствующим fd1
		*/

		int err = execl(PATH_PROGRAMM,NAME,"-c","3","google.com",NULL); // выполняем команду

		if(err == -1)
		{
			perror("execle");
			return errno;
		}
	}

	else { // родительский процесс

		int status_child;
		wait(&status_child); // ждём выполнения дочернего процесса

		if(WIFEXITED(status_child)) { // используем макроопределения, вернёт true, когда программа завершилась не аварийно
			int status = WEXITSTATUS(status_child); // получаем код завершения процесса

			if(status == 0) {
				printf("Success\n");
			}
			else {
				printf("Fail with code %d\n",status);
			}
		}
	}
	return 0;
}