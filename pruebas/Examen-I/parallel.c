#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

#define n 4

/**
 * @author Wilson Aguilar
 * Ejercicio 22
 */

void print_mtx(int mtx[n][n])
{
  for (size_t i = 0; i < n; i++)
  {
    for (size_t j = 0; j < n; j++)
    {
      printf("%d\t", mtx[i][j]);
    }
    printf("\n");
  }
}

int main()
{
  int mtx[n][n];
  int sum = 0,
      cont = 0;
  srand(time(NULL));

  omp_set_num_threads(n);
#pragma omp parallel shared(mtx, cont) reduction(+ \
                                                 : sum)
  {
    int tid = omp_get_thread_num();

    if (tid == 0 || tid == (n - 1))
    {
      for (size_t i = 0; i < n; i++)
      {
        mtx[tid][i] = rand() % 10;
        sum += mtx[tid][i];
        cont++;
      }
    }
    else
    {
      mtx[tid][0] = rand() % 10;
      mtx[tid][n - 1] = rand() % 10;

      sum += mtx[tid][0] + mtx[tid][n - 1];
      cont += 2;
    }
  }

  int mean = ceil(sum / (float)cont);
  printf("Promedio redondeado: %d\n", mean);
  // int rn = rand() % (mean + 1 - 0) - 0;
  for (size_t i = 1; i < n - 1; i++)
  {
    for (size_t j = 1; j < n - 1; j++)
    {
      mtx[i][j] = rand() % (mean + 1 - 0) - 0;
    }
  }

  print_mtx(mtx);
  return 0;
}
