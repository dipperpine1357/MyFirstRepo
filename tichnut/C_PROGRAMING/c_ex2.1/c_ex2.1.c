// Name: c_ex7.1.c
// Author: dipper pine
// Date: 15.6.2026
// Description: no perpuse
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
