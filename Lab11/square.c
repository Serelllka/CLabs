#include "square.h"

float _square (struct square *sq)
{
    return 0.5 * ((sq->x1 - sq->x2) * (sq->x1 - sq->x2) + (sq->y1 - sq->y2) * (sq->y1 - sq->y2));
}

float _perimetr (struct square *sq)
{
    return sqrt(((sq->x1 - sq->x2) * (sq->x1 - sq->x2) + (sq->y1 - sq->y2) * (sq->y1 - sq->y2)) * 8);
}
