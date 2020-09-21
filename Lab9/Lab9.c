#include<stdio.h>
#include<math.h>
#include<string.h>

/**
Lab 9
**/

int main()
{
    int subscriptionFee, convLen, costPerMinute;

    printf ("Enter subscription Fee:\n");
    scanf ("%d", &subscriptionFee);
    printf ("Enter conversation length:\n");
    scanf ("%d", &convLen);
    printf ("Enter cost per minute:\n");
    scanf ("%d", &costPerMinute);
    while (costPerMinute < subscriptionFee / 499)
    {
        printf ("Enter correct cost per minute:\n");
        scanf ("%d", costPerMinute);
    }
    printf ("Your monthly bill: %d\n", subscriptionFee + (convLen - 499) * costPerMinute);
    int n;
    printf ("Enter your numeral:\n");
    scanf ("%d", &n);
    if (n > 9 || n < 0)
    {
        printf ("Enter correct numeral:\n");
        scanf ("%d", &n);
    }
    n = '0' + n;
    printf ("%d", n);
}
