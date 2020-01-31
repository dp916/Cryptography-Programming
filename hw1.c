/**
Danny Pham - 1538
10-2-18

Invertible function by Feistel construction
*/

#include <stdio.h>

unsigned perm(unsigned x)
{
  unsigned int hi = x >> 16;
  unsigned int lo = x & 0xFFFF;
  hi = hi ^ (lo * lo);
  lo = lo ^ (hi * hi);
  x = (hi << 16) | (lo & 0xFFFF);

  return x;
}

unsigned inverse_perm(unsigned y)
{
  unsigned int hi = y >> 16;
  unsigned int lo = y & 0xFFFF;
  lo = lo ^ (hi * hi);
  hi = hi ^ (lo * lo);
  y = (hi << 16) | (lo & 0xFFFF);

  return y;
}
