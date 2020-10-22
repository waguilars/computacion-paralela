#include <stdio.h>

int main(void)
{
  int a, c;
  double b;

  printf("Entero a: ");
  scanf("%d", &a);

  printf("Flotante b: ");
  scanf("%lf", &b);

  printf("Entero c: ");
  scanf("%d", &c);

  printf("El entero a es %d, el flotante b es %f y el entero c es %d\n", a, b, c);

  return 0;
}
