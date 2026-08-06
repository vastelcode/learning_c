#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


#define AMOUNT_STRING 5
#define MAX_LENGTH 1024

int main(void)
{
	/*
	int fputs(const char *s, FILE *stream) - функция для записи строки в файл ;возвращает -1 в случае ошибки
	char *fgets(char *s, int size, FILE *stream) - функция для считывая строк из файла;возвращает переданный указатель в случае успеха; читает максимум size - 1 символов

	int fprintf(FILE *stream,const char *format, ...) - запись форматных данных
	int fscanf(FILE *stream,const char *format,...) - чтение форматных данных
	*/

	char *strings[AMOUNT_STRING] = {"Hello !", "I am Maksim.", "I am 16.", "I am programmer", "Goodbye !"}; // определяем массив строк

	FILE *fb = fopen("bio.txt","w+"); // открываем файл для записи

	if (fb == NULL) {
		perror("bio.txt");
		return errno;
	}

	for(int i = 0; i < AMOUNT_STRING;i++) {
		fputs(strings[i],fb); // записываем строку в файл
		fputc('\n',fb); // заканчиваем строку
	}

	fclose(fb); // закрываем файл для записи

	FILE *fr = fopen("arina.txt","r"); // открываем файл для чтения

	if (fr == NULL) {
		perror("arina.txt");
		return errno;
	}

	char **buffer = malloc(sizeof(char *) * (AMOUNT_STRING + 1));

	if (buffer == NULL) {
		perror("buffer");
		return errno;
	}

	int k = 0;

	for(;k < AMOUNT_STRING - 1;k++) {
		buffer[k] = malloc(sizeof(char) * 20);

		if(buffer[k] == NULL) {
			for(size_t i = 0; i < k; i++) free(buffer[i]);
			free(buffer);
			perror("buffer[k]");
			return errno;
		}

		fgets(buffer[k],20,fr); // записываем строку из файла в строку buffer
	}

	buffer[k] = NULL; // завершаем массив со строками

	for(int j = 0; buffer[j] != NULL; j++) {
		printf("%d string = %s\n",j,buffer[j]);
		free(buffer[j]);
	}

	free(buffer);

	fclose(fr); // закрываем файл для чтения


	FILE *fread = fopen("data.csv","r"); // открываем файл для чтения

	if (fread == NULL) {
		perror("data.csv");
		return errno;
	}



	fclose(fread); // закрываем файл для чтения

	FILE *fcsv = fopen("data.csv","r"); // открываем файл на чтение

	double data[MAX_LENGTH] = {0.0};
	unsigned length = 0;

	if (fcsv == NULL) {
		perror("data.csv");
		return errno;
	}

	while(fscanf(fcsv,"%lf; ",&data[length++]) == 1); // читаем форматные данные и записываем в ячейки массива data

	fclose(fcsv); // закрываем файл на чтение

	for(int u = 0; u < length;u++) {
		printf("%.2lf\n",data[u]);
	}

	const char *phones[][5] ={
		{"8","963","331","31","72"},
		{"8","906","205","81","56"},
		{"8","905","291","09","13"}
	};
	// 8(963)331-31-72 - нужный формат

	FILE *fwrite = fopen("phones.txt","w+");

	if (fwrite == NULL) {
		perror("phones.txt");
		return errno;
	}

	// запись номер телефонов в текстовый файл с помощью форматной строки
	for(int index = 0; index < sizeof(phones) / sizeof(*phones);index++) {
		fprintf(fwrite,"%s(%s)%s-%s-%s\n",phones[index][0],phones[index][1], phones[index][2], phones[index][3], phones[index][4]);
	}

	fclose(fwrite);

	return 0;
}