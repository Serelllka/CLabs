#include<stdio.h>

/**
Lab 5
**/

int main()
{
    int mas[7] = {23, 5678, 2, 564, 365, 77, 443};
    int matrA[2][2] =
    {
        1, 1,
        0, 1
    };
    int matrB[2][2] =
    {
        2, 0,
        3, 0
    };
    int matrC[2][2];

    printf ("Elements of massive are:\n");
    for (int i = 0; i < 7; ++i)
    {
        printf ("%d ", mas[i]);
    }

    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            for(int k = 0; k < 2; k++)
            {
                matrC[i][j] = matrA[i][k] * matrB[k][j];
            }
        }
    }
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            printf ("%d ",matrC[i][j]);
        }
        printf ("\n");
    }

}
