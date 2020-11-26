#include <stdio.h>
#include <math.h>
#include <omp.h>

#define n 4
/**
 * @author Wilson Aguilar
 */
void print(int mtx[n][n])
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

  int x[] = {2, 3, 5, 4};
  int d[n][n];

  omp_set_num_threads(n);

#pragma omp parallel
  {
    int tid = omp_get_thread_num();
    int exp = n - tid -1;
    // printf("id: %d, exp: %d\n", tid, exp);

#pragma omp critical
    {
      for (size_t i = 0; i < n; i++)
      {
        // printf("i: %d, tid: %d = %d\n", i, tid, x[i]);
        d[i][tid] = pow(x[i], exp);
      }
    }
  }

  print(d);
  return 0;
}
