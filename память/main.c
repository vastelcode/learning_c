#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AMOUNT 10

// функция перевода массива температур по Фаренгейту в градусы Цельсия
double *transtemp(double temps[], int amount)
{
    // выделяем память под массив с новыми значениями
    double *new_temps = malloc(sizeof(double) * amount);

    // перевод значений
    for(int i = 0; i < amount; i++) {
        *(new_temps + i) = (temps[i] - 32) * 5 / 9;
    }

    // возвращаем указатель
    return new_temps;
}

void *append(short *data, size_t *length, size_t *capacity, short value)
{
    if(*length >= *capacity) {
        *(capacity) *= 2;

        short *array = realloc(data, *capacity); 

        if(array == NULL) {
            return data;
        }

        data = array;

        /* for(int i = 0; i < *length; i++) {
            array[i] = data[i];
        } */
        // memcpy(array, data, *length * sizeof(short));

       // free(data) больше не нужно, так как realloc автоматически освобождает память

        // data = array;
    }

    data[*length] = value;
    (*length)++;

    return data;
}

int main(void)
{
    /*
    До сих пор данные программы мы размещали в переменных. Данные для глобальных переменных хранятся в секциях .data и .bss - локальные переменные - в стековом фрейме.
    Вся остальная область памяти, за исключением той, что требуется для процессов, параллельных с нашей программой, не используется и называется кучей(heap).
    Язык Си предоставляет возможность самостоятельно выделять память в куче и освобождать её, когда она уже не нужна.

    Для таких операций в <stdlib.h> определены две основные функции:
    - void *malloc(size_t size) - для выделения size байтов памяти
    - void free(void *pointer) - для освобождения памяти по указателю pointer

    В том случае, когда память постоянно выделяется на нужды программы, но при этом не освобождается по её окончанию, то происходит процесс утечки памяти.
    В современных языках программирования, конечно же, речь не идёт о Си, существует процесс сборки мусора и программистам на этих языках можно не задумываться о столько низкоуровневых процессах.
    Суть сборки мусора: если на выделенную область памяти не ссылается ни один указатель, то она автоматически освобождается.

    Дополнительные функции работы с памятью:
    - void *calloc(size_t nmemb, size_t size) - выделение памяти под nmemb элементов, каждый из которых размеров size; происхожит автоматическое заполнение нулями
    - void *realloc(void *ptr, size_t length) - изменение размера ранее выделенной памяти по адресу ptr , новый размер определяется параметром length; если length == 0, то аналог функции free
    
    string.h
    - void *memcpy(void *restrict dst,const void *restrict src, size_t length) - копирование данных из массива src в массив dst
    - void *memmove(void *dst,const void *src, size_t length) - перемещение памяти

    */

    char *arr = malloc(4); // выделяем 4 байта из памяти
    int *pointer_int = malloc(sizeof(int)); // выделили память под одно значение типа int

    // в случае неуспешного выделения памяти вместо указателя будет возвращено значение NULL
    if(arr == NULL || pointer_int == NULL) {
        printf("Malloc Error: память не выделилась");
        return 1;
    }

    // можем пользоваться ячейками памяти, заносить в них данные с помощью указателей
    *arr = 'M';
    *(arr + 1) = 'a';
    *(arr + 2) = 'x';
    *(arr + 3) = '\0';

    printf("name = %s\n",arr); // name = Max

    *pointer_int = 487; // аналогично со вторым указателем

    // освобождаем ячейки памяти после использования
    free(arr);
    free(pointer_int);

    /* double fahr_temps[AMOUNT] = {14,-8,9,32,-74,10,52,30,-27,13};

    double *cels_temps = transtemp(fahr_temps, AMOUNT);

    printf("Fahr\tCels\n");

    for(int i = 0; i < AMOUNT; i++) {
        printf("%.2f\t%.2f\n",fahr_temps[i],*(cels_temps + i));
    }
    
    free(cels_temps);
    */

    size_t length = 0;
    size_t capacity = 10;

    short *data = malloc(sizeof(short) * capacity);

    for(int i = 0; i < 11; i++) {
        data = append(data,&length,&capacity, rand() % 40 - 20);
    }

    printf("length = %lu, capacity = %lu\n",length,capacity);

    for(int i = 0; i < length; i++) {
        printf("%i ",data[i]);
    }

    printf("\n");

    free(data);

    return 0;
}