#include <stdio.h>
#include <stdlib.h>

struct tag_vector {
    double x,y;
};

typedef struct tag_vector vector_t;
typedef struct tag_vector *vector_ptr; 

// функция сложения двух векторов
vector_ptr compose_vectors(vector_ptr v_1, vector_ptr v_2)
{
    vector_ptr new_vector = malloc(sizeof(vector_t));

    new_vector->x = v_1->x + v_2->x;
    new_vector->y = v_1->y + v_2->y;

    return new_vector;
}

void isum_vector(vector_ptr v_1, const vector_ptr v_2)
{
    v_1->x += v_2->x;
    v_1->y += v_2->y;
}

int main(void)
{
    vector_t vector_1 = {70.1,-9.3};
    vector_t vector_2 = {-45.2,8.3};

    vector_ptr vector_ptr = compose_vectors(&vector_1,&vector_2);

    printf("new_vector: %.2f %.2f\n",vector_ptr->x,vector_ptr->y); // new_vector: 24.90 -1.00

    isum_vector(&vector_1,vector_ptr); // сложим первый и второй вектор
    isum_vector(&vector_2, &(vector_t) {3.0,5.0}); // такой синтаксис тоже возможен

    printf("vector_1: %.2f %.2f\n",vector_1.x,vector_1.y); // vector_1: 95.00 -10.30
    printf("vector_2: %.2f %.2f\n",vector_2.x,vector_2.y); // vector_2: -42.20 13.30

    free(vector_ptr);
    return 0;
}