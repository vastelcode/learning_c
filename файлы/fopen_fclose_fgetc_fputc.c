#include <stdio.h>

#define MAX_SIZE_BUFFER 50

int main(void)
{
	/*
	FILE *fopen(const char *path, const char *mode) - функция открытия потока, связанного с файлом; вёрнет NULL, если файл открыть не удалось(нужно ВСЕГДА проверять)
	- первый аргумент - путь до файла
	- второй аргумент - режим открытия (r - чтение,w - запись,a - дозапись,r+ - r + w, w+ - r + w, a+ - w+ + a);  также к каждому режиму доступна его запись с буквой b, например, rb, wb, ab и так далее, эти режимы для работы с двоичными файлами.

	int fclose(FILE *fp) - функция для закрытия потока, связанного с файлом, вызывать строго обязательно; 0 - успех ; -1 -  ошибка

	int fgetc(FILE *stream) - функция для чтения одного байта из файла

	int fputc(int ch, FILE *stream) - функция для записи одного байта в файл
	*/

	FILE *fp = fopen("text.txt","w+"); // открыли файл для записи

	if (fp == NULL) return 1;

	char str[] = "Function fputs()";

	for(int i = 0; str[i] != '\0'; i++)
	    fputc(str[i],fp);

	fclose(fp); // закрыли файл для записи

	FILE *fc = fopen("content.txt","r"); // открыли файл для чтения

	if (fc == NULL) return 1;

	char buffer[MAX_SIZE_BUFFER]; // буфер, куда будем записывать данные
	int k = 0;
	int symbol;

	while((symbol = fgetc(fc)) != EOF && k < MAX_SIZE_BUFFER) {
		buffer[k++] = (char) symbol;
	}

	buffer[k] = '\0';

	printf("buffer = %s\n",buffer);

	fclose(fc); // закрыли файл для чтения

	return 0;
}