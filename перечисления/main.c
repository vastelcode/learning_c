#include <stdio.h>


int is_even(int x)
{
    return x % 2 == 0;
}

enum colors {red, green, blue} wnd_colors; // можем сразу определять переменные такого типа

// можно также задавать свои собственные значения констант в перечислениях
enum commands {enter = 25, exit = 0, login = 36};

enum any {one = 131, two, three}; // если последующие значение неопределены , то идёт увеличение значения на 1 с каждым элементом

enum { // можно не указывать имя набора
    go = 0x1f00,
    stop = 0x001,
    forward = go,
    run = 0x00a2,
    back = run - 1 // использовать константные значения тоже можно при определении перечисления
} actions, variables_actions; // глобальное объявление двух переменных


typedef unsigned char byte; // теперь вместо unsigned char можем использовать имя byte

typedef enum {
    buffer_size = 1048,
    element_size = 64,
    byte_size = 8
} SIZE;

typedef int (* pointer_even) (int); // заменили указатель на функцию новым типом

int main(void) 
{

    /*
    Перечисление (enum) - тип данных, для определения набора целочисленных констант.
    Синтаксис объявления перечислений: enum <идентификатор> {набор констант};

    Когда мы определяем перечисления типа enum мы создаём тип данных, который можем использовать в программе.

    В языке Си существует директива typedef, которая позволяет задавать пользовательское имя типа.
    */

    printf("red = %d green = %d blue = %d\n",red,green,blue); // принимают соответствующие значения 0, 1 и 2
    printf("enter = %d exit = %d login = %d\n",enter,exit,login); // enter = 25 exit = 0 login = 36
    printf("one = %d two = %d three = %d\n",one,two,three); // one = 131 two = 132 three = 133

    enum commands user_command = enter;

    switch(user_command) {
        case enter:
           printf("Enter\n");
           break;
        case exit:
           printf("Exit\n");
           break;
        case login:
           printf("Login\n");
           break;
        default:
           printf("Exit\n");
           break;   
    }

    byte byte_1 = 240;

    SIZE user_input_size;

    pointer_even even = is_even;

    printf("is_even(5) = %d\n",even(5));

    return 0;
}