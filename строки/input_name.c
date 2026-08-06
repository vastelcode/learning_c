#include <stdio.h>

#define SIZE_NAME 10

int main(void) {

    char name[SIZE_NAME], sym;

    printf("Enter your name: ");

    int i = 0;

    while((sym = getchar()) != '\n' && sym != EOF && i < SIZE_NAME) {
        name[i++] = (char) sym;
    }

    name[i] = '\0';

    int age;

    printf("Enter your age: ");

    scanf("%i",&age);

    printf("Welcome, %s ! You are %i\n", name, age);

    return 0;
}