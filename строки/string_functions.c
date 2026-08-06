#include <stdio.h>
#include <string.h>

int main(void) {

    // 1. Копирование строк

    // 1: ручной способ
    char source[100] = "Source string";
    char destination[10];

    size_t size_source = sizeof(source) / sizeof(source[0]);
    size_t size_destination = sizeof(destination) / sizeof(destination[0]);
    size_t size_target = (size_source < size_destination) ? size_source : size_destination;

    int i = 0;

    for(i; i < size_target - 1 && source[i] != '\0'; i++) {
        destination[i] = source[i];
    }

    destination[i] = '\0';

    printf("hand target = %s\n",destination); // Source st

    // 2: встроенные функции из файла string.h

    // char* strcpy(char* dest, const char* src);

    char src[100] = "Source string";
    char dest[10];

    strcpy(dest, src);

    printf("strcpy target = %s\n",dest); // Source string

   // char* strncpy(char* dest, const char* src,int max_len); - более безопасный вариант за счёт третьего аргумента

    char original[100] = "Source string";
    char copy[10];

    int max_length = sizeof(copy) - 1;

    strncpy(copy,original,max_length);

    copy[max_length] = '\0'; // полезная строка

    printf("strncpy target = %s\n",copy);  // Source st

    // 2. Определение длины строки

    // 1: ручные способы
    char string[] = "Qwerty";

    int length = sizeof(string) / sizeof(string[0]) - 1;

    printf("length = %i\n", length); // 6

    // в этом случае данная операция отработала корректно, так как мы не указывали явно размер строки и он определился при инициализации

    char string_2[10] = "Qwerty";

    int length_2 = sizeof(string_2) / sizeof(string_2[0]);

    printf("length_2 = %i\n", length_2); // 10

    //  а в этом случае несмотря на то, что строка имеет длину 6 символов + \0 итого 7, размер, выделенный под этот массив символов будет равен 10(значение при объявлении)

    char string_3[10] = "Qwerty";

    int j = 0;

    for(; string_3[j] != '\0'; j++);

    printf("length_3 = %i\n", j); // 6

    // этот способ гораздо более гибкий и работоспособный

    // 2: встроенные функция из файла string.h

    int len = strlen(string);

    printf("length = %i\n", len); // 6

    // длина строки - кол-во символов до нулевого символа

    // 3. Объединение строк

    // 1: ручной способ

    char hello[15] = "Hello, ";
    char world[10] = "World !";

    // определяем размер строки
    size_t s = sizeof(hello) / sizeof(hello[0]);

    // счётчик индекса записи
    int c = strlen(hello);

    for(int m = 0; c < s - 1&& world[m] != '\0'; c++, m++) {

        hello[c] = world[m];
    }

    hello[c] = '\0';

    puts(hello);

    // 2: встроенные функции из файла string.h

    // char* strcat(char *dest, const char *src) - добавляет абсолютно все символы из src в dest

    char name[10] = "Maksim";
    char surname[10] = " Vasiliev";

    strcat(name,surname);

    printf("full_name = %s\n",name); // Maksim Vasiliev (проблема - вышли за пределы размера массива name)
    
    // char* strncat(char *dest, const char *src,int max_add) - добавляет только определенное количество символов, определяемое 3 аргументом

    char name_wife[12] = "Arina";
    char surname_wife[7] = " Deeva";

    strncat(name_wife, surname_wife,4);

    surname_wife[sizeof(surname_wife) - 1] = '\0'; // важный момент: если символы были скопированы при ограничении(как в случае с strncat), 
    // то нулевой символ окончания строки скопирован не будет , и надо самостоятельно его поместить

    printf("full name wife = %s\n",name_wife); // Arina Dee (уже не выходим за пределы массива name_wife)

    return 0;
}