#include <stdio.h>

int main(void) {

    int arr[10] = {14,25,68,32,74,12,2,99,1087,321};

    int *pointer_array = arr; // имя массива - указатель на его первый элемент
    // данную запись можно заменить следующий образом: int *pointer_array = &arr[0];

    printf("first element = %i\n",*arr); // first element = 14

    // можем также проводить с массивом индексные операции с помощью указателей
    printf("array: ");

    for(int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        printf("%i\t",*(arr + i)); // вывод всех элементнов массива
    }

    printf("\n");

    // за точку начало отчёта можем взять также и другие элементы массива
    int *pointer_second = arr + 1;

    printf("second element - %i\n",*pointer_second); // 25

    /*
    Формулы получения:
    * arr - указатель на первый элемент массива
    * arr + i - указатель на i-ый элемент массива
    * *(arr + i) - значение i-го элемента массива
    * *arr - значение первого элемента массива    
    */
    

    return 0;
}