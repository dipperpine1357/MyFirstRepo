#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define BUFFER_SIZE 64

int main() {

    char name[BUFFER_SIZE];
    int age;
    printf ("enter dog's name\n");
    fgets(name, BUFFER_SIZE, stdin);

    // deletes the new line chaar in the strig
    name[strcspn(name, "\n")] = '\0';
    printf ("enter dog's age\n");
    scanf("%d", &age);
    age = age * 7;
    printf ("%s is %d old\n", name, age);
    system("pause");
}