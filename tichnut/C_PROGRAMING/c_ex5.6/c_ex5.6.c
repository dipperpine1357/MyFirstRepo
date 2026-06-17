// Name: c_ex7.1.c
// Author: dipper pine
// Date: 15.6.2026
// Description: takes a string as an input and print if it is a palindrome
// imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define BUFFER_SIZE 64

int main() 
{
    //recive str
    char name[BUFFER_SIZE];
    printf ("enter str\n");
    fgets(name, BUFFER_SIZE, stdin);

    //CONVERT TO LOWER
    for (int i = 0; i < strlen(name); i++) 
    {
        if (isupper(name[i])) 
        {
            name[i] = tolower(name[i]);
        }
    }

    // delete spacess
    int len = strlen(name);
    char space = ' ';
    int good_letter,i;
    for (i = good_letter = 0; i < len; i++) 
    {
        if (name[i] >= 'a' && name[i] <= 'z')
        {
            name[good_letter++] = name[i];
        }
    }
    name[good_letter] = '\0';
    

    //check pol
    int letters = strlen(name);
    bool is_pol = true;
    int half_str = letters/2;
    int beggining_half = 0;
    int end_half = letters - 1;

    //go through the string
    while (beggining_half < end_half)
    {
        
        if (name[beggining_half] != name[end_half])
        {
            printf("no good\n");
            is_pol = false;
            break;
        }
        beggining_half = beggining_half + 1;
        end_half = end_half - 1;


    }
    if (is_pol)
    {
        printf("very good\npalindrome !!!!\n");
    }
    system("pause");
    return 0;

}