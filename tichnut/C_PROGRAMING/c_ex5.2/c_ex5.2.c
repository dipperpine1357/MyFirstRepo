// Name: c_ex7.1.c
// Author: dipper pine
// Date: 15.6.2026
// Description: this code calculates the length of an input string
// imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 64

int main() {
    char name[BUFFER_SIZE];
    int letters = 0;
    printf ("enter str\n");
    fgets(name, BUFFER_SIZE, stdin);
    int array_len = sizeof(name);

    for (letters=0; letters < array_len; letters++){

        if (name[letters] == '\n'){
            printf("there are %d chars in the string", letters);
            break;
        }
    }
    system("pause");
}