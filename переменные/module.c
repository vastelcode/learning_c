#include <stdlib.h>

int global_var = 144; // внешнее связывание

// в данном случае ключевое слово static запрещает использование этой глобальной переменной в других модулях программы
static int global_seed_radint = 0; // внутреннее связывание

// по аналогии состоят дела с функциями
static void print_hi(void)
{
    printf("Hi !");
}

int randint(int a, int b)
{
    int right = a, left = b;

    if (a > b) {
        right = a;
        left = b;
    }

    return rand() % (left - right + 1) + right;
}