// Как отправлять массивы данных , используя pipe ?
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int nums[20];
int amount_nums;

int main(int argc, char *argv[])
{
	int fd[2];

	if(pipe(fd) == -1) { // создаём канал связи
		printf("Ошибка вызова pipe()\n");
		return 1;
	}

	int pid = fork(); // создаём дочерний процесс

	if(pid < 0) {
		printf("Ошибка вызова fork()\n");
		return 2;
	}

	if(pid == 0) {

		close(fd[0]); // закрываем поток чтения

		// запрашиваем у пользователя кол-во цифр для генерации
		int count;
		printf("Input amount: ");
		scanf("%d",&count);

		// приводим число к числовому отрезку [5;20]
		if (count < 5) count = 5;
		else if (count > 20) count = 20;

		// сначала записываем кол-во
		if(write(fd[1],&count,sizeof(count)) != sizeof(count)) {
			printf("Ошибка записи\n");
			return 5;
		}

		int i = 0;
		srand(time(NULL));
		
		for(; i < count; i++) {
			int x = rand() % 10;

			if(write(fd[1],&x,sizeof(x)) != sizeof(x)) {
				printf("Ошибка записи\n");
				return 3;
			}
		}

		close(fd[1]); // закрываем поток записи
	}
	else {
		close(fd[1]); // закрываем поток записи

		// сначала читаем кол-во элементов
		int received_count;
		if(read(fd[0],&received_count,sizeof(received_count)) != sizeof(received_count)) {
			printf("Ошибка чтения\n");
			return 4;
		}

		// записываем все остальные элементы в массив
		for(int i = 0; i < received_count; i++) {

			if(read(fd[0],&nums[i],sizeof(nums[i])) != sizeof(nums[i])) {
				printf("Ошибка чтения\n");
				return 6;
			}
		}

		close(fd[0]); // закрываем поток чтения

		int status;
		wait(&status); // ждём завершения дочернего процесса

		if(WIFEXITED(status)) {
			int statusCode = WEXITSTATUS(status); // получаем статус выхода

			if(statusCode == 0) {
				for(int i = 0;i < received_count; i++) printf(" %d",nums[i]);
				putchar('\n');
			}
			else {
				printf("Код завершения - %d\n",statusCode);
			}
		}
	}
	return 0;
}