#include <stdio.h>

#define TOTAL_LEN 10

int main(void) {

    // операция копирования
    float func_1[100] = {2.4,-3.8,7.5,6.6,24.1,32.4};
    int func_2[50];

    size_t size_1 = sizeof(func_1) / sizeof(func_1[0]);
    size_t size_2 = sizeof(func_2) / sizeof(func_2[0]);
    size_t size = (size_1 < size_2) ? size_1 : size_2;


    for(int i = 0; i < size; i++) {
        func_2[i] = (int) func_1[i];
    }

    printf("%i\n",func_2[2]); // 7

    // вставка нового значения в произвольный элемент массива

    int marks[TOTAL_LEN] = {3,2,5};

    size_t size_marks = sizeof(marks) / sizeof(marks[0]);

    int position = 2;
    int target = 4;

    for(int k = size_marks - 1; k >= position; k--) {
        marks[k] = marks[k - 1];

        if(k == position) {
            marks[k] = target;
        }
    }

    printf("marks: ");
    for(int k = 0; k < size_marks; k++) {
        printf("%d\t",marks[k]);
    }

    printf("\n");

    // удаление значения из произвольного элемента массива

    int values[TOTAL_LEN] = {1,2,3,4,5,6};

    int del_index = 3;

    for(int j = del_index; j < TOTAL_LEN - 1; j++) {
        values[j] = values[j + 1];
    }

    printf("values: ");

    for(int j = 0; j < TOTAL_LEN; j++) {
        printf("%d\t", values[j]);
    }

    printf("\n");

    // сортировка выбором: построение чисел в массиве по возрастанию

    int arr[TOTAL_LEN] = {7,2,-9,4,3,1,12,54,-98,23};
    int pos;

    for(int i = 0; i < TOTAL_LEN - 1; i++) {
        pos = i;
        for(int j = i + 1; j < TOTAL_LEN; j++) {
            if(arr[pos] > arr[j]) {
                pos = j;
            }
        }

        if(pos != i) {
            int t = arr[i];
            arr[i] = arr[pos];
            arr[pos] = t;
        }
    }

    printf("array: ");
    for(int c = 0; c < TOTAL_LEN; c++) {
        printf("%d\t", arr[c]);
    }
    printf("\n");

    return 0;
}