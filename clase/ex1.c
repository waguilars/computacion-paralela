#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define n 5

int main()
{
  // Secuencial
  // int i, num, acum;

  // for (i = 0; i < n; i++)
  // {
  //   num = rand();

  //   acum = acum + num;

  //   printf("num_rand %d\n", num);
  // }
  // printf("valor acumulado %ld\n", acum);

  //Paralelo
  int i, num, acum, total = 0;

  omp_set_num_threads(4);
  srand(time(NULL));
  printf("%d", total);

#pragma omp parallel private(num, i, acum)
  {
    int hilo = omp_get_thread_num();

    i = 0;
    while (i < n)
    {
      num = rand() / 10000000;
      acum = acum + num;
      printf("hilo: %d -> valor: %d\n", hilo, num);
      i++;
    }

    printf("hilo: %d -> acumulado: %d\n", hilo, acum);

    total = total + acum;
  }

  printf("Total: %d\n", total);

  return 0;
}