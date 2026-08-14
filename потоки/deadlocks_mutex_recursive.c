// Взаимоблокировки и рекурсивный мьютекс
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define _POSIX_C_SOURCE 200809L   // для современных POSIX-функций

#define AMOUNT_THREAD 8

pthread_mutex_t mutex_fuel;
// pthread_mutex_t mutex_water;
int fuel = 50;
// int water = 10;

void *routine(void *)
{
	// if(rand() % 2 == 0) { // <- вот тут возникает ситуация взаимной блокировки из за различного порядка блокировки мьютексов 
	   // pthread_mutex_lock(&mutex_fuel);
	   // sleep(1);
	   // pthread_mutex_lock(&mutex_water);
	// }
	/* else {
	    pthread_mutex_lock(&mutex_water);
		sleep(1);
		pthread_mutex_lock(&mutex_fuel);
	} */

    pthread_mutex_lock(&mutex_fuel);
    pthread_mutex_lock(&mutex_fuel);
	fuel += 50;
	// water = fuel;
	// printf("Addicted fuel: %d set water to %d\n",fuel,water);
	printf("Addicted fuel: %d\n",fuel);

	pthread_mutex_unlock(&mutex_fuel); // сколько раз заблокировали, столько же и разблокировали
	pthread_mutex_unlock(&mutex_fuel);
	// pthread_mutex_unlock(&mutex_water);
}

int main(int argc, char *argv[])
{
	/* Взаимная блокировка
	       Fuel  Water
	Thread 1   x    wait
	Thread 2   wait  x

	Из-за того, что первый поток ждёт, пока кто-то разблокирует мьютекс воды, а второй поток - мьютекс топлива,
	выполнение программы зависает, так как они взаимноблокируют друг друга.

	Для того, чтобы блокировать один и тот же мьютекс в одном потоке и при 
	этом не вызвать взаимную блокировку, нужно использовать рекурсивный мьютекс и указать атрибуты при иниализации мьютекса.

	*/
	pthread_t th[AMOUNT_THREAD];

	pthread_mutexattr_t recursiveMutexAttr;

	pthread_mutexattr_init(&recursiveMutexAttr);

	pthread_mutexattr_settype(&recursiveMutexAttr,PTHREAD_MUTEX_RECURSIVE); // перед этим важно его инициализировать

	pthread_mutex_init(&mutex_fuel,&recursiveMutexAttr);
	// pthread_mutex_init(&mutex_water,NULL);

	for(int i = 0; i < AMOUNT_THREAD; i++) {
		if(pthread_create(th + i ,NULL,&routine,NULL) != 0) {
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

	printf("Fuel: %d\n",fuel);
	// printf("Water: %d\n",water);

	pthread_mutexattr_destroy(&recursiveMutexAttr);
	pthread_mutex_destroy(&mutex_fuel);
	// pthread_mutex_destroy(&mutex_water);

	return 0;
}