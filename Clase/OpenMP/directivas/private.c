#include <stdio.h>
#include <omp.h>
int main(void)
{
  int nthreads, tid = -1;
  printf("trabajaremos con 4 threads\n");
  omp_set_num_threads(4);
  nthreads = omp_get_num_threads(); // obtiene el número de hilos en ejecución
  printf("Número de threads en ejecución = %d\n", nthreads);

#pragma omp parallel private(tid) // Expande un grupo de                         \
                                  // threads.  Cada threads contiene sus propias \
                                  // copias de variables
  {
    tid = omp_get_thread_num();
    printf("hilo = %d\n", tid);
    if (tid == 0)
    {
      nthreads = omp_get_max_threads();
      printf("Numero de threads = %d\n", nthreads);
    }
  }

  printf("\nvalor tid = %d\n", tid);

  printf("trabajemos ahora con 3 threads\n");
  omp_set_num_threads(3);
  nthreads = omp_get_num_threads();
  printf("Número de trheads en ejecución = %d\n\n", nthreads);

#pragma omp parallel
  {
    tid = omp_get_thread_num();
    printf("Hola desde el thread = %d\n", tid);
    if (tid == 0)
    {
      nthreads = omp_get_max_threads();
      printf("Numero de threads = %d\n", nthreads);
    }
  }

  printf("valor tid = %d\n", tid);

  return 0;
}