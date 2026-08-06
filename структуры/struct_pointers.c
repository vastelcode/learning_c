#include <stdio.h>
#include <stdlib.h>


struct tag_vector {
    double x,y;
};


struct tag_vector *create_vector(double x, double y)
{
    /*
    struct tag_vector v = {x, y};
    return v; // возврат структуры влечёт копирование всего её содержимого в bias; сама же v перестаёт существовать*/

    struct tag_vector *ptr_v = malloc(sizeof(struct tag_vector));

    ptr_v->x = x;
    ptr_v->y = y;

    return ptr_v;
}


int main(void)
{
    struct tag_vector v = {1,2};
    struct tag_vector* pointer_v = &v; // объявили и инициализировали указатель на структуру

    (*pointer_v).x = 3; // изменили переменную x в структуре через указатель
    double y = (*pointer_v).y; // прочитали значение

    printf("new_x = %.2f\n",v.x); // new_x = 3.00
    printf("y = %.2f\n",y); // y = 2.00

    // но такой синтаксис работы с указателями на структуры не удобен и есть другой :

    pointer_v->x = 4.98; // аналог (*pointer_v).x = 4.98

    printf("new_x = %.2f\n",(*pointer_v).x); // new_x = 4.98

    // также можем динамически выделять памяти на структуры

    struct tag_vector *ptr_v = malloc(sizeof(struct tag_vector));

    ptr_v->x = 14.5;
    ptr_v->y = 54.97;

    printf("x = %.2f y = %.2f\n",ptr_v->x,ptr_v->y);

    free(ptr_v);

    struct tag_vector *ptr_bias = create_vector(4.5,61.7);

    struct tag_vector bias = *ptr_bias; // копируем содержимое ячеек памяти в переменую bias

    printf("bias_x = %.2f\n",bias.x); // bias_x = 4.50

    free(ptr_bias);

    return 0;
}