// подключаем стандартные библиотеки
#include <stdio.h>

// подключаем вспомогательные модули
#include "quicksort.h"

enum sizes {
	default_size_data = 10
};

int main(void)
{
	int numbers[10] = {9,12,15,14,2,-8,32,10,78};

	quicksort(numbers,0,10 - 1);

	for(size_t i = 0; i < 10; i++) printf(" %d",numbers[i]);

	putchar('\n');

	return 0;
}