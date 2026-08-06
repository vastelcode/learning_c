#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value; // значение в ячейке
	struct node *next; // ссылка на следующий элемент
} node_t;

node_t *get_end(node_t *head)
{
	node_t *end = head; // определяем конечный элемент списка

	while(end->next != NULL) {
		end = end->next; // переходим к следующему элементу
	}

	return end;
}

node_t *unshift(node_t *head, int value) // добавление в начало
{
	node_t *new_node = malloc(sizeof(node_t)); // выделяем место в памяти для новой ячейки
	
	if(new_node == NULL) {
		printf("Malloc Error: unshift->new_node\n");
		return NULL;
	}

	//  заносим значения в ячейку
	new_node->value = value;
	new_node->next = head;

	printf("Add head %d\n",value);

	return new_node; // переопределяем верхний элемент
}

node_t *shift(node_t *head) // удаление из начала
{
	if(head == NULL) return NULL;

	printf("Delete head %d\n",head->value);

	node_t *ptr_next = head->next;  // запоминаем адрес следущего элемента
	free(head); // освобождаем текущий верхний элемент
	 
	return ptr_next; // переопределяем верхний элемент
}

node_t *push(node_t *head, int value) // добавление в конец
{

	node_t *new_node = malloc(sizeof(node_t)); // выделяем память на новый элемент

	if (new_node == NULL) {
		printf("Malloc Error: push->new_node\n");
		return NULL;
	}

	node_t *end = get_end(head); // определяем конечный элемент списка


	printf("Add end %d\n",value);

	// заносим значения в поля
	new_node->value = value;
	new_node->next = NULL;

	end->next = new_node; // теперь последний элемент ссылается на новый
}

node_t *pop(node_t *head) // удаление из конца
{
	node_t *prelast = head; // определяем предпоследний элемент

	while(prelast->next->next != NULL) {
		prelast = prelast->next;
	}

	node_t *end = prelast->next;

	printf("Delete end %d\n",end->value);

	free(end);
	prelast->next = NULL;
}

void show(node_t *head) // вывод всех элементов списка
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
	node_t *end = NULL;

	head = unshift(head, 12); // добавление значений в начало
	head = unshift(head, -16);
	end = push(head, 203);
	head = unshift(head, 986);

	show(head); // вывод всех значений

	head = shift(head); //удаляем значения из начала
	head = shift(head);
	end = pop(head);
	head = shift(head);

	return 0;
}