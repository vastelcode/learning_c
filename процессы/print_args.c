// Вспомогательная программа для изучения exec
#include <stdio.h>

int main(int argc, char *argv[])
{
	// вывод всех аргументов командной строки
	for(int i = 0; i < argc; i++) printf("Аргумент: %s\n",argv[i]);
	return 0;
}