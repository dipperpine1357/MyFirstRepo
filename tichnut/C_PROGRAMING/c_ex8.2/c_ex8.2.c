// Name: c_ex7.1.c
// Author: dipper pine
// Date: 15.6.2026
// Description: this code takes a string and creats a 
//              copy in the heap using malloc similarlly to strdup
// imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// this func recives a pointer to an str
// returns pointer to the copy in the heap or null if error occurred
char* strdup_func(const char *source)
{
    // reserve the neede place in the heap
    int str_size = strlen(source) + 1;
    char *str_heap;
    str_heap = malloc(sizeof(char) * str_size);

    // check if malloc complited successfully
    if (!*str_heap)
    {
        return NULL;
    }

    memcpy(&str_heap, &source, sizeof(source));

    return str_heap;

}


int main()
{
    
    char *dest_ptr = strdup_func("baduk");
    if (dest_ptr == NULL)
    {
        printf("error\n");
    }

    printf("copied the string\n%s\n", dest_ptr);
    system("pause");

    free(dest_ptr);
    return 0;
}