#include <stdio.h>
#include <omp.h>

/**
 * @author Wilson Aguilar
 * Diseña un programa que pida el valor de n y m y calcule C .
 * (Ten en cuenta que n ha de ser mayor o igual que m.).
 *
 * c(m,n) = n! / (n-m)! m!
 */

long int factorize(int value)
{
  if (value == 0)
    return 1;

  long int fact = value * factorize(value - 1);
  return fact;
}

int main()
{
  long int m, n, factm, factn, factnm;
  printf("Ingrese m: ");
  scanf("%ld", &m);
  printf("Ingrese n: ");
  scanf("%ld", &n);

  if (!(n >= m))
  {
    printf("El valor de n debe ser mayor a m!\n");
    return 1;
  }

  omp_set_num_threads(3);

#pragma omp parallel shared(factm, factn, factnm)
  {
    int tid = omp_get_thread_num();

    if (tid == 0)
      factm = factorize(m);

    if (tid == 1)
      factn = factorize(n);

    if (tid == 2)
      factnm = factorize(n - m);
  }

  int c = factn / (factnm * factm);

  printf("El valor de c es: %d\n", c);
  return 0;
}
