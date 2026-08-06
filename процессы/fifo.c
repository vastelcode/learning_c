// Введение в FIFOs
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>

#define FILE_PATH "data/myfifo1"

int main(int argc, char *argv[])
{
	/*
	Проблема pipe() заключается в том, что мы не моежм создать "трубу" между двумя каналами, которые не находятся в одной иерархии.
	В таких случаях нам следует использовать fifo.

	Есть одна особенность работы с файлами FIFO: когда мы открываем файл на запись, процесс блокируется до тех пор, пока не будет тот же файл на чтение.
	То есть для того, чтобы запись завершилась, нужно чтобы началось чтение. Нам нужен другой процесс, который откроект файл на чтение.

	*/
	if(mkfifo(FILE_PATH,0777) == -1) { // может вернуть значение -1, если файл уже создан и делать ничего не надо
		if(errno != EEXIST) {
			printf("An error ocurred mkfifo\n");
		    return errno;
		}
	}

	int id = fork(); // создаём дочерний процесс

	if(id == -1) {
		printf("An error ocurred fork\n");
		return errno;
	}

	if(id == 0) { // в дочернем процессе записываем

       int fd = open(FILE_PATH,O_WRONLY); // открываем файл только для записи; получаем файловый дескриптор

	   if(fd == -1) {
		   printf("An error ocurred openning for write\n");
		   return errno;
	   }
	   char x = 'Y';

	   if (write(fd,&x,sizeof(x)) == -1) { // записываем символ Y в файл
		   printf("An error ocurred write\n");
		   return errno;
	   }

	   close(fd); // закрываем файл
	}

	else { // в родительском процессе - читаем
		int fd = open(FILE_PATH,O_RDONLY); // открываем файл только для чтения

	   if(fd == -1) {
		   printf("An error ocurred openning for read\n");
		   return errno;
	   }

		char x;

		if(read(fd,&x,sizeof(x)) == -1) {

			printf("An error ocurred read\n");
			return errno;
		}

		printf("Sumbol = %c\n",x);
		wait(NULL);
	}

	return 0;
}