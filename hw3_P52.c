// Danny Pham
// 10-13-18
// Replace original P52 with SSE code

#include <string.h>
#include <stdio.h>
#include <emmintrin.h>

void P52(unsigned s[12])
{
  unsigned long x0,y0,z0,x1,y1,z1,x2,y2,z2,x3,y3,z3;
  for (int i = 0; i < 24; i++)
  {
    //Load, Rotate, and Store using SSE
    __m128i reg0 = _mm_loadu_si128((__m128i *)(s+0));
    __m128i o1 = _mm_or_si128(_mm_slli_epi32(reg0,24), _mm_srli_epi32(reg0,8));
    _mm_storeu_si128((__m128i *)(s+0),o1);

    x0 = s[0];
    x1 = s[1];
    x2 = s[2];
    x3 = s[3];

    __m128i reg1 = _mm_loadu_si128((__m128i *)(s+4));
    __m128i o2 = _mm_or_si128(_mm_slli_epi32(reg1,9), _mm_srli_epi32(reg1,23));
    _mm_storeu_si128((__m128i *)(s+4),o2);

    y0 = s[4];
    y1 = s[5];
    y2 = s[6];
    y3 = s[7];

    //__m128i reg2 = _mm_loadu_si128((__m128i *)(s+8));

    z0 = s[8];
    z1 = s[9];
    z2 = s[10];
    z3 = s[11];

    // Load in new x0, y0, z0 values
    __m128i reg3 = _mm_loadu_si128((__m128i *)(s+0));
    __m128i reg4 = _mm_loadu_si128((__m128i *)(s+4));
    __m128i reg5 = _mm_loadu_si128((__m128i *)(s+8));

    //s[8] = x0 ^ (z0 << 1) ^ ((y0 & z0) << 2);

    __m128i result1 = _mm_xor_si128(reg3,
    _mm_xor_si128(_mm_slli_epi32(_mm_and_si128(reg4, reg5),2),
    _mm_slli_epi32(reg5,1))
    );

    _mm_storeu_si128((__m128i *)(s+8), result1);

    //s[4] = y0 ^ x0 ^ ((x0 | z0) << 1);

    __m128i result2 = _mm_xor_si128(reg4,
    _mm_xor_si128(_mm_slli_epi32(_mm_or_si128(reg3, reg5),1),
    reg3)
    );

    _mm_storeu_si128((__m128i *)(s+4), result2);

    //s[0] = z0 ^ y0 ^ ((x0 & y0) << 3);

    __m128i result3 = _mm_xor_si128(reg5,
    _mm_xor_si128(_mm_slli_epi32(_mm_and_si128(reg3, reg4),3),
    reg4)
    );

    _mm_storeu_si128((__m128i *)(s+0), result3);


    if ((i % 4)== 0)
    {
      //Swap first with second and third with fourth elements

      __m128i set1 = _mm_set_epi32(s[1], s[0], s[3], s[2]);
      __m128i shu1 = _mm_shuffle_epi32(set1,0x1B);
      _mm_storeu_si128((__m128i *)(s+0), shu1);

      s[0] = s[0] ^ 0x9e377900 ^ (24-i);
    }

    else if ((i % 4)== 2)
    {
      //Swap first with third and second with fourth elements

      __m128i set2 = _mm_set_epi32(s[2], s[3], s[0], s[1]);
      __m128i shu2 = _mm_shuffle_epi32(set2,0x1B);
      _mm_storeu_si128((__m128i *)(s+0), shu2);

    }
  }
}
