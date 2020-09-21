#include<stdio.h>

/**
Lab 4
**/

int main()
{
    int number, result;

    printf ("Enter your number:\n");
    scanf ("%d", &number);
    result = (number < 1000) * (number > 100);
    printf ("Result is: %d\nEnter your the second number:\n", result);
    scanf ("%d", &number);
    printf ("Result is: %d", (number >> 21) % 2);
}
