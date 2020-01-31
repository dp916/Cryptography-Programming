// Danny Pham
// 10-2-18
// GF multiplication

#include <stdio.h>

unsigned mult(unsigned a, unsigned b, unsigned modulus, unsigned degree)
{
    unsigned p1 = a;
    unsigned p2 = b;
    unsigned extra = 0;

    while (p1 != 0)
    {
        if ((p1 % 2) == 1)              // p1 has x^0 terms
        {
            p1 = p1 - 1;
            extra = extra ^ p2;         // extra + p2
        }

        p1 = p1 >> 1;                   // p1 / x
        p2 = p2 << 1;                   // p2 * x

        if (p2 & (1 << degree))         // p2 has x^n terms
        {
            p2 = p2 ^ modulus;          // p2 - x^n + modulus
        }
    }
    return (p1 * p2 + extra);
}
