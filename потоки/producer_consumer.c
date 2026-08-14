// Проблема производителя-потребителя
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define AMOUNT_THREAD 2

int buffer[10];
int count = 0;

sem_t semEmpty; // кол-во пустых ячеек
sem_t semFull; // кол-во заполненных ячеек

pthread_mutex_t mutex_buffer;

void *producer(void *arg)
{
	while(1) {
	   // Этап производства
	   int x = rand() % 100;
	   sleep(1);

	   sem_wait(&semEmpty); // уменьшаем кол-во пустых ячеек
	   pthread_mutex_lock(&mutex_buffer);

	   // Этап добавления значения в буфер
	   buffer[count] = x;
	   count++;

	   pthread_mutex_unlock(&mutex_buffer);
	   sem_post(&semFull); // увеличиваем кол-во заполненных ячеек
	}

	return NULL;
}

void *consumer(void *arg)
{
	while(1) {

	   sem_wait(&semFull); // уменьшаем кол-во заполненных ячеек
	   pthread_mutex_lock(&mutex_buffer);

	    // Этап взятия элемента из буфера
	    int x = buffer[count - 1];
	    count--;

	   pthread_mutex_unlock(&mutex_buffer);
	   sem_post(&semEmpty); // увеличиваем кол-во заполненных

	    // Этап потребления
	    printf("Got %d\n",x);
		sleep(1);
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	/*
	У нас есть общий буфер, то есть общая область памяти, находящаяся между потоками.
	Есть производители, которые добавляют данные в буфер.
	И есть потребители, которые эти данные из буфера берут.

	Есть три проблемы, которые надо решить:
	1) управление доступом к общей памяти <- решили с помощью мьютекса
	2) проверка буфера на заполнение <- решили с помощью семафоры semFull
	3) проверка буфера на пустоту <- решили с помощью семафоры semEmpty

	*/

	pthread_t th[AMOUNT_THREAD];
	srand(time(NULL));

	pthread_mutex_init(&mutex_buffer,NULL);

	sem_init(&semEmpty,0,10);
	sem_init(&semFull,0,0);

	for(int i = 0; i < AMOUNT_THREAD; i++) {
		if(i % 2 == 0) {
			if(pthread_create(th + i, NULL, &producer, NULL) != 0) {
			perror("Ошибка вызова pthread_create()\n");
			return 1;
		   }
		}
		else {
		  if(pthread_create(th + i, NULL, &consumer, NULL) != 0) {
			  perror("Ошибка вызова pthread_create()\n");
			  return 1;
		   }
		}
	}

	for(int i = 0; i < AMOUNT_THREAD; i++) {
		if(pthread_join(th[i],NULL) != 0) {
			perror("Ошибка вызова pthread_join()\n");
			return 2;
		}
	}

	sem_destroy(&semEmpty);
	sem_destroy(&semFull);

	pthread_mutex_destroy(&mutex_buffer);

	return 0;
}
