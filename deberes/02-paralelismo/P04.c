#include <stdio.h>
#include <omp.h>
#include <math.h>

/**
 * @author Wilson Aguilar
 *  Desarrollar un programa para calcular la siguiente suma:
 * x _ x^3 _ x^5 _ x^7 _ x^9
 *     3!     5!    7     9
 *
 * Indicar el valor de x (0 ≤ x ≤ 1) por teclado y sumar N términos.
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
  int n = 5;
  float x,
        res = 0;

  printf("Ingrese x, x debe cumplir la condicion 0 <= x <= 1: ");
  scanf("%f", &x);

  if (x < 0 && x > 1)
  {
    printf("X no cumple la condicion!\n");
    return 1;
  }

  printf("x -> %f\n", x);
  omp_set_num_threads(n);
#pragma omp parallel shared(x) private(n) reduction(+: res)
  {
    int tid = omp_get_thread_num();
    float value;
    n = (tid + 1) * 2 - 1;

    value = pow(x, n) / factorize(n);
    if (tid % 2 == 0)
    {
      /* Positivos */
      res += value;
    }

    if (tid % 2 == 1)
    {
      /* negativos */
      res -= value;
    }
  }

  printf("Total: %f\n", res);

  return 0;
}
