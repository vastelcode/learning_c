#include <stdio.h>

void print_all(int N)
{
	for(int i = 0; i < N; i++) printf("%d",i);
	putchar('\n');
}

int main(void)
{
	print_all(10);
	return 0;
}