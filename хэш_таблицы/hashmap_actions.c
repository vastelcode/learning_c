// подключение стандартных библиотек
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// определяем константы
#define LOAD_FACTOR 1.0

// подключение вспомогательных модулей
#include "hash_map.h"

size_t get_hash(size_t capacity,int key)
{
    return (size_t)((key % (int)capacity + capacity) % capacity);
}

bucket_t *find(map_t *base,int key)
{
	if (base == NULL || base->data == NULL || base->count == 0) return NULL;

	size_t i = get_hash(base->capacity,key); // получаем индекс

	bucket_t *bucket = base->data[i]; // получаем ячейку

	if(bucket == NULL) return NULL;

	bucket_t *current = bucket; // получаем текущий элемент связного списка

	while(current != NULL) {
		if(current->key == key) return current;
		current = current->next;
	}

	return NULL;
}

int get(map_t *base, int key)
{
	bucket_t *target = find(base,key); // ищем элемент

	if(target == NULL) {
		printf("Not Founded Key\n");
		return -1;
	}

	return target->value;
}

void delete_key(map_t *base, int key)
{
	if(base == NULL || base->data == NULL || base->count == 0) return;

	bucket_t *target = find(base,key); // находим целевую ячейку

	if(target == NULL) return; // если нет такого элемента

	size_t i = get_hash(base->capacity,key); // получаем индекс ячейки

	bucket_t *current = base->data[i];

	if(current == target) {
		base->data[i] = current->next;
		free(current);
		base->count--;
		return;
	}

	while(current->next != target) { // ищем элемент перед целевым
		current = current->next;
	}

	current->next = target->next;
	free(target);
	base->count--;
}

void rehash(map_t *base)
{
	couple_t **couples = free_map(base,true); // освобождаем место старого массива и получаем массив пар ключ-значение

	if(couples == NULL) {
		printf("Malloc Error: rehash->couples\n");
		return;
	}

	base->capacity *= 2; // увеличиваем вместимость в два раза

	bucket_t **array = malloc(sizeof(bucket_t *) * base->capacity); // выделяем место под новым массив корзин

	if(array == NULL) {
		printf("Malloc Error: rehash->array\n");
		return;
	}

	for(size_t i = 0; i < base->capacity; i++) array[i] = NULL; // обнуляем массив

	base->data = array; // переназначаем массив с корзинами
	base->count = 0; // обнуляем счётчик элементов

	for(size_t i = 0; couples[i] != NULL; i++){ 
		insert(base,couples[i]->key,couples[i]->value); 
		free(couples[i]);
	}// добавляем каждую пару в новый массив

	// освобождаем массив с парами после использования
	free(couples);
}

void insert(map_t *base,int key, int value)
{
	if(base == NULL || base->data == NULL) return;

	bucket_t *existing = find(base,key); // ищем корзину по ключу

	if(existing != NULL) { // если ключ уже есть в таблице
		existing->value = value; // обновляем значение
		return;
	}

	double factor = (double) base->count / base->capacity; // определяем фактор загруженности

	if(factor >= LOAD_FACTOR) { // пора совершать рехеширование
		rehash(base);
	}

	size_t i = get_hash(base->capacity,key); // получаем индекс

	bucket_t *bucket = base->data[i]; // получаем элемент массива

	if(bucket == NULL) { // если элемент нулевой

		bucket = malloc(sizeof(bucket_t)); // выделяем память на элемент

		if(bucket == NULL) {
			printf("Malloc Error: insert->bucket\n");
			return;
		}

		// заносим значения в поля
		bucket->key = key;
		bucket->value = value;
		bucket->next = NULL;

		base->data[i] = bucket;
	}
	else {
		// определяем конечный элемент связного списка
		bucket_t *end = bucket;

		while(end->next != NULL) {
			end = end->next;
		}

		bucket_t *new_cell = malloc(sizeof(bucket_t)); // выделяем память под новый элемент

		if(new_cell == NULL) {
			printf("Malloc Error: insert->new_cell\n");
			return;
		}

		new_cell->key = key;
		new_cell->value = value;
		new_cell->next = NULL;

		end->next = new_cell; // добавляем в конец списка
	}
	
	
	base->count++; // увеличиваем счётчик элементов

}

void show(map_t *base)
{
	if(base == NULL || base->data == NULL || base->count == 0) return;

	for(size_t i = 0; i < base->capacity; i++) {

		bucket_t *bucket = base->data[i]; // получаем ячейку массива

		if(bucket == NULL) continue; // если ячейка пустая

		printf("bucket %zu:\n",i); // выводим номер ячейки

		bucket_t *end = bucket; // определяем конец списка

		while(end != NULL) {
			printf("key: %d value: %d\n",end->key,end->value);
			end = end->next;
		}
	}
}

couple_t **free_map(map_t *base,bool rehash)
{

	if(base == NULL || base->data == NULL) return NULL;

	couple_t **couples = NULL;

	if(rehash) { // если функция используется в ходе операции рехеширования
	   couples = malloc(sizeof(couple_t *) * (base->count + 1));

	   if(couples == NULL) return NULL;
	}
	
	size_t j = 0;

	for(size_t i = 0; i < base->capacity && j < base->count; i++) {
		bucket_t *bucket = base->data[i]; // получаем ячейку массива

		if(bucket == NULL) continue; // если ячейка пустая

		bucket_t *next; // определеям временный указатель

		while(bucket != NULL) { // освобождаем весь список
			
			if(rehash) {
				couple_t *couple = malloc(sizeof(couple_t)); // выделяем память для пары

				if(couple != NULL) {
				   // заносим значения в поля
				   couple->value = bucket->value;
				   couple->key = bucket->key;

				   couples[j++] = couple; // переносим пару в массив
				}

			}
			next = bucket->next;
			free(bucket);
			bucket = next;
		}

		base->data[i] = NULL; // обнуляем элемент
	}

	if (rehash) couples[j] = NULL; // символ окончания массива

	free(base->data); // освобождаем массив
	base->data = NULL;

	return couples;
}