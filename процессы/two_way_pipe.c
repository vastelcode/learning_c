// Двусторонняя связь между процессами
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	// устанавливаем первый поток связи
	int p1[2]; // [0] - чтение [1] - запись
	int p2[2]; // аналогично

	if(pipe(p1) == -1) {
		printf("Ошибка установки связи: main->pipe(1)\n");
		return errno;
	}

	if(pipe(p2) == -1) {
		printf("Ошибка установки связи: main->pipe(2)\n");
		return errno;
	}

	int pid = fork(); // создаём дочерний процесс

	if(pid == -1) {
		printf("Ошибка при создании дочернего процесса: main->fork\n");
		return errno;
	}

	if(pid == 0) { // дочерний процесс

		close(p1[1]); // закрываем поток записи первого канала
		close(p2[0]); // закрываем поток чтения второго канала

		int x;

		if(read(p1[0], &x,sizeof(x)) == -1) { // читаем данные из первого канала
			printf("Ошибка при чтении данных: main->child_process->read\n");
			return errno;
		}

		printf("Прочитано: %d\n",x);

		close(p1[0]); // закрываем чтение

		x *= 4; // изменяем число

		if(write(p2[1],&x,sizeof(x)) == -1) { // записываем данные во второй канал
			printf("Ошибка при записи данных: main->child_process->write\n");
			return errno;
		}

		printf("Записано: %d\n",x);

		close(p2[1]); // закрываем запись
	}

	else {
		close(p1[0]); // закрываем чтение первого потока
		close(p2[1]); // закрываем запись второго потока

		// генерируем число
		srand(time(NULL));
		int x = rand() % 10;

		if(write(p1[1],&x,sizeof(x)) == -1) { // записываем данные в первый поток
			printf("Ошибка при записи данных: main->parent_process->write\n");
			return errno;
		}

		printf("Записано: %d\n",x);

		close(p1[1]); // закрываем запись

		int new_x; // определяем переменную для хранения нового числового значения

		if(read(p2[0],&new_x,sizeof(new_x)) == -1) {
			printf("Ошибка при чтении данных: main->parent_process->read\n");
			return errno;
		}

		printf("Итог: %d\n",new_x);

		close(p2[0]); // закрываем чтение

		wait(NULL);
	}
	return 0;
}