// Получение значения семафоры
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define THREAD_AMOUNT 4

sem_t semaphore;

void *routine(void *arg)
{
	int index = * (int *) arg;
	int semVal;

	sem_wait(&semaphore);

	sem_getvalue(&semaphore,&semVal);
	printf("(%d) Semaphore value = %d\n",index,semVal);

	sem_post(&semaphore);

	free(arg);
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t th[THREAD_AMOUNT];

	sem_init(&semaphore,0,THREAD_AMOUNT);

	for(int i = 0; i <  THREAD_AMOUNT; i++) {
		int *arg = malloc(sizeof(int));
		*arg = i;

		if(pthread_create(th + i, NULL, &routine, (void *) arg) != 0) {
			perror("Ошибка вызова pthread_create()\n");
			return 1;
		}		
	}

	for(int i = 0; i <  THREAD_AMOUNT; i++) {
		if(pthread_join(th[i],NULL) != 0) {
			perror("Ошибка вызова pthread_join()\n");
			return 2;
		}		
	}

	sem_destroy(&semaphore);

	return 0;
}