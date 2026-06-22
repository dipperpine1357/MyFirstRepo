// Name: c_ex7.1.c
// Author: dipper pine
// Date: 15.6.2026
// Description:  a program that simply echoes (prints)
//                  what ever is typed on the keyboard, until end-of-file is reached.
// very importent to look on the dumb ex in the book
// imports
#include <stdio.h>
#include <stdlib.h>


int main() {
    char string[64];
    fgets(string, 63, stdin);
    while (string != EOF) {
        printf(string);
        fgets(string, 63, stdin);
    }
    return EXIT_SUCCESS;
    return 0;
}
