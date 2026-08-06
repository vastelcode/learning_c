// Как запускать другие программы с использованием exec() в Си
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

// путь до программы, которая будет запущена
#define PATH_PROGRAMM "/home/maksim/programms_c/процессы/bin/fork"
#define PATH_FILE "bin/print"

int main(int argc, char *argv[])
{
	/*
	Системный вызов exec() полностью заменяет вызывающий процесс процессом, который указан в аргументах вызова. Происходит вызов функции main() другой программы.
	В случае ошибки, функция exec() вернёт -1, в случае успеха - управление не будет возвращаться в вызывающий процесс.
	При вызове exec() не создаётся новый процесс, а проиходит замена, поэтому идентификатор процесса остаётся тем же, что и у вызывающего процесса.
	Весь текущий процесс заменяется при вызове exec(): его сегмент кода, сегмент данных, динамическая область памяти (куча), стек.

	Существует семь различных функций exec:

	- int execl(const char *pathname, const char *arg0, ...)
	- int execv(const char *pathname, char *const argv[])
	- int execle(const char *pathname, const char *arg0, ..., char *const envp[])
	- int execve(const char *pathname, char *const argv[], char *const envp[])
	- int execlp(const char *filename, const char *arg0, ...)
	- int execvp(const char *filename, char *const argv[])
	- int fexecve(int fd, char *const argv[], char *const envp[])

	Можем заметить, что первые 4 функции exec принимают полный путь до файла, следующие две - только имя файла, а последняя - файловый дескриптор.
	Также различаются способы передачи аргументов: символ 'l' (list) в названии функции обозначает список, 'v' (vector) - массив.
	Все списки аргументов должны заканчиваться нулевым указателем - (char *) 0, без приведения типов 0 будет распознан, как числовой аругмент командной строки,
	а не символ окончания списка.


	*/

	// Запустим программу fork в родительском процессе, которую мы разрабатывали до этого
	int pid = fork();

	if(pid == 0) {
		printf("Сообщение: дочерний процесс\n");
	}
	else {
		/* int status_exec = execv(PATH_PROGRAMM,argv);

		if(status_exec == -1) {
			perror("Ошибка вызова стороннего процесса");
			return errno;
		}

		printf("Это сообщение проигнорировано\n"); // так как управление не будет возвращено */

		// инициализируем массив аргументов
		char *arguments[] = {"Hello","World","!",NULL}; // массив аргументов должен заканчиваться нулевым указателем

		/* if(execvp(PATH_FILE,arguments) == -1) {
			perror("Ошибка вызова стороннего процесса");
			return errno;
		} */

		char *env_init[] = {"USER=unkwown"}; // инициализируем переменные окружения

		int fd = open(PATH_FILE,O_RDONLY); // открываем исполняем файл на чтение

		if(fd == -1) {
			perror("Ошибка открытия файла на чтение");
			return errno;
		}

		if(fexecve() == -1) {
			perror("Ошибка вызова стороннего процесса");
			return errno;
		}

	}

	/* Вывод 1(execv)
    Сообщение: дочерний процесс <- наша программа exec
    Message from process 65636 <- стороння программа fork
    Message from process 0
    Message from process 0
	*/

	/* Вывод 2 (execvp)
    Сообщение: дочерний процесс
    Аргумент: Hello
    Аргумент: World
    Аргумент: !
	*/

	/* Вывод 3 (fexecve)

	*/

	return 0;
}