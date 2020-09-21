#include<stdio.h>
#include<math.h>
#include<string.h>

/**
Lab 8
**/

int main()
{
    char str1[100], str2[100];
    printf ("enter your first string:\n");
    scanf ("%s", str1);
    printf ("enter your second string:\n");
    scanf ("%s", str2);

    char str3[100];
    int n;
    strcpy(str3, str1);
    printf ("your string copied string: %s\n", str3);
    printf ("enter n:\n");
    scanf ("%d", &n);
    strncat (str3, str2, n);
    printf ("your string after concatenation: %s\n", str3);
    printf ("enter symbol:\n");
    char c;
    scanf ("%c", &c);
    scanf ("%c", &c);
    if (strchr (str1, c) == NULL)
    {
        printf ("this string have no that symbol\n");
    }
    else
    {
        printf ("your symbol on %d position\n", strchr(str1, c) - str1 + 1);
    }
    printf ("enter symbol:\n");
    scanf ("%c", &c);
    scanf ("%c", &c);
    if (strrchr (str1, c) == NULL)
    {
        printf ("this string have no that symbol\n");
    }
    else
    {
        printf ("your symbol on %d position\n", strrchr(str1, c) - str1 + 1);
    }
    printf ("length: %s", strcspn(str1, str2));
}
