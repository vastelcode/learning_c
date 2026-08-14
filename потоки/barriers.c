// Введение в барьеры (pthread_barrier)
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define _POSIX_C_SOURCE 200809L   // для современных POSIX-функций

#define AMOUNT_THREADS 9

pthread_barrier_t barrier; //  определяем барьер

void *routine(void *)
{
	printf("Waiting...\n");
	pthread_barrier_wait(&barrier); // <- та точка, где потоки остановятся

	printf("Run !\n");
	return NULL;
}

int main(int argc, char *argv[])
{
	/*
	Идея барьера заключается в том, что барьер - объект, дойдя до которого потоки останавливаются,
	пока количество  остановившихся потоков не дойдёт до некоторого количества. Когда нужное количество потоков
	будет набрано, барьер поднимется , потоки продолжат своё выполнение.

	*/
	pthread_t th[AMOUNT_THREADS];

	pthread_barrier_init(&barrier, NULL, 3); // 1 - указатель на переменную барьера; 2 - атрибуты; 3 - кол-во потоков для подьёма барьера 

	for(int i = 0; i < AMOUNT_THREADS; i++) {
		if(pthread_create(th + i, NULL,&routine, NULL)) {
			printf("Ошибка вызова pthread_create()\n");
			return 1;
		}
	}

	for(int i = 0; i < AMOUNT_THREADS; i++) {
		if(pthread_join(th[i], NULL)) {
			printf("Ошибка вызова pthread_join()\n");
			return 2;
		}
	}

	pthread_barrier_destroy(&barrier);

	return 0;
}