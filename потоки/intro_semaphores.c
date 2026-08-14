// Введение в семафоры
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define AMOUNT_THREAD 4

sem_t semaphore;

void *routine(void *arg)
{
	sem_wait(&semaphore);

	sleep(1);
	printf("Hello from thread %d\n",* (int *) arg);
	free(arg);

	sem_post(&semaphore);

	return NULL;
}

int main(int argc, char *argv[])
{
	/*

	Семафоры в действительности имеет инициализируется целочисленным значением, занесённым в её струкутуру.

	С семафорами доступно двве основные операции:
	- wait (что очень похоже на блокировку мьютекса)
	- post (что очень похоже на разблокировку мьютекса)

	sem_wait работает следующим образом: если значение семафоры == 0 и его больше нельзя уменьшить, то
	он будет ждать завершение семафоры для этого потока, иначе значение семафоры > 0 -> s-- (уменьшить значение , не будет ждать и начнёт выполнять следующие инструкции после вызова)
	
	sem_post увеличивает значение семафоры.

	Мьютекс по сути - семафора с начальным значением - 1.
	*/
	pthread_t th[AMOUNT_THREAD];

	sem_init(&semaphore,0,2); // 3 аргумента - начальное целочисленное значение семафоры

	for(int i = 0; i < AMOUNT_THREAD; i++) {
		int *arg = malloc(sizeof(int));
		*arg = i;

		if(pthread_create(th + i, NULL, &routine, (void *) arg) != 0) {
			perror("Ошибка вызова pthread_create()");
			return 1;
		}
	}

	for(int i = 0; i < AMOUNT_THREAD; i++) {
		if(pthread_join(th[i],NULL) != 0) {
			perror("Ошибка вызова pthread_join()");
			return 2;
		}
	}

	sem_destroy(&semaphore);

	return 0;
}