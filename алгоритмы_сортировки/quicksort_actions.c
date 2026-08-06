// подключение стандартных библиотек
#include <stdio.h>
#include <stdlib.h>

// подключение вспомогательных модулей
#include "quicksort.h"


void quicksort(int arr[], int left, int right)
{

	if(left >= right) return;

	int i = left, j = right;
	
	int pivot = arr[(left + right) / 2]; // определяем опорный элемент

	while(i <= j) {
		// сдвигаем левую и правую границы
		while(arr[i] < pivot) i++;
		while(arr[j] > pivot) j--;

		if( i <= j) {
			// алгоритм трёх стаканов
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;

			// сдвигаем индексы
			i++;
			j--;
		}
	}

	quicksort(arr,left,j);
	quicksort(arr,i,right);
}