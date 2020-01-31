// Danny Pham
// 10-21-18
// Counter mode encryption program (incomplete)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NONCE_LEN 12
#define BLK_LEN 48
#define KEY_LEN 48

void P52(unsigned s[12]);

void P52BC(unsigned char *x, unsigned char counter[BLK_LEN], unsigned char key[KEY_LEN])
{
  int i;
  for (i = 0; i < BLK_LEN; ++i)
  {
    x[i] = counter[i] ^ key[i];
  }
}

int main(int argc, const char* argv[])
{
    size_t bytes_read;
    unsigned char key[KEY_LEN] = {0};
    unsigned char nonce[NONCE_LEN] = {0};
    unsigned char blk[BLK_LEN] = {0};
    unsigned char counter[BLK_LEN] = {0};
    unsigned char p52bc[BLK_LEN] = {0};


    /* Setup key and nonce. Report command line errors */
    if ((argc == 3) && (strlen(argv[1]) == 1) && (strlen(argv[2]) <= KEY_LEN) &&
                    ((argv[1][0] == 'e') || (argv[1][0] == 'd')))
    {
        if (argv[1][0] == 'e')
        {
            FILE *rand = fopen("/dev/urandom", "rb");
            fread(nonce, 1, NONCE_LEN, rand);
            fclose(rand);
            fwrite(nonce, 1, NONCE_LEN, stdout);
        }
        else
        {
            fread(nonce, 1, NONCE_LEN, stdin);
        }
        memcpy(key, argv[2], strlen(argv[2]));
    }
    else
    {
        fprintf(stderr, "usage: %s d|e <pwd up to 48 chars>\n", argv[0]);
        return EXIT_FAILURE;
    }

    do
    {
        bytes_read = fread(blk, 1, BLK_LEN, stdin);

        if (bytes_read > 0)
        {
            // process bytes_read bytes
            memcpy(counter, nonce, NONCE_LEN);

            P52BC(p52bc, counter, key);
            P52((unsigned*) p52bc);
            P52BC(p52bc, p52bc, key);
            //P52BC(p52bc, blk, counter);
            P52BC(p52bc, p52bc, p52bc);

            int j;
            for (j = 47; j > 11; j++)
            {
              counter[j] = counter[j] + 1;

              if (counter[j] != 0)
              {
                break;
              }
            }
            fwrite(p52bc, 1, bytes_read, stdout);
        }
    }
    while (bytes_read == BLK_LEN);
    return EXIT_SUCCESS;
}
