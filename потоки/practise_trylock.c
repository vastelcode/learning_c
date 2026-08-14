#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// chefs = threads
// stove = shared data + mutex

pthread_mutex_t mutex_cook[4];

int stove_fuel[4] = {100,100,100,100};

void *routine(void *arg)
{
	for(int i = 0; i < 4; i++) {
		
		if(pthread_mutex_trylock(&mutex_cook[i]) == 0) { // занимаем газовую плиту
			int fuel_needed = (rand() % 30); // определяем необходимое кол-во топлива
		
			if(stove_fuel[i] - fuel_needed < 0) {
			   printf("Топлива не хватает\n");
			}
			else {
		  	   stove_fuel[i] -= fuel_needed;
		  	   sleep(1);
		  	   printf("Топлива осталось: %d\n",stove_fuel[i]);
	    	}

			pthread_mutex_unlock(&mutex_cook[i]);
			break;
		}
		else { // вместо того, чтобы уходить домой, повар подождёт, пока осводится плита
			if(i == 3) {
				printf("Нет свободной газовой плиты ! Немного подожду\n");
				sleep(1);
				i = 0;
			}
		}
	}
	return NULL;
}

int main(int argc, char *argv[])
{

	srand(time(NULL));

	pthread_t th[10];

	for(int i = 0; i < 4; i++) pthread_mutex_init(&mutex_cook[i], NULL);

	for(int i = 0; i < 10; i++) {
		if(pthread_create(th + i, NULL,&routine,NULL) != 0) {
			printf("Ошибка вызова pthread_create()\n");
			return 1;
		}
	}

	for(int i = 0; i < 10; i++) {
		if(pthread_join(th[i],NULL) != 0) {
			printf("Ошибка вызова pthread_join()\n");
			return 2;
		}
	}

	for(int i = 0; i < 4; i++) pthread_mutex_destroy(&mutex_cook[i]);

	return 0;
}