#include <stdio.h>

int main(void)
{
  char c = 'a';
  short int s = -32000;
  int i = 1000000;
  long long ll = -1;
  unsigned long long ull = 18446744073709551615ULL;
  double d = 2e1;

  printf("c   : %c %hhd %hho %hhx\n", c, c, c, c);
  printf("s   : %hd %ho %hx\n", s, s, s);
  printf("s   : %hu <- ojo:mal usado\n", s);
  printf("i   : %d |%10d| |%-10d|\n", i, i, i);
  printf("ll  : %lld\n", ll);
  printf("ll  : %llu <- ojo: mal usado\n", ll);
  printf("ull : %llu\n", ull);
  printf("d   : %f %10.2f %+4.2f\n", d, d, d);
  return 0;
}
