// подключение стандартных библиотек
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// подключение вспомогатльных модулей
#include "hash_map.h"

void destroy_map(map_t *base) {
    if (!base) return;
    free_map(base, false);   // освобождает узлы и массив, обнуляет base->data
    free(base);          // освобождаем структуру
}

int main(void)
{
	// выделяем память на структуру таблицы
	map_t *base = malloc(sizeof(map_t));

	// иницализируем значения
	base->count = 0;
	base->capacity = 10;

	// выделяем память на массив с данными
	base->data = malloc(sizeof(bucket_t) * base->capacity);
	
	// 2. Вставляем пары с коллизиями (ключи 5,15,25 -> бакет 5; 3,13 -> бакет 3)
    printf("--- Вставка элементов ---\n");
    insert(base, 5, 50);
    insert(base, 15, 150);
    insert(base, 25, 250);
    insert(base, 3, 30);
    insert(base, 13, 130);

    printf("Таблица после вставки (capacity = %zu, count = %zu):\n", base->capacity, base->count);
    show(base);
    printf("\n");

    // 3. Поиск существующего и отсутствующего ключей
    printf("--- Поиск ---\n");
    int key_to_find = 15;
    bucket_t *b = find(base, key_to_find);
    printf("find(%d) -> %s (value = %d)\n", key_to_find, b ? "найден" : "не найден", b ? b->value : -1);

    key_to_find = 99;
    b = find(base, key_to_find);
    printf("find(%d) -> %s\n", key_to_find, b ? "найден" : "не найден");

    // Используем get
    printf("get(15) = %d\n", get(base, 15));
    printf("get(99) = %d\n\n", get(base, 99));

    // 4. Удаление ключа
    printf("--- Удаление ключа 15 ---\n");
    delete_key(base, 15);
    printf("Таблица после удаления:\n");
    show(base);
    printf("\n");

    // 5. Добавляем элементы для вызова рехеширования (загрузка > 1.0)
    printf("--- Добавление элементов для рехеширования ---\n");
    insert(base, 35, 350);
    insert(base, 45, 450);
    insert(base, 55, 550);
    insert(base, 65, 650);
    insert(base, 75, 750);
    // На данный момент count = 5 (было 5, удалили 1 = 4, добавили 5 = 9)
    // При вставке следующего элемента count станет 10, capacity=10, factor=1.0 -> рехеширование
    printf("Вставляем 85 (должно вызвать рехеширование)...\n");
    insert(base, 85, 850);
    printf("После рехеширования (capacity = %zu, count = %zu):\n", base->capacity, base->count);
    show(base);
    printf("\n");

    // 6. Проверяем, что все данные сохранились
    printf("--- Проверка после рехеширования ---\n");
    printf("get(5) = %d\n", get(base, 5));
    printf("get(25) = %d\n", get(base, 25));
    printf("get(85) = %d\n", get(base, 85));
    printf("get(15) = %d (должен быть -1, т.к. удалён)\n", get(base, 15));
    printf("\n");

    // 7. Освобождение памяти
    printf("--- Освобождение таблицы ---\n");
    destroy_map(base);
    printf("Память освобождена.\n");

	return 0;
}