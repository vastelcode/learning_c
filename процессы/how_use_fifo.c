// Как использовать FIFO-файлы для взаимодействия между процессами
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>

#define FIFO_PATH "data/myfifo"
#define ARRAY_SIZE 5

int main(int argc, char *argv[])
{
	if(mkfifo(FIFO_PATH,0777) == -1) { // создаём файл FIFO
		if(errno != EEXIST) {
			printf("Ошибка: main->mkfifo\n");
			return errno;
		}
	}

	// генерируем массив чисел
	int arr[ARRAY_SIZE];

	srand(time(NULL));

	for(int i = 0; i < ARRAY_SIZE;i++) arr[i] = rand() % 100;

	int fd_write = open(FIFO_PATH,O_WRONLY); // открываем FIFO-файл на запись

	if(fd_write == -1) {
		printf("Ошибка открытия на запись: main->open\n");
		return errno;
	}

	for(int i = 0;i < ARRAY_SIZE; i++) { // записываем числа из массива в FIFO-файл
		if(write(fd_write,&arr[i],sizeof(arr[0])) == -1) {
			printf("Ошибка записи: main->write\n");
			return errno;
		}
		printf("Записано %d\n",arr[i]);
	}

	close(fd_write); // закрываем FIFO-файл

	int fd_read = open(FIFO_PATH,O_RDONLY); // открываем файл на чтение

	if(fd_read == -1) {
		printf("Ошибка открытия на чтение: main->open\n");
		return errno;
	}

	int total; // определяем переменную для суммы

	if(read(fd_read,&total,sizeof(total)) == -1) {
		printf("Ошибка чтения: main->read\n");
		return errno;
	}

	printf("Сумма = %d\n",total);

	close(fd_read); // закрываем FIFO-файл

	return 0;
}