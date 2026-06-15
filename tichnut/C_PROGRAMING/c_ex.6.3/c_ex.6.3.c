// Name: c_ex7.1.c
// Author: dipper pine
// Date: 15.6.2026
// Description: program that asks for values for two fractions (numerator and denominator for each), and
//              computes and prints the sum of the fractions
// imports
#include <stdio.h>
#include <stdlib.h>

struct fraction 
{
    int numerator;
    int denominator;
}; 

struct result 
{
    int sum;
}; 


int main() 
{
    struct fraction frac_1, frac_2;
    int dev_1, dev_2;


    printf("enter numerator 1\n");
    scanf("%d", &frac_1.numerator);
    printf("enter denominator 1\n");
    scanf("%d", &frac_1.denominator);

    printf("enter numerator 2\n");
    scanf("%d", &frac_2.numerator);
    printf("enter denominator 2\n");
    scanf("%d", &frac_2.denominator);

    dev_1 = frac_1.numerator / frac_1.denominator;
    dev_2 = frac_2.numerator / frac_2.denominator;
    struct result my_result = {dev_1 + dev_2};
    printf("sum is : %d \n", my_result.sum);

    system("pause");
}
