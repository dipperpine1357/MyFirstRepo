// Name: c_ex7.1.c
// Author: dipper pine
// Date: 15.6.2026
// Description: this code takes2 fraction struct compares their results
//              prints -1 if 1 is bigger then 2, returns 1 if it is the opposite
//              otherwise prints 0
// imports
#include <stdio.h>
#include <stdlib.h>

struct fraction 
{
    int numerator;
    int denominator;
}; 

// this function recives 2 fraction struct compares their results
// returns -1 if 1 is bigger then 2, returns 1 if it is the opposite
// otherwise returns 0
int compare(struct fraction frac_1, struct fraction frac_2)
{
    // multiply by 1.0 to get factorial output
    float res_1 = frac_1.numerator * 1.0 / frac_1.denominator;
    float res_2 = frac_2.numerator * 1.0 / frac_2.denominator;

    if (res_1 == res_2)
    {
        return 0;
    }
    if (res_1 < res_2)
    {
        return -1;
    }
    return 1;
}

int main()
{
    struct fraction frac_1, frac_2;

    // recive  fraction 1
    printf("let us take fraction 1\nenter numerator \n");
    scanf("%d", &frac_1.numerator);
    printf("let us take the denominator\n");
    scanf("%d", &frac_1.denominator);

    // recive  fraction 2
    printf("\nlet us take fraction 2\nenter numerator \n");
    scanf("%d", &frac_2.numerator);
    printf("let us take the denominator\n");
    scanf("%d", &frac_2.denominator);

    int result = compare(frac_1, frac_2);
    printf("%d\n", result);

    system("pause");

}