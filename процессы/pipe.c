// Функция pipe() в Си

#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	/*
	int pipe(int pipedes[2]) - функция создающая файл с данными, которыми могут пользоваться различные потоки.
	Возвращает 0 в случае успеха, иначе - -1.
	Принимает массив из двух чисел - дескрипторов, куда она будет записывать числовые значения.
	Дескриптор - по-сути ключ доступа к данным.

	*/

	int fd[2]; // fd[0] - read fd[1] - write
	
	if(pipe(fd) == -1) {
		printf("An error occured with oppening the pipe\n");
		return 1;
	}

	int id = fork();

	if(id == -1) {
		printf("An error ocurrend with create new process\n");
		return 4;
	}

	if(id == 0) {
		close(fd[0]);

		int n;
		printf("Enter number: ");
		scanf("%d",&n);
		ssize_t status_write = write(fd[1], &n, sizeof(n)); // записываем данные

		if(status_write == -1) {
			printf("Write Error: child_process->write\n");
			return 2;
		}
		
		close(fd[1]); // закрываем файловый дескриптор
	}
	else {
		close(fd[1]);
		int x;
		ssize_t status_read = read(fd[0],&x,sizeof(x));

		if(status_read == -1) {
			printf("Read Error: parent_process->read\n");
			return 3;
		}
		printf("Number: %d\n",x);
		close(fd[0]);
	}

	return 0;
}