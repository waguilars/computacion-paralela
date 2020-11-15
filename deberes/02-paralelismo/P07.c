#include <stdio.h>
#include <stdbool.h>
#include <omp.h>

/**
 * @author Wilson Aguilar
 * Dada la matriz de m*n y el vector de tamaño n,
 * determinar que columna de la matriz es igual al vector
 */

int main()
{
  int mtx[4][3] = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9},
      {1, 4, 7}};

  int v[] = {2, 5, 8, 4},
      vlen = sizeof(v) / sizeof(v[0]),
      cols = sizeof(mtx[0]) / sizeof(mtx[0][0]),
      rows = sizeof(mtx[0]) / cols;

  omp_set_num_threads(cols);

#pragma omp parallel firstprivate(mtx)
  {
    int tid = omp_get_thread_num();
    bool is_eq = true;

    for (size_t i = 0; i < vlen; i++)
    {
      // printf("%d - %d \n", mtx[i][tid], v[i]);
      if (mtx[i][tid] != v[i])
      {
        is_eq = false;
        break;
      }
    }

    if (is_eq)
      printf("La columna %d es igual al vector dado.\n", tid);
  }
  return 0;
}
