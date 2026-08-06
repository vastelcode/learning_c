#include <stdio.h>
#include <stdarg.h> // в данном файле описан тип va_list

int sum(int count, ...) // мы обязательно должны передать обычный параметр, который будет определять кол-во вариадических параметров
{
    int s = 0;

    va_list arg;

    va_start(arg,count); // делаем так, чтобы arg ссылался на аргумент после count
    
    for (int  i = 0; i < count; i++) {
        s += va_arg(arg, int);
    }

    va_end(arg); // обязательный вызов

    return s;
}

int main(void) {

    int s = sum(4,12,15,36,85);

    printf("sum = %i\n",s); // sum = 148

    return 0;
}