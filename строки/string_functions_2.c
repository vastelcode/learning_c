#include <stdio.h>
#include <string.h>

#define LEN_FILTERED_ARRAY 20

int main(void) {
    // 1. Функции сравнения строк

    // строки считаются равными, если равны их длины и все соответсвующие символы
    char s1[12] = "Hello";
    char s2[10] = "Hello";
    // эти строки считаются равными, несмотря на разные размеры массивов

    char s3[20] = "Maximal";
    char s4[20] = "Maximus";

    // 1: Ручной способ сравнивания строк представлен в файле comparsion_strings.c
    // 2: Встроенные функции string.h

    // int strcmp(const char *str1, const char *str2);

    if(strcmp(s3,s4) == 0) {
        printf("strcmp log: Strings are eaqual !\n");
    }
    else {
        printf("strcmp log: Strings are not eaqual !\n");
    }

    // int strncmp(const char *str1, const char *str2, size_t max_len); - сравнивниват не все символы переданных строк, а только первые max_len символы

    if(strncmp(s3, s4, 5) == 0) {
        printf("strncmp log: Strings are eaqual !\n");
    }
    else {
        printf("strncmp log: Strings are not eaqual !\n");
    }

    /*
    Функции сравнения возвращают целочисленное значение:

    - 0, если строки равны (то есть содержат одинаковые символы в одинаковом порядке).
    - Отрицательное число, если первая строка лексикографически меньше второй (то есть первый несовпадающий символ в первой строке имеет меньший код, чем соответствующий символ во второй).
    - Положительное число, если первая строка лексикографически больше второй (соответственно, больший код).
    */

    // пример использования: выбрать все строки, у которых первые два символы - sh

    const char *strings[] = {
        "Shoping", "Shop", "Shematic", "Super", "Car", "Sherif"
    };


    size_t length = sizeof(strings) / sizeof(strings[0]);

    for(int i = 0; i < length; i++) {

        if(strncmp(strings[i],"sh",2) == 0 || strncmp(strings[i],"Sh",2) == 0) {
            printf("%s\n",strings[i]);
        }
    }

    // 2. Функции поиска символов и подстрок

    // char *strchr(const char *str, int val); выполняет поиск символа слева-направо с кодом val в строке str(первое вхождение)

    char text[] = "Lorem ispum dolor";
    char symbol = 'r';
    char sub[] = " is";
    char sub_2[] = "more";

    // в результате получаем указатель на этот символ в строке
    char *pointer = strchr(text,(int) symbol);

    // если символ найден
    if(pointer != NULL) {
        int counter = 0;
        char *ptr = text;

        while((ptr + counter) != pointer) {
            counter++;
        }

        printf("index_strchr = %d\n",counter); // 2 - индекс в данном случае
    }
    
    // char *strrchr(const char *str, int val); аналогичный поиск справа-налево(последнее вхождение)

    // в результате получаем указатель на этот символ в строке
    char *pointer_right = strrchr(text,(int) symbol);

    // если символ найден
    if(pointer_right != NULL) {
        int counter = 0;
        char *ptr = text;

        while((ptr + counter) != pointer_right) {
            counter++;
        }

        printf("index_strrchr = %d\n",counter);  // 16 - индекс в данному случае
    }

    // char *strstr(const char *str, const char *find); поиск слева-направо подстроки find в строке str

    char *pointer_find = strstr(text,sub);

    if(pointer_find != NULL) {
        int counter = 0;
        char *ptr = text;
        while((ptr + counter) != pointer_find) {
            counter++;
        }
        printf("index_strstr = %i\n",counter); // на 5 индексе начинается подстрока sub
    }

    // char *strpbrk(const char *str, const char *find); поиск слева-направо любого символа из подстроки find в строке str

    char *pointer_find_subsym = strpbrk(text,sub_2);

    if(pointer_find_subsym != NULL) {
        int counter = 0;
        char *ptr = text;

        while((ptr + counter) != pointer_find_subsym) {
            counter++;
        }
        printf("index_strpbk = %i\n",counter); // на 1 индексе встречается символ o из подстроки more
    }
   
    return 0;
}