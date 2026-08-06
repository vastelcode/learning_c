#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value; // значение в ячейке
	struct node *next; // ссылка на следующий элемент
} node_t;

node_t *push(node_t *head, int value)
{
	node_t *new_node = malloc(sizeof(node_t)); // выделяем место в памяти для новой ячейки
	
	if(new_node == NULL) {
		printf("Malloc Error: push->new_node\n");
		return NULL;
	}

	//  заносим значения в ячейку
	new_node->value = value;
	new_node->next = head;

	printf("Add %d\n",value);

	return new_node; // переопределяем верхний элемент
}

node_t *pop(node_t *head)
{
	if(head == NULL) return NULL;

	printf("Delete %d\n",head->value);

	node_t *ptr_next = head->next;  // запоминаем адрес следущего элемента
	free(head); // освобождаем текущий верхний элемент
	 
	return ptr_next; // переопределяем верхний элемент
}

void show(node_t *head)
{
	node_t *current = head; // определяем текущий элемент

	while(current != NULL) {
		printf("Value %d\n",current->value);
		current = current->next;
	}
}

int main(void)
{
	node_t *head = NULL; // определяем верхний элемент нашего списка

	head = push(head, 12); // добавление значений
	head = push(head, -16); // добавление значений
	head = push(head, 203); // добавление значений
	head = push(head, 986); // добавление значений

	show(head); // вывод всех значений

	head = pop(head); //удаляем значения
	head = pop(head); //удаляем значения
	head = pop(head); //удаляем значения
	head = pop(head); //удаляем значения

	return 0;
}