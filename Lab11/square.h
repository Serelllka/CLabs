#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED

#include<math.h>

struct square
{
    float x1, y1, x2, y2;
};

float _square (struct square *sq);

float _perimetr (struct square *sq);

#endif // SQUARE_H_INCLUDED
