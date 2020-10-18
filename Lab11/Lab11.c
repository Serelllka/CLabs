#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "square.c"

/**
Lab11
**/

int main(int argc, char* argv[])
{
    struct square Square;
    if (argc > 1)
    {
        Square.x1 = atof(argv[1]);
        Square.y1 = atof(argv[2]);
        Square.x2 = atof(argv[3]);
        Square.y2 = atof(argv[4]);
    }
    else
    {
        printf ("Enter dots:\n");
        scanf ("%f %f %f %f", &Square.x1, &Square.y1, &Square.x2, &Square.y2);
    }
    printf("%.3f\n", _square(&Square));
    printf("%.3f", _perimetr(&Square));
}
