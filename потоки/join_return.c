// Получение возвращаемого значения из потока (pthread_join) и pthread_exit()
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define AMOUNT_THREADS 4 // кол-во потоков

void *roll_dice(void *arg) // бросок кубика (1-6)
{
	int *value = malloc(sizeof(int));

	if(value == NULL) {
		printf("Ошибка вызова malloc()\n");
		return NULL;
	}

	*value = (rand() % 6) + 1;

	// return (void *) value; - вместо return можно вызвать pthread_exit()
	printf("Result = %d\n",*value);
	pthread_exit((void *) value);
}

void print_results(int *array[], size_t size_array) // функция вывода результатов
{
	for(int i = 0; i < size_array; i++) printf("%d: Result = %d\n",i,**(array + i));
}

void free_all(int *array[], size_t size_array) // освобождение всех указателей
{
	for(int i = 0; i < size_array; i++) {
		if(array[i] == NULL) continue;

		free(*(array + i));
	}
}

int main(int argc, char *argv[])
{
	srand(time(NULL));

	pthread_t threads[AMOUNT_THREADS]; // массив потоков
	int *results[AMOUNT_THREADS] = {NULL}; // массив указателей на результаты бросков кубика

	// цикл создания потоков
	for(int i = 0; i < AMOUNT_THREADS; i++) {

	   if(pthread_create(threads + i,NULL,&roll_dice,NULL) != 0) {
		   printf("%d: Ошибка вызова pthread_create()\n",i);
		   return 1;
	   }
	}

	// pthread_exit(NULL); // СРАЗУ ЗАВЕРШАЕМ ВЫПОЛНЕНИЕ ВСЕХ ПОТОКОВ
	// т.к вызвади функцию pthread_exit() в главном потоке

	// цикл ожидания завершения потоков
	for(int i = 0; i < AMOUNT_THREADS; i++) {

	   if(pthread_join(threads[i],(void **) (results + i)) != 0) {
		   printf("Ошибка вызова pthread_join()\n");
		   return 2;
	   }

	   if(*(results + i) == NULL) return 3; // произошла ошибка с выделением памяти
	}

	print_results(results,AMOUNT_THREADS); // выводим все результаты
	free_all(results,AMOUNT_THREADS); // освобождаем память

	return 0;
}