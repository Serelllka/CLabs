#include<stdio.h>
#include<math.h>
#include<string.h>

/**
Lab 10
**/

double lenght (double x1, double y1, double x2, double y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int** dist (int dotsX[], int dotsY[], int n)
{
    int **matr = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i)
    {
        matr[i] = (int*)malloc(n * sizeof(int));
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

int* toMas (int x)
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
    return mas;
}

int main()
{
    int dotsX[1000];
    int dotsY[1000];
    int n, x;
    printf ("Enter count  of dots:\n");
    scanf ("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        printf ("Enter dot number %d (x y):\n", i);
        scanf ("%d %d", &dotsX[i], &dotsY[i]);
    }

    printf ("Enter value:\n");
    scanf ("%d", &x);

    int** matr = dist (&dotsX, &dotsY, n);
    int* mas = toMas (x);
}
