#include<stdio.h>

/**
Lab 6
**/

int main()
{
    int n = 4;
    float masA[4] = {56.4, 36.5, 7.7, 44.3};

    for (int i = 0; i < n; ++i)
    {
        printf ("%.1f ", *(masA + i));
    }
    printf("\n");

    float *masB;
    masB = (float*)malloc(4 * sizeof(float));

    for (int i = 0; i < n; ++i)
    {
        scanf ("%f", &masB[i]);
    }

    printf ("Your massive:\n");

    for (int i = 0; i < n; ++i)
    {
        printf ("%.1f ", masB[i]);
    }

    free(masB);
}
