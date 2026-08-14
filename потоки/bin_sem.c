// Бинарные семафоры
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_AMOUNT 1

sem_t semFuel;

int *fuel;

void *routine(void *arg)
{
	*fuel += 50;
	printf("Текущее кол-во топлива: %d\n",*fuel);

	sem_post(&semFuel); // увеличиваем значение до 1
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t th[THREAD_AMOUNT];

	fuel = malloc(sizeof(int));
	*fuel = 50;

	sem_init(&semFuel,0,0); // изначально 0

	for(int i = 0; i < THREAD_AMOUNT; i++) {
		if(pthread_create(th + i, NULL, &routine, NULL) != 0) {
			perror("Ошибка вызова pthread_create()");
			return 1;
		}
	}

	sem_wait(&semFuel); // ждём, пока значение семафоры можно будет уменьшить

	printf("Освобождение памяти\n");
	free(fuel);

	for(int i = 0; i < THREAD_AMOUNT; i++) {
		if(pthread_join(th[i],NULL) != 0) {
			perror("Ошибка вызова pthread_join()");
			return 2;
		}
	}

	sem_destroy(&semFuel);

	return 0;
}