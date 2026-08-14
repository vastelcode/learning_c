// Практический пример : суммирование числе в массиве
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int nums[10] = {1,2,3,4,5,6,7,8,9,10}; // массив чисел для суммирования
int mid = (sizeof(nums) / sizeof(nums[0])) / 2; // серединный индекс
int sum = 0;

void *routine(void *arg)
{
	int index = * (int *) arg; // выполняем преобразование типов
	int sum = 0;

	for(int i = 0; i < mid; i++) sum += nums[index + i];
	printf("part = %d\n",sum);
	
	* (int *) arg = sum; // зачисляем значение суммы в переданную область памяти

	return arg;
}

int main(int argc, char *argv[])
{
	pthread_t threads[2];

	for(int i = 0; i < 2; i++) {
		// определяем стартовую позицию
		int *start = malloc(sizeof(int));
		*start = i * mid;

		if(pthread_create(threads + i,NULL,&routine,start) != 0) {
			printf("Ошибка вызова pthread_create()\n");
			return 1;
		}
	}

	for(int i = 0; i < 2; i++) {
		int *res;

		if(pthread_join(threads[i],(void **) &res) != 0) {
			printf("Ошибка вызова pthread_join()\n");
			return 2;
		}

		sum += *res;
		free(res);
	}

	printf("total = %d\n",sum);

	return 0;
}