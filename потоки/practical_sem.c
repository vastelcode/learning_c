// Практический пример использования семафоры (Login Queue)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define AMOUNT_THREAD 16

sem_t semaphore;

void *routine(void *arg)
{
	printf("(%d) Waiting in the login queue...\n", * (int *) arg);

	sem_wait(&semaphore);
	printf("(%d) Logged in\n", * (int *) arg);

	sleep(rand() % 5 + 1);

	printf("(%d) Logged out\n", * (int *) arg);
	free(arg);

	sem_post(&semaphore);

	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t th[AMOUNT_THREAD];

	sem_init(&semaphore,0,12); // допустим, что на сервер могут одновременно зайти только 12 пользователей

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