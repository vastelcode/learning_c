#ifndef HASH_MAP_H

#include <stdio.h>
#include <stdbool.h>

#define HASH_MAP_H

typedef struct bucket { // структура для звена связного списка
	int key; // ключ
	int value; // значение
	struct bucket *next; // следующий элемент
} bucket_t;

typedef struct couple { // структура для пары ключ-значение
	int key, value;
} couple_t;

typedef struct map { // структура для определения хэш-таблицы
	bucket_t **data; // массив с данными
	size_t capacity; // вместимость массива
	size_t count; // счётчик элементов
} map_t;

size_t get_hash(size_t capacity,int key); // получение хэша из ключа
void insert(map_t *base,int key, int value); // добавление значения в хэш-таблицу
void show(map_t *base); // вывод всех элементов
couple_t **free_map(map_t *base,bool rehash); // освобождение хэш-таблицы
bucket_t *find(map_t *base,int key); // нахождение ключа в хэш-таблице
void delete_key(map_t *base,int key); // удаление значения по ключу
void rehash(map_t *base); // рехеширование таблицы
int get(map_t *base, int key); // получение значения по ключу

#endif