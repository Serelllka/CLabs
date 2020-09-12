#include <stdio.h>
#include <string.h>


int main()
{
    char str[31] = "";
    int x, y;
    printf ("~~~~~~~~~~~~~~~Lab_3~~~~~~~~~~~~~~~\n");
    printf ("Enter your number in octal system:\n");
    scanf ("%o", &x);
    printf ("Your number in decimal system: %d\n",x);
    printf ("Your number in hexadecimal system: %x\n",x);
    printf ("Your number in hexadecimal system with shifted bit: %x\n",x >> 2);
    printf ("Your reversed number in hexadecimal system: %x\n",~x);
    printf ("Enter your number in octal system:\n");
    scanf ("%x", &y);
    printf ("Result is: %x", x || y);
}
