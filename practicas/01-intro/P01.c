#include <stdio.h>

int main(void)
{
  char c1 = 1;
  char c2 = -1;
  char c3 = 127;
  char c4 = 128;
  char c5 = -128;
  char c6 = 64L;
  char c7 = 64LL;
  char c8 = 'a';

  unsigned char uc1 = 1;
  unsigned char uc2 = -1;
  unsigned char uc3 = 10L;
  unsigned char uc4 = 1024;

  short s1 = 0;
  short s2 = 32767;
  short s3 = -1;
  short s4 = 32768;

  int i4 = 32768;
  int i5 = 32768L;
  int i6 = 32768LL;
  int i7 = 2147483648L;

  return 0;
}
