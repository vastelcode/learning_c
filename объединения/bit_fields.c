#include <stdio.h>


typedef struct date_time {
    unsigned day : 5; // от 0 до 31 (5 бит)
    unsigned month: 4; // от 0 до 15 (4 бита)
    unsigned year: 11; // от 0 до 2047 (11 бит)
    unsigned sec: 6; // и так далее
    unsigned min: 6;
    unsigned hour: 5;
} date; // 38 бит = 32 + 6 занимает вся структура

int main(void)
{
    /*
    В языке Си есть возможность объявлять структуры с целочисленными полями типа int 
    и дополнительно для каждого из них указывать, сколько бит они будут заниматься в памяти устройства.
    */

    date moment = {14,7,2026,32,3,23};

    printf("size = %lu\n",sizeof(date)); // 8 байт

    printf("moment = %02d/%02d/%d %02d:%02d:%02d\n",
     moment.day, moment.month, moment.year, moment.hour, moment.min, moment.sec); // 14/07/2026 23:03:32

    return 0;
}