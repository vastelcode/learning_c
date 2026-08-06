#include <stdio.h>


typedef enum {
    union_var_none,
    union_var_ch,
    union_var_i,
    union_var_d
} type_var;

union tag_var {
    char var_ch;
    int var_i;
    double var_d;
};

typedef struct {
    union tag_var var;
    type_var  type;
} var_t ;

void show_var(var_t v)
{
    type_var type = v.type;
    union tag_var var = v.var;

    switch(type){
    case union_var_ch:
    printf("%c\n",var.var_ch);
    break;

    case union_var_i:
    printf("%i\n",var.var_i);
    break;

    case union_var_d:
    printf("%.2f\n",var.var_d);
    break;

    case union_var_none:
    puts("Underfined type var");
    break;

    }
}

int main(void)
{
    /*
    Синтаксис объявления объединения:
    union [имя объединения] {
    [поля]
    };

    Объединения отличаются от структур тем, что в структуре все её поля находятся в памяти последовательно друг за другом.
    А у объединений все их поля имеют одинаковый начальный адрес и в таком случае значения полей  могут затмевать друг друга, но объединения и не предназначены для хранения всех полей одновременно, а точно наоборот позволяют хранить только одно из многих значений.

    Например, нам в программе потребовалось создать уникальную переменную, которая может хранить либо тип char, либо int, либо double, в таком случае мы воспользуемся union.
    */

    union tag_var var;
    var.var_ch = 'h';

    printf("var_ch = %c var_i = %i var_d = %.2f\n",var.var_ch,var.var_i,var.var_d); // var_ch = h остальные поля принимают неопределенные значения

    var.var_i = -45;

    printf("var_ch = %c var_i = %i var_d = %.2f\n",var.var_ch,var.var_i,var.var_d); // var_i = -45 остальные поля принимают неопределенные значения

    // то есть объединение хранит только последнее значение

    /* show_var(var,union_var_i); // -45

    var.var_ch = 'u';

    show_var(var,union_var_ch); // u

    var.var_d = -3.14;

    show_var(var,union_var_d); // -3.14 */

    var_t v;

    v.var.var_ch = 'm';
    v.type = union_var_ch;

    show_var(v);

    return 0;
}