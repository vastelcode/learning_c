#include <stdio.h>
#include <errno.h> // коды ошибок

int main(void)
{
	/*
	В случае, когда нам надо вывести сообщение об ошибке, следует использовать функцию perror(). Выводит сообщение в поток stderr.
	Макрос errno позволяет получить номер ошибки произошедшей в программе.

	Магия чтения файла с помощью функции int fgetc(FILE *stream) состоит в том, что указатель на файловый поток stream содержит в себе указатель позиции,
	который указывает на очередной для чтения байт, после его чтения переходит к следующему. Такой указатель имеет и для потока записи в файл.
	Мы можем управлять этим указателем позции с помощью двух функций:
	- int fseek(FILE *stream, long offset, int whence) - для установки позиции (offset - смещение файловой позиции, whence - относительно чего смещаем).
	whence может иметь следующие значения: SEEK_SET (от начала файла), SEEK_CUR (от текущей позиции), SEEK_END (от конца файла)
	- long ftell(FILE *stream) - для получения текущей позиции

	*/

	/* FILE *error_open = fopen("text2.txt","r"); // несуществующий файл в режиме чтения

	if (error_open == NULL) {
		printf("code error: %d\n",errno);
		perror("text2.txt"); // text2.txt: No such file or directory
		return 1;
	} */

	// прочитаем файл text.txt в обратном порядке

	FILE *file_read = fopen("text.txt","r");

	if (file_read == NULL) {
		perror("text.txt");
		return errno;
	} 

	fseek(file_read, 0, SEEK_END);
	int length = ftell(file_read); // текущая файловая позиция(последний символ файла, так как указали SEEK_END) ; кол-во байт в файле

	char buffer[50];
	int i;

	for(i = 1; i <= length && i < 50; i++) {
		fseek(file_read,-i,SEEK_END); // смещение относительно конца на -i
		buffer[i - 1] = (char) fgetc(file_read);
	}

	buffer[i] = '\0';

	printf("buffer = %s\n",buffer);

	fclose(file_read);

	// записываем в файл каждый символ в первый байт(они заменяют друг друга)

	char str[] = "String for write to file.";

	FILE *fw = fopen("content_2.txt","w+");

	if (fw == NULL) {
		perror("content_2.txt");
		return errno;
	}

	int k = 0;

	while(str[k] != '\0') {
		fseek(fw,0,SEEK_SET);
		fputc(str[k++],fw);
	}

	fclose(fw);

	return 0;
}