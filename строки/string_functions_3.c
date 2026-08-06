#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    // 1. int sprintf(char *buffer, const char *format,...) - функция вывода форматированной строки, но в отличие от функции printf 
    // , которая выводит строку в stdout, выводит в строку buffer
    // первый аргумент - строка, заменяющая выходной поток, остальные аргументы - аргументы, аналогичные аргументам printf

    // 1-й пример
    char buffer[512];
    char name[10] = "Maksim";

    sprintf(buffer,"name = %s\n", name);

    printf("buffer: ");

    for(int i = 0; buffer[i] != '\n'; i++) {
        printf("%c",buffer[i]); // buffer: name = Maksim
    }

    printf("\n");

    // 2-й пример

    double width = 2.4, height = 3.2, depth = 8.6;
    char title[] = "info: "; // возможна проблема - это имя может быть сколько угодно большое и даже выходить за пределы массива info
    const char format[] = "%.4s: (%.2f x %.2f x %.2f)"; // решается эта проблема регулирование длины подставляемой строки внутри строки format (максимум - 4 символа теперь)

    // char info[100]; нам было бы удобнее формировать размер массива info на основе длины строки title, чтобы места точно хватило

    // для решения этой задачи нам не подходит присваивание массиву info переменной длины: char info[size] - неправильно
    // однако можем выделить память на массив info с помощью функции malloc; размер памяти будем вычислять на основе длины строки title

    size_t size = strlen(title) + 100;

    char *info = malloc(size);

    // если не удалось получить указатель на область памяти, то заканчиваем программу
    if(info == NULL) {
        printf("Malloc Error: memory is NULL");
        return 0;
    }

    sprintf(info, format, title, width, height, depth);

    for(int i = 0; info[i] != '\0'; i++) {
        printf("%c",info[i]); // info: (2.40 x 3.20 x 8.60)
    }

    printf("\n");

    // после все необходимых манипуляций с массивом  info необходимо освободить память
    free(info);

    // функцию sprinf часто используют для преобразования числа в строку

    // например:

    int x = -10; // необходимо преобразовать в строку {'-','1','0','\0'}

    char str_x[10]; // переменная строчного вида переменной x

    sprintf(str_x,"%i",x);

    for(int i = 0; str_x[i] != '\0'; i++) {
        printf("%c",str_x[i]); // -10
    }

    printf("\n");

    // 2. Функции(stdlib.h) для преобразования числовых данных из строк в соответсвующий числовой тип данных

    // int atoi(const char *str)

    int a = atoi("156978");

    printf("a = %d\n",a);

    // long atol(const char *str)

    long int b = atol("478563201785");

    printf("b = %ld\n",b);

    // long long atoll(const char *str)

    long long int c = atoll("12306547129312");

    printf("c = %lld\n", c);

    // double atof(const char *str)

    double d = atof("54.78");

    printf("d = %.2f\n",d);

    return 0;
}