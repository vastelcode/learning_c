#include <stdio.h>
#define SIZE 10

int sq_rect(int w, int h) 
{
    return w * h;
}

int per_rect(int w,int h)
{
    return 2 * (w + h);
}

int is_even(int x)
{
    return x % 2 == 0;
}

int is_positive(int x)
{
    return x > 0;
}
void filter(int dest[],size_t size_dest, int src[], size_t size_src, int (* callback) (int))  // callback-функция - это функция, которая является параметром другой функции
{
    for(int i = 0; i < size_dest;i++) {
        dest[i] = 0; // чтобы не было мусорных значений
    }
    // фильтрация массива по callback-функции
    for(int i = 0,j = 0; i < size_src && j < size_dest; i++) {
        if(callback(src[i])) {
            dest[j] = src[i];
            j++;
        }
    }
}

void print_array(int array[], int max_len) {
    for(int i = 0; i < max_len; i++) {
        printf("%i ",array[i]);
    }
    printf("\n");
}

int main(void) {
    // В языке Си можно определять не только указатели на переменные, то есть данные, но и на функции.
    /*
    Синтаксис объявления указателя на функцию: <тип> (* <имя указателя>) (<типы параметров>)
    Синтаксис объявления массива из указателей на функцию: <тип> (* <имя массива>[<размер>]) (<параметры>)
    */

    printf("sq_rect = %p\n", sq_rect); // 0x638309c7d149 ; имя функции есть ни что иное, как указатель на неё

    // объявляем указатель на функцию sq_rect
    int (* pointer_func) (int, int) = sq_rect;

    int res = pointer_func(2,3); // вызов функции через указатель

    printf("res = %d\n", res); // res = 6

    pointer_func = per_rect; // может ссылаться на аналогичную по типу и параметрам функцию

    printf("res = %i\n",pointer_func(2,3)); // res = 10

    // определяем два массива
    int digits[] = {-3,4,10,11,-5,3};
    int even_digits[SIZE];
    int positive_digits[SIZE];

    // находим максимальную длину
    size_t size = sizeof(digits) / sizeof(digits[0]);

    // определяем указатель на функцию для проверки чётности
    int (* pointer_cb) (int) = is_even;
    int (* pointer_cb2) (int) = is_positive;

    // НОВОЕ: определяем массив из указателей на функции
    int (* criterials[]) (int) = {is_even, is_positive};

    // фильтрация массива
    // filter(even_digits,SIZE,digits,size,pointer_cb);
    // filter(positive_digits, SIZE, digits, size, pointer_cb2);

    filter(even_digits,SIZE,digits,size,criterials[0]);
    filter(positive_digits,SIZE,digits,size,criterials[1]);

    // вывод массивов
    print_array(even_digits, SIZE); // 4 10 0 0 0 0 0 0 0 0 
    print_array(positive_digits, SIZE); // 4 10 11 3 0 0 0 0 0 0

    return 0;
}