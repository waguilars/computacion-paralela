#include <stdio.h>
#include <omp.h>
/**
 * @author Wilson Aguilar
 * Realizar un programa que genere las tablas de multiplicar del 1 hasta N 
 * y tablas desde 1 hasta 20.
 * Consideraciones:
    • Cada proceso deberá realizar la tabla de multiplicar del número según su índice.
    • El tamaño de cada tabla será hasta 20 multiplicaciones.
 */

int main()
{
  int n = 5, limit = 20;
  omp_set_num_threads(n);

#pragma omp parallel firstprivate(limit)
  {
    int tid = omp_get_thread_num() + 1;

    for (size_t i = 1; i <= limit; i++)
      printf("%d x %d = %d\t", tid, i, i * tid);
  }

  return 0;
}
