#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 20

char *input(char *message, int max_length) 
{
    int i = 0, symbol; // объявление необходимых переменных

    char *response = malloc(max_length); // выделение памяти под результат

    // проверка на ошибку
    if(response == NULL) {
        printf("Malloc Error\n");
        return NULL;
    }

    printf("%s", message); // вывод сообщения

    // посимвольный ввод строки
    while((symbol = getchar()) != EOF && symbol != '\n' && i < max_length) {
        response[i++] = (char) symbol; // запись символа в строку
    }

    response[i] = '\0'; // заканчиваем строку

    return response;
}

int comparison(char *dest, const char *src) 
{

    int length_dest = strlen(dest), length_src = strlen(src); // определяем длины строк

    // сперва проверяем совпадение длин строк
    if(length_dest == length_src) {
        int i = 0;

        for(; i < length_dest; i++) {
            if (dest[i] != src[i]) {
                return -1;
            }
        }
        // если цикл дошёл до конца, то возвращаем 0
        if(i == length_dest) {
            return 0;
        }
    }
    else {
        return -1;
    }
}

int main(void) 
{

    int sym;

    int i = 0;

    char *s1 = input("",MAX_LEN);
    char *s2 = input("",MAX_LEN);

    int res = comparison(s1,s2);

    if(res == 0) {
        printf("Strings are equals\n");
    }

    free(s1);
    free(s2);
    
    return 0;
}