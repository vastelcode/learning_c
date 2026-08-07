// Перевод процессов в фоновый режим и возвращение на передний план. Обработчики сигналов
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define _POSIX_C_SOURCE 200809L

void handle_sigtstp(int signal)
{
	printf("Stop not allowed\n");
}

void handle_sigcont(int signal)
{
	printf("Welcome !\n");
}

int main(int argc, char *argv[])
{
	/*
	Фоновый и передний план

	Если мы при выполнении программы введём комбинацию клавиш Cntrl + Z, то мы
	отправим процессу сигнал SIGTSTP(аналогичный SIGSTOP ) и процесс будет ждать, пока
	ему отправят сигнал о продолжении (с помощью команды fg) в фоновом режиме (background).

	Пока процесс остановлен он находится в фоновом режиме.
	*/

	/* struct sigaction sa;
	sa.sa_handler = &handle_sigtstp;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGTSTP,&sa, NULL); */

	struct sigaction sa;
	sa.sa_handler = &handle_sigcont;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGCONT,&sa,NULL); // третий аргумент - можем сохранить предуыюдущую обработку сигнала

	// signal(SIGTSTP,&handle_sigtstp); - более короткий путь регистрации обработчика сигнала,
	// но имеет проблемы с переносимостью на другие версии/реализации


	int x;
	printf("Input number: ");
	scanf("%d",&x);
	printf("Result %d * 5 = %d\n",x,x * 5);
	
	return 0;
}