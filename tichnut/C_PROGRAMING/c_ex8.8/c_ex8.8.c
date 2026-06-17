// Name: c_ex7.1.c
// Author: dipper pine
// Date: 15.6.2026
// Description: this code reads from a file path and prints the file content
// imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// this function recives a file path 
// returns how many chars are in it
int char_counter(const char* path)
{
    FILE *fptr;

    char temp_char;
    char *str;
    long size = 0;

    // Open a file in read mode
    fptr = fopen(path, "r");

    if (fptr == NULL)
    {
        printf("Not able to open the file.");
        return 0;
    }


    // count chars in the file
    while((temp_char = fgetc(fptr)) != EOF) 
    {
        size ++;
        //printf("%c", temp_char);
    }


    // close file
    fclose(fptr);
    return size;
}


// this func recives a string of a path
// returns a pointer to a string with the file's content in the heap
// when using this func u must free the pointer returned
char* get_content(const char* path)
{
    FILE *fptr;
    int size = char_counter(path);
    char* str_heap = malloc(size+2);
    if (str_heap == NULL) 
    {
        printf("error with malloc.");
        return NULL;
    }
    char temp_char;

    // Open a file in read mode
    fptr = fopen(path, "r");

    if (fptr == NULL)
    {
        printf("Not able to open the file.");
        return NULL;
    }
    if (str_heap == NULL) 
    {
        printf("error with malloc.");
        return NULL;
    }

    int current_str_location = -1;
    char* temp_char2 = str_heap;

    memset(str_heap, 0, size * sizeof(char));

    // adds charecters
    for ( int current_str_location; current_str_location <= size; current_str_location++)
    {
        
        temp_char = fgetc(fptr);
        str_heap[current_str_location] = temp_char;

    }
    str_heap[current_str_location] = '\0';

    // close file
    fclose(fptr);
    printf(" my str\n %s-\n", str_heap);
    return str_heap;
}



int main()
{
    char path[] = ("");
    printf("enter path of the txt file: like : \nC:\\dipper\\my_first_repo\\tichnut\\C_PROGRAMING\\c_ex8.8\\c_ex8.8.txt\n");
    scanf("%s", &path);

    // strip newline
    path[strcspn(path, "\n")] = '\0'; 

    char* str_heap = get_content (path);
    int size = char_counter(path);
    for (int current_str_location = 0; current_str_location < size; current_str_location++) 
    {
        printf("%c", str_heap[current_str_location], current_str_location);
    }

    system("pause");

    printf("freeing");
    free(str_heap);
    return 0;
}