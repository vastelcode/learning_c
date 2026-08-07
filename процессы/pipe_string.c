// Передаче строки через pipe
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 20

char *input(char *pref, size_t max_size)
{
	char *buffer = calloc(max_size,sizeof(char)); // выделяем память на строку

	if(buffer == NULL) {
		printf("Ошибка вызова malloc()\n");
		return NULL;
	}

	printf("%s",pref);

	size_t i = 0;
	int sym;

	// записываем символы в строку
	while((sym = getchar()) != '\n' && sym != EOF && i < max_size) {
		buffer[i++] = (char) sym;
	}

	buffer[i] = '\0';

	return buffer;
}

int main(int argc, char *argv[])
{
	int fd[2]; // fd[0] - чтение fd[1] - запись
	if(pipe(fd) == -1) {
		printf("Ошибка вызова pipe()\n");
		return 1;
	}

	int pid = fork(); // создаём дочерний процесс

	if(pid < 0) {
		printf("Ошибка вызова fork()\n");
		return 2;
	}

	if(pid == 0) { // дочерний процесс
		close(fd[0]); // закрываем поток чтения

		char *string = input("Введите строку: ",MAX_SIZE); // получаем строку от пользователя

		if(string == NULL) return 3;

		// записываем размер строки
		size_t size = strlen(string) + 1;
		if(write(fd[1],&size,sizeof(size)) != sizeof(size)) {
			printf("Ошибка записи\n");
			return 5;
		}

		// записываем все символы строки
		if(write(fd[1],string,size) != size) {
			printf("Ошибка записи\n");
			return 4;
		}

		free(string); // освобождаем память

		close(fd[1]); // закрываем поток записи
	}
	else {
		close(fd[1]); // закрываем поток записи

		// читаем размер
		size_t size;

		if(read(fd[0],&size,sizeof(size)) != sizeof(size)) {
			printf("Ошибка чтения\n");
			return 6;
		}
		
		char *buffer = malloc(size); // определяем место, куда будем читать строку

		size_t i = 0;

		if(read(fd[0],buffer,size) != size) {
				printf("Ошибка чтения\n");
				return 7;
		}

		close(fd[0]); // закрываем поток чтения

		int status;
		wait(&status);

		if(WIFEXITED(status)) {
			int statusCode = WEXITSTATUS(status);

			if(statusCode == 0) {
				printf("%s\n",buffer);
			}
			else {
				printf("Код завершения - %d\n",statusCode);
			}
		}

		free(buffer);
	}
	return 0;
}