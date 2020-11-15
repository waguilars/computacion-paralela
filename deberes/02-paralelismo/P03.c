#include <stdio.h>
#include <omp.h>

/**
 * @author Wilson Aguilar
 * Escribir un programa que permita calcular el MCM y el MCD de 2 *Números enteros positivos.
 */
int max_common_divisor(int a, int b)
{
  if (a > b)
    return a % b;
  else
    return b % a;
}

int min_common_multiple(int a, int b)
{
  return a * b / max_common_divisor(a, b);
}

int main()
{
  int mcm, mcd;
  int n1 = 40, n2 = 60;

  omp_set_num_threads(2);

#pragma omp parallel private(mcd, mcm)
  {
    int tid = omp_get_thread_num();
    mcd = max_common_divisor(n1, n2);

    if(tid == 0)
      printf("El MCD de %d y %d es: %d\n", n1, n2, mcd);

    if (tid == 1)
    {
      mcm = n1 * n2 / mcd;
      printf("El MCM de %d y %d es: %d\n", n1, n2, mcm);
    }
  }
}
