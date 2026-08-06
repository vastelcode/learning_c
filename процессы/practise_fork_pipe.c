// Практичные примеры использования fork() и pipe()
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv)
{
	int arr[] = {1,2,3,4,7,8};
	size_t size = sizeof(arr) / sizeof(arr[0]);
	size_t start, end; // определяем переменные для стартового индекса и конца

	int fd[2]; // fd[0] - read fd[1] - write

	if(pipe(fd) == -1) {
		printf("An error ocurred pipe\n");
		return errno;
	}

	int id = fork();

	if(id == -1) {
		printf("An error ocurred fork\n");
		return errno;
	}

	if(id == 0) { // дочерний процесс
		start = 0;
		end = start + size / 2;
	}
	else { // родительский процесс
		start = size / 2;
		end = size;
	}

	int sum = 0;
	for(int i = start; i < end; i++) {
		sum += arr[i];
	}

	if(id == 0) {
		close(fd[0]);
		if(write(fd[1],&sum,sizeof(sum)) == -1) {
			printf("An error ocurred write\n");
			return errno;
		}
		close(fd[1]);
	}

	else {

		int sum_part = 0;

		close(fd[1]);
		
		if(read(fd[0],&sum_part,sizeof(sum_part)) == -1) {
			printf("An error ocurred read\n");
			return errno;
		}

		close(fd[0]);

		int total = sum + sum_part;

		printf("Total: %d\n",total);
		wait(NULL);
	}
	return 0;
}