// Функция fork() в Си

#include <stdio.h>
#include <unistd.h> // заголовочный файл, нужный для работы с fork

int main(int argc, char *argv[])
{
	/*
	Функция fork() создаёт копию вызывающего процесса. Возвращает целочисленное значение - идентификатор дочернего процесса. Вызывающтй процесс - родительский процесс.
	Когда мы доходим до вызова функции fork() рождается дочерний процесс, который начинает выполнять следующий сегмент кода одновременно с родительским процессом.

	Если мы вызвали n-раз функцию fork(), то в итоге мы получаем разветвление на 2^n процессов.
	*/

	// в этой программе у нас ДВА процесса
	// int pid = fork();
	// printf("Message from pid: %d\n",pid); // вывод будет выполнен дважды из копирования текущего процесса

	/*
	Message from pid: 37086 - родительский процесс
    Message from pid: 0 - дочерний процесс всегда имеет PID, равный нулю
	*/

	/* if(pid == 0) { // создаём ветвление на основе PID
		printf("Hello from child process\n");
	}
	else {
		printf("Hello from parent process\n");
	} */

	/*
    Message from pid: 39697
    Hello from parent process
    Message from pid: 0
    Hello from child process    
	*/

	// Можем создавать копию копии процесса за счёт повторного вызова fork()

	int pid = fork();
	
	if(pid == 0) { // можем создать три процесса, если вызывать fork только в том случае, если процесс дочерний
		fork();
	}

	printf("Message from process %d\n",pid);

	/*
	Message from process 45477
    Message from process 0
    Message from process 0
	*/

	return 0;
}