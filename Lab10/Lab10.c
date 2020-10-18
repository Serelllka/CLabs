#include<stdio.h>
#include<math.h>
#include<string.h>

/**
Lab 10
**/

float lenght (float x1, float y1, float x2, float y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int** dist (float dotsX[], float dotsY[], int n)
{
    float **matr = (float**)malloc(n * sizeof(float*));
    for (int i = 0; i < n; ++i)
    {
        matr[i] = (float*)malloc(n * sizeof(float));
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            matr[i][j] = lenght(dotsX[i], dotsY[i], dotsX[j], dotsY[j]);
        }
    }

    return matr;
}

int* toMas (int x, int *t)
{
    int k = 0;
    int a = x;
    while (a != 0)
    {
        k++;
        a /= 10;
    }
    int *mas = malloc(k * sizeof(int));
    for (int i = 0; i < k; ++i)
    {
        mas[i] = x % 10;
        x /= 10;
    }
    *t = k;
    return mas;
}

int main()
{
    float dotsX[1000];
    float dotsY[1000];
    int n, x;
    printf ("Enter count  of dots:\n");
    scanf ("%d", &n);

    int i, j;
    for (i = 0; i < n; ++i)
    {
        printf ("Enter dot number %d (x y):\n", i + 1);
        scanf ("%f %f", &dotsX[i], &dotsY[i]);
    }

    printf ("Enter value:\n");
    scanf ("%d", &x);

    int t = 0;
    float** matr = dist (&dotsX, &dotsY, n);
    int* mas = toMas (x, &t);

    for (i = 0; i < n; ++i)
    {
        printf ("%d :", i + 1);
        for (j = 0; j < n; ++j)
        {
            printf ("%f ", matr[i][j]);
        }
        printf ("\n");
    }

    for (i = 0; i < t; ++i)
    {
        printf ("%d ",  mas[t - i - 1]);
    }

}
