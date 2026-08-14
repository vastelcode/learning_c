// Практический пример использования барьеров
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define _POSIX_C_SOURCE 200809L   // для современных POSIX-функций
#define AMOUNT_THREADS 8

pthread_barrier_t barrier_rolls;
pthread_barrier_t barrier_calculate;

int rolls[8];
int status[8] = {0};

void *roll_dice(void *arg)
{
	int index = * (int *) arg;
	int dice = (rand() % 6) + 1;

	rolls[index] = dice;

	pthread_barrier_wait(&barrier_rolls);
	pthread_barrier_wait(&barrier_calculate);

	if(status[index] == 1) {
		printf("%d: I won %d\n",index,rolls[index]);
	}
	else {
		printf("%d: I lost %d\n",index,rolls[index]);
	}

	free(arg);
}

int main(int argc, char *argv[])
{
	pthread_t th[AMOUNT_THREADS];
	srand(time(NULL));

	pthread_barrier_init(&barrier_rolls,NULL, AMOUNT_THREADS + 1); // +1 - так как учитываем основной поток тоже
	pthread_barrier_init(&barrier_calculate,NULL, AMOUNT_THREADS + 1);

	for(int i = 0; i < AMOUNT_THREADS; i++) {
		int *arg = malloc(sizeof(int));

		if(arg == NULL) {
			printf("Malloc Error: main->arg\n");
			pthread_exit(NULL);
			return 3;
		}
		*arg = i;

		if(pthread_create(th + i, NULL, &roll_dice, (void *) arg) != 0) {
			printf("Ошибка вызова pthread_create()\n");
			return 1;
		}
	}

	pthread_barrier_wait(&barrier_rolls);

	//  Определение победителей
	int max = 0;

	for(int i = 0; i < AMOUNT_THREADS; i++) {
		if(rolls[i] > max) max = rolls[i];
	}

	for(int i = 0; i < AMOUNT_THREADS; i++) {
		if(rolls[i] == max) status[i] = 1;
	}

	pthread_barrier_wait(&barrier_calculate);

	for(int i = 0; i < AMOUNT_THREADS; i++) {
		if(pthread_join(th[i],NULL) != 0) {
			printf("Ошибка вызова pthread_join()\n");
			return 2;
		}
	}

	pthread_barrier_destroy(&barrier_rolls);
	pthread_barrier_destroy(&barrier_calculate);

	return 0;
}