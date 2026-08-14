// Как передавать аргументы потокам в Си ?
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}; // массив простых чисел

void *action(void *arg)
{
	printf("%d ",* (int *) arg);
	putchar('\n');
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t threads[10];

	for(int i = 0; i < 10; i++) {
		if(pthread_create(threads + i, NULL,&action,(void *) (primes + i)) != 0) {
			perror("Ошибка вызова pthread_create()");
			return 1;
		}

	}

	for(int i = 0; i < 10; i++) {
		if(pthread_join(threads[i], NULL) != 0) {
			perror("Ошибка вызова pthread_join()");
			return 2;
		}
	}
	return 0;
}