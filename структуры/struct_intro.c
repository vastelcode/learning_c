#include <stdio.h>
#include <string.h>

struct coords {
    int x;
    int y;
    int z;
};

// типом поля структуры может быть другая структура

enum {name_length = 50, b_length = 20, s_length = 7};
enum {max_points = 10};


struct tag_info {
    char name[name_length];
    char last[name_length];

};

struct tag_person {
    struct tag_info full_name;
    char sex[s_length];
    unsigned short age;
    char b_data[b_length];
};

struct tag_array {
    int marks[b_length];
};

struct tag_point {
    double x,y,z;
};

int main(void)
{
    /*
    Структуры в языке Си нужны для объединения полей различных типов в один новый составной тип данных.
    Объявление структуры - описание нового составного типа в тексте программы.

    Синтаксис объявления структуры:
    struct [имя структуры] {
      [поля структуры]
    };

    Имя структуры указывать необязательно.

    На уровне машинных кодов структур не существует, структуры - лишь абстракция языка Си.
    При определении переменной типа некой структуры в памяти устройства выделяется нужный непрерывный участок байт, необходимый для всех полей структуры, при этом распологаются они друг за другом

    На месте, где проходит границы между полями структуры, компилятор может самостоятельно добавлять выравнивающие байты.

    */

    struct coords point = { // процесс иницализации
        .x = 14,
        .y = 25,
        .z = -8
    };

    /* можно и так инициализировать

    struct coords point = {14,25,-8};

    struct coords point = {10}; y и z будут иметь значение 0
    */

    point.x = 12; // присвоение другого значения

    // point.x есть ни что иное, как простая целочисленная переменная x, объявленная в структуре, поэтому можем совершать с ней всевозможные операции, что с обычными переменнами

    size_t sz_point = sizeof(point);
    size_t sz_struct = sizeof(struct coords);
    size_t sz_x = sizeof(point.x); // можем обращаться к конкретным полям point.x

    printf("size_point = %ld size_struct = %ld  size_x = %ld\n",sz_point, sz_struct,sz_x); // size_point = 12 size_struct = 12 size_x = 4

    printf("x = %d y = %d z = %d\n",point.x,point.y,point.z); // x = 12 y = 25 z = -8

    struct tag_person user = {
        .sex = "male",
        .age = 16,
        .b_data = "30.04.2010",
        .full_name = {"Maksim","Vasiliev"}
    };

    printf("sex = %s name = %s\n",user.sex,user.full_name.name); // sex = male name = Maksim

    strcpy(user.full_name.last,"Grenz");

    printf("surname = %s\n",user.full_name.last); // surname = Grenz

    // возможен такой функционал копирования структуры в другую
    struct tag_person people;

    people = user; // используем операцию присваивания

    printf("people_age = %d\n",people.age); // people_age = 16

    // можем копировать массивы друг в друга
    struct tag_array st_array = {
        {5,4,3,2,2,5,3,4,4,5}
    };

    struct tag_array other_array = st_array;

    printf("mark = %d\n",other_array.marks[0]); // mark = 5

    // массив из структур
    struct tag_point figure[max_points] = {{-5.6,2.1,-7.8}, {5.4,1.5,-5.2}, {6.3,7.4,-9.5}};
    
    printf("x of fist point = %.1f\n", figure[0].x); // -5

    return 0;
}