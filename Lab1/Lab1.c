#include <stdio.h>
#include <string.h>


int main()
{
    char str[31] = "";
    int x;
    printf ("~~~~~~~~~~~~~~~Lab_1~~~~~~~~~~~~~~~\n");
    printf ("Enter your string:\n");
    gets(str);
    //scanf ("%30s", &str);
    printf ("And now enter your number:\n");
    scanf ("%d", &x);
    printf ("Your string is: %s\n", str);
    printf ("Your number is: %d\n", x);
}
