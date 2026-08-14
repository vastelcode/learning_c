// Пул потоков
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define THREAD_AMOUNT 4

pthread_mutex_t mutexTask;
pthread_cond_t condTask;

typedef struct {
	int arg1,arg2;
	void (* taskFunc) (int, int);
} task_t;

task_t taskQueue[256];
int taskCount = 0;

void sumAndProduct(int a, int b)
{	
	int sum = a + b;
	int product = a * b;

	printf("(%d, %d) Sum = %d Product = %d\n",a,b, sum,product);

}

void submitTask(task_t task)
{
	pthread_mutex_lock(&mutexTask);

    taskQueue[taskCount++] = task;

	pthread_mutex_unlock(&mutexTask);

	pthread_cond_signal(&condTask);
}

void executeTask(task_t *task)
{
	task->taskFunc(task->arg1,task->arg2);
}

void *startThread(void *arg)
{
	while(1) {

	    pthread_mutex_lock(&mutexTask);

		while (taskCount == 0) pthread_cond_wait(&condTask,&mutexTask);

	    task_t task = taskQueue[0];

	    for(int i = 0; i < taskCount - 1; i++) taskQueue[i] = taskQueue[i + 1];

	    taskCount--;
	    pthread_mutex_unlock(&mutexTask);

	    executeTask(&task);
	}
}

int main(int argc, char *argv[])
{
	srand(time(NULL));

	pthread_t th[THREAD_AMOUNT];

	pthread_mutex_init(&mutexTask,NULL);
	pthread_cond_init(&condTask,NULL);

	for(int i = 0; i < THREAD_AMOUNT; i++) {
		if(pthread_create(th + i, NULL, &startThread, NULL) != 0) {
			perror("Ошибка вызова pthread_create()");
			return 1;
		}
	}

	for(int i = 0; i < 10; i++) {

		int a = rand() % 100;
	    int b = rand() % 100;

		task_t new_task = {
			.taskFunc = &sumAndProduct,
			.arg1 = a,
			.arg2 = b
		};

		submitTask(new_task);

	}
	for(int i = 0; i < THREAD_AMOUNT; i++) {
		if(pthread_join(th[i],NULL) != 0) {
			perror("Ошибка вызова pthread_join()");
			return 2;
		}
	}

	pthread_mutex_destroy(&mutexTask);
	pthread_cond_destroy(&condTask);

	return 0;
}