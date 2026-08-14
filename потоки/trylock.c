// Разница между trylock и lock
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


pthread_mutex_t mutex;

void *routine(void *arg)
{
	if(pthread_mutex_trylock(&mutex) == 0) { // попытка блокировки, 0 - блокировка мьютекса прошла
	   printf("Got lock\n");
	   sleep(1);
	   pthread_mutex_unlock(&mutex);
	}
	else {
		printf("Didn't get lock\n");
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	/*
	Главное отличие lock от trylock заключается в том, что lock в любом случае будет ждать, пока мьютекс разблокируется,
	а trylock в том случае, если на момент вызова мьютекс заблокирован, не будет ждать и вернёт значение, отличное от нуля.
	*/
	pthread_t th[4];

	pthread_mutex_init(&mutex,NULL);

	for(int i = 0; i < 4; i++) {
		if(pthread_create(th + i, NULL,&routine,NULL) != 0) {
			printf("Ошибка вызова pthread_create()\n");
			return 1;
		}
	}

	for(int i = 0; i < 4; i++) {
	    if(pthread_join(th[i], NULL) != 0) {
			printf("Ошибка вызова pthread_join()\n");
			return 2;
		}
	}

	pthread_mutex_destroy(&mutex);

	return 0;
}