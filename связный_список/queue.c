// Реализация структуры данных "Очередь" на основе связного списка

#include <stdlib.h>
#include <stdio.h>

typedef struct node {
	int value;
	struct node *next;
} node_t;

void push(node_t **head, int value) // добавление в конец списка
{
	if(*head == NULL) {
		*head = malloc(sizeof(node_t)); // выделям память на начало списка

		if(*head == NULL) {
			printf("Malloc Error: push->head\n");
			return;
		}

		// заносим значения
		(*head)->value = value;
		(*head)->next = NULL;

	    printf("Add %d\n",value);

		return;
	}

	node_t *new_node = malloc(sizeof(node_t)); // создаём новый элемент списка

	if(new_node == NULL) {
		printf("Malloc Error: push->new_node\n");
		return;
	}

	// заносим значения
	new_node->value = value;
	new_node->next = NULL;

	printf("Add %d\n",value);

	// ищем конец списка
	node_t *end = *head;

	while(end->next != NULL) {
		end = end->next;
	}

	end->next = new_node; // записываем в конец списка новый элемент
}

void shift(node_t **head) // удаление из начала
{
	if(*head == NULL) return; // если нечего удалять, то пропуск

	printf("Delete %d\n",(*head)->value);

	node_t *next_ptr = (*head)->next;

	free(*head);

	(*head) = next_ptr;
}

void show(node_t *head) // вывод всех элементов списка
{
	if(head == NULL) return;

	node_t *ptr = head;

	printf("queue:");

	while(ptr != NULL) {
		printf(" %d",ptr->value);
		ptr = ptr->next;
	}

	putchar('\n');
}

int main(void)
{
	// инициализируем значения начала списка
	node_t *head = NULL;

	push(&head,101);
	push(&head,35);
	push(&head,96);
	push(&head,12);

	show(head);

	shift(&head);
	shift(&head);
	shift(&head);
	shift(&head);

	return 0;
}