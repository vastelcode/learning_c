// Условные переменные в Си
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

pthread_mutex_t mutex_fuel;
pthread_cond_t  condition_fuel;

int fuel = 0; // топливо

void *fuel_filling(void *arg) // "заправка топливом"
{
	for(int i = 0; i < 5; i++) {
		
		// там , где работатем с глобальной переменной, оборачиваем в мьютекс
		pthread_mutex_lock(&mutex_fuel);
		fuel += 60;
		printf("Filling fuel: %d\n",fuel);
		pthread_mutex_unlock(&mutex_fuel);

		// pthread_cond_signal(&condition_fuel); // отправка сигнала - старая реализация
		pthread_cond_broadcast(&condition_fuel); // новая реализация

		sleep(1);
	}
	return NULL;
}

void *car(void *arg) // "машина, ожидающая заправки"
{
	pthread_mutex_lock(&mutex_fuel);

	while(fuel < 40) {
		printf("No fuel. Waiting...\n");

		pthread_cond_wait(&condition_fuel,&mutex_fuel); // ожидание сигнала от другого потока

		/* Эквивалент:
		pthread_mutex_unlock(&mutex_fuel)
		wait for signal on condition_fuel
		pthread_mutex_lock(&mutex_fuel)
		*/
	}
	// когда цикл завершился, заправляемся
	fuel -= 40;
	printf("Car got fuel. Now left: %d\n",fuel);

	pthread_mutex_unlock(&mutex_fuel);
	return NULL;
}

typedef void *(* routine_t) (void *);

int main(int argc, char *argv[])
{
	/*
	Условная переменная - идентификатор определенного сигнала, который можно либо подать, либо подождать.
	Подача сигнала не означает, что условие истинно, но сообщает о том, что оно могло измениться.
	Во время ожидания сигнала происходит разблокировка мьютекса, другой поток может подключиться и дождаться значения.

	Добавление:

	Немного изменяем нашу программу: теперь у нас 4 потока, представляющие машины и 1 поток - заправку.
	Возникает проблема: топлива на всез не хватает. Да и распределяется оно вызовом pthread_cond_signal случаный образом.
	Мы не можем в данной реализации отправить топливо какому-то конкретному потоку.

	Увеличим поступление топлива до 60 единиц за раз, получим вывод:

	No fuel. Waiting...
    No fuel. Waiting...
    No fuel. Waiting...
    No fuel. Waiting...
    Filling fuel: 60
    Car got fuel. Now left: 20
    Filling fuel: 80 <- на этом этапе могло бы заправиться 2 машины
    Car got fuel. Now left: 40 <- но только одна машина заправилась, только один поток получил сигнал
    Filling fuel: 100
    Car got fuel. Now left: 60
    Filling fuel: 120
    Car got fuel. Now left: 80
    Filling fuel: 140

	Как сделать так, чтобы активировались все потоки ? Использовать pthread_cond_broadcast() !

	Получаем новый вывод:

	No fuel. Waiting...
	No fuel. Waiting...
	No fuel. Waiting...
	Filling fuel: 60
	Car got fuel. Now left: 20
	No fuel. Waiting... <- сигнал получили все потоки, заправился только один
	No fuel. Waiting...
	No fuel. Waiting...
	Filling fuel: 80 
	Car got fuel. Now left: 40 <-]
	Car got fuel. Now left: 0  <-] - заправилось сразу две машины, сигнал получили все потоки, первые два заправились
	No fuel. Waiting...
	Filling fuel: 60
	Car got fuel. Now left: 20
	Filling fuel: 80
	Filling fuel: 140
	No fuel. Waiting...

	*/
	pthread_t th[5];
	routine_t routines[2] = {car,fuel_filling};

	pthread_mutex_init(&mutex_fuel,NULL);
	pthread_cond_init(&condition_fuel,NULL);

	for(int i = 0;i < 5; i++) {
		if(i == 4) { // 1 поток - заправка
		 if(pthread_create(th + i,NULL,routines[1],NULL) != 0) {
			printf("Ошибка вызова pthread_create()\n");
			return 1;
		 }	
		}
		else { // 4 потока - машины
		 if(pthread_create(th + i,NULL,routines[0],NULL) != 0) {
			printf("Ошибка вызова pthread_create()\n");
			return 1;
		 }	
		}
	}

	for(int i = 0;i < 5; i++) {
		if(pthread_join(th[i],NULL) != 0) {
			printf("Ошибка вызова pthread_join()\n");
			return 2;
		}	
	}

	pthread_cond_destroy(&condition_fuel);
	pthread_mutex_destroy(&mutex_fuel);

	return 0;
}