#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node { // структура для узла
	int value; // числовое значение узла
	struct node *left, *right; // указатели на потомков
} node_t;


node_t *create_node(int value) // создание узла
{
	node_t *node = malloc(sizeof(node_t)); // выделяем память из кучи под структуру

	if(node == NULL) {
		printf("Malloc Error: create_node->node\n");
		return NULL;
	}

	// заносим значения в поля
	node->value = value;
	node->left = NULL;
	node->right = NULL;

	return node;
}

void insert(node_t **root, int value) // вставка значения
{
	if(*root == NULL) { // если корень неопределён, то создаём его сами
		*root = create_node(value);
		return;
	}

	if(value > (*root)->value) { // если значение больше, идём вправо
		insert(&(*root)->right,value);
	}
	else if(value < (*root)->value ){ // иначе, идём влево
		insert(&(*root)->left, value);
	}
	else { // если равно, то никак не изменяем дерево, дубликаты не хранятся
		return;
	}
}

node_t *search(node_t *root, int value) // поиск значения
{
	if(root == NULL) return NULL; // не нашли совпадние и дерево закончилось
	if(root->value == value) return root; // нашли совпадение

	if(value > root->value) { // если больше, то идём по правой ветви
		return search(root->right,value);
	}
	else { // если меньше, то по левой ветви
		return search(root->left,value);
	}
}

void inorder(node_t *root) // симметричный обход дерева: Left Root Right
{

	if(root == NULL) return;

	inorder(root->left); // сначала левую часть

	printf("%d\n",root->value); // выводим значение

	inorder(root->right); // потом правую часть
}

void preorder(node_t *root) // прямой обход: Root Left Right
{
	if(root == NULL) return;

	printf("%d\n",root->value);

	preorder(root->left);

	preorder(root->right);
}

void postorder(node_t *root) // обратный обход: Left Right Root
{
	if(root == NULL) return;

	postorder(root->left);

	postorder(root->right);
	
	printf("%d\n",root->value);
}

int find_min(node_t *root) // нахождение узла с наименшим значением
{
	if(root != NULL) {
	   if(root->left == NULL) return root->value;

	   return find_min(root->left);
	}

	return -1;
}

void delete_node(node_t **root, int value) // удаление узла из дерева
{
	if((*root) == NULL) return; // значение не найдено

	if(value > (*root)->value) { // двигаемся по правой ветви
		delete_node(&(*root)->right,value);
	}
	else if(value < (*root)->value) { // двигаемся по левой ветви
		delete_node(&(*root)->left,value);
	}
	else { // нашли нужный узел
		if((*root)->left == NULL && (*root)->right == NULL) { // лист
			free((*root));
			(*root) = NULL;
		}
		else if(
			((*root)->left != NULL && (*root)->right == NULL)
			|| 
			((*root)->left == NULL && (*root)->right != NULL)
		) { // если только один потомок
			node_t *ptr = (*root);
			
			if((*root)->left != NULL) { // если только левый потомок
				node_t *ptr_left = (*root)->left;
				free((*root));
				(*root) = ptr_left;
			}
			else { // если только правый потомок
				node_t *ptr_right = (*root)->right;
				free((*root));
				(*root) = ptr_right;
			}
		}
		else { // оба потомка есть
			int min_value = find_min((*root)->right); // находим минимальное значение в правом поддереве

			(*root)->value = min_value; // присваиваем это значение

			delete_node(&(*root)->right,min_value); // удаляем дубликат
		}
	}
}

void free_tree(node_t *root)
{
	if(root == NULL) return;

	free_tree(root->left);

	free_tree(root->right);

	free(root);
}


int main(void)
{
	node_t *root = NULL; // создаём корень дерева

	// заполняем дерево значениями
	insert(&root,50);
	insert(&root,30);
	insert(&root,70);
	insert(&root,20);
	insert(&root,40);
	insert(&root,60);
	insert(&root,80);

	inorder(root);

	printf("--------\n");

	delete_node(&root,20);

	inorder(root);

	printf("--------\n");

	delete_node(&root,30);

	inorder(root);

	printf("--------\n");

	delete_node(&root,50);

	inorder(root);

	printf("--------\n");

	free_tree(root);

	return 0;
}