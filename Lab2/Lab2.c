#include <stdio.h>
#include <string.h>
#include <math.h>


int main()
{
    float alpha;
    printf ("~~~~~~~~~~~~~~~Lab_2~~~~~~~~~~~~~~~\n");
    printf ("Enter alpha:\n");
    scanf ("%f", &alpha);
    float z1 = 0.5 * sin(4 * alpha) * sin(4 * alpha);
    float z2 = - 0.5 * sin(4 * alpha) * sin(4 * alpha);
    printf ("z1 is %.3f\nz2 is %.3f", z1, z2);
}
