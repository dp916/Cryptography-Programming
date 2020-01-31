// Danny Pham
// 9-30-18
// 48 byte permutation


#include <stdio.h>

int leftrot(unsigned num, int bits)
{
  int bit = 32 - bits;
  return num<<bits|num>>bit;
}

void P52(unsigned s[12])
{
  unsigned long x,y,z,temp;
  for (int i = 0; i < 24; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      x = leftrot(s[j],24);
      y = leftrot(s[j+4],9);
      z = s[j+8];

      s[j+8] = x ^ (z<<1) ^ ((y & z)<<2);
      s[4+j] = y ^ x ^ ((x | z) << 1);
      s[j] = z ^ y ^ ((x & y) << 3);
    }

      if ((i % 4)== 0)
      {
        temp = s[0];
        s[0] = s[1];
        s[1] = temp;
        temp = s[2];
        s[2] = s[3];
        s[3] = temp;
        s[0] = s[0] ^ 0x9e377900 ^ (24-i);
        }

      else if ((i % 4)== 2)
      {
        temp = s[0];
        s[0] = s[2];
        s[2] = temp;
        temp = s[1];
        s[1] = s[3];
        s[3] = temp;
      }
    }

    for (int i = 0; i < 12; i++)
    {
      printf("%08x\n", s[i]);
    }
}
