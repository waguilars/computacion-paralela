#include <stdio.h>
#include <math.h>
#include <omp.h>
/**
 * @author Wilson Aguilar
 */
int main()
{
  float p[] = {79.5, 53.5, 65.1, 52.9, 62.3},
        t[] = {1.50, 1.62, 1.68, 1.73, 1.57},
        imc = 0;

  int n = sizeof p / sizeof p[0];

  omp_set_num_threads(n);
#pragma omp parallel
  {
    int tid = omp_get_thread_num();
#pragma omp critical
    {
      imc = p[tid] / pow(t[tid], 2);
      // printf("imc %d: %f\n", tid, imc);
      if (imc < 20)
        printf("La persona %d tiene %.2f de IMC, esta desnutrida.\n", tid, imc);

      if (imc >= 20 && imc < 25)
        printf("La persona %d tiene %.2f de IMC, esta normal.\n", tid, imc);

      if (imc >= 25 && imc < 30)
        printf("La persona %d tiene %.2f de IMC, esta con sobrepeso.\n", tid, imc);

      if (imc >= 30 && imc < 35)
        printf("La persona %d tiene %.2f de IMC, esta Obesidad Grado 1.\n", tid, imc);

      if (imc >= 35 && imc < 40)
        printf("La persona %d tiene %.2f de IMC, esta Obesidad Grado 2.\n", tid, imc);

      if (imc >= 40)
        printf("La persona %d tiene %.2f de IMC, esta Obesidad Grado 3.\n", tid, imc);
    }
  }

  return 0;
}
