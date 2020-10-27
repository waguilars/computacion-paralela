#include <stdio.h>
#include <unistd.h>
#include "omp.h"

int main(void)
{
  int threads;
  printf("Ingrese el numero de hilos: ");
  scanf("%d", &threads);

  int n_procs = omp_get_num_procs();

  omp_set_num_threads(threads);

#pragma omp parallel
  {
    int thread_id = omp_get_thread_num();
    if (thread_id == 0)
    {
      sleep(2);
    }
    printf("Hola soy el hilo %d, se esta ejecutando %d hilos\n", thread_id, omp_get_num_threads());
  }

  return 0;
}
