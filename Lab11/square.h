#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED

struct square
{
    float x1, y1, x2, y2;
};

float _square (struct square *sq)
{
    return 0.5 * ((sq->x1 - sq->x2) * (sq->x1 - sq->x2) + (sq->y1 - sq->y2) * (sq->y1 - sq->y2));
}

float _perimetr (struct square *sq)
{
    return sqrt(((sq->x1 - sq->x2) * (sq->x1 - sq->x2) + (sq->y1 - sq->y2) * (sq->y1 - sq->y2)) * 8);
}

#endif // SQUARE_H_INCLUDED
