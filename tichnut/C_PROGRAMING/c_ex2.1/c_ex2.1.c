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
}
