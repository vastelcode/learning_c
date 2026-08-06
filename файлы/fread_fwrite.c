#include <stdio.h>
#include <errno.h>

int main(void)
{
	/*
	Мы можем сохранять данные в файлах в таком же виде, как они выглядят в памяти устройства, то есть в двоичном виде.
	При таком подходе мы исключаем потерю данных при переносе в текстовый файл.

	size_t fwrite(const void * restrict ptr, size_t size, size_t nmemb, FILE *stream)
	size_t fread(const void * restrict ptr, size_t size, size_t nmemb, FILE *stream)

	Обе функции принимают указатель ptr на область данных, которую следует записать или занести прочитанные данные из файла.
	size - размер порции данных
	nmemb - кол-во элементов, которые мы читаем
	stream - файловый поток

	*/

	/* int var_i = -10;
	double pi = 3.141592653589793;
	char sym = 'A';

	FILE *fb = fopen("data.txt","wb"); // открыли файл в бинарном режиме на запись

	if (fb == NULL) {
		perror("data.txt");
		return errno;
	}

	fwrite(&var_i,sizeof(var_i),1, fb);
	fwrite(&pi,sizeof(pi),1, fb);
	fwrite(&sym,sizeof(sym),1, fb);

	fclose(fb); // закрыли файл */

	int var_i;
	double pi;
	char sym;

	FILE *fb_read = fopen("data.txt","rb");

	if(fb_read == NULL) {
		perror("data.txt");
		return errno;
	}

	fread(&var_i,sizeof(var_i),1,fb_read);
	fread(&pi,sizeof(pi),1,fb_read);
	fread(&sym,sizeof(sym),1,fb_read);

	printf("var_i = %d pi = %f sym = %c\n",var_i,pi,sym); // var_i = -10 pi = 3.141593 sym = A

	fclose(fb_read);

	return 0;
}