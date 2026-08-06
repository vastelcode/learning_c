#include <stdio.h>
#include <stdlib.h>

#define LOAD_FACTOR 1.0

typedef struct node { // элемент связного списка
	int value; // значение
	int key; // ключ
	struct node *next; // следующий элемент
} node_t;

typedef struct {
	node_t **data; // данные
	size_t capacity; // вместимость массива
	size_t count; // кол-во элементов в массиве
} container_t;

int get_index(container_t *container,int key) // простейшая хэш-функция
{
	int index = key % container->capacity; // высчитыванием индекс

	return index;
}

void free_data(container_t *container) // освобождение массива data
{
    for(size_t i = 0; i < container->count; i++) { // проходимся по каждому элементу массива
	    node_t *node = container->data[i]; // получаем элемент массива

	    if(node == NULL) continue; // если нулевой, то двигаемся дальше

	    node_t *end = node; // определяем конец связного списка
	    node_t *next;

	    while(end->next != NULL) { // освобождаем все элементы списка
		    next = end->next;
		    free(end);
		    end = next;
	    }

	    free(end);

		container->data[i] = NULL; // обнуляем элемент
    }

	free(container->data); // освобождаем сам массив
	container->count = 0; // обнуляем счётчик элементов
}

void insert(container_t *container,int key, int value)
{
	if(container == NULL) return;
	if(container->data == NULL) return;

	double factor_load = container->count / container->capacity; // высчитываем фактор загрузки

	if (factor_load >= LOAD_FACTOR) {
		container->capacity *= 2; // увеличиваем размер

		node_t **array = malloc(sizeof(node_t) * container->capacity); // выделяем новый сегмент памяти в два раза больше

		if(array == NULL) {
			printf("Malloc Error: insert->array\n");
			container->capacity /= 2; // уменьшаем размер обратно
			return;
		}

		free_data(container); // освобождаем все данные

	}

	int index = get_index(container, key); // получаем индекс

	node_t *node = container->data[index];

	if(node == NULL) { // если нет первого узла
		node = malloc(sizeof(node_t));

		node->value = value;
		node->key = key;
		node->next = NULL;

		container->data[index] = node;
	}

	else {
		node_t *end = node;

		while(end->next != NULL) {
			end = end->next;
		}

		end->next = malloc(sizeof(node_t));
		end->next->value = value;
		end->next->key = key;
		end->next->next = NULL;

	}
}

void show(container_t *container)
{
	if (container == NULL) return;
	if(container->data == NULL) return;

	for(size_t i = 0; i < container->count; i++) {
		
	}
}

int main(void)
{
	container_t *container = malloc(sizeof(container_t));

	// инициализируем значения
	container->count = 0;
	container->capacity = 10;

	// выделяем память на массив
	container->data = malloc(sizeof(node_t *) * container->capacity);

	insert(container,5,10);


	free_data(container->data);
	free(container);

	return 0;
}