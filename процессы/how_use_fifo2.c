// Второй модуль по теме "Как использовать FIFO-файлы для взаимодействия между процессами"
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#define FIFO_PATH "data/myfifo"
#define ARRAY_SIZE 5

int main(int argc, char *argv[])
{
	// определяем массив чисел
	int arr[ARRAY_SIZE];

	// открываем FIFO-файл на чтение
	int fd_read = open(FIFO_PATH,O_RDONLY);

	if(fd_read == -1) {
		printf("Ошибка открытия на чтение: main2->open\n");
		return errno;
	}

	for(int i = 0; i < ARRAY_SIZE;i++) { // читаем данные из FIFO-файла и записываем их в массив
		if(read(fd_read,&arr[i],sizeof(arr[0])) == -1) {
			printf("Ошибка чтения: main2->read\n");
			return errno;
		}
		printf("Прочитано %d\n",arr[i]);
	}

	close(fd_read);

	// вычисляем сумму всех элементов
	int total = 0;
	for(int i = 0; i < ARRAY_SIZE; i++) total += arr[i];

	// открываем FIFO-файл на запись
	int fd_write = open(FIFO_PATH,O_WRONLY);

	if(fd_write == -1) {
		printf("Ошибка открытия на запись: main2->open\n");
		return errno;
	}

	if(write(fd_write,&total,sizeof(total)) == -1) { //  записываем сумму в FIFO-файл
		printf("Ошибка записи: main2->write\n");
		return errno;
	}

	close(fd_write);

	return 0;
}