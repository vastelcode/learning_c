#include <stdio.h>
#include <errno.h>


#define FORMAT_DATA "%lf; "

enum {
	max_length = 100,
	buffer_size = 512,
	data_size = 100
};

int main(void)
{
	/*
	  int feof(FILE *stream) - функция возвращает 1 , если мы достигли конца файла и 0, если нет
	  int fflush(FILE *stream); - очистка выходного потока с помещением всех данных из буфера в файл (вызывать её следует после операции записи информации)
	  int sevbuf(FILE* restrict stream, char* restrict buf,int mode, size_t size) - функция для определения собственного буфера; следует вызывать сразу после открытия файлового потока
	  - stream - файловый поток, для которого будет создаваться буфер
	  - buf - область памяти для буфера, если равен NULL, то буфер будет создан автоматически
	  - mode - режим работы буфера
	  - size - размер буфера в байтах

	  Параметр mode может иметь следующие значения:

	  _IOFBF - полная буферизация(очистка после заполнения буфера)
	  _IOLBF - построчная буферизация(очистка по символу переноса строки)
	  _IONBF - выключение буферизации

	*/

	/* double data[max_length];
	char buffer[max_length];
	int length = 0; // кол-во прочитанных частей

	FILE *fread = fopen("money.csv","r"); // открываем файл для чтения

	if (fread == NULL) {
		perror("money.csv");
		return errno;
	}

	while(!feof(fread)) {
		fgets(buffer,sizeof(buffer),fread); // записываем заголовок

		length = 0;

		while(fscanf(fread,FORMAT_DATA,&data[length]) == 1) length++; // записываем данные

		puts(buffer);
		for(int i = 0; i < length; i++) printf("%.2f ",data[i]);
		putchar('\n');
	}

	fclose(fread); // закрываем файл для чтения */

	/* int data[] = {1,5,7,9,4,12,13,20,61};

	int length = sizeof(data) / sizeof(data[0]);

	// открываем запись на чтение и запись одновременно
	FILE *fp = fopen("writeand_read.dat","w");
	FILE *in = fopen("writeand_read.dat","r");

	if(fp == NULL || in == NULL) {
		perror("write_and_read.dat");
		return errno;
	}

	for (int i = 0; i < length; i++) { // записываем данные в файл
		fprintf(fp,"%d ",data[i]);
	}

	fflush(fp); // очистка выходного потока, чтобы мы далее могли прочитать данные; перемещаем данные в файл

	int val;

	for(int i = 0; i < length; i++) {
		fscanf(in,"%d ",&val);
		printf("val = %d\n",val);
	}

	fclose(fp);
	fclose(in); */

	char buffer[buffer_size]; // область памяти под буфер
	char data[data_size]; // область памяти под данные из файла

	FILE *file = fopen("money.csv","r");

	if (file == NULL) {
		perror("money.csv");
		return errno;
	}

	if (setvbuf(file,buffer,_IOFBF,buffer_size) != 0) { // полная буферизация
		perror("Incorrect type of size buffer");
		return errno;
	}

	fgets(data,sizeof(data),file);
	puts(buffer);
	puts("---");
	puts(data); // первая строчка, которую прочитала функция fgets()

	fclose(file);

	return 0;
}