#include<math.h>
#include "square.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
Lab11
**/

int main(int argc, char* argv[])
{
    struct square Square;
    Square.x1 = atof(argv[1]);
    Square.y1 = atof(argv[2]);
    Square.x2 = atof(argv[3]);
    Square.y2 = atof(argv[4]);
    printf("%.3f\n", _square(&Square));
    printf("%.3f", _perimetr(&Square));
}
