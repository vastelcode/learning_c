#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLS 3

// Вместо того, чтобы передавать в функцию сами значения x и y , передаём указатели на эти переменные
void change_xy(int *x, int *y)
{
    int val = *x;
    *x = *y;
    *y = val;
}

int count_sum(int *array, int length) {
    int sum = 0;

    for(int i = 0; i < length; i++) {
        sum += array[i];
    }

    return sum;
}

// ИСПРАВИТЬ !!!!!!!!
/* // функция фильтрации целочисленных массивов по чётности
int *filter_even(int *array, size_t length) // можно заменить на запись (int array[], size_t length), чтобы подчеркнуть, что это именно массив
{
    // ошибка: при передаче указателя на массив в функцию также необходимо передать его длину
    // вычисление длины массива внутри функции ошибочка , так как операция sizeof(array) - вычислит размер указателя(8 байт в моей ОС), а это совсем не то, что нужно

    int *new_array = malloc(sizeof(int) * length);
    // ошибка: int *new_array = malloc(length) - length - это длина массива, то есть кол-во элементов в массиве array
    // а функция malloc выделяет БАЙТЫ в памяти, то есть в данном случае выделится 9 байт, что неверно, ибо размер int = 4 байта, то есть всего два элемента

    if (new_array == NULL) {
       
    }

    for(int i = 0, j = 0; i < length; i++) {

        if(array[i] % 2 == 0) {
            *(new_array + j) = array[i];
            j++;
        }
    }

    return new_array;
}

void print_array(int *array,size_t length ,char *name) 
{

    printf("%s", name);

    for(int i = 0; i <= length; i++) {
        printf("%i ",array[i]);
    }

    printf("\n");
} */

// функции также могут возвразать указатели

const char* find_space(const char string[])
{
    while(*string != '\0') {
        if(*string == ' ') {
            return string;
        }
        string++;
    }
}

void show_arr2d(short (* arr)[COLS], int rows) // можем передавать указатель на двумерный массив; также передаём первую размерность
{
    for(int i = 0; i < rows; i++) {
        printf("row %i: ",i);
        for(int j = 0; j < COLS; j++) {
            printf("%i ",arr[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{

    // Указатели - ключевой инструмент для изменения значения локальных переменных внутри функций
    // Также указатели мы передаём в качестве аргументов функции в том случае, если необходимо передать массив

    int x = 5, y = 10;

    change_xy(&x, &y);

    printf("x = %i\ty = %i\n",x,y); // x = 10 y = 5

    int numbers[] = {57,45,62,30,95,122,65,107,24};

    int sum = count_sum(numbers,sizeof(numbers) /  sizeof(numbers[0]));

    printf("sum = %d\n", sum); // sum = 607

    const char username[] = "vastel hanter";

    const char *pointer_space = find_space(username);

    printf("pointer_string = %p\tpointer_space = %p\n", username,pointer_space);

    short arr[][COLS] = {{1,2,3},{4,5,6}};

    // вычисление кол-во строк
    size_t bytes = sizeof(arr);
    size_t bytes_rows = sizeof(arr[0]);
    int rows = bytes / bytes_rows;

    show_arr2d(arr,rows);

    /* size_t length = sizeof(numbers) / sizeof(numbers[0]);

    int *even_numbers = filter_even(numbers, length); // имя массива есть ни что иное, как указатель на ту непрерывную область памяти, где хранятся его значения

    size_t length_filtered = sizeof(even_numbers) / sizeof(even_numbers[0]);

    print_array(even_numbers,length_filtered ,"even: ");

    free(even_numbers); */

    return 0;
}