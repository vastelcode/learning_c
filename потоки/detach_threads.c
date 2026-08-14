// Отсоединие потоков от основного
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#define AMOUNT_THREAD 2

void *routine(void *)
{
	sleep(1);
	printf("Finished execution\n");
	return NULL;
}

int main(int argc, char *argv[])
{
	/*
	Отсоединённый поток больше не может быть присоединён с помощью функции pthread_join().

	Отсоёдиненный поток обычно используется, когда у вас есть длительный процесс,
	который вы хотите запустить внутри основного потока, но у вас нет необходимости того, чтобы основной поток
	продолжал своё выполнение. Основному потоку не приходится ждать выполнения потока с длительным процессом,
	так как он может продолжать своё выполнение очень долго.

	Вместо вызова pthread_detach после создания потока, можно воспользовать вторым аргументом функции pthread_create.

	Отсоединение имеет смысл в ситуациях, когда вам не нужно получать результат работы потока, 
	и вы просто хотите, чтобы система сама позаботилась об освобождении ресурсов. 
	Например: потоки, которые выполняют фоновые задачи, не требующие контроля со стороны создателя.

	Никогда не следует выделять память в отсоединённом потоке.
	*/
	pthread_t th[AMOUNT_THREAD];
	pthread_attr_t detachedThreads;

	pthread_attr_init(&detachedThreads);

	pthread_attr_setdetachstate(&detachedThreads,PTHREAD_CREATE_DETACHED);

	for(int i = 0; i < AMOUNT_THREAD; i++) {
		if(pthread_create(th + i ,&detachedThreads,&routine,NULL) != 0) {
			perror("Ошибка вызова pthread_create()");
			return 1;
		}

		// pthread_detach(th[i]); // отсоединие потока от главного
	}

	/* for(int i = 0; i < AMOUNT_THREAD; i++) {
		if(pthread_join(th[i],NULL) != 0) {
			perror("Ошибка вызова pthread_join()");
		}
	} */

	pthread_attr_destroy(&detachedThreads);
	
	pthread_exit(0);
}