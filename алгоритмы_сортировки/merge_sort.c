#include <stdio.h>
#include <stdlib.h>

void merge_sort(int *, size_t); // сортировка слиянием
void merge(int *arr,int *arr1,size_t size1, int *arr2, size_t size2); // слияние массивов arr1 и arr2 в массив arr

int main(void)
{
	int nums[8] = {2,1,7,3,5,4,6,8};

	size_t size = sizeof(nums) / sizeof(nums[0]);

	merge_sort(nums,size);

	for(size_t i = 0; i < size; i++) printf(" %d",nums[i]);
	putchar('\n');

	return 0;
}


void merge(int *arr,int *arr1,size_t size1, int *arr2, size_t size2)
{
	size_t i = 0, j = 0, cnt = 0; // определяем счётчики
	size_t base_size = size1 ? (size1 < size2) : size2;

	while(i < size1 && j < size2) { // пока не закончились оба массива
		if(arr1[i] <= arr2[j]) {
			arr[cnt++] = arr1[i++];
		}
		else {
			arr[cnt++] = arr2[j++];
		}
	}

	while(i < size1) arr[cnt++] = arr1[i++]; // ещё остались элементы в первом массиве
	while(j < size2) arr[cnt++] = arr2[j++]; // ещё остались элементы во втором массиве
}

void merge_sort(int *arr, size_t n)
{
	if(n <= 1) return; // базовый случай

	size_t mid = n / 2; // определяем середину

	// дополнительные выделения памяти
	int *arr1 = malloc(sizeof(int) * mid);
	int *arr2 = malloc(sizeof(int) * (n - mid));

	// записываем данные в обе части массива
	for(size_t i = 0; i < mid; i++) arr1[i] = arr[i];
	for(size_t i = 0; i < (n - mid); i++) arr2[i] = arr[mid + i];

	// рекурсивный вызов для каждой половины
	merge_sort(arr1,mid);
	merge_sort(arr2,n - mid);

	// слияние отсортированных половин
	merge(arr,arr1,mid,arr2, n - mid);

	// освобождение памяти
	free(arr1);
	free(arr2);
}

